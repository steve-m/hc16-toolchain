; $Id: fixsfsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; fixsfsi.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Fix-Truncate Single Float to Long Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point calculator

	public	___hc16_fix_truncsfsi	; fix-truncate single float to long
	extern	fp_push_float		; push float on stack
	extern	fp_pop_long		; pop float as long integer


;----------------------------------------------------------------------------
;
;	___hc16_fix_truncsfsi		- fix-truncate single float to long
;
;	input:	0,s points to offset of arguments in stack frame
;		x points to stack frame
;	output:	d holds result
;
___hc16_fix_truncsfsi
	pshm	d,e,x,y		; protect registers
	pshm	z,k		; save frame pointer

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; point to argument offsets in instruction stream
	lded	-4,z		; get return address...
	ande	#000Fh
	tedz			; ...into z

; push second argument as float
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	2-2,z		; point to argument
	jsr	fp_push_float	; push argument as float

; pop into first argument as long
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	0-2,z		; point to argument
	jsr	fp_pop_long	; pop as long integer

; done, exit
	freea			; drop float stack

	pulm	z,k		; get original frame pointer
	lde	-2,z		; fix return address
	adde	#4
	ste	-2,z

	pulm	d,e,x,y		; recover registers
	rts


	end

	end

