; $Id: fltusisf.s,v 1.2 2014/05/30 03:01:41 querbach Exp $

; fltusisf.asm		           Copyright (C) 2008, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Convert Unsigned Long Integer to Single Float
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point calculator

	public	___hc12_floatunssisf	; convert long integer to float
	extern	fp_push_ulong		; push unsigned long on float stack
	extern	fp_pop_float		; pop float from float stack


;----------------------------------------------------------------------------
;
;	___hc12_floatunssisf	- convert unsigned long to single float
;
;	input:	0,s points to offset of arguments in stack frame
;		x points to stack frame
;	output:	none
;
___hc12_floatunssisf
	pshd			; protect registers
	pshx
	pshy

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; push second argument as unsigned long integer
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	2,y		; point to second argument

	jsr	fp_push_ulong	; push as unsigned long

; pop result into first argument
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	0,y		; point to first argument

	jsr	fp_pop_float	; pop as float

; done, exit
	tsy			; point to stack frame
	ldd	aa_siz+6,y	; point to target and source indexes
	addd	#4		; fix return address
	std	aa_siz+6,y

	freea			; drop float stack
	puly			; recover registers
	pulx
	puld
	rts


	end

