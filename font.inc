font:
            .byte $00,$00,$00,$00,$00,$00,$00,$00	; ASCII 32-127
            .byte $18,$18,$18,$18,$18,$00,$18,$00
            .byte $6C,$6C,$6C,$00,$00,$00,$00,$00
            .byte $36,$36,$7F,$36,$7F,$36,$36,$00
            .byte $0C,$3F,$68,$3E,$0B,$7E,$18,$00
            .byte $60,$66,$0C,$18,$30,$66,$06,$00
            .byte $38,$6C,$6C,$38,$6D,$66,$3B,$00
            .byte $0C,$18,$30,$00,$00,$00,$00,$00
            .byte $0C,$18,$30,$30,$30,$18,$0C,$00
            .byte $30,$18,$0C,$0C,$0C,$18,$30,$00
            .byte $00,$18,$7E,$3C,$7E,$18,$00,$00
            .byte $00,$18,$18,$7E,$18,$18,$00,$00
            .byte $00,$00,$00,$00,$00,$18,$18,$30
            .byte $00,$00,$00,$7E,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$18,$18,$00
            .byte $00,$06,$0C,$18,$30,$60,$00,$00
            .byte $3C,$66,$6E,$7E,$76,$66,$3C,$00
            .byte $18,$38,$18,$18,$18,$18,$7E,$00
            .byte $3C,$66,$06,$0C,$18,$30,$7E,$00
            .byte $3C,$66,$06,$1C,$06,$66,$3C,$00
            .byte $0C,$1C,$3C,$6C,$7E,$0C,$0C,$00
            .byte $7E,$60,$7C,$06,$06,$66,$3C,$00
            .byte $1C,$30,$60,$7C,$66,$66,$3C,$00
            .byte $7E,$06,$0C,$18,$30,$30,$30,$00
            .byte $3C,$66,$66,$3C,$66,$66,$3C,$00
            .byte $3C,$66,$66,$3E,$06,$0C,$38,$00
            .byte $00,$00,$18,$18,$00,$18,$18,$00
            .byte $00,$00,$18,$18,$00,$18,$18,$30
            .byte $0C,$18,$30,$60,$30,$18,$0C,$00
            .byte $00,$00,$7E,$00,$7E,$00,$00,$00
            .byte $30,$18,$0C,$06,$0C,$18,$30,$00
            .byte $3C,$66,$0C,$18,$18,$00,$18,$00

            .byte $3C,$42,$9D,$B1,$B1,$9D,$42,$3C	; (c)
            .byte $1E,$36,$66,$FE,$C6,$C6,$C6,$00	; A
            .byte $1E,$36,$6C,$FE,$C6,$C6,$FE,$00	; B
            .byte $1E,$30,$60,$C0,$C0,$C0,$FE,$00	; C
            .byte $F0,$D8,$CC,$C6,$C6,$C6,$FE,$00	; D
            .byte $1E,$30,$60,$F8,$C0,$C0,$FE,$00	; E
            .byte $1E,$30,$60,$F8,$C0,$C0,$C0,$00	; F
            .byte $1E,$30,$60,$C6,$C6,$C6,$FE,$00	; G
            .byte $C6,$C6,$FE,$C6,$C6,$C6,$C6,$00	; H
            .byte $0C,$18,$30,$60,$60,$60,$60,$00	; I
            .byte $1E,$06,$06,$06,$66,$36,$1E,$00	; J
            .byte $1B,$36,$6C,$F8,$D8,$CC,$C6,$00	; K
            .byte $18,$30,$60,$C0,$C0,$C0,$FE,$00	; L
            .byte $C6,$EE,$FE,$D6,$C6,$C6,$C6,$00	; M
            .byte $F0,$D8,$CC,$C6,$C6,$C6,$C6,$00	; N
            .byte $1E,$36,$66,$C6,$C6,$C6,$FE,$00	; O
            .byte $1E,$36,$66,$FE,$C0,$C0,$C0,$00	; P
            .byte $1E,$36,$66,$C6,$C6,$DE,$FE,$0C	; Q
            .byte $1E,$36,$66,$FE,$D8,$CC,$C6,$00	; R
            .byte $1E,$30,$60,$FE,$06,$06,$FE,$00	; S
            .byte $FE,$18,$30,$60,$60,$60,$60,$00	; T
            .byte $C6,$C6,$C6,$C6,$C6,$C6,$FE,$00	; U
            .byte $C6,$CC,$D8,$F0,$E0,$C0,$80,$00	; V
            .byte $C6,$C6,$C6,$D6,$FE,$EE,$C6,$00	; W
            .byte $C6,$6C,$38,$38,$6C,$C6,$C6,$00	; X
            .byte $C6,$66,$36,$1E,$0C,$18,$F0,$00	; Y
            .byte $FE,$06,$0C,$18,$30,$60,$FE,$00	; Z
            .byte $0C,$18,$30,$60,$60,$60,$60,$00	; I
            .byte $3E,$66,$06,$1C,$70,$C0,$FE,$00	; 2
            .byte $7E,$0C,$18,$0C,$06,$06,$FE,$00	; 3
            .byte $18,$30,$66,$FE,$06,$06,$06,$00	; 4
            .byte $1E,$30,$60,$FC,$06,$06,$FC,$00	; 5
            .byte $1E,$30,$60,$FC,$C6,$C6,$FC,$00	; 6

;======================================================================
;FONT ROUTINES:
;======================================================================
; PUTSTRING
;  - x,y,string,0
;  - x,y,string,0
;  - $ff
;
; PUTCHAR x,y,a
;
; PRINTCHAR A
;======================================================================

PUTSTRING:
    stx $e8
    sty $e9


    ldy #0
P_S_0:
    lda ($e8),y    ; Check end of printing
    cmp #$ff
    beq P_S_4

P_S_1:
    sta XPOS       ; Save x,y,attribute
    jsr PTR_INC
    lda ($e8),y
    sta YPOS

P_S_2:
    jsr PTR_INC    ; Print character until 0
    lda ($e8),y
    beq P_S_5
    jsr PRINTCHAR
;    inc XPOS
    jmp P_S_2
P_S_5:
    jsr PTR_INC
    jmp P_S_0

P_S_4:
    rts            ; Return to program

PTR_INC:           ; Increment textpointer
    inc $e8
    bne PTR_1
    inc $e9
PTR_1:
    rts

;----------------------------------------------------------------------

curs_back:
	dec XPOS
	jmp P_C_exit
curs_forw:
	inc XPOS
	jmp P_C_exit
curs_down:
	inc YPOS
	jmp P_C_exit

;----------------------------------------------------------------------
SCR      = $e0
CHR      = $e2
TMP_Y    = $e4
TMP_X    = $e5
TMP_A	 = $e6

PUTCHAR:
    stx XPOS
    sty YPOS

PRINTCHAR:
    sta TMP_A
    stx TMP_X
    sty TMP_Y

	cmp #08
	beq curs_back

	cmp #09
	beq curs_forw

	cmp #$0A
	beq curs_down

	cmp #$01
	beq P_C_exit

	sec
	sbc #32

    sta CHR        ; Calculate characterspritedata address
    lda #0         ; = A * 8 + charsprite data address
    sta CHR+1
    asl CHR
    rol CHR+1
    asl CHR
    rol CHR+1
    asl CHR
    rol CHR+1
    lda CHR
    clc
    adc #<font
    sta CHR
    lda CHR+1
    adc #>font
    sta CHR+1
    
    lda XPOS       ; Calculate screenaddress
    sta SCR
    lda YPOS
    clc
    adc #>$8000
    sta SCR+1
 
    ldx #0
    ldy #0         ; Put character on screen
P_C_1:
    lda (CHR),y
    sta (SCR),y
    inc CHR
    bne P_C_2
    inc CHR+1
P_C_2:
    lda SCR
    clc
    adc #$20
    sta SCR
    lda SCR+1
    adc #0
    sta SCR+1
    inx
    cpx #8
    bne P_C_1

    inc XPOS
	lda XPOS
	cmp #32
	bne P_C_exit
	lda #0
	sta XPOS
	inc YPOS
P_C_exit:
    ldx TMP_X
    ldy TMP_Y
    lda TMP_A
    rts
 