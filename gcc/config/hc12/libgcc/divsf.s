; $Id: divsf.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; divsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Divide Single Floats
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package

	public	___hc12_divsf	; divide single floats
	extern	___hc12_sfsfsf	; perform trinary single float operation
	extern	fp_div		; floating point divide


;----------------------------------------------------------------------------
;
;	___hc12_divsf		- divide single floats
;
;	input:	0,s points to offsets of three arguments in stack frame
;		x points to stack frame
;	output:	first argument holds result
;
___hc12_divsf
	pshd				; protect register

	ldd	#fp_div			; point to handler
	jsr	___hc12_sfsfsf		; perform trinary operation

	puld				; recover register
	rts


	end

