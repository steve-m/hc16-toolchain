/* $Id: hc16.c,v 1.3 2000/06/08 00:12:56 jiang Exp $

   Copyright (C) 2000 Real Time Systems Inc.
      
   This file is part of GNU CC.
            
   GNU CC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option) 
   any later version.
                           
   GNU CC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU General Public License for more details.
                                          
   You should have received a copy of the GNU General Public License
   along with GNU CC; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.                               
                                                         
                                                           
   This file is ported to 68HC16 by:
     Real-Time Systems Inc.
     1212 Austin Avenue, Coquitlam, B.C. Canada. V3H 3X3
     email: querbach@realtime.bc.ca
                                                                                
** hc16.c
**---------------------------------------------------------------------------
**
** 	Subroutines for aux-output.c for Motorola 68HC12 Family.
**   	This file is part of GNU CC.
**
**---------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

#include "flags.h"
#include "rtl.h"
#include "output.h"


/* externals ----------------------------------------------------------------
**
*/
extern FILE *asm_out_file;


/* global variables ---------------------------------------------------------
**
*/
int hc1x_mem_mode;		/* mode of current MEM reference */
char* HC1x_offset = "";         /* constant address offset */


/* handle constant offsets on addresses -------------------------------------
**
**      This routine replaces output_asm_insn() for operands needing
**      a fixed address offset, such as when splitting multi-byte or
**      multi-word operations.  Normally we could just code "0+%1" and
**      "2+%1" in the template, but this loses for the HC12 indirect
**      addressing mode, leaving us with, for example, "0+[12,sp]" which
**      chokes the assembler.  To avoid this we trap the constant and
**      save it for later output by PRINT_OPERAND_ADDRESS().
*/
void output_asm_HC1x(char* oldtemp, rtx* operands)
{
  int pos;

  pos = strcspn(oldtemp, "+");
  if (oldtemp[pos])
  {
    char offset[10] = "";
    char newtemp[80] = "";

    strncat(offset, &oldtemp[pos - 1], 2);      // get "n+" into buffer
    HC1x_offset = offset;                       // save for later

    strncat(newtemp, &oldtemp[0], pos - 1);     // remove "n+" from template
    strcat(newtemp, &oldtemp[pos + 1]);

    output_asm_insn(newtemp, operands);
  }

  else
  {
    output_asm_insn(oldtemp, operands);
  }
}


/* output runtime library function call -------------------------------------
**
*/


/* Output the stack offset of a runtime library routine argument.
   All such arguments are assumed to be in the stack frame.
*/

static void HC1x_code_offset(rtx x)
{
  if (GET_CODE(x) == MEM)
  {
    int offs;
    rtx y = XEXP(x, 0);

    if (REG_P(y))
    {
      switch (REGNO(y))
      {
	case STACK_POINTER_REGNUM:
	case FRAME_POINTER_REGNUM:
	  offs = 0;
	  break;

	default:
	  abort();
      }
    }

    else if (GET_CODE(y) == PLUS)
    {
      rtx l = XEXP(y, 0);
      rtx r = XEXP(y, 1);

      if (REG_P(l) && CONSTANT_P(r))
      {
	switch (REGNO(l))
	{
	  case STACK_POINTER_REGNUM:
	  case FRAME_POINTER_REGNUM:
	    offs =  INTVAL(r);
	    break;

	  default:
	    abort();
	}
      }
      else
      {
	abort();
      }
    }

    else
    {
      abort();
    }

    asm_fprintf(asm_out_file, "%d", offs);
  }

  else
  {
    abort;
  }
}


/* Do general runtime library call.  Emit a call to the handler, followed
   by the frame offsets of any 32-bit results and/or arguments. */

void HC1x_oper(char* sig, char* name, rtx* operands)
{
  /* call handler for this operation */
  {
    char handler[80] = "";

    strcat(handler, "__hc16_");
    strcat(handler, name);

    asm_fprintf(asm_out_file, "\tjsr\t");
    assemble_name(asm_out_file, handler);
    output_asm_insn(" ", operands);
  }

  /* set up result/argument frame offsets for handler */
  {
    char* sigp = sig;
    int arg = 0;
    int dbs = 0;

    while (*sigp)
    {
      if (   strncmp(sigp, "sf", 2) == 0
	  || strncmp(sigp, "si", 2) == 0
	 )
      {
	if (dbs++ == 0)
	  asm_fprintf(asm_out_file, "\tdc.w\t");
	else
	  asm_fprintf(asm_out_file, ",");

	HC1x_code_offset(operands[arg]);
      }

      if (strncmp(sigp, "cc", 2) != 0)
	arg += 1;
      sigp += 2;
    }

    if (dbs)
      asm_fprintf(asm_out_file, "\n");
  }
}


