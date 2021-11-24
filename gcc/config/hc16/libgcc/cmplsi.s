; $Id: cmplsi.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; cmplsi.asm		 	   Copyright (C) 1998, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	GCC Runtime Routine:  Ones-Complement 32-bit Integer
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package

	public	___hc16_one_cmplsi	; ones-complement 32-bit integer
	extern	___hc16_si_setup	; set up for si operation
	extern	___hc16_si_1_cleanup	; clean up after si binary operation


;----------------------------------------------------------------------------
;
;	___hc16_one_cmplsi		- ones-complement 32-bit integer
;
;	input:	return address points to byte indexes of target and source
;		  relative to incoming stack frame
;	output:	target holds complemented copy of source
;
;	note:	requires 10 bytes stack
;
___hc16_one_cmplsi
	pshm	d,e,x,y			; protect registers
	jsr	___hc16_si_setup	; set up for operation

	comw	0,x			; complement high word
	comw	2,x			; complement low word

; done, exit
	jsr	___hc16_si_1_cleanup	; clean up after operation
	pulm	d,e,x,y			; recover registers
	rts


	end

