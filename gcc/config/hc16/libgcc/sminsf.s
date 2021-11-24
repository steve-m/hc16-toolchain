; $Id: sminsf.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; sminsf.asm			   Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Find Minimum of Two Single Floats
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package

	public	___hc16_sminsf	; find minimum of two single floats
	extern	___hc16_sfsf	; perform binary single float operation
	extern	fp_min		; floating point minimize


;----------------------------------------------------------------------------
;
;	___hc16_sminsf		- find minimum of two single floats
;
;	input:	0,s points to offsets of two arguments in stack frame
;		x points to stack frame
;	output:	first argument holds result
;
___hc16_sminsf
	pshd				; protect register

	ldd	#fp_min			; point to handler
; FIXME need more float stack:
	jsr	___hc16_sfsf		; perform trinary operation

	puld				; recover register
	rts


	end

