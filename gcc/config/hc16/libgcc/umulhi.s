; $Id: umulhi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; umulhi.asm		           Copyright (C) 1996, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Multiply Unsigned 16-bit Integers
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	public	___hc16_umulhi	; multiply unsigned integers


;----------------------------------------------------------------------------
;
;	___hc16_umulhi		- multiply unsigned 16-bit integers
;
;	input:	d holds multiplicand
;		x holds multiplier
;	output:	d holds product
;		x destroyed
;
;	note:	requires 6 bytes stack
;
___hc16_umulhi
	pshd			; save multiplicand
	pshx			; save multiplier
	tsx			; point to stack frame

; make partial product with 2^8 weight
	ldaa	0,x
	mul
	stab	0,x

; make partial product with 2^8 weight
	ldaa	1,x
	ldab	2,x
	mul
	addb	0,x
	stab	0,x

; make partial product with 2^0 weight
	ldaa	1,x
	ldab	3,x
	mul
	adda	0,x

; done, exit
	pulx			; drop multiplier
	pulx			; drop multiplicand
	rts


	end

