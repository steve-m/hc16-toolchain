/* hc11-opcode.h -- Motorola 68HC11
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

This file is ported to 68HC11 by:
     Real-Time Systems Inc.
     1212 Austin Avenue, Coquitlam, B.C. Canada. V3H 3X3
     email: querbach@realtime.bc.ca
*/


/* opcode table entry structure */

struct hc11_opcode
{
  char* name;			/* mnemonic */
  char* args;			/* operand pattern */
  int len;			/* instruction length in bytes */
  unsigned char code[5];	/* instruction bytes */
};


/* operand codes for "args" field:

  # 	immediate operand follows
  ,	literal comma required
  i	1-bytez immediate operand
  j	2-byte immediate operand
  f	1-byte offset from x or y
  g	1-byte direct-page address
  h	2-byte extended address
  r	1-byte pc-relative offset

*/

static struct hc11_opcode hc11_opcodes[] =
{
  { "aba",  "",		1, {       0x1B },		},
  { "aby",  "",		2, { 0x18, 0x3A }, 		},
  { "abx",  "",		1, {       0x3A } 		},

  { "adca", "#i",	1, {       0x89 } 		},
  { "adca", "f,y",	2, { 0x18, 0xA9 } 		},
  { "adca", "f,x",	1, {       0xA9 } 		},
  { "adca", "g",	1, {       0x99 } 		},
  { "adca", "h",	1, {       0xB9 } 		},

  { "adcb", "#i",	1, {       0xC9 } 		},
  { "adcb", "f,y",	2, { 0x18, 0xE9 } 		},
  { "adcb", "f,x",	1, {       0xE9 } 		},
  { "adcb", "g",	1, {       0xD9 } 		},
  { "adcb", "h",	1, {       0xF9 } 		},

  { "adda", "#i",	1, {       0x8B } 		},
  { "adda", "f,y",	2, { 0x18, 0xAB } 		},
  { "adda", "f,x",	1, {       0xAB } 		},
  { "adda", "g",	1, {       0x9B } 		},
  { "adda", "h",	1, {       0xBB } 		},

  { "addb", "#i",	1, {       0xCB } 		},
  { "addb", "f,y",	2, { 0x18, 0xEB } 		},
  { "addb", "f,x",	1, {       0xEB } 		},
  { "addb", "g",	1, {       0xDB } 		},
  { "addb", "h",	1, {       0xFB } 		},

  { "incd", "",		3, {       0xC3, 0x00, 0x01 }	}, /* addd #1 */

  { "addd", "#j",	1, {       0xC3 } 		},
  { "addd", "f,y",	2, { 0x18, 0xE3 } 		},
  { "addd", "f,x",	1, {       0xE3 } 		},
  { "addd", "g",	1, {       0xD3 } 		},
  { "addd", "h",	1, {       0xF3 } 		},

  { "anda", "#i",	1, {       0x84 } 		},
  { "anda", "f,y",	2, { 0x18, 0xA4 } 		},
  { "anda", "f,x",	1, {       0xA4 } 		},
  { "anda", "g",	1, {       0x94 } 		},
  { "anda", "h",	1, {       0xB4 } 		},

  { "andb", "#i",	1, {       0xC4 }		},
  { "andb", "f,y",	2, { 0x18, 0xE4 }		},
  { "andb", "f,x",	1, {       0xE4 }		},
  { "andb", "g",	1, {       0xD4 }		},
  { "andb", "h",	1, {       0xF4 }		},

  { "asld", "",		1, {       0x05 }		},

  { "asla", "",		1, {       0x48 }		},
  { "aslb", "",		1, {       0x58 }		},
  { "asl",  "f,y",	2, { 0x18, 0x68 }		},
  { "asl",  "f,x",	1, {       0x68 }		},
  { "asl",  "h",	1, {       0x78 }		},

  { "asrd", "",		2, {       0x47, 0x56 }		},  /* asra, rorb */

  { "asra", "",		1, {       0x47 }		},
  { "asrb", "",		1, {       0x57 }		},
  { "asr",  "f,y",	2, { 0x18, 0x67 }		},
  { "asr",  "f,x",	1, {       0x67 }		},
  { "asr",  "h",	1, {       0x77 } 		},

  { "lbrn", "h",	3, {       0x20, 0x03, 0x7E } 	},  /* bra, jmp */
  { "lbhi", "h",	3, {       0x23, 0x03, 0x7E } 	},  /* bls, jmp */
  { "lbls", "h",	3, {       0x22, 0x03, 0x7E } 	},  /* bhi, jmp */
  { "lbhs", "h",	3, {       0x25, 0x03, 0x7E } 	},  /* blo, jmp */
  { "lbcc", "h",	3, {       0x25, 0x03, 0x7E } 	},  /* bcs, jmp */
  { "lblo", "h",	3, {       0x24, 0x03, 0x7E } 	},  /* bhs, jmp */
  { "lbcs", "h",	3, {       0x24, 0x03, 0x7E } 	},  /* bcc, jmp */
  { "lbne", "h",	3, {       0x27, 0x03, 0x7E } 	},  /* beq, jmp */
  { "lbeq", "h",	3, {       0x26, 0x03, 0x7E } 	},  /* bne, jmp */
  { "lbvc", "h",	3, {       0x29, 0x03, 0x7E } 	},  /* bvs, jmp */
  { "lbvs", "h",	3, {       0x28, 0x03, 0x7E } 	},  /* bvc, jmp */
  { "lbpl", "h",	3, {       0x2B, 0x03, 0x7E } 	},  /* bmi, jmp */
  { "lbmi", "h",	3, {       0x2A, 0x03, 0x7E } 	},  /* bpl, jmp */
  { "lbge", "h",	3, {       0x2D, 0x03, 0x7E } 	},  /* blt, jmp */
  { "lblt", "h",	3, {       0x2C, 0x03, 0x7E } 	},  /* bge, jmp */
  { "lbgt", "h",	3, {       0x2F, 0x03, 0x7E } 	},  /* ble, jmp */
  { "lble", "h",	3, {       0x2E, 0x03, 0x7E } 	},  /* bgt, jmp */

  { "bra",  "r",	1, {       0x20 }		},
  { "brn",  "r",	1, {       0x21 }		},
  { "bhi",  "r",	1, {       0x22 }		},
  { "bls",  "r",	1, {       0x23 }		},
  { "bhs",  "r",	1, {       0x24 }		},
  { "bcc",  "r",	1, {       0x24 }		},
  { "blo",  "r",       	1, {       0x25 }		},
  { "bcs",  "r",	1, {       0x25 }		},
  { "bne",  "r",	1, {       0x26 }		},
  { "beq",  "r",	1, {       0x27 }		},
  { "bvc",  "r",	1, {       0x28 }		},
  { "bvs",  "r",	1, {       0x29 }		},
  { "bpl",  "r",	1, {       0x2A }		},
  { "bmi",  "r",	1, {       0x2B }		},
  { "bge",  "r",	1, {       0x2C }		},
  { "blt",  "r",	1, {       0x2D }		},
  { "bgt",  "r",	1, {       0x2E }		},
  { "ble",  "r",	1, {       0x2F }		},

  { "bita", "#i",	1, {       0x85 } 		},
  { "bita", "f,y",	2, { 0x18, 0xA5 } 		},
  { "bita", "f,x",	1, {       0xA5 } 		},
  { "bita", "g",	1, {       0x95 } 		},
  { "bita", "h",	1, {       0xB5 } 		},

  { "bitb", "#i",	1, {       0xC5 } 		},
  { "bitb", "f,y",	2, { 0x18, 0xE5 } 		},
  { "bitb", "f,x",	1, {       0xE5 } 		},
  { "bitb", "g",	1, {       0xD5 } 		},
  { "bitb", "h",	1, {       0xF5 } 		},

  { "bclr", "g,#i",	1, {       0x15 }		},
  { "bclr", "f,y,#i",	2, { 0x18, 0x1D }		},
  { "bclr", "f,x,#i",	1, {       0x1D }		},

  { "bset", "g,#i",	1, {       0x14 }		},
  { "bset", "f,y,#i",	2, { 0x18, 0x1C }		},
  { "bset", "f,x,#i",	1, {       0x1C }		},

  { "brclr", "g,#i,r",	1, {       0x13 }		},
  { "brclr", "f,y,#i,r",2, { 0x18, 0x1F }		},
  { "brclr", "f,x,#i,r",1, {       0x1F }		},

  { "brset", "g,#i,r",	1, {       0x12 }		},
  { "brset", "f,y,#i,r",2, { 0x18, 0x1E }		},
  { "brset", "f,x,#i,r",1, {       0x1E }		},

  { "cba",  "",		1, {       0x11 }		},
  { "clc",  "",		1, {       0x0C } 		},
  { "cli",  "",		1, {       0x0E } 		},
  { "clv",  "",		1, {       0x0A } 		},

  { "sxtb", "",		5, {	   0x4F, 0x57, 0x59, 0x82, 0x00 }}, /* clra,
							asrb, rolb, sbca #0 */
  { "clrd", "",		2, {       0x4F, 0x5F }		},  /* clra, clrb */

  { "clra", "",		1, {       0x4F }		},
  { "clrb", "",		1, {       0x5F }		},
  { "clr",  "f,y",	2, { 0x18, 0x6F }		},
  { "clr",  "f,x",	1, {       0x6F }		},
  { "clr",  "h",	1, {       0x7F }		},

  { "cmpa", "#i",	1, {       0x81 } 		},
  { "cmpa", "f,y",	2, { 0x18, 0xA1 } 		},
  { "cmpa", "f,x",	1, {       0xA1 } 		},
  { "cmpa", "g",	1, {       0x91 } 		},
  { "cmpa", "h",	1, {       0xB1 } 		},

  { "cmpb", "#i",	1, {       0xC1 } 		},
  { "cmpb", "f,y",	2, { 0x18, 0xE1 } 		},
  { "cmpb", "f,x",	1, {       0xE1 } 		},
  { "cmpb", "g",	1, {       0xD1 } 		},
  { "cmpb", "h",	1, {       0xF1 } 		},

  { "negd", "",		5, {       0x43, 0x53, 0xC3, 0x00, 0x01 }}, /* coma,
							     comb, addd #1 */
  { "comd", "",		2, {       0x43, 0x53	} 	}, /* coma, comb */

  { "coma", "",		1, {       0x43 }		},
  { "comb", "",		1, {       0x53 }		},
  { "com",  "f,y",	2, { 0x18, 0x63 }		},
  { "com",  "f,x",	1, {       0x63 }		},
  { "com",  "h",	1, {       0x73 }		},

  { "tsty", "",		4, { 0x18, 0x8C, 0x00, 0x00 } 	}, /* cpy #0 */

  { "cpy",  "#j",	2, { 0x18, 0x8C } 		},
  { "cpy",  "f,y",	2, { 0x18, 0xAC } 		},
  { "cpy",  "f,x",	2, { 0x1A, 0xAC } 		},
  { "cpy",  "g",	2, { 0x18, 0x9C } 		},
  { "cpy",  "h",	2, { 0x18, 0xBC } 		},

  { "tstx", "",		3, {       0x8C, 0x00, 0x00 } 	}, /* cpx #0 */

  { "cpx",  "#j",	1, {       0x8C } 		},
  { "cpx",  "f,y",	2, { 0xCD, 0xAC } 		},
  { "cpx",  "f,x",	1, {       0xAC } 		},
  { "cpx",  "g",	1, {       0x9C } 		},
  { "cpx",  "h",	1, {       0xBC } 		},

  { "tstd", "",		4, { 0x1A, 0x83, 0x00, 0x00 } 	}, /* cpd #0 */

  { "cpd",  "#j",	2, { 0x1A, 0x83 } 		},
  { "cpd",  "f,y",	2, { 0xCD, 0xA3 } 		},
  { "cpd",  "f,x",	2, { 0x1A, 0xA3 } 		},
  { "cpd",  "g",	2, { 0x1A, 0x93 } 		},
  { "cpd",  "h",	2, { 0x1A, 0xB3 } 		},

  { "daa",  "",		1, {       0x19 }		},

  { "deca", "",		1, {       0x4A }		},
  { "decb", "",		1, {       0x5A }		},
  { "dec",  "f,y",	2, { 0x18, 0x6A }		},
  { "dec",  "f,x",	1, {       0x6A }		},
  { "dec",  "h",	1, {       0x7A }		},

  { "dey",  "",		2, { 0x18, 0x09 }		},
  { "dex",  "",		1, {       0x09 }		},
  { "des",  "",		1, {       0x34 }		},

  { "eora", "#i",	1, {       0x88 } 		},
  { "eora", "f,y",	2, { 0x18, 0xA8 } 		},
  { "eora", "f,x",	1, {       0xA8 } 		},
  { "eora", "g",	1, {       0x98 } 		},
  { "eora", "h",	1, {       0xB8 } 		},

  { "eorb", "#i",	1, {       0xC8 } 		},
  { "eorb", "f,y",	2, { 0x18, 0xE8 } 		},
  { "eorb", "f,x",	1, {       0xE8 } 		},
  { "eorb", "g",	1, {       0xD8 } 		},
  { "eorb", "h",	1, {       0xF8 } 		},

  { "fdiv", "",		1, {       0x03 }		},
  { "idiv", "",		1, {       0x02 }		},

  { "inca", "",		1, {       0x4C }		},
  { "incb", "",		1, {       0x5C }		},
  { "inc",  "f,y",	2, { 0x18, 0x6C }		},
  { "inc",  "f,x",	1, {       0x6C }		},
  { "inc",  "h",	1, {       0x7C }		},

  { "iny",  "",		2, { 0x18, 0x08 }		},
  { "inx",  "",		1, {       0x08 }		},
  { "ins",  "",		1, {       0x31 }		},

  { "jmp",  "f,y",	2, { 0x18, 0x6E }		},
  { "jmp",  "f,x",	1, {       0x6E }		},
  { "jmp",  "h",	1, {       0x7E }		},

  { "lbra", "h",	1, {       0x7E	}		},  /* jmp */

  { "bsr",  "r",	1, {       0x8D } 		},
  { "jsr",  "f,y",	2, { 0x18, 0xAD } 		},
  { "jsr",  "f,x",	1, {       0xAD } 		},
  { "jsr",  "g",	1, {       0x9D } 		},
  { "jsr",  "h",	1, {       0xBD } 		},

  { "ldaa", "#i",	1, {       0x86 } 		},
  { "ldaa", "f,y",	2, { 0x18, 0xA6 } 		},
  { "ldaa", "f,x",	1, {       0xA6 } 		},
  { "ldaa", "g",	1, {       0x96 } 		},
  { "ldaa", "h",	1, {       0xB6 } 		},

  { "ldab", "#i",	1, {       0xC6 } 		},
  { "ldab", "f,y",	2, { 0x18, 0xE6 } 		},
  { "ldab", "f,x",	1, {       0xE6 } 		},
  { "ldab", "g",	1, {       0xD6 } 		},
  { "ldab", "h",	1, {       0xF6 } 		},

  { "clry", "",		4, { 0x18, 0xCE, 0x00, 0x00 } 	},  /* ldy #0 */

  { "ldy",  "#j",	2, { 0x18, 0xCE } 		},
  { "ldy",  "f,y",	2, { 0x18, 0xEE } 		},
  { "ldy",  "f,x",	2, { 0x1A, 0xEE } 		},
  { "ldy",  "g",	2, { 0x18, 0xDE } 		},
  { "ldy",  "h",	2, { 0x18, 0xFE } 		},

  { "clrx", "",		3, {       0xCE, 0x00, 0x00 } 	},  /* ldx #0 */

  { "ldx",  "#j",	1, {       0xCE } 		},
  { "ldx",  "f,y",	2, { 0xCD, 0xEE } 		},
  { "ldx",  "f,x",	1, {       0xEE } 		},
  { "ldx",  "g",	1, {       0xDE } 		},
  { "ldx",  "h",	1, {       0xFE } 		},

  { "ldd",  "#j",	1, {       0xCC } 		},
  { "ldd",  "f,y",	2, { 0x18, 0xEC } 		},
  { "ldd",  "f,x",	1, {       0xEC } 		},
  { "ldd",  "g",	1, {       0xDC } 		},
  { "ldd",  "h",	1, {       0xFC } 		},

  { "lds",  "#j",	1, {       0x8E } 		},
  { "lds",  "f,y",	2, { 0x18, 0xAE } 		},
  { "lds",  "f,x",	1, {       0xAE } 		},
  { "lds",  "g",	1, {       0x9E } 		},
  { "lds",  "h",	1, {       0xBE } 		},

  { "lsld", "",		1, {       0x05 }		},

  { "lsla", "",		1, {       0x48 }		},
  { "lslb", "",		1, {       0x58 }		},
  { "lsl",  "f,y",	2, { 0x18, 0x68 }		},
  { "lsl",  "f,x",	1, {       0x68 }		},
  { "lsl",  "h",	1, {       0x78 }		},

  { "lsrd", "",		1, {       0x04 }		},

  { "lsra", "",		1, {       0x44 }		},
  { "lsrb", "",		1, {       0x54 }		},
  { "lsr",  "f,y",	2, { 0x18, 0x64 }		},
  { "lsr",  "f,x",	1, {       0x64 }		},
  { "lsr",  "h",	1, {       0x74 }		},

  { "mul",  "",		1, {       0x3D }		},

  { "nega", "",		1, {       0x40 }		},
  { "negb", "",		1, {       0x50 }		},
  { "neg",  "f,y",	2, { 0x18, 0x60 }		},
  { "neg",  "f,x",	1, {       0x60 }		},
  { "neg",  "h",	1, {       0x70 }		},

  { "nop",  "",		1, {       0x01 }		},

  { "oraa", "#i",	1, {       0x8A } 		},
  { "oraa", "f,y",	2, { 0x18, 0xAA } 		},
  { "oraa", "f,x",	1, {       0xAA } 		},
  { "oraa", "g",	1, {       0x9A } 		},
  { "oraa", "h",	1, {       0xBA } 		},

  { "orab", "#i",	1, {       0xCA } 		},
  { "orab", "f,y",	2, { 0x18, 0xEA } 		},
  { "orab", "f,x",	1, {       0xEA } 		},
  { "orab", "g",	1, {       0xDA } 		},
  { "orab", "h",	1, {       0xFA } 		},

  { "tdy",  "",		4, {       0x37, 0x36, 0x18, 0x38 } }, /* pshd, puly */
  { "tdx",  "",		3, {       0x37, 0x36,       0x38 } }, /* pshd, pulx */

  { "tyd",  "", 	4, { 0x18, 0x3C, 0x32, 0x33 }	}, /* pshy, puld */
  { "txd",  "", 	3, {       0x3C, 0x32, 0x33 }	}, /* pshx, puld */

  { "tyx",  "",         3, { 0x18, 0x3C,       0x38 }	}, /* pshy, pulx */
  { "txy",  "",		3, {       0x3C, 0x18, 0x38 }	}, /* pshx, puly */


  { "pshy", "",		2, { 0x18, 0x3C }		},
  { "pshx", "",		1, {       0x3C }		},
  { "pshd", "",		2, {       0x37, 0x36 }		},  /* pshb, psha */
  { "pshb", "",		1, {       0x37 }		},
  { "psha", "",		1, {       0x36 }		},

  { "puly", "",		2, { 0x18, 0x38 }		},
  { "pulx", "",		1, {       0x38 }		},
  { "puld", "",		2, {       0x32, 0x33 }		},  /* pula, pulb */
  { "pulb", "",		1, {       0x33 }		},
  { "pula", "",		1, {       0x32 }		},

  { "rold", "",		2, {       0x59, 0x49 }		},  /* rolb, rola */

  { "rola", "",		1, {       0x49 }		},
  { "rolb", "",		1, {       0x59 }		},
  { "rol",  "f,y",	2, { 0x18, 0x69 }		},
  { "rol",  "f,x",	1, {       0x69 }		},
  { "rol",  "h",	1, {       0x79 }		},

  { "rord", "",		2, {       0x46, 0x56 }		},  /* rora, rorb */

  { "rora", "",		1, {       0x46 }		},
  { "rorb", "",		1, {       0x56 }		},
  { "ror",  "f,y",	2, { 0x18, 0x66 }		},
  { "ror",  "f,x",	1, {       0x66 }		},
  { "ror",  "h",	1, {       0x76 }		},

  { "rti",  "",		1, {       0x3B }		},
  { "rts",  "",		1, {       0x39 }		},

  { "sbca", "#i",	1, {       0x82 } 		},
  { "sbca", "f,y",	2, { 0x18, 0xA2 } 		},
  { "sbca", "f,x",	1, {       0xA2 } 		},
  { "sbca", "g",	1, {       0x92 } 		},
  { "sbca", "h",	1, {       0xB2 } 		},

  { "sbcb", "#i",	1, {       0xC2 } 		},
  { "sbcb", "f,y",	2, { 0x18, 0xE2 } 		},
  { "sbcb", "f,x",	1, {       0xE2 } 		},
  { "sbcb", "g",	1, {       0xD2 } 		},
  { "sbcb", "h",	1, {       0xF2 } 		},

  { "sba",  "",		1, {       0x10 }		},
  { "sec",  "",		1, {       0x0D } 		},
  { "sei",  "",		1, {       0x0F } 		},
  { "sev",  "",		1, {       0x0B } 		},

  { "staa", "f,y",	2, { 0x18, 0xA7 } 		},
  { "staa", "f,x",	1, {       0xA7 } 		},
  { "staa", "g",	1, {       0x97 } 		},
  { "staa", "h",	1, {       0xB7 } 		},

  { "stab", "f,y",	2, { 0x18, 0xE7 } 		},
  { "stab", "f,x",	1, {       0xE7 } 		},
  { "stab", "g",	1, {       0xD7 } 		},
  { "stab", "h",	1, {       0xF7 } 		},

  { "stop", "",		1, {       0xCF }		},

  { "sty",  "f,y",	2, { 0x18, 0xEF } 		},
  { "sty",  "f,x",	2, { 0x1A, 0xEF } 		},
  { "sty",  "g",	2, { 0x18, 0xDF } 		},
  { "sty",  "h",	2, { 0x18, 0xFF } 		},

  { "stx",  "f,y",	2, { 0xCD, 0xEF } 		},
  { "stx",  "f,x",	1, {       0xEF } 		},
  { "stx",  "g",	1, {       0xDF } 		},
  { "stx",  "h",	1, {       0xFF } 		},

  { "std",  "f,y",	2, { 0x18, 0xED } 		},
  { "std",  "f,x",	1, {       0xED } 		},
  { "std",  "g",	1, {       0xDD } 		},
  { "std",  "h",	1, {       0xFD } 		},

  { "sts",  "f,y",	2, { 0x18, 0xAF } 		},
  { "sts",  "f,x",	1, {       0xAF } 		},
  { "sts",  "g",	1, {       0x9F } 		},
  { "sts",  "h",	1, {       0xBF } 		},

  { "suba", "#i",	1, {       0x80 } 		},
  { "suba", "f,y",	2, { 0x18, 0xA0 } 		},
  { "suba", "f,x",	1, {       0xA0 } 		},
  { "suba", "g",	1, {       0x90 } 		},
  { "suba", "h",	1, {       0xB0 } 		},

  { "subb", "#i",	1, {       0xC0 } 		},
  { "subb", "f,y",	2, { 0x18, 0xE0 } 		},
  { "subb", "f,x",	1, {       0xE0 } 		},
  { "subb", "g",	1, {       0xD0 } 		},
  { "subb", "h",	1, {       0xF0 } 		},

  { "decd", "",		3, {       0x83, 0x00, 0x01 } 	}, /* subd #1 */

  { "subd", "#j",	1, {       0x83 } 		},
  { "subd", "f,y",	2, { 0x18, 0xA3 } 		},
  { "subd", "f,x",	1, {       0xA3 } 		},
  { "subd", "g",	1, {       0x93 } 		},
  { "subd", "h",	1, {       0xB3 } 		},

  { "swi",  "",		1, {       0x3F }		},
  { "tab",  "",		1, {       0x16 }		},
  { "tap",  "",		1, {       0x06 }		},
  { "tba",  "",		1, {       0x17 }		},
  { "tpa",  "",		1, {       0x07 }		},

  { "test", "",		1, {       0x00 }		},

  { "tsta", "",		1, {       0x4D }		},
  { "tstb", "",		1, {       0x5D }		},
  { "tst",  "f,y",	2, { 0x18, 0x6D }		},
  { "tst",  "f,x",	1, {       0x6D }		},
  { "tst",  "h",	1, {       0x7D }		},

  { "tsy",  "",		2, { 0x18, 0x30 }		},
  { "tsx",  "",		1, {       0x30 }		},
  { "tys",  "",		2, { 0x18, 0x35 }		},
  { "txs",  "",		1, {       0x35 }		},

  { "wai",  "",		1, {       0x3E }		},

  { "xgxy", "",		4, { 	   0x8F, 0x18, 0x8F, 0x8F }}, /* xgdx, xgdy,
								  xgdx */
  { "xgdy", "",		2, { 0x18, 0x8F }		},
  { "xgdx", "",		1, {       0x8F }		},

  { NULL }
};


/* end of hc1x-opcode.h */
