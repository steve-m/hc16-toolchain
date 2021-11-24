; $Id: ashlhi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; ashlhi.asm		           Copyright (C) 1996, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Shift-left 16-bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	public	___hc16_ashlhi	; shift-left 16-bit integer


;----------------------------------------------------------------------------
;
;	___hc16_ashlhi		- shift-left 16-bit integer
;
;	input:	d holds number to shift
;		z holds shift count
;	output:	d holds result
;		z destroyed
;
___hc16_ashlhi

ashlhi1 cpz	#0		; done all?
	beq	ashlhi2		; yes, exit

	asld			; shift accumulator
	aiz	#-1		; dec counter 
	bra	ashlhi1		; loop

ashlhi2	rts


	end

