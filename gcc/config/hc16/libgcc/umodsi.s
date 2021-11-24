; $Id: umodsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; umodsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Get Modulus of Unsigned 32-Bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc16_umodsi		; get modulus of unsigned 32-bit ints
	extern	___hc16_si_setup	; set up for si operation
	extern	___hc16_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc16_umodsi		- get modulus of unsigned 32-bit integers
;
;	input:	return address points to byte indexes of target and sources
;		  relative to incoming stack frame
;	output:	target holds quotient
;
;	note:	requires ?? bytes stack
;
___hc16_umodsi
	pshm	d,e,x,y			; protect registers
	jsr	___hc16_si_setup	; set up for operation

	lded	0,y			; push divisor
	pshm	e,d
	tsy				; point to it

	jsr	___hc1x_udivmodsi	; make quotient and remainder
	
	pulm	e,d			; get remainder
	sted	0,x

	jsr	___hc16_si_3_cleanup	; clean up after operation
	pulm	d,e,x,y			; recover registers
	rts


	end

