;----------------------------------------------------
; Set mode 5
;----------------------------------------------------

setmode5:
	lda #$f0	; Clear4 colour mode
	sta $b000

	rts

;----------------------------------------------------
; Clear zero page
;----------------------------------------------------

clz:
	lda #0
	tax
clz_loop:
	sta 0,x
	inx
	bne clz_loop
	rts

;----------------------------------------------------
; Clear screen
;----------------------------------------------------

XPOS	= $0318
YPOS	= $0319

cls:
	ldy #0
	tya
cls_loop:
	sta $8000,y
	sta $8100,y
	sta $8200,y
	sta $8300,y
	sta $8400,y
	sta $8500,y
	sta $8600,y
	sta $8700,y
	sta $8800,y
	sta $8900,y
	sta $8a00,y
	sta $8b00,y
	sta $8c00,y
	sta $8d00,y
	sta $8e00,y
	sta $8f00,y
	sta $9000,y
	sta $9100,y
	sta $9200,y
	sta $9300,y
	sta $9400,y
	sta $9500,y
	sta $9600,y
	sta $9700,y
	iny
	bne cls_loop

	lda #0		; Reset cursor
	sta XPOS
	sta YPOS

	rts

;----------------------------------------------------
; Clear graphics
;----------------------------------------------------

clg:
	ldy #0
	tya
clg_loop:
	sta $8600,y
	sta $8700,y
	sta $8800,y
	sta $8900,y
	sta $8a00,y
	sta $8b00,y
	sta $8c00,y
	sta $8d00,y
	sta $8e00,y
	sta $8f00,y
	sta $9000,y
	sta $9100,y
	sta $9200,y
	sta $9300,y
	sta $9400,y
	sta $9500,y
	sta $9600,y
	sta $9700,y
	iny
	bne clg_loop

	rts

;---------------------------------------------
; Read key in matrix
;
; Select row and read column:
;
; X = key to be checked
;
; columnbit = 0 - key pressed,
;             1 - key not pressed
;---------------------------------------------

controlflag = $0381

readkey:
	bit controlflag		; Check controls
	bvs joykey		; Control = Joykey
	bmi joymmc		; Control = JoyMMC

; Control = Keyboard -------------------------

keyboard:
	lda key_row,x
	ora #$f0
	sta $b000		; Select row

	lda $b001		; Read column
	and key_column,x
	bne not_pressed
	lda key_return,x
	rts

not_pressed:
	lda #0
	rts
;                      Z   X  SPC ESC RET  JL  JR  JA
key_row:	.byte $01,$03,$09,$00,$06,$00,$00,$00
key_column:	.byte $20,$20,$01,$20,$02,$02,$08,$01
key_return:	.byte $ef,$de,$9d,$8f,$b6,$ff,$ff,$ff

; Control = Joykey ---------------------------

joykey:
	cpx #3
	bcs keyboard
	inx
	inx
	inx
	inx
	inx
	jmp keyboard

; Control = JoyMMC ---------------------------

joymmc:
	cpx #3
	bcs keyboard
	jsr joyget
	sta joy_scan

	cpx #0
	bne scan_r
scan_l:
	and #$02
	beq scan_no
	lda #$fe
	rts
scan_r:
	cpx #1
	bne scan_u
	lda joy_scan
	and #$01
	beq scan_no
	lda #$02
	rts
scan_u:
	cpx #2
	bne scan_no
	lda joy_scan
	and #$10
	beq scan_no
	lda #$ff
	rts
scan_no:
	lda #0
	rts

joy_scan:	.byte 0
