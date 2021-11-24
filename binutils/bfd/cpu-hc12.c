/* BFD support for the Motorola HC11/HC12/HC16 architecture.

   Copyright (C) 2000 Real Time Systems Inc.
   
This file is part of BFD, the Binary File Descriptor library.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  

This file is ported to 68HC12 by:
   Real-Time Systems Inc.
   1212 Austin Avenue, Coquitlam, B.C. Canada. V3H 3X3
   email: querbach@realtime.bc.ca
*/


#include "bfd.h"
#include "sysdep.h"
#include "libbfd.h"



const bfd_arch_info_type bfd_hc12_arch =
{
  16,				/* bits in a word */
  24,				/* bits in an address */
  8,				/* bits in a byte */
  bfd_arch_hc1x,		/* architecture descriptor */
  bfd_mach_hc12,		/* machine code */
  "hc1x",			/* architecture name string */
  "hc12",			/* machine name string */
  1, 				/* section alignment power */
  true,				/* default machine in arch? */
  bfd_default_compatible,
  bfd_default_scan,
  0				/* next in list */
};



