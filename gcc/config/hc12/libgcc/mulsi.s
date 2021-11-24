; $Id: mulsi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; mulsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Multiply Signed 32-Bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc12_mulsi		; multiply signed 32-bit integers
	extern	___hc12_si_setup	; set up for si operation
	extern	___hc12_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc12_mulsi		- multiply signed 32-bit integers
;
;	input:	return address points to byte indexes of target and sources
;		  relative to incoming stack frame
;	output:	target holds product
;
;	note:	requires ?? bytes stack
;
___hc12_mulsi
	pshd				; protect registers
	pshx
	pshy
	jsr	___hc12_si_setup	; set up for operation
	leas	-9,s			; open stack frame

; capture sign
	ldaa	0,x			; get sign of second argument
	eora	0,y			; get sign of product
	staa	8,s			; save it

	movw	0,y,0,s			; get copy of third argument
	movw	2,y,2,s

; make second argument positive
	tst	0,x			; argument positive?
	bpl	mul_1			; yes, go on

	leay	0,x			; negate argument
	jsr	neg_si

; make third argument positive
mul_1	tst	0,s			; argument positive?
	bpl	mul_2			; yes, go on

	leay	0,s			; negate argument
	jsr	neg_si

; multiply second and third arguments
mul_2	ldd	2,x			; make partial product with 2^0 weight
	ldy	2,s
	emul
	sty	4,s
	std	6,s

	ldd	0,x			; make partial product with 2^16 weight
	ldy	2,s
	emul
	addd	4,s
	std	4,s	

	ldd	2,x			; make partial product with 2^16 weight
	ldy	0,s
	emul
	addd	4,s
	std	4,s	

; store unsigned product
	movw	4,s,0,x			; store product
	movw	6,s,2,x

; set sign of product
	tst	8,s			; product positive?
	bpl	mul_3			; yes, go on

	leay	0,x			; negate product
	jsr	neg_si

; done, exit
mul_3	leas	9,s			; close stack frame
	jsr	___hc12_si_3_cleanup	; clean up after operation
	puly				; recover registers
	pulx
	puld
	rts


;-----------------------------------------------------------------------------
;
;	neg_si		- negate si variable in memory
;
;	input:	y points to variable to negate
;	output:	none
;
neg_si
	pshd			; protect register

	com	0,y		; complement high word
	com	1,y

	ldd	2,y		; negate low word
	comd
	addd	#1
	std	2,y

	ldd	0,y		; propagate carry
	adcb	#0
	adca	#0
	std	0,y

	puld			; recover register
	rts


	end

