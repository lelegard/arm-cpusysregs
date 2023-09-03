#!/usr/bin/env python
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Rebuild the table of contents in all specified markdown files.
# If a markdown file contains a line which is exactly '**Contents:**',
# a table of contents is automatically generated or updated immediately
# following that line.
#
#----------------------------------------------------------------------------

import os, sys, re, string

# Get input files from command line.
if len(sys.argv) < 2:
    print('usage: %s md-file ...' % os.path.basename(__file__), file=sys.stderr)
    exit(1)

toc_header = '**Contents:**'

for filename in sys.argv[1:]:
    # Phase 1: Read file, build ToC.
    output_intro = ''
    input_toc = ''
    output_toc = []
    output_body = ''
    state = 'intro'
    min_level = 99
    in_code = False
    with open(filename, 'r') as input:
        for line in input:
            sline = line.strip()
            if state == 'intro':
                output_intro += line
                if sline == toc_header:
                    # Found ToC header, start collecting headers and build ToC
                    state = 'toc'
            elif state == 'toc':
                if sline.startswith('* '):
                    input_toc += line
                elif sline != '':
                    state = 'body'
            if state == 'body':
                output_body += line
                if sline == '~~~' or sline == '```':
                    in_code = not in_code
                if sline.startswith('#') and not in_code:
                    # Found a header.
                    level = re.search(r'[^#]', sline).start()
                    min_level = min(level, min_level)
                    text = sline[level:].strip().replace('`', '')
                    anchor = ''.join([c for c in text.lower().replace(' ', '-') if c in string.ascii_lowercase + string.digits + '-'])
                    output_toc.append('%s* [%s](#%s)\n' % (((2 * (level - 1)) * ' '), text, anchor))
    # Phase 2: rewrite the file if a new ToC was produced.
    if len(output_toc) > 0 and min_level > 1:
        # Adjust indentation in output ToC
        margin = (2 * (min_level - 1)) * ' '
        for i in range(len(output_toc)):
            if output_toc[i].startswith(margin):
               output_toc[i] = output_toc[i][len(margin):]
    output_toc = ''.join(output_toc)
    if output_toc != '' and output_toc != input_toc:
        print('updating ToC of %s' % filename)
        with open(filename, 'w') as output:
            output.write(output_intro)
            output.write('\n')
            output.write(output_toc)
            output.write('\n')
            output.write(output_body)
