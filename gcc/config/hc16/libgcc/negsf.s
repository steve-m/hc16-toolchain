; $Id: negsf.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; negsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Negate Single Float
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package

	public	___hc16_negsf	; negate single float
	extern	___hc16_sfsf	; perform binary single float operation
	extern	fp_neg		; floating point negate


;----------------------------------------------------------------------------
;
;	___hc16_negsf		- negate single float
;
;	input:	0,s points to offsets of two arguments in stack frame
;		x points to stack frame
;	output:	first argument holds result
;
___hc16_negsf
	pshd				; protect register

	ldd	#fp_neg			; point to handler
	jsr	___hc16_sfsf		; perform trinary operation

	puld				; recover register
	rts


	end

