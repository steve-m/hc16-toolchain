; $Id: udivmdsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; udivmdsi.asm			   Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Calculate Unsigned 32-Bit Quotient and Remainder
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	public	___hc1x_udivmodsi	; unsigned SI div/mod


;----------------------------------------------------------------------------
;
;	___hc1x_udivmodsi	- calculate unsigned 32-bit quotient/remainder
;
;	input:	x points to dividend
;		y points to divisor
;	output:	x points to quotient
;		y points to remainder
;		d destroyed
;
___hc1x_udivmodsi
	pshx			; save pointer to dividend/quotient
	pshy			; save pointer to divisor/remainder

	ldx	#0		; clear space for remainder
	pshx
	pshx
	tsx			; point to stack frame

	ldaa	#32		; number of iterations required

; shift dividend left into remainder
udm_1	ldy	6,x		; point to divident and quotient

	asl	3,y		; shift divident and quotient left...
	rol	2,y
	rol	1,y
	rol	0,y

	rol	3,x		; ...into remainder
	rol	2,x
	rol	1,x
	rol	0,x

; if remainder greater/equal divisor...
	ldy	4,x		; point to divisor

	ldab	3,x		; compare low bytes
	subb	3,y

	ldab	2,x		; compare mid bytes
	sbcb	2,y

	ldab	1,x		; compare mid bytes
	sbcb	1,y

	ldab	0,x		; compare high bytes
	sbcb	0,y

	bcs	udm_2		; divisor greater?  go on

; ...subtract out a divisor, increment quotient
	ldab	3,x		; subtract low bytes
	subb	3,y
	stab	3,x

	ldab	2,x		; subtract mid bytes
	sbcb	2,y
	stab	2,x

	ldab	1,x		; subtract mid bytes
	sbcb	1,y
	stab	1,x

	ldab	0,x		; subtract high bytes
	sbcb	0,y
	stab	0,x

	ldy	6,x		; increment quotient
	inc	3,y

; count iterations
udm_2	deca			; done all bits?
	bne	udm_1		; no, loop

; save remainder
	ldy	4,x		; point to target

	pulx			; copy high word
	stx	0,y
	pulx			; copy low word
	stx	2,y

; done, exit
	puly			; recover registers
	pulx
	rts


	end

