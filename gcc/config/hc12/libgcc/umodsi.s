; $Id: umodsi.s,v 1.1 2002/09/08 20:40:20 querbach Exp $

; umodsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Get Modulus of Unsigned 32-Bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc12_umodsi		; get modulus of unsigned 32-bit ints
	extern	___hc12_si_setup	; set up for si operation
	extern	___hc12_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc12_umodsi		- get modulus of unsigned 32-bit integers
;
;	input:	return address points to byte indexes of target and sources
;		  relative to incoming stack frame
;	output:	target holds quotient
;
;	note:	requires ?? bytes stack
;
___hc12_umodsi
	pshd				; protect registers
	pshx
	pshy
	jsr	___hc12_si_setup	; set up for operation

	ldd	2,y			; push divisor
	pshd
	ldd	0,y
	pshd
	tsy				; point to it

	jsr	___hc1x_udivmodsi	; make quotient and remainder
	
	puld				; get remainder
	std	0,x
	puld
	std	2,x

	jsr	___hc12_si_3_cleanup	; clean up after operation
	puly				; recover registers
	pulx
	puld
	rts


	end

