/* $Id: binutils-2.9.1-hc1x-0.patch,v 1.1 2000/06/27 17:07:43 jiang Exp $
   Copyright (C) 2000 Real Time Systems Inc.
   
   tc-hc1x.c -- Assemble code for the Motorola 68HC11/68HC12/68HC16

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


#include "as.h"
#include "opcode/hc12.h"


/* This array holds the chars that always start a comment.  If the
   pre-processor is disabled, these aren't very useful */

const char comment_chars[] = ";";


/* This array holds the chars that only start a comment at the beginning of
   a line.  If the line seems to have the form '# 123 filename'
   .line and .file directives will appear in the pre-processed output */

/* Note that input_file.c hand checks for '#' at the beginning of the
   first line of the input file.  This is because the compiler outputs
   #NO_APP at the beginning of its output. */

/* Also note that comments started like this one will always work if
   '/' isn't otherwise defined.  */

const char line_comment_chars[] = "*";
const char line_separator_chars[] = "";


/* Chars that can be used to separate mant from exp in floating point nums */

const char EXP_CHARS[] = "eE";


/* Chars that mean this number is a floating point constant */
/* As in 0f12.456 */
/* or    0d1.2345e12 */

const char FLT_CHARS[] = "fFdD";


/* machine-specific short options */

CONST char* md_shortopts = "";


/* machine-specific long options */

struct option md_longopts[] =
{
  { NULL, no_argument, NULL, 0 }
};

size_t md_longopts_size = sizeof (md_longopts);


/* handle machine-specific options */

int
md_parse_option(int c, char* arg)
{
  return 0;
}


/* show usage for machine-specific options */

void
md_show_usage(FILE* stream)
{
}


/* machine-specific pseudo-operation table */

const pseudo_typeS md_pseudo_table[] =
{
  { "db",	cons, 1		},
  { "dw",	cons, 2		},
  { "dl",	cons, 4		},
  { "ds",	s_space, 1	},
  { "public", 	s_globl, 0	},
  {NULL}
};


//#if 0
//---------------------------------------------------------------------------
//
//	Test Routines
//
//


// print bfd section for testing

static void
psec (struct sec* s, int indent)
{
  char pad[41];
  strncpy(pad, "                                      ", indent);
  pad[indent] = 0;

  if (s == NULL)
  {
    fprintf (stdout, "  NULL",                pad);
    return;
  }

  fprintf (stdout, "  %08lX", (long)s);
  fprintf (stdout, "\n%sname:            %s",  pad, s->name ? s->name : "NULL");
  fprintf (stdout, "\n%sflags:           %0lX", pad, (long)(s->flags));
}


// print bfd symbol for testing

static void
pasym (asymbol* a, int indent)
{
  char pad[41];
  strncpy(pad, "                                      ", indent);
  pad[indent] = 0;

  if (a == NULL)
  {
    fprintf (stdout, "  NULL",                pad);
    return;
  }

  fprintf (stdout, "  %08lX", (long)a);
  fprintf (stdout, "\n%sname:            %s",  pad, a->name ? a->name : "NULL");
  fprintf (stdout, "\n%svalue:           %ld", pad, (long)(a->value));
  fprintf (stdout, "\n%sflags:           %0lX", pad, (long)(a->flags));
  fprintf (stdout, "\n%ssec:",		       pad);
    psec(a->section, indent + 2);
}


// print symbol for testing

static void
psym (symbolS* s, int indent)
{
  char pad[41];
  strncpy(pad, "                                      ", indent);
  pad[indent] = 0;

  if (s == NULL)
  {
    fprintf (stdout, "  NULL",                pad);
    return;
  }

  fprintf (stdout, "  %08lX", (long)s);
  fprintf (stdout, "\n%sbsym:",		       pad);
    pasym(s->bsym, indent + 2);
//  fprintf (stdout, "\n%ssy_value:",	       pad);
//    pexp(s->sy_value, indent + 2);

  fprintf (stdout, "\n%swritten:          %d",  pad, (int)(s->written));
  fprintf (stdout, "\n%ssy_resolved:      %d",  pad, (int)(s->sy_resolved));
  fprintf (stdout, "\n%ssy_resolving:     %d",  pad, (int)(s->sy_resolving));
  fprintf (stdout, "\n%ssy_used_in_reloc: %d",  pad, (int)(s->sy_used_in_reloc));
  fprintf (stdout, "\n%ssy_used:          %d",  pad, (int)(s->sy_used));
  fprintf (stdout, "\n%ssy_mri_common:    %d",  pad, (int)(s->sy_mri_common));
//  fprintf (stdout, "\n%sS_GET_NAME:       %s",  pad, S_GET_NAME(s) ? S_GET_NAME(s) : "NULL");
//  fprintf (stdout, "\n%stype:             %s%s",  pad, S_IS_EXTERNAL (s) ?
//						     "EXTERNAL " : "",
//					   segment_name (S_GET_SEGMENT (s)));
}


// print expression for testing

static void
pexp (expressionS *e, int indent)
{
  char pad[41];
  strncpy(pad, "                                      ", indent);
  pad[indent] = 0;

  if (e == NULL)
  {
    fprintf (stdout, "  NULL",                pad);
    return;
  }

  fprintf (stdout, "  %08lX", (long)e);
  fprintf (stdout, "\n%sX_add_symbol:",	       pad);
    psym(e->X_add_symbol, indent + 2);
  fprintf (stdout, "\n%sX_add_symbol:",	       pad);
    psym(e->X_op_symbol, indent + 2);
  fprintf (stdout, "\n%sX_add_number:    %ld", pad, (long)(e->X_add_number));
  fprintf (stdout, "\n%sX_op:            %d",  pad, (int)(e->X_op));
  fprintf (stdout, "\n%sX_unsigned       %d",  pad, (int)(e->X_unsigned));
}


// print frag for testing

pfrag (fragS* f, int indent)
{
  int i;
  char pad[41];
  strncpy(pad, "                                      ", indent);
  pad[indent] = 0;

  if (f == NULL)
  {
    fprintf (stdout, "  NULL",                pad);
    return;
  }

  fprintf (stdout, "  %08lX", (long)f);
  fprintf (stdout, "\n%sfr_address:      %d",  pad, (int)(f->fr_address));
  fprintf (stdout, "\n%sfr_fix:          %d",  pad, (int)(f->fr_fix));
  fprintf (stdout, "\n%sfr_var:          %d",  pad, (int)(f->fr_var));
  fprintf (stdout, "\n%sfr_symbol:", 	       pad);
    psym(f->fr_symbol, indent + 2);
  fprintf (stdout, "\n%sfr_offset:       %d",  pad, (int)(f->fr_offset));
  fprintf (stdout, "\n%sfr_opcode:       %d",  pad, (int)(f->fr_opcode));
  fprintf (stdout, "\n%sfr_type:         %d",  pad, (int)(f->fr_type));
  fprintf (stdout, "\n%sfr_subtype:      %d",  pad, (int)(f->fr_subtype));
  fprintf (stdout, "\n%sfr_line:         %d",  pad, (int)(f->fr_line));
  fprintf (stdout, "\n%sfr_literal:      ",    pad);

  for (i = 0; i < f->fr_fix + f->fr_var; ++i)
  {
    if (i % 8 == 0)
    {
      if (i != 0)
	 fprintf (stdout, "\n%                  ", pad);
      fprintf (stdout, "%04X: ", i & 0xFFFF);
    }
    fprintf (stdout, " %02X", (int)((f->fr_literal[i]) & 0x00FF));
  }
}


// print fixup for testing

static void
pfix (fixS* f, int indent)
{
  char pad[41];
  strncpy(pad, "                                      ", indent);
  pad[indent] = 0;

  if (f == NULL)
  {
    fprintf (stdout, "  NULL",                pad);
    return;
  }

  fprintf (stdout, "  %08lX", (long)f);
  fprintf (stdout, "\n%sfx_pcrel_adjust: %d",  pad, (int)(f->fx_pcrel_adjust));
  fprintf (stdout, "\n%sfx_size:         %d",  pad, (int)(f->fx_size));
  fprintf (stdout, "\n%sfx_pcrel:        %d",  pad, (int)(f->fx_pcrel));
  fprintf (stdout, "\n%sfx_plt:          %d",  pad, (int)(f->fx_plt));
  fprintf (stdout, "\n%sfx_im_disp:      %d",  pad, (int)(f->fx_im_disp));
  fprintf (stdout, "\n%sfx_tcbit:        %d",  pad, (int)(f->fx_tcbit));
  fprintf (stdout, "\n%sfx_done:         %d",  pad, (int)(f->fx_done));
  fprintf (stdout, "\n%sfx_no_overflow:  %d",  pad, (int)(f->fx_no_overflow));
  fprintf (stdout, "\n%sfx_frag:", 	       pad);
    pfrag(f->fx_frag, indent + 2);
  fprintf (stdout, "\n%sfx_where:        %ld", pad, (long)(f->fx_where));
  fprintf (stdout, "\n%sfx_addsy:", 	       pad);
    psym(f->fx_addsy, indent + 2);
  fprintf (stdout, "\n%sfx_subsy:", 	       pad);
    psym(f->fx_subsy, indent + 2);
  fprintf (stdout, "\n%sfx_offset:       %ld", pad, (long)(f->fx_offset));
  fprintf (stdout, "\n%sfx_r_type:       %d",  pad, (int)(f->fx_r_type));
  fprintf (stdout, "\n%sfx_addnumber:    %d",  pad, (long)(f->fx_addnumber));
  fprintf (stdout, "\n%sfx_line:         %d",  pad, (int)(f->fx_line));
}
//#endif //0

static void
parg( char* tag, char* cp )
{
  fprintf (stdout, "%s<%s>", tag, cp);
}


//
//
//	End Test Routines
//
//--------------------------------------------------------------------------
//#endif // 0




/* hash table for opcode lookup */

static struct hash_control *op_hash;


/* initialize module at start of assembly */

void
md_begin ()
{
  struct hc12_opcode* opcode;
  char* prev_name = "";

  // initialize op_code hash table

  op_hash = hash_new ();

  // Enter each unique mnemonic into the opcode hash table.  The name
  // pointers of the duplicates are set to point to the first entry's
  // string.  This is used as a termination condition when searching.

  for (opcode = hc12_opcodes; opcode->name; opcode++)
  {
    if (strcmp (prev_name, opcode->name))
    {
      prev_name = opcode->name;
      hash_insert (op_hash, opcode->name, (char*) opcode);
    }
    else
    {
      opcode->name = prev_name;	     /* point duplicates to first string */
    }
  }
}


//---------------------------------------------------------------------------
//
//	Get an expression from a string, returning zero if success, or
//	a pointer to an error message.
//

void
get_expression
(
  char** str,
  expressionS* exp
)
{
  char *save_in;
  segT seg;

  save_in = input_line_pointer;
  input_line_pointer = *str;

  seg = expression (exp);		// parse the expression
  if (
	  seg != absolute_section
       && seg != undefined_section
       && ! SEG_NORMAL (seg)
     )
  {
    as_bad("bad segment in expression");
  }

  *str = input_line_pointer;
  input_line_pointer = save_in;
}


//---------------------------------------------------------------------------
//
//	Parse an absolute byte from a string.
//

int parse_absbyte
(
  char** ap,
  expressionS** ep
)
{
  // parse expression if not already done

  if ((*ep)->X_op == 0)			// parse expression first time
    get_expression(ap, *ep);

  else             			// otherwise step past it
    while (**ap && **ap != ',')
      (*ap)++;

  // check validity, consume if valid

  if (    (*ep)->X_op == O_constant
       && (*ep)->X_add_number < 256
       && (*ep)->X_add_number >= 0
     )
  {
    ++(*ep);
    return 1;
  }
  return 0;
}

int parse_idx3
(
  char** ap,
  expressionS** ep
)
{
  // parse expression if not already done

  if ((*ep)->X_op == 0)			// parse expression first time
    get_expression(ap, *ep);

  else             			// otherwise step past it
    while (**ap && **ap != ',')
      (*ap)++;

  // check validity, consume if valid

  if (    (*ep)->X_op == O_constant
       && (*ep)->X_add_number <= 8
       && (*ep)->X_add_number >= 1
     )
  {
    ++(*ep);
    return 1;
  }
  return 0;
}

int parse_idx5
(
  char** ap,
  expressionS** ep
)
{
  // parse expression if not already done

  if ((*ep)->X_op == 0)			// parse expression first time
    get_expression(ap, *ep);

  else             			// otherwise step past it
    while (**ap && **ap != ',')
      (*ap)++;

  // check validity, consume if valid

  if (    (*ep)->X_op == O_constant
       && (*ep)->X_add_number <= 15
       && (*ep)->X_add_number >= -16
     )
  {
    ++(*ep);
    return 1;
  }
  return 0;
}

int parse_idx9
(
  char** ap,
  expressionS** ep
)
{
  // parse expression if not already done

  if ((*ep)->X_op == 0)			// parse expression first time
    get_expression(ap, *ep);

  else             			// otherwise step past it
    while (**ap && **ap != ',')
      (*ap)++;

  // check validity, consume if valid

  if (    (*ep)->X_op == O_constant
       && (*ep)->X_add_number <= 255
       && (*ep)->X_add_number >= -256
     )
  {
    ++(*ep);
    return 1;
  }
  return 0;
}


//---------------------------------------------------------------------------
//
//	Parse a relocatable byte from a string.
//

int parse_relative
(
  char** ap,
  expressionS** ep
)
{

  // parse expression if not already done

  if ((*ep)->X_op == 0)			// parse expression first time
    get_expression(ap, *ep);

  else             			// otherwise step past it
    while (**ap && **ap != ',')
      (*ap)++;

  // check validity, consume if valid

  if (    (*ep)->X_op != O_illegal
       && (*ep)->X_op != O_absent
     )
  {
    ++(*ep);
    return 1;
  }
  parg("   ","illegal or absent");
  return 0;
}

//---------------------------------------------------------------------------
//
//	Parse indexed mode, register from input string.
//      input:	idx_post table, input source string
//	output: idx_post pointer, idx_reg pointer

int parse_index
(
  struct idx_post* pidx,
  struct idx_post** its_idx,
  struct idx_reg** its_reg,
  char** app,
  expressionS** exp_pp
)
{
   struct idx_post* pi;
   struct idx_reg* pg;
   int success = 1;
   char* beg_app;
   expressionS* beg_exp_pp;
   char* arg;

   beg_app = *app;
   beg_exp_pp = *exp_pp;

   for (pi = pidx; pi->oprand; pi++)
   {
     *app = beg_app;
     *exp_pp = beg_exp_pp;
     success = 1;

     for (arg = pi->oprand; *arg && **app; arg++)
     {
       switch(*arg)
       {

	 case ',':
	 case 'a':		// register a
	 case 'b':              // register b
	 case 'd':              // register d
	 case '+':
	 case '-':
	 case '[':
	 case ']':
	   if (tolower(*(*app)++) != *arg)
	     success = 0;
	   break;

	 case '3':               // operx3
	   if (!parse_idx3(app, exp_pp))
		success = 0;
	   break;

	 case '5':               // operx5
	   if (!parse_idx5(app, exp_pp))
		success = 0;
	   break;

	 case '9':               // operx9
	   if (!parse_idx9(app, exp_pp))
		success = 0;
	   break;

	 case 'w':               // operx16
	   if (**app == '[')
	     success = 0;
	   else
	     if (!(parse_relative(app, exp_pp)))
		success = 0;

	   break;

	 case 'v':               // register x, y, s, sp
	   pg = idx_regs;
	   for ( ; pg->reg != NULL; pg++)
	   {
	      success = 1;
	      switch(*pg->reg)
	      {
		case 'x':
		case 'y':
		case 's':
		  if (tolower(**app) != *pg->reg)
		  {
		    success = 0;
		  }
		  else
		  {
		    (*app)++;
		    if(*pg->reg == 's' && tolower(**app) == 'p')
		       (*app)++;
		  }
		  break;
		case 'p':
		  success = 0;
		  break;
		default:
		 as_bad("illegal character '%c' for register '%s',parse v", **app, pg->reg);
		 success = 0;
		 break;
	      }
	      if (success)
		break;

	   }
	   break;
	 case 'z':               // register x, y, s, sp, p, pc
	   pg = idx_regs;
	   for ( ; pg->reg != NULL; pg++)
	   {
	      success = 1;
	      switch(*pg->reg)
	      {
		case 'x':
		case 'y':
		case 's':
		case 'p':
		  if (tolower(**app) != *pg->reg)
		  {
		    success = 0;
		  }
		  else
		  {
		    (*app)++;
		    if(    (*pg->reg == 's' && tolower(**app) == 'p')
			|| (*pg->reg == 'p' && tolower(**app) == 'c')
		      )
		       (*app)++;
		  }
		  break;
		default:
		 as_bad("illegal character '%c' for register '%s',parse z", **app, pg->reg);
		 success = 0;
		 break;
	      }
	      if (success)
	       break;

	   }
	   break;

	 default:
	  as_bad("illegal character '%c' in operand '%s',parse idx", *arg, pi->oprand);
	  success = 0;
	  break;
       }
       if (!success)			// bad operands, try next opcode
       {
	  break;
       }
     }
     if (*arg)				// ran out of input arguments?
     {
       success = 0;
     }
     if (success)
     {
       *its_idx = pi;			// remember index table
       *its_reg = pg;          	        // remember register table
       break;
     }
   }
   return success;
}

// parse register a,b,ccr,d,x,y,s,sp
int parse_regs
(
  char** app,
  int*  eb
)
{
   int i, success;
   char c;

   success = 1;
   for (i = 0; **app && i < 3; (*app)++, i++)
   {
      c = **app;
      switch (c)
      {
	case 'a':
	  if ( i == 1)
	    success = 0;
	  *eb = 0;
	  break;
	case 'b':
	  if ( i == 1)
	    success = 0;
	  *eb = 1;
	  break;
	case 'c':
	  if ( i == 1)
	    success = 0;
	  if ((i == 2 && (*app)[1] == 'c' && (*app)[2] == 'r')
	   || (i == 0 && (*app)[1] == 'c' && (*app)[2] == 'r'))
	  {
	    (*app) += 2;
	  }
	  *eb = 2;
	  break;
	case 'd':
	  if ( i == 1)
	    success = 0;
	  *eb = 4;
	  break;
	case 'x':
	  if ( i == 1)
	    success = 0;
	  *eb = 5;
	  break;
	case 'y':
	  if ( i == 1)
	    success = 0;
	  *eb = 6;
	  break;
	case 's':
	  if ( i == 1)
	    success = 0;
	  *eb = 7;
	  if ((*app)[1] == 'p')
	  {
	    (*app)++;
	  }
	  break;
	default:
	  as_bad("illegal register '%c'", **app);
	  success = 0;
	  break;
      }
   }

   if (**app)
     success = 0;

   return success;
}

//---------------------------------------------------------------------------
//
//   Assemble one source line.  The scrubber has dealt with all labels,
//   normal pseudo-ops, and has removed all whitespace except one space
//   character between the opcode and the first operand.
//
//   After parsing, emit code and set fixups for later resolution.
//

void
md_assemble
(
  char* line
)
{
  char* lp;   			// line parsing position
  struct hc12_opcode* opcode;	// opcode table entry
  struct idx_post* index;
  struct idx_reg*  reg;
  struct idx_post* index2;
  struct idx_reg*  reg2;
  char* name;			// name of opcode
  char* arg;			// argument pattern pointer
  expressionS expr_tbl[3];	// expressions parsed
  expressionS* exp_p;		// pointer to latest expression
  char* fp;			// output frag pointer
  int win;			// good opcode and operand
  int i, eb, e;
  int byte, in_squote;
  char oprand_buf[300];
  char c;
  char swappedletter;

  // find end of opcode, make string of it
  for (lp = line; *lp && *lp != ' '; ++lp)
    ;

  if (*lp)
    *lp++ = 0;

  i = 0;
  in_squote = 0;
  do		// token space
  {
    if (*lp == '\'')
      in_squote = !in_squote;

    if(*lp != ' ' || in_squote)
    {
      oprand_buf[i] = *lp;
      if (i < 300 - 1)
	++i;
    }
  }while(*lp++);

  // look up first instance of opcode in opcode table

  if ((opcode = (struct hc12_opcode*) hash_find (op_hash, line)) == NULL)
  {
    as_bad ("Unknown opcode '%s'", line);
    return;
  }

  // for each instance of opcode in table, try to match arguments

  memset ((char*)expr_tbl, 0, sizeof(expr_tbl));
  i = opcode->len;

  for (name = opcode->name; name == opcode->name; opcode++)
  {
    char* arg;			// argument specifier in syntax
    char* ap = oprand_buf;	// argument pointer in input line
    exp_p = expr_tbl;		// current input expression
    win = 1;			// be optomistic about this alternative

    for (arg = opcode->args; *arg && *ap; ++arg)
    {
      switch (*arg)
      {
	case '#':			// require literal match
	case ',':
	  if (tolower(*ap++) != *arg)
	    win = 0;
	  break;

	case 'g':			// 1-byte direct-page address
	case 'p':			// trap
	  if (!parse_absbyte(&ap, &exp_p))
	    win = 0;
	  break;

	case 'i':			// 1-byte immediate operand
	case 'h':			// 2-byte extended address
	case 'j':			// 2-byte immediate operand
	case 'r':			// 1-byte pc-relative offset
	  if (!parse_relative(&ap, &exp_p))
	    win = 0;
	  break;
	case 'e':			// exchange
	  eb = 0;
	  ap = strtok(oprand_buf, ",");
	  if (!parse_regs(&ap, &e))
	  {
	    win = 0;
	    break;
	  }
	  eb = e << 4;
	  ap = strtok(NULL, "\0");
	  if (!parse_regs(&ap, &e))
	  {
	    win = 0;
	    break;
	  }
	  eb += (0x80 + e);
	  break;
	case 'l':			// loop
	  eb = 0;
	  ap = strtok(oprand_buf, ",");
	  if (!parse_regs(&ap, &eb))
	  {
	    win = 0;
	    break;
	  }
	  i = opcode->len;
	  eb += opcode->code[i];

	  ap = strtok(NULL, "\0");
	  if (!parse_relative(&ap, &exp_p))
	    win = 0;
	  break;
	case 't':			// transfer
	  eb = 0;
	  ap = strtok(oprand_buf, ",");

	  if ( !parse_regs(&ap, &e))
	  {
	    win = 0;
	    break;
	  }
	  eb = e << 4;
	  ap = strtok(NULL, "\0");
	  if ( !parse_regs(&ap, &e))
	  {
	    win = 0;
	    break;
	  }
	  eb +=  e;

	  if (  (eb >= 0x03 && eb < 0x10)
	     || (eb >= 0x13 && eb < 0x20)
	     || (eb >= 0x23 && eb < 0x40))
	     win = 0;
	  break;

	case 's':			// sign extend
	  eb = 0;

	  ap = strtok(oprand_buf, ",");
	  if ( !parse_regs(&ap, &e))
	  {
	    win = 0;
	    break;
	  }
	  eb = e << 4;
	  ap = strtok(NULL, "\0");
	  if ( !parse_regs(&ap, &e))
	  {
	    win = 0;
	    break;
	  }
	  eb += e;
	  if (  ( eb < 0x04)
	     || ( eb > 0x07 && eb < 0x14)
	     || ( eb > 0x17 && eb < 0x24)
	     || ( eb > 0x27))
	     win = 0;
	  break;

	case 'q':			// long pc-relative offset
	  if (!parse_relative(&ap, &exp_p))
	    win = 0;
	  break;

	case 'u':			// indexed indirect only
	  if (!parse_index(idx_ind, &index, &reg, &ap, &exp_p))
	    win = 0;
	  break;

	case 'v':			// relocate call
	  if (!parse_relative(&ap, &exp_p))
	    win = 0;
	  break;

	case 'x':			// oprx0_xysp only, first in insn
	  if (!parse_index(idx0, &index, &reg, &ap, &exp_p))
	    win = 0;
	  break;

	case 'y':			// oprx0_xysp only, second in insn
	  if (!parse_index(idx0, &index2, &reg2, &ap, &exp_p))
	    win = 0;
	  break;

	case 'w':
	{
	  expressionS* te = exp_p;
	  char* temp = ap;
				// any indexed mode
	  if (!parse_index(idx_ind, &index, &reg, &ap, &exp_p))
	  {
	     ap = temp;			// argument pointer in input line
	     exp_p = te;		// current input expression

	     if (!parse_index(idx0, &index, &reg, &ap, &exp_p))
	     {
		ap = temp;		// argument pointer in input line
		exp_p = te;	// current input expression
		if (!parse_index(idx16, &index, &reg, &ap, &exp_p))
		  win = 0;
	     }
	  }
	  break;
	}
	case 'z':			// indexed mode exclude indirect
	{
	  expressionS* te = exp_p;
	  char* temp = ap;

	  if (!parse_index(idx0, &index, &reg, &ap, &exp_p))
	  {
	     ap = temp;			// argument pointer in input line
	     exp_p = te;		// current input expression
	     if (!parse_index(idx16, &index, &reg, &ap, &exp_p))
		win = 0;
	  }
	}
	  break;

	default:
	  as_fatal("illegal character '%c' in insn '%s'", *arg, name);
	  win = 0;
	  break;
      }
      if (!win)			// bad operands, try next opcode
	break;
    }
    if (*arg || *ap)		// ran out of input arguments?  fixme
      win = 0;

    if (win)			// found opcode and operand
      break;
  }

  if (!win)
  {
    as_bad ("bad or missing operand");
    return;
  }

  // good instruction, emit opcode bytes

  fp = frag_more (opcode->len);
  for (i = 0; i < opcode->len; ++i)
    md_number_to_chars(fp + i, opcode->code[i], 1);

  // emit operand(s)

  exp_p = expr_tbl;

  for (arg = opcode->args; *arg; ++arg)
  {
    fixS* fixP;
    c = *arg;

    if(opcode->swap)		// swap xb and hhll for movb and movw
    {
      switch (c)
      {
	case 'h':
	case 'i':
	case 'j':
	  swappedletter = c;
	  c = 'x';
	  exp_p = &expr_tbl[1];
	  break;
	case 'x':
	  c = swappedletter;
	  exp_p = &expr_tbl[0];
	  break;
      }
    }
    switch (c)
    {
      case 'g':			// 1-byte direct-page address
	fp = frag_more(1);      // get memory for output
	md_number_to_chars(fp, exp_p->X_add_number, 1);// put const to output
	exp_p++;
	break;

      case 'i':			// 1-byte immediate operand
	fp = frag_more(1);
	// put relocation to output
	fix_new_exp( frag_now,			// fragment
		     fp - frag_now->fr_literal,	// where in fragment
		     1,				// size in bytes
		     exp_p++,			// expression to fix
		     0,				// pc-relative?
		     BFD_RELOC_8 );		// relocation type code
	break;

      case 'h':			// 2-byte extended address
      case 'j':			// 2-byte immediate operand
	fp = frag_more(2);

	fix_new_exp( frag_now,			// fragment
		     fp - frag_now->fr_literal,	// where in fragment
		     2,				// size in bytes
		     exp_p++,			// expression to fix
		     0,				// pc-relative?
		     BFD_RELOC_16 );		// relocation type code

	break;
      case 'l':
	fp = frag_more(2);

	md_number_to_chars(fp, eb, 1);
	fix_new_exp( frag_now,			// fragment
		     fp - frag_now->fr_literal + 1,	// where in fragment
		     1,				// size in bytes
		     exp_p++,			// expression to fix
		     1,				// pc-relative?
		     BFD_RELOC_9_PCREL );	// relocation type code

	break;
      case 'r':			// 1-byte pc-relative offset
	fp = frag_more(1);
	fix_new_exp (frag_now,			// fragment
		     fp - frag_now->fr_literal,	// where in fragment
		     1,				// size in bytes
		     exp_p++,			// expression to fix
		     1,				// pc-relative?
		     BFD_RELOC_8_PCREL );	// relocation type code
	break;

      case 'p':                 // trap
	fp = frag_more(1);      // get memory for output

	if (exp_p->X_add_number < 0x30 || exp_p->X_add_number  > 0xFF
	|| (exp_p->X_add_number > 0x39 && exp_p->X_add_number  < 0x40))
	  as_bad ("Address is out of range.");

	md_number_to_chars(fp, exp_p->X_add_number, 1);// put const to output
	exp_p++;
	break;

      case 'q':			// 2-byte pc-relative offset
	fp = frag_more(2);
	fix_new_exp (frag_now,			// fragment
		     fp - frag_now->fr_literal,	// where in fragment
		     2,				// size in bytes
		     exp_p++,			// expression to fix
		     1,				// pc-relative?
		     BFD_RELOC_16_PCREL );	// relocation type code
	break;

      case 't':			// transfer, exchange, sign-extend
      case 'e':
      case 's':
	fp = frag_more(1);
	md_number_to_chars(fp, eb, 1);

	break;

      case 'x':			// oprx0_xysp
	fp = frag_more(1);
	switch (index->common)
	{
	  case 0x20:                // increment offset
	  case 0x30:
	    byte = index->common + (reg->code * index->rr)
				 + exp_p->X_add_number - 1;
	    exp_p++;
	    break;

	  case 0x28:                // decrement offset
	  case 0x38:
	    byte = index->common + (reg->code * index->rr)
				 + ((exp_p->X_add_number * (-1)) & 0x07);
	    exp_p++;
	    break;

	  case 0x00:                // 5 bit offset
	    byte = index->common + (reg->code * index->rr)
				 + (exp_p->X_add_number & 0x1F);
	    exp_p++;
	    break;

	  case 0xE4:                // accumulator offset
	  case 0xE5:
	  case 0xE6:
	    byte = index->common + (reg->code * index->rr);
	    break;
	}
	md_number_to_chars(fp, byte, 1);
	break;

      case 'y':			// oprx0_xysp
	fp = frag_more(1);
	switch (index2->common)
	{
	  case 0x20:                // increment offset
	  case 0x30:
	    byte = index2->common + (reg2->code * index2->rr)
				  + exp_p->X_add_number - 1;
	    exp_p++;
	    break;

	  case 0x28:                // decrement offset
	  case 0x38:
	    byte = index2->common + (reg2->code * index2->rr)
				  + ((exp_p->X_add_number * (-1)) & 0x07);
	    exp_p++;
	    break;

	  case 0x00:                // 5 bit offset
	    byte = index2->common + (reg2->code * index2->rr)
				  + (exp_p->X_add_number & 0x1F);
	    exp_p++;
	    break;

	  case 0xE4:                // accumulator offset
	  case 0xE5:
	  case 0xE6:
	    byte = index2->common + (reg2->code * index2->rr);
	    break;
	}
	md_number_to_chars(fp, byte, 1);
	break;

      case 'u':			// indirect indexed mode
	fp = frag_more(1);
	switch (index->common)
	{
	  case 0xE7:            // indirect d reg offset
	    byte = index->common + (reg->code * index->rr);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    break;

	  case 0xE3:            // 16 bit indirect indexed
	    byte = index->common + (reg->code * index->rr);
	    md_number_to_chars(fp, byte, 1);// put const to output

	    fp = frag_more(2);
	    if (reg->code == 3)		// pc-relative
	    {
	      fix_new_exp( frag_now,			// fragment
			   fp - frag_now->fr_literal,	// where in fragment
			   2,				// size in bytes
			   exp_p++,			// expression to fix
			   1,				// pc-relative?
			   BFD_RELOC_16_PCREL);		// relocation type code
	      break;
	    }
	    else
	    {				// normal
	      fix_new_exp( frag_now,			// fragment
			   fp - frag_now->fr_literal,	// where in fragment
			   2,				// size in bytes
			   exp_p++,			// expression to fix
			   0,				// pc-relative?
			   BFD_RELOC_16 );		// relocation type code
	      break;
	    }
	}
	break;

      case 'v':
	fp = frag_more(3);

	fix_new_exp( frag_now,			// fragment
		     fp - frag_now->fr_literal,	// where in fragment
		     2,				// size in bytes
		     exp_p,			// expression to fix
		     0,				// pc-relative?
		     BFD_RELOC_16 );		// relocation type code

	fixP =
	fix_new_exp( frag_now,			// fragment
		     fp - frag_now->fr_literal + 2,	// where in fragment
		     1,				// size in bytes
		     exp_p++,			// expression to fix
		     0,				// pc-relative?
		     BFD_RELOC_HC12 );		// relocation type code
	fixP->fx_no_overflow = 1;	// ignore overflow in file offset
	break;

      case 'w':                 // any indexed mode
	switch (index->common)
	{
	  case 0x20:		// increment offset
	  case 0x30:
	    fp = frag_more(index->len);
	    byte = index->common + (reg->code * index->rr)
				 + (exp_p->X_add_number - 1);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0x28:            // decrement offset
	  case 0x38:
	    fp = frag_more(index->len);
	    byte = index->common + (reg->code * index->rr)
				 + ((exp_p->X_add_number * (-1)) & 0x07);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0x00:            // 5 bits constant offset
	    fp = frag_more(index->len);
	    byte = index->common + (reg->code * index->rr)
				 + (exp_p->X_add_number & 0x1F);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0xE4:            // accumulator offset
	  case 0xE5:
	  case 0xE6:
	  case 0xE7:            // indirect d reg offset
	    fp = frag_more(index->len);
	    byte = index->common + (reg->code * index->rr);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    break;

	  case 0xE0:            // 9 bit const offset
	    fp = frag_more(1);
	    byte = index->common + (reg->code * index->rr)
				 + ((exp_p->X_add_number >> 8) & 0x1);
	    md_number_to_chars(fp, byte, 1);// put const to output

	    fp = frag_more(1);

	    byte = exp_p->X_add_number;

	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0xE2:            // 16 bit const
	  case 0xE3:            // 16 bit indirect indexed
	    fp = frag_more(1);
	    byte = index->common + (reg->code * index->rr);
	    md_number_to_chars(fp, byte, 1);// put const to output

	    fp = frag_more(2);
	    if (reg->code == 3)		// pc-relative
	    {
	      fix_new_exp( frag_now,			// fragment
			   fp - frag_now->fr_literal,	// where in fragment
			   2,				// size in bytes
			   exp_p++,			// expression to fix
			   1,				// pc-relative?
			   BFD_RELOC_16_PCREL);		// relocation type code
	      break;
	    }
	    else
	    {				// normal
	      fix_new_exp( frag_now,			// fragment
			   fp - frag_now->fr_literal,	// where in fragment
			   2,				// size in bytes
			   exp_p++,			// expression to fix
			   0,				// pc-relative?
			   BFD_RELOC_16 );		// relocation type code
	      break;
	    }
	}
	break;

      case 'z':                 // not indirect indexed mode
	fp = frag_more(1);

	switch (index->common)
	{
	  case 0x20:		// increment offset
	  case 0x30:
	    byte = index->common + (reg->code * index->rr)
				 + exp_p->X_add_number - 1;
	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0x28:            // decrement offset
	  case 0x38:
	    byte = index->common + (reg->code * index->rr)
				 + ((exp_p->X_add_number * (-1)) & 0x07);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0x00:            // 5 bits constant offset
	    byte = index->common + (reg->code * index->rr)
				 + (exp_p->X_add_number & 0x1F);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0xE0:            // 9 bit const offset
	    byte = index->common + (reg->code * index->rr)
				 + ((exp_p->X_add_number >> 8) & 0x1);
	    md_number_to_chars(fp, byte, 1);// put const to output

	    byte = exp_p->X_add_number;
	    fp = frag_more(1);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    exp_p++;
	    break;

	  case 0xE4:            // accumulator offset
	  case 0xE5:
	  case 0xE6:
	    byte = index->common + (reg->code * index->rr);
	    md_number_to_chars(fp, byte, 1);// put const to output
	    break;

	  case 0xE2:            // 16 bit const offset
	    byte = index->common + (reg->code * index->rr);
	    md_number_to_chars(fp, byte, 1);// put const to output

	    fp = frag_more(2);
	    if (reg->code == 3)		// pc-relative
	    {
	      fix_new_exp( frag_now,			// fragment
			   fp - frag_now->fr_literal,	// where in fragment
			   2,				// size in bytes
			   exp_p++,			// expression to fix
			   1,				// pc-relative?
			   BFD_RELOC_16_PCREL);		// relocation type code
	      break;
	    }
	    else
	    {				// normal
	      fix_new_exp( frag_now,			// fragment
			   fp - frag_now->fr_literal,	// where in fragment
			   2,				// size in bytes
			   exp_p++,			// expression to fix
			   0,				// pc-relative?
			   BFD_RELOC_16 );		// relocation type code
	      break;
	    }
	}
	break;

      default:
	break;
    }
  }
}


/* Apply a fixup to the object code.  This is called for all the
   fixups we generated by the call to fix_new_exp, above.  In the call
   above we used a reloc code which was the largest legal reloc code
   plus the operand index.  Here we undo that to recover the operand
   index.  At this point all symbol values should be fully resolved,
   and we attempt to completely resolve the reloc.  If we can not do
   that, we determine the correct reloc code and put it back in the fixup.  */

/* FIXME: This function handles some of the fixups and bfd_install_relocation
   handles the rest.  bfd_install_relocation (or some other bfd function)
   should handle them all.  */

int
md_apply_fix3 (fixP, valueP, seg)
     fixS *fixP;
     valueT *valueP;
     segT seg;
{
  char *where = fixP->fx_frag->fr_literal + fixP->fx_where;
  valueT value;

  /* FIXME FIXME FIXME: The value we are passed in *valuep includes
     the symbol values.  Since we are using BFD_ASSEMBLER, if we are
     doing this relocation the code in write.c is going to call
     bfd_install_relocation, which is also going to use the symbol
     value.  That means that if the reloc is fully resolved we want to
     use *valuep since bfd_install_relocation is not being used.
     However, if the reloc is not fully resolved we do not want to use
     *valuep, and must use fx_offset instead.  However, if the reloc
     is PC relative, we do want to use *valuep since it includes the
     result of md_pcrel_from.  This is confusing.  */

  if (fixP->fx_addsy == (symbolS *) NULL)
    {
      value = *valueP;
      fixP->fx_done = 1;
    }
  else if (fixP->fx_pcrel)
    value = *valueP;
  else
    {
      value = fixP->fx_offset;
      if (fixP->fx_subsy != (symbolS *) NULL)
	{
	  if (S_GET_SEGMENT (fixP->fx_subsy) == absolute_section)
	    value -= S_GET_VALUE (fixP->fx_subsy);
	  else
	    {
	      /* We don't actually support subtracting a symbol.  */
	      as_bad_where (fixP->fx_file, fixP->fx_line,
			    "expression too complex");
	    }
	}
    }

  if ((int) fixP->fx_r_type >= (int) BFD_RELOC_UNUSED)
  {
    as_fatal("fixP->fx_r_type >= BFD_RELOC_UNUSED");
  }
#if 0
    {
      int opindex = (int) fixP->fx_r_type - (int) BFD_RELOC_UNUSED;
      const struct cgen_operand *operand = & CGEN_SYM (operand_table) [opindex];
      const char *errmsg;
      bfd_reloc_code_real_type reloc_type;
      struct cgen_fields fields;
      const struct cgen_insn *insn = (struct cgen_insn *) fixP->tc_fix_data.insn;

      /* If the reloc has been fully resolved finish the operand here.  */
      /* FIXME: This duplicates the capabilities of code in BFD.  */
      if (fixP->fx_done
	  /* FIXME: If partial_inplace isn't set bfd_install_relocation won't
	     finish the job.  Testing for pcrel is a temporary hack.  */
	  || fixP->fx_pcrel)
	{
	  /* This may seem like overkill, and using bfd_install_relocation or
	     some such may be preferable, but this is simple.  */
	  CGEN_FIELDS_BITSIZE (&fields) = CGEN_INSN_BITSIZE (insn);
	  CGEN_SYM (set_operand) (opindex, &value, &fields);
	  errmsg = CGEN_SYM (validate_operand) (opindex, &fields);
	  if (errmsg)
	    as_warn_where (fixP->fx_file, fixP->fx_line, "%s\n", errmsg);
	  CGEN_SYM (insert_operand) (opindex, &fields, where);
	}

      if (fixP->fx_done)
	return 1;

      /* The operand isn't fully resolved.  Determine a BFD reloc value
	 based on the operand information and leave it to
	 bfd_install_relocation.  Note that this doesn't work when
	 partial_inplace == false.  */

      reloc_type = CGEN_SYM (lookup_reloc) (insn, operand, fixP);
      if (reloc_type != BFD_RELOC_NONE)
	{
	  fixP->fx_r_type = reloc_type;
	}
      else
	{
	  as_bad_where (fixP->fx_file, fixP->fx_line,
			"unresolved expression that must be resolved");
	  fixP->fx_done = 1;
	  return 1;
	}
    }
#endif // 0

  else /* if (fixP->fx_done)   || fixP->pcrel ?? */
    {
      /* We're finished with this fixup.  Install it because
	 bfd_install_relocation won't be called to do it.  */
      switch (fixP->fx_r_type)
	{
	case BFD_RELOC_8:
	  md_number_to_chars (where, value, 1);
	  break;
	case BFD_RELOC_16:
	  md_number_to_chars (where, value, 2);
	  break;
	case BFD_RELOC_32:
	  md_number_to_chars (where, value, 4);
	  break;

	case BFD_RELOC_8_PCREL:
	  if ((long)value < -128 || (long)value > 127)
	    as_bad("short branch too far");
	  md_number_to_chars (where, value, 1);
	  break;
	case BFD_RELOC_9_PCREL:
	  if ((long)value < -256 || (long)value > 255)
	    as_bad("short branch too far");
	  // deal with sign bit
	  if((long)value < 0)
	      where[-1] |= 0x10;

	  md_number_to_chars (where, value, 1);
	  break;
	case BFD_RELOC_16_PCREL:
	  md_number_to_chars (where, value, 2);
	  break;
	case BFD_RELOC_32_PCREL:
	  md_number_to_chars (where, value, 4);
	  break;

	case BFD_RELOC_HC12:
	  md_number_to_chars(where, 0, 1);
	  break;

	/* FIXME: later add support for 64 bits.  */
	default:
	  abort ();
	}
    }
#if 0
  else
    {
      /* bfd_install_relocation will be called to finish things up.  */
    }
#endif

  /* Tuck `value' away for use by tc_gen_reloc.
     See the comment describing fx_addnumber in write.h.
     This field is misnamed (or misused :-).  */
  fixP->fx_addnumber = value;

  return 1;
}



/* Translate internal representation of relocation info to BFD target format. */

arelent*
tc_gen_reloc
(
  asection* section,
  fixS* fixP
)
{
  arelent *reloc;
  reloc = (arelent *) bfd_alloc (stdoutput, sizeof (arelent));

  reloc->howto = bfd_reloc_type_lookup (stdoutput, fixP->fx_r_type);
  if (reloc->howto == (reloc_howto_type *) NULL)
  {
    as_bad_where (fixP->fx_file, fixP->fx_line,
		  "internal error: can't export reloc type %d (`%s')",
		  fixP->fx_r_type, bfd_get_reloc_code_name (fixP->fx_r_type));
    return NULL;
  }

  assert (!fixP->fx_pcrel == !reloc->howto->pc_relative);

  reloc->sym_ptr_ptr = &fixP->fx_addsy->bsym;
  reloc->address = fixP->fx_frag->fr_address + fixP->fx_where;
  reloc->addend = fixP->fx_addnumber;

  return reloc;
}



/* unused machine-specific handlers */

int md_short_jump_size = 3;

void
md_create_short_jump
(
  char* ptr,
  addressT from_addr,
  addressT to_addr,
  fragS* frag,
  symbolS* to_symbol
)
{
  as_fatal ("md_create_short_jump() called");
}

int md_long_jump_size = 5;

void
md_create_long_jump
(
  char* ptr,
  addressT from_addr,
  addressT to_addr,
  fragS* frag,
  symbolS* to_symbol
)
{
  as_fatal ("md_create_long_jump() called");
}

void
md_convert_frag
(
  bfd* headers,
  segT seg,
  fragS* fragP
)
{
  printf ("md_convert_frag() called");
  abort();
}

int
md_estimate_size_before_relax
(
  fragS* fragP,
  segT segment_type
)
{
  printf ("md_estimate_size_before_relax() called");
  abort();
}


/* Exactly what point is a PC-relative offset relative to?  On the hc12,
   they're relative to the start of the next instruction.
*/

long
md_pcrel_from
(
  fixS* fixP
)
{
  long pcrel;

  switch (fixP->fx_r_type)
  {
    case BFD_RELOC_8_PCREL:
    case BFD_RELOC_9_PCREL:
     pcrel = fixP->fx_frag->fr_address + fixP->fx_where + 1;
     break;

    case BFD_RELOC_16_PCREL:
     pcrel = fixP->fx_frag->fr_address + fixP->fx_where + 2;
     break;
  }
  return pcrel;
}


/* pad section to desired alignment */

valueT
md_section_align
(
  segT seg,
  valueT size
)
{
  return size;
}


/* write number to output buffer in proper order */

void
md_number_to_chars
(
  char* ptr,
  valueT use,
  int nbytes
)
{
  number_to_chars_bigendian (ptr, use, nbytes);
}


/* try to parse operand for which standard methods failed */

void
md_operand
(
  expressionS* expressionP
)
{
}


/* handle undefined symbol -- can be used to handle register names */

symbolS*
md_undefined_symbol
(
  char* name
)
{
  return NULL;
}


/* output floating point number in our format
**
**	input:	INPUT_LINE_POINTER points to the first character of
**		a floating-point number
**
**		TYPE holds a flag indicating the statement type wanting
**		the number formatted
**
**		LITP points to target buffer for formatted number
**
**		SIZEP points to storage for final size of number, in bytes
**
**	output:	INPUT_LINE_POINTER points to first character after float
**		number
**
**		return error message, or zero if success
*/

/* Equal to MAX_PRECISION in atof-ieee.c */
#define MAX_LITTLENUMS 6

char *
md_atof (type, litP, sizeP)
     char type;
     char *litP;
     int *sizeP;
{
  int prec;
  LITTLENUM_TYPE words[MAX_LITTLENUMS];
  LITTLENUM_TYPE *wordP;
  char *t;

  switch (type)
  {
    case 'f':
    case 'F':
    case 's':
    case 'S':
      prec = 2;
      break;

    case 'd':
    case 'D':
    case 'r':
    case 'R':
      prec = 4;
      break;

    case 'x':
    case 'X':
      prec = 6;
      break;

    case 'p':
    case 'P':
      prec = 6;
      break;

    default:
      *sizeP = 0;
      return "Bad call to MD_ATOF()";
  }

  t = atof_ieee (input_line_pointer, type, words);
  if (t)
    input_line_pointer = t;

  *sizeP = prec * sizeof (LITTLENUM_TYPE);
  for (wordP = words; prec--; )
  {
    md_number_to_chars (litP, (valueT) (*wordP++), sizeof (LITTLENUM_TYPE));
    litP += sizeof (LITTLENUM_TYPE);
  }

  return 0;
}


/* print statistics */

void
hc1x_print_statistics (file)
     FILE *file;
{
  hash_print_statistics (file, "hc12 opcode", op_hash);
}


/* end of tc-hc1x.c */
