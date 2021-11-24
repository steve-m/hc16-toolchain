; $Id: mulsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; mulsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Multiply Signed 32-Bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc16_mulsi		; multiply signed 32-bit integers
	extern	___hc16_si_setup	; set up for si operation
	extern	___hc16_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc16_mulsi		- multiply signed 32-bit integers
;
;	input:	return address points to byte indexes of target and sources
;		  relative to incoming stack frame
;	output:	target holds product
;
;	note:	requires ?? bytes stack
;
___hc16_mulsi
	pshm	d,e,x,y			; protect registers
	jsr	___hc16_si_setup	; set up for operation
	pshm	z			; protect frame pointer
	ais	#-6			; open stack frame
	tsz				; point to it

; capture sign
	ldaa	0,x			; get sign of second argument
	eora	0,y			; get sign of product
	staa	4,z			; save it

; make second argument positive
	tst	0,x			; argument positive?
	bpl	mul_1			; yes, go on

	xgxy				; negate argument
	jsr	neg_si
	xgxy

; make third argument positive
mul_1	tst	0,y			; argument positive?
	bpl	mul_2			; yes, go on

	jsr	neg_si

; multiply second and third arguments
mul_2	ldd	2,x			; make partial product with 2^0 weight
	lde	2,y
	emul
	sted	0,z

	ldd	0,x			; make partial product with 2^16 weight
	lde	2,y
	emul
	addd	0,z
	std	0,z	

	ldd	2,x			; make partial product with 2^16 weight
	lde	0,y
	emul
	addd	0,z
	std	0,z	

; store unsigned product
	lded	0,z			; store product
	sted	0,x

; set sign of product
	tst	4,z			; product positive?
	bpl	mul_3			; yes, go on

	txy				; negate product
	jsr	neg_si

; done, exit
mul_3	ais	#+6			; close stack frame
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

