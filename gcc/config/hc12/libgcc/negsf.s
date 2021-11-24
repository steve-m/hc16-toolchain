; $Id: negsf.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; negsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Negate Single Float
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package

	public	___hc12_negsf	; negate single float
	extern	___hc12_sfsf	; perform binary single float operation
	extern	fp_neg		; floating point negate


;----------------------------------------------------------------------------
;
;	___hc12_negsf		- negate single float
;
;	input:	0,s points to offsets of two arguments in stack frame
;		x points to stack frame
;	output:	first argument holds result
;
___hc12_negsf
	pshd				; protect register

	ldd	#fp_neg			; point to handler
	jsr	___hc12_sfsf		; perform trinary operation

	puld				; recover register
	rts


	end

