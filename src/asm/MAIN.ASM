;
; MODUL: маин
;
;
         .OPT NO LIST
;
         *=  $0800
;
         .INCLUDE #D8:LABELS.M65
         .INCLUDE #D8:IO.M65
         .INCLUDE #D8:MACHINA.M65
         .INCLUDE #D8:CZOLO.M65
         .INCLUDE #D8:GRA.M65
         .INCLUDE #D8:MYSL.M65
         .INCLUDE #D8:BITWA.M65
         .INCLUDE #D8:TURNIEJ.M65
         .INCLUDE #D8:GRINT.M65
         .INCLUDE #D8:KONIEC.M65
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
