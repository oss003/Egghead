;----------------------------------------------
; Egghead in space
; Acorn Electron conversion by Kees van Oss 2015
;----------------------------------------------
	.DEFINE asm_code $2300
	.DEFINE header   1		; Header Wouter Ras emulator
	.DEFINE filenaam "EGGHEAD"

.org asm_code-22*header

.IF header
;********************************************************************
; ATM Header for Atom emulator Wouter Ras

name_start:
	.byte filenaam			; Filename
name_end:
	.repeat 16-name_end+name_start	; Fill with 0 till 16 chars
	  .byte $0
	.endrep

	.word asm_code			; 2 bytes startaddress
	.word L4935			; 2 bytes linkaddress
	.word eind_asm-start_asm	; 2 bytes filelength

;********************************************************************
.ENDIF

start_asm:
	.include "ehcode.inc"
	.include "font.inc"
	.include "routines.inc"
	.include "joystick.inc"
	.include "sound.inc"
eind_asm:
