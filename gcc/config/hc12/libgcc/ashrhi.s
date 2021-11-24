; $Id: ashrhi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; ashrhi.asm		           Copyright (C) 1996, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Shift-right 16-bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	public	___hc12_ashrhi	; shift-right 16-bit integer


;----------------------------------------------------------------------------
;
;	___hc12_ashrhi		- shift-right 16-bit integer
;
;	input:	d holds number to shift
;		x holds shift count
;	output:	d holds result
;		x destroyed
;
___hc12_ashrhi

ashrhi1	cpx	#0		; done all?
	beq	ashrhi2		; yes, exit

	asrd			; shift accumulator
	dex			; count shifts
	bra	ashrhi1		; loop

ashrhi2	rts


	end

