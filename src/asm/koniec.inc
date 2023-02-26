;
; MODUL: KONIEC 
;

KONIECTRUP STA POM
         JSR KONIECSCROFF
         JSR STATSCR
         JSR PLTRUPPIC
         JMP WAITMOD
;
KONIECBREAK JSR KONIECSCROFF
         LDA #0
         STA POM
KONIECBREAK1 LDY POM
         LDA HUMANPL,Y
         CMP #255
         BEQ KONIECBREAK2
         JSR STATSCR
KONIECBREAK2 INC POM
         LDA POM
         CMP #2
         BNE KONIECBREAK1
         LDA IMMZN
         BNE KONIECBREAK3
         LDA $D01F
         AND #$07
         CMP #$03
         BEQ KONIECWIN2
KONIECBREAK3 RTS 
;
KONIECWIN JSR KONIECSCROFF
         LDY #0
         LDA HUMANPL
         CMP #255
         BNE KONIECWIN1
         INY 
KONIECWIN1 STY POM
         JSR STATSCR
KONIECWIN2 JSR WINGAME
         JMP WAITMOD
;
KONIECSCROFF LDA $D40B
         BNE KONIECSCROFF
         STA $D40E
         STA $D400
         RTS 
;
WAITMOD  LDY #50
WAITMOD1 LDA $D40B
         BNE WAITMOD1
         TYA 
         PHA 
         JSR MUSICPLAY
         LDY #0
WAITMOD2 DEY 
         BNE WAITMOD2
         PLA 
         TAY 
         DEY 
         BNE WAITMOD1
         RTS 
;
PRSTATSCR LDA # <STATSCRDAT
         LDY # >STATSCRDAT
         STA VZN
         STY VZN+1
         LDA # <SCRPE
         LDY # >SCRPE
         STA VZN+2
         STY VZN+3
PRSTATSCR1 LDY #$00
         LDA #1
         STA VZN+4
         LDA (VZN),Y
         JSR PRSTATSCRPROC
         CMP #$FF
         BEQ PRSTATSCR2
         CMP #$FE
         BNE PRSTATSCR3
         LDA (VZN),Y
         STA VZN+4
         JSR PRSTATSCRPROC
         LDA #0
PRSTATSCR3 STA (VZN+2),Y
         INC VZN+2
         BNE PRSTATSCR4
         INC VZN+3
PRSTATSCR4 DEC VZN+4
         BNE PRSTATSCR3
         BEQ PRSTATSCR1
PRSTATSCR2 RTS 
;
PRSTATSCRPROC INC VZN
         BNE PRSTATSCRPROC1
         INC VZN+1
PRSTATSCRPROC1 RTS 
;
STATSCRDAT .BYTE $FE,14
         .SB "- STATYSTYKA GRY"
         .BYTE $FE,50
         .SB "ILO\:"
         .BYTE $FE,82
         .SB "NAJ]TYCH O^NIERZY:"
         .BYTE $FE,21
         .SB "ZABITYCH O^NIERZY:"
         .BYTE $FE,61
         .SB "STOCZONYCH BITEW:"
         .BYTE $FE,23
         .SB "WYGRANYCH BITEW:"
         .BYTE $FE,64
         .SB "OBL]E_ ZAMK W:"
         .BYTE $FE,25
         .SB "UDANYCH OBL]E_:"
         .BYTE $FE,56
         .SB "CZAS GRY:"
         .BYTE $FE,79
         .SB "KALENDARZOWY:"
         .BYTE $FE,5
         .SB "MIES."
         .BYTE $FE,17
         .SB "RZECZYWISTY:"
         .BYTE $FE,100
         .SB "Z^OTO:"
         .BYTE $FE,34
         .SB "O^NIERZE:"
         .BYTE $FE,110
         .SB "LICZBA PUNKT W:"
         .BYTE $FE,25
         .BYTE $FF
;
STATSCR  JSR WAITMOD
         LDA GRACZ
         PHA 
         LDA # <STATDL
         LDY # >STATDL
         LDX # >CHARGEN
         STA $D402
         STY $D403
         STX $D409
         LDA #0
         STA $D40E
         STA $D400
         LDA # <STATSCRNMI
         LDY # >STATSCRNMI
         STA $FFFA
         STY $FFFB
         LDY #34
         LDX #64
STATSCR1 LDA $D40B
         BNE STATSCR1
         STY $D400
         STX $D40E
         LDA #0
         STA $D01A
         STA $D018
         LDA #12
         STA $D017
         JSR PRSTATSCR
         LDY POM
         LDA HUMANPL,Y
         ASL
         ASL
         ASL
         TAY 
         LDX #0
STATSCR2 LDA NAMPLTAB,Y
         STA SCRPE+8,X
         INY 
         INX 
         CPX #5
         BNE STATSCR2
         LDA # <SCRPE+188
         LDY # >SCRPE+188
         STA VZN
         STY VZN+1
         LDA POM
         ASL
         TAX 
         LDA BUYSOLD+1,X
         TAY 
         LDA BUYSOLD,X
         LDX #0
         JSR CONVLONG
         LDY POM
         LDA HUMANPL,Y
         TAX 
         STX GRACZ
         LDA KSZN,X
         BEQ STATSCR3
         LDA ARMPOS,X
         TAY 
         TXA 
         JSR CRBUF
         JSR WOJKUPA
STATSCR3 LDA # <SCRPE+228
         LDY # >SCRPE+228
         STA VZN
         STY VZN+1
         LDA POM
         ASL
         TAY 
         LDA GRACZ
         ASL
         TAX 
         SEC 
         LDA BUYSOLD,Y
         SBC WOJZN,X
         STA ZN
         LDA BUYSOLD+1,Y
         SBC WOJZN+1,X
         TAY 
         LDX #0
         LDA ZN
         JSR CONVLONG
         LDA <SCRPE+306
         LDY >SCRPE+306
         STA VZN
         STY VZN+1
         LDY POM
         LDA NBITEW,Y
         LDY #0
         LDX #0
         JSR CONVLONG
         LDA <SCRPE+345
         LDY >SCRPE+345
         STA VZN
         STY VZN+1
         LDY POM
         LDA NWINBITEW,Y
         LDY #0
         LDX #0
         JSR CONVLONG
         LDA <SCRPE+424
         LDY >SCRPE+424
         STA VZN
         STY VZN+1
         LDY POM
         LDA NOBL,Y
         LDY #0
         LDX #0
         JSR CONVLONG
         LDA <SCRPE+465
         LDY >SCRPE+465
         STA VZN
         STY VZN+1
         LDY POM
         LDA NWINOBL,Y
         LDY #0
         LDX #0
         JSR CONVLONG
         LDA <SCRPE+622
         LDY >SCRPE+622
         STA VZN
         STY VZN+1
         LDY POM
         LDA NMCY,Y
         LDY #0
         LDX #0
         JSR CONVLONG
         LDY <SCRPE+661
         LDX >SCRPE+661
         JSR PRRTIMER
         LDA <SCRPE+767
         LDY >SCRPE+767
         STA VZN
         STY VZN+1
         LDA GRACZ
         ASL
         TAY 
         LDA KASAZN,Y
         STA ZN
         LDA KASAZN+1,Y
         TAY 
         LDA ZN
         LDX #0
         JSR CONVLONG
         LDA <SCRPE+811
         LDY >SCRPE+811
         STA VZN
         STY VZN+1
         LDA GRACZ
         ASL
         TAY 
         LDA WOJZN,Y
         STA ZN
         LDA WOJZN+1,Y
         TAY 
         LDA ZN
         LDX #0
         JSR CONVLONG
         JSR LICZPKT
         LDA <SCRPE+936
         LDY >SCRPE+936
         STA VZN
         STY VZN+1
         LDA ZN+2
         LDY ZN+3
         LDX #0
         JSR CONVLONG
         LDY #0
         LDA NOPCJA
         CMP #2
         BNE STATSCR4
         LDY POM
STATSCR4 JSR WAITFIRE
         JSR KONIECSCROFF
         PLA 
         STA GRACZ
         JMP WAITMOD
;
LICZPKTPROC STA ZN+4
         STY ZN
         STX ZN+1
LICZPKTPROC1 SEC 
         LDA ZN
         SBC ZN+4
         STA ZN+5
         LDA ZN+1
         SBC #0
         STA ZN+6
         BCC LICZPKTPROC2
         LDA ZN+5
         STA ZN
         LDA ZN+6
         STA ZN+1
         INC ZN+2
         BNE LICZPKTPROC1
         INC ZN+3
         BNE LICZPKTPROC1
         LDA #255
         STA ZN+2
         STA ZN+3
         BNE LICZPKTPROC1
LICZPKTPROC2 LDA ZN
         ORA ZN+1
         BEQ LICZPKTPROC3
         INC ZN+2
         BNE LICZPKTPROC3
         INC ZN+3
         BNE LICZPKTPROC3
         LDA #255
         STA ZN+2
         STA ZN+3
LICZPKTPROC3 RTS 
;
LICZPKTPROCB CLC 
         ADC ZN+2
         TAX 
         TYA 
         ADC ZN+3
         TAY 
         BCC LICZPKTPROCB1
         LDX #255
         LDY #255
LICZPKTPROCB1 STX ZN+2
         STY ZN+3
         RTS 
;
LICZPKTPROCC STA ZN
         STY ZN+1
         SEC 
         LDA ZN+2
         SBC ZN
         TAY 
         LDA ZN+3
         SBC ZN+1
         BCS LICZPKTPROCC1
         LDA #0
         TAY 
LICZPKTPROCC1 STY ZN+2
         STA ZN+3
         RTS 
;
LICZPKT  LDA #0
         STA ZN+2
         STA ZN+3
         LDA GRACZ
         TAY 
         ASL
         TAX 
         PHA 
         LDA KSZN,Y
         BEQ LICZPKT1
         LDA QUITZN
         BNE LICZPKT1
         LDA KASAZN,X
         TAY 
         LDA KASAZN+1,X
         TAX 
         LDA #100
         JSR LICZPKTPROC
         PLA 
         TAX 
         LDA WOJZN,X
         TAY 
         LDA WOJZN+1,X
         TAX 
         LDA #200
         JSR LICZPKTPROC
         LDY POM
         LDA NWINBITEW,Y
         LDY #0
         JSR LICZPKTPROCB
         LDY POM
         LDA NWINOBL,Y
         LDY #0
         JSR LICZPKTPROCB
         LDX POM
         LDA NMCY,X
         CMP #55
         BCS LICZPKT3
         SEC 
         LDA #54
         SBC NMCY,X
         LDY #0
         JSR LICZPKTPROCB
         JMP LICZPKT2
LICZPKT3 SEC 
         LDA NMCY,X
         SBC #54
         STA VZN
         LDA #0
         STA VZN+1
LICZPKT4 INC VZN+1
         LDA VZN+1
         LDY #0
         JSR LICZPKTPROCC
         DEC VZN
         BNE LICZPKT4
         BEQ LICZPKT2
LICZPKT1 PLA 
         TAX 
         LDA KASAZN,X
         TAY 
         LDA KASAZN+1,X
         TAX 
         LDA #200
         JSR LICZPKTPROC
         LDY POM
         LDA NWINBITEW,Y
         LDY #0
         JSR LICZPKTPROCB
LICZPKT2 RTS 
;
STATSCRNMI CLD 
         PHA 
         TYA 
         PHA 
         TXA 
         PHA 
         LDA $D40F
         STA $D40F
         ASL
         ASL
         BCC STATSCRNMI1
         JSR MUSICPLAY
STATSCRNMI1 PLA 
         TAX 
         PLA 
         TAY 
         PLA 
         RTI 
;
TRUPPICCOLTAB .BYTE 21,23,24,18,0
;
PLTRUPPIC LDA #$00
         STA $D40E
         STA $D400
         LDA # <STATSCRNMI
         LDY # >STATSCRNMI
         STA $FFFA
         STY $FFFB
         LDA # <TRUPPICDL
         LDY # >TRUPPICDL
         LDX # >SCRPE
         STA $D402
         STY $D403
         STX $D409
         LDY #$00
PLTRUPPIC1 LDA TRUPPICDAT,Y
         STA SCRPE,Y
         LDA #0
         STA SCRPE+$0200,Y
         INY 
         BNE PLTRUPPIC1
         LDY #$17
PLTRUPPIC2 LDA TRUPPICDAT+$0100,Y
         STA SCRPE+$0100,Y
         DEY 
         BPL PLTRUPPIC2
         LDA <TRUPPICDAT+280
         LDY >TRUPPICDAT+280
         STA VZN
         STY VZN+1
         LDA <SCRPE+$0200+$08
         LDY >SCRPE+$0200+$08
         STA VZN+2
         STY VZN+3
         LDX #8
PLTRUPPIC3 LDY #15
PLTRUPPIC4 LDA (VZN),Y
         STA (VZN+2),Y
         DEY 
         BPL PLTRUPPIC4
         CLC 
         LDA VZN
         ADC #16
         STA VZN
         BCC PLTRUPPIC5
         INC VZN+1
PLTRUPPIC5 CLC 
         LDA VZN+2
         ADC #32
         STA VZN+2
         BCC PLTRUPPIC6
         INC VZN+3
PLTRUPPIC6 DEX 
         BNE PLTRUPPIC3
         LDY #4
PLTRUPPIC7 LDA TRUPPICCOLTAB,Y
         STA $D016,Y
         DEY 
         BPL PLTRUPPIC7
         LDY #33
         LDX #64
PLTRUPPIC8 LDA $D40B
         BNE PLTRUPPIC8
         STY $D400
         STX $D40E
         LDY #0
         LDA NOPCJA
         CMP #2
         BNE PLTRUPPIC9
         LDY POM
PLTRUPPIC9 JSR WAITFIRE
         JMP KONIECSCROFF
;
PLKONIECPICPROC LDY #0
PLKONIECPICPROC1 STA (VZN),Y
         INC VZN
         BNE PLKONIECPICPROC2
         INC VZN+1
PLKONIECPICPROC2 DEX 
         BNE PLKONIECPICPROC1
         RTS 
;
PLKONIECPICTAB .BYTE 112,3,64+15,1, <KONIECPIC,1, >KONIECPIC,1,15,88
         .BYTE 64+15,1, <(KONIECPIC+3560),1, >(KONIECPIC+3560),1,15,101
         .BYTE 48+128,1,0,1,64+2+16,1, <INFOLINE,1, >INFOLINE,1
         .BYTE 65,1, <SCRPE,1, >SCRPE,1,255,255
;
PLKONIECPIC LDA <SCRPE
         LDY >SCRPE
         LDX #0
         STA VZN
         STY VZN+1
         STX VZN+2
PLKONIECPIC1 LDY VZN+2
         LDA PLKONIECPICTAB+1,Y
         TAX 
         LDA PLKONIECPICTAB,Y
         CMP #255
         BEQ PLKONIECPIC2
         JSR PLKONIECPICPROC
         INC VZN+2
         INC VZN+2
         JMP PLKONIECPIC1
PLKONIECPIC2 LDA #0
         LDY #47
PLKONIECPIC3 STA INFOLINE,Y
         DEY 
         BPL PLKONIECPIC3
         LDA # <SCRPE
         LDY # >SCRPE
         STA $D402
         STY $D403
         LDA #0
         LDY #$0C
         LDX # >CHARGEN
         STA $D016
         STA $D018
         STA $D019
         STA $D01A
         STY $D017
         STX $D409
         LDA #1
         STA NRTEXT
         JSR TEXTSCROLLINIT
         LDA #65
         STA $D01B
         LDY #34
         LDX #192
PLKONIECPIC4 LDA $D40B
         BNE PLKONIECPIC4
         STY $D400
         STX $D40E
         RTS 
;
WINGAME  LDA # <WINGAMENMI
         LDY # >WINGAMENMI
         STA $FFFA
         STY $FFFB
         JSR MUSICOFF
         LDA #0
         JSR MUSICON
         JSR PLKONIECPIC
WINGAME1 LDA $D01F
         AND #$07
         BNE WINGAME1
         JSR KONIECSCROFF
         JSR MUSICOFF
         LDA #$01
         STA $D01B
         JMP MUSICON
;
WINGAMENMI CLD 
         PHA 
         TYA 
         PHA 
         TXA 
         PHA 
         LDA $D40F
         STA $D40F
         ASL
         BCC WINGAMENMI1
         JSR WINGAMEDLI
         JMP WINGAMENMI2
WINGAMENMI1 ASL
         BCC WINGAMENMI2
         JSR WINGAMEVBL
WINGAMENMI2 PLA 
         TAX 
         PLA 
         TAY 
         PLA 
         RTI 
;
WINGAMEVBL LDA #$41
         STA $D01B
         JSR TEXTSCROLL
         JMP MUSICPLAY
;
WINGAMEDLI LDA #$01
         STA $D01B
         RTS 
;
KONIECTEXT .BYTE $FE,10,0
         .SB "GRATULACJE!!!"
         .BYTE $FE,10,0
         .SB "ZJEDNOCZY^E ROZBITE KR LESTWO!"
         .BYTE $FE,10,0
         .SB "ZOSTA^E  W ^ A D C [ !!!"
         .BYTE $FE,20,0
         .SB "MOESZ TERAZ POZOSTA\ W WIECIE, W KT RYM WYNIESIONO CI] NA TRON LUB PR BOWA\ POWR CI\ DO "
         .SB "SWOJEGO CZASU W GRZE: �נޠ��Ġà�����"
         .BYTE $FE,48,0
         .SB "LECZ WCZENIEJ POSZUKAJ W SKLEPIE NASZEJ NAST]PNEJ GRY: �РɠҠ��àɠ"
         .SB " (JU WKR TCE)"
         .BYTE $FE,48,0
         .SB "POWR T DO GRY: �����,������,������."
         .BYTE $FE,100,0
         .BYTE $FF
;

