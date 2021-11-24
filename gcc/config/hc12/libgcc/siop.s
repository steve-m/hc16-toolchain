; $Id: siop.s,v 1.2 2014/05/30 03:01:41 querbach Exp $

; siop.asm			   Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	SI/SF Library Run-Time Helper Routines
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	public	___hc12_si_setup	; set up for binary/trinary operation
	public	___hc12_si_1_cleanup	; fix up after unary operation
	public	___hc12_si_2_cleanup	; fix up after binary operation
	public	___hc12_si_3_cleanup	; fix up after trinary operation


;----------------------------------------------------------------------------
;
;	___hc12_si_setup	- set up for binary or trinary operation
;
;	This routine handles arguments set up by the compiler for SI and
;	SF binary and trinary run-time library function calls.  The second
;	argument is copied onto the first, and pointers to the first and
;	third argument are returned.
;
;	input:	8,s points to offsets of arguments in stack frame
;		4,s holds stack frame pointer
;	output:	x points to first argument
;		y points to third argument
;
___hc12_si_setup
	pshd				; protect register

; point to first argument
	leax	12,s			; point to original frame
	tfr	x,d
	ldx	10,s			; point to target and source indexes
	addd	0,x			; point to first argument
	tfr	d,x			; ...with x

; point to second argument
	leay	12,s			; point to original frame
	tfr	y,d
	ldy	10,s			; point to target and source indexes
	addd	2,y			; point to second argument
	tfr	d,y			; ...with y

; copy second argument over first
	ldd	0,y			; copy high word
	std	0,x
	ldd	2,y			; copy low word
	std	2,x

; point to third argument
	leay	12,s			; point to original frame
	tfr	y,d
	ldy	10,s			; point to target and source indexes
	addd	4,y			; point to second argument
	tfr	d,y			; ...with y

; done, exit
	puld				; recover register
	rts


;----------------------------------------------------------------------------
;
;	___hc12_si_1_cleanup	- fix up after unary operation
;	___hc12_si_2_cleanup	- fix up after binary operation
;	___hc12_si_3_cleanup	- fix up after trinary operation
;
;	These routines clean up after an SI or SF run-time library function 
;	calls by advancing the return address past the argument offsets.
;
;	input:	8,s points to offsets of arguments in stack frame
;	output:	8,s points to valid code
;		d,x destroyed
;
___hc12_si_1_cleanup
	ldab	#2			; one byte
	bra	___hc12_si_cleanup


___hc12_si_2_cleanup
	ldab	#4			; two bytes
	bra	___hc12_si_cleanup


___hc12_si_3_cleanup
	ldab	#6			; three bytes


___hc12_si_cleanup
	clra				; extend amount to d
	tsx				; point to stack frame
	addd	8,x			; update return address
	std	8,x

	rts


	end

