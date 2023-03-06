#!/usr/bin/env bash
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Rebuild the table of contents in all markdown files in this directory.
# If a markdown file contains a line which is exactly '**Contents:**',
# a table of contents is automatically generated or updated immediately
# following that line.
#
#----------------------------------------------------------------------------

# Work on files in the same directory as the script.
cd $(dirname $0)

# Search or install command "gh-md-toc"
GH_MD_TOC=$(which gh-md-toc 2>/dev/null)
if [[ -z $GH_MD_TOC && $(uname -s) == Darwin ]]; then
    brew install github-markdown-toc
    GH_MD_TOC=$(which gh-md-toc 2>/dev/null)
fi
if [[ -z $GH_MD_TOC ]]; then
    echo "$0: command gh-md-toc not found, tables of contents not updated in markdown files"
    exit 0
fi

# Process all markdown files.
for file in *.md; do
    # Process file which contains a line which is exactly '**Contents:**'.
    if grep -q '^\*\*Contents:\*\*$' $file; then
        intoc=false  # true when inside the previous TOC
        while IFS= read -r line; do
            if $intoc; then
                [[ $line =~ ^\ *$ || $line =~ ^\ *\*\ \[ ]] || intoc=false
            fi
            if [[ $line =~ ^\*\*Contents:\*\*$ ]]; then
                intoc=true
                echo "$line"
                echo ""
                gh-md-tocgh-md-toc --hide-header --hide-footer --start-depth=1 $file
            elif ! $intoc; then
                echo "$line"
            fi
        done <$file >$file.tmp
        if cmp -s $file $file.tmp; then
            rm $file.tmp  # identical files
        else
            echo "updated TOC of $file"
            mv $file.tmp $file
        fi
    fi
done
