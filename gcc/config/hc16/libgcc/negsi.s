; $Id: negsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; negsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Negate 32-Bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc16_negsi		; negate 32-bit integer
	extern	___hc16_si_setup	; set up for si operation
	extern	___hc16_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc16_negsi		- negate 32-bit integer
;
;	input:	return address points to byte indexes of target and source
;		  relative to incoming stack frame
;	output:	target holds negated copy of source
;
___hc16_negsi
	pshm	d,e,x,y			; protect registers
	jsr	___hc16_si_setup	; set up for operation

	lded	0,x			; get integer

	come				; complement it
	comd
	addd	#1			; increment it
	adce	#0

	sted	0,x			; save result

	jsr	___hc16_si_2_cleanup	; clean up after operation
	pulm	d,e,x,y			; recover registers
	rts


	end

