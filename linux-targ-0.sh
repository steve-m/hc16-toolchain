#!/bin/sh

# This is the second of three stages in a Canadian cross from linux 
# via a host such as go32 or cygwin32 to any target.  This stage builds
# the linux-to-target toolchain.  It need only be done once per target.


# Configure the following to suit your circumstances

host=i686-pc-linux-gnu		# As we are running in a container, we have to hard-code the host arch
target=hc16-coff		# machine to target
prefix=$PWD/inst		# where to install the cross-compiler


# First, build the source symlink tree if necessary, and clean up from any
# previous builds.

	if [ ! -d "src" ] ; then
          ./one-tree-0.sh
	fi

	rm -rf build

# Now configure, build, and install (you may need to be root):

	mkdir build
	cd build
	  ../src/configure -v --target=$target --host=$host --prefix=$prefix \
	      2>&1 | tee ../config.log
	  make -w 2>&1 | tee ../build.log
	  make -w install 2>&1 | tee ../inst.log
	cd ..

