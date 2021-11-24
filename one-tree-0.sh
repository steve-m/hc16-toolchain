#!/bin/sh
# Create a single source tree from the various development tools.
# Version 1.3, modified by Real-Time Systems
# Send comments or questions to querbach@stargate.ca
#
# The script needs a binutils, gcc, and newlib release, as maintained
# by CVS, in the current directory.  Unlike the one-tree.sh from Cygnus, 
# this script doesn't want version numbers in the directory names.
#
# The tree is faked, using symlinks.  The goal is to keep it simple while
# providing a working example.
#
# After running this script:
# 1) mkdir build
# 2) cd build
# 3) ../src/configure --host=[your-host] --target=[your-target] [other options]
# 4) make all info
# 5) make install install-info
#
# If you are going to be building with gcc, do this instead.
#
# 1) mkdir build
# 2) cd build
# 3) CC=gcc ../src/configure --host=[your-host] --target=[your-target] [other options]
# 4) make all info CC=gcc
# 5) make install install-info
#
# The CC=gcc on line 4 is present for the sake of older releases
# and doesn't hurt to specify it again (normally, setting CC=gcc while
# running configure is enough).
#
# Building in a separate directory assumes of course that you have a version
# of `make' that understands VPATH.  GNU Make is such a critter and
# it is not recommended trying it with other makes.
#
# That's it.

# Find source trees for binutils, gcc, and newlib.
for pkg in binutils gcc
do
    dir=`ls -1d $pkg | tail -1`
    if [ ! -f "$dir/Makefile.in" ] ; then
	echo "Unable to find a $pkg source tree."
	echo "You need to install a $pkg release in this directory."
	exit 1
    fi

    eval $pkg=$dir
    echo "Using $pkg."
done

mkdir src
cd src

# Most of the toplevel stuff we take from binutils
for f in ../$binutils/*
do
    ln -s $f .
done

# Create a symlink to the gcc tree.
ln -s ../$gcc gcc

# Create symlinks to newlib.
ln -s ../$newlib/newlib .
ln -s ../$newlib/libgloss .
ln -s ../$newlib/COPYING.NEWLIB .


exit 0
