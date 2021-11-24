; $Id: divsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; divsi.asm		 	   Copyright (C) 1997, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Divide Signed 32-Bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc16_divsi		; divide signed 32-bit integers
	extern	___hc16_si_setup	; set up for si operation
	extern	___hc16_si_2_cleanup	; clean up after si binary operation
	extern	___hc1x_udivmodsi	; 32-bit unsigned divide/modulus


;----------------------------------------------------------------------------
;
;	___hc16_divsi		- divide signed 32-bit integers
;
;	input:	return address points to byte indexes of target and sources
;		  relative to incoming stack frame
;	output:	target holds quotient
;
;	note:	requires ?? bytes stack
;
___hc16_divsi
	pshm	d,e,x,y			; protect registers
	jsr	___hc16_si_setup	; set up for operation
	pshm	z			; protect frame pointer
	ais	#-6			; open stack frame
	tsz

; capture sign
	ldaa	0,x			; get sign of second argument
	eora	0,y			; get sign of quotient
	staa	4,z			; save it

	lded	0,y			; get copy of third argument
	sted	0,z

; make second argument positive
	tst	0,x			; argument positive?
	bpl	div_1			; yes, go on

	txy				; negate argument
	jsr	neg_si

; make third argument positive
div_1	tst	0,z			; argument positive?
	bpl	div_2			; yes, go on

	tzy				; negate argument
	jsr	neg_si

; divide second argument by third
div_2	tzy				; point to divisor
	jsr	___hc1x_udivmodsi	; do 32-bit unsigned divide/mod

; set sign of quotient
	tst	4,z			; quotient positive?
	bpl	div_3			; yes, go on

	txy				; negate quotient
	jsr	neg_si

; done, exit

div_3	ais	#+6			; close stack frame
	pulm	z			; recover frame pointer
	jsr	___hc16_si_3_cleanup	; clean up after operation
	pulm	d,e,x,y			; recover registers
	rts


;-----------------------------------------------------------------------------
;
;	neg_si		- negate si variable in memory
;
;	input:	y points to variable to negate
;	output:	none
;
neg_si
	pshm	e,d		; protect register

	lded	0,y		; get variable

	come			; complement it
	comd
	addd	#1		; increment it
	adce	#0

	sted	0,y		; store result

	pulm	e,d		; recover register
	rts
	

	end

