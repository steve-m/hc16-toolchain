; $Id: fixusfsi.s,v 1.2 2014/05/30 03:01:41 querbach Exp $

; fixusfsi.asm		           Copyright (C) 2008, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Fix-Truncate Single Float to Unsigned Long
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point calculator

	public	___hc12_fixuns_truncsfsi ; fix-truncate single float to ulong
	extern	fp_push_float		; push float on stack
	extern	fp_pop_ulong		; pop float as unsigned long integer


;----------------------------------------------------------------------------
;
;	___hc12_fixuns_truncsfsi	- fix-truncate single float to ulong
;
;	input:	0,s points to offset of arguments in stack frame
;		s points to stack frame
;	output:	stack frame holds result
;
___hc12_fixuns_truncsfsi
	pshd			; protect registers
	pshx
	pshy

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; push second argument as float
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	2,y		; point to second argument

	jsr	fp_push_float	; push argument as float

; pop into first argument as long
	leay	aa_siz+8,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+6,s	; point to target and source indexes
	addd	0,y		; point to first argument

	jsr	fp_pop_ulong	; pop as unsigned long integer

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

