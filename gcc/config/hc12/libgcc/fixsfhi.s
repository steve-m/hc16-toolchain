; $Id: fixsfhi.s,v 1.2 2014/05/30 03:01:41 querbach Exp $

; fixsfhi.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Fix-Truncate Single Float to Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point calculator

	public	___hc12_fix_truncsfhi	; fix-truncate single float to int
	extern	fp_push_float		; push float on stack
	extern	fp_pop_int		; pop float as integer


;----------------------------------------------------------------------------
;
;	___hc12_fix_truncsfhi		- fix-truncate single float to int
;
;	input:	0,s points to offset of argument in stack frame
;		x points to stack frame
;	output:	d holds result
;
___hc12_fix_truncsfhi
	pshd			; protect registers
	pshx
	pshy

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; push first argument, pop as int
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	0,y		; point to first argument

	jsr	fp_push_float	; push argument as float
	jsr	fp_pop_int	; pop as integer

; done, exit
	tsy			; point to stack frame
	std	aa_siz+4,y	; save result

	ldd	aa_siz+6,y	; point to target and source indexes
	addd	#2		; fix return address
	std	aa_siz+6,y

	freea			; drop float stack
	puly			; recover registers
	pulx
	puld
	rts


	end

