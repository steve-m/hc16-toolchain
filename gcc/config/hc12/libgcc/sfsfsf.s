; $Id: sfsfsf.s,v 1.2 2014/05/30 03:01:41 querbach Exp $

; sfsfsf.asm			   Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	Perform GCC Run-Time Library Single Float Trinary Operation
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point package
	public	___hc12_sfsfsf		; perform sf trinary operation


;----------------------------------------------------------------------------
;
;	___hc12_sfsfsf		- perform single-float trinary operation
;
;	This routine builds a float stack, pushes two arguments on it,
;	then calls the supplied handler.  When the handler returns, this
;	routine pops the result into the first argument.
;
;	input:	4,s points to offsets of arguments in stack frame
;		x points to stack frame
;		d points to handler routine
;	output:	none
;
___hc12_sfsfsf
	pshd			; save pointer to handler
	pshx			; protect registers
	pshy

; make float stack
	tsx			; point to top of float stack
	alloca	2*fp_siz	; make space for float stack

; push second argument
	leay	aa_siz+12,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+10,s	; point to target and source indexes
	addd	2,y		; point to second argument

	jsr	fp_push_float	; push argument

; push third argument
	leay	aa_siz+12,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+10,s	; point to target and source indexes
	addd	4,y		; point to third argument

	jsr	fp_push_float	; push argument

; run handler
	tsy			; point to handler
	ldy	aa_siz+4,y
	jsr	0,y		; run it

; pop result into first argument
	leay	aa_siz+12,s	; point to original frame
	tfr	y,d
	ldy	aa_siz+10,s	; point to target and source indexes
	addd	0,y		; point to first argument

	jsr	fp_pop_float	; pop argument

; done, exit
	tsx			; point to stack frame
	ldd	aa_siz+10,x	; point to target and source indexes
	addd	#6		; fix return address
	std	aa_siz+10,x

	freea			; drop float stack
	puly			; recover registers
	pulx
	puld
	rts


	end

