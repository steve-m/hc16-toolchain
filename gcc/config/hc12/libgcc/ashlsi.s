; $Id: ashlsi.s,v 1.1 2002/09/08 20:40:19 querbach Exp $

; ashlsi.asm		 	   Copyright (C) 1995, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Shift-Left 32-Bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc12_ashlsi		; shift-left 32-bit integer
	extern	___hc12_si_setup	; set up for si operation
	extern	___hc12_si_2_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc12_ashlsi		- shift-left 32-bit integer
;
;	input:	return address points to byte indexes of target and source
;		  relative to incoming stack frame
;		b holds shift count
;	output:	target holds shifted copy of source
;
;	note:	requires 10 bytes stack
;
___hc12_ashlsi
	pshd				; protect registers
	pshx
	pshy
	jsr	___hc12_si_setup	; set up for operation

ashlsi1	lsl	3,x			; shift low byte...
	rol	2,x
	rol	1,x
	rol	0,x			; ...into high byte

	decb				; done all?
	bne	ashlsi1			; no, loop

; done, exit
	jsr	___hc12_si_2_cleanup	; clean up after operation
	puly				; recover registers
	pulx
	puld
	rts


	end

