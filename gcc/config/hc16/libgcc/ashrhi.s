; $Id: ashrhi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; ashrhi.asm		           Copyright (C) 1996, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Shift-right 16-bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	public	___hc16_ashrhi	; shift-right 16-bit integer


;----------------------------------------------------------------------------
;
;	___hc16_ashrhi		- shift-right 16-bit integer
;
;	input:	d holds number to shift
;		z holds shift count
;	output:	d holds result
;		z destroyed
;
___hc16_ashrhi

ashrhi1	cpz	#0		; done all?
	beq	ashrhi2		; yes, exit

	asrd			; shift accumulator
	aiz	#-1		; dec counter
	bra	ashrhi1		; loop

ashrhi2	rts


	end

