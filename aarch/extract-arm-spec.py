#!/usr/bin/env python
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023-2024, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# This script downloads a few Arm specifications from the Arm site.
# These specs are tarballs of JSON or XML files which are useful to
# process the description of the Arm ISA or registers. The script also
# extracts information from these files and generates pieces of source
# files which will be copied into source files of the project.
#
# Options:
# --force (-f) : force download even if spec files are already downloaded.
#
#----------------------------------------------------------------------------

import re, os, sys, glob, shutil, subprocess, tarfile, json
import urllib.request, urllib.parse
import xml.etree.ElementTree as etree

# Calling script name, project root.
SCRIPT = os.path.basename(sys.argv[0])
SCRIPTDIR = os.path.dirname(os.path.abspath(sys.argv[0]))
ROOTDIR = os.path.dirname(SCRIPTDIR)

# Force download.
FORCE_DOWNLOAD = '--force' in sys.argv[1:] or '-f' in sys.argv[1:]

# Directory of downloaded files.
OUTPUT_DIR = SCRIPTDIR + '/downloads'

# Arm Web site.
BASE_URL        = 'https://developer.arm.com/downloads/-/exploration-tools'
ISA_PREFIX      = 'ISA_A64_xml_A_profile'
FEATURES_PREFIX = 'AARCHMRS_A_profile'
SYSREG_PREFIX   = 'SysReg_xml_A_profile'
TAR_SUFFIX      = '.tar.gz'

# Reference index files into the downloaded tarballs.
ISAINDEX_FILE  = '@/index.xml'
FEATINDEX_FILE = 'Features.json'
REGINDEX_FILE  = '@/AArch64-regindex.xml'
ENCINDEX_FILE  = '@/enc_index.xml'

# Existing files to verify in the project.
FEATURES_MD   = ROOTDIR + '/docs/features.md'
ARMFEATURES_H = ROOTDIR + '/apps/armfeatures.h'
CPUSYSREGS_H  = ROOTDIR + '/kernel/cpusysregs.h'

# Generated files inside output directory.
FEATURES_MD_OUT   = SCRIPTDIR + '/partial_features.md'
REGISTERS_MD_OUT  = SCRIPTDIR + '/partial_registers.md'
CPUSYSREGS_H_OUT  = SCRIPTDIR + '/partial_cpusysregs.h'
ARMFEATURES_H_OUT = SCRIPTDIR + '/partial_armfeatures.h'
REGVIEW_CPP_OUT   = SCRIPTDIR + '/partial_regview.cpp'

#----------------------------------------------------------------------------
# General-purpose functions
#----------------------------------------------------------------------------

# Get last existing file from a wildcard (assumed most recent if properly named).
# Return None if not found.
def last_file(wildcard):
    files = glob.glob(wildcard)
    files.sort(key=str.lower)
    return None if len(files) == 0 else files[-1]

# Check if a file exists and is executable.
def is_executable(filename):
    return os.path.exists(filename) and os.access(filename, os.X_OK)

# Try to locate Chrome browser.
# Return None if not found.
def get_chrome():
    chrome = None
    for cmd in ['chrome-browser', 'chromium-browser', 'chrome', 'chromium']:
        chrome = shutil.which(cmd)
        if chrome is not None:
            break
    if chrome is None and sys.platform == 'darwin':
        app = '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome'
        if is_executable(app):
            chrome = app
    return chrome

# Get the content of an URL as a text string.
def download_text(url):
    with urllib.request.urlopen(url) as response:
        return response.read().decode('utf-8')

# Get the output of a command as a text string.
def command_text(args):
    return subprocess.run(args, stdout=subprocess.PIPE).stdout.decode('utf-8')

# Search an URL in a downloaded HTML text.
# Return None if not found.
def extract_url(html, prefix, suffix, base_url):
    # Get all 'href="..."'
    hrefs = re.findall('href="[^"]*/' + prefix.replace('.', '\\.') + '[^"]*' + suffix.replace('.', '\\.') + '"', html)
    # Remove all 'href="' and '"' and resolve relative URL's.
    urls = [urllib.parse.urljoin(base_url, h[6:-1]) for h in hrefs]
    urls.sort()
    return None if len(urls) == 0 else urls[-1]

# Download an archive.
# Return local file path or None if not found.
def download_archive(url, description):
    if url is None:
        print('No URL found for %s' % description)
        return None
    else:
        print('Downloading %s ...' % url)
        filename = '%s/%s' % (OUTPUT_DIR, os.path.basename(urllib.parse.urlsplit(url).path))
        with urllib.request.urlopen(url) as response:
            with open(filename, 'wb') as output:
                output.write(response.read())
        return filename

# Get a system register name from a MSR or MRS instruction.
# Return None if not found.
def get_register_from_instruction(inst):
    if not isinstance(inst,str) or ',' not in inst:
        return None
    inst = inst.strip().upper()
    if inst.startswith('MRS '):
        return re.sub(r'.*,', '', inst).strip()
    elif inst.startswith('MSR '):
        return re.sub(r',.*', '', inst[3:]).strip()
    else:
        return None

# Format a string as a binary literal "0b...".
# Return None if invalid.
def bin_literal(op):
    if not isinstance(op,str):
        return None
    op = op.strip()
    if not op.startswith('0b'):
        op = '0b' + op
    if op == '0b':
        return None
    for c in op[2:]:
        if c != '0' and c != '1':
            return None
    return op

#----------------------------------------------------------------------------
# Download phase
#----------------------------------------------------------------------------

# Initial tarballs, if already downloaded.
ISA_TARBALL = last_file('%s/%s*%s' % (OUTPUT_DIR, ISA_PREFIX, TAR_SUFFIX))
FEATURES_TARBALL = last_file('%s/%s*%s' % (OUTPUT_DIR, FEATURES_PREFIX, TAR_SUFFIX))
SYSREG_TARBALL = last_file('%s/%s*%s' % (OUTPUT_DIR, SYSREG_PREFIX, TAR_SUFFIX))

# Make sure output directory is created.
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Download files if required.
if not FORCE_DOWNLOAD and ISA_TARBALL is not None and FEATURES_TARBALL is not None and SYSREG_TARBALL is not None:
    for file in [ISA_TARBALL, FEATURES_TARBALL, SYSREG_TARBALL]:
        print('Already downloaded: %s' % os.path.relpath(file, ROOTDIR))
else:
    print('Downloading %s ...' % BASE_URL)
    # Download HTML text form Web page.
    text = download_text(BASE_URL)
    # Try to find the three URL's in the returned HTML text.
    isa_url = extract_url(text, ISA_PREFIX, TAR_SUFFIX, BASE_URL)
    features_url = extract_url(text, FEATURES_PREFIX, TAR_SUFFIX, BASE_URL)
    sysreg_url = extract_url(text, SYSREG_PREFIX, TAR_SUFFIX, BASE_URL)
    if isa_url is None or features_url is None or sysreg_url is None:
        # Not found in returned HTML content, probably generated by scripts in the page.
        chrome = get_chrome()
        if chrome is None:
            print('Error: Information not found in returned HTML, install Chrome to generate the page')
            exit(1)
        else:
            print('Information not found in returned HTML, using Chrome to generate the page')
            text = command_text([chrome, '--headless', '--dump-dom', BASE_URL])
            isa_url = extract_url(text, ISA_PREFIX, TAR_SUFFIX, BASE_URL)
            features_url = extract_url(text, FEATURES_PREFIX, TAR_SUFFIX, BASE_URL)
            sysreg_url = extract_url(text, SYSREG_PREFIX, TAR_SUFFIX, BASE_URL)
    # Try to download the three tarballs.
    ISA_TARBALL = download_archive(isa_url, 'ISA')
    FEATURES_TARBALL = download_archive(features_url, 'Features')
    SYSREG_TARBALL = download_archive(sysreg_url, 'SysReg')

# Expand an archive, optionally only if a reference file does not exist.
# The reference file is relative inside the output directory and '@' is replaced with the archive base name.
# Return output directory of files and full path of reference file.
def expand(tarball, reffile=None, force=False):
    tarname = os.path.basename(tarball)
    dirname = tarname.removesuffix(TAR_SUFFIX)
    outdir = '%s/%s' % (OUTPUT_DIR, dirname)
    # Check presence of reference file.
    if reffile is not None:
        reffile = '%s/%s' % (outdir, reffile.replace('@', dirname))
        if not force and os.path.exists(reffile):
            print('Already expanded: %s' % tarname)
            return outdir, reffile
    # Reference file not found, need to expand the archive.
    print('Expanding %s into %s ...' % (tarname, os.path.relpath(outdir, ROOTDIR)))
    with tarfile.open(tarball) as tar:
        # Check if all files already start with the dirname.
        start_all = True
        for info in tar.getmembers():
            if not info.name.startswith(dirname + '/'):
                start_all = False
                break
        if start_all:
            tar.extractall(OUTPUT_DIR, filter='data')
        else:
            tar.extractall(outdir, filter='data')
        return outdir, reffile

# Expand all archives.
ISA_DIR, ISAINDEX_FILE = expand(ISA_TARBALL, ISAINDEX_FILE, FORCE_DOWNLOAD)
FEATURES_DIR, FEATINDEX_FILE = expand(FEATURES_TARBALL, FEATINDEX_FILE, FORCE_DOWNLOAD)
SYSREG_DIR, REGINDEX_FILE = expand(SYSREG_TARBALL, REGINDEX_FILE, FORCE_DOWNLOAD)
ENCINDEX_FILE = ENCINDEX_FILE.replace('@', os.path.dirname(REGINDEX_FILE))

#----------------------------------------------------------------------------
# Extract list of features
#----------------------------------------------------------------------------

# Definition of a feature.
class Feature:
    def __init__(self, name='', optional='', mandatory='', sysregs='', description=''):
        self.name = name
        self.optional = optional
        self.mandatory = mandatory
        self.sysregs = sysregs
        self.description = description
        self.documented = False
    def removed(self):
        return self.description.endswith('(removed)')

# Default header line:
headers = Feature('Feature', 'Optional', 'Mandatory', 'sysregs', 'Description')

# Dictionary of features, indexed by name:
all_features = dict()

# Load all features which are already documented in this project.
removed = 0
pattern = re.compile(r'\| +([^\|]+)\|([^\|]+)\|([^\|]+)\|([^\|]+)\|(.*)')
with open(FEATURES_MD, 'r') as file:
    for line in file:
        match = pattern.fullmatch(line.strip())
        if match is None or match.group(1) == '' or match.group(1).startswith('-'):
            pass
        else:
            f = [match.group(i).strip() for i in range(1, 6)]
            feat = Feature(f[0], f[1], f[2], f[3], f[4])
            if feat.name.startswith('FEAT_'):
                all_features[feat.name] = feat
                if feat.removed():
                    removed += 1
            else:
                headers = feat

print('Existing features: %d, %d marked as "removed"' % (len(all_features), removed))

# Load the description of all features from the downloaded tarball.
with open(FEATINDEX_FILE, 'r') as file:
    jfeatures = json.load(file)

loaded_features = 0
new_features = 0
for param in jfeatures.get('parameters', []):
    if isinstance(param, dict) and param.get('name','').startswith('FEAT_'):
        # Found a loaded feature.
        loaded_features += 1
        name = param.get('name','')
        if name in all_features:
            feat = all_features[name]
        else:
            new_features += 1
            feat = Feature(name)
            feat.sysregs = '???'  # indicate that we need to check
            all_features[name] = feat
        # Mark the feature as documented by Arm.
        feat.documented = True
        # Get description from title. Do not override if already existing
        # (this is an existing feature, the name of which was manually edited).
        if feat.description == '':
            feat.description = param.get('title','').strip()
        # Concatenate all description fields from the JSON entry.
        text = ''
        desc = param.get('description')
        if isinstance(desc, dict):
            for key in ('before', 'after'):
                text1 = desc.get(key)
                if isinstance(text1, str):
                    text += text1
                elif isinstance(text1, list):
                    for text2 in text1:
                        text += str(text2)
        # Get versions where the feature was introduced.
        text = text.lower()
        opt = re.search(name.lower() + r' +is +optional +from +armv([0-9\.]*[0-9])', text);
        mand = re.search(name.lower() + r' +is +mandatory +from +armv([0-9\.]*[0-9])', text);
        if opt is not None:
            feat.optional = 'Armv' + opt.group(1)
        if mand is not None:
            feat.mandatory = 'Armv' + mand.group(1)

print('Loaded features: %d, %d new' % (loaded_features, new_features))

# Check legacy features in the list of features in this project.
for feat in all_features.values():
    if not feat.documented and not feat.removed():
        print('--- %s is not longer documented, should be marked as (removed)' % feat.name)

# Compute column widths.
name_width = max(len(headers.name), max([len(f.name) for f in all_features.values()]))
opt_width = max(len(headers.optional), max([len(f.optional) for f in all_features.values()]))
mand_width = max(len(headers.mandatory), max([len(f.mandatory) for f in all_features.values()]))
sys_width = max(len(headers.sysregs), max([len(f.sysregs) for f in all_features.values()]))
desc_width = len(headers.description)

# Build list of features.
with open(FEATURES_MD_OUT, 'w') as output:
    print('<!-- automatically generated by %s from %s -->' % (SCRIPT, os.path.basename(FEATURES_DIR)), file=output)
    print(file=output)
    print('| %-*s | %-*s | %-*s | %-*s | %s' %
          (name_width, headers.name, opt_width, headers.optional,
           mand_width, headers.mandatory, sys_width, headers.sysregs, headers.description),
          file=output)
    print('| %s | %s | %s | :%s: | %s' %
          (name_width * '-', opt_width * '-', mand_width * '-', (sys_width - 2) * '-', desc_width * '-'),
          file=output)
    for key in sorted(all_features.keys(), key=str.lower):
        feat = all_features[key]
        print('| %-*s | %-*s | %-*s | %s | %s' %
              (name_width, feat.name, opt_width, feat.optional,
               mand_width, feat.mandatory, feat.sysregs.center(sys_width), feat.description),
              file=output)

#----------------------------------------------------------------------------
# Extract list of system registers
#----------------------------------------------------------------------------

# Definition of a bitfield inside a register.
class Bitfield:
    def __init__(self, name, msb, lsb):
        self.name = name
        self.lsb = int(lsb)
        self.bits = int(msb) - self.lsb + 1

# Definition of a system register.
class Register:
    def __init__(self, name):
        self.name = name
        self.description = ''
        self.size = 64           # Register size in bits, some of them are 128-bit
        self.cppfield = None     # C++ field name in class ArmFeatures
        self.cppindex = -1       # Order in class ArmFeatures
        self.cpusysregs = False  # Can be accessed from cpusysregs kernel module
        self.encoding = None     # String of op0, op1, CRn, CRm, op2
        self.bitfields = None    # List of Bitfield
    def set_encoding(self, op0, op1, CRn, CRm, op2):
        enc = []
        for bits in (op0, op1, CRn, CRm, op2):
            bits = bin_literal(bits)
            if bits is None:
                return
            enc.append(bits)
        enc = ', '.join(enc)
        if self.encoding is not None and self.encoding != enc:
            print('--- Conflicting encodings for register %s: %s vs. %s' % (self.name, self.encoding, enc))
        else:
            self.encoding = enc

# Dictionary of registers, indexed by name:
all_registers = dict()

# Get register entry.
def get_register(name):
    global all_registers
    if name in all_registers:
        reg = all_registers[name]
    else:
        reg = Register(name)
        all_registers[name] = reg
    return reg

# Load all registers which are used in C++ class ArmFeatures.
pattern = re.compile(r'csr_u64_t +(_[a-zA-Z0-9_]+) *=.*@REG: +([a-zA-Z0-9_]+)')
index = 0
with open(ARMFEATURES_H, 'r') as file:
    for line in file:
        match = pattern.match(line.strip())
        if match is not None:
            reg = get_register(match.group(2))
            reg.cppfield = match.group(1)
            reg.cppindex = index
            index += 1

print('Registers used to check Arm features: %d' % len(all_registers))

# Load all registers which can be accessed by the cpusysreg kernel module.
pattern = re.compile(r'CSR_REGID_([a-zA-Z0-9_]+), ')
count = 0
with open(CPUSYSREGS_H, 'r') as file:
    for line in file:
        match = pattern.match(line.strip())
        if match is not None and match.group(1) != 'INVALID':
            get_register(match.group(1)).cpusysregs = True
            count += 1

print('Registers accessible through cpusysregs: %d' % count)

# Load the XML file containing the list of all registers and their individual XML files.
xmlfiles = []
xmldir = os.path.dirname(REGINDEX_FILE)
xmltree = etree.parse(REGINDEX_FILE)
for link in xmltree.findall('.//register_links/register_link'):
    filename = link.attrib.get('registerfile', '')
    if filename != '':
        xmlfiles.append(filename)

print('XML files for registers: %d' % len(xmlfiles))

# Load all register descriptions, file by file.
for filename in xmlfiles:
    xmltree = etree.parse('%s/%s' % (xmldir, filename))
    # Get register name, ignore generic names with '<n>'
    regname = xmltree.findtext('.//registers/register/reg_short_name')
    if regname is not None and not re.match('.*<.*>.*', regname):
        regname = regname.strip().upper()
        reg = get_register(regname)
        # Get register encoding.
        # Warning: In file "X.xml", with reg_short_name "X", sometimes there are encodings for
        # another register Y in addition to X, normally redundant with file "Y.xml". So, differentiate
        # register names from reg_short_name and access_instruction. Seen for TCR_EL1 in TCR_EL2.
        for xenc in xmltree.findall('.//encoding'):
            # Register name and encoding is extracted from MSR or MRS or both.
            # Some registers a WO, RO or R/W.
            enc_regname = get_register_from_instruction(xenc.findtext('./access_instruction'))
            op0 = xenc.find('./enc[@n="op0"]')
            op1 = xenc.find('./enc[@n="op1"]')
            CRn = xenc.find('./enc[@n="CRn"]')
            CRm = xenc.find('./enc[@n="CRm"]')
            op2 = xenc.find('./enc[@n="op2"]')
            if None not in (enc_regname, op0, op1, CRn, CRm, op2):
                get_register(enc_regname).set_encoding(op0.get('v'), op1.get('v'), CRn.get('v'), CRm.get('v'), op2.get('v'))
        # Get description.
        desc = xmltree.findtext('.//registers/register/reg_long_name')
        if desc is not None:
            desc = desc.strip()
            if desc != '':
                reg.description = desc
        # Get bitfields in the register.
        xfields = xmltree.find('.//fields')
        if (reg.cpusysregs or reg.cppfield is not None) and xfields is not None:
            reg.bitfields = []
            length = xfields.get('length', '')
            if length.isdigit():
                reg.size = int(length)
            for xf in xfields.findall('.//field'):
                name = xf.findtext('./field_name')
                msb = xf.findtext('./field_msb')
                lsb = xf.findtext('./field_lsb')
                if None not in (name, msb, lsb):
                    reg.bitfields.append(Bitfield(name, msb, lsb))
            # Sort all bitfields from msb to lsb.
            reg.bitfields.sort(key=lambda x: x.lsb, reverse=True)
            # Verify the all fields are consistent.
            for bf in reg.bitfields:
                if bf.lsb + bf.bits > reg.size:
                    print('--- Invalid bitfield %d:%d %s_%s' % (bf.lsb, bf.bits, reg.name, bf.name))
            # Look for duplicates (there are some) and remove them.
            i = 1
            while i < len(reg.bitfields):
                if reg.bitfields[i-1].name != reg.bitfields[i].name:
                    i += 1
                else:
                    del reg.bitfields[i]

print('Known registers: %d' % len(all_registers))

# Load missing encodings from enc_index.xml
xmltree = etree.parse(ENCINDEX_FILE)
for row in xmltree.findall('.//row'):
    op0 = row.findtext('./entry[@field="op0"]')
    op1 = row.findtext('./entry[@field="op1"]')
    CRn = row.findtext('./entry[@field="CRn"]')
    CRm = row.findtext('./entry[@field="CRm"]')
    op2 = row.findtext('./entry[@field="op2"]')
    if None not in (op0, op1, CRn, CRm, op2):
        for entry in row.findall('./entry'):
            name = entry.findtext('.')
            if name in all_registers:
                 get_register(name).set_encoding(op0, op1, CRn, CRm, op2)

# Fixed missing descriptions for _EL12 and _EL02 registers.
for reg in all_registers.values():
    if reg.description == '':
        if reg.name.endswith('_EL12') and reg.name[:-1] in all_registers:
            reg.description = all_registers[reg.name[:-1]].description.replace('EL1', 'EL1&2')
        elif reg.name.endswith('_EL02') and reg.name[:-1] in all_registers:
            reg.description = all_registers[reg.name[:-1]].description.replace('EL0', 'EL0&2')

# Build list of register.
reg_header = ('System Register', 'Description')
reg_width = max(len(reg_header[0]), max([len(r.name) for r in all_registers.values()]))
with open(REGISTERS_MD_OUT, 'w') as output:
    print('<!-- automatically generated by %s from %s -->' % (SCRIPT, os.path.basename(SYSREG_DIR)), file=output)
    print(file=output)
    print('Total: %d system registers.' % len(all_registers), file=output)
    print(file=output)
    print('| %-*s | %s' % (reg_width, reg_header[0], reg_header[1]), file=output)
    print('| %s | %s' % (reg_width * '-', len(reg_header[1]) * '-'), file=output)
    for key in sorted(all_registers.keys(), key=str.lower):
        reg = all_registers[key]
        print(('| %-*s | %s' % (reg_width, reg.name, reg.description)).strip(), file=output)

# Generate the C/C++ definitions of the register encodings.
name_width = max([len(name) for name in all_registers])
with open(CPUSYSREGS_H_OUT, 'w') as output:
    print('// automatically generated by %s from %s' % (SCRIPT, os.path.basename(SYSREG_DIR)), file=output)
    for name in sorted(all_registers.keys()):
        reg = all_registers[name]
        if reg.encoding is None:
            print('--- Undefined encoding for register %s' % name)
        else:
            print('#define CSR_SREG_%-*s  CSR_SREG(%s)' % (name_width, name, reg.encoding), file=output)

# Generate the C/C++ definitions for armfeatures.h.
cppregs = [reg for reg in all_registers.values() if reg.cppfield is not None and reg.bitfields is not None]
cppregs.sort(key=lambda x: x.cppindex)
with open(ARMFEATURES_H_OUT, 'w') as output:
    print('    // automatically generated by %s from %s' % (SCRIPT, os.path.basename(SYSREG_DIR)), file=output)
    for reg in cppregs:
        for bf in reg.bitfields:
            typename = 'int' if bf.bits < 32 else 'csr_u64_t'
            shift = '' if bf.lsb == 0 else ' >> %d' % bf.lsb
            mask = 0xFFFFFFFFFFFFFFFF >> (64 - bf.bits)
            print('    %s %s_%s() const { return (%s)(%s%s) & 0x%02X; }' %
                  (typename, reg.name, bf.name, typename, reg.cppfield, shift, mask), file=output)
        print(file=output)

# Generate the C/C++ template data structure for regview.cpp.
with open(REGVIEW_CPP_OUT, 'w') as output:
    print('    // automatically generated by %s from %s' % (SCRIPT, os.path.basename(SYSREG_DIR)), file=output)
    for reg in [reg for reg in all_registers.values() if reg.cpusysregs]:
        print('    {', file=output)
        print('        "%s", CSR_REGID_%s, READ,' % (reg.name, reg.name), file=output)
        print('        {', file=output)
        if reg.bitfields is not None and len(reg.bitfields) > 0:
            width = 3 + max([len(bf.name) for bf in reg.bitfields])
            for bf in reg.bitfields:
                name = '"%s",' % bf.name
                print('            {%-*s %2d, %2d, {}},' % (width, name, bf.lsb + bf.bits - 1, bf.lsb), file=output)
        print('        }', file=output)
        print('    },', file=output)
