;
; MODUL: маин
;
;
         .OPT NO LIST
;
         *=  $0800
;
         .INCLUDE #H1:LABELS.INC
         .INCLUDE #H1:IO.INC
         .INCLUDE #H1:MACHINA.INC
         .INCLUDE #H1:CZOLO.INC
         .INCLUDE #H1:GRA.INC
         .INCLUDE #H1:MYSL.INC
         .INCLUDE #H1:BITWA.INC
         .INCLUDE #H1:TURNIEJ.INC
         .INCLUDE #H1:GRINT.INC
         .INCLUDE #H1:KONIEC.INC
;
; TU ZOSTANA WSTAWIONE:
;
;WARTOSCI ETYKIET DANYCH,
;BLOK UNIWERSALNYCH PROCEDUR,
;    OBLEZENIE ZAMKU,
;        CZOLOWKA,
; GLOWNA PROCEDURA GRY,
;  PROCEDURY MYSLENIA,
;    PROCEDURA BITWY,
;       TURNIEJU,
;   INTERFEJS GRACZA,
;        KONCOWKA.
;
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
         STA NOPCJA
         LDA #1
         JSR MUSICON
;
MAIN     JSR CZOLO
         JSR GRA
         JMP MAIN
;
         .OPT LIST
;
         *=  $02E0
;
         .WORD GO
;
         .OPT NO LIST
;
