#!/usr/bin/env bash
#----------------------------------------------------------------------------
#
# Arm64 CPU system registers tools
# Copyright (c) 2023, Thierry Lelegard
# BSD-2-Clause license, see the LICENSE file.
#
# Collect various standard information on the current platform.
#
#----------------------------------------------------------------------------

SCRIPT=$(basename $BASH_SOURCE)
error() { echo >&2 "$SCRIPT: $*"; exit 1; }

# Destination directory for test files.
DESTDIR=$1
[[ -n $DESTDIR ]] || error "usage: $SCRIPT output-directory"
[[ -d $DESTDIR ]] || mkdir -p -v $DESTDIR
DESTDIR=$(cd $DESTDIR; pwd)

# Build or update tools for this project.
cd $(dirname $BASH_SOURCE)/..
make -j10
make unload
SYSTEM=$(uname -s)
[[ $SYSTEM == Linux ]] && make install
make load

# Generate result files.
echo "Creating cpusysregs-* files"
(
    echo "Kernel"
    echo "------"
    uname -m -p -r -s -v  # same as "uname -a" without host name (anonymized)
    echo
    echo "Operating system"
    echo "----------------"
    if [[ $SYSTEM == Darwin ]]; then
        sw_vers
    elif [[ -n $(which lsb_release) ]]; then
        lsb_release -a
    else
        for name in os fedora redhat ubuntu debian alpine; do
            if [[ -e /etc/$name-release ]]; then
                cat /etc/$name-release
                break
            fi
        done
    fi
    echo
    echo "Compiler"
    echo "--------"
    [[ $SYSTEM == Linux ]] && gcc --version
    [[ $SYSTEM == Darwin ]] && clang --version
) | expand >$DESTDIR/cpusysregs-system.txt

apps/sysregs -s >$DESTDIR/cpusysregs-features.txt
apps/sysregs -p >$DESTDIR/cpusysregs-pac.txt
apps/sysregs -a -v >$DESTDIR/cpusysregs-registers.txt
apps/demo-pac >$DESTDIR/cpusysregs-demo-pac-1.txt
apps/demo-pac >$DESTDIR/cpusysregs-demo-pac-2.txt
apps/demo-pac >$DESTDIR/cpusysregs-demo-pac-3.txt
apps/demo-userfeatures >$DESTDIR/cpusysregs-user-features.txt
apps/collect >$DESTDIR/cpusysregs-pac-md.txt

ls -l $DESTDIR/cpusysregs-*.txt
