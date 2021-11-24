; $Id: ashrsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; ashrsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Arithmetic Shift-Right 32-Bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc16_ashrsi		; shift-right 32-bit integer
	extern	___hc16_si_setup	; set up for si operation
	extern	___hc16_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc16_ashrsi		- shift-right 32-bit integer
;
;	input:	return address points to byte indexes of target and source
;		  relative to incoming stack frame
;		b holds shift count
;	output:	target holds shifted copy of source
;
;	note:	requires 10 bytes stack
;
___hc16_ashrsi
	pshm	d,e,x,y			; protect registers
	jsr	___hc16_si_setup	; set up for operation

ashrsi1	asr	0,x			; shift high byte...
	ror	1,x
	ror	2,x
	ror	3,x			; ...into low byte

	decb				; done all?
	bne	ashrsi1			; no, loop

; done, exit
	jsr	___hc16_si_2_cleanup	; clean up after operation
	pulm	d,e,x,y			; recover registers
	rts


	end

