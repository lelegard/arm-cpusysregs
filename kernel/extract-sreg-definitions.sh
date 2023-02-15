#!/usr/bin/env bash
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# This script automatically extracts and formats the CSR_SREG definitions of
# all Arm system registers, as used in cpusysregs.h, from a PDF file of the
# Arm Architecture Reference Manual. This script was successfully used on
# version I.a of this PDF document. Manual adjustments may be necessary on
# future versions.
#
# The latest revision of the "Arm Architecture Reference Manual for A-profile
# architecture" is available at:
# https://developer.arm.com/documentation/ddi0487/latest
#
# Usage: ./extract-sreg-definitions.sh file.pdf [first [last]]
#
# The "first" and "last" parameters indicate the page numbers of the section
# D17 "AArch64 System Register Descriptions" of the manual. The default
# values below apply to version I.a of the PDF document.
#
#----------------------------------------------------------------------------

INPUT_FILE=$1
FIRST_PAGE=${2:-5545}
LAST_PAGE=${3:-7124}

SCRIPT=$(basename $0)
info() { echo >&2 "$SCRIPT: $*"; }
error() { echo >&2 "$SCRIPT: $*"; exit 1; }

[[ -z $INPUT_FILE ]] && error "usage: $0 arm-arch-manual.pdf [first [last]]"

# Fields of a CPU register are: name op0 op1 CRn CRm op2
fields=()

pdftotext -f $FIRST_PAGE -l $LAST_PAGE $INPUT_FILE - |
    grep -A 20 'MRS *<Xt>,' |
    (grep -e '^--$' -e '^MRS *<Xt>,' -e '^0b[01]*$'; echo "--") |
    sed -e 's/^MRS *<Xt>, *//' |
    while IFS= read line; do
        if [[ $line != -- ]]; then
            fields+=("$line")
        else
            if [[ ${#fields[@]} -eq 6 ]]; then
                fields[0]=$(tr <<<${fields[0]} a-z A-Z)
                printf '#define CSR_SREG_%-18s CSR_SREG(%4s, %5s, %6s, %6s, %5s)\n' "${fields[@]}"
            else
                info "incomplete register description: ${fields[@]}"
            fi
            fields=()
        fi
    done
