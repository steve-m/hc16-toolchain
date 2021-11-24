/* $Id: hc16.h,v 1.19 2015/02/19 20:21:27 querbach Exp $ */
/* Definitions of target machine for GNU compiler.  Motorola 68HC16 version.

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


/*---------------------------------------------------------------------------
**
**	ACTION ON COMPILER ABORT
**
**  The following is an even better abort() that also prints the file
**  and line in the gcc source that called abort().
*/

#if 0
#define abort()								\
(               	        					\
  (									\
    (__INCLUDE_LEVEL__) ? 						\
      printf("\n%s, #include %s, line %d", 				\
	       __BASE_FILE__, __FILE__, __LINE__)			\
    :									\
      printf("\n%s, line %d", __FILE__, __LINE__)			\
  ),									\
  fancy_abort()								\
)
#endif


/*---------------------------------------------------------------------------
**
**      CONTROLLING THE COMPILATION DRIVER, GCC
**
*/

/* A C string constant that tells the GNU CC driver program options to
   pass to CPP.  It can also specify how to translate options you
   give to GNU CC into options for GNU CC to pass to the CPP.
      
   Do not define this macro if it does not need to do anything.         */
         
#define CPP_SPEC                                                        \
  "                                                                     \
    %{mmedium:              -D__MODEL_MEDIUM__       }                  \
    %{!mmedium:             -D__MODEL_SMALL__        }                  \
    %{msmall:               -D__MODEL_SMALL__        }                  \
  "


/* A C string constant that tells the GNU CC driver program options to
   pass to the assembler.  It can also specify how to translate
   options you give to GNU CC into options for GNU CC to pass to the
   assembler.  See the file `sun3.h' for an example of this.

   Do not define this macro if it does not need to do anything.         */

#define ASM_SPEC "-M"


/* Another C string constant used much like `LINK_SPEC'.  The
   difference between the two is that `LIB_SPEC' is used at the end
   of the command given to the linker.
               
   If this macro is not defined, a default is provided that loads the
   standard C library from the usual place.  See `gcc.c'.		*/
                         
#define LIB_SPEC ""


/* Another C string constant used much like `LINK_SPEC'.  The
   difference between the two is that `STARTFILE_SPEC' is used at the
   very beginning of the command given to the linker.
               
   If this macro is not defined, a default is provided that loads the
   standard C startup file from the usual place.  See `gcc.c'.		*/

#define STARTFILE_SPEC ""


/*---------------------------------------------------------------------------
**
**      RUN-TIME TARGET SPECIFICATION
**
*/

/* Define this to be a string constant containing `-D' options to
   define the predefined macros that identify this machine and system.
   These macros will be predefined unless the `-ansi' option is
   specified.

   In addition, a parallel set of macros are predefined, whose names
   are made by appending `__' at the beginning and at the end.  These
   `__' macros are permitted by the ANSI standard, so they are
   predefined regardless of whether `-ansi' is specified.

   For example, on the Sun, one can use the following value:

	"-Dmc68000 -Dsun -Dunix"

	The result is to define the macros `__mc68000__', `__sun__' and
	`__unix__' unconditionally, and the macros `mc68000', `sun' and
	`unix' provided `-ansi' is not specified.  			*/

#define CPP_PREDEFINES "-Dmc68hc16 					\
			-DMC68HC16					\
			-Dhc16						\
			-DHC16"

/* This series of macros is to allow compiler command arguments to
   enable or disable the use of optional features of the target
   machine.  For example, one machine description serves both the
   68000 and the 68020; a command argument tells the compiler whether
   it should use 68020-only instructions or not.  This command
   argument works by means of a macro `TARGET_68020' that tests a bit
   in `target_flags'.

   Define a macro `TARGET_FEATURENAME' for each such option.  Its
   definition should test a bit in `target_flags'; for example:

	#define TARGET_68020 (target_flags & 1)

   One place where these macros are used is in the
   condition-expressions of instruction patterns.  Note how
   `TARGET_68020' appears frequently in the 68000 machine description
   file, `m68k.md'.  Another place they are used is in the
   definitions of the other macros in the `MACHINE.h' file. 		*/

#define TARGET_DEFAULT 0


/* This macro defines names of command options to set and clear bits
   in `target_flags'.  Its definition is an initializer with a
   subgrouping for each command option.

   Each subgrouping contains a string constant, that defines the
   option name, and a number, which contains the bits to set in
   `target_flags'.  A negative number says to clear bits instead; the
   negative of the number is which bits to clear.  The actual option
   name is made by appending `-m' to the specified name.

   One of the subgroupings should have a null string.  The number in
   this grouping is the default value for `target_flags'.  Any target
   options act starting with that value.

   Here is an example which defines `-m68000' and `-m68020' with
   opposite meanings, and picks the latter as the default:

	#define TARGET_SWITCHES  \
	{ { "68020", 1},         \
	  { "68000", -1},        \
	  { "", 1}}							*/


#define TARGET_SWITCHES							\
{ 									\
  { "",        TARGET_DEFAULT },					\
  { "small",  -1  	      },					\
  { "medium",  1  	      }						\
}

#define TARGET_MEDIUM (target_flags & 1)

extern int target_flags;


/* This macro is a C statement to print on `stderr' a string
   describing the particular machine description choice.  Every
   machine description should define `TARGET_VERSION'.  For example:

     #ifdef MOTOROLA
     #define TARGET_VERSION \
       fprintf (stderr, " (68k, Motorola syntax)");
     #else
     #define TARGET_VERSION \
       fprintf (stderr, " (68k, MIT syntax)");
     #endif */

#define TARGET_VERSION fprintf (stderr, " (MC68HC16, MRI syntax)");


/* Define this macro if debugging can be performed even without a
   frame pointer.  If this macro is defined, GNU CC will turn on the
   `-fomit-frame-pointer' option whenever `-O' is specified.		*/

/* #define CAN_DEBUG_WITHOUT_FP


/*---------------------------------------------------------------------------
**
**	STORAGE LAYOUT
**
*/

/* Define this macro to have the value 1 if the most significant bit
   in a byte has the lowest number; otherwise define it to have the
   value zero.  This means that bit-field instructions count from the
   most significant bit.  If the machine has no bit-field
   instructions, then this must still be defined, but it doesn't
   matter which value it is defined to.  This macro need not be a
   constant.

   This macro does not affect the way structure fields are packed into
   bytes or words; that is controlled by `BYTES_BIG_ENDIAN'.		*/

#define BITS_BIG_ENDIAN 0


/* Define this macro to have the value 1 if the most significant byte
   in a word has the lowest number.  This macro need not be a
   constant.								*/

#define BYTES_BIG_ENDIAN 1


/* Define this macro to have the value 1 if, in a multiword object,
   the most significant word has the lowest number.  This applies to
   both memory locations and registers; GNU CC fundamentally assumes
   that the order of words in memory is the same as the order in
   registers.  This macro need not be a constant.			*/

#define WORDS_BIG_ENDIAN 1


/* Define this macro to be the number of bits in an addressable
   storage unit (byte); normally 8.					*/

#define BITS_PER_UNIT 8


/* Width in bits of a "word", which is the contents of a machine
   register.  Note that this is not necessarily the width of data
   type "int";  if using 16-bit ints on a 32-bit machine,, this
   would still be 32.  But on a machine with 16-bit registers,
   this would be 16.  							*/

#define BITS_PER_WORD 16


/* Number of storage units in a word.					*/

#define UNITS_PER_WORD 2


/* Width of a pointer, in bits.  You must specify a value no wider
   than the width of `Pmode'.  If it is not equal to the width of
   `Pmode', you must define `POINTERS_EXTEND_UNSIGNED'.			*/

#define POINTER_SIZE 16


/* Normal alignment required for function parameters on the stack, in
   bits.  All stack parameters receive at least this much alignment
   regardless of data type.  On most machines, this is the same as the
   size of an integer.							*/

#define PARM_BOUNDARY 16


/* Define this macro if you wish to preserve a certain alignment for
   the stack pointer.  The definition is a C expression for the
   desired alignment (measured in bits).

   If `PUSH_ROUNDING' is not defined, the stack will always be aligned
   to the specified boundary.  If `PUSH_ROUNDING' is defined and
   specifies a less strict alignment than `STACK_BOUNDARY', the stack
   may be momentarily unaligned while pushing arguments.	        */

#define STACK_BOUNDARY 16


/* Alignment required for a function entry point, in bits.		*/

#define FUNCTION_BOUNDARY 16


/* Biggest alignment that any data type can require on this machine,
   in bits.								*/

#define BIGGEST_ALIGNMENT 16


/* If defined, a C expression to compute the alignment for a static
   variable.  TYPE is the data type, and BASIC-ALIGN is the alignment
   that the object would ordinarily have.  The value of this macro is
   used instead of that alignment to align the object.

   If this macro is not defined, then BASIC-ALIGN is used.

   One use of this macro is to increase alignment of medium-size data
   to make it all fit in fewer cache lines.  Another is to cause
   character arrays to be word-aligned so that `strcpy' calls that
   copy constants to character arrays can be done inline.		*/

/*#define DATA_ALIGNMENT(TYPE, BASIC_ALIGN) 16				*/


/* If defined, a C expression to compute the alignment given to a
   constant that is being placed in memory.  CONSTANT is the constant
   and BASIC-ALIGN is the alignment that the object would ordinarily
   have.  The value of this macro is used instead of that alignment to
   align the object.

   If this macro is not defined, then BASIC-ALIGN is used.

   The typical use of this macro is to increase alignment for string
   constants to be word aligned so that `strcpy' calls that copy
   constants can be done inline.					*/

/*#define CONSTANT_ALIGNMENT(CONSTANT, BASIC_ALIGN) 16			*/ 			


/* Alignment in bits to be given to a structure bit field that
   follows an empty field such as `int : 0;'.

   Note that `PCC_BITFIELD_TYPE_MATTERS' also affects the alignment
   that results from an empty field.					*/

#define EMPTY_FIELD_BOUNDARY 8


/* Number of bits which any structure or union's size must be a
   multiple of.  Each structure or union's size is rounded up to a
   multiple of this.

   If you do not define this macro, the default is the same as
   `BITS_PER_UNIT'.							*/

/* #define STRUCTURE_SIZE_BOUNDARY 8					*/


/* Define this macro to be the value 1 if instructions will fail to
   work if given data not on the nominal alignment.  If instructions
   will merely go slower in that case, define this macro as 0.		*/

#define STRICT_ALIGNMENT 0


/* An integer expression for the size in bits of the largest integer
   machine mode that should actually be used.  All integer machine
   modes of this size or smaller can be used for structures and
   unions with the appropriate sizes.  If this macro is undefined,
   `GET_MODE_BITSIZE (DImode)' is assumed.				*/

#define MAX_FIXED_MODE_SIZE 32


/* GNU CC supports two ways of implementing C++ vtables:  traditional
   or with so-called "thunks".  The flag `-fvtable-thunk' chooses
   between them.  Define this macro to be a C expression for the          
   default value of that flag.  If `DEFAULT_VTABLE_THUNKS' is 0, GNU
   CC uses the traditional implementation by default.  The "thunk"   
   implementation is more efficient (especially if you have provided
   an implementation of `ASM_OUTPUT_MI_THUNK', see *Note Function
   Entry::), but is not binary compatible with code compiled using
   the traditional implementation.  If you are writing a new ports,
   define `DEFAULT_VTABLE_THUNKS' to 1.
                              
   If you do not define this macro, the default for `-fvtable-thunk'
   is 0.                                                                */
                                                                              
#define DEFAULT_VTABLE_THUNKS 1


/*---------------------------------------------------------------------------
**
**	LAYOUT OF SOURCE LANGUAGE DATA TYPES
**
**
**  These macros define the sizes and other characteristics of the
**  standard basic data types used in programs being compiled.  Unlike the
**  macros in the previous section, these apply to specific features of C
**  and related languages, rather than to fundamental aspects of storage
**  layout.
*/

/* A C expression for the size in bits of the type `int' on the
   target machine.  If you don't define this, the default is one word.	*/

#define INT_TYPE_SIZE 16


/* A C expression for the size in bits of the type `short' on the
   target machine.  If you don't define this, the default is half a
   word.  (If this would be less than one storage unit, it is rounded
   up to one unit.) 							*/

#define SHORT_TYPE_SIZE 16


/* A C expression for the size in bits of the type `long' on the
   target machine.  If you don't define this, the default is one word.	*/

#define LONG_TYPE_SIZE 32


/* A C expression for the size in bits of the type `long long' on the
   target machine.  If you don't define this, the default is two
   words.  If you want to support GNU Ada on your machine, the value
   of macro must be at least 64.					*/

#define LONG_LONG_TYPE_SIZE 32


/* A C expression for the size in bits of the type `char' on the
   target machine.  If you don't define this, the default is one
   quarter of a word.  (If this would be less than one storage unit,
   it is rounded up to one unit.) 					*/

#define CHAR_TYPE_SIZE 8


/* A C expression for the size in bits of the type `float' on the
   target machine.  If you don't define this, the default is one word.	*/

#define FLOAT_TYPE_SIZE 32


/* A C expression for the size in bits of the type `double' on the
   target machine.  If you don't define this, the default is two
   words. 								*/

#define DOUBLE_TYPE_SIZE 32


/* A C expression for the size in bits of the type `long double' on
   the target machine.  If you don't define this, the default is two
   words. 								*/

#define LONG_DOUBLE_TYPE_SIZE 32


/* An expression whose value is 1 or 0, according to whether the type
   `char' should be signed or unsigned by default.  The user can
   always override this default with the options `-fsigned-char' and
   `-funsigned-char'.    						*/

#define DEFAULT_SIGNED_CHAR 0


/* A C expression to determine whether to give an `enum' type only as
   many bytes as it takes to represent the range of possible values
   of that type.  A nonzero value means to do that; a zero value
   means all `enum' types should be allocated like `int'.

   If you don't define the macro, the default is 0.			*/

/* #define DEFAULT_SHORT_ENUMS 1					*/


/* A C expression for a string describing the name of the data type
   to use for size values.  The typedef name `size_t' is defined
   using the contents of the string.

   The string can contain more than one keyword.  If so, separate
   them with spaces, and write first any length keyword, then
   `unsigned' if appropriate, and finally `int'.  The string must
   exactly match one of the data type names defined in the function
   `init_decl_processing' in the file `c-decl.c'.  You may not omit
   `int' or change the order--that would cause the compiler to crash
   on startup.

   If you don't define this macro, the default is `"long unsigned
   int"'.								*/

#define SIZE_TYPE "unsigned int"


/* A C expression for a string describing the name of the data type
   to use for the result of subtracting two pointers.  The typedef
   name `ptrdiff_t' is defined using the contents of the string.  See
   `SIZE_TYPE' above for more information.  				*/

#define PTRDIFF_TYPE "int"


/* A C constant expression for the integer value for escape sequence
   `\a'. 								*/

#define TARGET_BELL 	007


/* C constant expressions for the integer values for escape sequences
   `\b', `\t' and `\n'.							*/

#define TARGET_BS   	010
#define TARGET_TAB  	011
#define TARGET_NEWLINE  012


/* C constant expressions for the integer values for escape sequences
   `\v', `\f' and `\r'. 						*/

#define TARGET_VT       013
#define TARGET_FF	014
#define TARGET_CR	015


/*---------------------------------------------------------------------------
**
**	BASIC CHARACTERISTICS OF REGISTERS
**
*/

/* Number of hardware registers known to the compiler.  They receive
   numbers 0 through `FIRST_PSEUDO_REGISTER-1'; thus, the first
   pseudo register's number really is assigned the number
   `FIRST_PSEUDO_REGISTER'.  All registers that the compiler knows
   about must be given numbers, even those that are not normally
   considered general registers. 					*/

#define FIRST_PSEUDO_REGISTER 7


/* An initializer that says which registers are used for fixed
   purposes all throughout the compiled code and are therefore not
   available for general allocation.  These would include the stack
   pointer, the frame pointer (except on machines where that can be
   used as a general register when no frame pointer is needed), the
   program counter on machines where that is considered one of the
   addressable registers, and any other numbered register with a
   standard use.

   This information is expressed as a sequence of numbers, separated
   by commas and surrounded by braces.  The Nth number is 1 if
   register N is fixed, 0 otherwise.

   The table initialized from this macro, and the table initialized by
   the following one, may be overridden at run time either
   automatically, by the actions of the macro
   `CONDITIONAL_REGISTER_USAGE', or by the user with the command
   options `-ffixed-REG', `-fcall-used-REG' and `-fcall-saved-REG'.	*/

#define FIXED_REGISTERS { 0, 0, 0, 0, 1, 1, 1 }


/* 1 for registers not available across function calls.


/* Like `FIXED_REGISTERS' but has 1 for each register that is
   clobbered (in general) by function calls as well as for fixed
   registers.  This macro therefore identifies the registers that are
   not available for general allocation of values that must live
   across function calls.

   These must include the FIXED_REGISTERS and also any
   registers that can be used without being saved.
   The latter must include the registers where values are returned
   and the register where structure-value addresses are passed.
   Aside from that, you can include as many other registers as you like.

   If a register has 0 in `CALL_USED_REGISTERS', the compiler
   automatically saves it on function entry and restores it on
   function exit, if the register is used within the function.		*/

#define CALL_USED_REGISTERS { 1, 1, 1, 1, 1, 1, 1 }


/*---------------------------------------------------------------------------
**
**	ORDER OF ALLOCATION OF REGISTERS
**
*/

/* If defined, an initializer for a vector of integers, containing the
   numbers of hard registers in the order in which GNU CC should
   prefer to use them (from most preferred to least).

   If this macro is not defined, registers are used lowest numbered
   first (all else being equal).

   One use of this macro is on machines where the highest numbered
   registers must always be saved and the save-multiple-registers
   instruction supports only sequences of consecutive registers.  On
   such machines, define `REG_ALLOC_ORDER' to be an initializer that
   lists the highest numbered allocatable register first.		*/

#define REG_ALLOC_ORDER { EREG, DREG, YREG, XREG, ZREG, SREG, APREG }


/*---------------------------------------------------------------------------
**
**	HOW VALUES FIT IN REGISTERS
**
**  This section discusses the macros that describe which kinds of values
**  (specifically, which machine modes) each register can hold, and how many
**  consecutive registers are needed for a given mode.
*/

/* A C expression for the number of consecutive hard registers,
   starting at register number REGNO, required to hold a value of mode
   MODE.  This is ordinarily the length in words of a value of mode MODE
   but can be less for certain modes in special long registers.

   On a machine where all registers are exactly one word, a suitable
   definition of this macro is

	#define HARD_REGNO_NREGS(REGNO, MODE)            \
	   ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1)  \
	    / UNITS_PER_WORD))						*/

#define HARD_REGNO_NREGS(REGNO, MODE)   				\
  ( (GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD )


/* A C expression that is nonzero if it is permissible to store a
   value of mode MODE in hard register number REGNO (or in several
   registers starting with that one).  For a machine where all
   registers are equivalent, a suitable definition is

	#define HARD_REGNO_MODE_OK(REGNO, MODE) 1

   It is not necessary for this macro to check for the numbers of
   fixed registers, because the allocation mechanism considers them
   to be always occupied.

   On some machines, double-precision values must be kept in even/odd
   register pairs.  The way to implement that is to define this macro
   to reject odd register numbers for such modes.

   The minimum requirement for a mode to be OK in a register is that
   the `movMODE' instruction pattern support moves between the
   register and any other hard register for which the mode is OK; and
   that moving a value into the register and back out not alter it.

   Since the same instruction used to move `SImode' will work for all
   narrower integer modes, it is not necessary on any machine for
   `HARD_REGNO_MODE_OK' to distinguish between these modes, provided
   you define patterns `movhi', etc., to take advantage of this.  This
   is useful because of the interaction between `HARD_REGNO_MODE_OK'
   and `MODES_TIEABLE_P'; it is very desirable for all integer modes
   to be tieable.

   Many machines have special registers for floating point arithmetic.
   Often people assume that floating point machine modes are allowed
   only in floating point registers.  This is not true.  Any
   registers that can hold integers can safely *hold* a floating
   point machine mode, whether or not floating arithmetic can be done
   on it in those registers.  Integer move instructions can be used
   to move the values.

   On some machines, though, the converse is true: fixed-point machine
   modes may not go in floating registers.  This is true if the
   floating registers normalize any value stored in them, because
   storing a non-floating value there would garble it.  In this case,
   `HARD_REGNO_MODE_OK' should reject fixed-point machine modes in
   floating registers.  But if the floating registers do not
   automatically normalize, if you can store any bit pattern in one
   and retrieve it unchanged without a trap, then any machine mode
   may go in a floating register, so you can define this macro to say
   so.

   The primary significance of special floating registers is rather
   that they are the registers acceptable in floating point arithmetic
   instructions.  However, this is of no concern to
   `HARD_REGNO_MODE_OK'.  You handle it by writing the proper
   constraints for those instructions.

   On some machines, the floating registers are especially slow to
   access, so that it is better to store a value in a stack frame
   than in such a register if floating point arithmetic is not being
   done.  As long as the floating registers are not in class
   `GENERAL_REGS', they will not be used unless some pattern's
   constraint asks for one. 						*/

#define HARD_REGNO_MODE_OK(REGNO, MODE) 				\
  (                                          				\
       GET_MODE_SIZE((MODE)) == 1 && (REGNO) == DREG			\
    || GET_MODE_SIZE((MODE)) == 2					\
  )


/* A C expression that is nonzero if it is desirable to choose
   register allocation so as to avoid move instructions between a
   value of mode MODE1 and a value of mode MODE2.

   If `HARD_REGNO_MODE_OK (R, MODE1)' and `HARD_REGNO_MODE_OK (R,
   MODE2)' are ever different for any R, then `MODES_TIEABLE_P (MODE1,
   MODE2)' must be zero.						*/

#define MODES_TIEABLE_P(MODE1, MODE2)					\
  (									\
    (MODE1) == (MODE2)							\
  )


/*---------------------------------------------------------------------------
**
**	HANDLING LEAF FUNCTIONS
**
**  On some machines, a leaf function (i.e., one which makes no calls)
**  can run more efficiently if it does not make its own register window.
**  Often this means it is required to receive its arguments in the
**  registers where they are passed by the caller, instead of the registers
**  where they would normally arrive.
**
**  The special treatment for leaf functions generally applies only when
**  other conditions are met; for example, often they may use only those
**  registers for its own variables and temporaries.  We use the term "leaf
**  function" to mean a function that is swuitable for this special
**  handling, so that functions with no calls are not necessarily "leaf
**  functions".
**
**  GNU CC assigns register numbers before it knows whether the function
**  is suitable for leaf function treatment.  So it needs to renumber the
**  registers in order to output a leaf function.  The following macros
**  accomplish this.
**
**  Normally, `FUNCTION_PROLOGUE' and `FUNCTION_EPILOGUE' must treat
**  leaf functions specially.  It can test the C variable `leaf_function'
**  which is nonzero for leaf functions.  (The variable `leaf_function' is
**  defined only if `LEAF_REGISTERS' is defined.)
**/

/* A C initializer for a vector, indexed by hard register number,
   which contains 1 for a register that is allowable in a candidate
   for leaf function treatment.

   If leaf function treatment involves renumbering the registers,
   then the registers marked here should be the ones before
   renumbering--those that GNU CC would ordinarily allocate.  The
   registers which will actually be used in the assembler code, after
   renumbering, should not be marked with 1 in this vector.

   Define this macro only if the target machine offers a way to
   optimize the treatment of leaf functions.				*/

/* #define LEAF_REGISTERS { 1, 1, 0, 0, 0 }				*/
/* extern int leaf_function;						*/


/* A C expression whose value is the register number to which REGNO
   should be renumbered, when a function is treated as a leaf
   function.

   If REGNO is a register number which should not appear in a leaf
   function before renumbering, then the expression should yield -1,
   which will cause the compiler to abort.

   Define this macro only if the target machine offers a way to
   optimize the treatment of leaf functions, and registers need to be
   renumbered to do this.						*/

/* #define LEAF_REG_REMAP(REGNO) (REGNO)				*/



/*---------------------------------------------------------------------------
**
**	REGISTER CLASSES
**
**  On many machines, the numbered registers are not all equivalent.
**  For example, certain registers may not be allowed for indexed
**  addressing; certain registers may not be allowed in some instructions.
**  These machine restrictions are described to the compiler using
**  "register classes".
**
**  You define a number of register classes, giving each one a name and
**  saying which of the registers belong to it.  Then you can specify
**  register classes that are allowed as operands to particular instruction
**  patterns.
**
**  In general, each register will belong to several classes.  In fact,
**  one class must be named `ALL_REGS' and contain all the registers.
**  Another class must be named `NO_REGS' and contain no registers.  Often
**  the union of two classes will be another class; however, this is not
**  required.
**
**  One of the classes must be named `GENERAL_REGS'.  There is nothing
**  terribly special about the name, but the operand constraint letters `r'
**  and `g' specify this class.  If `GENERAL_REGS' is the same as
**  `ALL_REGS', just define it as a macro which expands to `ALL_REGS'.
**  Also, registers outside this class are allocated only when
**  instructions express preferences for them.
**
**  Order the classes so that if class X is contained in class Y then X
**  has a lower class number than Y.
**
**  For any two classes, it is very desirable that there be another
**  class that represents their union.
**
**  The way classes other than `GENERAL_REGS' are specified in operand
**  constraints is through machine-dependent operand constraint letters.
**  You can define such letters to correspond to various classes, then use
**  them in operand constraints.
**
**  You should define a class for the union of two classes whenever some
**  instruction allows both classes.  For example, if an instruction allows
**  either a floating point (coprocessor) register or a general register
**  for a certain operand, you should define a class `FLOAT_OR_GENERAL_REGS'
**  which includes both of them.  Otherwise you will get suboptimal code.
**
**  You must also specify certain redundant information about the
**  register classes: for each class, which classes contain it and which
**  ones are contained in it; for each pair of classes, the largest class
**  contained in their union.
**
**  When a value occupying several consecutive registers is expected in a
**  certain class, all the registers used must belong to that class.
**  Therefore, register classes cannot be used to enforce a requirement for
**  a register pair to start with an even-numbered register.  The way to
**  specify this requirement is with `HARD_REGNO_MODE_OK'.
**
**  Register classes used for input-operands of bitwise-and or shift
**  instructions have a special requirement: each such class must have, for
**  each fixed-point machine mode, a subclass whose registers can transfer
**  that mode to or from memory.  For example, on some machines, the
**  operations for single-byte values (`QImode') are limited to certain
**  registers.  When this is so, each register class that is used in a
**  bitwise-and or shift instruction must have a subclass consisting of
**  registers from which single-byte values can be loaded or stored.  This
**  is so that `PREFERRED_RELOAD_CLASS' can always have a possible value to
**  return.
*/

/* Names for register numbers.						*/
#define EREG  0
#define DREG  1
#define YREG  2
#define XREG  3
#define ZREG  4
#define SREG  5
#define APREG 6


/* An enumeral type that must be defined with all the register class
   names as enumeral values.  `NO_REGS' must be first.  `ALL_REGS'
   must be the last register class, followed by one more enumeral
   value, `LIM_REG_CLASSES', which is not a register class but rather
   tells how many classes there are.

   Each register class has a number, which is the value of casting
   the class name to type `int'.  The number serves as an index in
   many of the tables described below.					*/

enum reg_class
{
  NO_REGS,
  E_REGS,
  D_REGS,
  Y_REGS,
  X_REGS,
  ED_REGS,
  YX_REGS,
  EDYX_REGS,
  PTR_REGS,
  ALL_REGS,
  LIM_REG_CLASSES
};

#define GENERAL_REGS ALL_REGS


/* The number of distinct register classes.				*/

#define N_REG_CLASSES (int) LIM_REG_CLASSES


/* An initializer containing the names of the register classes as C
   string constants.  These names are used in writing some of the
   debugging dumps.							*/

#define REG_CLASS_NAMES		 					\
{									\
  "NO_REGS", 								\
  "E_REGS",								\
  "D_REGS",								\
  "Y_REGS",								\
  "X_REGS",								\
  "ED_REGS",								\
  "YX_REGS",								\
  "EDYX_REGS",								\
  "PTR_REGS",								\
  "ALL_REGS" 								\
}


/* An initializer containing the contents of the register classes, as
   integers which are bit masks.  The Nth integer specifies the
   contents of class N.  The way the integer MASK is interpreted is
   that register R is in the class if `MASK & (1 << R)' is 1.

   When the machine has more than 32 registers, an integer does not
   suffice.  Then the integers are replaced by sub-initializers,
   braced groupings containing several integers.  Each
   sub-initializer must be suitable as an initializer for the type
   `HARD_REG_SET' which is defined in `hard-reg-set.h'.			*/

#define REG_CLASS_CONTENTS			 					\
{											\
  0,											\
									   1 << EREG,	\
							       1 << DREG,		\
						   1 << YREG,				\
				       1 << XREG,					\
							       1 << DREG | 1 << EREG,	\
				       1 << XREG | 1 << YREG,				\
				       1 << XREG | 1 << YREG | 1 << DREG | 1 << EREG,	\
  1 << APREG | 1 << SREG | 1 << ZREG | 1 << XREG | 1 << YREG,			     	\
  1 << APREG | 1 << SREG | 1 << ZREG | 1 << XREG | 1 << YREG | 1 << DREG | 1 << EREG	\
}


/* A C expression whose value is a register class containing hard
   register REGNO.  In general there is more than one such class;
   choose a class which is "minimal", meaning that no smaller class
   also contains the register.  This could be a conditional expression
   or could index an array.     					*/

#define REGNO_REG_CLASS(REGNO)						\
  (									\
    ((REGNO) == EREG) ? E_REGS	  :					\
    ((REGNO) == DREG) ? D_REGS	  :					\
    ((REGNO) == YREG) ? Y_REGS	  :					\
    ((REGNO) == XREG) ? X_REGS	  :					\
    ((REGNO) == ZREG) ? PTR_REGS  :					\
    ((REGNO) == SREG) ? PTR_REGS  :					\
    ((REGNO) == APREG) ? PTR_REGS :					\
    fatal("invalid register number")					\
  )


/* A macro whose definition is the name of the class to which a valid
   base register must belong.  A base register is one used in an
   address which is the register value plus a displacement.		*/

#define BASE_REG_CLASS							\
  (									\
    YX_REGS								\
  )


/* A macro whose definition is the name of the class to which a valid
   index register must belong.  An index register is one used in an
   address where its value is either multiplied by a scale factor or
   added to another register (as well as added to a displacement).	*/

#define INDEX_REG_CLASS NO_REGS


/* A C expression which defines the machine-dependent operand
   constraint letters for register classes.  If CHAR is such a
   letter, the value should be the register class corresponding to
   it.  Otherwise, the value should be `NO_REGS'.  The register
   letter `r', corresponding to class `GENERAL_REGS', will not be
   passed to this macro; you do not need to handle it.			*/

#define REG_CLASS_FROM_LETTER(C)					\
  (									\
    ((C) == 'd') ? D_REGS  :						\
    ((C) == 'e') ? E_REGS  :						\
    ((C) == 'D') ? ED_REGS :						\
    ((C) == 'x') ? X_REGS  :						\
    ((C) == 'y') ? Y_REGS  :						\
    ((C) == 'A') ? YX_REGS :						\
		   NO_REGS						\
  )


/* Macros to check register numbers against specific register classes.  */

/* A C expression which is nonzero if register number NUM is suitable
   for use as a base register in operand addresses.  It may be either
   a suitable hard register or a pseudo register that has been
   allocated such a hard register.

   The macro gives nonzero only if REGNO is a hard reg of the suitable
   class or a pseudo reg currently allocated to a suitable hard reg.
   Since it uses reg_renumber, it is safe only once reg_renumber
   has been allocated, which happens in local-alloc.c.  		*/

#define REGNO_OK_FOR_BASE_P(REGNO)					\
  (									\
      (REGNO) == YREG							\
   || (REGNO) == XREG							\
   || (REGNO) == ZREG							\
   || (REGNO) == SREG							\
   || (REGNO) == APREG							\
   || (unsigned)reg_renumber[REGNO] == YREG				\
   || (unsigned)reg_renumber[REGNO] == XREG				\
   || (unsigned)reg_renumber[REGNO] == ZREG				\
   || (unsigned)reg_renumber[REGNO] == SREG				\
   || (unsigned)reg_renumber[REGNO] == APREG				\
  )


/* A C expression which is nonzero if register number NUM is suitable
   for use as an index register in operand addresses.  It may be
   either a suitable hard register or a pseudo register that has been
   allocated such a hard register.

   The difference between an index register and a base register is
   that the index register may be scaled.  If an address involves the
   sum of two registers, neither one of them scaled, then either one
   may be labeled the "base" and the other the "index"; but whichever
   labeling is used must fit the machine's constraints of which
   registers may serve in each capacity.  The compiler will try both
   labelings, looking for one that is valid, and will reload one or
   both registers only if neither labeling works.

   The macro gives nonzero only if REGNO is a hard reg of the suitable
   class or a pseudo reg currently allocated to a suitable hard reg.
   Since it uses reg_renumber, it is safe only once reg_renumber
   has been allocated, which happens in local-alloc.c.  		*/

#define REGNO_OK_FOR_INDEX_P(REGNO) 0


/* A C expression that places additional restrictions on the register
   class to use when it is necessary to copy value X into a register
   in class CLASS.  The value is a register class; perhaps CLASS, or
   perhaps another, smaller class.  On many machines, the following
   definition is safe:

	#define PREFERRED_RELOAD_CLASS(X,CLASS) CLASS

   Sometimes returning a more restriitive class makes better code.
   For example, on the 68000, when X is an integer constant that is
   in range for a `moveq' instruction, the value of this macro is
   always `DATA_REGS' as long as CLASS includes the data registers.
   Requiring a data register guarantees that a `moveq' will be used.

   If X is a `const_double', by returning `NO_REGS' you can force X
   into a memory constant.  This is useful on certain machines where
   immediate floating values cannot be loaded into certain kinds of
   registers.								*/

#define PREFERRED_RELOAD_CLASS(X,CLASS) (CLASS)


/* Certain machines have the property that some registers cannot be
   copied to some other registers without using memory.  Define this
   macro on those machines to be a C expression that is non-zero if
   objects of mode M in registers of CLASS1 can only be copied to
   registers of class CLASS2 by storing a register of CLASS1 into
   memory and loading that memory location into a register of CLASS2.

   Do not define this macro if its value would always be zero.		*/

/* #define SECONDARY_MEMORY_NEEDED (CLASS1, CLASS2, M)'			*/


/* Normally the compiler avoids choosing registers that have been
   explicitly mentioned in the rtl as spill registers (these
   registers are normally those used to pass parameters and return
   values).  However, some machines have so few registers of certain
   classes that there would not be enough registers to use as spill
   registers if this were done.

   Define `SMALL_REGISTER_CLASSES' on these machines.  When it is
   defined, the compiler allows registers explicitly used in the rtl
   to be used as spill registers but avoids extending the lifetime of
   these registers.

   It is always safe to define this macro, but if you unnecessarily
   define it, you will reduce the amount of optimizations that can be
   performed in some cases.  If you do not define this macro when it
   is required, the compiler will run out of spill registers and
   print a fatal error message.  For most machines, you should not
   define this macro.  							*/

#define SMALL_REGISTER_CLASSES 1


/* A C expression whose value is nonzero if pseudos that have been
   assigned to registers of class CLASS would likely be spilled
   because registers of CLASS are needed for spill registers.

   The default value of this macro returns 1 if CLASS has exactly one
   register and zero otherwise.  On most machines, this default
   should be used.  Only define this macro to some other expression
   if pseudo allocated by `local-alloc.c' end up in memory because
   their hard registers were needed for spill registers.  If this
   macro returns nonzero for those classes, those pseudos will only
   be allocated by `global.c', which knows how to reallocate the
   pseudo to another register.  If there would not be another
   register available for reallocation, you should not change the
   definition of this macro since the only effect of such a
   definition would be to slow down register allocation. 		*/

/* #define CLASS_LIKELY_SPILLED_P(CLASS) 1				*/


/* A C expression for the maximum number of consecutive registers of
   class CLASS needed to hold a value of mode MODE.

   This is closely related to the macro `HARD_REGNO_NREGS'.  In fact,
   the value of the macro `CLASS_MAX_NREGS (CLASS, MODE)' should be
   the maximum value of `HARD_REGNO_NREGS (REGNO, MODE)' for all
   REGNO values in the class CLASS.

   This macro helps control the handling of multiple-word values in
   the reload pass.							*/

#define CLASS_MAX_NREGS(CLASS, MODE)					\
  ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD)


/* A C expression that defines the machine-dependent operand
   constraint letters that specify particular ranges of integer
   values.  If C is one of those letters, the expression should check
   that VALUE, an integer, is in the appropriate range and return 1
   if so, 0 otherwise.  If C is not one of those letters, the value
   should be 0 regardless of VALUE.  The letters I, J, K, L, and M
   are available for this purpose.					*/

#define CONST_OK_FOR_LETTER_P(VALUE, C)             	                \
  (									\
    ((C) == 'I' && ((VALUE) ==    0		     )) ? 1 :		\
    ((C) == 'J' && ((VALUE) ==    1		     )) ? 1 :		\
    ((C) == 'K' && ((VALUE) ==   -1 || (VALUE) ==   1)) ? 1 :		\
							  0		\
  )									\


/* A C expression that defines the machine-dependent operand
   constraint letters that specify particular ranges of
   `const_double' values.

   If C is one of those letters, the expression should check that
   VALUE, an RTX of code `const_double', is in the appropriate range
   and return 1 if so, 0 otherwise.  If C is not one of those
   letters, the value should be 0 regardless of VALUE.

   `const_double' is used for all floating-point constants and for
   `DImode' fixed-point constants.  A given letter can accept either
   or both kinds of values.  It can use `GET_MODE' to distinguish
   between these kinds.							*/

#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C)                          \
  (									\
       (C) == 'G'							\
    && GET_MODE_CLASS (GET_MODE (VALUE)) == MODE_FLOAT			\
    && (VALUE) == CONST0_RTX (GET_MODE (VALUE))				\
  )


/* A C expression that defines the optional machine-dependent
   constraint letters that can be used to segregate specific types of
   operands, usually memory references, for the target machine.
   Normally this macro will not be defined.  If it is required for a
   particular target machine, it should return 1 if VALUE corresponds
   to the operand type represented by the constraint letter C.  If C
   is not defined as an extra constraint, the value returned should
   be 0 regardless of VALUE.

   For example, on the ROMP, load instructions cannot have their
   output in r0 if the memory reference contains a symbolic address.
   Constraint letter `Q' is defined as representing a memory address
   that does *not* contain a symbolic address.  An alternative is
   specified with a `Q' constraint on the input and `r' on the
   output.  The next alternative specifies `m' on the input and a
   register class that does not include r0 on the output.		*/

/* #define EXTRA_CONSTRAINT (VALUE, C)					*/


/*---------------------------------------------------------------------------
**
**	BASIC STACK LAYOUT
**
*/

/* Define this macro if pushing a word onto the stack moves the stack
   pointer to a smaller address.					*/

#define STACK_GROWS_DOWNWARD


/* Define this macro if the addresses of local variable slots are at
   negative offsets from the frame pointer, that is, each additional
   local variable allocated goes at a more negative offset in the
   frame.								*/

/* #define FRAME_GROWS_DOWNWARD						*/


/* Define this macro if successive arguments to a function occupy
   decreasing addresses on the stack.					*/

/* #define ARGS_GROW_DOWNWARD */


/* Offset from the frame pointer to the first local variable slot to
   be allocated.

   If `FRAME_GROWS_DOWNWARD', find the next slot's offset by
   subtracting the first slot's length from `STARTING_FRAME_OFFSET'.
   Otherwise, it is found by adding the length of the first slot to
   the value `STARTING_FRAME_OFFSET'.

   If FRAME_GROWS_DOWNWARD, this is the offset to the END of the
   first local allocated.  Otherwise, it is the offset to the BEGINNING
   of the first local allocated.  					*/

#define STARTING_FRAME_OFFSET (current_function_outgoing_args_size)


/* Offset from the stack pointer register to the first location at
   which outgoing arguments are placed.  If not specified, the
   default value of zero is used.  This is the proper value for most
   machines.

   If `ARGS_GROW_DOWNWARD', this is the offset to the location above
   the first location at which outgoing arguments are placed.		*/

/* #define STACK_POINTER_OFFSET						*/


/* Offset from the argument pointer register to the first argument's
   address.  On some machines it may depend on the data type of the
   function.

   If `ARGS_GROW_DOWNWARD', this is the offset to the location above
   the first argument's address.					*/

#define FIRST_PARM_OFFSET(FNDECL) 0


/* A C expression whose value is RTL representing the address in a
   stack frame where the pointer to the caller's frame is stored.
   Assume that FRAMEADDR is an RTL expression for the address of the
   stack frame itself.

   If you don't define this macro, the default is to return the value
   of FRAMEADDR--that is, the stack frame address is also the address
   of the stack word that points to the previous frame.			*/

/* #define DYNAMIC_CHAIN_ADDRESS (FRAMEADDR)				*/


/* A C expression whose value is RTL representing the value of the
   return address for the frame COUNT steps up from the current frame.
   fRAMEADDR is the frame pointer of the COUNT frame, or the frame
   pointer of the COUNT - 1 frame if `RETURN_ADDR_IN_PREVIOUS_FRAME'
   is defined.								*/

/* #define RETURN_ADDR_RTX (COUNT, FRAMEADDR)				*/


/* Define this if the return address of a particular stack frame is
   accessed from the frame pointer of the previous stack frame.		*/

/* #define RETURN_ADDR_IN_PREVIOUS_FRAME				*/


/*---------------------------------------------------------------------------
**
**	REGISTERS THAT ADDRESS THE STACK FRAME
**
*/

/* The register number of the stack pointer register, which must also
   be a fixed register according to `FIXED_REGISTERS'.  On most
   machines, the hardware determines which register this is.		*/

#define STACK_POINTER_REGNUM SREG


/* The register number of the frame pointer register, which is used to
   access automatic variables in the stack frame.  On some machines,
   the hardware determines which register this is.  On other
   machines, you can choose any register you wish for this purpose.	*/

#define FRAME_POINTER_REGNUM ZREG


/* On some machines the offset between the frame pointer and starting
   offset of the automatic variables is not known until after register
   allocation has been done (for example, because the saved registers
   are between these two locations).  On those machines, define
   `FRAME_POINTER_REGNUM' the number of a special, fixed register to
   be used internally until the offset is known, and define
   `HARD_FRAME_POINTER_REGNUM' to be actual the hard register number
   used for the frame pointer.

   You should define this macro only in the very rare circumstances
   when it is not possible to calculate the offset between the frame
   pointer and the automatic variables until after register
   allocation has been completed.  When this macro is defined, you
   must also indicate in your definition of `ELIMINABLE_REGS' how to
   eliminate `FRAME_POINTER_REGNUM' into either
   `HARD_FRAME_POINTER_REGNUM' or `STACK_POINTER_REGNUM'.

   Do not define this macro if it would be the same as
   `FRAME_POINTER_REGNUM'.						*/

/* #define HARD_FRAME_POINTER_REGNUM					*/


/*  The register number of the arg pointer register, which is used to
   access the function's argument list.  On some machines, this is
   the same as the frame pointer register.  On some machines, the
   hardware determines which register this is.  On other machines,
   you can choose any register you wish for this purpose.  If this is
   not the same register as the frame pointer register, then you must
   mark it as a fixed register according to `FIXED_REGISTERS', or
   arrange to be able to eliminate it.					*/

#define ARG_POINTER_REGNUM APREG


/* Register numbers used for passing a function's static chain
   pointer.  If register windows are used, the register number as
   seen by the called function is `STATIC_CHAIN_INCOMING_REGNUM',
   while the register number as seen by the calling function is
   `STATIC_CHAIN_REGNUM'.  If these registers are the same,
   `STATIC_CHAIN_INCOMING_REGNUM' need not be defined.

   The static chain register need not be a fixed register.

   If the static chain is passed in memory, these macros should not be
   defined; instead, the next two macros should be defined.		*/

/* #define STATIC_CHAIN_REGNUM YREG					*/


/* If the static chain is passed in memory, these macros provide rtx
   giving `mem' expressions that denote where they are stored.
   `STATIC_CHAIN' and `STATIC_CHAIN_INCOMING' give the locations as
   seen by the calling and called functions, respectively.  Often the
   former will be at an offset from the stack pointer and the latter
   at an offset from the frame pointer.

   The variables `stack_pointer_rtx', `frame_pointer_rtx', and
   `arg_pointer_rtx' will have been initialized prior to the use of
   these macros and should be used to refer to those items.

   If the static chain is passed in a register, the two previous
   macros should be defined instead.					*/

/* #define STATIC_CHAIN							*/
/* #define STATIC_CHAIN_INCOMING					*/


/*---------------------------------------------------------------------------
**
**	ELIMINATING FRAME POINTER AND ARG POINTER
**
*/

/* A C expression which is nonzero if a function must have and use a
   frame pointer.  This expression is evaluated  in the reload pass.
   If its value is nonzero the function will have a frame pointer.

   The expression can in principle examine the current function and
   decide according to the facts, but on most machines the constant 0
   or the constant 1 suffices.  Use 0 when the machine allows code to
   be generated with no frame pointer, and doing so saves some time
   or space.  Use 1 when there is no possible advantage to avoiding a
   frame pointer.

   In certain cases, the compiler does not know how to produce valid
   code without a frame pointer.  The compiler recognizes those cases
   and automatically gives the function a frame pointer regardless of
   what `FRAME_POINTER_REQUIRED' says.  You don't need to worry about
   them.

   In a function that does not require a frame pointer, the frame
   pointer register can be allocated for ordinary usage, unless you
   mark it as a fixed register.  See `FIXED_REGISTERS' for more
   information.

   Zero means the frame pointer need not be set up (and parms
   may be accessed via the stack pointer) in functions that seem
   suitable.  This is computed in `reload', in reload1.c.  		*/

#define FRAME_POINTER_REQUIRED 1


/* A C statement to store in the variable DEPTH-VAR the difference
   between the frame pointer and the stack pointer values immediately
   after the function prologue.  The value would be computed from
   information such as the result of `get_frame_size ()' and the
   tables of registers `regs_ever_live' and `call_used_regs'.

   If `ELIMINABLE_REGS' is defined, this macro will be not be used and
   need not be defined.  Otherwise, it must be defined even if
   `FRAME_POINTER_REQUIRED' is defined to always be true; in that
   case, you may set DEPTH-VAR to anything.				*/

#define INITIAL_FRAME_POINTER_OFFSET(DEPTH_VAR)  (DEPTH_VAR) = 0;


/* If defined, this macro specifies a table of register pairs used to
   eliminate unneeded registers that point into the stack frame.  If
   it is not defined, the only elimination attempted by the compiler
   is to replace references to the frame pointer with references to
   the stack pointer.

   The definition of this macro is a list of structure
   initializations, each of which specifies an original and
   replacement register.

   On some machines, the position of the argument pointer is not
   known until the compilation is completed.  In such a case, a
   separate hard register must be used for the argument pointer.
   This register can be eliminated by replacing it with either the
   frame pointer or the argument pointer, depending on whether or not
   the frame pointer has been eliminated.

   In this case, you might specify:
	#define ELIMINABLE_REGS  \
	{{ARG_POINTER_REGNUM, STACK_POINTER_REGNUM}, \
	 {ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM}, \
	 {FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}}

   Note that the elimination of the argument pointer with the stack
   pointer is specified first since that is the preferred elimination.  */

#define ELIMINABLE_REGS							\
{									\
  { STACK_POINTER_REGNUM, FRAME_POINTER_REGNUM }, 			\
  { ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM }				\
}


/* A C expression that returns non-zero if the compiler is allowed to
   try to replace register number FROM-REG with register number
   TO-REG.  This macro need only be defined if `ELIMINABLE_REGS' is
   defined, and will usually be the constant 1, since most of the
   cases preventing register elimination are things that the compiler
   already knows about.  						*/

#define CAN_ELIMINATE(FROM, TO) 1


/* This macro is similar to `INITIAL_FRAME_POINTER_OFFSET'.  It
   specifies the initial difference between the specified pair of
   registers.  This macro must be defined if `ELIMINABLE_REGS' is
   defined.  								*/

#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET)			\
{									\
  if (FROM == ARG_POINTER_REGNUM)					\
    (OFFSET) = 6 + get_frame_size()					\
		 + current_function_outgoing_args_size;			\
  else 									\
    (OFFSET) = 0;							\
}


/*---------------------------------------------------------------------------
**
**	PASSING FUNCTION ARGUMENTS ON THE STACK
**
*/

/* Define this macro if an argument declared in a prototype as an
   integral type smaller than `int' should actually be passed as an
   `int'.  In addition to avoiding errors in certain cases of
   mismatch, it also makes for better code on certain machines.		*/

#define PROMOTE_PROTOTYPES


/* A C expression that is the number of bytes actually pushed onto the
   stack when an instruction attempts to push NPUSHED bytes.

   If the target machine does not have a push instruction, do not
   define this macro.  That directs GNU CC to use an alternate
   strategy: to allocate the entire argument block and then store the
   arguments into it.

   On some machines, the definition

	#define PUSH_ROUNDING(BYTES) (BYTES)

   will suffice.  But on other machines, instructions that appear to
   push one byte actually push two bytes in an attempt to maintain
   alignment.  Then the definition should be

	#define PUSH_ROUNDING(BYTES) (((BYTES) + 1) & ~1)		*/

/* #define PUSH_ROUNDING (BYTES)					*/


/* If defined, the maximum amount of space required for outgoing
   arguments will be computed and placed into the variable
   `current_function_outgoing_args_size'.  No space will be pushed
   onto the stack for each call; instead, the function prologue should
   increase the stack frame size by this amount.

   Defining both `PUSH_ROUNDING' and `ACCUMULATE_OUTGOING_ARGS' is
   not proper.								*/

#define ACCUMULATE_OUTGOING_ARGS


/* A C expression that should indicate the number of bytes of its own
   arguments that a function pops on returning, or 0 if the function
   pops no arguments and the caller must therefore pop them all after
   the function returns.						*/

#define RETURN_POPS_ARGS(FUNDECL, FUNTYPE, SIZE) 0


/*---------------------------------------------------------------------------
**
**	PASSING ARGUMENTS IN REGISTERS
**
*/

/* A C expression that controls whether a function argument is passed
   in a register, and which register.

   The arguments are CUM, which summarizes all the previous
   arguments; MODE, the machine mode of the argument; TYPE, the data
   type of the argument as a tree node or 0 if that is not known
   (which happens for C support library functions); and NAMED, which
   is 1 for an ordinary argument and 0 for nameless arguments that
   correspond to `...' in the called function's prototype.

   The value of the expression should either be a `reg' RTX for the
   hard register in which to pass the argument, or zero to pass the
   argument on the stack.

   For machines like the Vax and 68000, where normally all arguments
   are pushed, zero suffices as a definition.

   The usual way to make the ANSI library `stdarg.h' work on a machine
   where some arguments are usually passed in registers, is to cause
   nameless arguments to be passed on the stack instead.  This is done
   by making `FUNCTION_ARG' return 0 whenever NAMED is 0.

   You may use the macro `MUST_PASS_IN_STACK (MODE, TYPE)' in the
   definition of this macro to determine if this argument is of a
   type that must be passed in the stack.  If `REG_PARM_STACK_SPACE'
   is not defined and `FUNCTION_ARG' returns non-zero for such an
   argument, the compiler will abort.  If `REG_PARM_STACK_SPACE' is
   defined, the argument will be computed in the stack and then
   loaded into a register.						*/

#define FUNCTION_ARG(CUM, MODE, TYPE, NAMED)                            \
  (                                                                     \
       NAMED								\
    && !MUST_PASS_IN_STACK(MODE, TYPE)					\
    && GET_MODE_SIZE(MODE) <= (4 - CUM)					\
    ? gen_rtx(REG, MODE, CUM == 0 ? EREG : DREG)			\
    : 0									\
  )


/* A C expression for the number of words, at the beginning of an
   argument, must be put in registers.  The value must be zero for
   arguments that are passed entirely in registers or that are
   entirely pushed on the stack.

   On some machines, certain arguments must be passed partially in
   registers and partially in memory.  On these machines, typically
   the first N words of arguments are passed in registers, and the
   rest on the stack.  If a multi-word argument (a `double' or a
   structure) crosses that boundary, its first few words must be
   passed in registers and the rest must be pushed.  This macro tells
   the compiler when this occurs, and how many of the words should go
   in registers.

   `FUNCTION_ARG' for these arguments should return the first
   register to be used by the caller for this argument; likewise
   `FUNCTION_INCOMING_ARG', for the called function.			*/

#define FUNCTION_ARG_PARTIAL_NREGS(CUM, MODE, TYPE, NAMED) 0


/* A C expression that indicates when an argument must be passed by
   reference.  If nonzero for an argument, a copy of that argument is
   made in memory and a pointer to the argument is passed instead of
   the argument itself.  The pointer is passed in whatever way is
   appropriate for passing a pointer to that type.

   On machines where `REG_PARM_STACK_SPACE' is not defined, a suitable
   definition of this macro might be
	#define FUNCTION_ARG_PASS_BY_REFERENCE\
	(CUM, MODE, TYPE, NAMED)  \
	  MUST_PASS_IN_STACK (MODE, TYPE)				*/

#define FUNCTION_ARG_PASS_BY_REFERENCE(CUM, MODE, TYPE, NAMED)		\
  MUST_PASS_IN_STACK (MODE, TYPE)


/* If defined, a C expression that indicates when it is the called
   function's responsibility to make a copy of arguments passed by
   invisible reference.  Normally, the caller makes a copy and passes
   the address of the copy to the routine being called.  When
   FUNCTION_ARG_CALLEE_COPIES is defined and is nonzero, the caller
   does not make a copy.  Instead, it passes a pointer to the "live"
   value.  The called function must not modify this value.  If it can
   be determined that the value won't be modified, it need not make a
   copy; otherwise a copy must be made.					*/

/* #define FUNCTION_ARG_CALLEE_COPIES (CUM, MODE, TYPE, NAMED)		*/


/* A C type for declaring a variable that is used as the first
   argument of `FUNCTION_ARG' and other related values.  For some
   target machines, the type `int' suffices and can hold the number
   of bytes of argument so far.

   There is no need to record in `CUMULATIVE_ARGS' anything about the
   arguments that have been passed on the stack.  The compiler has
   other variables to keep track of that.  For target machines on
   which all arguments are passed on the stack, there is no need to
   store anything in `CUMULATIVE_ARGS'; however, the data structure
   must exist and should not be empty, so use `int'.			*/

#define CUMULATIVE_ARGS int


/* A C statement (sans semicolon) for initializing the variable CUM
   for the state at the beginning of the argument list.  The variable
   has type `CUMULATIVE_ARGS'.  The value of FNTYPE is the tree node
   for the data type of the function which will receive the args, or 0
   if the args are to a compiler support library function.  The value
   of INDIRECT is nonzero when processing an indirect call, for
   example a call through a function pointer.  The value of INDIRECT
   is zero for a call to an explicitly named function, a library
   function call, or when `INIT_CUMULATIVE_ARGS' is used to find
   arguments for the function being compiled.

   When processing a call to a compiler support library function,
   LIBNAME identifies which one.  It is a `symbol_ref' rtx which
   contains the name of the function, as a string.  LIBNAME is 0 when
   an ordinary C function call is being processed.  Thus, each time
   this macro is called, either LIBNAME or FNTYPE is nonzero, but
   never both of them at once.						*/

#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT)		\
  (									\
    (CUM) = 0								\
  )


/* A C statement (sans semicolon) to update the summarizer variable
   CUM to advance past an argument in the argument list.  The values
   MODE, TYPE and NAMED describe that argument.  Once this is done,
   the variable CUM is suitable for analyzing the *following*
   argument with `FUNCTION_ARG', etc.

   This macro need not do anything if the argument in question was
   passed on the stack.  The compiler knows how to track the amount
   of stack space used for arguments without any special help.		*/

#define FUNCTION_ARG_ADVANCE(CUM, MODE, TYPE, NAMED)			\
  CUM += GET_MODE_SIZE(MODE)


/* A C expression that is nonzero if REGNO is the number of a hard
   register in which function arguments are sometimes passed.  This
   does *not* include implicit arguments such as the static chain and
   the structure-value address.  On many machines, no registers can be
   used for this purpose since all function arguments are pushed on
   the stack.								*/

#define FUNCTION_ARG_REGNO_P(N) 					\
  (									\
    (N) == EREG || (N) == DREG		 				\
  )



/*---------------------------------------------------------------------------
**
**	HOW SCALAR FUNCTION VALUES ARE RETURNED
**
*/

/* A C expression to create an RTX representing the place where a
   function returns a value of data type VALTYPE.  VALTYPE is a tree
   node representing a data type.  Write `TYPE_MODE (VALTYPE)' to get
   the machine mode used to represent that type.  On many machines,
   only the mode is relevant.  (Actually, on most machines, scalar
   values are returned in the same place regardless of mode).

   If `PROMOTE_FUNCTION_RETURN' is defined, you must apply the same
   promotion rules specified in `PROMOTE_MODE' if VALTYPE is a scalar
   type.

   If the precise function being called is known, FUNC is a tree node
   (`FUNCTION_DECL') for it; otherwise, FUNC is a null pointer.  This
   makes it possible to use a different value-returning convention
   for specific functions when all their calls are known.

   `FUNCTION_VALUE' is not used for return vales with aggregate data
   types, because these are returned in another way.  See
   `STRUCT_VALUE_REGNUM' and related macros, below.			*/

#define FUNCTION_VALUE(VALTYPE, FUNC)  					\
  (									\
    TYPE_MODE (VALTYPE) == QImode || TYPE_MODE (VALTYPE) == HImode	\
      ? gen_rtx (REG, TYPE_MODE (VALTYPE), DREG)			\
      : gen_rtx (REG, TYPE_MODE (VALTYPE), EREG)			\
  )


/* A C expression to create an RTX representing the place where a
   library function returns a value of mode MODE.  If the precise
   function being called is known, FUNC is a tree node
   (`FUNCTION_DECL') for it; otherwise, FUNC is a null pointer.  This
   makes it possible to use a different value-returning convention
   for specific functions when all their calls are known.

   Note that "library function" in this context means a compiler
   support routine, used to perform arithmetic, whose name is known
   specially by the compiler and was not mentioned in the C code being
   compiled.

   The definition of `LIBRARY_VALUE' need not be concerned aggregate
   data types, because none of the library functions returns such
   types.								*/

#define LIBCALL_VALUE(MODE)						\
  (									\
    GET_MODE_SIZE (MODE) <= 2						\
      ? gen_rtx (REG, MODE, DREG)					\
      : gen_rtx (REG, MODE, EREG)					\
  )


/* A C expression that is nonzero if REGNO is the number of a hard
   register in which the values of called function may come back.

   A register whose use for returning values is limited to serving as
   the second of a pair (for a value of type `double', say) need not
   be recognized by this macro.  So for most machines, this definition
   suffices:

	#define FUNCTION_VALUE_REGNO_P(N) ((N) == 0)

   If the machine has register windows, so that the caller and the
   called function use different registers for the return value, this
   macro should recognize only the caller's register numbers.		*/

#define FUNCTION_VALUE_REGNO_P(N) 					\
  (									\
    (N) == EREG	|| (N) == DREG							\
  )


/*---------------------------------------------------------------------------
**
**	HOW LARGE VALUES ARE RETURNED
**
**  When a function value's mode is `BLKmode' (and in some other cases),
**  the value is not returned according to `FUNCTION_VALUE'.  Instead,
**  the caller passes the address of a block of memory in which the
**  value should be stored.  This address is called the "structure value
**  address".
*/

/* A C expression which can inhibit the returning of certain function
   values in registers, based on the type of value.  A nonzero value
   says to return the function value in memory, just as large
   structures are always returned.  Here TYPE will be a C expression
   of type `tree', representing the data type of the value.

   Note that values of mode `BLKmode' must be explicitly handled by
   this macro.  Also, the option `-fpcc-struct-return' takes effect
   regardless of this macro.  On most systems, it is possible to
   leave the macro undefined; this causes a default definition to be
   used, whose value is the constant 1 for `BLKmode' values, and 0
   otherwise.

   Do not use this macro to indicate that structures and unions
   should always be returned in memory.  You should instead use
   `DEFAULT_PCC_STRUCT_RETURN' to indicate this.			*/

/* #define RETURN_IN_MEMORY (TYPE)					*/


/* Define this macro to be 1 if all structure and union return values
   must be in memory.  Since this results in slower code, this should
   be defined only if needed for compatibility with other compilers
   or with an ABI.  If you define this macro to be 0, then the
   conventions used for structure and union return values are decided
   by the `RETURN_IN_MEMORY' macro.

   If not defined, this defaults to the value 1.			*/

#define DEFAULT_PCC_STRUCT_RETURN 0


/* If the structure value address is passed in a register, then
   `STRUCT_VALUE_REGNUM' should be the number of that register.		*/

/* #define STRUCT_VALUE_REGNUM						*/


/* If the structure value address is not passed in a register, define
   `STRUCT_VALUE' as an expression returning an RTX for the place
   where the address is passed.  If it returns 0, the address is
   passed as an "invisible" first argument.				*/

#define STRUCT_VALUE 0


/*---------------------------------------------------------------------------
**
**	FUNCTION ENTRY AND EXIT
**
*/

/* A C compound statement that outputs the assembler code for entry
   to a function.  The prologue is responsible for setting up the
   stack frame, initializing the frame pointer register, saving
   registers that must be saved, and allocating SIZE additional bytes
   of storage for the local variables.  SIZE is an integer.  FILE is
   a stdio stream to which the assembler code should be output.

   The label for the beginning of the function need not be output by
   this macro.  That has already been done when the macro is run.

   To determine which registers to save, the macro can refer to the
   array `regs_ever_live': element R is nonzero if hard register R is
   used anywhere within the function.  This implies the function
   prologue should save register R, provided it is not one of the
   call-used registers.  (`FUNCTION_EPILOGUE' must likewise use
   `regs_ever_live'.)

   On machines that have "register windows", the function entry code
   does not save on the stack the registers that are in the windows,
   even if they are supposed to be preserved by function calls;
   instead it takes appropriate steps to "push" the register stack,
   if any non-call-used registers are used in the function.

   On machines where functions may or may not have frame-pointers, the
   function entry code must vary accordingly; it must set up the frame
   pointer if one is wanted, and not otherwise.  To determine whether
   a frame pointer is in wanted, the macro can refer to the variable
   `frame_pointer_needed'.  The variable's value will be 1 at run
   time in a function that needs a frame pointer.

   The function entry code is responsible for allocating any stack
   space required for the function.  This stack space consists of the
   regions listed below.  In most cases, these regions are allocated
   in the order listed, with the last listed region closest to the
   top of the stack (the lowest address if `STACK_GROWS_DOWNWARD' is
   defined, and the highest address if it is not defined).  You can
   use a different order for a machine if doing so is more convenient
   or required for compatibility reasons.  Except in cases where
   required by standard or by a debugger, there is no reason why the
   stack layout used by GCC need agree with that used by other
   compilers for a machine.

      * A region of `current_function_pretend_args_size' bytes of
	uninitialized space just underneath the first argument
	arriving on the stack.  (This may not be at the very start of
	the allocated stack region if the calling sequence has pushed
	anything else since pushing the stack arguments.  But
	usually, on such machines, nothing else has been pushed yet,
	because the function prologue itself does all the pushing.)
	This region is used on machines where an argument may be
	passed partly in registers and partly in memory, and, in some
	cases to support the features in `varargs.h' and `stdargs.h'.

      * An area of memory used to save certain registers used by the
	function.  The size of this area, which may also include
	space for such things as the return address and pointers to
	previous stack frames, is machine-specific and usually
	depends on which registers have been used in the function.
	Machines with register windows often do not require a save
	area.

      * A region of at least SIZE bytes, possibly rounded up to an
	allocation boundary, to contain the local variables of the
	function.  On some machines, this region and the save area
	may occur in the opposite order, with the save area closer to
	the top of the stack.

      * Optionally, when `ACCUMULATE_OUTGOING_ARGS' is defined, a
	region of `current_function_outgoing_args_size' bytes to be
	used for outgoing argument lists of the function.

   Normally, it is necessary for the macros `FUNCTION_PROLOGUE' and
   `FUNCTION_EPILOGUE' to treat leaf functions specially.  The C
   variable `leaf_function' is nonzero for such a function.		*/

#define FUNCTION_PROLOGUE(STREAM, SIZE)   				\
{									\
  int locs = SIZE + current_function_outgoing_args_size;		\
									\
  fprintf(STREAM, "\tpshm\tz\n");					\
  if (locs)								\
    fprintf(STREAM, "\tais\t#-%d\n", locs);				\
  fprintf(STREAM, "\ttsz\n\n", locs);      				\
}


/* Define this macro as a C expression that is nonzero if the return
   instruction or the function epilogue ignores the value of the stack
   pointer; in other words, if it is safe to delete an instruction to
   adjust the stack pointer before a return from the function.

   Note that this macro's value is relevant only for functions for
   which frame pointers are maintained.  It is never safe to delete a
   final stack adjustment in a function that has no frame pointer,
   and the compiler knows this regardless of `EXIT_IGNORE_STACK'.	*/

#define EXIT_IGNORE_STACK 0


/* A C compound statement that outputs the assembler code for exit
   from a function.  The epilogue is responsible for restoring the
   saved registers and stack pointer to their values when the
   function was called, and returning control to the caller.  This
   macro takes the same arguments as the macro `FUNCTION_PROLOGUE',
   and the registers to restore are determined from `regs_ever_live'
   and `CALL_USED_REGISTERS' in the same way.

   On some machines, there is a single instruction that does all the
   work of returning from the function.  On these machines, give that
   instruction the name `return' and do not define the macro
   `FUNCTION_EPILOGUE' at all.

   Do not define a pattern named `return' if you want the
   `FUNCTION_EPILOGUE' to be used.  If you want the target switches
   to control whether return instructions or epilogues are used,
   define a `return' pattern with a validity condition that tests the
   target switches appropriately.  If the `return' pattern's validity
   condition is false, epilogues will be used.

   On machines where functions may or may not have frame-pointers, the
   function exit code must vary accordingly.  Sometimes the code for
   these two cases is completely different.  To determine whether a
   frame pointer is wanted, the macro can refer to the variable
   `frame_pointer_needed'.  The variable's value will be 1 when
   compiling a function that needs a frame pointer.

   Normally, `FUNCTION_PROLOGUE' and `FUNCTION_EPILOGUE' must treat
   leaf functions specially.  The C variable `leaf_function' is
   nonzero for such a function.

   On some machines, some functions pop their arguments on exit while
   others leave that for the caller to do.  For example, the 68020
   when given `-mrtd' pops arguments in functions that take a fixed
   number of arguments.

   Your definition of the macro `RETURN_POPSSARGS' decides which
   functions pop their own arguments.  `FUNCTION_EPILOGUE' needs to
   know what was decided.  The variable that is called
   `current_function_pops_args' is the number of bytes of its
   arguments that a function should pop.

   The function epilogue should not depend on the current stack pointer!
   It should use the frame pointer only.  This is mandatory because
   of alloca; we also take advantage of it to omit stack adjustments
   before returning.  							*/

#define FUNCTION_EPILOGUE(STREAM, SIZE)					\
{                                                                       \
  int locs = SIZE + current_function_outgoing_args_size;		\
									\
  if (locs)								\
    fprintf (STREAM, "\n\tais\t#+%d\n", locs);				\
  fprintf (STREAM, "\tpulm\tz\n");					\
									\
  fprintf (STREAM, "\trts\n\n");					\
}


/* A C compound statement that outputs the assembler code for a thunk
   function, used to implement C++ virtual function calls with            
   multiple inheritance.  The thunk acts as a wrapper around a
   virtual function, adjusting the implicit object parameter before  
   handing control off to the real function.
                                     
   First, emit code to add the integer DELTA to the location that 
   contains the incoming first argument.  Assume that this argument
   contains a pointer, and is the one used to pass the `this' pointer
   in C++.  This is the incoming argument *before* the function
   prologue, e.g. `%o0' on a sparc.  The addition must preserve the 
   values of all other incoming arguments.
                                                                                                 
   After the addition, emit code to jump to FUNCTION, which is a
   `FUNCTION_DECL'.  This is a direct pure jump, not a call, and does
   not touch the return address.  Hence returning from FUNCTION will
   return to whoever called the current `thunk'.
   
   The effect must be as if FUNCTION had been called directly with
   the adjusted first argument.  This macro is responsible for
   emitting all of the code for a thunk function; `FUNCTION_PROLOGUE'
   and `FUNCTION_EPILOGUE' are not invoked.
                                                                                                                                                                                                     
   The THUNK_FNDECL is redundant.  (DELTA and FUNCTION have already
   been extracted from it.)  It might possibly be useful on some
   targets, but probably not.
   
   If you do not define this macro, the target-independent code in
   the C++ frontend will generate a less efficient heavyweight thunk
   that calls FUNCTION instead of jumping to it.  The generic
   approach does not support varargs.                                   */
                                                                                                                                                                                                                          
#define ASM_OUTPUT_MI_THUNK(STREAM, THUNK_FNDECL, DELTA, FUNCTION)	\
{									\
  char* name =  XSTR (XEXP (DECL_RTL (FUNCTION), 0), 0);		\
									\
  fprintf (STREAM, "\tadde\t#%d\n", DELTA);				\
  fprintf (STREAM, "\tjmp\t");						\
  ASM_OUTPUT_LABELREF (STREAM, name);					\
  fprintf (STREAM, "\n\n");						\
}
                                                                                                                                                                                                                                                                                                            

/*---------------------------------------------------------------------------
**
**	GENERATING CODE FOR POFILING
**
*/

/* A C statement or compound statement to output to FILE some
   assembler code to call the profiling subroutine `mcount'.  Before
   calling, the assembler code must load the address of a counter
   variable into a register where `mcount' expects to find the
   address.  The name of this variable is `LP' followed by the number
   LABELNO, so you would generate the name using `LP%d' in a
   `fprintf'.

   The details of how the address should be passed to `mcount' are
   determined by your operating system environment, not by GNU CC.  To
   figure them out, compile a small program for profiling using the
   system's installed C compiler and look at the assembler code that
   results.								*/

#define FUNCTION_PROFILER(FILE, LABELNO)  				\
  fatal("profiling not implemented");



/*---------------------------------------------------------------------------
**
**	IMPLEMENTING THE VARARGS MACROS
**
*/

/* Define this macro if the location where a function argument is
   passed depends on whether or not it is a named argument.

   This macro controls how the NAMED argument to `FUNCTION_ARG' is
   set for varargs and stdarg functions.  With this macro defined,
   the NAMED argument is always true for named arguments, and false
   for unnamed arguments.  If this is not defined, but
   `SETUP_INCOMING_VARARGS' is defined, then all arguments are
   treated as named.  Otherwise, all named arguments except the last
   are treated as named.						*/

/* #define STRICT_ARGUMENT_NAMING					*/



/*---------------------------------------------------------------------------
**
**	TRAMPOLINES FOR NESTED FUNCTIONS
**
**  A "trampoline" is a small piece of code that is created at run time
**  when the address of a nested function is taken.  It normally resides on
**  the stack, in the stack frame of the containing function.  These macros
**  tell GNU CC how to generate code to allocate and initialize a
**  trampoline.
**
**  The instructions in the trampoline must do two things: load a
**  constant address into the static chain register, and jump to the real
**  address of the nested function.  On CISC machines such as the m68k,
**  this requires two instructions, a move immediate and a jump.  Then the
**  two addresses exist in the trampoline as word-long immediate operands.
**  On RISC machines, it is often necessary to load each address into a
**  register in two parts.  Then pieces of each address form separate
**  immediate operands.
**
**  The code generated to initialize the trampoline must store the
**  variable parts--the static chain value and the function address--into
**  the immediate operands of the instructions.  On a CISC machine, this is
**  simply a matter of copying each address to a memory reference at the
**  proper offset from the start of the trampoline.  On a RISC machine, it
**  may be necessary to take out pieces of the address and store them
**  separately.
*/

/* A C statement to output, on the stream FILE, assembler code for a
   block of data that contains the constant parts of a trampoline.
   This code should not include a label--the label is taken care of
   automatically.							*/

#define TRAMPOLINE_TEMPLATE(FILE)					\
  fatal("trampolines not implemented");


/* A C expression for the size in bytes of the trampoline, as an
   integer.								*/

#define TRAMPOLINE_SIZE 1


/* Emit RTL insns to initialize the variable parts of a trampoline.
   FNADDR is an RTX for the address of the function's pure code.
   CXT is an RTX for the static chain value for the function.  */

/* A C statement to initialize the variable parts of a trampoline.
   ADDR is an RTX for the address of the trampoline; FNADDR is an RTX
   for the address of the nested function; STATIC_CHAIN is an RTX for
   the static chain value that should be passed to the function when
   it is called.							*/

#define INITIALIZE_TRAMPOLINE(TRAMP, FNADDR, CXT)			\
  fatal("trampolines not implemented");


/*---------------------------------------------------------------------------
**
**	IMPLICIT CALLS TO LIBRARY ROUTINES
**
*/

/* Define this macro if GNU CC should generate calls to the System V
   (and ANSI C) library functions `memcpy' and `memset' rather than
   the BSD functions `bcopy' and `bzero'.				*/

#define TARGET_MEM_FUNCTIONS


/*---------------------------------------------------------------------------
**
**	ADDRESSING MODES
**
*/


/* Define these macros if the machine supports the indicated addressing
   mode.								*/

/* #define HAVE_POST_INCREMENT						*/
/* #define HAVE_PRE_INCREMENT						*/
/* #define HAVE_POST_DECREMENT						*/
/* #define HAVE_PRE_DECREMENT						*/


/* A C expression that is 1 if the RTX X is a constant which is a
   valid address.  On most machines, this can be defined as
   `CONSTANT_P (X)', but a few machines are more restrictive in which
   constant addresses are supported.

   `CONSTANT_P' accepts integer-values expressions whose values are
   not explicitly known, such as `symbol_ref', `label_ref', and
   `high' expressions and `const' arithmetic expressions, in addition
   to `const_int' and `const_double' expressions.			*/

#define CONSTANT_ADDRESS_P(X)		   				\
  (   GET_CODE (X) == LABEL_REF 					\
   || GET_CODE (X) == SYMBOL_REF					\
   || GET_CODE (X) == CONST_INT 					\
   || GET_CODE (X) == CONST						\
   || GET_CODE (X) == HIGH						\
  )


/* A number, the maximum number of registers that can appear in a
   valid memory address.  Note that it is up to you to specify a
   value equal to the maximum number that `GO_IF_LEGITIMATE_ADDRESS'
   would ever accept.							*/

#define MAX_REGS_PER_ADDRESS 1


/* A C compound statement with a conditional `goto LABEL;' executed
   if X (an RTX) is a legitimate memory address on the target machine
   for a memory operand of mode MODE.

   It usually pays to define several simpler macros to serve as
   subroutines for this one.  Otherwise it may be too complicated to
   understand.

   This macro must exist in two variants: a strict variant and a
   non-strict one.  The strict variant is used in the reload pass.  It
   must be defined so that any pseudo-register that has not been
   allocated a hard register is considered a memory reference.  In
   contexts where some kind of register is required, a pseudo-register
   with no hard register must be rejected.

   The non-strict variant is used in other passes.  It must be
   defined to accept all pseudo-registers in every context where some
   kind of register is required.

   Compiler source files that want to use the strict variant of this
   macro define the macro `REG_OK_STRICT'.  You should use an `#ifdef
   REG_OK_STRICT' conditional to define the strict variant in that
   case and the non-strict variant otherwise.

   Subroutines to check for acceptable registers for various purposes
   (one for base registers, one for index registers, and so on) are
   typically among the subroutines used to define
   `GO_IF_LEGITIMATE_ADDRESS'.  Then only these subroutine macros
   need have two variants; the higher levels of macros may be the
   same whether strict or not.

   Normally, constant addresses which are the sum of a `symbol_ref'
   and an integer are stored inside a `const' RTX to mark them as
   constant.  Therefore, there is no need to recognize such sums
   specifically as legitimate addresses.  Normally you would simply
   recognize any `const' as legitimate.

   Usually `PRINT_OPERAND_ADDRESS' is not prepared to handle constant
   sums that are not marked with  `const'.  It assumes that a naked
   `plus' indicates indexing.  If so, then you *must* reject such
   naked constant sums as illegitimate addresses, so that none of
   them will be given to `PRINT_OPERAND_ADDRESS'.

   On some machines, whether a symbolic address is legitimate depends
   on the section that the address refers to.  On these machines,
   define the macro `ENCODE_SECTION_INFO' to store the information
   into the `symbol_ref', and then check for it here.  When you see a
   `const', you will have to look inside it to find the `symbol_ref'
   in order to determine the section.

   The best way to modify the name string is by adding text to the
   beginning, with suitable punctuation to prevent any ambiguity.
   Allocate the new name in `saveable_obstack'.  You will have to
   modify `ASM_OUTPUT_LABELREF' to remove and decode the added text
   and output the name accordingly, and define `STRIP_NAME_ENCODING'
   to access the original name string.

   You can check the information stored here into the `symbol_ref' in
   the definitions of the macros `GO_IF_LEGITIMATE_ADDRESS' and
   `PRINT_OPERAND_ADDRESS'.						*/

#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, LABEL)                        \
{                                                                       \
  register rtx Addr = X;                                                \
                                                                        \
  if (CONSTANT_ADDRESS_P(Addr))                                         \
    goto LABEL;                                                         \
                                                                        \
  if (LEGIT_BASE_ADDR(Addr))                                            \
    goto LABEL;                                                         \
									\
  if (LEGIT_BASE_OFFSET_ADDR(Addr))                                     \
    goto LABEL;                                                         \
}                                                                       \


#define LEGIT_BASE_ADDR(Addr)                                           \
  (                                                                     \
       REG_P(Addr)                                                      \
    && REG_OK_FOR_BASE_P(Addr)                                          \
  )


#define LEGIT_INDEX_ADDR(Addr)                                          \
  (                                                                     \
       REG_P(Addr)                                                      \
    && REG_OK_FOR_INDEX_P(Addr)                                         \
  )


#define LEGIT_BASE_OFFSET_ADDR(Addr)                                    \
  (                                                                     \
       GET_CODE(Addr) == PLUS                                           \
    && LEGIT_BASE_ADDR(XEXP(Addr, 0))                                   \
    && CONSTANT_ADDRESS_P(XEXP(Addr, 1))                                \
    && INTVAL(XEXP(Addr, 1)) >= -32768					\
    && INTVAL(XEXP(Addr, 1)) <= 32767					\
  )


#define LEGIT_BASE_SHORT_OFFSET_ADDR(Addr)                              \
  (                                                                     \
       LEGIT_BASE_OFFSET_ADDR(Addr)                                     \
    && INTVAL(XEXP(Addr, 1)) >= -16                                     \
    && INTVAL(XEXP(Addr, 1)) < 15                                       \
  )


#define LEGIT_MODIFIED_BASE_ADDR(Addr)                                  \
  (                                                                     \
       (   GET_CODE(Addr) == PRE_INC                                    \
        || GET_CODE(Addr) == PRE_DEC                                    \
        || GET_CODE(Addr) == POST_INC                                   \
        || GET_CODE(Addr) == POST_DEC                                   \
       )                                                                \
    && LEGIT_BASE_ADDR(XEXP(Addr, 0))                                   \
  )


#define LEGIT_BASE_INDEX_ADDR(Addr)                                     \
  (                                                                     \
       GET_CODE(Addr) == PLUS                                           \
    &&                                                                  \
       (                                                                \
              LEGIT_BASE_ADDR(XEXP(Addr, 0))                            \
           && LEGIT_INDEX_ADDR(XEXP(Addr, 1))                           \
        ||                                                              \
              LEGIT_BASE_ADDR(XEXP(Addr, 1))                            \
           && LEGIT_INDEX_ADDR(XEXP(Addr, 0))                           \
       )                                                                \
  )


#define LEGIT_INDIRECT_ADDR(Addr)                                       \
  (                                                                     \
       GET_CODE(Addr) == MEM                                            \
    && (                                                                \
           LEGIT_BASE_ADDR(XEXP(Addr, 0))                               \
        || LEGIT_BASE_OFFSET_ADDR(XEXP(Addr, 0))                        \
        || LEGIT_BASE_INDEX_ADDR(XEXP(Addr, 0))                         \
       )                                                                \
  )


#define LEGIT_INDIRECT_NONBASEINDEX_ADDR(Addr)                          \
  (                                                                     \
       GET_CODE(Addr) == MEM                                            \
    && (                                                                \
           LEGIT_BASE_ADDR(XEXP(Addr, 0))                               \
        || LEGIT_BASE_OFFSET_ADDR(XEXP(Addr, 0))                        \
       )                                                                \
  )


/* The macros REG_OK_FOR..._P assume that the arg is a REG rtx
   and check its validity for a certain class.
   We have two alternate definitions for each of them.

   The usual definition accepts all pseudo regs; the other rejects
   them unless they have been allocated suitable hard regs.
   The symbol REG_OK_STRICT causes the latter definition to be used.

   Most source files want to accept pseudo regs in the hope that
   they will get allocated to the class that the insn wants them to be in.
   Source files for reload pass need to be strict.
   After reload, it makes no difference, since pseudo regs have
   been eliminated by then.  						*/

/* A C expression that is nonzero if X (assumed to be a `reg' RTX) is
   valid for use as a base register.  For hard registers, it should
   always accept those which the hardware permits and reject the
   others.  Whether the macro accepts or rejects pseudo registers
   must be controlled by `REG_OK_STRICT' as described above.  This
   usually requires two variant definitions, of which `REG_OK_STRICT'
   controls the one actually used.					*/

#ifndef REG_OK_STRICT

  #define REG_OK_FOR_BASE_P(X)					 	\
    (									\
	 REGNO(X) == YREG	 						\
      || REGNO(X) == XREG							\
      || REGNO(X) == ZREG							\
      || REGNO(X) == SREG							\
      || REGNO(X) == APREG							\
      || REGNO(X) >= FIRST_PSEUDO_REGISTER				\
    )

#else /* REG_OK_STRICT */

  #define REG_OK_FOR_BASE_P(X) 						\
    REGNO_OK_FOR_BASE_P (REGNO (X))

#endif


/* A C expression that is nonzero if X (assumed to be a `reg' RTX) is
   valid for use as an index register.

   The difference between an index register and a base register is
   that the index register may be scaled.  If an address involves the
   sum of two registers, neither one of them scaled, then either one
   may be labeled the "base" and the other the "index"; but whichever
   labeling is used must fit the machine's constraints of which
   registers may serve in each capacity.  The compiler will try both
   labelings, looking for one that is valid, and will reload one or
   both registers only if neither labeling works.			*/

#ifndef REG_OK_STRICT

  #define REG_OK_FOR_INDEX_P(X) 0

#else /* REG_OK_STRICT */

  #define REG_OK_FOR_INDEX_P(X) 					\
    REGNO_OK_FOR_INDEX_P (REGNO (X))

#endif


/* A C compound statement that attempts to replace X with a valid
   memory address for an operand of mode MODE.  WIN will be a C
   statement label elsewhere in the code; the macro definition may use

	GO_IF_LEGITIMATE_ADDRESS (MODE, X, WIN);

   to avoid further processing if the address has become legitimate.

   X will always be the result of a call to `break_out_memory_refs',
   and OLDX will be the operand that was given to that function to
   produce X.

   The code generated by this macro should not alter the substructure
   of X.  If it transforms X into a more legitimate form, it should
   assign X (which will always be a C variable) a new value.

   It is not necessary for this macro to come up with a legitimate
   address.  The compiler has standard ways of doing so in all cases.
   In fact, it is safe for this macro to do nothing.  But often a
   machine-dependent strategy can generate better code.			*/

#define LEGITIMIZE_ADDRESS(X, OLDX, MODE, WIN) { }


/* A C statement or compound statement with a conditional `goto
   LABEL;' executed if memory address X (an RTX) can have different
   meanings depending on the machine mode of the memory reference it
   is used for or if the address is valid for some modes but not
   others.

   Autoincrement and autodecrement addresses typically have
   mode-dependent effects because the amount of the increment or
   decrement is the size of the operand being addressed.  Some
   machines have other mode-dependent addresses.  Many RISC machines
   have no mode-dependent addresses.

   You may assume that ADDR is a valid address for the machine.		*/

#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR, LABEL)                       \
{									\
}


/* A C expression that is nonzero if X is a legitimate constant for
   an immediate operand on the target machine.  You can assume that X
   satisfies `CONSTANT_P', so you need not check this.  In fact, `1'
   is a suitable definition for this macro on machines where anything
   `CONSTANT_P' is valid.						*/

#define LEGITIMATE_CONSTANT_P(X) 1


/*---------------------------------------------------------------------------
**
**	CONDITION CODE STATUS
**
**  The file `conditions.h' defines a variable `cc_status' to describe
**  how the condition code was computed (in case the interpretation of the
**  condition code depends on the instruction that it was set by).  This
**  variable contains the RTL expressions on which the condition code is
**  currently based, and several standard flags.
**
**  Sometimes additional machine-specific flags must be defined in the
**  machine description header file.  It can also add additional
**  machine-specific information by defining `CC_STATUS_MDEP'.
*/

/* A C compound statement to set the components of `cc_status'
   appropriately for an insn INSN whose body is EXP.  It is this
   macro's responsibility to recognize insns that set the condition
   code as a byproduct of other activity as well as those that
   explicitly set `(cc0)'.

   This macro is not used on machines that do not use `cc0'.

   If there are insns that do not set the condition code but do alter
   other machine registers, this macro must check to see whether they
   invalidate the expressions that the condition code is recorded as
   reflecting.  For example, on the 68000, insns that store in address
   registers do not set the condition code, which means that usually
   `NOTICE_UPDATE_CC' can leave `cc_status' unaltered for such insns.
   But suppose that the previous insn set the condition code based
   on location `a4@(102)' and the current insn stores a new value in
   `a4'.  Although the condition code is not changed by this, it will
   no longer be true that it reflects the contents of `a4@(102)'.
   Therefore, `NOTICE_UPDATE_CC' must alter `cc_status' in this case
   to say that nothing is known about the condition code value.

   The definition of `NOTICE_UPDATE_CC' must be prepared to deal with
   the results of peephole optimization: insns whose patterns are
   `parallel' RTXs containing various `reg', `mem' or constants which
   are just the operands.  The RTL structure of these insns is not
   sufficient to indicate what the insns actually do.  What
   `NOTICE_UPDATE_CC' should do when it sees one is just to run
   `CC_STATUS_INIT'.

   A possible definition of `NOTICE_UPDATE_CC' is to call a function
   that looks at an attribute (*note Insn Attributes::.) named, for
   example, `cc'.  This avoids having detailed information about
   patterns in two places, the `md' file and in `NOTICE_UPDATE_CC'.	*/

#define NOTICE_UPDATE_CC(EXP, INSN)					\
do {									\
  if (GET_CODE (EXP) == SET)						\
  {									\
    register rtx src;							\
    register rtx dst;							\
    									\
    src = SET_SRC(EXP);							\
    dst = SET_DEST(EXP);						\
    									\
    if (dst == pc_rtx)							\
      break;								\
									\
    if (								\
           GET_MODE_SIZE (GET_MODE (dst)) > 2				\
	|| GET_MODE_SIZE (GET_MODE (src)) > 2				\
       )								\
    {									\
      CC_STATUS_INIT;							\
      break;								\
    }									\
									\
    if (								\
          (                                                             \
              GET_CODE (dst) == REG                                     \
           &&								\
              (								\
                  GET_CODE (src) == MEM					\
               || GET_CODE (src) == AND					\
               || GET_CODE (src) == IOR					\
               || GET_CODE (src) == XOR					\
               || GET_CODE (src) == NOT					\
               || GET_CODE (src) == PLUS				\
                  && REG_P (XEXP (src, 0))                              \
                  && (                                                  \
                         REGNO (XEXP (src, 0)) == DREG                  \
                      || REGNO (XEXP (src, 0)) == EREG                  \
                     )                                                  \
               || GET_CODE (src) == MINUS				\
              )								\
          )                                                             \
       ||                                                               \
          (                                                             \
              GET_CODE (dst) == MEM                                     \
           &&								\
              (								\
                  GET_CODE (src) == REG					\
               || GET_CODE (src) == AND					\
               || GET_CODE (src) == IOR					\
               || GET_CODE (src) == NOT					\
               || GET_CODE (src) == PLUS				\
              )								\
          )                                                             \
       )                                                                \
    {									\
      cc_status.flags = CC_NO_OVERFLOW;                       		\
      cc_status.value1 = dst;						\
      if (!reg_overlap_mentioned_p(dst, src))				\
        cc_status.value2 = src;						\
      else								\
        cc_status.value2 = 0;						\
									\
      break;								\
    }									\
									\
    if (GET_CODE (src) == CALL)						\
    {									\
      CC_STATUS_INIT;							\
      break;								\
    }									\
									\
    if (dst == cc0_rtx)							\
    {                                                                   \
      CC_STATUS_INIT;                                                   \
      cc_status.value2 = src;		                                \
      break;                                                            \
    }                                                                   \
									\
    CC_STATUS_INIT;							\
  }                                                                     \
  else									\
  {									\
    CC_STATUS_INIT;							\
  }									\
} while (0);


/* A C expression whose value is one if it is always safe to reverse a
   comparison whose mode is MODE.  If `SELECT_CC_MODE' can ever
   return MODE for a floating-point inequality comparison, then
   `REVERSIBLE_CC_MODE (MODE)' must be zero.

   You need not define this macro if it would always returns zero or
   if the floating-point format is anything other than
   `IEEE_FLOAT_FORMAT'.  For example, here is the definition used on
   the Sparc, where floating-point inequality comparisons are always
   given `CCFPEmode':

	#define REVERSIBLE_CC_MODE(MODE)  ((MODE) != CCFPEmode)		*/

/* #define REVERSIBLE_CC_MODE(MODE)  1					*/


/*---------------------------------------------------------------------------
**
**	DESCRIBING THE RELATIVE COSTS OF OPERATIONS
**
*/

/* A part of a C `switch' statement that describes the relative costs
   of constant RTL expressions.  It must contain `case' labels for
   expression codes `const_int', `const', `symbol_ref', `label_ref'
   and `const_double'.  Each case must ultimately reach a `return'
   statement to return the relative cost of the use of that kind of
   constant value in an expression.  The cost may depend on the
   precise value of the constant, which is available for examination
   in X, and the rtx code of the expression in which it is contained,
   found in OUTER_CODE.

   CODE is the expression code--redundant, since it can be obtained
   with `GET_CODE (X)'.							*/

#define CONST_COSTS(X, CODE, OUTER_CODE)				\
  case CONST_INT:							\
  case CONST:								\
  case LABEL_REF:							\
  case SYMBOL_REF:							\
  case CONST_DOUBLE:							\
    return 0;


/* Like `CONST_COSTS' but applies to nonconstant RTL expressions.
   This can be used, for example, to indicate how costly a multiply
   instruction is.  In writing this macro, you can use the construct
   `COSTS_N_INSNS (N)' to specify a cost equal to N fast
   instructions.  OUTER_CODE is the code of the expression in which X
   is contained.

   This macro is optional; do not define it if the default cost
   assumptions are adequate for the target machine.			*/

#define RTX_COSTS(X,CODE,OUTER_CODE)					\
  case MULT:								\
    return COSTS_N_INSNS (4);						\
									\
  case UDIV:								\
  case UMOD:								\
    return COSTS_N_INSNS (4);						\
									\
  case DIV:								\
  case MOD:								\
    return COSTS_N_INSNS (4);


/* An expression giving the cost of an addressing mode that contains
   ADDRESS.  If not defined, the cost is computed from the ADDRESS
   expression and the `CONST_COSTS' values.

   For most CISC machines, the default cost is a good approximation
   of the true cost of the addressing mode.  However, on RISC
   machines, all instructions normally have the same length and
   execution time.  Hence all addresses will have equal costs.

   In cases where more than one form of an address is known, the form
   with the lowest cost will be used.  If multiple forms have the
   same, lowest, cost, the one that is the most complex will be used.

   For example, suppose an address that is equal to the sum of a
   register and a constant is used twice in the same basic block.
   When this macro is not defined, the address will be computed in a
   register and memory references will be indirect through that
   register.  On machines where the cost of the addressing mode
   containing the sum is no higher than that of a simple indirect
   reference, this will produce an additional instruction and
   possibly require an additional register.  Proper specification of
   this macro eliminates this overhead for such machines.

   Similar use of this macro is made in strength reduction of loops.

   ADDRESS need not be valid as an address.  In such a case, the cost
   is not relevant and can be any value; invalid addresses need not be
   assigned a different cost.

   On machines where an address involving more than one register is as
   cheap as an address computation involving only one register,
   defining `ADDRESS_COST' to reflect this can cause two registers to
   be live over a region of code where only one would have been if
   `ADDRESS_COST' were not defined in that manner.  This effect should
   be considered in the definition of this macro.  Equivalent costs
   should probably only be given to addresses with different numbers
   of registers on machines with lots of registers.

   This macro will normally either not be defined or be defined as a
   constant.								*/

/* #define ADDRESS_COST (ADDRESS)					*/


/* A C expression for the cost of moving data from a register in class
   FROM to one in class TO.  The classes are expressed using the
   enumeration values such as `GENERAL_REGS'.  A value of 2 is the
   default; other values are interpreted relative to that.

   It is not required that the cost always equal 2 when FROM is the
   same as TO; on some machines it is expensive to move between
   registers if they are not general registers.

   If reload sees an insn consisting of a single `set' between two
   hard registers, and if `REGISTER_MOVE_COST' applied to their
   classes returns a value of 2, reload does not check to ensure that
   the constraints of the insn are met.  Setting a cost of other than
   2 will allow reload to verify that the constraints are met.  You
   should do this if the `movM' pattern's constraints do not allow
   such copying.							*/

#define REGISTER_MOVE_COST(FROM, TO) (4)


/* A C expression for the cost of moving data of mode M between a
   register and memory.  A value of 4 is the default; this cost is
   relative to those in `REGISTER_MOVE_COST'.

   If moving between registers and memory is more expensive than
   between two registers, you should define this macro to express the
   relative cost.							*/

#define MEMORY_MOVE_COST(M)  (4)


/* A C expression for the cost of a branch instruction.  A value of 1
   is the default; other values are interpreted relative to that.	*/

#define BRANCH_COST 0


/* Define this macro as a C expression which is nonzero if accessing
   less than a word of memory (i.e. a `char' or a `short') is no
   faster than accessing a word of memory, i.e., if such access
   require more than one instruction or if there is no difference in
   cost between byte and (aligned) word loads.

   When this macro is not defined, the compiler will access a field by
   finding the smallest containing object; when it is defined, a
   fullword load will be used if alignment permits.  Unless bytes
   accesses are faster than word accesses, using word accesses is
   preferable since it may eliminate subsequent memory access if
   subsequent accesses occur to other fields in the same word of the
   structure, but to different bytes.					*/

#define SLOW_BYTE_ACCESS 0


/* Define this macro if zero-extension (of a `char' or `short' to an
   `int') can be done faster if the destination is a register that is
   known to be zero.

   If you define this macro, you must have instruction patterns that
   recognize RTL structures like this:

	(set (strict_low_part (subreg:QI (reg:SI ...) 0)) ...)

   and likewise for `HImode'.						*/

/* #define SLOW_ZERO_EXTEND 						*/


/* Define this macro to inhibit strength reduction of memory
   addresses.  (On some machines, such strength reduction seems to do
   harm rather than good.)						*/

#define DONT_REDUCE_ADDR


/* The number of scalar move insns which should be generated instead
   of a string move insn or a library call.  Increasing the value
   will always make code faster, but eventually incurs high cost in
   increased code size.

   If you don't define this, a reasonable default is used.		*/

/* #define MOVE_RATIO							*/


/* Define this macro if it is as good or better to call a constant
   function address than to call an address kept in a register.		*/

#define NO_FUNCTION_CSE


/* Define this macro if it is as good or better for a function to call
   itself with an explicit address than to call an address kept in a
   register.								*/

#define NO_RECURSIVE_FUNCTION_CSE


/*---------------------------------------------------------------------------
**
**	DIVIDING THE OUTPUT INTO SECTIONS
**
**  An object file is divided into sections containing different types of
**  data.  In the most common case, there are three sections: the "text
**  section", which holds instructions and read-only data; the "data
**  section", which holds initialized writable data; and the "bss section",
**  which holds uninitialized data.  Some systems have other kinds of
**  sections.
**
**  The compiler must tell the assembler when to switch sections.  These
**  macros control what commands to output to tell the assembler this.  You
**  can also define additional sections.
*/

/* A list of names for sections other than the standard two, which are
   `in_text' and `in_data'.  You need not define this macro on a
   system with no other sections (that GCC needs to use).		*/

#define EXTRA_SECTIONS 							\
  in_udata, 								\
  in_ctor, 								\
  in_dtor, 								\
  in_const

#define HC1x_EXTRA_SECTIONS 						\
  HC1x_in_udata, 							\
  HC1x_in_ctor, 							\
  HC1x_in_dtor, 							\
  HC1x_in_const

/* A C expression whose value is a string containing the assembler
   operation that should precede instructions and read-only data.
   Normally `".text"' is right.						*/

#define TEXT_SECTION_ASM_OP 						\
    "\n\tsection\t.text"						\


/* A C expression whose value is a string containing the assembler
   operation to identify the following data as writable initialized
   data.  Normally `".data"' is right.					*/

#define DATA_SECTION_ASM_OP						\
   "\n\tsection\t.data"						\


/* If defined, a C expression whose value is a string containing the
   assembler operation to identify the following data as shared data.
   If not defined, `DATA_SECTION_ASM_OP' will be used.			*/

/* #define SHARED_SECTION_ASM_OP					*/


/* If defined, a C expression whose value is a string containing the
   assembler operation to identify the following data as
   initialization code.  If not defined, GNU CC will assume such a
   section does not exist.						*/

/* #define INIT_SECTION_ASM_OP						*/


/* One or more functions to be defined in `varasm.c'.  These
   functions should do jobs analogous to those of `text_section' and
   `data_section', for your additional sections.  Do not define this
   macro if you do not define `EXTRA_SECTIONS'.				*/

#define EXTRA_SECTION_FUNCTIONS						\
  UDATA_SECTION_FUNCTION						\
  CTOR_SECTION_FUNCTION							\
  DTOR_SECTION_FUNCTION							\
  CONST_SECTION_FUNCTION

#define UDATA_SECTION_FUNCTION						\
void udata_section()							\
{									\
  if (in_section != in_udata)						\
  {									\
    fprintf (asm_out_file,  "\n\tsection\t.bss\n");			\
    in_section = in_udata;						\
  }									\
}

#define CTOR_SECTION_FUNCTION						\
void ctor_section()							\
{									\
  if (in_section != in_ctor)						\
  {									\
    fprintf (asm_out_file, "\n\tsection\t.ctor\n");			\
    in_section = in_ctor;						\
  }									\
}

#define DTOR_SECTION_FUNCTION						\
void dtor_section()							\
{									\
  if (in_section != in_dtor)						\
  {									\
    fprintf (asm_out_file, "\n\tsection\t.dtor\n");			\
    in_section = in_dtor;						\
  }									\
}

#define CONST_SECTION_FUNCTION						\
void const_section()							\
{									\
  if (in_section != in_const)						\
  {									\
    fprintf (asm_out_file, "\n\tsection\t.const\n");			\
    in_section = in_const;						\
  }									\
}


/* On most machines, read-only variables, constants, and jump tables
   are placed in the text section.  If this is not the case on your
   machine, this macro should be defined to be the name of a function
   (either `data_section' or a function defined in `EXTRA_SECTIONS')
   that switches to the section to be used for read-only items.

   If these items should be placed in the text section, this macro
   should not be defined.						*/

#define READONLY_DATA_SECTION  data_section


/* A C statement or statements to switch to the appropriate section
   for output of EXP.  You can assume that EXP is either a `VAR_DECL'
   node or a constant of some sort.  RELOC indicates whether the
   initial value of EXP requires link-time relocations.  Select the
   section by calling `text_section' or one of the alternatives for
   other sections.

   Do not define this macro if you put all read-only variables and
   constants in the read-only data section (usually the text section).	*/

/* #define SELECT_SECTION (EXP, RELOC)					*/


/* A C statement or statements to switch to the appropriate section
   for output of RTX in mode MODE.  You can assume that RTX is some
   kind of constant in RTL.  The argument MODE is redundant except in
   the case of a `const_int' rtx.  Select the section by calling
   `text_section' or one of the alternatives for other sections.

   Do not define this macro if you put all constants in the read-only
   data section.							*/

/* #define SELECT_RTX_SECTION (MODE, RTX)				*/


/* Define this macro if jump tables (for `tablejump' insns) should be
   output in the text section, along with the assembler instructions.
   Otherwise, the readonly data section is used.

   This macro is irrelevant if there is no separate readonly data
   section.								*/

#define JUMP_TABLES_IN_TEXT_SECTION


/* Define this macro if references to a symbol must be treated
   differently depending on something about the variable or function
   named by the symbol (such as what section it is in).

   The macro definition, if any, is executed immediately after the
   rtl for DECL has been created and stored in `DECL_RTL (DECL)'.
   The value oo the rtl will be a `mem' whose address is a
   `symbol_ref'.

   The usual thing for this macro to do is to record a flag in the
   `symbol_ref' (such as `SYMBOL_REF_FLAG') or to store a modified
   name string in the `symbol_ref' (if one bit is not enough
   information).							*/

/* #define ENCODE_SECTION_INFO (DECL)					*/


/* Decode SYM_NAME and store the real name part in VAR, sans the
   characters that encode section info.  Define this macro if
   `ENCODE_SECTION_INFO' alters the symbol's name string.		*/

/* #define STRIP_NAME_ENCODING (VAR, SYM_NAME)				*/


/*---------------------------------------------------------------------------
**
**	DEFINING THE OUTPUT ASSEMBLER LANGUAGE
**
*/


/* A C expression which outputs to the stdio stream STREAM some
   appropriate text to go at the start of an assembler file.

   Normally this macro is defined to output a line containing
   `#NO_APP', which is a comment that has no effect on most
   assemblers but tells the GNU assembler that it can save time by not
   checking for certain assembler constructs.

   On systems that use SDB, it is necessary to output certain
   commands; see `attasm.h'. 						*/

#define ASM_FILE_START(STREAM)


/* A C expression which outputs to the stdio stream STREAM some
   appropriate text to go at the end of an assembler file.

   If this macro is not defined, the default is to output nothing
   special at the end of the file.  Most systems don't require any
   definition.

   On systems that use SDB, it is necessary to output certain
   commands; see `attasm.h'. 						*/

#define ASM_FILE_END(STREAM)						\
  fprintf(STREAM, "\n\n\tend\n");


/* A C statement to output assembler commands which will identify the
   object file as having been compiled with GNU CC (or another GNU
   compiler).

   If you don't define this macro, the string `gcc_compiled.:' is
   output.  This string is calculated to define a symbol which, on
   BSD systems, will never be defined for any other reason.  GDB
   checks for the presence of this symbol when reading the symbol
   table of an executable.

   On non-BSD systems, you must arrange communication with GDB in
   some other fashion.  If GDB is not used on your system, you can
   define this macro with an empty body.				*/

#define ASM_IDENTIFY_GCC(STREAM)

/* A C string constant describing how to begin a comment in the target
   assembler language.  The compiler assumes that the comment will
   end at the end of the line. 						*/

#define ASM_COMMENT_START "\t;"


/* A C string constant for text to be output before each `asm'
   statement or group of consecutive ones.  Normally this is
   `"#APP"', which is a comment that has no effect on most assemblers
   but tells the GNU assembler that it must check the lines that
   follow for all valid assembler constructs.				*/

#define ASM_APP_ON ""


/* A C string constant for text to be output after each `asm'
   statement or group of consecutive ones.  Normally this is
   `"#NO_APP"', which tells the GNU assembler to resume making the
   time-saving assumptions that are valid for ordinary compiler
   output.								*/

#define ASM_APP_OFF ""


/* A C statement to output something to the assembler file to handle a
   `#ident' directive containing the text STRING.  If this macro is
   not defined, nothing is output for a `#ident' directive.		*/

/* #define ASM_OUTPUT_IDENT(STREAM, NAME)				\
  fprintf (STREAM, "\tident \"%s\"\n", NAME)				*/


/* A C statement to output something to the assembler file to switch
   to section NAME for object DECL which is either a `FUNCTION_DECL',
   a `VAR_DECL' or `NULL_TREE'.  RELOC indicates whether the initial
   value of EXP requires link-time relocations.  Some target formats
   do not support arbitrary sections.  Do not define this macro in
   such cases.

   At present this macro is only used to support section attributes.
   When this macro is undefined, section attributes are disabled.	*/

#define ASM_OUTPUT_SECTION_NAME(STREAM, DECL, NAME, RELOC)		\
  do {									\
    fprintf (STREAM, "\tsection\t%s\n", NAME);				\
  } while (0)



/*---------------------------------------------------------------------------
**
**	OUTPUT OF DATA
**
*/

/* A C statement to output to the stdio stream STREAM an assembler
   instruction to assemble a floating-point constant of `TFmode',
   `DFmode', `SFmode', `TQFmode', `HFmode', or `QFmode',
   respectively, whose value is VALUE.  VALUE will be a C expression
   of type `REAL_VALUE_TYPE'.  Macros such as
   `REAL_VALUE_TO_TARGET_DOUBLE' are useful for writing these
   definitions.								*/

#define ASM_OUTPUT_FLOAT(STREAM, VALUE)					\
  fprintf (STREAM, "\tfloat\t%e\n", VALUE);

#define ASM_OUTPUT_DOUBLE(STREAM, VALUE)				\
  fprintf (STREAM, "\tfloat\t%e\n", VALUE);

#define ASM_OUTPUT_LONG_DOUBLE(STREAM, VALUE)				\
  fprintf (STREAM, "\tfloat\t%e\n", VALUE);


/* A C statement to output to the stdio stream STREAM an assembler
   instruction to assemble an integer of 16, 8, 4, 2 or 1 bytes,
   respectively, whose value is VALUE.  The argument EXP will be an
   RTL expression which represents a constant value.  Use
   `output_addr_const (STREAM, EXP)' to output this value as an
   assembler expression.

   For sizes larger than `UNITS_PER_WORD', if the action of a macro
   would be identical to repeatedly calling the macro corresponding to
   a size of `UNITS_PER_WORD', once for each word, you need not define
   the macro.								*/

#define ASM_OUTPUT_INT(STREAM, VALUE) 					\
( 									\
  fprintf (STREAM, "\tdc.l\t"),						\
  output_addr_const (STREAM, (VALUE)),					\
  fprintf (STREAM, "\n")							\
)

#define ASM_OUTPUT_SHORT(STREAM, VALUE)	  				\
( 									\
  fprintf (STREAM, "\tdc.w\t"),						\
  output_addr_const (STREAM, (VALUE)),					\
  fprintf (STREAM, "\n")							\
)

#define ASM_OUTPUT_CHAR(STREAM, VALUE)	  				\
(									\
  fprintf (STREAM, "\tdc.b\t"),						\
  output_addr_const (STREAM, (VALUE)),					\
  fprintf (STREAM, "\n")						\
)


/* A C statement to output to the stdio stream STREAM an assembler
   instruction to assemble a single byte containing the number VALUE.	*/

#define ASM_OUTPUT_BYTE(STREAM, VALUE)					\
  fprintf (STREAM, "\tdc.b\t0%02Xh\n", (VALUE))


/* A C string constant giving the pseudo-op to use for a sequence of
   single-byte constants.  If this macro is not defined, the default
   is `"byte"'.								*/

#define ASM_BYTE_OP "\tdc.b\t"


/* A C statement to output to the stdio stream STREAM an assembler
   instruction to assemble a string constant containing the LEN bytes
   at PTR.  PTR will be a C expression of type `char *' and LEN a C
   expression of type `int'.

   If the assembler has a `.ascii' pseudo-op as found in the Berkeley
   Unix assembler, do not define the macro `ASM_OUTPUT_ASCII'.		*/

#define ASM_OUTPUT_ASCII(STREAM, PTR, LEN)				\
  do {									\
    unsigned char *s;							\
    int i;								\
    for (i = 0, s = (unsigned char *)(PTR); i < (LEN); s++, i++)	\
    {									\
      if ((i % 8) == 0)							\
	fprintf ((STREAM),"%s\tdc.b\t", (i ? "\n" : ""));		\
      fprintf ((STREAM), "%s0%02Xh", (i%8 ? "," : ""), (unsigned)*s);	\
    }									\
    fputs ("\n", (STREAM));						\
    fputs ("\n\talign\t1\t; ASM_OUTPUT_ASCII\n", (STREAM));		\
  } while (0)


/* These macros are defined as C string constant, describing the
   syntax in the assembler for grouping arithmetic expressions.  The
   following definitions are correct for most assemblers:		*/

#define ASM_OPEN_PAREN "("
#define ASM_CLOSE_PAREN ")"


/*---------------------------------------------------------------------------
**
**	OUTPUT OF UNINITIALIZED VARIABLES
**
*/

/* A C statement (sans semicolon) to output to the stdio stream
   STREAM the assembler definition of a common-label named NAME whose
   size is SIZE bytes.  The variable ROUNDED is the size rounded up
   to whatever alignment the caller wants.

   Use the expression `assemble_name (STREAM, NAME)' to output the
   name itself; before and after that, output the additional
   assembler syntax for defining the name, and a newline.

   This macro controls how the assembler definitions of uninitialized
   global variables are output. */

#define ASM_OUTPUT_COMMON(STREAM, NAME, SIZE, ROUNDED)			\
  do {									\
    udata_section();							\
    ASM_GLOBALIZE_LABEL(STREAM, NAME);					\
    ASM_OUTPUT_LABEL(STREAM, NAME);					\
    fprintf (STREAM, "\tds.b\t%u\n", SIZE);				\
  } while (0)


/* A C statement (sans semicolon) to output to the stdio stream
   STREAM the assembler definition of a local-common-label named NAME
   whose size is SIZE bytes.  The variable ROUNDED is the size
   rounded up to whatever alignment the caller wants.

   Use the expression `assemble_name (STREAM, NAME)' to output the
   name itself; before and after that, output the additional
   assembler syntax for defining the name, and a newline.

   This macro controls how the assembler definitions of uninitialized
   static variables are output. */

#define ASM_OUTPUT_LOCAL(STREAM, NAME, SIZE, ROUNDED)			\
  do {									\
    udata_section();							\
    ASM_OUTPUT_LABEL (STREAM, NAME);					\
    fprintf (STREAM, "\tds.b\t%u\n", SIZE);				\
  } while (0)


/*---------------------------------------------------------------------------
**
**	OUTPUT AND GENERATION OF LABELS
**
*/

/* A C statement (sans semicolon) to output to the stdio stream
   STREAM the assembler definition of a label named NAME.  Use the
   expression `assemble_name (STREAM, NAME)' to output the name
   itself; before and after that, output the additional assembler
   syntax for defining the name, and a newline. */

#define ASM_OUTPUT_LABEL(STREAM, NAME)					\
  do {									\
    assemble_name (STREAM, NAME);					\
    fprintf (STREAM, "\n");			        	  	\
  } while (0)


/* A C statement (sans semicolon) to output to the stdio stream
   STREAM any text necessary for declaring the name NAME of a
   function which is being defined.  This macro is responsible for
   outputting the label definition (perhaps using
   `ASM_OUTPUT_LABEL').  The argument DECL is the `FUNCTION_DECL'
   tree node representing the function.

   If this macro is not defined, then the function name is defined in
   the usual manner as a label (by means of `ASM_OUTPUT_LABEL'). */

#define ASM_DECLARE_FUNCTION_NAME(STREAM, NAME, DECL)			\
  do {									\
    if (TARGET_MEDIUM)							\
    {                   						\
      const_section();							\
      ASM_OUTPUT_LABEL(STREAM, NAME);					\
									\
      if (!strstr(NAME, "__thunk_"))					\
      {									\
	fprintf(STREAM, "\tjmp\tL");  ASM_OUTPUT_LABEL(STREAM, NAME);	\
									\
	text_section();							\
	fprintf(STREAM, "L");  ASM_OUTPUT_LABEL(STREAM, NAME);		\
      }									\
    }									\
									\
    else								\
    {									\
      ASM_OUTPUT_LABEL(STREAM, NAME);					\
    }									\
									\
  } while (0)


/* A C statement (sans semicolon) to output to the stdio stream
   STREAM any text necessary for declaring the size of a function
   which is being defined.  The argument NAME is the name of the
   function.  The argument DECL is the `FUNCTION_DECL' tree node
   representing the function.

   If this macro is not defined, then the function size is not
   defined. */

/* ASM_DECLARE_FUNCTION_SIZE (STREAM, NAME, DECL) */


/* A C statement (sans semicolon) to output to the stdio stream
   STREAM any text necessary for declaring the name NAME of an
   initialized variable which is being defined.  This macro must
   output the label definition (perhaps using `ASM_OUTPUT_LABEL').
   The argument DECL is the `VAR_DECL' tree node representing the
   variable.

   If this macro is not defined, then the variable name is defined in
   the usual manner as a label (by means of `ASM_OUTPUT_LABEL'). */

/* #define ASM_DECLARE_OBJECT_NAME(STREAM, NAME, DECL)			*/


/* A C statement (sans semicolon) to finish up declaring a variable
   name once the compiler has processed its initializer fully and
   thus has had a chance to determine the size of an array when
   controlled by an initializer.  This is used on systems where it's
   necessary to declare something about the size of the object.

   If you don't define this macro, that is equivalent to defining it
   to do nothing. */

/* #define ASM_FINISH_DECLARE_OBJECT(STREAM, DECL, TOPLEVEL, ATEND)	*/


/* A C statement (sans semicolon) to output to the stdio stream
   STREAM some commands that will make the label NAME global; that
   is, available for reference from other files.  Use the expression
   `assemble_name (STREAM, NAME)' to output the name itself; before
   and after that, output the additional assembler syntax for making
   that name global, and a newline. */

#define ASM_GLOBALIZE_LABEL(STREAM, NAME)				\
  do {									\
    fputs ("\n\tglobal\t", STREAM);					\
    assemble_name (STREAM, NAME);					\
    fputs ("\n", STREAM);						\
  } while (0)


/* A C statement (sans semicolon) to output to the stdio stream
   STREAM any text necessary for declaring the name of an external
   symbol named NAME which is referenced in this compilation but not
   defined.  The value of DECL is the tree node for the declaration.

   This macro need not be defined if it does not need to output
   anything.  The GNU assembler and most Unix assemblers don't
   require anything. */

/* #define ASM_OUTPUT_EXTERNAL(STREAM, DECL, NAME) 			*/


/* A C statement (sans semicolon) to output to the stdio stream
   STREAM a reference in assembler syntax to a label named NAME.
   This should add `_' to the front of the name, if that is customary
   on your operating system, as it is in most Berkeley Unix systems.
   This macro is used in `assemble_name'.				*/

#define ASM_OUTPUT_LABELREF(STREAM, NAME)					\
  do {									\
    fprintf (STREAM, "_%s", NAME);					\
  } while (0)


/* A C statement to output to the stdio stream STREAM a label whose
   name is made from the string PREFIX and the number NUM.

   It is absolutely essential that these labels be distinct from the
   labels used for user-level functions and variables.  Otherwise,
   certain programs will have name conflicts with internal labels.

   It is desirable to exclude internal labels from the symbol table
   of the object file.  Most assemblers have a naming convention for
   labels that should be excluded; on many systems, the letter `L' at
   the beginning of a label has this effect.  You should find out what
   convention your system uses, and follow it.

   The usual definition of this macro is as follows:

	fprintf (STREAM, "L%s%d:\n", PREFIX, NUM)			*/

#define ASM_OUTPUT_INTERNAL_LABEL(STREAM, PREFIX, NUM)			\
  do {									\
    char buf[256];							\
    ASM_GENERATE_INTERNAL_LABEL (buf, PREFIX, NUM);			\
									\
    fprintf (STREAM, "\n");     					\
    assemble_name (STREAM, buf);					\
									\
  } while (0)


/* A C statement to store into the string STRING a label whose name
   is made from the string PREFIX and the number NUM.

   This string, when output subsequently by `assemble_name', should
   produce the output that `ASM_OUTPUT_INTERNAL_LABEL' would produce
   with the same PREFIX and NUM.

   If the string begins with `*', then `assemble_name' will output
   the rest of the string unchanged.  It is often convenient for
   `ASM_GENERATE_INTERNAL_LABEL' to use `*' in this way.  If the
   string doesn't start with `*', then `ASM_OUTPUT_LABELREF' gets to
   output the string, and may change it.  (Of course,
   `ASM_OUTPUT_LABELREF' is also part of your machine description, so
   you should know what it does on your machine.)			*/

#define ASM_GENERATE_INTERNAL_LABEL(LABEL, PREFIX, NUM)			\
  do {									\
      sprintf (LABEL, "*%s%d", PREFIX, NUM);				\
  } while (0)


/* A C expression to assign to OUTVAR (which is a variable of type
   `char *') a newly allocated string made from the string NAME and
   the number NUMBER, with some suitable punctuation added.  Use
   `alloca' to get space for the string.

   The string will be used as an argument to `ASM_OUTPUT_LABELREF' to
   produce an assembler label for an internal static variable whose
   name is NAME.  Therefore, the string must be such as to result in
   valid assembler code.  The argument NUMBER is different each time
   this macro is executed; it prevents conflicts between
   similarly-named internal static variables in different scopes.

   Ideally this string should not be a valid C identifier, to prevent
   any conflict with the user's own symbols.  Most assemblers allow
   periods or percent signs in assembler symbols; putting at least
   one of these between the name and the number will suffice.		*/

#define ASM_FORMAT_PRIVATE_NAME(OUTPUT, NAME, LABELNO)			\
do {									\
    int len = strlen (NAME);						\
    char *temp = (char *) alloca (len + 3);				\
    temp[0] = 'L';							\
    strcpy (&temp[1], (NAME));						\
    temp[len + 1] = '.';						\
    temp[len + 2] = 0;							\
    (OUTPUT) = (char *) alloca (strlen (NAME) + 11);			\
    ASM_GENERATE_INTERNAL_LABEL (OUTPUT, temp, LABELNO);		\
   }while (0)


/*---------------------------------------------------------------------------
**
**	MACROS CONTROLLING INITIALIZATION ROUTINES
**
*/

/* If defined, a C string constant for the assembler operation to
   identify the following data as initialization code.  If not
   defined, GNU CC will assume such a section does not exist.  When
   you are using special sections for initialization and termination
   functions, this macro also controls how `crtstuff.c' and
   `libgcc2.c' arrange to run the initialization functions.		*/

/* #define INIT_SECTION_ASM_OP						*/


/* If defined, `main' will not call `__main' as described above.
   This macro should be defined for systems that control the contents
   of the init section on a symbol-by-symbol basis, such as OSF/1,
   and should not be defined explicitly for systems that support
   `INIT_SECTION_ASM_OP'.						*/

#define HAS_INIT_SECTION


/* If defined, `main' will call `__main' despite the presence of
   `INIT_SECTION_ASM_OP'.  This macro should be defined for systems
   where the init section is not actually run automatically, but is
   still useful for collecting the lists of constructors and
   destructors.								*/

/* #define INVOKE__main							*/


/* Define this macro as a C statement to output on the stream STREAM
   the assembler code to arrange to call the function named NAME at
   initialization time.

   Assume that NAME is the name of a C function generated
   automatically by the compiler.  This function takes no arguments.
   Use the function `assemble_name' to output the name NAME; this
   performs any system-specific syntactic transformations such as
   adding an underscore.

   If you don't define this macro, nothing special is output to
   arrange to call the function.  This is correct when the function
   will be called in some other manner--for example, by means of the
   `collect2' program, which looks through the symbol table to find
   these functions by their names. 					*/

#define ASM_OUTPUT_CONSTRUCTOR(STREAM, NAME)				\
  do {									\
    ctor_section ();							\
    fprintf (STREAM, "\tdc.w\t");					\
    assemble_name (STREAM, NAME);					\
    fprintf (STREAM, "\n");						\
  } while (0)


/* This is like `ASM_OUTPUT_CONSTRUCTOR' but used for termination
   functions rather than initialization functions. 			*/

#define ASM_OUTPUT_DESTRUCTOR(STREAM, NAME)			       	\
  do {									\
    dtor_section (); 		                  			\
    fprintf (STREAM, "\tdc.w\t");					\
    assemble_name (STREAM, NAME);              				\
    fprintf (STREAM, "\n");						\
  } while (0)


/*---------------------------------------------------------------------------
**
**	 OUTPUT OF ASSEMBLER INSTRUCTIONS
**
*/

/* A C initializer containing the assembler's names for the machine
   registers, each one as a C string constant.  This is what
   translates register numbers in the compiler into assembler
   language.								*/

#define REGISTER_NAMES							\
  { "e", "d", "y", "x", "z", "s", "ap" }


/* Print operand X (an rtx) in assembler syntax to file FILE.
   CODE is a letter or dot (`z' in `%z0') or 0 if no letter was specified.
   For `%' followed by punctuation, CODE is the punctuation and X is null. */

/* A C compound statement to output to stdio stream STREAM the
   assembler syntax for an instruction operand X.  X is an RTL
   expression.

   CODE is a value that can be used to specify one of several ways of
   printing the operand.  It is used when identical operands must be
   printed differently depending on the context.  CODE comes from the
   `%' specification that was used to request printing of the
   operand.  If the specification was just `%DIGIT' then CODE is 0;
   if the specification was `%LTR DIGIT' then CODE is the ASCII code
   for LTR.

   If X is a register, this macro should print the register's name.
   The names can be found in an array `reg_names' whose type is `char
   *[]'.  `reg_names' is initialized from `REGISTER_NAMES'.

   When the machine description has a specification `%PUNCT' (a `%'
   followed by a punctuation character), this macro is called with a
   null pointer for X and the punctuation character for CODE.		*/

#define PRINT_OPERAND(STREAM, X, CODE) 					\
{									\
  int i;								\
									\
  if (GET_CODE (X) == REG)						\
    fprintf (STREAM, "%s", reg_names[REGNO (X)]);			\
									\
  else if (GET_CODE (X) == MEM)                                         \
  {                                                                     \
    hc1x_mem_mode = GET_MODE (X);					\
    output_address (XEXP (X, 0));					\
  }									\
									\
  else if (GET_CODE (X) == CONST_DOUBLE)				\
  {									\
    REAL_VALUE_TYPE d;							\
    long l;								\
									\
    REAL_VALUE_FROM_CONST_DOUBLE (d, X);				\
    REAL_VALUE_TO_TARGET_SINGLE (d, l);					\
    fprintf (STREAM, "%ld", l);						\
  }									\
									\
  else									\
  {									\
    fprintf (STREAM, "#");						\
    output_addr_const (STREAM, X);		 			\
  }									\
}


/* A C compound statement to output to stdio stream STREAM the
   assembler syntax for an instruction operand that is a memory
   reference whose address is X.  X is an RTL expression.

   On some machines, the syntax for a symbolic address depends on the
   section that the address refers to.  On these machines, define the
   macro `ENCODE_SECTION_INFO' to store the information into the
   `symbol_ref', and then check for it here.				*/

#define PRINT_OPERAND_ADDRESS(STREAM, ADDR)			      	\
{									\
  register rtx Addr = ADDR;						\
                                                                        \
  if (CONSTANT_ADDRESS_P(Addr))                                         \
  {                                                                     \
    fprintf(STREAM, "%s", HC1x_offset);                                 \
									\
    if (GET_CODE(Addr) == CONST_INT)                                    \
      fprintf(STREAM, "0%04Xh", INTVAL(Addr) & 0xFFFF);                 \
    else                                                                \
      output_addr_const(STREAM, Addr);                                  \
  }                                                                     \
									\
  else if (LEGIT_BASE_ADDR(Addr))                                       \
  {                                                                     \
    fprintf(STREAM, "%s0,%s", HC1x_offset, reg_names[REGNO(Addr)]);     \
  }                                                                     \
									\
  else if (LEGIT_BASE_OFFSET_ADDR(Addr))                                \
  {                                                                     \
    fprintf(STREAM, "%s", HC1x_offset);                                 \
    output_addr_const(STREAM, XEXP(Addr, 1));                           \
    fprintf(STREAM, ",%s", reg_names[REGNO(XEXP(Addr, 0))]);            \
  }                                                                     \
									\
  else                                                                  \
  {                                                                     \
    fprintf(STREAM, "bad address");                                     \
    print_rtl(STREAM, ADDR);                                            \
  }                                                                     \
									\
  HC1x_offset = "";                                                     \
}


/* A C expression to output to STREAM some assembler code which will
   push hard register number REGNO onto the stack.  The code need not
   be optimal, since this macro is used only when profiling.		*/

#define ASM_OUTPUT_REG_PUSH(STREAM, REGNO) 				\
  fatal("profiling not implemented");


/* A C expression to output to STREAM some assembler code which will
   pop hard register number REGNO off of the stack.  The code need
   not be optimal, since this macro is used only when profiling.	*/

#define ASM_OUTPUT_REG_POP(STREAM, REGNO)				\
  fatal("profiling not implemented");


/*---------------------------------------------------------------------------
**
**	OUTPUT OF DISPATCH TABLES
**
*/

/* This macro should be provided on machines where the addresses in a
   dispatch table are relative to the table's own address.

   The definition should be a C statement to output to the stdio
   stream STREAM an assembler pseudo-instruction to generate a
   difference between two labels.  VALUE and REL are the numbers of
   two internal labels.  The definitions of these labels are output
   using `ASM_OUTPUT_INTERNAL_LABEL', and they must be printed in the
   same way here.  For example,

	fprintf (STREAM, "\t.word L%d-L%d\n",
		 VALUE, REL)						*/

#define ASM_OUTPUT_ADDR_DIFF_ELT(STREAM, VALUE, REL)  			\
  do {									\
    char buf0[256];							\
    char buf1[256];							\
    ASM_GENERATE_INTERNAL_LABEL (buf0, "L", VALUE);			\
    ASM_GENERATE_INTERNAL_LABEL (buf1, "L", REL);			\
    									\
    fprintf (STREAM, "\tdc.w\t");					\
    assemble_name (STREAM, buf0);					\
    fprintf (STREAM, " - ");						\
    assemble_name (STREAM, buf1);					\
    fprintf (STREAM, "t\n");						\
									\
  } while(0)


/* This macro should be provided on machines where the addresses in a
   dispatch table are absolute.

   The definition should be a C statement to output to the stdio
   stream STREAM an assembler pseudo-instruction to generate a
   reference to a label.  VALUE is the number of an internal label
   whose definition is output using `ASM_OUTPUT_INTERNAL_LABEL'.  For
   example,

	fprintf (STREAM, "\t.word L%d\n", VALUE)			*/

#define ASM_OUTPUT_ADDR_VEC_ELT(STREAM, VALUE)  			\
  do {									\
    char buf[256];							\
    ASM_GENERATE_INTERNAL_LABEL (buf, "L", VALUE);			\
									\
    fprintf (STREAM, "\tdc.w\t");					\
    assemble_name (STREAM, buf);					\
    fprintf (STREAM, "\n");						\
									\
  } while(0)


/* Define this if the label before a jump-table needs to be output
   specially.  The first three arguments are the same as for
   `ASM_OUTPUT_INTERNAL_LABEL'; the fourth argument is the jump-table
   which follows (a `jump_insn' containing an `addr_vec' or
   `addr_diff_vec').

   This feature is used on system V to output a `swbeg' statement for
   the table.

   If this macro is not defined, these labels are output with
   `ASM_OUTPUT_INTERNAL_LABEL'.						*/

#define ASM_OUTPUT_CASE_LABEL(STREAM, PREFIX, NUM, TABLE)		\
 do {									\
   char buf[256];							\
   ASM_GENERATE_INTERNAL_LABEL (buf, "L", NUM);				\
    									\
   assemble_name (STREAM, buf);						\
   fprintf (STREAM, "t\n");						\
    									\
   data_section();							\
   assemble_name(STREAM, buf);						\
   fprintf (STREAM, "\n");						\
    									\
  } while(0)
 

/* Define this if something special must be output at the end of a
   jump-table.  The definition should be a C statement to be executed
   after the assembler code for the table is written.  It should write
   the appropriate code to stdio stream STREAM.  The argument TABLE
   is the jump-table insn, and NUM is the label-number of the
   preceding label.

   If this macro is not defined, nothing special is output at the end
   of the jump-table.							*/

#define ASM_OUTPUT_CASE_END(STREAM, NUM, TABLE)				\
 do {									\
   text_section();							\
 } while(0)



/*---------------------------------------------------------------------------
**
**	ASSEMBLER COMMANDS FOR ALIGNMENT
**
*/

/* A C statement to output to the stdio stream STREAM an assembler
   instruction to advance the location counter by NBYTES bytes.
   Those bytes should be zero when loaded.  NBYTES will be a C
   expression of type `int'.						*/

#define ASM_OUTPUT_SKIP(STREAM, SIZE)  					\
  fprintf ((STREAM), "\tdcb.b\t%u,0\n", (SIZE))


/* A C statement to output to the stdio stream STREAM an assembler
   command to advance the location counter to a multiple of 2 to the
   POWER bytes.  POWER will be a C expression of type `int'.		*/

#define ASM_OUTPUT_ALIGN(STREAM, LOG)					\
  fprintf (STREAM, "\talign\t%d\n", LOG);


/*---------------------------------------------------------------------------
**
**	MACROS AFFECTING ALL DEBUGGING FORMATS
**
*/

/* A C expression that returns the DBX register number for the
   compiler register number REGNO.  In simple cases, the value of this
   expression may be REGNO itself.  But sometimes there are some
   registers that the compiler knows about and DBX does not, or vice
   versa.  In such cases, some register may need to have one number in
   the compiler and another for DBX.

   If two registers have consecutive numbers inside GNU CC, and they
   can be used as a pair to hold a multiword value, then they *must*
   have consecutive numbers after renumbering with
   `DBX_REGISTER_NUMBER'.  Otherwise, debuggers will be unable to
   access such a pair, because they expect register pairs to be
   consecutive in their own numbering scheme.

   If you find yourself defining `DBX_REGISTER_NUMBER' in way that
   does not preserve register pairs, then what you must do instead is
   redefine the actual register numbering scheme.			*/

#define DBX_REGISTER_NUMBER(REGNO) (REGNO)



/*---------------------------------------------------------------------------
**
**	MISCELLANEOUS PARAMETERS
**
*/

/* An alias for a machine mode name.  This is the machine mode that
   elements of a jump-table should have.				*/

#define CASE_VECTOR_MODE HImode


/* Define this macro if jump-tables should contain relative addresses.	*/
     
#define CASE_VECTOR_PC_RELATIVE
     

/* Define this to be the smallest number of different values for
   which it is best to use a jump-table instead of a tree of
   conditional branches.  The default is four for machines with a
   `casesi' instruction and five otherwise.  This is best for most
   machines.								*/

/* #define CASE_VALUES_THRESHOLD					*/


/* An alias for a tree code that should be used by default for
   conversion of floating point values to fixed point.  Normally,
   `FIX_ROUND_EXPR' is used.						*/

#define IMPLICIT_FIX_EXPR FIX_ROUND_EXPR


/* An alias for a tree code that is the easiest kind of division to
   compile code for in the general case.  It may be `TRUNC_DIV_EXPR',
   `FLOOR_DIV_EXPR', `CEIL_DIV_EXPR' or `ROUND_DIV_EXPR'.  These four
   division operators differ in how they round the result to an
   integer.  `EASY_DIV_EXPR' is used when it is permissible to use
   any of those kinds of division and the choice should be made on
   the basis of efficiency.						*/

#define EASY_DIV_EXPR TRUNC_DIV_EXPR


/* The maximum number of bytes that a single instruction can move
   quickly from memory to memory.					*/

#define MOVE_MAX 2


/* A C expression that is nonzero if on this machine the number of
   bits actually used for the count of a shift operation is equal to
   the number of bits needed to represent the size of the object
   being shifted.  When this macro is non-zero, the compiler will
   assume that it is safe to omit a sign-extend, zero-extend, and
   certain bitwise `and' instructions that truncates the count of a
   shift operation.  On machines that have instructions that act on
   bitfields at variable positions, which may include `bit test'
   instructions, a nonzero `SHIFT_COUNT_TRUNCATED' also enables
   deletion of truncations of the values that serve as arguments to
   bitfield instructions.

   If both types of instructions truncate the count (for shifts) and
   position (for bitfield operations), or if no variable-position
   bitfield instructions exist, you should define this macro.

   However, on some machines, such as the 80386 and the 680x0,
   truncation only applies to shift operations and not the (real or
   pretended) bitfield operations.  Define `SHIFT_COUNT_TRUNCATED' to
   be zero on such machines.  Instead, add patterns to the `md' file
   that include the implied truncation of the shift instructions.

   You need not define this macro if it would always have the value
   of zero.								*/

/* #define SHIFT_COUNT_TRUNCATED					*/


/* A C expression which is nonzero if on this machine it is safe to
   "convert" an integer of INPREC bits to one of OUTPREC bits (where
   OUTPREC is smaller than INPREC) by merely operating on it as if it
   had only OUTPREC bits.

   On many machines, this expression can be 1.

   When `TRULY_NOOP_TRUNCATION' returns 1 for a pair of sizes for
   modes for which `MODES_TIEABLE_P' is 0, suboptimal code can result.
   If this is the case, making `TRULY_NOOP_TRUNCATION' return 0 in
   such cases may improve things.					*/

#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1


/* An alias for the machine mode for pointers.  On most machines,
   define this to be the integer mode corresponding to the width of a
   hardware pointer; `SImode' on 32-bit machine or `DImode' on 64-bit
   machines.  On some machines you must define this to be one of the
   partial integer modes, such as `PSImode'.

   The width of `Pmode' must be at least as large as the value of
   `POINTER_SIZE'.  If it is not equal, you must define the macro
   `POINTERS_EXTEND_UNSIGNED' to specify how pointers are extended to
   `Pmode'.

   After generation of rtl, the compiler makes no further distinction
   between pointers and any other objects of this machine mode.  	*/

#define Pmode HImode


/* An alias for the machine mode used for memory references to
   functions being called, in `call' RTL expressions.  On most
   machines this should be `QImode'.					*/

#define FUNCTION_MODE QImode


/* Define this macro to control use of the character `$' in identifier
   names.  The value should be 0, 1, or 2.  0 means `$' is not allowed
   by default; 1 means it is allowed by default if `-traditional' is
   used; 2 means it is allowed by default provided `-ansi' is not
   used.  1 is the default; there is no need to define this macro in
   that case. 								*/

/*#define DOLLARS_IN_IDENTIFIERS 0 */


/* Define this macro if the assembler does not accept the character
   `$' in label names.  By default constructors and destructors in
   G++ have `$' in the identifiers.  If this macro is defined, `.' is
   used instead. 							*/

/*#define NO_DOLLAR_IN_LABEL */


/* Define this macro if the assembler does not accept the character
   `.' in label names.  By default constructors and destructors in G++
   have names that use `.'.  If this macro is defined, these names
   are rewritten to avoid `.'. 						*/

/* #define NO_DOT_IN_LABEL */


/*---------------------------------------------------------------------------
**
**	GLOBAL SYMBOLS IN HC1x.C
**
*/

extern int hc1x_mem_mode;	/* mode of current MEM reference */
extern char* HC1x_offset;	/* constant memory offset to add */

