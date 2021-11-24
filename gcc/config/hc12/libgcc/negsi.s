; $Id: negsi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; negsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Negate 32-Bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc12_negsi		; negate 32-bit integer
	extern	___hc12_si_setup	; set up for si operation
	extern	___hc12_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc12_negsi		- negate 32-bit integer
;
;	input:	return address points to byte indexes of target and source
;		  relative to incoming stack frame
;	output:	target holds negated copy of source
;
___hc12_negsi
	pshd				; protect registers
	pshx
	pshy
	jsr	___hc12_si_setup	; set up for operation

	com	0,x			; complement high word
	com	1,x

	ldd	2,x			; negate low word
	coma
	comb
	addd	#1
	std	2,x

	ldd	0,x			; propagate carry
	adcb	#0
	adca	#0
	std	0,x

	jsr	___hc12_si_2_cleanup	; clean up after operation
	puly				; recover registers
	pulx
	puld
	rts


	end

