; $Id: abssf.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; abssf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Take Absolute Value of Single Float
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package

	public	___hc12_abssf	; take absolute value of single float
	extern	___hc12_sfsf	; perform binary single float operation
	extern	fp_abs		; floating point absolute value


;----------------------------------------------------------------------------
;
;	___hc12_abssf		- take absolute value of single float
;
;	input:	0,s points to offsets of two arguments in stack frame
;		x points to stack frame
;	output:	first argument holds result
;
___hc12_abssf
	pshd				; protect register

	ldd	#fp_abs			; point to handler
	jsr	___hc12_sfsf		; perform trinary operation

	puld				; recover register
	rts


	end

