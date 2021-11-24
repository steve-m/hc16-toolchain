; $Id: subsf.s,v 1.1 2002/09/08 20:40:20 querbach Exp $

; subsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Subtract Single Floats
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package

	public	___hc12_subsf	; subtract single floats
	extern	___hc12_sfsfsf	; perform trinary single float operation
	extern	fp_sub		; floating point subtract


;----------------------------------------------------------------------------
;
;	___hc12_subsf		- subtract single floats
;
;	input:	0,s points to offsets of three arguments in stack frame
;		x points to stack frame
;	output:	first argument holds result
;
___hc12_subsf
	pshd				; protect register

	ldd	#fp_sub			; point to handler
	jsr	___hc12_sfsfsf		; perform trinary operation

	puld				; recover register
	rts


	end

