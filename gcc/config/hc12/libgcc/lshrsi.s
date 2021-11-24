; $Id: lshrsi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; lshrsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Logical Shift-Right 32-Bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc12_lshrsi		; logical shift-right 32-bit integer
	extern	___hc12_si_setup	; set up for si operation
	extern	___hc12_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc12_ashlsi		- logical shift-right 32-bit integer
;
;	input:	return address points to byte indexes of target and source
;		  relative to incoming stack frame
;		b holds shift count
;	output:	target holds shifted copy of source
;
;	note:	requires 10 bytes stack
;
___hc12_lshrsi
	pshd				; protect registers
	pshx
	pshy
	jsr	___hc12_si_setup	; set up for operation

lshrsi1	lsr	0,x			; shift high byte...
	ror	1,x
	ror	2,x
	ror	3,x			; ...into low byte

	decb				; done all?
	bne	lshrsi1			; no, loop

	jsr	___hc12_si_2_cleanup	; clean up after operation
	puly				; recover registers
	pulx
	puld
	rts


	end

