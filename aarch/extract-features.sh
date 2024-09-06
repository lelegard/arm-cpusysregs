#!/usr/bin/env bash
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# This script automatically extracts all Arm features (FEAT_xxx), from the
# reference description on Arm site.
#
#----------------------------------------------------------------------------

SCRIPT=$(basename $0)
SCRIPTDIR=$(cd $(dirname $0); pwd)
error() { echo >&2 "$SCRIPT: $*"; exit 1; }

# JSON file containing all features description.
FEATINDEX="Features.json"

# Need jq utility.
[[ -z $(which jq 2>/dev/null) ]] && error "jq not installed"

# Get Features tarball. Pass all options to download-arm-spec.sh.
DLDIR=$("$SCRIPTDIR/download-arm-spec.sh" "$@" --features --log-outdir '#@@#' 2>&1 |
            tee /dev/stderr |
            grep '#@@#' |
            sed -e 's|^#@@#||')
[[ -z "$DLDIR" ]] && exit 1
[[ -d "$DLDIR" ]] || error "directory $DLDIR not found"
OUTFILE="$DLDIR/../features.txt"
JSONFILE="$DLDIR/$FEATINDEX"
[[ -z "$JSONFILE" ]] && error "$FEATINDEX not found in tarball"

# Format list of features.
jq -r '.parameters[] | "| " + .name + " | " + .title' "$JSONFILE" |
    LANG=C sort -u -d |
    grep FEAT_ >"$OUTFILE"

echo "generated file: "$(realpath "$OUTFILE")
echo found $(wc -l "$OUTFILE" | awk '{ print $1 }') features

# Reference features documentation file.
REFNAME="docs/features.md"
REFFILE="$SCRIPTDIR/../$REFNAME"

# Check that all features are documented in docs/features.md.
while read bar feat rest; do
    if ! grep -q $feat "$REFFILE"; then
        echo "*** $feat is missing in $REFNAME"
    fi
done <"$OUTFILE"

# Check that all features in docs/features.md actuall exist in Features.json.
while read bar feat rest; do
    if [[ $bar == "|" && $feat == FEAT_* && $rest != *'(removed)' ]] && ! grep -q "^| *$feat *|" "$OUTFILE"; then
        echo "--- $feat does not exist in $FEATINDEX, should be marked '(removed)'"
    fi
done <"$REFFILE"
