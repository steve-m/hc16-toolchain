; $Id: modsi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; modsi.asm		 	   Copyright (C) 1997, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Find Modulus of Signed 32-Bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc12_modsi		; modulus of signed 32-bit integers
	extern	___hc12_si_setup	; set up for si operation
	extern	___hc12_si_2_cleanup	; clean up after si binary operation
	extern	___hc1x_udivmodsi	; 32-bit unsigned divide/modulus


;----------------------------------------------------------------------------
;
;	___hc12_modsi		- modulus of signed 32-bit integers
;
;	input:	return address points to byte indexes of target and sources
;		  relative to incoming stack frame
;	output:	target holds quotient
;
;	note:	requires ?? bytes stack
;
___hc12_modsi
	pshd				; protect registers
	pshx
	pshy
	jsr	___hc12_si_setup	; set up for operation
	leas	-5,s			; open stack frame

; capture sign
	ldaa	0,x			; get sign of dividend
	staa	4,s			; save it

	movw	0,y,0,s			; get copy of third argument
	movw	2,y,2,s

; make second argument positive
	tst	0,x			; argument positive?
	bpl	mod_1			; yes, go on

	leay	0,x			; negate argument
	jsr	neg_si

; make third argument positive
mod_1	tst	0,s			; argument positive?
	bpl	mod_2			; yes, go on

	leay	0,s			; negate argument
	jsr	neg_si

; divide second argument by third
mod_2	leay	0,s			; point to divisor
	jsr	___hc1x_udivmodsi	; do 32-bit unsigned divide/mod
	movw	0,y,0,x			; get remainder
	movw	2,y,2,x

; set sign of quotient
	tst	4,s			; dividend positive?
	bpl	mod_3			; yes, go on

	leay	0,x			; negate remainder
	jsr	neg_si

; done, exit
mod_3	leas	5,s			; close stack frame
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

