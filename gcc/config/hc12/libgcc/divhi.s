; $Id: divhi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; divhi.asm			   Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Divide Signed 16-bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	public	___hc12_divhi	; divide signed integers


;----------------------------------------------------------------------------
;
;	___hc12_divhi	- divide signed 16-bit integers
;
;	input:	d holds dividend
;		x holds divisor
;	output:	d holds product
;		x destroyed
;
;	note:	requires 9 bytes stack
;
___hc12_divhi
	des				; make space for sign byte

; set up for unsigned division
	pshx				; save divisor

	tsx				; point to stack frame
	eora	0,x			; save sign of quotient
	staa	2,x

	eora	0,x			; make dividend unsigned
	absd

	pulx				; get divisor
	xgdx				; make divisor unsigned
	absd

; do unsigned division
	xgdx				; dividend to d, divisor to x
	idiv				; divide
	xgdx				; quotient to d

; set sign of product
	tsx				; point to sign byte
	brclr	0,x,#80h,divhi_1	; product positive?  go on

	negd				; make product negative

; done, exit
divhi_1	ins				; drop sign byte
	rts


	end

