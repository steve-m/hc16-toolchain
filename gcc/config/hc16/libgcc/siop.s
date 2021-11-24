; $Id: siop.s,v 1.1 2015/02/19 20:21:28 querbach Exp $

; siop.asm			   Copyright (C) 1997, Real-Time Systems Inc.
;--------------------------------------------- All Rights Reserved ----------
;
;	SI/SF Library Run-Time Helper Routines
;
;----------------------------------------------------------------------------

	include	std.mac			; standard macro package
	public	___hc16_si_setup	; set up for binary/trinary operation
	public	___hc16_si_1_cleanup	; fix up after unary operation
	public	___hc16_si_2_cleanup	; fix up after binary operation
	public	___hc16_si_3_cleanup	; fix up after trinary operation


;----------------------------------------------------------------------------
;
;	___hc16_si_setup	- set up for binary or trinary operation
;
;	This routine handles arguments set up by the compiler for SI and
;	SF binary and trinary run-time library function calls.  The second
;	argument is copied onto the first, and pointers to the first and
;	third argument are returned.
;
;	input:	-4,z points to 2 past offsets of arguments in stack frame
;		z holds stack frame pointer
;	output:	x points to first argument
;		y points to third argument
;
___hc16_si_setup
	pshm	d,e,z,k			; save frame pointer

; point to argument offsets in instruction stream
	lded	-4,z			; get return address...
	ande	#000Fh
	tedz				; ...into z

; point to first argument
	tsx				; get frame pointer
	ldx	2,x
	addx	0-2,z			; point to argument

; point to second argument
	tsy				; get frame pointer
	ldy	2,y
	addy	2-2,z			; point to argument

; copy second argument over first
	lded	0,y			; copy argument
	sted	0,x

; point to third argument
	tsy				; get frame pointer
	ldy	2,y
	addy	4-2,z			; point to argument

; done, exit
	pulm	d,e,z,k			; recover register
	rts


;----------------------------------------------------------------------------
;
;	___hc16_si_1_cleanup	- fix up after unary operation
;	___hc16_si_2_cleanup	- fix up after binary operation
;	___hc16_si_3_cleanup	- fix up after trinary operation
;
;	These routines clean up after an SI or SF run-time library function 
;	calls by advancing the return address past the argument offsets.
;
;	input:	-4,z points to offsets of arguments in stack frame
;	output:	-4,z points to valid code
;		d destroyed
;
___hc16_si_1_cleanup
	ldd	#2			; one byte
	bra	___hc16_si_cleanup


___hc16_si_2_cleanup
	ldd	#4			; two bytes
	bra	___hc16_si_cleanup


___hc16_si_3_cleanup
	ldd	#6			; three bytes


___hc16_si_cleanup
	addd	-2,z			; update return address
	std	-2,z

	rts


	end

