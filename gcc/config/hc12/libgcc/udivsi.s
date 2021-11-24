; $Id: udivsi.s,v 1.1 2002/09/08 20:40:20 querbach Exp $

; udivsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Divide Unsigned 32-Bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc12_udivsi		; divide unsigned 32-bit integers
	extern	___hc12_si_setup	; set up for si operation
	extern	___hc12_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc12_udivsi		- divide unsigned 32-bit integers
;
;	input:	return address points to byte indexes of target and sources
;		  relative to incoming stack frame
;	output:	target holds quotient
;
;	note:	requires ?? bytes stack
;
___hc12_udivsi
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
	
	pulx				; drop remainder
	pulx

	jsr	___hc12_si_3_cleanup	; clean up after operation
	puly				; recover registers
	pulx
	puld
	rts


	end

