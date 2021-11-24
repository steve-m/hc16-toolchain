/* hc16-opcode.h -- Motorola 68HC16
   Copyright (C) 2000 Real Time Systems Inc.
   
This file is part of GAS, the GNU Assembler, and GDB, the GNU Debugger.

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
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

This file is ported to 68HC16 by:
     Real-Time Systems Inc.
     1212 Austin Avenue, Coquitlam, B.C. Canada. V3H 3X3
     email: querbach@realtime.bc.ca
*/


/* opcode table entry structure */

struct hc16_opcode
{
  char* name;			/* mnemonic */
  char* args;			/* operand pattern */
  int len;			/* instruction length in bytes */
  unsigned char code[12];	/* instruction bytes */
  int  swap;			/* swap oprands */
};


/* operand codes for "args" field:

  # 	immediate operand follows
  ,	literal comma required
  a	high byte for mac
  b	low byte for mac
  d     20 bits offset from x or y or z
  e	accumulator offset from x or y or z
  f	1-byte constant unsigned offset from x or y or z
  g	2-byte offset from x or y or z
  h	2-byte extended address
  i	1-byte immediate operand
  j	2-byte immediate operand
  k     1-byte signed constant
  r	1-byte pc-relative offset
  l	2-byte pc-relative offset
  m     20 bits extended address
  o	pshm multiple register mask
  p	pulm multiple register mask
  q	for brset, brclr
  s	swap offset and operand
*/

static struct hc16_opcode hc16_opcodes[] =
{
  { "aba",  "",		2, { 0x37, 0x0B },	0		},
  { "aby",  "",		2, { 0x37, 0x5F },	0		},
  { "abx",  "",		2, { 0x37, 0x4F },	0		},
  { "abz",  "",		2, { 0x37, 0x6F },	0		},

  { "ace",  "",		2, { 0x37, 0x22 },	0		},
  { "aced", "",		2, { 0x37, 0x23 },	0		},

  { "adca", "#i",	1, {       0x73 },	0		},
  { "adca", "e,x",	2, { 0x27, 0x43 },	0		},
  { "adca", "e,y",	2, { 0x27, 0x53 },	0		},
  { "adca", "e,z",	2, { 0x27, 0x63 },	0		},
  { "adca", "f,x",	1, {       0x43 },	0		},
  { "adca", "f,y",	1, {       0x53 },	0		},
  { "adca", "f,z",	1, {       0x63 },	0		},
  { "adca", "g,x",	2, { 0x17, 0x43 },	0		},
  { "adca", "g,y",	2, { 0x17, 0x53 },	0		},
  { "adca", "g,z",	2, { 0x17, 0x63 },	0		},
  { "adca", "h",	2, { 0x17, 0x73 },	0		},

  { "adcb", "#i",	1, {       0xF3 },	0		},
  { "adcb", "e,x",	2, { 0x27, 0xC3 },	0		},
  { "adcb", "e,y",	2, { 0x27, 0xD3 },	0		},
  { "adcb", "e,z",	2, { 0x27, 0xE3 },	0		},
  { "adcb", "f,x",	1, {       0xC3 },	0		},
  { "adcb", "f,y",	1, {       0xD3 },	0		},
  { "adcb", "f,z",	1, {       0xE3 },	0		},
  { "adcb", "g,x",	2, { 0x17, 0xC3 },	0		},
  { "adcb", "g,y",	2, { 0x17, 0xD3 },	0		},
  { "adcb", "g,z",	2, { 0x17, 0xE3 },	0		},
  { "adcb", "h",	2, { 0x17, 0xF3 },	0		},

  { "adcd", "#j",	2, { 0x37, 0xB3 },	0		},
  { "adcd", "e,x",	2, { 0x27, 0x83 },	0		},
  { "adcd", "e,y",	2, { 0x27, 0x93 },	0		},
  { "adcd", "e,z",	2, { 0x27, 0xA3 },	0		},
  { "adcd", "f,x",	1, {       0x83 },	0		},
  { "adcd", "f,y",	1, {       0x93 },	0		},
  { "adcd", "f,z",	1, {       0xA3 },	0		},
  { "adcd", "g,x",	2, { 0x37, 0xC3 },	0		},
  { "adcd", "g,y",	2, { 0x37, 0xD3 },	0		},
  { "adcd", "g,z",	2, { 0x37, 0xE3 },	0		},
  { "adcd", "h",	2, { 0x37, 0xF3 },	0		},

  { "adce", "#j",	2, { 0x37, 0x33 },	0		},
  { "adce", "g,x",	2, { 0x37, 0x43 },	0		},
  { "adce", "g,y",	2, { 0x37, 0x53 },	0		},
  { "adce", "g,z",	2, { 0x37, 0x63 },	0		},
  { "adce", "h",	2, { 0x37, 0x73 },	0		},

  { "adda", "#i",	1, {       0x71 },	0		},
  { "adda", "e,x",	2, { 0x27, 0x41 },	0		},
  { "adda", "e,y",	2, { 0x27, 0x51 },	0		},
  { "adda", "e,z",	2, { 0x27, 0x61 },	0		},
  { "adda", "f,x",	1, {       0x41 },	0		},
  { "adda", "f,y",	1, {       0x51 },	0		},
  { "adda", "f,z",	1, {       0x61 },	0		},
  { "adda", "g,x",	2, { 0x17, 0x41 },	0		},
  { "adda", "g,y",	2, { 0x17, 0x51 },	0		},
  { "adda", "g,z",	2, { 0x17, 0x61 },	0		},
  { "adda", "h",	2, { 0x17, 0x71 },	0		},

  { "addb", "#i",	1, {       0xF1 },	0		},
  { "addb", "e,x",	2, { 0x27, 0xC1 },	0		},
  { "addb", "e,y",	2, { 0x27, 0xD1 },	0		},
  { "addb", "e,z",	2, { 0x27, 0xE1 },	0		},
  { "addb", "f,x",	1, {       0xC1 },	0		},
  { "addb", "f,y",	1, {       0xD1 },	0		},
  { "addb", "f,z",	1, {       0xE1 },	0		},
  { "addb", "g,x",	2, { 0x17, 0xC1 },	0		},
  { "addb", "g,y",	2, { 0x17, 0xD1 },	0		},
  { "addb", "g,z",	2, { 0x17, 0xE1 },	0		},
  { "addb", "h",	2, { 0x17, 0xF1 },	0		},

  { "incd", "",		2, { 0xFC, 0x01 },	0		}, /* addd #1 */

  { "addd", "#k",	1, {       0xFC },	0		},
  { "addd", "#j",	2, { 0x37, 0xB1 },	0		},
  { "addd", "e,x",	2, { 0x27, 0x81 },	0		},
  { "addd", "e,y",	2, { 0x27, 0x91 },	0		},
  { "addd", "e,z",	2, { 0x27, 0xA1 },	0		},
  { "addd", "f,x",	1, {       0x81 },	0		},
  { "addd", "f,y",	1, {       0x91 },	0		},
  { "addd", "f,z",	1, {       0xA1 },	0		},
  { "addd", "g,x",	2, { 0x37, 0xC1 },	0		},
  { "addd", "g,y",	2, { 0x37, 0xD1 },	0		},
  { "addd", "g,z",	2, { 0x37, 0xE1 },	0		},
  { "addd", "h",	2, { 0x37, 0xF1 },	0		},

  { "aid",  "#k",	1, {       0xFC },	0		},
  { "aid",  "#j",	2, { 0x37, 0xB1 },	0		},

  { "adde", "#k",	1, {       0x7C },	0		},
  { "adde", "#j",	2, { 0x37, 0x31 },	0		},
  { "adde", "g,x",	2, { 0x37, 0x41 },	0		},
  { "adde", "g,y",	2, { 0x37, 0x51 },	0		},
  { "adde", "g,z",	2, { 0x37, 0x61 },	0		},
  { "adde", "h",	2, { 0x37, 0x71 },	0		},

  { "aie",  "#k",	1, {       0x7C },	0		},
  { "aie",  "#j",	2, { 0x37, 0x31 },	0		},

  { "ince", "",		2, { 0x7C, 0x01 },	0		}, /* adde #1*/

  { "ade",  "",         2, { 0x27, 0x78 },	0		},
  { "adx",  "",         2, { 0x37, 0xCD },	0		},
  { "ady",  "",         2, { 0x37, 0xDD },	0		},
  { "adz",  "",         2, { 0x37, 0xED },	0		},
  { "aex",  "",         2, { 0x37, 0x4D },	0		},
  { "aey",  "",         2, { 0x37, 0x5D },	0		},
  { "aez",  "",         2, { 0x37, 0x6D },	0		},

  { "ais",  "#k",       1, {       0x3F },	0		},
  { "ais",  "#j",       2, { 0x37, 0x3F },	0		},

  { "aix",  "#k",       1, { 	   0x3C },	0		},
  { "aix",  "#j",       2, { 0x37, 0x3C },	0		},

  { "aiy",  "#k",       1, { 	   0x3D },	0		},
  { "aiy",  "#j",       2, { 0x37, 0x3D },	0		},

  { "aiz",  "#k",       1, { 	   0x3E },	0		},
  { "aiz",  "#j",       2, { 0x37, 0x3E },	0		},

  { "anda", "#i",	1, {       0x76 },	0		},
  { "anda", "e,x",	2, { 0x27, 0x46 },	0		},
  { "anda", "e,y",	2, { 0x27, 0x56 },	0		},
  { "anda", "e,z",	2, { 0x27, 0x66 },	0		},
  { "anda", "f,x",	1, {       0x46 },	0		},
  { "anda", "f,y",	1, {       0x56 },	0		},
  { "anda", "f,z",	1, {       0x66 },	0		},
  { "anda", "g,x",	2, { 0x17, 0x46 },	0		},
  { "anda", "g,y",	2, { 0x17, 0x56 },	0		},
  { "anda", "g,z",	2, { 0x17, 0x66 },	0		},
  { "anda", "h",	2, { 0x17, 0x76 },	0		},

  { "andb", "#i",	1, {       0xF6 },	0		},
  { "andb", "e,x",	2, { 0x27, 0xC6 },	0		},
  { "andb", "e,y",	2, { 0x27, 0xD6 },	0		},
  { "andb", "e,z",	2, { 0x27, 0xE6 },	0		},
  { "andb", "f,x",	1, {       0xC6 },	0		},
  { "andb", "f,y",	1, {       0xD6 },	0		},
  { "andb", "f,z",	1, {       0xE6 },	0		},
  { "andb", "g,x",	2, { 0x17, 0xC6 },	0		},
  { "andb", "g,y",	2, { 0x17, 0xD6 },	0		},
  { "andb", "g,z",	2, { 0x17, 0xE6 },	0		},
  { "andb", "h",	2, { 0x17, 0xF6 },	0		},

  { "andd", "#j",	2, { 0x37, 0xB6 },	0		},
  { "andd", "e,x",	2, { 0x27, 0x86 },	0		},
  { "andd", "e,y",	2, { 0x27, 0x96 },	0		},
  { "andd", "e,z",	2, { 0x27, 0xA6 },	0		},
  { "andd", "f,x",	1, {       0x86 },	0		},
  { "andd", "f,y",	1, {       0x96 },	0		},
  { "andd", "f,z",	1, {       0xA6 },	0		},
  { "andd", "g,x",	2, { 0x37, 0xC6 },	0		},
  { "andd", "g,y",	2, { 0x37, 0xD6 },	0		},
  { "andd", "g,z",	2, { 0x37, 0xE6 },	0		},
  { "andd", "h",	2, { 0x37, 0xF6 },	0		},

  { "ande", "#j",	2, { 0x37, 0x36 },	0		},
  { "ande", "g,x",	2, { 0x37, 0x46 },	0		},
  { "ande", "g,y",	2, { 0x37, 0x56 },	0		},
  { "ande", "g,z",	2, { 0x37, 0x66 },	0		},
  { "ande", "h",	2, { 0x37, 0x76 },	0		},

  { "andp", "#j",	2, { 0x37, 0x3A },	0		},

  { "asla", "",		2, { 0x37, 0x04 },	0		},
  { "aslb", "",		2, { 0x37, 0x14 },	0		},
  { "asld", "",		2, { 0x27, 0xF4 },	0		},
  { "asle", "",		2, { 0x27, 0x74 },	0		},
  { "aslm", "",		2, { 0x27, 0xB6 },	0		},
  { "aslw", "g,x",	2, { 0x27, 0x04 },	0		},
  { "aslw", "g,y",	2, { 0x27, 0x14 },	0		},
  { "aslw", "g,z",	2, { 0x27, 0x24 },	0		},
  { "aslw", "h",	2, { 0x27, 0x34 },	0		},

  { "lsle", "",		2, { 0x27, 0x74 },	0		}, /* asle */

  { "asl",  "f,x",	1, {  	   0x04 },	0		},
  { "asl",  "f,y",	1, {       0x14 },	0		},
  { "asl",  "f,z",	1, {       0x24 },	0		},
  { "asl",  "g,x",	2, { 0x17, 0x04 },	0		},
  { "asl",  "g,y",	2, { 0x17, 0x14 },	0		},
  { "asl",  "g,z",	2, { 0x17, 0x24 },	0		},
  { "asl",  "h",	2, { 0x17, 0x34 },	0		},

  { "asra", "",		2, { 0x37, 0x0D },	0		},
  { "asrb", "",		2, { 0x37, 0x1D },	0		},
  { "asrd", "",		2, { 0x27, 0xFD },	0		},
  { "asre", "",		2, { 0x27, 0x7D },	0		},
  { "asrm", "",		2, { 0x27, 0xBA },	0		},

  { "asrw", "g,x",	2, { 0x27, 0x0D },	0		},
  { "asrw", "g,y",	2, { 0x27, 0x1D },	0		},
  { "asrw", "g,z",	2, { 0x27, 0x2D },	0		},
  { "asrw", "h",	2, { 0x27, 0x3D },	0		},

  { "asr",  "f,x",	1, {  	   0x0D },	0		},
  { "asr",  "f,y",	1, {       0x1D },	0		},
  { "asr",  "f,z",	1, {       0x2D },	0		},
  { "asr",  "g,x",	2, { 0x17, 0x0D },	0		},
  { "asr",  "g,y",	2, { 0x17, 0x1D },	0		},
  { "asr",  "g,z",	2, { 0x17, 0x2D },	0		},
  { "asr",  "h",	2, { 0x17, 0x3D },	0		},

  { "bcc",  "r",	1, {       0xB4 },	0		},
  { "bhs",  "r",	1, {       0xB4 },	0		},
  { "bcs",  "r",	1, {       0xB5 },	0		},
  { "blo",  "r",	1, {       0xB5 },	0		},
  { "beq",  "r",	1, {       0xB7 },	0		},
  { "bge",  "r",	1, {       0xBC },	0		},
  { "bgt",  "r",	1, {       0xBE },	0		},
  { "bhi",  "r",	1, {       0xB2 },	0		},
  { "ble",  "r",	1, {       0xBF },	0		},
  { "bls",  "r",	1, {       0xB3 },	0		},
  { "blt",  "r",	1, {       0xBD },	0		},
  { "bmi",  "r",	1, {       0xBB },	0		},
  { "bne",  "r",	1, {       0xB6 },	0		},
  { "bpl",  "r",	1, {       0xBA },	0		},
  { "bra",  "r",	1, {       0xB0 },	0		},
  { "brn",  "r",	1, {       0xB1 },	0		},
  { "bsr",  "r",	1, { 	   0x36 },	0		},
  { "bvc",  "r",	1, {       0xB8 },	0		},
  { "bvs",  "r",	1, {       0xB9 },	0		},

  { "bclrw", "g,x,#j",	2, { 0x27, 0x08 },	0		},
  { "bclrw", "g,y,#j",	2, { 0x27, 0x18 },	0		},
  { "bclrw", "g,z,#j",	2, { 0x27, 0x28 },	0		},
  { "bclrw", "h,#j",	2, { 0x27, 0x38 },	0		},

  { "bclr", "f,x,#i",	2, { 0x17, 0x08 },	1		},
  { "bclr", "f,y,#i",	2, { 0x17, 0x18 },	1		},
  { "bclr", "f,z,#i",	2, { 0x17, 0x28 },	1		},
  { "bclr", "g,x,#i",	1, { 	   0x08 },	1		},
  { "bclr", "g,y,#i",	1, { 	   0x18 },	1		},
  { "bclr", "g,z,#i",	1, {	   0x28 },	1		},
  { "bclr", "h,#i",     1, { 	   0x38 },	1		},

  { "bgnd", "",		2, { 0x37, 0xA6 },	0		},

  { "bita", "#i",	1, {       0x79 },	0		},
  { "bita", "e,x",	2, { 0x27, 0x49 },	0		},
  { "bita", "e,y",	2, { 0x27, 0x59 },	0		},
  { "bita", "e,z",	2, { 0x27, 0x69 },	0		},
  { "bita", "f,x",	1, {       0x49 },	0		},
  { "bita", "f,y",	1, {       0x59 },	0		},
  { "bita", "f,z",	1, {       0x69 },	0		},
  { "bita", "g,x",	2, { 0x17, 0x49 },	0		},
  { "bita", "g,y",	2, { 0x17, 0x59 },	0		},
  { "bita", "g,z",	2, { 0x17, 0x69 },	0		},
  { "bita", "h",	2, { 0x17, 0x79 },	0		},

  { "bitb", "#i",	1, {       0xF9 },	0		},
  { "bitb", "e,x",	2, { 0x27, 0xC9 },	0		},
  { "bitb", "e,y",	2, { 0x27, 0xD9 },	0		},
  { "bitb", "e,z",	2, { 0x27, 0xE9 },	0		},
  { "bitb", "f,x",	1, {       0xC9 },	0		},
  { "bitb", "f,y",	1, {       0xD9 },	0		},
  { "bitb", "f,z",	1, {       0xE9 },	0		},
  { "bitb", "g,x",	2, { 0x17, 0xC9 },	0		},
  { "bitb", "g,y",	2, { 0x17, 0xD9 },	0		},
  { "bitb", "g,z",	2, { 0x17, 0xE9 },	0		},
  { "bitb", "h",	2, { 0x17, 0xF9 },	0		},

  { "brclr", "g,x,#i,q",1, { 	   0x0A },	1		}, /* FIXME short branch */
  { "brclr", "g,y,#i,q",1, { 	   0x1A },	1		},
  { "brclr", "g,z,#i,q",1, {	   0x2A },	1		},
  { "brclr", "h,#i,q",  1, { 	   0x3A },	1		},

  { "brset", "g,x,#i,q",1, { 	   0x0B },	1		}, /* FIXME short branch */
  { "brset", "g,y,#i,q",1, { 	   0x1B },	1		},
  { "brset", "g,z,#i,q",1, {	   0x2B },	1		},
  { "brset", "h,#i,q",  1, { 	   0x3B },	1		},

  { "bsetw", "g,x,#j",	2, { 0x27, 0x09 },	0		},
  { "bsetw", "g,y,#j",	2, { 0x27, 0x19 },	0		},
  { "bsetw", "g,z,#j",	2, { 0x27, 0x29 },	0		},
  { "bsetw", "h,#j",	2, { 0x27, 0x39 },	0		},

  { "bset", "f,x,#i",	2, { 0x17, 0x09 },	1		},
  { "bset", "f,y,#i",	2, { 0x17, 0x19 },	1		},
  { "bset", "f,z,#i",	2, { 0x17, 0x29 },	1		},
  { "bset", "g,x,#i",	1, { 	   0x09 },	1		},
  { "bset", "g,y,#i",	1, { 	   0x19 },	1		},
  { "bset", "g,z,#i",	1, {	   0x29 },	1		},
  { "bset", "h,#i",     1, { 	   0x39 },	1		},

  { "cba",  "",		2, { 0x37, 0x1B },	0		},

  { "clc",  "",		4, { 0x37, 0x3A, 0xFE, 0xFF },	0	},  /* andp mask */
  { "cli",  "",		4, { 0x37, 0x3A, 0xFF, 0x1F },	0	},  /* andp mask */
  { "clv",  "",		4, { 0x37, 0x3A, 0xFD, 0xFF },	0	},  /* andp mask */

  { "clra", "",		2, { 0x37, 0x05 },	0		},  /* clra, clrb */
  { "clrb", "",		2, { 0x37, 0x15 },	0		},
  { "clrd", "",		2, { 0x27, 0xF5 },	0		},
  { "clre", "",		2, { 0x27, 0x75 },	0		},
  { "clrm", "",		2, { 0x27, 0xB7 },	0		},
  { "clrw", "g,x",	2, { 0x27, 0x05 },	0		},
  { "clrw", "g,y",	2, { 0x27, 0x15 },	0		},
  { "clrw", "g,z",	2, { 0x27, 0x25 },	0		},
  { "clrw", "h",	2, { 0x27, 0x35 },	0		},

  { "clred", "",	4, { 0x27, 0x75, 0x27, 0xF5 },	0	},  /* clre clrd*/

  { "clr", "f,x",	1, { 	   0x05 },	0		},
  { "clr", "f,y",	1, {       0x15 },	0		},
  { "clr", "f,z",	1, { 	   0x25 },	0		},
  { "clr", "g,x",	2, { 0x17, 0x05 },	0		},
  { "clr", "g,y",	2, { 0x17, 0x15 },	0		},
  { "clr", "g,z",	2, { 0x17, 0x25 },	0		},
  { "clr", "h",         2, { 0x17, 0x35 },	0		},

  { "cmpa", "#i",	1, {       0x78 },	0		},
  { "cmpa", "e,x",	2, { 0x27, 0x48 },	0		},
  { "cmpa", "e,y",	2, { 0x27, 0x58 },	0		},
  { "cmpa", "e,z",	2, { 0x27, 0x68 },	0		},
  { "cmpa", "f,x",	1, {       0x48 },	0		},
  { "cmpa", "f,y",	1, {       0x58 },	0		},
  { "cmpa", "f,z",	1, {       0x68 },	0		},
  { "cmpa", "g,x",	2, { 0x17, 0x48 },	0		},
  { "cmpa", "g,y",	2, { 0x17, 0x58 },	0		},
  { "cmpa", "g,z",	2, { 0x17, 0x68 },	0		},
  { "cmpa", "h",	2, { 0x17, 0x78 },	0		},

  { "cmpb", "#i",	1, {       0xF8 },	0		},
  { "cmpb", "e,x",	2, { 0x27, 0xC8 },	0		},
  { "cmpb", "e,y",	2, { 0x27, 0xD8 },	0		},
  { "cmpb", "e,z",	2, { 0x27, 0xE8 },	0		},
  { "cmpb", "f,x",	1, {       0xC8 },	0		},
  { "cmpb", "f,y",	1, {       0xD8 },	0		},
  { "cmpb", "f,z",	1, {       0xE8 },	0		},
  { "cmpb", "g,x",	2, { 0x17, 0xC8 },	0		},
  { "cmpb", "g,y",	2, { 0x17, 0xD8 },	0		},
  { "cmpb", "g,z",	2, { 0x17, 0xE8 },	0		},
  { "cmpb", "h",	2, { 0x17, 0xF8 },	0		},

  { "coma", "",		2, { 0x37, 0x00 },	0		},
  { "comb", "",		2, { 0x37, 0x10 },	0		},
  { "comd", "",		2, { 0x27, 0xF0 },	0		},
  { "come", "",		2, { 0x27, 0x70 },	0		},
  { "comw", "g,x",	2, { 0x27, 0x00 },	0		},
  { "comw", "g,y",	2, { 0x27, 0x10 },	0		},
  { "comw", "g,z",	2, { 0x27, 0x20 },	0		},
  { "comw", "h",	2, { 0x27, 0x30 },	0		},

  { "com", "f,x",	1, { 	   0x00 },	0		},
  { "com", "f,y",	1, {       0x10 },	0		},
  { "com", "f,z",	1, { 	   0x20 },	0		},
  { "com", "g,x",	2, { 0x17, 0x00 },	0		},
  { "com", "g,y",	2, { 0x17, 0x10 },	0		},
  { "com", "g,z",	2, { 0x17, 0x20 },	0		},
  { "com", "h",         2, { 0x17, 0x30 },	0		},

  { "cpd", "#j",	2, { 0x37, 0xB8 },	0		},
  { "cpd", "e,x",	2, { 0x27, 0x88 },	0		},
  { "cpd", "e,y",	2, { 0x27, 0x98 },	0		},
  { "cpd", "e,z",	2, { 0x27, 0xA8 },	0		},
  { "cpd", "f,x",	1, { 	   0x88 },	0		},
  { "cpd", "f,y",	1, {       0x98 },	0		},
  { "cpd", "f,z",	1, { 	   0xA8 },	0		},
  { "cpd", "g,x",	2, { 0x37, 0xC8 },	0		},
  { "cpd", "g,y",	2, { 0x37, 0xD8 },	0		},
  { "cpd", "g,z",	2, { 0x37, 0xE8 },	0		},
  { "cpd", "h",         2, { 0x37, 0xF8 },	0		},

  { "cpe", "#j",        2, { 0x37, 0x38 },	0		},
  { "cpe", "g,x",	2, { 0x37, 0x48 },	0		},
  { "cpe", "g,y",	2, { 0x37, 0x58 },	0		},
  { "cpe", "g,z",	2, { 0x37, 0x68 },	0		},
  { "cpe", "h",         2, { 0x37, 0x78 },	0		},

  { "cps", "#j",	2, { 0x37, 0x7F },	0		},
  { "cps", "f,x",	1, { 	   0x4f },	0		},
  { "cps", "f,y",	1, {       0x5F },	0		},
  { "cps", "f,z",	1, { 	   0x6F },	0		},
  { "cps", "g,x",	2, { 0x17, 0x4F },	0		},
  { "cps", "g,y",	2, { 0x17, 0x5F },	0		},
  { "cps", "g,z",	2, { 0x17, 0x6F },	0		},
  { "cps", "h",         2, { 0x17, 0x7F },	0		},

  { "tstx", "",		4, { 0x37, 0x7C, 0x00, 0x00 },	0	}, /* cpx #0 */

  { "cpx", "#j",	2, { 0x37, 0x7C },	0		},
  { "cpx", "f,x",	1, { 	   0x4C },	0		},
  { "cpx", "f,y",	1, {       0x5C },	0		},
  { "cpx", "f,z",	1, { 	   0x6C },	0		},
  { "cpx", "g,x",	2, { 0x17, 0x4C },	0		},
  { "cpx", "g,y",	2, { 0x17, 0x5C },	0		},
  { "cpx", "g,z",	2, { 0x17, 0x6C },	0		},
  { "cpx", "h",         2, { 0x17, 0x7C },	0		},

  { "tsty", "",		4, { 0x37, 0x7D, 0x00, 0x00 },	0	}, /* cpy #0 */

  { "cpy", "#j",	2, { 0x37, 0x7D },	0		},
  { "cpy", "f,x",	1, { 	   0x4D },	0		},
  { "cpy", "f,y",	1, {       0x5D },	0		},
  { "cpy", "f,z",	1, { 	   0x6D },	0		},
  { "cpy", "g,x",	2, { 0x17, 0x4D },	0		},
  { "cpy", "g,y",	2, { 0x17, 0x5D },	0		},
  { "cpy", "g,z",	2, { 0x17, 0x6D },	0		},
  { "cpy", "h",         2, { 0x17, 0x7D },	0		},

  { "cpz", "#j",	2, { 0x37, 0x7E },	0		},
  { "cpz", "f,x",	1, { 	   0x4E },	0		},
  { "cpz", "f,y",	1, {       0x5E },	0		},
  { "cpz", "f,z",	1, { 	   0x6E },	0		},
  { "cpz", "g,x",	2, { 0x17, 0x4E },	0		},
  { "cpz", "g,y",	2, { 0x17, 0x5E },	0		},
  { "cpz", "g,z",	2, { 0x17, 0x6E },	0		},
  { "cpz", "h",         2, { 0x17, 0x7E },	0		},

  { "tstz", "",		4, { 0x37, 0x7E, 0x00, 0x00 },	0	},  /* cpz #0 */

  { "daa",  "",		2, { 0x37, 0x21 },	0		},

  { "deca", "",		2, { 0x37, 0x01 },	0		},
  { "decb", "",		2, { 0x37, 0x11 },	0		},
  { "decw", "g,x",	2, { 0x27, 0x01 },	0		},
  { "decw", "g,y",	2, { 0x27, 0x11 },	0		},
  { "decw", "g,z",	2, { 0x27, 0x21 },	0		},
  { "decw", "h",	2, { 0x27, 0x31 },	0		},

  { "dec", "f,x",	1, { 	   0x01 },	0		},
  { "dec", "f,y",	1, {       0x11 },	0		},
  { "dec", "f,z",	1, { 	   0x21 },	0		},
  { "dec", "g,x",	2, { 0x17, 0x01 },	0		},
  { "dec", "g,y",	2, { 0x17, 0x11 },	0		},
  { "dec", "g,z",	2, { 0x17, 0x21 },	0		},
  { "dec", "h",         2, { 0x17, 0x31 },	0		},

  { "dey",  "",		2, { 0x3D, 0xFF },	0	},  /* aiy #-1 */
  { "dex",  "",		2, { 0x3C, 0xFF },	0	},  /* aix #-1 */
  { "des",  "",		2, { 0x3F, 0xFF },	0	},  /* ais #-1 */

  { "ediv", "",		2, { 0x37, 0x28 },	0		},
  { "edivs","",		2, { 0x37, 0x29 },	0		},
  { "emul", "",		2, { 0x37, 0x25 },	0		},
  { "emuls","",		2, { 0x37, 0x26 },	0		},

  { "eora", "#i",	1, { 	   0x74 },	0		},
  { "eora", "e,x",	2, { 0x27, 0x44 },	0		},
  { "eora", "e,y",	2, { 0x27, 0x54 },	0		},
  { "eora", "e,z",	2, { 0x27, 0x64 },	0		},
  { "eora", "f,x",	1, { 	   0x44 },	0		},
  { "eora", "f,y",	1, {       0x54 },	0		},
  { "eora", "f,z",	1, { 	   0x64 },	0		},
  { "eora", "g,x",	2, { 0x17, 0x44 },	0		},
  { "eora", "g,y",	2, { 0x17, 0x54 },	0		},
  { "eora", "g,z",	2, { 0x17, 0x64 },	0		},
  { "eora", "h",        2, { 0x17, 0x74 },	0		},

  { "eorb", "#i",	1, { 	   0xF4 },	0		},
  { "eorb", "e,x",	2, { 0x27, 0xC4 },	0		},
  { "eorb", "e,y",	2, { 0x27, 0xD4 },	0		},
  { "eorb", "e,z",	2, { 0x27, 0xE4 },	0		},
  { "eorb", "f,x",	1, { 	   0xC4 },	0		},
  { "eorb", "f,y",	1, {       0xD4 },	0		},
  { "eorb", "f,z",	1, { 	   0xE4 },	0		},
  { "eorb", "g,x",	2, { 0x17, 0xC4 },	0		},
  { "eorb", "g,y",	2, { 0x17, 0xD4 },	0		},
  { "eorb", "g,z",	2, { 0x17, 0xE4 },	0		},
  { "eorb", "h",        2, { 0x17, 0xF4 },	0		},

  { "eord", "#j",	2, { 0x37, 0xB4 },	0		},
  { "eord", "e,x",	2, { 0x27, 0x84 },	0		},
  { "eord", "e,y",	2, { 0x27, 0x94 },	0		},
  { "eord", "e,z",	2, { 0x27, 0xA4 },	0		},
  { "eord", "f,x",	1, { 	   0x84 },	0		},
  { "eord", "f,y",	1, {       0x94 },	0		},
  { "eord", "f,z",	1, { 	   0xA4 },	0		},
  { "eord", "g,x",	2, { 0x37, 0xC4 },	0		},
  { "eord", "g,y",	2, { 0x37, 0xD4 },	0		},
  { "eord", "g,z",	2, { 0x37, 0xE4 },	0		},
  { "eord", "h",        2, { 0x37, 0xF4 },	0		},

  { "eore", "#j",	2, { 0x37, 0x34 },	0		},
  { "eore", "g,x",	2, { 0x37, 0x44 },	0		},
  { "eore", "g,y",	2, { 0x37, 0x54 },	0		},
  { "eore", "g,z",	2, { 0x37, 0x64 },	0		},
  { "eore", "h",        2, { 0x37, 0x74 },	0		},

  { "fdiv", "",		2, { 0x37, 0x2B },	0		},
  { "fmuls","",		2, { 0x37, 0x27 },	0		},
  { "idiv", "",		2, { 0x37, 0x2A },	0		},

  { "inca", "",		2, { 0x37, 0x03 },	0		},
  { "incb", "",		2, { 0x37, 0x13 },	0		},
  { "incw", "g,x",	2, { 0x27, 0x03 },	0		},
  { "incw", "g,y",	2, { 0x27, 0x13 },	0		},
  { "incw", "g,z",	2, { 0x27, 0x23 },	0		},
  { "incw", "h",	2, { 0x27, 0x33 },	0		},

  { "inc", "f,x",	1, { 	   0x03 },	0		},
  { "inc", "f,y",	1, {       0x13 },	0		},
  { "inc", "f,z",	1, { 	   0x23 },	0		},
  { "inc", "g,x",	2, { 0x17, 0x03 },	0		},
  { "inc", "g,y",	2, { 0x17, 0x13 },	0		},
  { "inc", "g,z",	2, { 0x17, 0x23 },	0		},
  { "inc", "h",         2, { 0x17, 0x33 },	0		},

  { "iny",  "",		2, { 0x3D, 0x01 },	0		},  /* aiy #1 */
  { "inx",  "",		2, { 0x3C, 0x01 },	0		},  /* aix #1 */
  { "ins",  "",		2, { 0x3F, 0x01 },	0		},  /* ais #1 */

  { "jmp",  "d,x",	1, { 	   0x4B },	0		},
  { "jmp",  "d,y",	1, {       0x5B },	0		},
  { "jmp",  "d,z",	1, {       0x6B },	0		},
  { "jmp",  "m",	1, { 	   0x7A },	0		},

  { "jsr",  "d,x",	1, { 	   0x89 },	0		},
  { "jsr",  "d,y",	1, {       0x99 },	0		},
  { "jsr",  "d,z",	1, {       0xA9 },	0		},
  { "jsr",  "m",	1, { 	   0xFA },	0		},

  { "call", "m",	1, { 	   0xFA },	0		},  /* jsr*/

  { "lbcc", "l",	2, { 0x37, 0x84 },	0		},
  { "lbhs", "l",	2, { 0x37, 0x84 },	0		},  /* HC12 instruction same as lbcc*/
  { "lbcs", "l",	2, { 0x37, 0x85 },	0		},
  { "lblo", "l",	2, { 0x37, 0x85 },	0		},
  { "lbeq", "l",	2, { 0x37, 0x87 },	0		},
  { "lbge", "l",	2, { 0x37, 0x8C },	0		},
  { "lbgt", "l",	2, { 0x37, 0x8E },	0		},
  { "lbhi", "l",	2, { 0x37, 0x82 },	0		},
  { "lble", "l",	2, { 0x37, 0x8F },	0		},
  { "lbls", "l",	2, { 0x37, 0x83 },	0		},
  { "lblt", "l",	2, { 0x37, 0x8D },	0		},
  { "lbmi", "l",	2, { 0x37, 0x8B },	0		},
  { "lbne", "l",	2, { 0x37, 0x86 },	0		},
  { "lbpl", "l",	2, { 0x37, 0x8A },	0		},
  { "lbra", "l",	2, { 0x37, 0x80 },	0		},
  { "lbrn", "l",	2, { 0x37, 0x81 },	0		},
  { "lbvc", "l",	2, { 0x37, 0x88 },	0		},
  { "lbvs", "l",	2, { 0x37, 0x89 },	0		},

  { "lbev", "l",	2, { 0x37, 0x91 },	0		},
  { "lbmv", "l",	2, { 0x37, 0x90 },	0		},
  { "lbsr", "l",	2, { 0x27, 0xF9 },	0		},

  { "ldaa", "#i",	1, { 	   0x75 },	0		},
  { "ldaa", "e,x",	2, { 0x27, 0x45 },	0		},
  { "ldaa", "e,y",	2, { 0x27, 0x55 },	0		},
  { "ldaa", "e,z",	2, { 0x27, 0x65 },	0		},
  { "ldaa", "f,x",	1, { 	   0x45 },	0		},
  { "ldaa", "f,y",	1, {       0x55 },	0		},
  { "ldaa", "f,z",	1, { 	   0x65 },	0		},
  { "ldaa", "g,x",	2, { 0x17, 0x45 },	0		},
  { "ldaa", "g,y",	2, { 0x17, 0x55 },	0		},
  { "ldaa", "g,z",	2, { 0x17, 0x65 },	0		},
  { "ldaa", "h",        2, { 0x17, 0x75 },	0		},

  { "ldab", "#i",	1, { 	   0xF5 },	0		},
  { "ldab", "e,x",	2, { 0x27, 0xC5 },	0		},
  { "ldab", "e,y",	2, { 0x27, 0xD5 },	0		},
  { "ldab", "e,z",	2, { 0x27, 0xE5 },	0		},
  { "ldab", "f,x",	1, { 	   0xC5 },	0		},
  { "ldab", "f,y",	1, {       0xD5 },	0		},
  { "ldab", "f,z",	1, { 	   0xE5 },	0		},
  { "ldab", "g,x",	2, { 0x17, 0xC5 },	0		},
  { "ldab", "g,y",	2, { 0x17, 0xD5 },	0		},
  { "ldab", "g,z",	2, { 0x17, 0xE5 },	0		},
  { "ldab", "h",        2, { 0x17, 0xF5 },	0		},

  { "ldd", "#j",	2, { 0x37, 0xB5 },	0		},
  { "ldd", "e,x",	2, { 0x27, 0x85 },	0		},
  { "ldd", "e,y",	2, { 0x27, 0x95 },	0		},
  { "ldd", "e,z",	2, { 0x27, 0xA5 },	0		},
  { "ldd", "f,x",	1, { 	   0x85 },	0		},
  { "ldd", "f,y",	1, {       0x95 },	0		},
  { "ldd", "f,z",	1, { 	   0xA5 },	0		},
  { "ldd", "g,x",	2, { 0x37, 0xC5 },	0		},
  { "ldd", "g,y",	2, { 0x37, 0xD5 },	0		},
  { "ldd", "g,z",	2, { 0x37, 0xE5 },	0		},
  { "ldd", "h",         2, { 0x37, 0xF5 },	0		},

  { "lded", "h",	2, { 0x27, 0x71 },	0		},

  { "lde",  "#j",	2, { 0x37, 0x35 },	0		},
  { "lde", "g,x",	2, { 0x37, 0x45 },	0		},
  { "lde", "g,y",	2, { 0x37, 0x55 },	0		},
  { "lde", "g,z",	2, { 0x37, 0x65 },	0		},
  { "lde", "h",         2, { 0x37, 0x75 },	0		},

  { "ldhi", "",		2, { 0x27, 0xB0 },	0		},

  { "lds", "#j",	2, { 0x37, 0xBF },	0		},
  { "lds", "f,x",	1, { 	   0xCF },	0		},
  { "lds", "f,y",	1, {       0xDF },	0		},
  { "lds", "f,z",	1, { 	   0xEF },	0		},
  { "lds", "g,x",	2, { 0x17, 0xCF },	0		},
  { "lds", "g,y",	2, { 0x17, 0xDF },	0		},
  { "lds", "g,z",	2, { 0x17, 0xEF },	0		},
  { "lds", "h",         2, { 0x17, 0xFF },	0		},

  { "clrx", "",		4, { 0x37, 0xBC, 0x00, 0x00 },	0	},  /* ldx #0 */

  { "ldx", "#j",	2, { 0x37, 0xBC },	0		},
  { "ldx", "f,x",	1, { 	   0xCC },	0		},
  { "ldx", "f,y",	1, {       0xDC },	0		},
  { "ldx", "f,z",	1, { 	   0xEC },	0		},
  { "ldx", "g,x",	2, { 0x17, 0xCC },	0		},
  { "ldx", "g,y",	2, { 0x17, 0xDC },	0		},
  { "ldx", "g,z",	2, { 0x17, 0xEC },	0		},
  { "ldx", "h",         2, { 0x17, 0xFC },	0		},

  { "clry", "",		4, { 0x37, 0xBD, 0x00, 0x00 },	0	},  /* ldy #0 */

  { "ldy", "#j",	2, { 0x37, 0xBD },	0		},
  { "ldy", "f,x",	1, { 	   0xCD },	0		},
  { "ldy", "f,y",	1, {       0xDD },	0		},
  { "ldy", "f,z",	1, { 	   0xED },	0		},
  { "ldy", "g,x",	2, { 0x17, 0xCD },	0		},
  { "ldy", "g,y",	2, { 0x17, 0xDD },	0		},
  { "ldy", "g,z",	2, { 0x17, 0xED },	0		},
  { "ldy", "h",         2, { 0x17, 0xFD },	0		},

  { "ldz", "#j",	2, { 0x37, 0xBE },	0		},
  { "ldz", "f,x",	1, { 	   0xCE },	0		},
  { "ldz", "f,y",	1, {       0xDE },	0		},
  { "ldz", "f,z",	1, { 	   0xEE },	0		},
  { "ldz", "g,x",	2, { 0x17, 0xCE },	0		},
  { "ldz", "g,y",	2, { 0x17, 0xDE },	0		},
  { "ldz", "g,z",	2, { 0x17, 0xEE },	0		},
  { "ldz", "h",         2, { 0x17, 0xFE },	0		},

  { "clrz", "",		4, { 0x37, 0xBE, 0x00, 0x00 },	0	}, /* ldz #0 */

  { "lpstop", "",	2, { 0x27, 0xF1 },	0		},
  { "stop",   "",	2, { 0x27, 0xF1 },	0		},

  { "lsld", "",		2, { 0x27, 0xF4 },	0		},  /* asld */

  { "lsla", "",		2, { 0x37, 0x04 },	0		},  /* asla */
  { "lslb", "",		2, { 0x37, 0x14 },	0		},  /* aslb */
  { "lsl",  "f,x",	1, {  	   0x04 },	0		},  /* asl */
  { "lsl",  "f,y",	1, {       0x14 },	0		},  /* asl */
  { "lsl",  "f,z",	1, {       0x24 },	0		},  /* asl */
  { "lsl",  "g,x",	2, { 0x17, 0x04 },	0		},  /* asl */
  { "lsl",  "g,y",	2, { 0x17, 0x14 },	0		},  /* asl */
  { "lsl",  "g,z",	2, { 0x17, 0x24 },	0		},  /* asl */
  { "lsl",  "h",	2, { 0x17, 0x34 },	0		},  /* asl */

  { "lsra", "",		2, { 0x37, 0x0F },	0		},
  { "lsrb", "",		2, { 0x37, 0x1F },	0		},
  { "lsrd", "",		2, { 0x27, 0xFF },	0		},
  { "lsre", "",		2, { 0x27, 0x7F },	0		},
  { "lsrw", "g,x",	2, { 0x27, 0x0F },	0		},
  { "lsrw", "g,y",	2, { 0x27, 0x1F },	0		},
  { "lsrw", "g,z",	2, { 0x27, 0x2F },	0		},
  { "lsrw", "h",        2, { 0x27, 0x3F },	0		},

  { "lsr", "f,x",	1, { 	   0x0F },	0		},
  { "lsr", "f,y",	1, {       0x1F },	0		},
  { "lsr", "f,z",	1, { 	   0x2F },	0		},
  { "lsr", "g,x",	2, { 0x17, 0x0F },	0		},
  { "lsr", "g,y",	2, { 0x17, 0x1F },	0		},
  { "lsr", "g,z",	2, { 0x17, 0x2F },	0		},
  { "lsr", "h",         2, { 0x17, 0x3F },	0		},

  { "mac", "#a,#b",    	1, {	   0x7B },	0		},
  { "mac", "a,b",	1, { 	   0x7B },	0		},

  { "movb", "k,x,h",	1, { 	   0x30 },	0    		},
  { "movb", "s,k,x",	1, { 	   0x32 },	1		},
  { "movb", "h,h",	2, { 0x37, 0xFE },	0		},

  { "movw", "k,x,h",	1, { 	   0x31 },	0		},
  { "movw", "s,k,x",	1, { 	   0x33 },	1		},
  { "movw", "h,h",	2, { 0x37, 0xFF },	0		},

  { "mul",  "",		2, { 0x37, 0x24 },	0		},
  { "nega", "",		2, { 0x37, 0x02 },	0		},
  { "negb", "",		2, { 0x37, 0x12 },	0		},
  { "negd", "",		2, { 0x27, 0xF2 },	0		},
  { "nege", "",		2, { 0x27, 0x72 },	0		},
  { "negw", "g,x",	2, { 0x27, 0x02 },	0		},
  { "negw", "g,y",	2, { 0x27, 0x12 },	0		},
  { "negw", "g,z",	2, { 0x27, 0x22 },	0		},
  { "negw", "h",        2, { 0x27, 0x32 },	0		},

  { "neg", "f,x",	1, { 	   0x02 },	0		},
  { "neg", "f,y",	1, {       0x12 },	0		},
  { "neg", "f,z",	1, { 	   0x22 },	0		},
  { "neg", "g,x",	2, { 0x17, 0x02 },	0		},
  { "neg", "g,y",	2, { 0x17, 0x12 },	0		},
  { "neg", "g,z",	2, { 0x17, 0x22 },	0		},
  { "neg", "h",         2, { 0x17, 0x32 },	0		},

  { "nop",  "",		2, { 0x27, 0x4C },	0		},

  { "oraa", "#i",	1, { 	   0x77 },	0		},
  { "oraa", "e,x",	2, { 0x27, 0x47 },	0		},
  { "oraa", "e,y",	2, { 0x27, 0x57 },	0		},
  { "oraa", "e,z",	2, { 0x27, 0x67 },	0		},
  { "oraa", "f,x",	1, { 	   0x47 },	0		},
  { "oraa", "f,y",	1, {       0x57 },	0		},
  { "oraa", "f,z",	1, { 	   0x67 },	0		},
  { "oraa", "g,x",	2, { 0x17, 0x47 },	0		},
  { "oraa", "g,y",	2, { 0x17, 0x57 },	0		},
  { "oraa", "g,z",	2, { 0x17, 0x67 },	0		},
  { "oraa", "h",        2, { 0x17, 0x77 },	0		},

  { "orab", "#i",	1, { 	   0xF7 },	0		},
  { "orab", "e,x",	2, { 0x27, 0xC7 },	0		},
  { "orab", "e,y",	2, { 0x27, 0xD7 },	0		},
  { "orab", "e,z",	2, { 0x27, 0xE7 },	0		},
  { "orab", "f,x",	1, { 	   0xC7 },	0		},
  { "orab", "f,y",	1, {       0xD7 },	0		},
  { "orab", "f,z",	1, { 	   0xE7 },	0		},
  { "orab", "g,x",	2, { 0x17, 0xC7 },	0		},
  { "orab", "g,y",	2, { 0x17, 0xD7 },	0		},
  { "orab", "g,z",	2, { 0x17, 0xE7 },	0		},
  { "orab", "h",        2, { 0x17, 0xF7 },	0		},

  { "ord", "#j",	2, { 0x37, 0xB7 },	0		},
  { "ord", "e,x",	2, { 0x27, 0x87 },	0		},
  { "ord", "e,y",	2, { 0x27, 0x97 },	0		},
  { "ord", "e,z",	2, { 0x27, 0xA7 },	0		},
  { "ord", "f,x",	1, { 	   0x87 },	0		},
  { "ord", "f,y",	1, {       0x97 },	0		},
  { "ord", "f,z",	1, { 	   0xA7 },	0		},
  { "ord", "g,x",	2, { 0x37, 0xC7 },	0		},
  { "ord", "g,y",	2, { 0x37, 0xD7 },	0		},
  { "ord", "g,z",	2, { 0x37, 0xE7 },	0		},
  { "ord", "h",         2, { 0x37, 0xF7 },	0		},

  { "ore", "#j",	2, { 0x37, 0x37 },	0		},
  { "ore", "g,x",	2, { 0x37, 0x47 },	0		},
  { "ore", "g,y",	2, { 0x37, 0x57 },	0		},
  { "ore", "g,z",	2, { 0x37, 0x67 },	0		},
  { "ore", "h",         2, { 0x37, 0x77 },	0		},

  { "orp", "#j",	2, { 0x37, 0x3B },	0		},

  { "tdy",  "",		4, { 0x34, 0x01, 0x35, 0x08 },	0	}, /* pshd, puly */
  { "tdx",  "",		4, { 0x34, 0x01, 0x35, 0x10 },	0	}, /* pshd, pulx */

  { "tyd",  "", 	4, { 0x34, 0x08, 0x35, 0x40 },	0	}, /* pshy, puld */
  { "txd",  "", 	4, { 0x34, 0x04, 0x35, 0x40 },	0	}, /* pshx, puld */

  { "pshm", "o",        1, {	   0x34 },	0		},
  { "pshy", "",		2, { 0x34, 0x08 },	0		},
  { "pshx", "",		2, { 0x34, 0x04 },	0		},
  { "pshd", "",		2, { 0x34, 0x01 },	0		},  /* pshb, psha */
  { "pshb", "",		2, { 0x37, 0x18 },	0		},
  { "psha", "",		2, { 0x37, 0x08 },	0		},

  { "pshmac", "",	2, { 0x27, 0xB8 },	0		},

  { "pulm", "p",        1, {	   0x35 },	0		},
  { "puly", "",		2, { 0x35, 0x08 },	0		},
  { "pulx", "",		2, { 0x35, 0x10 },	0		},
  { "puld", "",		2, { 0x35, 0x40 },	0		},
  { "pulb", "",		2, { 0x37, 0x19 },	0		},
  { "pula", "",		2, { 0x37, 0x09 },	0		},

  { "pulmac", "",	2, { 0x27, 0xB9 },	0		},

  { "rmac", "#a,#b",   	1, {	   0xFB },	0		},
  { "rmac", "a,b",    	1, {	   0xFB },	0		},

  { "rold", "",		2, { 0x27, 0xFC },	0		},
  { "role", "",		2, { 0x27, 0x7C },	0		},
  { "rola", "",		2, { 0x37, 0x0C },	0		},
  { "rolb", "",		2, { 0x37, 0x1C },	0		},

  { "asled", "",	4, { 0x27, 0xF4, 0x27, 0x7C },	0	}, /* asld, role */
  { "lsled", "",	4, { 0x27, 0xF4, 0x27, 0x7C },	0	}, /* lsld, role */

  { "rolw", "g,x",	2, { 0x27, 0x0C },	0		},
  { "rolw", "g,y",	2, { 0x27, 0x1C },	0		},
  { "rolw", "g,z",	2, { 0x27, 0x2C },	0		},
  { "rolw", "h",	2, { 0x27, 0x3C },	0		},

  { "rol",  "f,x",	1, {       0x0C },	0		},
  { "rol",  "f,y",	1, { 	   0x1C },	0		},
  { "rol",  "f,z",	1, { 	   0x2C },	0		},
  { "rol",  "g,x",	2, { 0x17, 0x0C },	0		},
  { "rol",  "g,y",	2, { 0x17, 0x1C },	0		},
  { "rol",  "g,z",	2, { 0x17, 0x2C },	0		},
  { "rol",  "h",	2, { 0x17, 0x3C },	0		},

  { "rord", "",		2, { 0x27, 0xFE },	0		},
  { "rore", "",		2, { 0x27, 0x7E },	0		},
  { "rora", "",		2, { 0x37, 0x0E },	0		},
  { "rorb", "",		2, { 0x37, 0x1E },	0		},

  { "asred", "",	4, { 0x27, 0x7D, 0x27, 0xFE },	0	}, /* asre, rord */
  { "lsred", "",	4, { 0x27, 0x7F, 0x27, 0xFE },	0	}, /* lsre, rord */

  { "rorw", "g,x",	2, { 0x27, 0x0E },	0		},
  { "rorw", "g,y",	2, { 0x27, 0x1E },	0		},
  { "rorw", "g,z",	2, { 0x27, 0x2E },	0		},
  { "rorw", "h",	2, { 0x27, 0x3E },	0		},

  { "ror",  "f,x",	1, {       0x0E },	0		},
  { "ror",  "f,y",	1, { 	   0x1E },	0		},
  { "ror",  "f,z",	1, { 	   0x2E },	0		},
  { "ror",  "g,x",	2, { 0x17, 0x0E },	0		},
  { "ror",  "g,y",	2, { 0x17, 0x1E },	0		},
  { "ror",  "g,z",	2, { 0x17, 0x2E },	0		},
  { "ror",  "h",	2, { 0x17, 0x3E },	0		},

  { "rti",  "",		2, { 0x27, 0x77 },	0		},
  { "rts",  "",		2, { 0x27, 0xF7 },	0		},

  { "sbca", "#i",	1, { 	   0x72 },	0		},
  { "sbca", "e,x",	2, { 0x27, 0x42 },	0		},
  { "sbca", "e,y",	2, { 0x27, 0x52 },	0		},
  { "sbca", "e,z",	2, { 0x27, 0x62 },	0		},
  { "sbca", "f,x",	1, { 	   0x42 },	0		},
  { "sbca", "f,y",	1, {       0x52 },	0		},
  { "sbca", "f,z",	1, { 	   0x62 },	0		},
  { "sbca", "g,x",	2, { 0x17, 0x42 },	0		},
  { "sbca", "g,y",	2, { 0x17, 0x52 },	0		},
  { "sbca", "g,z",	2, { 0x17, 0x62 },	0		},
  { "sbca", "h",        2, { 0x17, 0x72 },	0		},

  { "sbcb", "#i",	1, { 	   0xF2 },	0		},
  { "sbcb", "e,x",	2, { 0x27, 0xC2 },	0		},
  { "sbcb", "e,y",	2, { 0x27, 0xD2 },	0		},
  { "sbcb", "e,z",	2, { 0x27, 0xE2 },	0		},
  { "sbcb", "f,x",	1, { 	   0xC2 },	0		},
  { "sbcb", "f,y",	1, {       0xD2 },	0		},
  { "sbcb", "f,z",	1, { 	   0xE2 },	0		},
  { "sbcb", "g,x",	2, { 0x17, 0xC2 },	0		},
  { "sbcb", "g,y",	2, { 0x17, 0xD2 },	0		},
  { "sbcb", "g,z",	2, { 0x17, 0xE2 },	0		},
  { "sbcb", "h",        2, { 0x17, 0xF2 },	0		},

  { "sbcd", "#j",	2, { 0x37, 0xB2 },	0		},
  { "sbcd", "e,x",	2, { 0x27, 0x82 },	0		},
  { "sbcd", "e,y",	2, { 0x27, 0x92 },	0		},
  { "sbcd", "e,z",	2, { 0x27, 0xA2 },	0		},
  { "sbcd", "f,x",	1, { 	   0x82 },	0		},
  { "sbcd", "f,y",	1, {       0x92 },	0		},
  { "sbcd", "f,z",	1, { 	   0xA2 },	0		},
  { "sbcd", "g,x",	2, { 0x37, 0xC2 },	0		},
  { "sbcd", "g,y",	2, { 0x37, 0xD2 },	0		},
  { "sbcd", "g,z",	2, { 0x37, 0xE2 },	0		},
  { "sbcd", "h",        2, { 0x37, 0xF2 },	0		},

  { "sbce", "#j",	2, { 0x37, 0x32 },	0		},
  { "sbce", "g,x",	2, { 0x37, 0x42 },	0		},
  { "sbce", "g,y",	2, { 0x37, 0x52 },	0		},
  { "sbce", "g,z",	2, { 0x37, 0x62 },	0		},
  { "sbce", "h",        2, { 0x37, 0x72 },	0		},

  { "sba",  "",		2, { 0x37, 0x0A },	0		},
  { "sde",  "",		2, { 0x27, 0x79 },	0		},

  { "sec",  "",		4, { 0x37, 0x3B, 0x01, 0x00 },	0	},
  { "sei",  "",		4, { 0x37, 0x3B, 0x00, 0xE0 },	0	},
  { "sev",  "",		4, { 0x37, 0x3B, 0x02, 0x00 },	0	},

  { "staa", "e,x",	2, { 0x27, 0x4A },	0		},
  { "staa", "e,y",	2, { 0x27, 0x5A },	0		},
  { "staa", "e,z",	2, { 0x27, 0x6A },	0		},
  { "staa", "f,x",	1, { 	   0x4A },	0		},
  { "staa", "f,y",	1, {       0x5A },	0		},
  { "staa", "f,z",	1, { 	   0x6A },	0		},
  { "staa", "g,x",	2, { 0x17, 0x4A },	0		},
  { "staa", "g,y",	2, { 0x17, 0x5A },	0		},
  { "staa", "g,z",	2, { 0x17, 0x6A },	0		},
  { "staa", "h",        2, { 0x17, 0x7A },	0		},

  { "stab", "e,x",	2, { 0x27, 0xCA },	0		},
  { "stab", "e,y",	2, { 0x27, 0xDA },	0		},
  { "stab", "e,z",	2, { 0x27, 0xEA },	0		},
  { "stab", "f,x",	1, { 	   0xCA },	0		},
  { "stab", "f,y",	1, {       0xDA },	0		},
  { "stab", "f,z",	1, { 	   0xEA },	0		},
  { "stab", "g,x",	2, { 0x17, 0xCA },	0		},
  { "stab", "g,y",	2, { 0x17, 0xDA },	0		},
  { "stab", "g,z",	2, { 0x17, 0xEA },	0		},
  { "stab", "h",        2, { 0x17, 0xFA },	0		},

  { "std", "e,x",	2, { 0x27, 0x8A },	0		},
  { "std", "e,y",	2, { 0x27, 0x9A },	0		},
  { "std", "e,z",	2, { 0x27, 0xAA },	0		},
  { "std", "f,x",	1, { 	   0x8A },	0		},
  { "std", "f,y",	1, {       0x9A },	0		},
  { "std", "f,z",	1, { 	   0xAA },	0		},
  { "std", "g,x",	2, { 0x37, 0xCA },	0		},
  { "std", "g,y",	2, { 0x37, 0xDA },	0		},
  { "std", "g,z",	2, { 0x37, 0xEA },	0		},
  { "std", "h",         2, { 0x37, 0xFA },	0		},

  { "ste", "g,x",	2, { 0x37, 0x4A },	0		},
  { "ste", "g,y",	2, { 0x37, 0x5A },	0		},
  { "ste", "g,z",	2, { 0x37, 0x6A },	0		},
  { "ste", "h",         2, { 0x37, 0x7A },	0		},

  { "sted","h",         2, { 0x27, 0x73 },	0		},

  { "sts", "f,x",	1, { 	   0x8F },	0		},
  { "sts", "f,y",	1, {       0x9F },	0		},
  { "sts", "f,z",	1, { 	   0xAF },	0		},
  { "sts", "g,x",	2, { 0x17, 0x8F },	0		},
  { "sts", "g,y",	2, { 0x17, 0x9F },	0		},
  { "sts", "g,z",	2, { 0x17, 0xAF },	0		},
  { "sts", "h",         2, { 0x17, 0xBF },	0		},

  { "stx", "f,x",	1, { 	   0x8C },	0		},
  { "stx", "f,y",	1, {       0x9C },	0		},
  { "stx", "f,z",	1, { 	   0xAC },	0		},
  { "stx", "g,x",	2, { 0x17, 0x8C },	0		},
  { "stx", "g,y",	2, { 0x17, 0x9C },	0		},
  { "stx", "g,z",	2, { 0x17, 0xAC },	0		},
  { "stx", "h",         2, { 0x17, 0xBC },	0		},

  { "sty", "f,x",	1, { 	   0x8D },	0		},
  { "sty", "f,y",	1, {       0x9D },	0		},
  { "sty", "f,z",	1, { 	   0xAD },	0		},
  { "sty", "g,x",	2, { 0x17, 0x8D },	0		},
  { "sty", "g,y",	2, { 0x17, 0x9D },	0		},
  { "sty", "g,z",	2, { 0x17, 0xAD },	0		},
  { "sty", "h",         2, { 0x17, 0xBD },	0		},

  { "stz", "f,x",	1, { 	   0x8E },	0		},
  { "stz", "f,y",	1, {       0x9E },	0		},
  { "stz", "f,z",	1, { 	   0xAE },	0		},
  { "stz", "g,x",	2, { 0x17, 0x8E },	0		},
  { "stz", "g,y",	2, { 0x17, 0x9E },	0		},
  { "stz", "g,z",	2, { 0x17, 0xAE },	0		},
  { "stz", "h",         2, { 0x17, 0xBE },	0		},

  { "suba", "#i",	1, { 	   0x70 },	0		},
  { "suba", "e,x",	2, { 0x27, 0x40 },	0		},
  { "suba", "e,y",	2, { 0x27, 0x50 },	0		},
  { "suba", "e,z",	2, { 0x27, 0x60 },	0		},
  { "suba", "f,x",	1, { 	   0x40 },	0		},
  { "suba", "f,y",	1, {       0x50 },	0		},
  { "suba", "f,z",	1, { 	   0x60 },	0		},
  { "suba", "g,x",	2, { 0x17, 0x40 },	0		},
  { "suba", "g,y",	2, { 0x17, 0x50 },	0		},
  { "suba", "g,z",	2, { 0x17, 0x60 },	0		},
  { "suba", "h",        2, { 0x17, 0x70 },	0		},

  { "subb", "#i",	1, { 	   0xF0 },	0		},
  { "subb", "e,x",	2, { 0x27, 0xC0 },	0		},
  { "subb", "e,y",	2, { 0x27, 0xD0 },	0		},
  { "subb", "e,z",	2, { 0x27, 0xE0 },	0		},
  { "subb", "f,x",	1, { 	   0xC0 },	0		},
  { "subb", "f,y",	1, {       0xD0 },	0		},
  { "subb", "f,z",	1, { 	   0xE0 },	0		},
  { "subb", "g,x",	2, { 0x17, 0xC0 },	0		},
  { "subb", "g,y",	2, { 0x17, 0xD0 },	0		},
  { "subb", "g,z",	2, { 0x17, 0xE0 },	0		},
  { "subb", "h",        2, { 0x17, 0xF0 },	0		},

  { "decd", "",		4, { 0x37, 0xB0, 0x00, 0x01 },	0	}, /* subd #1 */

  { "subd", "#j",	2, { 0x37, 0xB0 },	0		},
  { "subd", "e,x",	2, { 0x27, 0x80 },	0		},
  { "subd", "e,y",	2, { 0x27, 0x90 },	0		},
  { "subd", "e,z",	2, { 0x27, 0xA0 },	0		},
  { "subd", "f,x",	1, { 	   0x80 },	0		},
  { "subd", "f,y",	1, {       0x90 },	0		},
  { "subd", "f,z",	1, { 	   0xA0 },	0		},
  { "subd", "g,x",	2, { 0x37, 0xC0 },	0		},
  { "subd", "g,y",	2, { 0x37, 0xD0 },	0		},
  { "subd", "g,z",	2, { 0x37, 0xE0 },	0		},
  { "subd", "h",        2, { 0x37, 0xF0 },	0		},

  { "sube", "#j",	2, { 0x37, 0x30 },	0		},
  { "sube", "g,x",	2, { 0x37, 0x40 },	0		},
  { "sube", "g,y",	2, { 0x37, 0x50 },	0		},
  { "sube", "g,z",	2, { 0x37, 0x60 },	0		},
  { "sube", "h",        2, { 0x37, 0x70 },	0		},

  { "dece", "",		4, { 0x37, 0x30, 0x00, 0x01 },	0	}, /* sube */

  { "swi",  "",		2, { 0x37, 0x20 },	0		},
  { "sxtb", "",		2, { 0x27, 0xF8 },	0		}, /* sxt */
  { "sxt",  "",		2, { 0x27, 0xF8 },	0		},

  { "sxtd", "",		10,{ 0x27, 0x75, 0x27, 0xFD, 0x27, 0xFC, 0x37, 0x32, 0x00, 0x00},	0	}, /*clre asrd rold sbce #0*/

  { "tab",  "",		2, { 0x37, 0x17 },	0		},
  { "tap",  "",		2, { 0x37, 0xFD },	0		},

  { "tba",  "",		2, { 0x37, 0x07 },	0		},
  { "tbek", "",		2, { 0x27, 0xFA },	0		},
  { "tbsk", "",		2, { 0x37, 0x9F },	0		},
  { "tbxk", "",		2, { 0x37, 0x9C },	0		},
  { "tbyk", "",		2, { 0x37, 0x9D },	0		},
  { "tbzk", "",		2, { 0x37, 0x9E },	0		},

  { "tde",  "",		2, { 0x27, 0x7B },	0		},
  { "tdmsk","",		2, { 0x37, 0x2F },	0		},
  { "tdp",  "",		2, { 0x37, 0x2D },	0		},

  { "ted",  "",		2, { 0x27, 0xFB },	0		},
  { "tedm", "",		2, { 0x27, 0xB1 },	0		},
  { "tekb", "",		2, { 0x27, 0xBB },	0		},
  { "tem",  "",		2, { 0x27, 0xB2 },	0		},
  { "tmer", "",		2, { 0x27, 0xB4 },	0		},
  { "tmet", "",		2, { 0x27, 0xB5 },	0		},
  { "tmxed","",		2, { 0x27, 0xB3 },	0		},

  { "tpa",  "",		2, { 0x37, 0xFC },	0		},
  { "tpd",  "",		2, { 0x37, 0x2C },	0		},

  { "tsta", "",		2, { 0x37, 0x06 },	0		},
  { "tstb", "",		2, { 0x37, 0x16 },	0		},
  { "tstd", "",		2, { 0x27, 0xF6 },	0		},
  { "tste", "",		2, { 0x27, 0x76 },	0		},

  { "tstw", "g,x",	2, { 0x27, 0x06 },	0		},
  { "tstw", "g,y",	2, { 0x27, 0x16 },	0		},
  { "tstw", "g,z",	2, { 0x27, 0x26 },	0		},
  { "tstw", "h",        2, { 0x27, 0x36 },	0		},

  { "tskb", "",		2, { 0x37, 0xAF },	0		},

  { "tst", "f,x",	1, { 	   0x06 },	0		},
  { "tst", "f,y",	1, {       0x16 },	0		},
  { "tst", "f,z",	1, { 	   0x26 },	0		},
  { "tst", "g,x",	2, { 0x17, 0x06 },	0		},
  { "tst", "g,y",	2, { 0x17, 0x16 },	0		},
  { "tst", "g,z",	2, { 0x17, 0x26 },	0		},
  { "tst", "h",         2, { 0x17, 0x36 },	0		},

  { "tsx",  "",		2, { 0x27, 0x4F },	0		},
  { "tsy",  "",		2, { 0x27, 0x5F },	0		},
  { "tsz",  "",		2, { 0x27, 0x6F },	0		},

  { "txkb", "",		2, { 0x37, 0xAC },	0		},
  { "txs",  "",		2, { 0x37, 0x4E },	0		},
  { "txy",  "",		2, { 0x27, 0x5C },	0		},
  { "txz",  "",		2, { 0x27, 0x6C },	0		},

  { "tykb", "",		2, { 0x37, 0xAD },	0		},
  { "tys",  "",		2, { 0x37, 0x5E },	0		},
  { "tyx",  "",		2, { 0x27, 0x4D },	0		},
  { "tyz",  "",		2, { 0x27, 0x6D },	0		},

  { "tzkb", "",		2, { 0x37, 0xAE },	0		},
  { "tzs",  "",		2, { 0x37, 0x6E },	0		},
  { "tzx",  "",		2, { 0x27, 0x4E },	0		},
  { "tzy",  "",		2, { 0x27, 0x5E },	0		},

  { "tex",  "",		4, { 0x34, 0x02, 0x35, 0x10},	0	}, /*pshm e pulm x*/
  { "txe",  "",		4, { 0x34, 0x04, 0x35, 0x20},	0	}, /*pshm x pulm e*/
  { "tey",  "",		4, { 0x34, 0x02, 0x35, 0x08},	0	}, /*pshm e pulm y*/
  { "tye",  "",		4, { 0x34, 0x08, 0x35, 0x20},	0	}, /*pshm y pulm e*/
  { "tdz",  "",		4, { 0x34, 0x01, 0x35, 0x04},	0	}, /*pshm d pulm z*/
  { "tzd",  "",		4, { 0x34, 0x10, 0x35, 0x40},	0	}, /*pshm z pulm d*/
  { "tez",  "",		4, { 0x34, 0x02, 0x35, 0x04},	0	}, /*pshm e pulm z*/
  { "tze",  "",		4, { 0x34, 0x10, 0x35, 0x20},	0	}, /*pshm z pulm e*/

  { "wai",  "",		2, { 0x27, 0xF3 },	0		},

  { "xgab", "",		2, { 0x37, 0x1A },	0		},
  { "xgde", "",		2, { 0x27, 0x7A },	0		},
  { "xgdx", "",		2, { 0x37, 0xCC },	0		},
  { "xgxy", "",		6, { 0x37, 0xCC, 0x37, 0xDC, 0x37, 0xCC }
					 ,	0		},
				 /* xgdx, xgdy, xgdx */
  { "roly", "",		2, { 0x37, 0xDC, 0x27, 0xFC, 0x37, 0xDC},
						0		}, /* xgdy, rold, xgdy */
  { "rory", "",		2, { 0x37, 0xDC, 0x27, 0xFE, 0x37, 0xDC},
						0		}, /* xgdy, rord, xgdy */
  { "asly", "",		2, { 0x37, 0xDC, 0x27, 0xF4, 0x37, 0xDC},
						0		}, /* xgdy, asld, xgdy */
  { "xgdy", "",		2, { 0x37, 0xDC },	0		},
  { "xgdz", "",		2, { 0x37, 0xEC },	0		},
  { "xgex", "",		2, { 0x37, 0x4C },	0		},
  { "xgey", "",		2, { 0x37, 0x5C },	0		},
  { "xgez", "",		2, { 0x37, 0x6C },	0		},

  { NULL }
};


/* end of hc1x-opcode.h */
