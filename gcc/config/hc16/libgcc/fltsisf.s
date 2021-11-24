; $Id: fltsisf.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; fltsisf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Convert Long Integer to Single Float
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point calculator

	public	___hc16_floatsisf	; convert long integer to float
	extern	fp_push_long		; push long integer on float stack
	extern	fp_pop_float		; pop float from float stack


;----------------------------------------------------------------------------
;
;	___hc16_floatsisf	- convert long integer to single float
;
;	input:	0,s points to offset of arguments in stack frame
;		x points to stack frame
;	output:	none
;
___hc16_floatsisf
	pshm	d,e,x,y		; protect registers
	pshm	z,k		; save frame pointer

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; point to argument offsets in instruction stream
	lded	-4,z		; get return address...
	ande	#000Fh
	tedz			; ...into z

; push second argument as long integer
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	2-2,z		; point to argument
	jsr	fp_push_long	; push as long integer

; pop result into first argument
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	0-2,z		; point to argument
	jsr	fp_pop_float	; pop as float

; done, exit
	freea			; drop float stack

	pulm	z,k		; get original frame pointer
	lde	-2,z		; fix return address
	adde	#4
	ste	-2,z

	pulm	d,e,x,y		; recover registers
	rts

