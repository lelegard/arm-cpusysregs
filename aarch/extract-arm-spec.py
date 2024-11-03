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
# --download (-d) : download only, do not generate the data.
# --force (-f) : force download even if spec files are already downloaded.
#
#----------------------------------------------------------------------------

import re, os, sys, glob, shutil, subprocess, tarfile, json
import urllib.request, urllib.parse
import xml.etree.ElementTree as etree

# Arm Web site and its files.
BASE_URL        = 'https://developer.arm.com/downloads/-/exploration-tools'
ISA_PREFIX      = 'ISA_A64_xml_A_profile'
FEATURES_PREFIX = 'AARCHMRS_A_profile'
SYSREG_PREFIX   = 'SysReg_xml_A_profile'
TAR_SUFFIX      = '.tar.gz'

# Reference index files into the downloaded tarballs.
ISAINDEX_FILE   = '@/index.xml'
FEATINDEX_FILE  = 'Features.json'
REGINDEX_FILE   = '@/AArch64-regindex.xml'
ENCINDEX_FILE   = '@/enc_index.xml'

# Calling script name, project root.
SCRIPT    = os.path.basename(sys.argv[0])
SCRIPTDIR = os.path.dirname(os.path.abspath(sys.argv[0]))
ROOTDIR   = os.path.dirname(SCRIPTDIR)

# Command line options.
DOWNLOAD_ONLY  = '--download' in sys.argv[1:] or '-d' in sys.argv[1:]
FORCE_DOWNLOAD = '--force' in sys.argv[1:] or '-f' in sys.argv[1:]

# Directory of downloaded files.
OUTPUT_DIR = SCRIPTDIR + '/downloads'

# Existing files to update in the project.
FEATURES_MD     = ROOTDIR + '/docs/features.md'
REGISTERS_MD    = ROOTDIR + '/docs/registers.md'
BITFIELDS_MD    = ROOTDIR + '/docs/registers-fields.md'
INSTRUCTIONS_MD = ROOTDIR + '/docs/instructions.md'
ARMFEATURES_H   = ROOTDIR + '/apps/armfeatures.h'
CPUSYSREGS_H    = ROOTDIR + '/kernel/cpusysregs.h'

# Generated files inside output directory.
REGVIEW_CPP_OUT = SCRIPTDIR + '/partial_regview.cpp'

#----------------------------------------------------------------------------
# Description of an Arm feature.
#----------------------------------------------------------------------------

class Feature:
    # Constructor.
    def __init__(self, name='', optional='', mandatory='', sysregs='', description=''):
        self.name = name
        self.optional = optional        # Feature is optional starting from this architecture version.
        self.mandatory = mandatory      # Feature become mandatory starting from this architecture version.
        self.sysregs = sysregs          # Value in column sysregs
        self.description = description
        self.documented = False         # Documented in Arm JSON file.

    # Static field: Dictionary of all features, indexed by name.
    byname = dict()

    # Static method: Get a feature entry. Create it if necessary.
    def get(name):
        if name in Feature.byname:
            feat = Feature.byname[name]
        else:
            feat = Feature(name)
            Feature.byname[name] = feat
        return feat

    # Check if a feature is marked as removed in its description.
    def removed(self):
        return self.description.endswith('(removed)')

#----------------------------------------------------------------------------
# Description of a system register.
#----------------------------------------------------------------------------

# Definition of a bitfield inside a register.
class Bitfield:
    # Constructor.
    def __init__(self, name, msb, lsb):
        self.name = name
        self.lsb = int(lsb)
        self.bits = int(msb) - self.lsb + 1
        self.description = ''

# Definition of a system register.
class Register:
    # Constructor.
    def __init__(self, name):
        self.name = name
        self.description = ''
        self.size = 64           # Register size in bits, some of them are 128-bit
        self.cppfield = None     # C++ field name in class ArmFeatures
        self.cppindex = -1       # Order in class ArmFeatures
        self.cpusysregs = False  # Can be accessed from cpusysregs kernel module
        self.encoding = None     # String of op0, op1, CRn, CRm, op2
        self.bitfields = None    # List of Bitfield

    # Static field: Dictionary of all registers, indexed by name.
    byname = dict()

    # Static method: Get a register entry. Create it if necessary.
    def get(name):
        if name in Register.byname:
            reg = Register.byname[name]
        else:
            reg = Register(name)
            Register.byname[name] = reg
        return reg

    # Static method: Get a system register name from a MSR or MRS instruction.
    # Return None if not found.
    def get_name_from_instruction(inst):
        if not isinstance(inst,str) or ',' not in inst:
            return None
        inst = inst.strip().upper()
        if inst.startswith('MRS '):
            return re.sub(r'.*,', '', inst).strip()
        elif inst.startswith('MSR '):
            return re.sub(r',.*', '', inst[3:]).strip()
        else:
            return None

    # Static method: Format a string as a binary literal "0b...".
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

    # Define the op0, op1, CRn, CRm, op2 encoding of a register.
    # Each of them can be None, '0101..', '0b0101..'
    def set_encoding(self, op0, op1, CRn, CRm, op2):
        enc = []
        for bits in (op0, op1, CRn, CRm, op2):
            bits = Register.bin_literal(bits)
            if bits is None:
                return
            enc.append(bits)
        enc = ', '.join(enc)
        if self.encoding is not None and self.encoding != enc:
            print('--- Conflicting encodings for register %s: %s vs. %s' % (self.name, self.encoding, enc))
        else:
            self.encoding = enc

#----------------------------------------------------------------------------
# Description of a class of instructions.
#----------------------------------------------------------------------------

class InstructionClass:
    # Constructor.
    def __init__(self, name, indexfile='', count=0):
        self.name = name
        self.indexfile = indexfile
        self.count = count

# Constant static field: all known instruction classes.
InstructionClass.all = [
    InstructionClass('Base', '@/index.xml'),
    InstructionClass('SIMD', '@/fpsimdindex.xml'),
    InstructionClass('SVE',  '@/sveindex.xml'),
    InstructionClass('SME',  '@/mortlachindex.xml')]

#----------------------------------------------------------------------------
# Description of an instruction.
#----------------------------------------------------------------------------

class Instruction:
    # Constructor.
    def __init__(self, name, description, iclass):
        self.name = name
        self.description = description
        self.iclass = iclass

    # Static field: Dictionary of all instructions, indexed by name.
    # Each entry is a list of instructions with that name.
    byname = dict()

    # Static method: add a new instruction, resolve name conflicts.
    def addnew(name, description, iclass):
        inst = Instruction(name, description, iclass)
        if name in Instruction.byname:
            Instruction.byname[name].append(inst)
        else:
            Instruction.byname[name] = [inst]

    # Static method: Split a string containing a list of instructions.
    def splitnames(s):
        # Names are separated with commas. But commas can be in description between parentheses.
        result = []
        parts = [p.strip() for p in ('' if s is None else s).split(',')]
        for part in [p for p in parts if p != '']:
            # Check if previous name contains an open parenthesis.
            append = False
            if len(result) > 0:
                opar = result[-1].rfind('(')
                cpar = result[-1].rfind(')')
                append = opar >= 0 and cpar < opar
            if append:
                result[-1] += ', ' + part
            else:
                result.append(part)
        return result

#----------------------------------------------------------------------------
# Description of a text file with an automatically generated part.
#----------------------------------------------------------------------------

class AutoGenFile:
    # Static fields: markers.
    BEGIN = "@AUTOGEN-BEGIN"
    END = "@AUTOGEN-END"

    # Constructor: load the file.
    def __init__(self, name, drop_content):
        self.filename = name
        self.before = []      # Lines before the autogenerated part.
        self.content = []     # Previous content of the autogenerated part.
        self.after = []       # Lines after the autogenerated part.

        # Read the initial content of the file.
        state = 'before'
        with open(name, 'r') as input:
            for line in input:
                line = line.rstrip()
                if state == 'before':
                    self.before.append(line)
                    if AutoGenFile.BEGIN in line:
                        state = 'content'
                elif state == 'content':
                    if AutoGenFile.END in line:
                        state = 'after'
                        self.after.append(line)
                    elif not drop_content:
                        self.content.append(line)
                else:
                    self.after.append(line)
        if state == 'before':
            print('*** No %s found in %s' % (AutoGenFile.BEGIN, name), file=sys.stderr)
            exit(1)
        if state == 'content':
            print('*** No %s found in %s' % (AutoGenFile.END, name), file=sys.stderr)
            exit(1)

    # Get the file basename.
    def name(self):
        return os.path.basename(self.filename)

    # Save the initial part of the file and return the file object.
    def rewrite(self):
        output = open(self.filename, 'w')
        for line in self.before:
            print(line, file=output)
        return output

    # Write the trailer part of the file.
    def complete(self, output):
        for line in self.after:
            print(line, file=output)

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

# Expand all archives, resolve path of reference files.
ISA_DIR, ISAINDEX_FILE = expand(ISA_TARBALL, ISAINDEX_FILE, FORCE_DOWNLOAD)
FEATURES_DIR, FEATINDEX_FILE = expand(FEATURES_TARBALL, FEATINDEX_FILE, FORCE_DOWNLOAD)
SYSREG_DIR, REGINDEX_FILE = expand(SYSREG_TARBALL, REGINDEX_FILE, FORCE_DOWNLOAD)
ENCINDEX_FILE = ENCINDEX_FILE.replace('@', os.path.dirname(REGINDEX_FILE))
for iclass in InstructionClass.all:
    iclass.indexfile = iclass.indexfile.replace('@', os.path.dirname(ISAINDEX_FILE))

if DOWNLOAD_ONLY:
    exit(0)

#----------------------------------------------------------------------------
# Load files to be automatically updated.
#----------------------------------------------------------------------------

file_features_md     = AutoGenFile(FEATURES_MD, False)
file_registers_md    = AutoGenFile(REGISTERS_MD, True)
file_bitfields_md    = AutoGenFile(BITFIELDS_MD, True)
file_instructions_md = AutoGenFile(INSTRUCTIONS_MD, True)
file_armfeatures_h   = AutoGenFile(ARMFEATURES_H, True)
file_cpusysregs_h    = AutoGenFile(CPUSYSREGS_H, True)

# Extract the definition of Arm features, potentially previously manually edited.
removed = 0
feat_headers = Feature('Feature', 'Optional', 'Mandatory', 'sysregs', 'Description')
pattern = re.compile(r'\| +([^\|]+)\|([^\|]+)\|([^\|]+)\|([^\|]+)\|(.*)')
for line in file_features_md.content:
    match = pattern.fullmatch(line)
    if match is not None and match.group(1) != '' and not match.group(1).startswith('-'):
        f = [match.group(i).strip() for i in range(1, 6)]
        feat = Feature(f[0], f[1], f[2], f[3], f[4])
        if feat.name.startswith('FEAT_'):
            Feature.byname[feat.name] = feat
            if feat.removed():
                removed += 1
        else:
            feat_headers = feat

print('Existing features in %s: %d, %d marked as "removed"' % (file_features_md.name(), len(Feature.byname), removed))

# Extract which features are detectable in armfeature.h.
detectable = 0
pattern = re.compile(r' *bool +(FEAT_[a-zA-Z0-9_]+)\(\) +const +{')
for line in file_armfeatures_h.after:
    match = pattern.match(line)
    if match is not None:
        Feature.get(match.group(1)).sysregs = 'X'
        detectable += 1

print('Detectable features in %s: %d' % (file_armfeatures_h.name(), detectable))

# Extract all registers which are used in C++ class ArmFeatures.
index = 0
pattern = re.compile(r' *csr_u64_t +(_[a-zA-Z0-9_]+) *=.*@REG: +([a-zA-Z0-9_]+)')
for line in file_armfeatures_h.after:
    match = pattern.match(line)
    if match is not None:
        reg = Register.get(match.group(2))
        reg.cppfield = match.group(1)
        reg.cppindex = index
        index += 1

print('Registers used to check features in %s: %d' % (file_armfeatures_h.name(), len(Register.byname)))

# Extract all registers which can be accessed by the cpusysreg kernel module.
count = 0
pattern = re.compile(r'CSR_REGID_([a-zA-Z0-9_]+), ')
for line in file_cpusysregs_h.before:
    match = pattern.match(line.strip())
    if match is not None and match.group(1) != 'INVALID':
        Register.get(match.group(1)).cpusysregs = True
        count += 1

print('Registers accessible through %s: %d' % (file_cpusysregs_h.name(), count))

#----------------------------------------------------------------------------
# Extract list of features from downloaded tarballs.
#----------------------------------------------------------------------------

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
        if name not in Feature.byname:
            new_features += 1
        feat = Feature.get(name)
        feat.documented = True
        if feat.sysregs == '':
            feat.sysregs = '???'  # indicate that we need to check
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
        # Check if feature was incorrectly marked '(removed)' in features.md.
        if feat.removed():
            print('--- %s is documented, should not be marked as (removed)' % feat.name)

print('Loaded features from %s: %d, %d new' % (os.path.basename(os.path.dirname(FEATINDEX_FILE)), loaded_features, new_features))

# Check legacy features in the list of features in this project.
for feat in Feature.byname.values():
    if not feat.documented and not feat.removed():
        print('--- %s is no longer documented, should be marked as (removed)' % feat.name)

#----------------------------------------------------------------------------
# Extract list of system registers from downloaded tarballs.
#----------------------------------------------------------------------------

# Load the XML file containing the list of all registers and their individual XML files.
xmlfiles = []
xmldir = os.path.dirname(REGINDEX_FILE)
xmltree = etree.parse(REGINDEX_FILE)
for link in xmltree.findall('.//register_links/register_link'):
    filename = link.attrib.get('registerfile', '')
    if filename != '':
        xmlfiles.append(filename)

print('XML files for system registers in %s: %d' % (os.path.basename(xmldir), len(xmlfiles)))

# Load all register descriptions, file by file.
for filename in xmlfiles:
    xmltree = etree.parse('%s/%s' % (xmldir, filename))
    # Get register name, ignore generic names with '<n>'
    regname = xmltree.findtext('.//registers/register/reg_short_name')
    if regname is not None and not re.match('.*<.*>.*', regname):
        regname = regname.strip().upper()
        reg = Register.get(regname)
        # Get register encoding.
        # Warning: In file "X.xml", with reg_short_name "X", sometimes there are encodings for
        # another register Y in addition to X, normally redundant with file "Y.xml". So, differentiate
        # register names from reg_short_name and access_instruction. Seen for TCR_EL1 in TCR_EL2.
        for xenc in xmltree.findall('.//encoding'):
            # Register name and encoding is extracted from MSR or MRS or both.
            # Some registers a WO, RO or R/W.
            enc_regname = Register.get_name_from_instruction(xenc.findtext('./access_instruction'))
            op0 = xenc.find('./enc[@n="op0"]')
            op1 = xenc.find('./enc[@n="op1"]')
            CRn = xenc.find('./enc[@n="CRn"]')
            CRm = xenc.find('./enc[@n="CRm"]')
            op2 = xenc.find('./enc[@n="op2"]')
            if None not in (enc_regname, op0, op1, CRn, CRm, op2):
                Register.get(enc_regname).set_encoding(op0.get('v'), op1.get('v'), CRn.get('v'), CRm.get('v'), op2.get('v'))
        # Get description.
        desc = xmltree.findtext('.//registers/register/reg_long_name')
        if desc is not None:
            desc = desc.strip()
            if desc != '':
                reg.description = desc
        # Get bitfields in the register.
        xfields = xmltree.find('.//fields')
        if xfields is not None:
            reg.bitfields = []
            length = xfields.get('length', '')
            if length.isdigit():
                reg.size = int(length)
            for xf in xfields.findall('.//field'):
                name = xf.findtext('./field_name')
                msb = xf.findtext('./field_msb')
                lsb = xf.findtext('./field_lsb')
                if None not in (name, msb, lsb):
                    bf = Bitfield(name, msb, lsb)
                    for xdesc in xf.findall('./field_description[@order="before"]'):
                        for text in xdesc.itertext():
                            text = text.strip()
                            if text != '':
                                if bf.description != '':
                                    bf.description += ' '
                                bf.description += text
                        if bf.description != '':
                            break
                    reg.bitfields.append(bf)
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

print('Known registers in %s: %d' % (os.path.basename(xmldir), len(Register.byname)))

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
            if name in Register.byname:
                 Register.get(name).set_encoding(op0, op1, CRn, CRm, op2)

# Fixed missing descriptions for _EL12 and _EL02 registers.
for reg in Register.byname.values():
    if reg.description == '':
        if reg.name.endswith('_EL12') and reg.name[:-1] in Register.byname:
            reg.description = Register.byname[reg.name[:-1]].description.replace('EL1', 'EL1&2')
        elif reg.name.endswith('_EL02') and reg.name[:-1] in Register.byname:
            reg.description = Register.byname[reg.name[:-1]].description.replace('EL0', 'EL0&2')

# Extract all registers which can be accessed by pair in the cpusysreg kernel module.
# We do it only now that we know the exact list of existing registers because we have
# to "guess" the actual registers in the pairs.
pattern = re.compile(r'CSR_REGID2_([a-zA-Z0-9_]+)(_EL[0-3]+), ')
for line in file_cpusysregs_h.before:
    match = pattern.match(line.strip())
    if match is not None:
        name = match.group(1) + match.group(2)
        name_hi = match.group(1) + "HI" + match.group(2)
        name_lo = match.group(1) + "LO" + match.group(2)
        if name in Register.byname:
            # Register has same name as pair.
            Register.byname[name].cpusysregs = True
        elif name_hi in Register.byname and name_lo in Register.byname:
            # The pair is over two registers.
            Register.byname[name_hi].cpusysregs = True
            Register.byname[name_lo].cpusysregs = True

#----------------------------------------------------------------------------
# Extract list of instructions from downloaded tarballs.
#----------------------------------------------------------------------------

for iclass in InstructionClass.all:
    xmltree = etree.parse(iclass.indexfile)
    for iform in xmltree.findall('.//iform'):
        for name in Instruction.splitnames(iform.get('heading')):
            iclass.count += 1
            Instruction.addnew(name, iform.text, iclass)
    print('Number of %s instruction: %d' % (iclass.name, iclass.count))

print('Total number of instruction: %d' % sum([c.count for c in InstructionClass.all]))

#----------------------------------------------------------------------------
# Generate output files.
#----------------------------------------------------------------------------

# Update list of features.
name_width = max(len(feat_headers.name), max([len(f.name) for f in Feature.byname.values()]))
opt_width = max(len(feat_headers.optional), max([len(f.optional) for f in Feature.byname.values()]))
mand_width = max(len(feat_headers.mandatory), max([len(f.mandatory) for f in Feature.byname.values()]))
sys_width = max(len(feat_headers.sysregs), max([len(f.sysregs) for f in Feature.byname.values()]))
desc_width = len(feat_headers.description)
detectable = len([f for f in Feature.byname.values() if f.sysregs == 'X'])
removed = len([f for f in Feature.byname.values() if f.removed()])
with file_features_md.rewrite() as output:
    print('Total: %d features, %d detectable, %d removed.' % (len(Feature.byname), detectable, removed), file=output)
    print(file=output)
    print('| %-*s | %-*s | %-*s | %-*s | %s' %
          (name_width, feat_headers.name, opt_width, feat_headers.optional,
           mand_width, feat_headers.mandatory, sys_width, feat_headers.sysregs, feat_headers.description),
          file=output)
    print('| %s | %s | %s | :%s: | %s' %
          (name_width * '-', opt_width * '-', mand_width * '-', (sys_width - 2) * '-', desc_width * '-'),
          file=output)
    for key in sorted(Feature.byname.keys(), key=str.lower):
        feat = Feature.byname[key]
        print(('| %-*s | %-*s | %-*s | %s | %s' %
              (name_width, feat.name, opt_width, feat.optional,
               mand_width, feat.mandatory, feat.sysregs.center(sys_width), feat.description)).rstrip(),
              file=output)
    file_features_md.complete(output)

# Update list of system registers.
header = ('System Register', 'sysregs', 'Description')
name_width = max(len(header[0]), max([len(r.name) for r in Register.byname.values()]))
sr_width = len(header[1])
readable = len([f for f in Register.byname.values() if f.cpusysregs])
with file_registers_md.rewrite() as output:
    print('Total: %d system registers, %d can be accessed by cpusysregs.' % (len(Register.byname), readable), file=output)
    print(file=output)
    print('| %-*s | %s | %s' % (name_width, header[0], header[1], header[2]), file=output)
    print('| %s | :%s: | %s' % (name_width * '-', (sr_width - 2) * '-', len(header[2]) * '-'), file=output)
    for key in sorted(Register.byname.keys(), key=str.lower):
        reg = Register.byname[key]
        sr = 'X' if reg.cpusysregs else ''
        print(('| %-*s | %s | %s' % (name_width, reg.name, sr.center(sr_width), reg.description)).rstrip(), file=output)
    file_registers_md.complete(output)

# Update lists of bitfields in system registers.
header = ('Bitfield', 'msb:lsb', 'Size', 'Description')
with file_bitfields_md.rewrite() as output:
    for key in sorted(Register.byname.keys(), key=str.lower):
        reg = Register.byname[key]
        bfcount = 0 if reg.bitfields is None else len(reg.bitfields)
        # Ignore registers with no bitfield or only one with same size as register.
        if bfcount > 1 or (bfcount == 1 and reg.bitfields[0].bits != reg.size):
            name_width = max(len(header[0]), max([len(bf.name) for bf in reg.bitfields]))
            print(file=output)
            print('## %s bitfields' % reg.name, file=output)
            print(file=output)
            print('| %-*s | %s | %s | %s' % (name_width, header[0], header[1], header[2], header[3]), file=output)
            print('| %s | %s: | %s: | %s' %
                  (name_width * '-', (len(header[1]) - 1) * '-', (len(header[2]) - 1) * '-', len(header[3]) * '-'),
                  file=output)
            for bf in reg.bitfields:
                pos = '%d:%d' % (bf.lsb + bf.bits - 1, bf.lsb)
                print(('| %-*s | %*s | %*d | %s' %
                       (name_width, bf.name, len(header[1]), pos, len(header[2]), bf.bits,
                        bf.description.replace('|', '\\|').replace('\n', ' '))).rstrip(),
                      file=output)
    file_bitfields_md.complete(output)

# Update list of instructions
with file_instructions_md.rewrite() as output:
    print(file=output)
    print('## Number of instructions per class', file=output)
    print(file=output)
    header = ('Class', 'Instructions')
    list = InstructionClass.all + [InstructionClass('Total', '', sum([c.count for c in InstructionClass.all]))]
    name_width = max(len(header[0]), max([len(c.name) for c in list]))
    print('| %-*s | %s' % (name_width, header[0], header[1]), file=output)
    print('| %s | %s' % (name_width * '-', len(header[1]) * '-'), file=output)
    for iclass in list:
        print('| %-*s | %d' % (name_width, iclass.name, iclass.count), file=output)

    print(file=output)
    print('## All instructions', file=output)
    print(file=output)
    print('| Opcode | Class | Description', file=output)
    print('| ------ | ----- | -----------', file=output)
    for key in sorted(Instruction.byname.keys()):
        for inst in Instruction.byname[key]:
            print('| %s | %s | %s' % (inst.name, inst.iclass.name, inst.description), file=output)
    file_instructions_md.complete(output)

# Update the C/C++ definitions of the register encodings.
name_width = max([len(name) for name in Register.byname])
with file_cpusysregs_h.rewrite() as output:
    for name in sorted(Register.byname.keys()):
        reg = Register.byname[name]
        if reg.encoding is None:
            print('--- Undefined encoding for register %s' % name)
        else:
            print('#define CSR_SREG_%-*s  CSR_SREG(%s)' % (name_width, name, reg.encoding), file=output)
    file_cpusysregs_h.complete(output)

# Update the C/C++ definitions for armfeatures.h.
cppregs = [reg for reg in Register.byname.values() if reg.cppfield is not None and reg.bitfields is not None]
cppregs.sort(key=lambda x: x.cppindex)
with file_armfeatures_h.rewrite() as output:
    for reg in cppregs:
        for bf in reg.bitfields:
            typename = 'int' if bf.bits < 32 else 'csr_u64_t'
            shift = '' if bf.lsb == 0 else ' >> %d' % bf.lsb
            mask = 0xFFFFFFFFFFFFFFFF >> (64 - bf.bits)
            print('    %s %s_%s() const { return (%s)(%s%s) & 0x%02X; }' %
                  (typename, reg.name, bf.name, typename, reg.cppfield, shift, mask), file=output)
        if reg.name != cppregs[-1].name:
            print(file=output)
    file_armfeatures_h.complete(output)

# Generate the C/C++ template data structure for regview.cpp.
cppregs = [reg for reg in Register.byname.values() if reg.cpusysregs]
cppregs.sort(key=lambda x: x.name.lower())
with open(REGVIEW_CPP_OUT, 'w') as output:
    for reg in cppregs:
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
