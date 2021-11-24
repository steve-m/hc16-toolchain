; $Id: mulhi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; mulhi.asm		           Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Multiply Signed 16-bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	public	___hc12_mulhi	; multiply signed integers
	extern	___hc12_umulhi	; multiply unsigned integers


;----------------------------------------------------------------------------
;
;	___hc12_mulhi	- multiply signed 16-bit integers
;
;	input:	d holds multiplicand
;		x holds multiplier
;	output:	d holds product
;		x destroyed
;
;	note:	requires 9 bytes stack
;
___hc12_mulhi
	des				; make space for sign byte
	pshx				; save multiplier
	tsx				; point to stack frame

; set up for unsigned multiplication
	eora	0,x			; save sign of product
	staa	2,x

	eora	0,x			; make multiplicand unsigned
	absd

	pulx				; make multiplier unsigned
	xgdx
	absd

; do unsigned multiplication
	jsr	___hc12_umulhi		; multiply

; set sign of product
	tsx				; point to sign byte
	brclr	0,x,#80h,mulhi_1	; product positive?  go on

	negd				; make product negative

; done, exit
mulhi_1	ins				; drop sign byte
	rts


	end

