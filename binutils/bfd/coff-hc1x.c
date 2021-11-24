/* BFD back-end for Motorola HC11/HC12/HC16 COFF files.
   Copyright 1990, 1991, 1992, 1993, 1994 Free Software Foundation, Inc.

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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include "bfd.h"
#include "sysdep.h"
#include "libbfd.h"
#include "coff/hc1x.h"
#include "coff/internal.h"
#include "libcoff.h"


#define COFF_DEFAULT_SECTION_ALIGNMENT_POWER (0)


/* relocation howto table */

static reloc_howto_type howto_table[] =
{
  HOWTO (R_RELBYTE,		/* type */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 8,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 0,			/* special_function */
	 "R_RELBYTE",		/* name */
	 true,			/* partial_inplace */
	 0x000000ff,		/* src_mask */
	 0x000000ff,		/* dst_mask */
	 false),		/* pcrel_offset */
  HOWTO (R_RELWORD,		/* type */
	 0,			/* rightshift */
	 1,			/* size (0 = byte, 1 = short, 2 = long) */
	 16,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont,/* complain_on_overflow */
	 0,			/* special_function */
	 "R_RELWORD",		/* name */
	 true,			/* partial_inplace */
	 0x0000ffff,		/* src_mask */
	 0x0000ffff,		/* dst_mask */
	 false),		/* pcrel_offset */
  HOWTO (R_RELLONG,		/* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_bitfield, /* complain_on_overflow */
	 0,			/* special_function */
	 "R_RELLONG",		/* name */
	 true,			/* partial_inplace */
	 0xffffffff,		/* src_mask */
	 0xffffffff,		/* dst_mask */
	 false),		/* pcrel_offset */
  HOWTO (R_PCRBYTE,		/* type */
	 0,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 8,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 0,			/* special_function */
	 "R_PCRBYTE",		/* name */
	 true,			/* partial_inplace */
	 0x000000ff,		/* src_mask */
	 0x000000ff,		/* dst_mask */
	 false),		/* pcrel_offset */
  HOWTO (R_PCRWORD,		/* type */
	 0,			/* rightshift */
	 1,			/* size (0 = byte, 1 = short, 2 = long) */
	 16,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont,/* complain_on_overflow */
	 0,			/* special_function */
	 "R_PCRWORD",		/* name */
	 true,			/* partial_inplace */
	 0x0000ffff,		/* src_mask */
	 0x0000ffff,		/* dst_mask */
	 false),		/* pcrel_offset */
  HOWTO (R_PCRLONG,		/* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 32,			/* bitsize */
	 true,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_signed, /* complain_on_overflow */
	 0,			/* special_function */
	 "R_PCRLONG",		/* name */
	 true,			/* partial_inplace */
	 0xffffffff,		/* src_mask */
	 0xffffffff,		/* dst_mask */
	 false),		/* pcrel_offset */
  HOWTO (R_RELBYTE_HC12,	/* type */
	 16,			/* rightshift */
	 0,			/* size (0 = byte, 1 = short, 2 = long) */
	 8,			/* bitsize */
	 false,			/* pc_relative */
	 0,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "R_RELBYTE_HC12",	/* name */
	 true,			/* partial_inplace */
	 0x00ffffff,		/* src_mask */
	 0x000000ff,		/* dst_mask */
	 false),		/* pcrel_offset */
  HOWTO (R_REL20,		/* type */
	 0,			/* rightshift */
	 2,			/* size (0 = byte, 1 = short, 2 = long) */
	 24,			/* bitsize */
	 false,			/* pc_relative */
	 8,			/* bitpos */
	 complain_overflow_dont, /* complain_on_overflow */
	 0,			/* special_function */
	 "R_REL20",		/* name */
	 true,			/* partial_inplace */
	 0x0FFFFF00,		/* src_mask */
	 0x0FFFFF00,		/* dst_mask */
	 false)			/* pcrel_offset */
};


/* Turn a howto into a reloc number */

#define SELECT_RELOC(x, howto) { x.r_type = howto->type; }


/* Turn an rtype into a howto pointer */

#define RTYPE2HOWTO(cache_ptr, dst)  hc1x_rtype2howto(cache_ptr, dst)

static void
hc1x_rtype2howto
(
  arelent* cache_ptr,
  struct internal_reloc* rel
)
{
  switch ((rel)->r_type)
  {
    case R_RELBYTE:
      cache_ptr->howto = howto_table + 0;
      break;

    case R_RELWORD:
      cache_ptr->howto = howto_table + 1;
      break;

    case R_RELLONG:
      cache_ptr->howto = howto_table + 2;
      break;

    case R_PCRBYTE:
      cache_ptr->howto = howto_table + 3;
      break;

    case R_PCRWORD:
      cache_ptr->howto = howto_table + 4;
      break;

    case R_PCRLONG:
      cache_ptr->howto = howto_table + 5;
      break;

    case R_RELBYTE_HC12:
      cache_ptr->howto = howto_table + 6;
      break;

    case R_REL20:
      cache_ptr->howto = howto_table + 7;
      break;
  }
}


/* turn a bfd reloc type into a howto pointer */

#define coff_bfd_reloc_type_lookup   hc1x_bfd_reloc_type_lookup

reloc_howto_type*
hc1x_bfd_reloc_type_lookup
(
  bfd* abfd,
  bfd_reloc_code_real_type code
)
{
  switch (code)
  {
    case BFD_RELOC_8:
      return howto_table + 0;

    case BFD_RELOC_CTOR:
    case BFD_RELOC_16:
      return howto_table + 1;

    case BFD_RELOC_32:
      return howto_table + 2;

    case BFD_RELOC_8_PCREL:
      return howto_table + 3;

    case BFD_RELOC_9_PCREL:
    case BFD_RELOC_16_PCREL:
      return howto_table + 4;

    case BFD_RELOC_32_PCREL:
      return howto_table + 5;

    case BFD_RELOC_HC12:
      return howto_table + 6;

    case BFD_RELOC_20:
      return howto_table + 7;
  }
}


/* define magic numbers */

#define BADMAG(x) HC1XBADMAG(x)
#define __A_MAGIC_SET__      	/* FIXME:  not sure what this does */


/* bring in all of the hard stuff */

#define HC1X 1			/* Customize coffcode.h */
#include "coffcode.h"


/* target descriptor */

const bfd_target hc1xcoff_vec =
{
  "coff-hc1x",			/* name */
  bfd_target_coff_flavour,
  BFD_ENDIAN_BIG,		/* data byte order is big */
  BFD_ENDIAN_BIG,		/* header byte order is big */

  (HAS_RELOC | EXEC_P |		/* object flags */
   HAS_LINENO | HAS_DEBUG |
   HAS_SYMS | HAS_LOCALS | WP_TEXT),

  (SEC_HAS_CONTENTS |		/* section flags */
   SEC_ALLOC | SEC_LOAD | SEC_RELOC),

  '_',				/* leading underscore */
  '/',				/* ar_pad_char */
  15,				/* ar_max_namelen */

  bfd_getb64, bfd_getb_signed_64, bfd_putb64,
  bfd_getb32, bfd_getb_signed_32, bfd_putb32,
  bfd_getb16, bfd_getb_signed_16, bfd_putb16, /* data */

  bfd_getb64, bfd_getb_signed_64, bfd_putb64,
  bfd_getb32, bfd_getb_signed_32, bfd_putb32,
  bfd_getb16, bfd_getb_signed_16, bfd_putb16, /* hdrs */

    {
       _bfd_dummy_target,
       coff_object_p, 			/* bfd_check_format */
       bfd_generic_archive_p,
       _bfd_dummy_target
    },
    {
       bfd_false,
       coff_mkobject,
       _bfd_generic_mkarchive, 		/* bfd_set_format */
       bfd_false
    },
    {
       bfd_false,
       coff_write_object_contents, 	/* bfd_write_contents */
       _bfd_write_archive_contents,
       bfd_false
    },

     BFD_JUMP_TABLE_GENERIC (coff),
     BFD_JUMP_TABLE_COPY (coff),
     BFD_JUMP_TABLE_CORE (_bfd_nocore),
     BFD_JUMP_TABLE_ARCHIVE (_bfd_archive_coff),
     BFD_JUMP_TABLE_SYMBOLS (coff),
     BFD_JUMP_TABLE_RELOCS (coff),
     BFD_JUMP_TABLE_WRITE (coff),
     BFD_JUMP_TABLE_LINK (coff),
     BFD_JUMP_TABLE_DYNAMIC (_bfd_nodynamic),

  COFF_SWAP_TABLE,
};
