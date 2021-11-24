; $Id: cmpsf.s,v 1.2 2014/05/30 03:01:41 querbach Exp $

; cmpsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Compare Single Floats
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	import	float.mac	; floating point calculator

	public	___hc12_cmpsf	; compare two single floats
	extern	fp_cmp		; floating point compare


;----------------------------------------------------------------------------
;
;	___hc12_cmpsf		- compare two single floats
;
;	input:	0,s points to offsets of two arguments in stack frame
;		x points to stack frame
;	output:	flags hold result
;
___hc12_cmpsf
	pshd			; protect registers
	pshx
	pshy

; make float stack
	tsx			; point to top of float stack
	alloca	2*fp_siz	; make space for float stack

; push first argument
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	0,y		; point to first argument

	jsr	fp_push_float	; push argument

; push second argument
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	2,y		; point to second argument

	jsr	fp_push_float	; push argument

; compare floats
	jsr	fp_cmp		; compare floats
	tpa			; save result

; done, exit
	xgdy
	tsx			; point to stack frame
	ldd	aa_siz+6,x	; point to target and source indexes
	addd	#4		; fix return address
	std	aa_siz+6,x
	xgdy

	freea			; drop float stack
	tap			; recover result
	puly			; recover registers
	pulx
	puld
	rts


	end

