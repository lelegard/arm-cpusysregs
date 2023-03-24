#!/usr/bin/env python
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Build the temporary header files _armfeatures.h and _userfeatures.h.
#
#----------------------------------------------------------------------------

import sys, re

if len(sys.argv) != 3:
    print('Usage: %s in-file out-file' % sys.argv[0], file=sys.stderr)
    exit(1)

class_name = None
input_file = sys.argv[1]
output_file = sys.argv[2]

lines = []
with open(input_file, 'r', encoding='utf-8') as input:
    for line in input:
        if class_name is None:
            match = re.search(r'^class\s+(\w+).*$', line.strip())
            if match is not None:
                class_name = match.group(1)
        else:
            match = re.search(r'^bool\s+(FEAT_[^ (]+)\s*\(\).*$', line.strip())
            if match is not None:
                lines.append('    {"%s", &%s::%s},' % (match.group(1), class_name, match.group(1)))

lines.sort(key = lambda x: x.lower())
with open(output_file, 'w') as output:
    for line in lines:
        print(line, file=output)
