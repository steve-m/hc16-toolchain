/* $Id: binutils-2.9.1-hc1x-0.patch,v 1.1 2000/06/27 17:07:43 jiang Exp $
   Copyright (C) 2000 Real Time Systems Inc.
   
   tc-hc1x.h -- Header file for tc-hc1x.c

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
   This file is ported to 68HC12 by:
     Real-Time Systems Inc.
     1212 Austin Avenue, Coquitlam, B.C. Canada. V3H 3X3
     email: querbach@realtime.bc.ca
*/
   


/* basic configuration: */

#define TC_HC1X 1
#define TARGET_BYTES_BIG_ENDIAN	1

#ifndef BFD_ASSEMBLER
  #error Need BFD_ASSEMBLER defined (not otherwise tested).
#else
  #define TARGET_ARCH bfd_arch_hc1x
  #define TARGET_MACH bfd_mach_hc12
#endif


/* use 3-argument md_apply_fix(), for no particular reason */

#define MD_APPLY_FIX3


/* With the hc1x family, we are not concerned about truly huge switch
   statements ( >32k bytes ) being generated by gcc, so we can avoid
   some convoluted handling of the .word pseudo-op:			*/

#define WORKING_DOT_WORD


/* Define nonzero to use the gasp alternate macro syntax:		*/

#define MACRO_ALTERNATE 0


/* Define nonzero to strip the `@' character during macro expansions.
   This allows token-pasting in macro expansions without having to
   use something like `foo/()bar' in the macro definition to get `foobar'
   after expansion.  We can now use `foo@bar' in the definition instead.
   Note that only gas, and not gasp, understands this.			*/

#define MACRO_STRIP_AT 1


/* For the hc1x family, we want the classical Motorola syntax, eg:

     - labels starting in first column don't require colons
     - `label equ value' and so forth are acceptable
     - hex constants are specified as $1F0C or 1F0Ch
     - binary constants are specified as %0010 or 0010b
     - string constants can be specified 'hello'.

   In gas, this syntax is specified when the flags `flag_mri' and
   `flag_m68k_mri' are true.  To achieve this, we parallel ourselves
   with the TC_M68K #ifdefs in several places in as.c, app.c, and read.c.

   This all works fine except for one point:  the existing M68K mri code
   always forces word alignment after an odd-sized dc.b directive, unless
   followed by another dc directive.  These being 8-bit processors, we
   defeat this alignment by defining:					*/

#define DONT_ALIGN_AFTER_MRI_DCB


/* When filling empty space in a section (should be rare), use an
   undefined opcode to cause an exception at runtime.			*/

#define NOP_OPCODE  0x55


/* Identify the CPU type on the listing:				*/

#define LISTING_HEADER  "MC68CH12 GAS"


/* end of tc-hc1x.h */
