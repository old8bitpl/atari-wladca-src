;
; MODUL: TURNIEJ
;

STLOTDAT 
	.BYTE $00, $03, $05, $08   
	.BYTE $0A, $0C, $0E, $10
	.BYTE $12, $14, $16, $18
	.BYTE $1A, $1C, $1E, $20
	.BYTE $22, $20, $24, $25
	.BYTE $27, $28, $2A, $2C
	.BYTE $2D, $2F, $30, $31
	.BYTE $33, $34, $35, $36
	.BYTE $38
	.BYTE $39, $3A, $3B, $3C   
	.BYTE $3D, $3E, $3F, $40
	.BYTE $40, $41, $42, $43
	.BYTE $43, $44, $45, $45
	.BYTE $46, $46, $46, $47
	.BYTE $47, $48, $48, $48
	.BYTE $48, $48, $48, $48
	.BYTE $48, $48, $48, $48
	.BYTE $48, $48, $48, $48   
	.BYTE $47, $47, $46, $46
	.BYTE $46, $45, $45, $44
	.BYTE $43, $43, $42, $41
	.BYTE $40, $40, $3F, $3E
	.BYTE $3D, $3C, $3B, $3A
	.BYTE $39, $38, $36, $35
	.BYTE $34, $33, $31, $30
	.BYTE $2F, $2D, $2C, $2A   
	.BYTE $28, $27, $25, $24
	.BYTE $22, $20, $1E, $1C
	.BYTE $1A, $18, $16, $14
	.BYTE $12, $10, $0E, $0C
	.BYTE $0A, $08, $05, $03
	.BYTE $00, $00, $00, $00
	.BYTE $00, $00, $00, $00
;
LICZSTPOS LDY IPOSST
         BPL LICZSTPOS13
LICZSTPOS14 JMP LICZSTPOS10
LICZSTPOS13 LDA HITSTZN
         BPL LICZSTPOS14
         LDA STLOTDAT,Y
         STA IZN+1
         LDA #0
         STA IZN
         STA IZN+2
         STA IZN+3
         LDY #6
LICZSTPOS1 LSR IZN+1
         ROR IZN
         DEY 
         BNE LICZSTPOS1
         LDA YCEL
         STA IZN+4
         LDY #8
LICZSTPOS2 LSR IZN+4
         BCC LICZSTPOS3
         CLC 
         LDA IZN+2
         ADC IZN
         STA IZN+2
         LDA IZN+3
         ADC IZN+1
         STA IZN+3
LICZSTPOS3 ASL IZN
         ROL IZN+1
         DEY 
         BNE LICZSTPOS2
         LDA YCEL
         LSR
         CLC 
         ADC YCEL
         CLC 
         ADC IZN+3
         STA IZN
         LDA #129
         SEC 
         SBC IZN
         TAX 
         LDY #0
         TYA 
LICZSTPOS4 STA PMBASE+$0700,Y
         INY 
         BNE LICZSTPOS4
         JSR CHKLOTST
         JSR CHKWIATR
         LDA FAZAST
         ASL
         ASL
         ASL
         ASL
         ASL
         TAY 
         LDA #32
LICZSTPOS5 PHA 
         LDA STDAT,Y
         STA PMBASE+$0700,X
         INY 
         INX 
         PLA 
         SEC 
         SBC #1
         BNE LICZSTPOS5
         LDA XPOSST
         STA $D003
         LDA NTARCZA
         TAY 
         ASL
         ASL
         TAX 
         LDA #4
         STA IZN+1
LICZSTPOS11 LDA XPOSST
         CMP OXYTAB,X
         BCC LICZSTPOS9
         CMP OXYTAB+1,X
         BCS LICZSTPOS9
         LDA DISTST
         CMP TDISTTAB,Y
         BCC LICZSTPOS9
         BNE LICZSTPOS8
         LDA IZN
         CMP OXYTAB+2,X
         BCC LICZSTPOS9
         CMP OXYTAB+3,X
         BCS LICZSTPOS9
         INC HITSTZN
         JMP LICZSTPOS9
LICZSTPOS8 LDA IZN+1
         CMP #4
         BNE LICZSTPOS9
         LDA IZN
         CMP OXYTAB+3,X
         BCS LICZSTPOS9
         LDA #7
         STA FAZAST
         BNE LICZSTPOS12
LICZSTPOS9 TXA 
         CLC 
         ADC #12
         TAX 
         DEC IZN+1
         BNE LICZSTPOS11
         LDA HITSTZN
         BPL LICZSTPOS10
LICZSTPOS12 LDA YCEL
         ASL
         CMP IPOSST
         BNE LICZSTPOS6
         SEC 
         LDA #128
         SBC YCEL
         SBC YCEL
         STA IPOSST
         JMP LICZSTPOS7
LICZSTPOS6 INC IPOSST
LICZSTPOS7 INC DISTST
LICZSTPOS10 RTS 
;
CHKLOTST LDA FAZAST
         CMP #7
         BEQ CHKLOTST3
         LDA DISTST
         LDY #0
CHKLOTST1 CMP POSLOTSTTAB,Y
         BNE CHKLOTST2
         STY FAZAST
         BEQ CHKLOTST3
CHKLOTST2 INY 
         CPY #8
         BNE CHKLOTST1
CHKLOTST3 RTS 
;
CHKWIATR LDA IPOSST
         CMP #64
         BCC CHKWIATR2
         AND #7
         BNE CHKWIATR2
         LDA FLAGAFAZAZN
         LSR
         TAY 
         BNE CHKWIATR1
         LDX XPOSST
         BEQ CHKWIATR2
         INC XPOSST
         JMP CHKWIATR2
CHKWIATR1 DEY 
         BNE CHKWIATR2
         LDX XPOSST
         BEQ CHKWIATR2
         DEC XPOSST
CHKWIATR2 RTS 
;
POSLOTSTTAB .BYTE 0,5,10,15,20,25,30,90
;
STDAT    
		 .BYTE $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01
		 .BYTE $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01
		 
		 .BYTE $00, $00, $00, $00, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01
		 .BYTE $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $00, $00, $00, $00
		 
		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $01, $01, $01, $01, $01, $01, $01, $01
		 .BYTE $01, $01, $01, $01, $01, $01, $01, $01, $00, $00, $00, $00, $00, $00, $00, $00
		 
		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01, $01, $01, $01
		 .BYTE $01, $01, $01, $01, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00

		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01, $01, $01
		 .BYTE $01, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00

		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01
		 .BYTE $01, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00

		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $01
		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		 
		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
		 .BYTE $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
;
OXYTAB   .BYTE 109,124,7,32,113,120,12,24,117,121,18,26
         .BYTE 112,122,10,27,114,119,12,24,117,121,18,26
         .BYTE 113,121,14,23,115,118,15,21,118,120,19,20
         .BYTE 116,118,16,17,116,117,16,17,119,120,19,20
;
TDISTTAB .BYTE 20,36,48
;
PLTURNIEJ STA POM+1
         LDY #0
         CMP HUMANPL
         BEQ PLTURNIEJ6
         CMP HUMANPL+1
         BEQ PLTURNIEJ7
         TAX 
         JMP ALLPKTUPPROC
PLTURNIEJ7 LDA NOPCJA
         CMP #2
         BNE PLTURNIEJ6
         INY 
PLTURNIEJ6 STY POM+2
         LDY #0
         STY $D007
         JSR PLUPTARCZA
         JSR PLTARCZAFAZA
         LDA $D20A
         AND #63
         CLC 
         ADC #85
         STA XCEL
         LDA $D20A
         AND #31
         PHA 
         EOR #31
         STA YCEL
         JSR PLLUK3
         PLA 
         STA YCEL
         JSR WIATRINIT
         LDA #4
         STA ZN+8
         LDA # <STRZALAEFTXT
         LDY # >STRZALAEFTXT
         CLC 
         JSR PRINT
         LDA POM+1
         LDY #1
         JSR PRINTPLNAME
         LDA # <NSTRZALTXT
         LDY # >NSTRZALTXT
         SEC 
         JSR PRINT
         JSR SILTLUM
PLTURNIEJ1 LDA ZN+8
         BNE PLTURNIEJ14
         JMP PLTURNIEJ12
PLTURNIEJ14 LDA #0
         STA IPOSST
         STA DISTST
         STA FAZAST
         LDA YCEL
         EOR #31
         STA YCEL
         JSR LUK
         LDA YCEL
         EOR #31
         STA YCEL
         PHA 
         JSR DYCELPROC
         LDA #255
         STA HITSTZN
         LDY # <LOTST
         LDX # >LOTST
         JSR SETVBLPROC
PLTURNIEJ2 LDA HITSTZN
         BPL PLTURNIEJ3
         LDA IPOSST
         BPL PLTURNIEJ2
PLTURNIEJ3 LDA #0
         STA $D007
         LDY HITSTZN
         INY 
         BNE PLTURNIEJ4
         STY HITSTZN
PLTURNIEJ4 LDY # <STVBLPROC
         LDX # >STVBLPROC
         JSR SETVBLPROC
         DEC ZN+8
         LDX POM+1
         CLC 
         LDA HITSTZN
         ADC ZN,X
         STA ZN,X
         JSR PRTURNIEJSTRZAL
         LDA DISTST
         CMP #90
         BCC PLTURNIEJ5
         LDY #2
         JSR PLUPTARCZA
         LDA $D20A
         AND #3
         CLC 
         ADC #$01
         JSR PLAYDIGI
         LDY POM+2
         JSR WAITFIRE
PLTURNIEJ5 LDY #$00
         LDA NTARCZA
         BEQ PLTURNIEJ13
         LDA HITSTZN
         BEQ PLTURNIEJ13
         INY 
PLTURNIEJ13 TYA 
         PHA 
         JSR PLUPTARCZA
         PLA 
         TAY 
         BEQ PLTURNIEJ11
         JSR PLHITUPTAR
PLTURNIEJ11 PLA 
         STA YCEL
         JMP PLTURNIEJ1
PLTURNIEJ12 LDY POM+2
         JSR WAITFIRE
         LDY #$00
         STY $D003
         STY $D007
         JSR PLUPTARCZA
         JMP GLSTLUM
;
PRTURNIEJSTRZAL LDA ZN+8
         ORA #16
         STA MENULINE+23
         LDA HITSTZN
         ORA #16
         STA INFOLINE+27
         LDX POM+1
         LDY #16
         LDA ZN,X
PRTURNIEJSTRZAL1 CMP #10
         BCC PRTURNIEJSTRZAL2
         SBC #10
         INY 
         BNE PRTURNIEJSTRZAL1
PRTURNIEJSTRZAL2 ORA #16
         STY INFOLINE+37
         STA INFOLINE+38
         RTS 
;
ALLPKTUP LDX #3
ALLPKTUP1 CPX HUMANPL
         BEQ ALLPKTUP2
         CPX HUMANPL+1
         BEQ ALLPKTUP2
         LDA ZN+4,X
         BNE ALLPKTUP2
         JSR ALLPKTUPPROC
ALLPKTUP2 DEX 
         BPL ALLPKTUP1
         RTS 
;
ALLPKTUPPROC LDY #4
ALLPKTUPPROC1 LDA $D20A
         AND #3
         ADC ZN,X
         STA ZN,X
         DEY 
         BNE ALLPKTUPPROC1
         RTS 
;
STRZALAEFTXT .SB "      :   PUNKTY ZA STRZA", $5E, ":    RAZEM:00 "
NSTRZALTXT .SB "               STRZA", $5E, "Y:4                "
;
LOTST    JSR STVBLPROC
         JMP LICZSTPOS
;
STVBLPROC JSR WIATROBS
         JMP PLFLAGAFAZA
;
LUKVBL   JSR STVBLPROC
         JMP PLLUK
;
DYCELPROC LDA FLAGAFAZAZN
         LSR
         TAY 
         DEY 
         LDA WIATRSILAZN
         EOR #3
         DEY 
         BNE DYCELPROC1
         EOR #255
         CLC 
         ADC YCEL
         BPL DYCELPROC2
         LDA #0
         BEQ DYCELPROC2
DYCELPROC1 DEY 
         BNE DYCELPROC3
         CLC 
         ADC YCEL
         CMP #32
         BCC DYCELPROC2
         LDA #31
DYCELPROC2 STA YCEL
DYCELPROC3 RTS 
;
LUK      LDY # <LUKVBL
         LDX # >LUKVBL
         JSR SETVBLPROC
LUK1     LDY POM+2
         JSR GETFIRE
         BNE LUK1
         LDY # <STVBLPROC
         LDX # >STVBLPROC
         JSR SETVBLPROC
         LDA XCEL
         STA XPOSST
         RTS 
;
PLLUK    LDY POM+2
         JSR GETJOY
         STA POM
         JSR CHKPOZ
         JSR CHKPION
PLLUK3   LDA XCEL
         STA $D000
         STA $D001
         STA $D002
         CLC 
         ADC #2
         STA $D004
         LDY #$20
         LDX #184
PLLUK1   LDA #64
         STA PMBASE+$0400,Y
         LDA #32
         STA PMBASE+$0500,Y
         LDA #8
         STA PMBASE+$0600,Y
         LDA PMBASE+$0300,Y
         AND #$FC
         ORA #$01
         STA PMBASE+$0300,Y
         INY 
         DEX 
         BNE PLLUK1
         LDA YCEL
         LSR
         CLC 
         ADC YCEL
         PHA 
         TAY 
         LDX #18
PLLUK2   LDA #32
         STA PMBASE+$0400+61,Y
         LDA #0
         STA PMBASE+$0400+61+1,Y
         LDA #192
         STA PMBASE+$0400+61+2,Y
         LDA #224
         STA PMBASE+$0400+61+3,Y
         LDA #204
         STA PMBASE+$0500+61,Y
         LDA #204
         STA PMBASE+$0500+61+1,Y
         LDA #32
         STA PMBASE+$0500+61+2,Y
         LDA #0
         STA PMBASE+$0500+61+3,Y
         LDA #0
         STA PMBASE+$0600+61,Y
         LDA #32
         STA PMBASE+$0600+61+1,Y
         LDA #12
         STA PMBASE+$0600+61+2,Y
         LDA #12
         STA PMBASE+$0600+61+3,Y
         INY 
         INY 
         INY 
         INY 
         DEX 
         BNE PLLUK2
         PLA 
         TAY 
         LDA #12+3
         STA PMBASE+$0600+61+35,Y
         LDA #0+3
         STA PMBASE+$0600+61+35+1,Y
         RTS 
;
PLTARCZAFAZA LDA # <TARCZAFAZATAB
         LDY # >TARCZAFAZATAB
         LDX NTARCZA
PLTARCZAFAZA1 DEX 
         BMI PLTARCZAFAZA2
         CLC 
         ADC #128
         BCC PLTARCZAFAZA1
         INY 
         BNE PLTARCZAFAZA1
PLTARCZAFAZA2 STA VZN
         STY VZN+1
         LDY #0
PLTARCZAFAZA3 LDA (VZN),Y
         STA TARCZAPIC+80*8,Y
         INY 
         BPL PLTARCZAFAZA3
         LDA #$50
         LDY NTARCZA
         BEQ PLTARCZAFAZA4
         LDA #$D0
         LDY #0
PLTARCZAFAZA4 LDX #$04
PLTARCZAFAZA5 STA TARCZAPIC+1024+417,Y
         CLC 
         ADC #$01
         INY 
         DEX 
         BNE PLTARCZAFAZA5
         PHA 
         TYA 
         CLC 
         ADC #36
         TAY 
         PLA 
         CPY #160
         BNE PLTARCZAFAZA4
         RTS 
;
WIATROBS DEC WIATRPAUZAZN
         BNE WIATROBS1
WIATRINIT LDA $D20A
         STA WIATRPAUZAZN
WIATROBS2 LDA $D20A
         AND #7
         CMP #5
         BCS WIATROBS2
         ASL
         STA FLAGAFAZAZN
         LDA $D20A
         AND #24
         LSR
         LSR
         LSR
         STA WIATRSILAZN
         CLC 
         ADC #4
         STA SFLAGAPAUZAZN
         STA FLAGAPAUZAZN
WIATROBS1 RTS 
;
PLFLAGAFAZA DEC SFLAGAPAUZAZN
         BNE PLFLAGAFAZA4
         LDA FLAGAPAUZAZN
         STA SFLAGAPAUZAZN
         LDX FLAGAFAZAZN
         LDA # <FLAGAFAZATAB
         LDY # >FLAGAFAZATAB
PLFLAGAFAZA1 DEX 
         BMI PLFLAGAFAZA2
         CLC 
         ADC #16
         BCC PLFLAGAFAZA1
         INY 
         BNE PLFLAGAFAZA1
PLFLAGAFAZA2 STA IZN
         STY IZN+1
         LDY #15
PLFLAGAFAZA3 LDA (IZN),Y
         STA TARCZAPIC+126*8,Y
         DEY 
         BPL PLFLAGAFAZA3
         LDA FLAGAFAZAZN
         EOR #1
         STA FLAGAFAZAZN
PLFLAGAFAZA4 RTS 
;
DIGIPROC INC DZN+6
         LDA DZN+6
         CMP DZN+5
         BNE DIGIPROC2
         LDY #0
         STY DZN+6
         LDA (DZN),Y
         LDX DZN+4
         BNE DIGIPROC1
         AND #15
         JSR DIGIPROCA
         INC DZN+4
         BNE DIGIPROC2
DIGIPROC1 LSR
         LSR
         LSR
         LSR
         JSR DIGIPROCA
         DEC DZN+4
         INC DZN
         BNE DIGIPROC3
         INC DZN+1
DIGIPROC3 LDA DZN+2
         BNE DIGIPROC4
         DEC DZN+3
DIGIPROC4 DEC DZN+2
         LDA DZN+2
         ORA DZN+3
         BNE DIGIPROC2
         LDA #255
         STA DZN+7
DIGIPROC2 RTS 
;
DIGIPROCA ORA #16
         STA $D207
         RTS 
;
PLAYDIGI STA DZN+5
         LDA # <KRZYKDAT
         LDY # >KRZYKDAT
         STA DZN
         STY DZN+1
         LDA # <1786
         LDY # >1786
         STA DZN+2
         STY DZN+3
         LDA #$00
         STA DZN+4
         STA DZN+6
         STA DZN+7
PLAYDIGI1 JSR DIGIPROC
         LDA DZN+7
         BEQ PLAYDIGI1
         LDA #$01
         STA $D207
         RTS 
;
GLSTLUM  LDY #$01
GLSTLUM1 STY $D207
         LDA #$05
         JSR WAIT
         INY 
         CPY #$05
         BNE GLSTLUM1
         RTS 
;
SILTLUM  LDY #$04
SILTLUM1 STY $D207
         LDA #$05
         JSR WAIT
         DEY 
         BNE SILTLUM1
         RTS 
;
PLUPTARCZATAB .BYTE 0,62,96
;
PLUPTARCZA LDA PLUPTARCZATAB,Y
         STA VZN
         LDY #0
PLUPTARCZA2 LDX #4
PLUPTARCZA1 LDA VZN
         STA TARCZAPIC+1024+41,Y
         INY 
         LDA VZN
         BEQ PLUPTARCZA3
         INC VZN
PLUPTARCZA3 DEX 
         BNE PLUPTARCZA1
         TYA 
         CLC 
         ADC #36
         TAY 
         CPY #160
         BNE PLUPTARCZA2
         RTS 
;
TURNIEJ  LDA #6
         LDY #8
         LDX #10
         STA $D012
         STY $D013
         STX $D014
         LDA #0
         STA $D015
         TAY 
TURNIEJ1 STA PMBASE+$0400,Y
         STA PMBASE+$0500,Y
         STA PMBASE+$0600,Y
         STA PMBASE+$0700,Y
         STA PMBASE+$0300,Y
         INY 
         BNE TURNIEJ1
         LDA #85
         LDY #149
         STA XCELMIN
         STY XCELMAX
         LDA #0
         LDY #31
         STA YCELMIN
         STA YCEL
         STY YCELMAX
         LDA #0
         STA NTARCZA
         LDA #6
         JSR SETSCR
         LDA #7
         STA $D206
         JSR ELIMFIRST
TURNIEJ2 LDA #0
         STA ZN
         STA ZN+1
         STA ZN+2
         STA ZN+3
         LDY HUMANPL
         LDA ZN+4,Y
         BEQ TURNIEJ6
         LDY HUMANPL+1
         LDA ZN+4,Y
         BEQ TURNIEJ6
         JSR ALLPKTUP
         JSR ELIMRUNDA
         JMP TURNIEJ11
TURNIEJ6 LDA #0
TURNIEJ12 PHA 
         TAY 
         LDA ZN+4,Y
         BNE TURNIEJ13
         TYA 
         JSR PLTURNIEJ
TURNIEJ13 PLA 
         CLC 
         ADC #1
         CMP #4
         BNE TURNIEJ12
         CLC 
         JSR PRINTNULL
         SEC 
         JSR PRINTNULL
         JSR PRSTRUNDA
         LDY #255
         JSR WAITFIRE
TURNIEJ7 LDA IMMZN
         BNE TURNIEJ11
         LDA $D01F
         AND #$07
         CMP #$03
         BNE TURNIEJ11
         LDX HUMANPL
         LDA #0
         STA ZN+4,X
         BEQ TURNIEJ8
TURNIEJ11 INC NTARCZA
         LDA NTARCZA
         CMP #3
         BNE TURNIEJ2
         LDX HUMANPL
         CPX #255
         BEQ TURNIEJ14
         LDA ZN+4,X
         BEQ TURNIEJ8
TURNIEJ14 LDX HUMANPL+1
         CPX #255
         BEQ TURNIEJ15
         LDA ZN+4,X
         BEQ TURNIEJ8
TURNIEJ15 LDX #3
TURNIEJ9 LDA ZN+4,X
         BEQ TURNIEJ10
         DEX 
         BPL TURNIEJ9
TURNIEJ10 JSR TURNIEJZLOTOUP
         JMP TURNIEJ3
TURNIEJ8 LDY #7
         LDA #0
TURNIEJ5 STA $D000,Y
         DEY 
         BPL TURNIEJ5
         TXA 
         PHA 
         JSR TURNIEJZLOTOUP
         LDA #7
         JSR SETSCR
         LDA # <WINTURNIEJ1TXT
         LDY # >WINTURNIEJ1TXT
         CLC 
         JSR PRINT
         PLA 
         PHA 
         LDY #12
         JSR PRINTPLNAME
         LDA # <WINTURNIEJ2TXT
         LDY # >WINTURNIEJ2TXT
         SEC 
         JSR PRINT
         JSR GLSTLUM
         PLA 
         LDY #0
         CMP HUMANPL
         BEQ TURNIEJ16
         LDA NOPCJA
         CMP #2
         BNE TURNIEJ16
         INY 
TURNIEJ16 JSR WAITFIRE
TURNIEJ3 LDA #0
         LDY #7
TURNIEJ4 STA $D200,Y
         STA $D000,Y
         DEY 
         BPL TURNIEJ4
         LDA #0
         JSR SETSCR
         LDA HUMANPL
         JSR POSARM
         LDA HUMANPL+1
         JMP POSARM
;
WINTURNIEJ1TXT .SB " GRATULACJE      !  WYGRA", $5E, "E", $01, " TURNIEJ!!! "
WINTURNIEJ2TXT .SB " NAGRODA: 1000 SZTUK Z", $5E, "OTA JEST TWOJA!  "
;
STRUNDATXT .SB "        :    PKT    "
;
PRSTRUNDA LDY #0
         STY VZN
         STY VZN+1
PRSTRUNDA1 LDX VZN
         LDA ZN+4,X
         BNE PRSTRUNDA2
         LDA VZN+1
         ASL
         ASL
         STA VZN+2
         ASL
         ASL
         CLC 
         ADC VZN+2
         STA VZN+2
         TAY 
         LDX #0
PRSTRUNDA3 LDA STRUNDATXT,X
         STA INFOLINE,Y
         INX 
         INY 
         CPX #20
         BNE PRSTRUNDA3
         CLC 
         LDA VZN+2
         ADC #3
         TAY 
         LDA VZN
         JSR PRINTPLNAME
         LDY VZN
         LDA ZN,Y
         LDX #16
PRSTRUNDA4 CMP #10
         BCC PRSTRUNDA5
         SBC #10
         INX 
         BNE PRSTRUNDA4
PRSTRUNDA5 ORA #16
         LDY VZN+2
         STA INFOLINE+11,Y
         TXA 
         STA INFOLINE+10,Y
         INC VZN+1
PRSTRUNDA2 INC VZN
         LDA VZN
         CMP #4
         BNE PRSTRUNDA1
;
ELIMRUNDA LDA #255
         STA VZN
         LDY #0
         LDX #3
ELIMRUNDA1 LDA ZN+4,X
         BNE ELIMRUNDA2
         INY 
         LDA ZN,X
         CMP VZN
         BEQ ELIMRUNDA5
         BCS ELIMRUNDA2
ELIMRUNDA5 STA VZN
         STX VZN+1
ELIMRUNDA2 DEX 
         BPL ELIMRUNDA1
         CPY #3
         BCS ELIMRUNDA4
         LDA NTARCZA
         CMP #2
         BNE ELIMRUNDA3
ELIMRUNDA4 LDY VZN+1
         LDA #255
         STA ZN+4,Y
ELIMRUNDA3 RTS 
;
ELIMFIRST LDX #3
ELIMFIRST1 LDY #0
         LDA KSZN,X
         BNE ELIMFIRST2
         DEY 
ELIMFIRST2 TYA 
         STA ZN+4,X
         DEX 
         BPL ELIMFIRST1
         RTS 
;
TURNIEJZLOTOUP TXA 
         ASL
         TAX 
         CLC 
         LDA KASAZN,X
         ADC # <1000
         STA VZN
         LDA KASAZN+1,X
         ADC # >1000
         STA VZN+1
         BCC TURNIEJZLOTOUP1
         LDA #255
         STA VZN
         STA VZN+1
TURNIEJZLOTOUP1 LDA VZN
         STA KASAZN,X
         LDA VZN+1
         STA KASAZN+1,X
         RTS 
;
PLHITUPTARTAB
         .BYTE $01,$00,$0B,$04
         .BYTE $01,$0D,$0B,$0F
         .BYTE $01,$04,$02,$0D
         .BYTE $09,$04,$0B,$0D
;
         .BYTE $02,$04,$09,$08
         .BYTE $02,$09,$09,$0D
         .BYTE $02,$08,$05,$09
         .BYTE $07,$08,$09,$09
;
         .BYTE $05,$08,$07,$09
         .BYTE $05,$08,$07,$09
         .BYTE $05,$08,$07,$09
         .BYTE $05,$08,$07,$09
;
PLHITUPTAR LDY HITSTZN
         DEY 
         TYA 
         ASL
         ASL
         ASL
         ASL
         STA VZN
         LDA $D20A
         AND #$0C
         ORA VZN
         TAX 
PLHITUPTAR1 LDA $D20A
         AND #$0F
         CMP PLHITUPTARTAB,X
         BCC PLHITUPTAR1
         CMP PLHITUPTARTAB+2,X
         BCS PLHITUPTAR1
         ADC #$35+2
         STA $D007
PLHITUPTAR2 LDA $D20A
         AND #$0F
         CMP PLHITUPTARTAB+1,X
         BCC PLHITUPTAR2
         CMP PLHITUPTARTAB+3,X
         BCS PLHITUPTAR2
         ADC #$2B-2
         PHA 
         LDY #$20
         LDX #184
         LDA #$01
PLHITUPTAR3 STA PMBASE+$0300,Y
         INY 
         DEX 
         BNE PLHITUPTAR3
         PLA 
         TAX 
         LDY #8
         LDA #$80+$01
PLHITUPTAR4 STA PMBASE+$0300,X
         INX 
         DEY 
         BNE PLHITUPTAR4
         RTS 
;

