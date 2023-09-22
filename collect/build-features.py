#!/usr/bin/env python
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD 2-Clause License, see LICENSE file.
# Build the FEATURES.md file which compares the features of tested Arm CPU.
#
#----------------------------------------------------------------------------

import os, sys

rootdir = os.path.dirname(__file__)
inputdir = rootdir + '/collect'
output = rootdir + '/FEATURES.md'

features = []
systems = {}

# Read all input files.
for d in (d for d in os.listdir(rootdir) if os.path.isdir(rootdir + '/' + d)):
    desc = rootdir + '/' + d + '/description.txt'
    feat = rootdir + '/' + d + '/cpusysregs-features.txt'
    if os.path.isfile(desc) and os.path.isfile(feat):
        core = ''
        with open(desc, 'r') as input:
            for line in input:
                fields = line.split(':', 1)
                if len(fields) == 2 and fields[0].strip() == 'core':
                    core = fields[1].strip()
                    break
        if core == '':
            continue
        systems[core] = {}
        with open(feat, 'r') as input:
            for line in input:
                fields = line.strip().replace('.', '').split(' ', 1)
                if len(fields) == 2 and fields[0].startswith('FEAT'):
                    f = fields[0].strip()
                    if f not in features:
                        features.append(f)
                    systems[core][f] = fields[1].strip()

# Generate the output markdown
cores = sorted(systems.keys())
features = sorted(features, key=str.casefold)
title = 'Feature'
width = len(title)
for f in features:
    width = max(width, len(f))
with open(output, 'w') as out:
    out.write('| %-*s |' % (width, title))
    for c in cores:
        out.write(' %s |' % c)
    out.write('\n')
    out.write('| %s |' % ('-' * width))
    for c in cores:
        out.write(' :%s: |' % ('-' * (len(c) - 2)))
    out.write('\n')
    for f in features:
        out.write('| %-*s |' % (width, f))
        for c in cores:
            state = systems[c][f] if f in systems[c] else ''
            out.write(' %-*s |' % (len(c), state))
        out.write('\n')
