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
error() { echo >&2 "$SCRIPT: $*"; exit 1; }

# XML file containing all system registers description.
REGINDEX="AArch64-regindex.xml"

# Need xmlstarlet utility.
[[ -z $(which xmlstarlet 2>/dev/null) ]] && error "xmlstarlet not installed"

# Get SysReg tarball. Pass all options to download-arm-spec.sh.
DLDIR=$("$SCRIPTDIR/download-arm-spec.sh" "$@" --sysreg --log-outdir '#@@#' 2>&1 |
            tee /dev/stderr |
            grep '#@@#' |
            sed -e 's|^#@@#||')
[[ -z "$DLDIR" ]] && exit 1
[[ -d "$DLDIR" ]] || error "directory $DLDIR not found"
OUTFILE="$DLDIR/../sregs.h"

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

echo "generated file: "$(realpath "$OUTFILE")
