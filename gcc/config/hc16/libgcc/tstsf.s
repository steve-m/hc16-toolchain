; $Id: tstsf.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; tstsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Zero-Test Single Float
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	import	float.mac	; floating point calculator

	public	___hc16_tstsf	; zero-test single float
	extern	fp_tst		; floating point compare


;----------------------------------------------------------------------------
;
;	___hc16_tstsf		- zero-test single float
;
;	input:	0,s points to offset of argument in stack frame
;		x points to stack frame
;	output:	flags hold result
;
___hc16_tstsf
	pshm	d,e,x,y		; protect registers
	pshm	z,k		; save frame pointer

; make float stack
	tsx			; point to top of float stack
	alloca	2*fp_siz	; make space for float stack

; point to argument offsets in instruction stream
	lded	-4,z		; get return address...
	ande	#000Fh
	tedz			; ...into z

; push first argument
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	0-2,z		; point to argument
	jsr	fp_push_float	; push argument

; zero-test float
	jsr	fp_tst		; zero-test float
	tpa			; save result

; done, exit
	freea			; drop float stack

	pulm	z,k		; recover original frame pointer
	lde	-2,z		; fix return address
	adde	#2
	ste	-2,z

	tap			; recover result
	pulm	d,e,x,y		; recover registers
	rts


	end

