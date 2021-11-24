; $Id: float.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; float.asm		      Copyright (C) 1992-1994, Real-Time Systems Inc.
;------------------------------------------- All Rights Reserved ------------
;
;	Stack-Based Floating-Point Math Routines
;
;	This module implements a floating-point calculator.  All routines
;	assume that x points to the top entry in a floating-point data
;	stack.  Due to the use of a stack for operands an results, all
;	routines in this module are re-entrant.  The size of each entry 
;	in the stack is fp_siz, defined in float.mac.
;
;	The first group of routines push items to or pop items from the
;	stack.  The second group provide stack manipulation operations.
;	The final group perform the basic arithmetic operations.
;
;	Several error conditions are trapped by the arithmetic routines.
;	In all cases, the error conditions are converted into reasonable
;	values on the stack, which allows calculations to continue.
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	export	float.mac	; floating-point package

; structure of floating-point numbers on stack
	struc	fps_
sgn	ds	1		; sign and mantissa overflow byte
exp	ds	1		; biased exponent
man0	ds	1		; mantissa high byte
man1	ds	1		; mantissa high-mid byte
man2	ds	1		; mantissa low-mid byte
man3	ds	1		; mantissa low byte
nxt				; start of next entry on stack
	endst	fps_
	assume	fps_siz,fp_siz	; check stack entry size in header file

; constants
exp_bias	equ	7Fh	; exponent bias (exponent of 1.0)
err_over	equ	1	; floating point overflow error
err_under	equ	2	; floating point underflow error
err_div0	equ	3	; division by 0 error


;----------------------------------------------------------------------------
;
;	fp_push_float	- push a floating point number on float stack
;
;	input:	x points to floating-point stack
;		d points to number to push
;	action:	open one space on stack
;		convert number from IEEE format in memory to stack format
;		push number on stack
;	output:	top stack entry holds number in stack format
;
	cfunc	fp_push_float
	pshd			; protect registers
	pshy
	xgdy			; point y to number

; open up stack space for new number
	subx	#nxt		; decrement float-stack pointer

; handle incoming sign
	clr	sgn,x		; set up for positive number
	ldd	0,y		; get exponent and high byte of mantissa
        beq	push_f2		; zero?  just copy

        bpl	push_f1		; positive?  go on

	bset	sgn,x,#80h	; negative, set sign bit

; handle exponent and high byte of mantissa
push_f1	lsld			; move exponent completely into a
	lsrb			; restore positon of msbyte of mantissa
	orab	#10000000b	; restore most significant bit in mantissa
push_f2	std	exp,x		; put in accumulator

; handle low word of mantissa
	ldd	2,y		; get low word of mantissa
	std	man1,x		; put in to middle word of stack mantissa
	clr	man3,x		; zero-extend low order mantissa

; done, exit
	puly			; recover registers
	puld
	cendf


;----------------------------------------------------------------------------
;
;	fp_pop_float	- pop a floating point number from float stack
;
;	input:	x points to floating-point stack
;		d points to target for number
;	action:	pop number from stack
;		convert number from stack format to IEEE format in memory
;		remove empty space from stack
;	output:	top stack entry deleted
;
	cfunc	fp_pop_float
	pshd			; protect registers
	pshy
	xgdy			; point y to number

; handle exponent and high byte of mantissa, round result
	ldd	exp,x		; get exponent and high byte of mantissa
	beq	pop_f1		; zero?  just copy

	bset	man2,x,#1	; jam lsbit to make error more symmetrical

	lslb			; discard msb of mantissa
	lsrd			; combine with exponent

; handle sign
	tst	sgn,x		; number negative?
	bpl	pop_f1		; no, go on

	oraa	#10000000b	; yes, set sign bit
pop_f1	std	0,y		; put sign, exponent, and mant-high to target

; handle rest of mantissa
	ldd	man1,x		; get middle word of mantissa
	std	2,y		; put to target low word

; delete empty stack space
	addx	#nxt		; drop entry from stack

; done, exit
	puly			; recover registers
	puld
	cendf


;----------------------------------------------------------------------------
;
;	fp_push_uint	- push unsigned integer to float stack
;
;	input:	d holds unsigned integer
;	action:	open space on stack
;		put unsigned integer on stack, set scale and normalize
;	output:	top stack entry holds number in stack format
;
	cfunc	fp_push_uint
	subx	#nxt		; open space on stack

	std	man2,x		; put low word of mantissa
	clrw	man0,x		; zero-extend into high word

	jsr	long_float	; convert long on stack to float
	cendf


;----------------------------------------------------------------------------
;
;	fp_push_int	- push signed integer to float stack
;
;	input:	d holds signed integer
;	action:	open space on stack
;		put signed integer on stack, set scale and normalize
;	output:	top stack entry holds number in stack format
;
	cfunc	fp_push_int
	pshd			; protect register

	subx	#nxt		; open space on stack

	stab	man3,x		; put low byte of mantissa
	tab			; shift high byte to middle
	sxtb			; sign-extend
	std	man1,x		; put middle word of mantissa
	staa	man0,x		; put high byte

	jsr	long_float	; convert long in accum to float

	puld			; recover register
	cendf


;----------------------------------------------------------------------------
;
;	fp_push_long	- push long signed integer to float stack
;
;	input:	d points to 4-byte signed integer
;	action:	open space on stack
;		put long signed integer on stack, set scale and normalize
;	output:	top stack entry holds number in stack format
;
	cfunc	fp_push_long
	pshd			; protect registers
	pshy
	xgdy			; point y to number

	subx	#nxt		; open space on stack

	ldd	0,y		; get high word
	std	man0,x		; put in accumulator
	ldd	2,y		; get low word
	std	man2,x		; put in accumulator

	jsr	long_float	; convert long in accum to float

	puly			; recover registers
	puld
	cendf


;----------------------------------------------------------------------------
;
;	long_float	- convert long integer to float
;
;	input:	mantissa of top float-stack entry holds 4-byte integer
;	action:	set scale of number and normalize                                                   
;	output:	top stack entry holds floating-point number
;
long_float
	pshd			; protect register

; number negative?  make positive and note sign
	clr	sgn,x		; assume positive
	tst	man0,x		; test sign
	bpl	long_f1		; positive?  go on

	jsr	neg_top		; make mantissa positive, set sign bit
	bclr	sgn,x,#7Fh	; clear overflow bits

; convert to float
long_f1	clr	exp,x		; kill any exponent
	jsr	test_top	; number already 0?
	beq	long_f2		; yes, exit

	ldaa	#exp_bias+31	; get exponent of un-normalized long integer
	staa	exp,x		; initialize exponent
	jsr	norm_top	; normalize to floating-point number

; done, exit
long_f2	puld			; recover register
	rts


;-----------------------------------------------------------------------------
;
;	fp_pop_q15	- pop Q15 fraction from float stack
;
;	input:	x points to float stack
;	output:	d holds Q15 fraction
;
	cfunc	fp_pop_q15

; if too small, return zero
	ldab	exp,x		; get exponent
	subb	#exp_bias-15	; does number have bits in Q15 range?
	bhs	pop_q1		; yes, go on

	ldd	#0		; no, load zero...
	std	man0,x		; ...into mantissa
	std	man2,x
	bra	pop_q3		; go on

; if too large, force maximum Q15 value
pop_q1	subb	#31		; is number too large to be made Q15?
	bcs	pop_q2		; no, go on

	ldd	#0FFFFh		; load maximum long integer...
	std	man0,x		; ...into mantissa
	std	man2,x
	ldab	#-1		; only one shift required

; shift mantissa to proper position to represent integer
pop_q2	negb			; make number of shifts required
	jsr	denorm_top	; de-normalize number

	ldd	man2,x		; round low word
	adcd	#0
	std	man2,x
	ldd	man0,x		; round high word
	adcd	#0
	std	man0,x

; if number is negative, negate result
	tst	sgn,x		; number negative?
	bpl	pop_q3		; no, go on

	jsr	neg_top		; make result negative

; check for under/over range
pop_q3	ldd	man0,x		; get high word
	asr	man2,x		; get sign of low word
	rol	man2,x
	adcb	#0		; add to high word
	adca	#0
	cpd	#0		; out of range?
	bne	pop_q4		; yes, go load maximum

	ldd	man2,x		; get low word
	bra	pop_q5		; exit

pop_q4	ldd	#07FFFh		; get maximum integer
	tst	man0,x		; should be negative?
	bpl	pop_q5		; no, exit

	ldd	#-07FFFh		; make negative

pop_q5	addx	#nxt		; drop top stack entry
	cendf


;----------------------------------------------------------------------------
;
;	fp_pop_uint	- pop stack as unsigned integer
;
;	input:	x points to float on top of stack
;	action:	convert floating point value to unsigned integer
;	output:	d holds unsigned integer:
;		  0 if underrange, FFFF if overrange
;		top stack entry deleted
;
	cfunc	fp_pop_uint
	jsr	float_long	; convert top of stack to long integer

; check for under/over range
	ldd	man2,x		; get low word
	tstw	man0,x		; test high word
	beq	pop_u1		; in range?  exit

; out of range
	ldd	#0		; get underrange replacement value
	tst	man0,x		; test high byte
	bmi	pop_u1		; underrange?  go on

	ldd	#0FFFFh		; get overrange replacement value

; done, exit
pop_u1	addx	#nxt		; drop top stack entry
	cendf	


;----------------------------------------------------------------------------
;
;	fp_pop_int	- pop stack as signed integer
;
;	input:	x points to float on top of stack
;	action:	convert floating point value to signed integer
;	output:	d holds signed integer:
;		  -7FFFh if underrange, +7FFF if overrange
;		top stack entry deleted
;
	cfunc	fp_pop_int
	jsr	float_long	; convert accumulator to long integer

; check for under/over range
	ldd	man0,x		; get high word
	asr	man2,x		; get sign of low word
	rol	man2,x
	adcb	#0		; add to high word
	adca	#0
	cpd	#0		; out of range?
	bne	pop_i1		; yes, go load maximum

	ldd	man2,x		; get low word
	bra	pop_i2		; exit

pop_i1	ldd	#7FFFh		; get maximum integer
	tst	man0,x		; should be negative?
	bpl	pop_i2		; no, exit

	ldd	#-7FFFh		; make negative

pop_i2	addx	#nxt		; drop top stack entry
	cendf


;----------------------------------------------------------------------------
;
;	fp_pop_long	- pop stack as long signed integer
;
;	input:	x points to float on top of stack
;		d points to target for result
;	action:	convert floating point value to long signed integer
;	output:	d points to 4-byte signed integer:
;		  -7FFFFFFFh if underrange, 7FFFFFFF if overrange
;		top stack entry deleted
;
	cfunc	fp_pop_long
	pshd			; protect registers
	pshy
	xgdy			; point y to target

	jsr	float_long	; convert accumulator to long integer

	ldd	man0,x		; get high word
	std	0,y		; put it
	ldd	man2,x		; get low word
	std	2,y		; put it

	addx	#nxt		; drop top stack entry

	puly			; recover registers
	puld
	cendf


;----------------------------------------------------------------------------
;
;	float_long	- convert floating-point number to long integer
;
;	input:	x points to floating-point number on top of float-stack
;	action:	determine scale and denormalize
;	output:	mantissa of top float-stack entry holds 4-byte integer
;
float_long
	pshd			; protect register

; if too small, return zero
	ldab	exp,x		; get exponent
	subb	#exp_bias	; does number have an integer part?
	bhs	flt_l1		; yes, go on

	ldd	#0		; no, load zero...
	std	man0,x		; ...into mantissa
	std	man2,x
	bra	flt_l3		; exit

; if too large, force maximum integer
flt_l1	subb	#31		; is number too large to be made an integer?
	bcs	flt_l2		; no, go on

	ldd	#0FFFFh		; load maximum long integer...
	std	man0,x		; ...into mantissa
	std	man2,x
	ldab	#-1		; only one shift required

; shift mantissa to proper position to represent integer
flt_l2	negb			; make number of shifts required
	jsr	denorm_top	; de-normalize number

; if number is negative, negate result
	tst	sgn,x		; number negative?
	bpl	flt_l3		; no, go on

	jsr	neg_top		; make result negative

; done, exit
flt_l3	puld			; recover register
	rts


;----------------------------------------------------------------------------
;
;	fp_int		- drop fractional part of top float-stack entry
;
;	input:	top stack entry holds full floating-point number
;	action:	truncate fractional part of number
;	output:	top stack entry holds integer floating-point number
;
	cfunc	fp_int
	jsr	float_long	; convert to long integer
	jsr	long_float	; convert to float, less fractional part
	cendf


;----------------------------------------------------------------------------
;
;	fp_frac		- drop integer part of top float-stack entry
;
;	input:	top stack entry holds full floating-point number
;	action:	discard fractional part of number
;	output:	top stack entry holds fractional floating-point number
;
	cfunc	fp_frac
	jsr	fp_dup		; make a copy
	jsr	fp_int		; drop fractional part of copy
	jsr	fp_sub		; take difference
	cendf


;----------------------------------------------------------------------------
;
;	fp_swap		- exchange top two float-stack entries
;
;	input:	top two stack entries loaded as desired
;	action:	exchange contents of top two entries
;	output:	top two entries loaded
;
	cfunc	fp_swap
	pshd			; protect registers
	pshy

	ldd	0,x		; get sign bytes and exponents
	ldy	nxt+0,x
	sty	0,x		; put them
	std	nxt+0,x

	ldd	2,x		; get high words of mantissa
	ldy	nxt+2,x
	sty	2,x		; put them
	std	nxt+2,x

	ldd	4,x		; get low words of mantissa
	ldy	nxt+4,x
	sty	4,x		; put them
	std	nxt+4,x

	puly			; recover registers
	puld
	cendf	


;----------------------------------------------------------------------------
;
;	fp_dup		- duplicate and push top float-stack entry
;
;	input:	x points to float on top of stack
;	action:	make new stack entry, initialize with old top entry
;	output:	two entries on top hold same number
;
	cfunc	fp_dup
	pshd			; protect register

	subx	#nxt		; open space on stack

	ldd	nxt+0,x		; get sign byte and exponent
	std	0,x		; put it

	ldd	nxt+2,x		; get high word of mantissa
	std	2,x		; put it

	ldd	nxt+4,x		; get low word of mantissa
	std	4,x		; put it

	puld			; recover register
	cendf	


;----------------------------------------------------------------------------
;
;	fp_over		- duplicate and push second float-stack entry
;
;	input:	x points to float-stack, holding two or more entries
;	action:	make new stack entry, initialize with old second entry
;	output:	first and third entries on top hold same number
;
	cfunc	fp_over
	pshd			; protect register

	subx	#nxt		; open space on stack

	ldd	2*nxt+0,x	; get sign byte and exponent
	std	0,x		; put it

	ldd	2*nxt+2,x	; get high word of mantissa
	std	2,x		; put it

	ldd	2*nxt+4,x	; get low word of mantissa
	std	4,x		; put it

	puld			; recover register
	cendf	


;----------------------------------------------------------------------------
;
;	fp_drop		- pop and discard top float-stack entry
;
;	input:	x points to float-stack
;	action:	drop and discard top float-stack entry
;	output:	one less entry on stack
;
	cfunc	fp_drop
	addx	#nxt		; drop top entry
	cendf


;----------------------------------------------------------------------------
;
;	fp_tst		- compare top stack entry with zero
;
;	input:	top stack entry holds floating-point number
;	output:	flags indicate result of comparison
;		top stack entry deleted
;
;	note:	use with unsigned branches; signed branches give 
;		 incorrect results
;
	cfunc	fp_tst
	pshd			; protect register

	ldd	#0		; get zero
	jsr	fp_push_int
	jsr	fp_cmp		; compare number with zero

	puld			; recover register
	cendf


;----------------------------------------------------------------------------
;
;	fp_min		- return minimum of top two stack entries
;
;	This routine compares the top two stack entries and returns
;	the most negative of the two.
;
;	input:	x points to float stack holding two entries
;	output:	x points to float stack holding one entry
;
	cfunc	fp_min
	jsr	fp_over		; make copy of second entry
	jsr	fp_over		; make copy of first entry
	jsr	fp_cmp		; first entry lower?
	bls	fp_min1		; no, go on

	jsr	fp_swap		; hide first entry for return
fp_min1	jsr	fp_drop		; drop larger entry
	cendf


;----------------------------------------------------------------------------
;
;	fp_max		- return maximum of top two stack entries
;
;	This routine compares the top two stack entries and returns
;	the most positive of the two.
;
;	input:	x points to float stack holding two entries
;	output:	x points to float stack holding one entry
;
	cfunc	fp_max
	jsr	fp_over		; make copy of second entry
	jsr	fp_over		; make copy of first entry
	jsr	fp_cmp		; first entry higher?
	bhs	fp_max1		; no, go on

	jsr	fp_swap		; hide first entry for return
fp_max1	jsr	fp_drop		; drop larger entry
	cendf


;----------------------------------------------------------------------------
;
;	fp_cmp		- compare top two float-stack entries
;
;	input:	x points to stack holding two floating-point numbers
;	output:	both entries deleted
;		flags indicate second entry <op> first entry
;		
;	note:	use with unsigned branches; signed branches give 
;		 incorrect results
;
	cfunc	fp_cmp
	pshd			; protect registers

; drop both entries from stack
	pshx			; get copy of current stack pointer
	puld
	addd	#2*nxt		; find new stack pointer
	pshd			; save for return

; if both entries positive...
	ldaa	nxt+sgn,x	; both numbers positive?
	oraa	sgn,x
	bmi	fp_cmp1		; no, go on

; ...compare in normal order
	ldab	nxt+exp,x	; compare exponents
	cmpb	exp,x		; equal?
	bne	fp_cmp2		; no, exit

	ldd	nxt+man0,x	; compare high word of mantissas
	cpd	man0,x
	bne	fp_cmp2		; no, exit

	ldd	nxt+man2,x	; compare low word of mantissas
	cpd	man2,x
	bra	fp_cmp2		; exit

; if both entries negative...
fp_cmp1	ldaa	sgn,x		; compare signs
	cmpa	nxt+sgn,x	; both negative?
	bne	fp_cmp2		; no, exit

; ...compare in reverse order
	ldab	exp,x		; compare exponents
	cmpb	nxt+exp,x	; equal?
	bne	fp_cmp2		; no, exit

	ldd	man0,x		; compare high word of mantissas
	cpd	nxt+man0,x
	bne	fp_cmp2		; no, exit

	ldd	man2,x		; compare low word of mantissas
	cpd	nxt+man2,x

; convert flags to be usable with signed branches
fp_cmp2	tpa			; get flags
	anda	#11110101b	; kill minus and overflow
	bcc	fp_cmp3		; positive result?  go on

	oraa	#00001000b	; make negative result
fp_cmp3	tap			; restore flags

; done, exit
	pulx			; get new stack pointer
	puld			; recover registers
	cendf


;----------------------------------------------------------------------------
;
;	fp_neg		- negate top stack entry
;
;	input:	x points to stack holding floating-point number
;	output:	top entry negated
;		
	cfunc	fp_neg
	pshb			; protect register

	ldab	sgn,x		; get sign bit
	eorb	#10000000b	; flip it
	stab	sgn,x		; store it

	pulb			; recover register
	cendf


;----------------------------------------------------------------------------
;
;	fp_abs		- take absolute value of top stack entry
;
;	input:	top stack entry holds floating-point number
;	action:	negate top entry if negative
;	output:	top stack entry holds positive magnitude
;
	cfunc	fp_abs
	clr	sgn,x		; force top entry positive
	cendf


;----------------------------------------------------------------------------
;
;	fp_add		- add two numbers on top of float stack
;	fp_sub		- subtract top stack entry from second stack entry
;
;	input:	x points to stack holding two floating-point numbers
;	action:	if either term is zero:
;		    return the other term
;		if one term is far smaller than the other:
;		    return the other term
;		if terms have different scale:
;		    move smaller to top of stack
;		    denormalize top term to equate scales
;		convert both mantissas to twos-complement representation
;		add terms, including sign bytes bits
;		convert result back to unsigned representation
;		normalize result
;		drop remaining term
;		fixup overflow or underflow errors
;	output:	top of stack holds sum
;
	cfunc	fp_sub
	com	sgn,x		; negate top stack entry
	bclr	sgn,x,#7Fh	; kill overflow bits
	jsr	fp_add		; add terms
	cendf


	cfunc	fp_add                                                                       
	pshd			; protect register

; handle special zero cases
	jsr	test_top	; top of stack zero?
	bne	fp_a1		; no, go on

	clra			; yes, return second entry with no error
	bra	fp_a8		; exit

fp_a1	jsr	test_nxt	; second entry zero?
	bne	fp_a2		; no, go on

	jsr	fp_swap		; yes, return top stack entry
	clra			; no error
	bra	fp_a8		; exit

; check relative ranges:  handle trivial cases
fp_a2	ldab	nxt+exp,x	; get second exponent
	subb	exp,x		; find difference in exponents
	bhs	fp_a3		; second larger or equal scale to first?  go on

	negb			; invert exponent difference
	jsr	fp_swap		; get smaller scale number on top

fp_a3	cmpb	#31		; are numbers within range of each other?
	bls	fp_a4		; yes, go on

	clra			; no, return second entry with no error
	bra	fp_a8		; exit

; denormalize to equate exponents, convert mantissas to signed numbers
fp_a4	jsr	denorm_top	; denormalize top stack entry
	tst	sgn,x		; first number positive?
	bpl	fp_a5		; yes, go on

	jsr	neg_top		; make mantissa and sign byte negative

fp_a5	tst	nxt+sgn,x	; second number positive?
	bpl	fp_a6		; yes, go on

	jsr	neg_nxt		; make mantissa and sign byte negative

; add mantissas as signed 40-bit integers
fp_a6	ldd	man2,x		; add low words
	addd	nxt+man2,x
	std	nxt+man2,x	; store result

	ldd	man0,x		; add high words
	adcb	nxt+man1,x
	adca	nxt+man0,x
	std	nxt+man0,x	; store result

	ldab	sgn,x		; add overflow bytes
	adcb	nxt+sgn,x
	stab	nxt+sgn,x	; store result

; set sign of result
	bpl	fp_a7		; positive result?  go on

	jsr	neg_nxt		; negate mantissa and sign byte
	bset	nxt+sgn,x,#80h	; note sign of result

; normalize result
fp_a7	clra			; load success flag
	jsr	norm_nxt	; normalize result
	bcc	fp_a8		; no error?  exit

	ldaa	#err_under	; load error flag
	tst	nxt+exp,x	; underflow error?
	beq	fp_a8		; yes, exit

	ldaa	#err_over	; overflow error
	
; done, exit
fp_a8	jsr	fp_drop		; drop remaining input value
	jsr	fix_errors	; substitute values for errors

	puld			; recover register
	cendf


;----------------------------------------------------------------------------
;
;	fp_mul		- multiply top two float-stack entries                                
;
;	input:	x points to stack holding two floating-point numbers
;	action:	if either term is zero:
;		  return zero
;		determine sign of result
;		multiply mantissas as unsigned longs
;		normalize product if required
;		determine scale of result, trap overflows and underflows
;	output:	top of stack holds product
;                                                                            
	cfunc	fp_mul
	pshd			; protect register
	
; handle special zero cases
	jsr	test_top	; first factor zero?
	bne	fp_m1		; no, go on

	jsr	fp_swap		; get the zero
	clra			; no error
	jmp	fp_m5		; return the zero

fp_m1	jsr	test_nxt	; second factor zero?
	bne	fp_m2		; no, go on

	clra			; no error
	jmp	fp_m5		; return zero

; determine sign of result
fp_m2	ldaa	sgn,x		; get sign of first number
	eora	nxt+sgn,x	; combine with sign of second number
	staa	nxt+sgn,x	; store result

; multiply mantissas as unsigned longs
	jsr	umul_ll		; multiply as unsigned longs
	jsr	norm_nxt	; normalize if required

; determine scale of result, test for out-of-range results
	ldab	exp,x		; get first exponent
	clra			; ...into d
	addb	nxt+exp,x	; combine with second exponent
	adca	#0		; ...in d
	addd	#1		; compensate for representation of 1

; -- underflow?
	cpd	#exp_bias	; resulting number too small?
	bgt	fp_m3		; no, go on

	ldaa	#err_under	; exponent underflow error
	bra	fp_m5		; exit

; -- overflow?
fp_m3	cpd	#3*exp_bias	; resulting number too large?
	ble	fp_m4		; no, go on

	ldaa	#err_over	; exponent overflow error
	bra	fp_m5		; exit

; store resulting exponent, round result
fp_m4	subd	#exp_bias	; restore exponent bias
	stab	nxt+exp,x	; store result

	bset	nxt+man3,x,#1	; jam lsbit to make error more symmetrical

; done, exit
fp_m5	jsr	fp_drop		; drop remaining input value
	jsr	fix_errors	; substitute values for errors

	puld			; recover register
	cendf


;----------------------------------------------------------------------------
;
;	fp_div		- divide second stack entry by top entry
;
;	input:	x points to stack holding two floating-point numbers
;	action:	if top number is zero:
;		  return error
;		if next number is zero:
;		  return zero
;		determine sign of result
;		divide second mantissa by top mantissa as unsigned longs
;		 using the approximation:
;
;		    a	  .   a     b - c
;		 -------  =  --- * -------
;		  b + c       b       b
;
;		 where:	a = 32-bit dividend
;			b = msword of divisor
;			c = lsword of divisor
;
;		determine scale of result, trap overflows and underflows
;	output:	top of stack holds quotient
;                                                                            
	cfunc	fp_div
	pshd			; protect registers
	pshy

; handle special zero cases
	jsr	test_top	; dividing by zero?
	bne	fp_d1		; no, go on

	ldaa	#err_div0	; divide-by-zero error
	jmp	fp_d6		; exit

fp_d1	jsr	test_nxt	; dividend zero?
	bne	fp_d2		; no, go on

	clra			; just return zero dividend
	jmp	fp_d6		; exit

; determine sign of result
fp_d2	ldaa	sgn,x		; get sign of divisor
	eora	nxt+sgn,x	; combine with sign of dividend
	staa	nxt+sgn,x	; store result

; divide as unsigned longs
; - divide 32-bit dividend by msword of divisor
	ldd	man0,x		; get msword of divisor
	pshd			; save a copy
	txy			; point to dividend
	addy	#nxt
	jsr	udiv_lw		; divide dividend by msword of divisor
	jsr	norm_nxt	; normalize if required

; - divide modified divisor by msword of divisor
	ldd	man2,x		; get lsword of divisor
	beq	fp_d3		; zero?  go on

	negd			; subtract from divisor
	std	man2,x
	decw	man0,x		; propagate borrow

fp_d3	puld			; get original msword of divisor
	txy			; point to modified divisor
	jsr	udiv_lw		; divide modified divisor by msword of divisor

	ldab	exp,x		; get exponent before normalization
	jsr	norm_top	; normalize mantissa if required
	subb	exp,x		; get inverse of amount exponent changed
	aslb			; double it...
	addb	exp,x		; ...to reverse direction of exponent change 
	stab	exp,x		; save result

; - multiply results to get approximation of 32 x 32 divide
	jsr	umul_ll		; multiply partial quotients
	jsr	norm_nxt	; normalize if required

; determine scale of result, test for out-of-range results
	ldab	nxt+exp,x	; get dividend exponent
	clra			; ...into d
	subb	exp,x		; combine with divisor exponent
	sbca	#0		; ...in d
	subd	#1		; compensate for representation of 1

; -- underflow?
	cpd	#-exp_bias	; resulting number too small?
	bgt	fp_d4		; no, go on

	ldaa	#err_under	; exponent underflow error
	bra	fp_d6		; exit

; -- overflow?
fp_d4	cpd	#exp_bias	; resulting number too large?
	ble	fp_d5		; no, go on

	ldaa	#err_over	; exponent overflow error
	bra	fp_d6		; exit

; - store resulting exponent, round result
fp_d5	addd	#exp_bias	; restore exponent bias
	stab	nxt+exp,x	; store result

	bset	nxt+man3,x,#1	; jam lsbit to make error more symmetrical
	clra			; no error

; done, exit
fp_d6	jsr	fp_drop		; drop remaining input value
	jsr	fix_errors	; substitute values for errors

	puly			; recover registers
	puld
	cendf

 
;----------------------------------------------------------------------------
;
;	fp_mod		- get remainder from division
;
;	input:	x points to stack holding two floating-point numbers
;	action:	divide numbers, extract remainder
;	output:	top stack entry holds remainder
;
	cfunc	fp_mod
	jsr	fp_swap		; get numerator
	jsr	fp_over		; get denominator
	jsr	fp_div		; make full quotient
	jsr	fp_frac		; drop integer part of quotient
	jsr	fp_mul		; make remainder
	cendf


;----------------------------------------------------------------------------
;
;	umul_ll		- multiply two unsigned longs (fractional)
;
;	This routine uses the mul instruction to multiply two 32-bit
;	unsigned long fractions, yielding a 32-bit unsigned result.
;
;	The input parameters are assumed to be stored in the top two 
;	float-stack entries.  The result is returned in	second stack
;	entry, but may be denormalized to the right by one bit.
;
;	input:	x points to two float-stack entries holding unsigned
;		  long fractions
;	output:	x unchanged, second stack entry holds un-rounded, possibly
;		  denormalized result
;
umul_ll
	pshd			; 6 protect registers
	pshy			; 5

; make space on cpu stack for product
	ldy	#0		; 4 clear product
	pshy			; 5
	pshy			; 5
	pshy			; 5
	pshy			; 5
	tsy			; 4 point to it

; make partial product with 2^0 weight
	ldaa	man3,x		; 4 get multiplier
	ldab	man3+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	std	6,y		; 6 store result

; make partial product with 2^8 weight
	ldaa	man3,x		; 4 get multiplier
	ldab	man2+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	5,y		; 7 combine with previous
	std	5,y		; 6 store result

	ldaa	man2,x		; 4 get multiplier
	ldab	man3+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	5,y		; 7 combine with previous
	std	5,y		; 6 store result
	bcc	um_ll1		; 3 no carry?  go on

	inc	4,y		; 7 propagate carry

; make partial product with 2^16 weight
um_ll1	ldaa	man3,x		; 4 get multiplier
	ldab	man1+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	4,y		; 7 combine with previous
	std	4,y		; 6 store result

	ldaa	man2,x		; 4 get multiplier
	ldab	man2+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	4,y		; 7 combine with previous
	std	4,y		; 6 store result
	bcc	um_ll2		; 3 no carry?  go on

	inc	3,y		; 7 propagate carry

um_ll2	ldaa	man1,x		; 4 get multiplier
	ldab	man3+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	4,y		; 7 combine with previous
	std	4,y		; 6 store result
	bcc	um_ll3		; 3 no carry?  go on

	inc	3,y		; 7 propagate carry

; make partial product with 2^24 weight
um_ll3	ldaa	man3,x		; 4 get multiplier
	ldab	man0+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	3,y		; 7 combine with previous
	std	3,y		; 6 store result
	bcc	um_ll3a		; 3 no carry?  go on

	inc	2,y		; 7 propagate carry

um_ll3a	ldaa	man2,x		; 4 get multiplier
	ldab	man1+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	3,y		; 7 combine with previous
	std	3,y		; 6 store result
	bcc	um_ll4		; 3 no carry?  go on

	inc	2,y		; 7 propagate carry

um_ll4	ldaa	man1,x		; 4 get multiplier
	ldab	man2+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	3,y		; 7 combine with previous
	std	3,y		; 6 store result
	bcc	um_ll5		; 3 no carry?  go on

	inc	2,y		; 7 propagate carry

um_ll5	ldaa	man0,x		; 4 get multiplier
	ldab	man3+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	3,y		; 7 combine with previous
	std	3,y		; 6 store result
	bcc	um_ll6		; 3 no carry?  go on

	inc	2,y		; 7 propagate carry

; make partial product with 2^32 weight
um_ll6	ldaa	man2,x		; 4 get multiplier
	ldab	man0+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	2,y		; 7 combine with previous
	std	2,y		; 6 store result
	bcc	um_ll6a		; 3 no carry?  go on

	inc	1,y		; 7 propagate carry

um_ll6a	ldaa	man1,x		; 4 get multiplier
	ldab	man1+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	2,y		; 7 combine with previous
	std	2,y		; 6 store result
	bcc	um_ll7		; 3 no carry?  go on

	inc	1,y		; 7 propagate carry

um_ll7	ldaa	man0,x		; 4 get multiplier
	ldab	man2+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	2,y		; 7 combine with previous
	std	2,y		; 6 store result
	bcc	um_ll8		; 3 no carry?  go on

	inc	1,y		; 7 propagate carry

; make partial product with 2^40 weight
um_ll8	ldaa	man1,x		; 4 get multiplier
	ldab	man0+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	1,y		; 7 combine with previous
	std	1,y		; 6 store result
	bcc	um_ll8a		; 3 no carry?  go on

	inc	0,y		; 7 propagate carry

um_ll8a	ldaa	man0,x		; 4 get multiplier
	ldab	man1+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	1,y		; 7 combine with previous
	std	1,y		; 6 store result
	bcc	um_ll9		; 3 no carry?  go on

	inc	0,y		; 7 propagate carry

; make partial product with 2^48 weight
um_ll9	ldaa	man0,x		; 4 get multiplier
	ldab	man0+nxt,x	; 4 get multiplicand
	mul			; 10 multiply
	addd	0,y		; 7 combine with previous
	std	0,y		; 6 store result

; copy result
	ldd	0,y		; 6 get high word
	std	man0+nxt,x	; 5 put on float stack
	ldd	2,y		; 6 get low word
	std	man2+nxt,x	; 5 put on float stack

; done, exit
	tsy			; 4 point to stack
	addy	#8		; 12 drop product
	tys			; 4 update stack pointer

	puly			; 6 recover registers
	puld			; 8
	rts			; 5 = 709
	

;----------------------------------------------------------------------------
;
;	udiv_lw		- divide unsigned long by unsigned word (fractional)
;
;	This routine uses the fdiv instruction to divide a 32-bit
;	unsigned long fraction by a 16-bit unsigned word fraction.
;
;	The input parameters are assumed to be normalized (high bit set).
;	The input long is held in a float-stack entry; the input word is
;	held in a register.  The result is returned in the same float-stack
;	entry, but may be denormalized to the left by one bit.
;
;	input:	y points to float-stack entry holding normalized unsigned
;		  long fraction dividend 
;		d holds normalized unsigned word fraction divisor
;	output:	y points to result in input buffer
;
udiv_lw
	pshd			; 6 protect registers
	pshx			; 4

; divide msword of dividend by divisor
	tsx			; 3 point to stack frame
	ldd	man0,y		; 6 get msword of dividend
	cpd	2,x		; 7 greater than divisor?
	blo	ud_lw1		; 3 no, go on

	subd	2,x		; 6 take out one divisor
	inc	sgn,y		; 7 note overflow
	
ud_lw1	ldx	2,x		; 5 get divisor
	fdiv			; 41 make msword of partial quotient
	stx	man0,y		; 6 save it

	tsx			; 3 point to stack frame
	ldx	2,x		; 5 get divisor
	fdiv			; 41 make lsword of partial quotient
	pshx			; 4 save it

; divide lsword of dividend by divisor
	tsx			; 3 point to stack frame
	ldd	man2,y		; 6 get lsword of dividend
	cpd	4,x		; 7 greater than divisor?
	blo	ud_lw2		; 3 no, go on

	subd	4,x		; 6 take out one divisor
	inc	man1,y		; 7 overflow into byte 1
	bne	ud_lw2		; 3 no carry?  go on

	inc	man0,y		; 7 overflow into byte 0
ud_lw2	ldx	4,x		; 5 get divisor
	fdiv			; 41 make lsw of partial quotient

	xgdx			; 3 get result
	tsx			; 3 point to stack frame
	addd	0,x		; 6 combine partial quotients
	std	man2,y		; 6 save result

	ldd	man0,y		; 6 get high order quotient
	adcb	#0		; 2 propagate carry
	adca	#0		; 2
	std	man0,y		; 6 save result

; done, exit
	pulx			; 5 drop temporary
	pulx			; 5 recover registers
	puld			; 8
	rts			; 5 = 293


;----------------------------------------------------------------------------
;
;	norm_top	- normalize number on top of stack
;	norm_nxt	- normalize second number on stack
;
;	input:	x points to float stack
;	action:	if number = 0:
;		  exit
;		else if number >= 1.0
;		  shift number to right until overflow bits are zero
;		  increment exponent once for each shift
;		else if number < 0.5
;		  shift number to left until high bit of mantissa = 1
;		  decrement exponent once for each shift
;	output:	carry clear:  normalized number on float stack
;		carry set:    number too small or too large to normalize
;
norm_nxt
	pshx			; protect stack pointer
	addx	#nxt		; treat second number as top
	bsr	norm_top	; normalize it
	pulx			; recover stack pointer
	rts

norm_top
	pshd				; protect register

; zero?  normalization has no meaning
	bsr	test_top		; number zero?
	clc				; (no error)
	beq	norm_t5			; yes, exit

; if number >= 1.0, shift mantissa to right as required
	ldd	man0,x			; get high word of mantissa
norm_t1	brclr	sgn,x,#7Fh, norm_t2	; no overflow?  go on

	asr	sgn,x			; shift overflow byte...
	bclr	sgn,x,#40h		; (kill spurious bit)
	rord				; ...into high word...
	ror	man2,x			; ...into next byte...
	ror	man3,x			; ...into low byte...

	inc	exp,x			; increment exponent for each shift
	brset	exp,x,#0FFh, norm_t3	; exponent overflow?  abort
	bra	norm_t1			; loop

; if number < 0.5, shift mantissa until high bit set
norm_t2	tsta				; number normalized?
	bmi	norm_t4			; yes, exit

	lsl	man3,x			; shift low byte...
	rol	man2,x			; ...into next byte
	rold				; ...into high word

	dec	exp,x			; decrement exponent for each shift
	bne	norm_t2			; still ok?  loop

; done, return result
norm_t3	sec				; too small or too large to normalize
norm_t4	std	man0,x			; store high word result
norm_t5	puld				; recover register
	rts


;----------------------------------------------------------------------------
;
;	denorm_top	- de-normalize top stack entry
;
;	input:	x points to float stack
;		b holds number of right-shifts required
;	action:	update exponent of top stack entry, shift mantissa to right
;	output:	none
;
denorm_top
	pshd			; protect register

	tba			; get copy of number of shifts
	beq	de_t2		; none required?  exit

	adda	exp,x		; correct exponent
	staa	exp,x		; save result

de_t1	lsr	man0,x		; shift high byte of mantissa...
	ror	man1,x		; ...into high-middle...
	ror	man2,x		; ...into low-middle...
	ror	man3,x		; ...into low
	decb			; done all shifts?
	bne	de_t1		; no, loop

de_t2	puld			; recover register
	rts


;----------------------------------------------------------------------------
;
;	test_top	- zero-test top float-stack entry
;
;	input:	x points to float stack
;	action:	test top number for zero, ignoring only sign bit
;	output:	flags = eq if number = 0
;
test_top
	pshd			; protect register

	ldd	sgn,x		; get overflow and exponent
	anda	#01111111b	; kill sign bit
	cpd	#0		; non-zero?
	bne	test_t1		; yes, exit

	ldd	man0,x		; test high word of mantissa
	bne	test_t1		; non-zero?  exit

	ldd	man2,x		; test low word of mantissa

test_t1	puld			; recover register
	rts


;----------------------------------------------------------------------------
;
;	test_nxt	- zero-test second float-stack entry
;
;	input:	x points to float stack
;	action:	test second number for zero, ignoring only sign bit
;	output:	flags = eq if number = 0
;
test_nxt
	pshd			; protect register

	ldd	nxt+sgn,x	; get overflow and exponent
	anda	#01111111b	; kill sign bit
	cpd	#0		; non-zero?
	bne	test_n1		; yes, exit

	ldd	nxt+man0,x	; test high word of mantissa
	bne	test_n1		; non-zero?  exit

	ldd	nxt+man2,x	; test low word of mantissa

test_n1	puld			; recover register
	rts


;----------------------------------------------------------------------------
;
;	neg_top		- negate mantissa of top float-stack entry
;	neg_nxt		- negate mantissa of second float-stack entry
;
;	input:	x points to float stack holding valid 39-bit number
;	action:	negate mantissa of specified entry
;		extend mantissa sign into sign byte, destroying original 
;		 sign bit
;	output:	none
;
neg_nxt
	pshx			; protect stack pointer
	addx	#nxt		; treat second number as top
	bsr	neg_top		; negate it
	pulx			; recover stack pointer
	rts

neg_top
	pshd			; protect register

	ldd	man2,x		; get low word
	comb			; complement it
	coma
	com	man1,x		; complement high word
	com	man0,x
	com	sgn,x		; complement overflow byte

	addd	#1		; negate low word
	std	man2,x		; store result

	ldd	man0,x		; get high word
	adcb	#0		; propagate carry
	adca	#0
	std	man0,x		; store result

	ldab	sgn,x		; get overflow byte
	adcb	#0		; propagate carry
	aslb			; fix high bit
	asrb
	stab	sgn,x		; store result

	puld			; recover register
	rts


;----------------------------------------------------------------------------
;
;	fix_errors	- convert error codes to values in top stack entry
;
;	input:	a = 0 if no error
;		else a holds small integer error code
;	action:	for underflows:
;		    replace top stack entry with zero
;		for overflows and divide-by-zeros:
;		    replace top stack entry with maximum positive or negative
;	output:	top stack entry holds reasonable number
;
fix_errors
	pshm	d,z,k		; protect registers
	ldab	#0		; point to z to zero page
	tbzk	

	tsta			; error?
	beq	fix_e3		; no, exit

	ldab	sgn,x		; get sign of result
	andb	#10000000b	; kill overflow bits
	aba			; combine with error code

	ldz	#error_tbl	; point to table of results to substitute
	ldab	#error_siz	; size of each entry
fix_e1	cmpa	0,z		; found error?
	beq	fix_e2		; yes, go on

	abz			; next entry
	cpz	#error_end	; done all?
	blo	fix_e1		; no, loop
	
fix_e2	ldd	1,z		; get sign byte and exponent
	std	sgn,x
	ldd	3,z		; get high word of mantissa
	std	man0,x	
	ldd	5,z		; get low word of mantissa
	std	man2,x

;	include	string.mac	; get string-handling definitions
;	aiz	#+err_val_siz	; point to message
;	jsr	put_string_z	; show it

fix_e3	pulm	d,z,k		; recover registers
	rts


; create error value and message table entry
error	macro	code,sgn,exp,man0,man1,man2,man3,msg
	db	code				; error code
	db	sgn,exp,man0,man1,man2,man3	; value to subsititute
	db	msg,0				; message to display
	endm

	const

error_tbl
	error	err_under,	00h,000h, 000h,000h,000h,000h,' PU',0  ; + underflow
	error	err_under+80h,  00h,000h, 000h,000h,000h,000h,' NU',0  ; - underflow
	error	err_over,	00h,0FEh, 0FFh,0FFh,0FFh,0FFh,' PO',0  ; + overflow
	error	err_over+80h,   80h,0FEh, 0FFh,0FFh,0FFh,0FFh,' NO',0  ; - overflow
	error	err_div0,	00h,0FEh, 0FFh,0FFh,0FFh,0FFh,' PZ',0  ; + div by 0
	error	err_div0+80h,   80h,0FEh, 0FFh,0FFh,0FFh,0FFh,' NZ',0  ; - div by 0
error_end
	error	0,		00h,000h, 000h,000h,000h,000h,' ??',0  ; unknown error
err_val_siz	equ	7		; size of value part of error entry
error_siz	equ	*-error_end	; size of entire error entry

	align	1
	code


	end

