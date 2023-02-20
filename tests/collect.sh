#!/usr/bin/env bash

SYSTEM=$(uname -s)

# Destination directory for test files.
DESTDIR=${1:-$(pwd)}
[[ -d $DESTDIR ]] || mkdir -p -v $DESTDIR
DESTDIR=$(cd $DESTDIR; pwd)

# Build or update tools for this project.
cd $(dirname ${BASH_SOURCE[0]})/..
make -j10
make unload
[[ $SYSTEM == Linux ]] && make install
make load

# Generate test-files.
echo "Creating cpusysregs-* files"
(
    uname -a
    [[ $SYSTEM == Linux ]] && gcc --version
    [[ $SYSTEM == Darwin ]] && clang --version
) >$DESTDIR/cpusysregs-system.txt

apps/sysregs -s >$DESTDIR/cpusysregs-features.txt
apps/sysregs -p >$DESTDIR/cpusysregs-pac.txt
apps/sysregs -a -v >$DESTDIR/cpusysregs-registers.txt
apps/demo-pac >$DESTDIR/cpusysregs-demo-pac-1.txt
apps/demo-pac >$DESTDIR/cpusysregs-demo-pac-2.txt
apps/demo-pac >$DESTDIR/cpusysregs-demo-pac-3.txt
apps/demo-userfeatures >$DESTDIR/cpusysregs-user-features.txt
