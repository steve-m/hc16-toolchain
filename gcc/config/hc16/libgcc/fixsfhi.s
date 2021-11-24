; $Id: fixsfhi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; fixsfhi.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Fix-Truncate Single Float to Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point calculator

	public	___hc16_fix_truncsfhi	; fix-truncate single float to int
	extern	fp_push_float		; push float on stack
	extern	fp_pop_int		; pop float as integer


;----------------------------------------------------------------------------
;
;	___hc16_fix_truncsfhi		- fix-truncate single float to int
;
;	input:	return address points to offset of argument in stack frame
;		x points to stack frame
;	output:	d holds result
;
___hc16_fix_truncsfhi
	pshm	e,x,y		; protect registers
	pshm	z,k		; save frame pointer

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; point to argument offsets in instruction stream
	lded	-4,z		; get return address...
	ande	#000Fh
	tedz			; ...into z

; push first argument, pop as int
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	0-2,z		; point to argument

	jsr	fp_push_float	; push argument as float
	jsr	fp_pop_int	; pop as integer

; done, exit
	freea			; drop float stack

	pulm	z,k		; get original frame pointer
	lde	-2,z		; fix return address
	adde	#2
	ste	-2,z

	pulm	e,x,y		; recover registers
	rts


	end

