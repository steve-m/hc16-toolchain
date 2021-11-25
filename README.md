# hc16-toolchain

This is a patched version of the toolchain for Motorola/Freescale M68HC11/12/16 by Real-Time Systems Inc. (https://www.realtime.bc.ca/open-source/gnu-hc1x.html), which is based on GCC 2.8.1 and binutils 2.9.1.

Note that for the M68HC11 and M68HC12 there is a somewhat newer toolchain available (http://savannah.nongnu.org/projects/m68hc11), but for the M68HC16 this repository contains the only open source toolchain available.

## Building

Create a container with the supplied Dockerfile, mount the repository inside and start ./linux-targ-0.sh
A folder inst will be created that contains the build result.
