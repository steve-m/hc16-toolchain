; $Id: ashlhi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; ashlhi.asm		           Copyright (C) 1996, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	GCC Runtime Routine:  Shift-left 16-bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac		; standard macro package
	public	___hc12_ashlhi	; shift-left 16-bit integer


;----------------------------------------------------------------------------
;
;	___hc12_ashlhi		- shift-left 16-bit integer
;
;	input:	d holds number to shift
;		x holds shift count
;	output:	d holds result
;		x destroyed
;
___hc12_ashlhi

ashlhi1	cpx	#0		; done all?
	beq	ashlhi2		; yes, exit

	asld			; shift accumulator
	dex			; count shifts 
	bra	ashlhi1		; loop

ashlhi2	rts


	end

