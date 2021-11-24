; $Id: cmpsf.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; cmpsf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Compare Single Floats
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	import	float.mac	; floating point calculator

	public	___hc16_cmpsf	; compare two single floats
	extern	fp_cmp		; floating point compare


;----------------------------------------------------------------------------
;
;	___hc16_cmpsf		- compare two single floats
;
;	input:	0,s points to offsets of two arguments in stack frame
;		x points to stack frame
;	output:	flags hold result
;
___hc16_cmpsf
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

; push second argument
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	2-2,z		; point to argument
	jsr	fp_push_float	; push argument

; compare floats
	jsr	fp_cmp		; compare floats
	tpa			; save result

; done, exit
	freea			; drop float stack

	pulm	z,k		; recover original frame pointer
	lde	-2,z		; fix return address
	adde	#4
	ste	-2,z

	tap			; recover result
	pulm	d,e,x,y		; recover registers
	rts


	end

