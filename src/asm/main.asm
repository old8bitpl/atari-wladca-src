;
; MODUL: MAIN
;
         org $0800
;
;
; TU ZOSTANA WSTAWIONE:
;
; WARTOSCI ETYKIET DANYCH
         ICL 'labels.inc'
; BLOK UNIWERSALNYCH PROCEDUR
         ICL 'io.inc'
; OBLEZENIE ZAMKU
         ICL 'machina.inc'
; CZOLOWKA
         ICL 'czolo.inc'
; GLOWNA PROCEDURA GRY
         ICL 'gra.inc'
; PROCEDURY MYSLENIA
         ICL 'mysl.inc'
; PROCEDURA BITWY
         ICL 'bitwa.inc'
; TURNIEJ
         ICL 'turniej.inc'
; INTERFEJS GRACZA
         ICL 'grint.inc'
; KONCOWKA
         ICL 'koniec.inc'
; UTIL
         ICL 'util.inc'
;

; PL CHARS (for .SB):
; char .BYTE	.SB
; A		$3B		$5B
; C		$3C		$5C
; E		$3D		$5D
; L		$3E		$5E
; N		$3F		$5F
; O		$40		$00
; S		$41		$01
; Z		$42		$02
; X		$43		$03

GO       LDX #$FF
         TXS 
         LDA #$00
         STA $D40E
         SEI 
         STA $D400
         LDA #$FE
         STA $D301
         LDA #0
         STA MUSICZN
         STA NOPTPLJOY
         LDA #1
         JSR MUSICON
;
MAIN     JSR CZOLO
         JSR GRA
         JMP MAIN

;
         org $02E0
;
         .WORD GO
;

