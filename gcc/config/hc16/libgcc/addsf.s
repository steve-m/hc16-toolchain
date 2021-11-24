; $Id: addsf.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; addsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Add Single Floats
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package

	public	___hc16_addsf	; add single floats
	extern	___hc16_sfsfsf	; perform trinary single float operation
	extern	fp_add		; floating point add


;----------------------------------------------------------------------------
;
;	___hc16_addsf		- add single floats
;
;	input:	0,s points to offsets of three arguments in stack frame
;		x points to stack frame
;	output:	first argument holds result
;
___hc16_addsf
	pshd				; protect register

	ldd	#fp_add			; point to handler
	jsr	___hc16_sfsfsf		; perform trinary operation

	puld				; recover register
	rts


	end

