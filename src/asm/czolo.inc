;
; MODUL: CZOLO
;

CZOLOCOLTABB .BYTE $73,$78,$7F,$06,$00
;
SETCZOLODL LDA #$00
         STA $D40E
         SEI 
         STA $D400
         LDA # <CZOLODL
         LDY # >CZOLODL
         LDX # >CZOLOPIC
         STA $D402
         STY $D403
         STX CHARGENVECT
         LDY #$04
SETCZOLODL1 LDA CZOLOPIC+$07FB,Y
         STA COLORSBUFA,Y
         LDA CZOLOCOLTABB,Y
         STA COLORSBUFB,Y
         DEY 
         BPL SETCZOLODL1
         LDA # <CZOLONMI
         LDY # >CZOLONMI
         STA $FFFA
         STY $FFFB
         LDA #0
         STA NRTEXT
         JSR TEXTSCROLLINIT
         LDY #47
         LDA #0
SETCZOLODL3 STA INFOLINE,Y
         DEY 
         BPL SETCZOLODL3
         LDY #34
         LDX #192
SETCZOLODL2 LDA $D40B
         BNE SETCZOLODL2
         STY $D400
         STX $D40E
         JMP CZOLOVBL
;
CZOLONMI CLD 
         PHA 
         TYA 
         PHA 
         TXA 
         PHA 
         LDA $D40F
         STA $D40F
         ASL
         BCC CZOLONMI1
         JSR CZOLODLI
         JMP CZOLONMI2
CZOLONMI1 ASL
         BCC CZOLONMI2
         JSR CZOLOVBL
CZOLONMI2 PLA 
         TAX 
         PLA 
         TAY 
         PLA 
         RTI 
;
CZOLODLI JMP SETCZOLOCOL
;
CZOLOVBL JSR SETCOLA
         JSR VBLTIMERDOWN
         JSR TEXTSCROLL
         JMP MUSICPLAY
;
SETCZOLOCOL LDY #$04
SETCZOLOCOL1 LDA COLORSBUFB,Y
         STA $D016,Y
         DEY 
         BPL SETCZOLOCOL1
         LDY #24+4
SETCZOLOCOL2 STA $D40A
         DEY 
         BNE SETCZOLOCOL2
         LDA COLORSBUFB+3
         LDY #0
         LDX # >CHARGEN
         STA $D016
         STA $D017
         STY $D018
         STY $D01A
         STX $D409
         RTS 
;
TEXTSCROLL LDY LSCROLLZN
         DEY 
         TYA 
         AND #3
         STA LSCROLLZN
         CMP #3
         BNE TEXTSCROLL1
         LDY #1
TEXTSCROLL6 LDA INFOLINE+1,Y
         STA INFOLINE,Y
         INY 
         CPY #47
         BNE TEXTSCROLL6
TEXTSCROLL4 LDY #0
         LDA TEXTZN
         LDX TEXTZN+1
         STA IZN
         STX IZN+1
         LDA (IZN),Y
         LDX TEXTZN+2
         BEQ TEXTSCROLL2
         DEC TEXTZN+2
         BNE TEXTSCROLL3
         JSR TEXTZNUP
         JMP TEXTSCROLL3
TEXTSCROLL2 CMP #$FF
         BNE TEXTSCROLL5
TEXTSCROLLINIT LDA NRTEXT
         ASL
         TAY 
         LDA TEXTSCROLLTAB,Y
         STA TEXTZN
         LDA TEXTSCROLLTAB+1,Y
         STA TEXTZN+1
         LDA #0
         STA TEXTZN+2
         JMP TEXTSCROLL4
TEXTSCROLL5 CMP #$FE
         BNE TEXTSCROLL7
         JSR TEXTZNUP
         INY 
         LDA (IZN),Y
         STA TEXTZN+2
         JSR TEXTZNUP
         JMP TEXTSCROLL4
TEXTSCROLL7 JSR TEXTZNUP
TEXTSCROLL3 STA INFOLINE+47
TEXTSCROLL1 LDA LSCROLLZN
         STA $D404
         RTS 
;
TEXTSCROLLTAB .WORD CZOLOTEXT,KONIECTEXT
;
TEXTZNUP INC TEXTZN
         BNE TEXTZNUP1
         INC TEXTZN+1
TEXTZNUP1 RTS 
;
CZOLOTEXT .BYTE $FE,10,0
         .SB "LABORATORIUM KOMPUTEROWE APM  ORAZ  MIRAGE SOFTWARE LTD.  "
         .SB "MAJ", $3B, " PRZYJEMNO", $41, $3C," ZAPREZENTOWA", $3C, " NOW", $3B, " GR", $3D, ": "
		 .SB " "+$80, "W"+$80, " "+$80, $3E+$80
		 .SB " "+$80, "A"+$80, " "+$80, "D"+$80
		 .SB " "+$80, "C"+$80, " "+$80, "A"+$80
		 .SB " "+$80
         .SB $FE,48,0
         .SB "PRACE NAD NI", $3B," ZOSTA", $3E, "Y UKO", $3F, "CZONE W SIERPNIU 1993 ROKU."
         .SB $FE,48,0
         .SB "AUTORZY:"
         .SB $FE,20,0
         .SB "MUZYKA,GRAFIKA: TOMASZ ", $3E, "USZCZ"
         .BYTE $FE,20,0
         .SB "PROGRAMOWANIE: ARTUR MIARECKI"
         .BYTE $FE,48,0
         .SB "CZYTAJ CZASOPISMA, PO", $41,"WI", $3D, "CONE MA", $3E, "EMU ATARI (WG KOLEJNO", $41, "CI ALFABETYCZNEJ):"
         .BYTE $FE,20,0
         .SB "ATARI MAGAZYN"
         .BYTE $FE,20,0
         .SB $41, "WIAT ATARI"
         .BYTE $FE,20,0
         .SB "TAJEMNICE ATARI."
         .BYTE $FE,48,0
         .SB "WARTO CZYTA", $3C, " TE", $42, " I INNE PISMA, NIE TYLKO DLA ATAROWC", $40, "W:"
         .BYTE $FE,20,0
         .SB "BAJTEK"
         .BYTE $FE,20,0
         .SB "SECRET SERVICE"
         .BYTE $FE,20,0
         .SB "TOP SECRET."
         .BYTE $FE,100,0
         .BYTE $FF
;
CHOPCJA  LDA $D01F
         AND #$07
         CMP #$03
         BNE CHOPCJA1
         INC NOPCJA
         LDA NOPCJA
         CMP #3
         BNE CHOPCJA2
         LDA #0
         STA NOPCJA
CHOPCJA2 JSR PRINTOPCJA
CHOPCJA3 LDA $D01F
         AND #$07
         CMP #$03
         BEQ CHOPCJA3
CHOPCJA1 RTS 
;
NOPCJATXTTAB .SB "112122"
;
PRINTOPCJA LDA NOPCJA
         ASL
         TAY 
         LDA NOPCJATXTTAB,Y
         STA OPTLINETXT+10
         LDA NOPCJATXTTAB+1,Y
         STA OPTLINETXT+15
         RTS 
;
CZOLO    JSR SETCZOLODL
         JSR PRINTOPCJA
CZOLO1   JSR CHOPCJA
         LDY #0
         JSR GETFIRE
         BEQ CZOLO2
         LDA NOPCJA
         CMP #2
         BNE CZOLO1
         LDY #1
         JSR GETFIRE
         BNE CZOLO1
CZOLO2   JSR SCREENOFF
         LDA #$00
         STA $D400
         STA $D40E
         JMP WAITMOD
;

