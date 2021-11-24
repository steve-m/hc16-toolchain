/* hc12-opcode.h -- Motorola 68hc12
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

This file is ported to 68HC12 by:
     Real-Time Systems Inc.
     1212 Austin Avenue, Coquitlam, B.C. Canada. V3H 3X3
     email: querbach@realtime.bc.ca
*/


/* opcode table entry structure */

struct hc12_opcode
{
  char* name;			/* mnemonic */
  char* args;			/* operand pattern */
  int len;			/* instruction length in bytes */
  unsigned char code[5];	/* instruction bytes */
  int swap;			/* only used for movb and movw*/
};


/* operand codes for "args" field:

  # 	immediate operand follows
  e	exchange
  i	1-byte immediate operand
  j	2-byte immediate operand
  g	1-byte direct-page address dir
  h	2-byte extended address ext
  l	loop
  p	trap
  q	long relative
  r	1-byte pc-relative offset
  s	sign extend
  t	transfer
  u	indexed indirect only
  v	call relocation
  w	any indexed mode
  x	oprx0_xysp only, first or only in insn
  y	oprx0_xysp only, second in insn
  z	indexed mode, but not indirect
*/

static struct hc12_opcode hc12_opcodes[] =
{
  { "aba",  "",		2, { 0x18, 0x06 },	0	},
  { "aby",  "",		2, { 0x19, 0xED }, 	0	},
  { "abx",  "",		2, { 0x1A, 0xE5 }, 		},

  { "adca", "#i",	1, {       0x89 }, 	0	},
  { "adca", "w",	1, {       0xA9 }, 	0	},
  { "adca", "g",	1, {       0x99 }, 	0	},
  { "adca", "h",	1, {       0xB9 }, 	0	},

  { "adcb", "#i",	1, {       0xC9 }, 	0	},
  { "adcb", "w",	1, {       0xE9 }, 	0	},
  { "adcb", "g",	1, {       0xD9 }, 	0	},
  { "adcb", "h",	1, {       0xF9 }, 	0	},

  { "adda", "#i",	1, {       0x8B }, 	0	},
  { "adda", "w",	1, {       0xAB }, 	0	},
  { "adda", "g",	1, {       0x9B }, 	0	},
  { "adda", "h",	1, {       0xBB }, 	0	},

  { "addb", "#i",	1, {       0xCB }, 	0	},
  { "addb", "w",	1, {       0xEB }, 	0	},
  { "addb", "g",	1, {       0xDB }, 	0	},
  { "addb", "h",	1, {       0xFB }, 	0	},

  { "addd", "#j",	1, {       0xC3 }, 	0	},
  { "addd", "w",	1, {       0xE3 }, 	0	},
  { "addd", "g",	1, {       0xD3 }, 	0	},
  { "addd", "h",	1, {       0xF3 }, 	0	},

  { "incd", "",		3, {       0xC3, 0x00, 0x01 }, 0	}, /* addd #1 */

  { "anda", "#i",	1, {       0x84 }, 	0	},
  { "anda", "w",	1, {       0xA4 }, 	0	},
  { "anda", "g",	1, {       0x94 }, 	0	},
  { "anda", "h",	1, {       0xB4 }, 	0	},

  { "andb", "#i",	1, {       0xC4 },	0	},
  { "andb", "w",	1, {       0xE4 },	0	},
  { "andb", "g",	1, {       0xD4 },	0	},
  { "andb", "h",	1, {       0xF4 },	0	},

  { "andcc", "#i",	1, {       0x10 },	0 		},

  { "asl",  "w",	1, {       0x68 },	0		},
  { "asl",  "h",	1, {       0x78 },        0		},
  { "asla", "",		1, {       0x48 },        0		},
  { "aslb", "",		1, {       0x58 },        0		},
  { "asld", "",		1, {       0x59 },        0		},

  { "asr",  "w",	1, {       0x67 },        0		},
  { "asr",  "h",	1, {       0x77 },        0 		},
  { "asra", "",		1, {       0x47 },        0		},
  { "asrb", "",		1, {       0x57 },        0		},
  { "asrd", "",		2, {       0x47, 0x56 },        0	},  /* asra, rorb */

  { "bcc",  "r",	1, {       0x24 },        0		},

  { "bclr", "g,#i",	1, {       0x4D },        0		},
  { "bclr", "h,#i",	1, { 	   0x1D },        0		},
  { "bclr", "z,#i",	1, {       0x0D },        0		},

  { "bcs",  "r",	1, {       0x25 },        0		},
  { "beq",  "r",	1, {       0x27 },        0		},
  { "bge",  "r",	1, {       0x2C },        0		},
  { "bgnd", "",		1, {	   0x00 },        0		},
  { "bgt",  "r",	1, {       0x2E },        0		},
  { "bhi",  "r",	1, {       0x22 },        0		},
  { "bhs",  "r",	1, {       0x24 },        0		},

  { "bita", "#i",	1, {       0x85 },        0 		},
  { "bita", "w",	1, {       0xA5 },        0 		},
  { "bita", "g",	1, {       0x95 },        0 		},
  { "bita", "h",	1, {       0xB5 },        0 		},

  { "bitb", "#i",	1, {       0xC5 },        0 		},
  { "bitb", "w",	1, {       0xE5 },        0 		},
  { "bitb", "g",	1, {       0xD5 },        0 		},
  { "bitb", "h",	1, {       0xF5 },        0 		},

  { "ble",  "r",	1, {       0x2F },        0		},
  { "blo",  "r",       	1, {       0x25 },        0		},
  { "bls",  "r",	1, {       0x23 },        0		},
  { "blt",  "r",	1, {       0x2D },        0		},
  { "bmi",  "r",	1, {       0x2B },        0		},
  { "bne",  "r",	1, {       0x26 },        0		},
  { "bpl",  "r",	1, {       0x2A },        0		},
  { "bra",  "r",	1, {       0x20 },        0		},

  { "brclr", "g,#i,r",	1, {       0x4F },        0		},
  { "brclr", "h,#i,r",  1, {       0x1F },        0		},
  { "brclr", "z,#i,r",  1, {       0x0F },        0		},

  { "brn",  "r",	1, {       0x21 },        0		},

  { "brset", "g,#i,r",	1, {       0x4E },        0		},
  { "brset", "h,#i,r",  1, {       0x1E },        0		},
  { "brset", "z,#i,r",  1, {       0x0E },        0		},

  { "bset", "g,#i",	1, {       0x4C },        0		},
  { "bset", "h,#i",	1, {       0x1C },        0		},
  { "bset", "z,#i",	1, {       0x0C },        0		},

  { "bsr",  "r",	1, {       0x07 },        0 		},
  { "bvc",  "r",	1, {       0x28 },        0		},
  { "bvs",  "r",	1, {       0x29 },        0		},

  { "call", "u",	1, {       0x4B },        0 		},
  { "call", "z,i",	1, {       0x4B },        0 		},
  { "call", "h,i",	1, {       0x4A },        0 		},
  { "call", "v",	1, {       0x4A },        0 		},

  { "cba",  "",		2, { 0x18, 0x17 },        0		},
  { "clc",  "",		2, { 0x10, 0xFE },        0 		},
  { "cli",  "",		2, { 0x10, 0xEF },        0 		},
  { "clv",  "",		2, { 0x10, 0xFD },        0 		},

  { "clr",  "w",	1, {       0x69 },        0		},
  { "clr",  "h",	1, {       0x79 },        0		},
  { "clra", "",		1, {       0x87 },        0		},
  { "clrb", "",		1, {       0xC7 },        0		},
  { "clrd", "",		2, {       0x87, 0xC7 },  0		},  /* clra, clrb */

  { "cmpa", "#i",	1, {       0x81 },        0 		},
  { "cmpa", "w",	1, {       0xA1 },        0 		},
  { "cmpa", "g",	1, {       0x91 },        0 		},
  { "cmpa", "h",	1, {       0xB1 },        0 		},

  { "cmpb", "#i",	1, {       0xC1 },        0 		},
  { "cmpb", "w",	1, {       0xE1 },        0 		},
  { "cmpb", "g",	1, {       0xD1 },        0 		},
  { "cmpb", "h",	1, {       0xF1 },        0 		},

  { "negd", "",		5, {       0x41, 0x51, 0xC3, 0x00, 0x01 },        0}, /* coma,
							     comb, addd #1 */
  { "comd", "",		2, {       0x41, 0x51	},	0 	}, /* coma, comb */

  { "com",  "w",	1, {       0x61 },        0		},
  { "com",  "h",	1, {       0x71 },        0		},
  { "coma", "",		1, {       0x41 },        0		},
  { "comb", "",		1, {       0x51 },        0		},

  { "tsty", "",		3, { 0x8D, 0x00, 0x00 },        0 	}, /* cpy #0 */

  { "cpd",  "#j",	1, {       0x8C },        0 		},
  { "cpd",  "w",	1, {       0xAC },        0 		},
  { "cpd",  "g",	1, {       0x9C },        0 		},
  { "cpd",  "h",	1, {       0xBC },        0 		},

  { "cps",  "#j",	1, {       0x8F },        0 		},
  { "cps",  "w",	1, {       0xAF },        0 		},
  { "cps",  "g",	1, {       0x9F },        0 		},
  { "cps",  "h",	1, {       0xBF },        0 		},

  { "cpx",  "#j",	1, {       0x8E },        0 		},
  { "cpx",  "w",	1, {       0xAE },        0 		},
  { "cpx",  "g",	1, {       0x9E },        0 		},
  { "cpx",  "h",	1, {       0xBE },        0 		},

  { "cpy",  "#j",	1, {       0x8D },        0 		},
  { "cpy",  "w",	1, {       0xAD },        0 		},
  { "cpy",  "g",	1, {       0x9D },        0 		},
  { "cpy",  "h",	1, {       0xBD },        0 		},

  { "tstx", "",		3, {       0x8E, 0x00, 0x00 },        0	}, /* cpx #0 */
  { "tstd", "",		3, {       0x8C, 0x00, 0x00 },        0	}, /* cpd #0 */

  { "daa",  "",		2, { 0x18, 0x07 },        0		},

  { "dbeq", "l",	1, {       0x04, 0x00},	  0		},
  { "dbne", "l",	1, {       0x04, 0x20},	  0		},

  { "dec",  "w",	1, {       0x63 },        0		},
  { "dec",  "h",	1, {       0x73 },        0		},
  { "deca", "",		1, {       0x43 },        0		},
  { "decb", "",		1, {       0x53 },        0		},

  { "dey",  "",		1, {       0x03 },        0		},
  { "dex",  "",		1, {       0x09 },        0		},
  { "des",  "",		2, { 0x1B, 0x9F },        0		},

  { "emacs","h",	2, { 0x18, 0x12 },        0		},
  { "emaxd","w",	2, { 0x18, 0x1A },        0		},
  { "emaxm","w",	2, { 0x18, 0x1E },        0		},
  { "emind","w",	2, { 0x18, 0x1B },        0		},
  { "eminm","w",	2, { 0x18, 0x1F },        0		},
  { "ediv", "",		1, {	   0x11 },        0		},
  { "edivs","",		2, { 0x18, 0x14 },        0		},

  { "emul", "",		1, {       0x13 },        0		},
  { "emuls","",		2, { 0x18, 0x13 },        0		},

  { "eora", "#i",	1, {       0x88 },        0 		},
  { "eora", "w",	1, {       0xA8 },        0 		},
  { "eora", "g",	1, {       0x98 },        0 		},
  { "eora", "h",	1, {       0xB8 },        0 		},

  { "eorb", "#i",	1, {       0xC8 },        0 		},
  { "eorb", "w",	1, {       0xE8 },        0 		},
  { "eorb", "g",	1, {       0xD8 },        0 		},
  { "eorb", "h",	1, {       0xF8 },        0 		},

  { "etbl", "x",	2, { 0x18, 0x3F },        0		},
  { "exg",  "e",	1, {       0xB7, 0x80 },  0		},

  { "fdiv", "",		2, { 0x18, 0x11 },        0		},

  { "ibeq", "l",	1, {       0x04, 0x80 },        0		},
  { "ibne", "l",	1, {       0x04, 0xA0 },        0		},

  { "idiv", "",		2, { 0x18, 0x10 },        0		},
  { "idivs","",		2, { 0x18, 0x15 },        0		},

  { "inca", "",		1, {       0x42 },        0		},
  { "incb", "",		1, {       0x52 },        0		},
  { "inc",  "w",	1, {       0x62 },        0		},
  { "inc",  "h",	1, {       0x72 },        0		},

  { "iny",  "",		1, {       0x02 },        0		},
  { "inx",  "",		1, {       0x08 },        0		},
  { "ins",  "",		2, { 0x1B, 0x81 },        0		},

  { "jmp",  "w",	1, {       0x05 },        0		},
  { "jmp",  "h",	1, {       0x06 },        0		},

  { "jsr",  "w",	1, {       0x15 },        0 		},
  { "jsr",  "g",	1, {       0x17 },        0 		},
  { "jsr",  "h",	1, {       0x16 },        0 		},

  { "lbsr", "q",	2, { 0x15, 0xFA },        0	 	},  /* jsr targ,pc */

  { "lbcc", "q",	2, { 0x18, 0x24 },        0	 	},
  { "lbcs", "q",	2, { 0x18, 0x25 },        0	 	},
  { "lbeq", "q",	2, { 0x18, 0x27 },        0	 	},
  { "lbge", "q",	2, { 0x18, 0x2C },        0	 	},
  { "lbgt", "q",	2, { 0x18, 0x2E },        0	 	},
  { "lbhi", "q",	2, { 0x18, 0x22 },        0	 	},
  { "lbhs", "q",	2, { 0x18, 0x24 },        0	 	},
  { "lble", "q",	2, { 0x18, 0x2F },        0	 	},
  { "lblo", "q",	2, { 0x18, 0x25 },        0	 	},
  { "lbls", "q",	2, { 0x18, 0x23 },        0	 	},
  { "lblt", "q",	2, { 0x18, 0x2D },        0	 	},
  { "lbmi", "q",	2, { 0x18, 0x2B },        0	 	},
  { "lbne", "q",	2, { 0x18, 0x26 },        0	 	},
  { "lbpl", "q",	2, { 0x18, 0x2A },        0	 	},
  { "lbra", "q",	2, { 0x18, 0x20	},        0		},
  { "lbrn", "q",	2, { 0x18, 0x21 },        0	 	},
  { "lbvc", "q",	2, { 0x18, 0x28 },        0	 	},
  { "lbvs", "q",	2, { 0x18, 0x29 },        0	 	},

  { "ldaa", "#i",	1, {       0x86 },        0 		},
  { "ldaa", "w",	1, {       0xA6 },        0 		},
  { "ldaa", "g",	1, {       0x96 },        0 		},
  { "ldaa", "h",	1, {       0xB6 },        0 		},

  { "ldab", "#i",	1, {       0xC6 },        0 		},
  { "ldab", "w",	1, {       0xE6 },        0 		},
  { "ldab", "g",	1, {       0xD6 },        0 		},
  { "ldab", "h",	1, {       0xF6 },        0 		},

  { "ldd",  "#j",	1, {       0xCC },        0 		},
  { "ldd",  "w",	1, {       0xEC },        0 		},
  { "ldd",  "g",	1, {       0xDC },        0 		},
  { "ldd",  "h",	1, {       0xFC },        0 		},

  { "lds",  "#j",	1, {       0xCF },        0 		},
  { "lds",  "w",	1, {       0xEF },        0 		},
  { "lds",  "g",	1, {       0xDF },        0 		},
  { "lds",  "h",	1, {       0xFF },        0 		},

  { "ldx",  "#j",	1, {       0xCE },        0 		},
  { "ldx",  "w",	1, {       0xEE },        0 		},
  { "ldx",  "g",	1, {       0xDE },        0 		},
  { "ldx",  "h",	1, {       0xFE },        0 		},

  { "clry", "",		3, { 0xCD, 0x00, 0x00 },  0	 	},  /* ldy #0 */

  { "ldy",  "#j",	1, {       0xCD },        0 		},
  { "ldy",  "w",	1, {       0xED },        0 		},
  { "ldy",  "g",	1, {       0xDD },        0 		},
  { "ldy",  "h",	1, {       0xFD },        0 		},

  { "clrx", "",		3, { 0xCE, 0x00, 0x00 },  0	 	},  /* ldx #0 */

  { "leas",  "z",	1, {       0x1B },        0 		},
  { "leax",  "z",	1, {       0x1A },        0 		},
  { "leay",  "z",	1, {       0x19 },        0 		},

  { "lsla", "",		1, {       0x48 },        0		},
  { "lslb", "",		1, {       0x58 },        0		},
  { "lsld", "",		1, {       0x59 },        0		},
  { "lsl",  "w",	1, {       0x68 },        0		},
  { "lsl",  "h",	1, {       0x78 },        0		},

  { "lsra", "",		1, {       0x44 },        0		},
  { "lsrb", "",		1, {       0x54 },        0		},
  { "lsrd", "",		1, {       0x49 },        0		},
  { "lsr",  "w",	1, {       0x64 },        0		},
  { "lsr",  "h",	1, {       0x74 },        0		},

  { "maxa", "w",	2, { 0x18, 0x18 },        0		},
  { "maxm", "w",	2, { 0x18, 0x1C },        0		},
  { "mem",  "",		1, {       0x01 },        0		},
  { "mina", "w",	2, { 0x18, 0x19 },        0		},
  { "minm", "w",	2, { 0x18, 0x1D },        0		},

  { "movb", "#i,h",	2, { 0x18, 0x0B },        0		},
  { "movb", "#i,x",	2, { 0x18, 0x08 },        1		},
  { "movb", "x,y",	2, { 0x18, 0x0A },        0		},
  { "movb", "x,h",	2, { 0x18, 0x0D },        0		},
  { "movb", "h,x",	2, { 0x18, 0x09 },        1		},
  { "movb", "h,h",	2, { 0x18, 0x0C },        0		},

  { "movw", "#j,h",	2, { 0x18, 0x03 },        0		},
  { "movw", "#j,x",	2, { 0x18, 0x00 },        1		},
  { "movw", "x,y",	2, { 0x18, 0x02 },        0		},
  { "movw", "x,h",	2, { 0x18, 0x05 },        0		},
  { "movw", "h,x",	2, { 0x18, 0x01 },        1		},
  { "movw", "h,h",	2, { 0x18, 0x04 },        0		},

  { "mul",  "",		1, {       0x12 },        0		},

  { "nega", "",		1, {       0x40 },        0		},
  { "negb", "",		1, {       0x50 },        0		},
  { "neg",  "w",	1, {       0x60 },        0		},
  { "neg",  "h",	1, {       0x70 },        0		},

  { "nop",  "",		1, {       0xA7 },        0		},

  { "oraa", "#i",	1, {       0x8A },        0 		},
  { "oraa", "w",	1, {       0xAA },        0 		},
  { "oraa", "g",	1, {       0x9A },        0 		},
  { "oraa", "h",	1, {       0xBA },        0 		},

  { "orab", "#i",	1, {       0xCA },        0 		},
  { "orab", "w",	1, {       0xEA },        0 		},
  { "orab", "g",	1, {       0xDA },        0 		},
  { "orab", "h",	1, {       0xFA },        0 		},

  { "orcc", "#i",	1, {       0x14 },        0 		},

  { "tdy",  "",		2, { 0x3B, 0x31 },        0 		}, /* pshd, puly */
  { "tdx",  "",		2, { 0x3B, 0x30 },        0		}, /* pshd, pulx */

  { "tyd",  "", 	2, { 0x35, 0x3A },        0		}, /* pshy, puld */
  { "txd",  "", 	2, { 0x34, 0x3A },        0		}, /* pshx, puld */

  { "tyx",  "",         2, { 0x35, 0x30 },        0		}, /* pshy, pulx */
  { "txy",  "",		2, { 0x34, 0x31 },        0		}, /* pshx, puly */


  { "pshy", "",		1, {       0x35 },        0		},
  { "pshx", "",		1, {       0x34 },        0		},
  { "pshd", "",		1, {       0x3B },        0		},  /* pshb, psha */
  { "pshc", "",		1, {       0x39 },        0		},
  { "pshb", "",		1, {       0x37 },        0		},
  { "psha", "",		1, {       0x36 },        0		},

  { "puly", "",		1, {       0x31 },        0		},
  { "pulx", "",		1, {       0x30 },        0		},
  { "puld", "",		1, {       0x3A },        0		},  /* pula, pulb */
  { "pulc", "",		1, {       0x38 },        0		},
  { "pulb", "",		1, {       0x33 },        0		},
  { "pula", "",		1, {       0x32 },        0		},

  { "rev", "",		2, { 0x18, 0x3A },        0		},
  { "revw", "",		2, { 0x18, 0x3B },        0		},

  { "rold", "",		2, {       0x55, 0x45 },  0		},  /* rolb, rola */

  { "rola", "",		1, {       0x45 },        0		},
  { "rolb", "",		1, {       0x55 },        0		},
  { "rol",  "w",	1, {       0x65 },        0		},
  { "rol",  "h",	1, {       0x75 },        0		},

  { "rord", "",		2, {       0x46, 0x56 },  0		},  /* rora, rorb */

  { "rora", "",		1, {       0x46 },        0		},
  { "rorb", "",		1, {       0x56 },        0		},
  { "ror",  "w",	1, {       0x66 },        0		},
  { "ror",  "h",	1, {       0x76 },        0		},

  { "rtc",  "",		1, {       0x0A },        0		},
  { "rti",  "",		1, {       0x0B },        0		},
  { "rts",  "",		1, {       0x3D },        0		},

  { "sba",  "",		2, { 0x18, 0x16 },        0		},

  { "sbca", "#i",	1, {       0x82 },        0 		},
  { "sbca", "w",	1, {       0xA2 },        0 		},
  { "sbca", "g",	1, {       0x92 },        0 		},
  { "sbca", "h",	1, {       0xB2 },        0 		},

  { "sbcb", "#i",	1, {       0xC2 },        0 		},
  { "sbcb", "w",	1, {       0xE2 },        0 		},
  { "sbcb", "g",	1, {       0xD2 },        0 		},
  { "sbcb", "h",	1, {       0xF2 },        0 		},

  { "sec",  "",		2, { 0x14, 0x01 },        0 		},
  { "sei",  "",		2, { 0x14, 0x10 },        0 		},
  { "sev",  "",		2, { 0x14, 0x02 },        0 		},
  { "sex",  "s",	1, {       0xB7, 0x00 },  0		},
  { "sxtb", "",         2, {       0xB7, 0x14 },  0		},

  { "staa", "w",	1, {       0x6A },        0 		},
  { "staa", "g",	1, {       0x5A },        0 		},
  { "staa", "h",	1, {       0x7A },        0 		},

  { "stab", "w",	1, {       0x6B },        0 		},
  { "stab", "g",	1, {       0x5B },        0 		},
  { "stab", "h",	1, {       0x7B },        0 		},

  { "std",  "w",	1, {       0x6C },        0 		},
  { "std",  "g",	1, {       0x5C },        0 		},
  { "std",  "h",	1, {       0x7C },        0 		},

  { "stop", "",		2, { 0x18, 0x3E },        0		},

  { "sts",  "w",	1, {       0x6F },        0 		},
  { "sts",  "g",	1, {       0x5F },        0 		},
  { "sts",  "h",	1, {       0x7F },        0 		},

  { "sty",  "w",	1, {       0x6D },        0 		},
  { "sty",  "g",	1, {       0x5D },        0 		},
  { "sty",  "h",	1, {       0x7D },        0 		},

  { "stx",  "w",	1, {       0x6E },        0 		},
  { "stx",  "g",	1, {       0x5E },        0 		},
  { "stx",  "h",	1, {       0x7E },        0 		},

  { "suba", "#i",	1, {       0x80 },        0 		},
  { "suba", "w",	1, {       0xA0 },        0 		},
  { "suba", "g",	1, {       0x90 },        0 		},
  { "suba", "h",	1, {       0xB0 },        0 		},

  { "subb", "#i",	1, {       0xC0 },        0 		},
  { "subb", "w",	1, {       0xE0 },        0 		},
  { "subb", "g",	1, {       0xD0 },        0 		},
  { "subb", "h",	1, {       0xF0 },        0 		},

  { "decd", "",		3, {       0x83, 0x00, 0x01 },        0 	}, /* subd #1 */

  { "subd", "#j",	1, {       0x83 },        0 		},
  { "subd", "w",	1, {       0xA3 },        0 		},
  { "subd", "g",	1, {       0x93 },        0 		},
  { "subd", "h",	1, {       0xB3 },        0 		},

  { "swi",  "",		1, {       0x3F },        0		},
  { "tab",  "",		2, { 0x18, 0x0E },        0		},
  { "tap",  "",		2, { 0xB7, 0x02 },        0		},
  { "tba",  "",		2, { 0x18, 0x0F },        0		},
  { "tbeq", "l",	1, {       0x04, 0x40 },  0		},
  { "tbl",  "x",	2, { 0x18, 0x3D },        0 		},
  { "tbne", "l",	1, {       0x04, 0x60 },  0		},

  { "tfr",  "t",	1, {       0xB7 },        0 		},
  { "tpa",  "",		2, { 0xB7, 0x20 },        0		},

  { "trap", "p",	1, {       0x18 },        0 		},

  { "test", "",		1, {       0x00 },        0		},

  { "tsta", "",		1, {       0x97 },        0		},
  { "tstb", "",		1, {       0xD7 },        0		},
  { "tst",  "w",	1, {       0xE7 },        0		},
  { "tst",  "h",	1, {       0xF7 },        0		},

  { "tsy",  "",		2, { 0xB7, 0x76 },        0		},
  { "tsx",  "",		2, { 0xB7, 0x75 },        0		},
  { "tys",  "",		2, { 0xB7, 0x67 },        0		},
  { "txs",  "",		2, { 0xB7, 0x57 },        0		},

  { "wai",  "",		1, {       0x3E },        0		},
  { "wav",  "",		2, { 0x18, 0x3C },        0 		},

  { "xgdy", "",		2, { 0xB7, 0xC6 },        0		},
  { "xgdx", "",		2, { 0xB7, 0xC5 },        0		},

  { NULL }
};

// indexed addressing mode postbyte decoding table entry structure
struct idx_post
{
  char* oprand;
  int	len;
  int	common;
  int	rr;
};

/* indexed addressing mode postbyte decoding table

   codes for oprand filed

   3	operx3
   5	operx5
   9	operx9
   w	operx16
   a	register a, b, d
   d	register d
   v	register x, y, s, sp
   z	register x, y, s, sp, p, pc
*/

// indexed idx mode
static struct idx_post idx0[] =
{
  { "a,z",	1,	0xE4,	 0x08 	},
  { "b,z",	1,	0xE5,	 0x08 	},
  { "d,z",	1,	0xE6,	 0x08 	},
  { "3,+v",     1,	0x20,	 0x40 	},
  { "3,-v",	1,	0x28,	 0x40 	},
  { "3,v+",	1,	0x30,	 0x40 	},
  { "3,v-",	1,	0x38,	 0x40 	},
  { "5,z",	1,	0x00,	 0x40	},
  { NULL }

};

// indexed idx1 and idx2 mode
static struct idx_post idx16[] =
{
  { "9,z",	2,	0xE0,	0x08	},
  { "w,z",	3,	0xE2,	0x08 	},
  { NULL }
};

// indexed indirect mode
static struct idx_post idx_ind[] =
{
  { "[d,z]",	1,	0xE7,	 0x08 	},
  { "[w,z]",	3,	0xE3,	 0x08 	},
  { NULL }
};

// index register entry structure
struct idx_reg
{
  char* reg;		// register name string
  int	code;		// postbyte register number field
};


static struct idx_reg idx_regs[] =
{
  { "x",	0x00	},
  { "y",	0x01	},
  { "s",	0x02	},
  { "sp",	0x02	},
  { "p",	0x03	},
  { "pc",	0x03	},
  { NULL }
};


/* end of hc1x-opcode.h */
