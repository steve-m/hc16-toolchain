; $Id: flthisf.s,v 1.2 2014/05/30 03:01:41 querbach Exp $

; flthisf.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Convert Integer to Single Float
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point calculator

	public	___hc12_floathisf	; convert integer to float
	extern	fp_push_int		; push integer on float stack
	extern	fp_pop_float		; pop float from float stack


;----------------------------------------------------------------------------
;
;	___hc12_floathisf	- convert integer to single float
;
;	input:	0,s points to offset of target in stack frame
;		x points to stack frame
;		d holds integer to convert
;	output:	target holds result
;
___hc12_floathisf
	pshd			; protect registers
	pshx
	pshy

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; push input integer
	jsr	fp_push_int	; push integer on float stack

; pop result into first argument
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	0,y		; point to first argument

	jsr	fp_pop_float	; pop as float

; done, exit
	tsy			; point to stack frame
	ldd	aa_siz+6,y	; point to target and source indexes
	addd	#2		; fix return address
	std	aa_siz+6,y

	freea			; drop float stack
	puly			; recover registers
	pulx
	puld
	rts


	end

