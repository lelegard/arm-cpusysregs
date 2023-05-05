#!/usr/bin/env bash
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# This script automatically extracts and formats the CSR_SREG definitions of
# all Arm system registers, as used in cpusysregs.h, from the reference
# description on Arm site.
#
#----------------------------------------------------------------------------

SCRIPT=$(basename $0)
SCRIPTDIR=$(cd $(dirname $0); pwd)
info() { echo >&2 "$SCRIPT: $*"; }
error() { echo >&2 "$SCRIPT: $*"; exit 1; }

# Description of Arm reference document (set of XML files).
BASEURL="https://developer.arm.com/downloads/-/exploration-tools"
TARBALL_PREFIX="SysReg_xml_A_profile"
TARBALL_SUFFIX=".tar.gz"
REGINDEX="AArch64-regindex.xml"

# Option "-d" forces download.
[[ $1 == -d ]] && FORCE_DOWNLOAD=true || FORCE_DOWNLOAD=false

# Need xmlstarlet utility.
[[ -z $(which xmlstarlet) ]] && error "xmlstarlet not installed"

# Get URL up to host part.
url_host() {
    sed <<<$1 -e 's|^\([[:alnum:]]*://[^/]*\).*$|\1|'
}

# Get URL up to directory part.
url_dir() {
    sed <<<$1 -e 's|/[^/]*$||'
}

# Resolve URL from base and relative URL.
resolve_url() {
    local base="$1"
    local rel="$2"
    if grep -q <<<$rel '^[[:alnum:]]*:'; then
        base=""
    elif [[ $rel == /* ]]; then
        base=$(url_host "$base")
    else
        base=$(url_dir "$base")/
    fi
    echo "$base$rel"
}

# Output files.
DLDIR="$SCRIPTDIR/downloads"
TARBALL="$DLDIR/SysReg.tar.gz"
OUTFILE="$DLDIR/sregs.h"
$FORCE_DOWNLOAD && rm -rf "$DLDIR"

# Download and extract SysReg.
if [[ ! -e "$TARBALL" ]]; then
    # Get URL of SysReg tarball at arm.com.
    URL=$(curl -sL "$BASEURL" | grep "href=\".*/$TARBALL_PREFIX.*$TARBALL_SUFFIX" | sed -e 's/.*href="//' -e 's/".*//' | head -1)
    [[ -z "$URL" ]] && error "$TARBALL_PREFIX*$TARBALL_SUFFIX not found in $BASEURL"
    URL=$(resolve_url "$BASEURL" "$URL")
    # Dowload and expand.
    rm -rf "$DLDIR"
    mkdir -p "$DLDIR"
    echo "downloading $URL ..."
    curl -L "$URL" -o "$TARBALL"
    [[ -e "$TARBALL" ]] || error "$TARBALL not downloaded"    
    (cd "$DLDIR"; tar xzf "$TARBALL")
fi

# Get top-level description of registers.
REGXML=$(find "$DLDIR" -name "$REGINDEX" | tail -1)
[[ -z "$REGXML" ]] && error "$REGINDEX not found in tarball"
REGDIR=$(dirname "$REGXML")

# Loop on all register description files (one XML file per register).
for regfile in $(xmlstarlet sel -T -t -v /register_index/register_links/register_link/@registerfile "$REGXML"); do
    regname=$(xmlstarlet sel -T -t -v /register_page/registers/register/reg_short_name "$REGDIR/$regfile" | tr a-z A-Z)
    if [[ $regname != *\<*\>* ]]; then
        xmlstarlet sel -T -t \
                   -m "//encoding/access_instruction[contains(text(),'MRS')]" \
                   -v "text()" \
                   -o " (" -v "../enc[@n='op0']/@v" \
                   -o ', ' -v "../enc[@n='op1']/@v" \
                   -o ', ' -v "../enc[@n='CRn']/@v" \
                   -o ', ' -v "../enc[@n='CRm']/@v" \
                   -o ', ' -v "../enc[@n='op2']/@v" \
                   -o ')' -n "$REGDIR/$regfile"
    fi
done |
    sed -e 's/^ *MRS *//' -e 's/[ ,]*<.*>[ ,]*//' |
    while IFS="" read line; do
        name=${line/ (*/}
        value=${line/* (/(}
        printf '#define CSR_SREG_%-18s CSR_SREG%s\n' $(tr a-z A-Z <<<$name) "$value"
    done |
    LANG=C sort -u -d >"$OUTFILE"

echo "generated file: $OUTFILE"
