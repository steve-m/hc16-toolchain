; $Id: sfsf.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; sfsfsf.asm			   Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	Perform GCC Run-Time Library Single Float Binary Operation
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	import	float.mac		; floating point package
	public	___hc16_sfsf		; perform sf binary operation


;----------------------------------------------------------------------------
;
;	___hc16_sfsf		- perform single-float binary operation
;
;	This routine builds a float stack, pushes one arguments on it,
;	then calls the supplied handler.  When the handler returns, this
;	routine pops the result into the first argument.
;
;	input:	-4,z points to offsets of arguments in stack frame
;		z points to stack frame
;		d points to handler routine
;	output:	none
;
___hc16_sfsf
	pshm	d,e,x,y		; protect registers
	pshm	z,k		; save frame pointer

; make float stack
	tsx			; point to top of float stack
	alloca	fp_siz		; make space for float stack

; point to argument offsets in instruction stream
	lded	-4,z		; get return address...
	ande	#000Fh
	tedz			; ...into z

; push second argument
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	2-2,z		; point to argument
	jsr	fp_push_float	; push argument

; run handler
	tsy			; point to handler
	ldy	aa_siz+10,y
	jsr	0,y		; run it

; pop result into first argument
	tsy			; get frame pointer
	ldd	aa_siz+2,y
	addd	0-2,z		; point to argument
	jsr	fp_pop_float	; pop argument

; done, exit
	freea			; drop float stack

	pulm	z,k		; recover original frame pointer
	ldd	-2,z		; fix return address
	addd	#4
	std	-2,z

	pulm	d,e,x,y		; recover registers
	rts


	end

