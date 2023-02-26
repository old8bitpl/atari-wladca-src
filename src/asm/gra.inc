;
; MODUL: GRA
;

COLORSTABB .BYTE 0,10,0,0,0
;
ANIMPROC INC ANIMPAUZA
         LDA ANIMPAUZA
         CMP #6
         BCC ANIMPROC1
         LDA #0
         STA ANIMPAUZA
         LDA ANIMFAZA
         ASL
         ASL
         ASL
         CLC 
         ADC # <ANIMBUF
         STA IZN
         LDA # >ANIMBUF
         ADC #0
         STA IZN+1
         LDA #9
         STA IZN+2
         LDX #0
ANIMPROC2 LDY #0
ANIMPROC3 LDA (IZN),Y
         STA MAPAPIC+82*8,X
         INY 
         INX 
         CPY #8
         BNE ANIMPROC3
         CLC 
         LDA IZN
         ADC #32
         STA IZN
         BCC ANIMPROC4
         INC IZN+1
ANIMPROC4 DEC IZN+2
         BNE ANIMPROC2
         INC ANIMFAZA
         LDA ANIMFAZA
         AND #3
         STA ANIMFAZA
ANIMPROC1 RTS 
;
VBLTIMERDOWN LDA VBLTIMER
         BEQ VBLTIMERDOWN1
         DEC VBLTIMER
VBLTIMERDOWN1 RTS 
;
SETCOLA  LDY #4
SETCOLA1 LDA COLORSBUFA,Y
         STA $D016,Y
         DEY 
         BPL SETCOLA1
         LDA CHARGENVECT
         STA $D409
         RTS 
;
SETCOLB  LDY #4
         LDA # >CHARGEN
         STA $D409
SETCOLB1 LDA COLORSBUFB,Y
         STA $D016,Y
         DEY 
         BPL SETCOLB1
         RTS 
;
VBLOBS   JSR VBLTIMERDOWN
         JSR RTIMEROBS
         JSR USERVBLGO
         JMP MUSICPLAY
;
USERVBLGO JMP (USERVBLVECT)
;
DLIOBS   LDA $D40B
         CMP #78
         BCS DLIOBS1
         JMP SETCOLA
DLIOBS1  JMP SETCOLB
;
NMIOBS   PHA 
         TYA 
         PHA 
         TXA 
         PHA 
         LDA $D40F
         STA $D40F
         ASL
         BCC NMIOBS1
         JSR DLIOBS
         JMP NMIOBS2
NMIOBS1  ASL
         BCC NMIOBS2
         JSR VBLOBS
NMIOBS2  PLA 
         TAX 
         PLA 
         TAY 
         PLA 
         RTI 
;
RTIMEROBS INC RTIMER
         LDA RTIMER
         CMP #50
         BNE RTIMEROBS1
         LDA #0
         STA RTIMER
         INC RTIMER+1
         LDA RTIMER+1
         CMP #60
         BNE RTIMEROBS1
         LDA #0
         STA RTIMER+1
         INC RTIMER+2
         LDA RTIMER+2
         CMP #60
         BNE RTIMEROBS1
         LDA #0
         STA RTIMER+2
         INC RTIMER+3
         LDA RTIMER+3
         CMP #24
         BNE RTIMEROBS1
         LDA #0
         STA RTIMER+3
RTIMEROBS1 LDY # <TIMELINE+2
         LDX # >TIMELINE+2
PRRTIMER LDA VZN
         PHA 
         LDA VZN+1
         PHA 
         STY VZN
         STX VZN+1
         LDY #0
         LDA RTIMER+3
         JSR RTIMERPROC
         JSR RTIMERPROCB
         LDA RTIMER+2
         JSR RTIMERPROC
         JSR RTIMERPROCB
         LDA RTIMER+1
         JSR RTIMERPROC
         PLA 
         STA VZN+1
         PLA 
         STA VZN
         RTS 
;
RTIMERPROC LDX #16
RTIMERPROC1 CMP #10
         BCC RTIMERPROC2
         SBC #10
         INX 
         BNE RTIMERPROC1
RTIMERPROC2 ORA #16
         PHA 
         TXA 
         STA (VZN),Y
         INY 
         PLA 
         STA (VZN),Y
         INY 
         RTS 
;
RTIMERPROCB LDA #$1A
         STA (VZN),Y
         INY 
         RTS 
;
CLRSTAT  LDY #79
         LDA #0
CLRSTAT1 STA TIMELINE,Y
         DEY 
         BPL CLRSTAT1
         LDY #[ENDSTAT-RTIMER-1]
CLRSTAT2 STA RTIMER,Y
         DEY 
         BPL CLRSTAT2
         LDA #20
         STA BUYSOLD
         STA BUYSOLD+2
         LDA #1
         STA NMCY
         STA NMCY+1
         RTS 
;
USERVBLPROC .WORD ANIMPROC
         .WORD NULLPROC
         .WORD NULLPROC
         .WORD NULLPROC
         .WORD NULLPROC
         .WORD NULLPROC
         .WORD NULLPROC
         .WORD NULLPROC
;
NULLPROC RTS 
;
SETSCR   PHA 
         JSR SCREENOFF
         PLA 
SETSCRPROC ASL
         TAY 
         LDA USERVBLPROC,Y
         STA USERVBLVECT
         LDA USERVBLPROC+1,Y
         STA USERVBLVECT+1
         TYA 
         ASL
         ASL
         CLC 
         ADC # >MAPAPIC
         STA CHARGENVECT
         CLC 
         ADC #4
         STA DLPEZN+1
         ADC #3
         STA VZN+1
         LDX #251
         STX VZN
         LDY #4
SETSCR1  LDA (VZN),Y
         STA COLORSBUFA,Y
         LDA COLORSTABB,Y
         STA COLORSBUFB,Y
         DEY 
         BPL SETSCR1
         RTS 
;
PREPGRADL LDA # <DL
         LDY # >DL
         STA $D402
         STY $D403
         LDA # <NMIOBS
         LDY # >NMIOBS
         STA $FFFA
         STY $FFFB
         LDY #62
         LDX #192
PREPGRADL1 LDA $D40B
         BNE PREPGRADL1
         STY $D400
         STX $D40E
         JMP SETCOLB
;
PREPGRA  LDA # >PMBASE
         LDY #3
         LDX #1
         STA 54279
         STY 53277
         STX 53275
         LDA #0
         STA ANIMFAZA
         STA VBLTIMER
         LDA #5
         STA ANIMPAUZA
         LDA #2
         JSR SETSCRPROC
         JSR SETCOLA
         JMP PREPGRADL
;
REFRSCR  LDA #1
         JSR WAIT
         LDA #12
         STA $D012
         LDA #24
         STA VZN
         LDX #0
REFRSCR1 CPX ARMPOS
         BEQ REFRSCR11
         CPX ARMPOS+1
         BEQ REFRSCR11
         CPX ARMPOS+2
         BEQ REFRSCR11
         CPX ARMPOS+3
         BEQ REFRSCR11
         TXA 
         ASL
         TAY 
         LDA SHIELDTAB,Y
         CLC 
         ADC <MAPAPIC+1024
         STA VZN+1
         LDA SHIELDTAB+1,Y
         ADC >MAPAPIC+1024
         STA VZN+2
         LDY #0
         LDA #128
         STA (VZN+1),Y
REFRSCR11 INX 
         DEC VZN
         BNE REFRSCR1
         LDX #0
REFRSCR2 LDA ARMPOS,X
         BMI REFRSCR7
         ASL
         TAY 
         CLC 
         LDA SHIELDTAB,Y
         ADC <MAPAPIC+1024
         STA VZN
         LDA SHIELDTAB+1,Y
         ADC >MAPAPIC+1024
         STA VZN+1
         LDY #0
         LDA #208
         STA (VZN),Y
REFRSCR7 INX 
         CPX #4
         BNE REFRSCR2
         LDX #0
REFRSCR3 TXA 
         ASL
         TAY 
         CLC 
         LDA FLAGTAB,Y
         ADC <MAPAPIC+1024
         STA VZN
         LDA FLAGTAB+1,Y
         ADC >MAPAPIC+1024
         STA VZN+1
         LDY #209
         LDA KSTAB,X
         BMI REFRSCR4
         CLC 
         ADC #210
         TAY 
REFRSCR4 TYA 
         LDY #0
         STA (VZN),Y
         INX 
         CPX #24
         BNE REFRSCR3
         SEC 
         JSR PRINTNULL
         LDA # <DATADAT
         LDY # >DATADAT
         LDX GRACZ
         CPX HUMANPL
         BEQ REFRSCR5
         CPX HUMANPL+1
         BNE REFRSCR8
REFRSCR5 LDA # <ZLOTODATADAT
         LDY # >ZLOTODATADAT
         LDX #0
REFRSCR8 PHP 
         CLC 
         JSR PRINT
         LDA #0
         CLC 
         PHP 
         LDA ROK
         LDY ROK+1
         LDX #23
         PLP 
         JSR CONVDEC
         LDA MIESIAC
         ASL
         ASL
         ASL
         ASL
         TAY 
         LDX #0
REFRSCR6 LDA MIESDAT,Y
         STA INFOLINE+29,X
         INY 
         INX 
         CPX #11
         BNE REFRSCR6
         LDA GRACZ
         PLP 
         BNE REFRSCR9
         LDY #0
         JSR PRINTPLNAME
         LDA GRACZ
         ASL
         TAX 
         LDA #0
         CLC 
         PHP 
         LDA KASAZN+1,X
         TAY 
         LDA KASAZN,X
         LDX #13
         PLP 
         JSR CONVDEC
         JMP REFRSCR10
REFRSCR9 LDY #12
         JSR PRINTPLNAME
REFRSCR10 RTS 
;
PLOTMAN  LDX GRACZ
         LDA KSZN,X
         BEQ PLOTMAN2
         LDA #1
         JSR WAIT
         CLC 
         LDA GRACZ
         ADC # >MANBUF
         STA ZN+1
         LDY #0
         STY ZN
PLOTMAN1 LDA (ZN),Y
         STA MAPAPIC+98*8,Y
         INY 
         CPY #240
         BNE PLOTMAN1
PLOTMAN2 RTS 
;
DATADAT  .SB "   RUCH MA:        ROK:     ,           "
ZLOTODATADAT .SB "     : Z^OTO:      ROK:     ,           "
;
MIESDAT  .SB "STYCZE_         "
         .SB "LUTY            "
         .SB "MARZEC          "
         .SB "KWIECIE_        "
         .SB "MAJ             "
         .SB "CZERWIEC        "
         .SB "LIPIEC          "
         .SB "SIERPIE_        "
         .SB "WRZESIE_        "
         .SB "PADZIERNIK     "
         .SB "LISTOPAD        "
         .SB "GRUDZIE_        "
;
TIMEUPPROC LDA HUMANPL,X
         TAY 
         CPY #255
         BEQ TIMEUPPROC1
         LDA KSZN,Y
         BEQ TIMEUPPROC1
         INC NMCY,X
TIMEUPPROC1 RTS 
;
TIMEUP   LDX #0
         JSR TIMEUPPROC
         INX 
         JSR TIMEUPPROC
         INC MIESIAC
         LDA MIESIAC
         CMP #12
         BNE TIMEUP1
         LDA #0
         STA MIESIAC
         INC ROK
         BNE TIMEUP1
         INC ROK+1
TIMEUP1  RTS 
;
CHKGRTRUP LDX GRACZ
         LDA KSZN,X
         BNE CHKGRTRUP1
         LDA #255
         STA ARMPOS,X
         TXA 
         ASL
         TAX 
         LDA #0
         STA DOCHZN,X
         STA DOCHZN+1,X
CHKGRTRUP1 RTS 
;
SCREENOFF LDA #1
         JSR WAIT
         LDX #9
         LDY #0
SCREENOFF2 LDA COLORSBUFA,X
         AND #15
         BEQ SCREENOFF1
         DEC COLORSBUFA,X
         INY 
SCREENOFF1 DEX 
         BPL SCREENOFF2
         TYA 
         BNE SCREENOFF
         LDX #9
         LDA #0
SCREENOFF3 STA COLORSBUFA,X
         DEX 
         BPL SCREENOFF3
         LDY # <NULLPROC
         LDX # >NULLPROC
SETVBLPROC LDA #1
         JSR WAIT
         STY USERVBLVECT
         STX USERVBLVECT+1
         RTS 
;
CHKBUNT  LDY #0
         LDX GRACZ
         CPX HUMANPL
         BEQ CHKBUNT3
         CPX HUMANPL+1
         BNE CHKBUNT1
         INY 
CHKBUNT3 LDA NMCY,Y
         CMP #96     ; 6 LAT
         BEQ CHKBUNT2
         CMP #60     ; 5 LAT
         BCC CHKBUNT1
         LDA $D20A
         AND #3
         BNE CHKBUNT1
CHKBUNT2 LDA ARMPOS,X
         TAY 
         TXA 
         JSR CRBUF
         JSR WOJKUPA
         LDX GRACZ
         LDA #0
         STA KSZN,X
         LDY #23
CHKBUNT4 LDA KSTAB,Y
         CMP GRACZ
         BNE CHKBUNT5
         LDA #255
         STA KSTAB,Y
CHKBUNT5 DEY 
         BPL CHKBUNT4
CHKBUNT1 RTS 
;
CHKPLENDPROC LDA HUMANPL,Y
         TAX 
         CPX #255
         BEQ CHKPLENDPROC1
         LDA KSZN,X
         BNE CHKPLENDPROC1
         TYA 
         PHA 
         JSR KONIECTRUP
         JSR PREPGRADL
         JSR REFRSCR
         LDA #50
         JSR WAIT
         PLA 
         TAY 
         LDA #255
         STA HUMANPL,Y
CHKPLENDPROC1 RTS 
;
CHKPLEND LDY #0
         JSR CHKPLENDPROC
         INY 
         JSR CHKPLENDPROC
         LDA HUMANPL
         AND HUMANPL+1
         CMP #255
         RTS 
;
CHKPLWINPROC LDA HUMANPL,Y
         TAX 
         CPX #255
         BEQ CHKPLWINPROC1
         LDA KSZN,X
         CMP #24
         BNE CHKPLWINPROC1
         SEC 
         BCS CHKPLWINPROC2
CHKPLWINPROC1 CLC 
CHKPLWINPROC2 RTS 
;
CHKPLWIN LDY #0
         JSR CHKPLWINPROC
         BCS CHKPLWIN1
         INY 
         JSR CHKPLWINPROC
CHKPLWIN1 RTS 
;
GRA      JSR INITGRA
         LDA #0
         STA QUITZN
         STA GRACZ
         JSR REFRSCR
GRA1     LDA #0
         STA GRACZ
         JSR SOJDOWN
GRA2     JSR CHKBUNT
         JSR CHKGRTRUP
         BEQ GRA3
         JSR REFRSCR
         JSR PLOTMAN
         JSR RUCHGR
         JSR REFRSCR
         LDA #50
         JSR WAIT
GRA3     JSR CHKPLEND
         BEQ GRA4
         JSR CHKPLWIN
         BCS GRA5
         LDA QUITZN
         BNE GRA6
         INC GRACZ
         LDA GRACZ
         CMP #4
         BNE GRA2
         JSR TIMEUP
         JMP GRA1
GRA4     JMP SCREENOFF
GRA5     LDA #50
         JSR WAIT
         JSR SCREENOFF
         JMP KONIECWIN
GRA6     LDA #50
         JSR WAIT
         JSR SCREENOFF
         JMP KONIECBREAK
;
MUSICON  PHA 
         LDA #$70
         LDX # <MUZYKADAT
         LDY # >MUZYKADAT
         JSR MUZYKAPR+3
         PLA 
         TAX 
         LDA #$00
         JMP MUZYKAPR+3
;
MUSICOFF LDA #$40
         JMP MUZYKAPR+3
;
MUSICPLAY LDA MUSICZN
         BMI MUSICPLAY5
         LDA $D01F
         AND #$07
         CMP #$06
         BNE MUSICPLAY1
         LDA #$00
         STA MUSICZN
         BEQ MUSICPLAY2
MUSICPLAY1 CMP #$05
         BNE MUSICPLAY2
         LDA #$01
         STA MUSICZN
MUSICPLAY2 LDA MUSICZN
         BNE MUSICPLAY3
         JMP MUZYKAPR+6
MUSICPLAY3 LDA #0
         LDY #8
MUSICPLAY4 STA $D200,Y
         DEY 
         BPL MUSICPLAY4
MUSICPLAY5 RTS 
;
SELMANTXT1 .SB "       GRACZ 1 - WYBIERZ POSTA\:        "
SELMANTXT2 .SB "           WPISZ SWOJE IMI]:            "
SELMANTXT3 .SB "      TA POSTA\ JEST JU WYBRANA!       "
;
SELMAN   LDY #31
SELMAN1  LDA NAMPLDAT,Y
         STA NAMPLTAB,Y
         DEY 
         BPL SELMAN1
         STY HUMANPL+1
         STY IMMZN
         LDA #12
         STA $D012
         LDA #0
         JSR SELMANPROC
         STA HUMANPL
         JSR GETNAME
         LDA NOPCJA
         BEQ SELMAN2
SELMAN3  LDA #1
         JSR SELMANPROC
         CMP HUMANPL
         BNE SELMAN4
         LDA # <SELMANTXT3
         LDY # >SELMANTXT3
         CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDA NOPCJA
         LSR
         TAY 
         JSR WAITFIRE
         JMP SELMAN3
SELMAN4  STA HUMANPL+1
         JSR GETNAME
SELMAN2  LDA #0
         STA $D000
         RTS 
;
SELMANPROC STA ZN
         LDA # <SELMANTXT1
         LDY # >SELMANTXT1
         CLC 
         JSR PRINT
         CLC 
         LDA ZN
         ADC #17
         STA INFOLINE+13
         SEC 
         JSR PRINTNULL
         LDA #0
         LDY #3
         STA XCEL
         STA XCELMIN
         STY XCELMAX
         TAY 
SELMANPROC1 STA PMBASE+$0400,Y
         INY 
         BNE SELMANPROC1
         LDX #0
SELMANPROC2 LDA DKURDAT,X
         STA PMBASE+$0400+80,Y
         INY 
         INY 
         INX 
         CPX #8
         BNE SELMANPROC2
SELMANPROC3 LDY #0
         LDA NOPCJA
         CMP #2
         BNE SELMANPROC5
         LDY ZN
SELMANPROC5 JSR GETJOY
         STA POM
         JSR CHKPOZ
         LDY XCEL
         LDA XKURSOJOPTTAB,Y
         STA $D000
         TYA 
         LDY #57
         JSR PRINTPLNAME
         LDA #4
         JSR WAIT
         LDY #0
         LDA NOPCJA
         CMP #2
         BNE SELMANPROC4
         LDY ZN
SELMANPROC4 JSR GETFIRE
         BNE SELMANPROC3
         JSR WAITFIREB
         LDA XCEL
         RTS 
;
GETKEY   LDA #$00
         LDY #$40
         STA $D20E
         STY $D20E
GETKEY1  LDA $D20E
         AND #$40
         BNE GETKEY1
         LDA $D209
         LDY #36
GETKEY2  CMP KEYTAB1,Y
         BEQ GETKEY3
         DEY 
         BPL GETKEY2
         BMI GETKEY
GETKEY3  LDA KEYTAB2,Y
         RTS 
;
KEYTAB1  .BYTE $3F,$15,$12,$3A,$2A,$38,$3D,$39,$0D,$01,$05,$00,$25,$23,$08,$0A,$2F,$28,$3E,$2D
         .BYTE $0B,$10,$2E,$16,$2B,$17
         .BYTE $BF,$92,$AA,$80,$A3,$88,$BE,$97,$96,$34,$0C
;
KEYTAB2  .SB "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_ þÿ"
;
GETNAME  PHA 
GETNAME4 LDA # <SELMANTXT2
         LDY # >SELMANTXT2
         CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDA #0
         STA VZN
         LDA #$80
         STA MENULINE+17
GETNAME1 JSR GETKEY
         CMP #254
         BEQ GETNAME4
         CMP #255
         BEQ GETNAME2
         LDY VZN
         STA MENULINE+17,Y
         LDA #$80
         STA MENULINE+18,Y
         LDA VZN
         CMP #$04
         BEQ GETNAME1
         INC VZN
         BNE GETNAME1
GETNAME2 PLA 
         ASL
         ASL
         ASL
         TAY 
         LDX #0
GETNAME3 LDA MENULINE+17,X
         AND #127
         STA NAMPLTAB,Y
         INX 
         INY 
         CPX #5
         BNE GETNAME3
         JMP CHKIMM
;
PASSWORD .SB "SECOH"
;
CHKIMM   LDA IMMZN
         BEQ CHKIMM3
         LDY #4
         LDX #0
CHKIMM1  LDA MENULINE+17,Y
         AND #127
         CMP PASSWORD,Y
         BEQ CHKIMM2
         INX 
CHKIMM2  DEY 
         BPL CHKIMM1
         TXA 
         BNE CHKIMM3
         STA IMMZN
CHKIMM3  RTS 
;
INITGRA  JSR PREPGRA
         JSR CLRSTAT
         JSR SELMAN
         LDA # <KSTAB
         LDX # >KSTAB
         LDY #0
         STA ZN
         STX ZN+1
         TYA 
INITGRA1 STA (ZN),Y
         INC ZN
         BNE INITGRA2
         INC ZN+1
INITGRA2 LDX ZN
         CPX # <BUFFER
         BNE INITGRA1
         LDX ZN+1
         CPX # >BUFFER
         BNE INITGRA2
         LDY #6
INITGRA3 LDA #20
         STA WOJZN,Y
         STA KASAZN,Y
         LDA #0
         STA WOJZN+1,Y
         STA KASAZN+1,Y
         TYA 
         LSR
         CMP HUMANPL
         BEQ INITGRA9
         CMP HUMANPL+1
         BNE INITGRA7
INITGRA9 LDA IMMZN
         BNE INITGRA7
         LDA #255
         STA KASAZN,Y
         STA KASAZN+1,Y
         STA WOJZN,Y
         STA WOJZN+1,Y
         STA BUYSOLD
         STA BUYSOLD+1
         STA BUYSOLD+2
         STA BUYSOLD+3
INITGRA7 DEY 
         DEY 
         BPL INITGRA3
         LDX #23
         LDA #255
INITGRA4 STA KSTAB,X
         DEX 
         BPL INITGRA4
         LDX #3
INITGRA5 CPX HUMANPL
         BEQ INITGRA8
         CPX HUMANPL+1
         BEQ INITGRA8
         LDA NOPCJA
         BEQ INITGRA8
         JSR FIND3KS
         JMP INITGRA6
INITGRA8 JSR FIND1KS
INITGRA6 DEX 
         BPL INITGRA5
         LDA #0
         LDY #237
         LDX #56
         STA MIESIAC
         STY ROK
         STX ROK+1
         LDA #0
         JMP SETSCR
;
FINDKSPROC LDA $D20A
         AND #31
         CMP #24
         BCS FINDKSPROC
         TAY 
         LDA KSTAB,Y
         BPL FINDKSPROC
         TYA 
         RTS 
;
FIND1KS  JSR FINDKSPROC
         STA ARMPOS,X
         TXA 
         STA KSTAB,Y
         LDA #1
         STA KSZN,X
         RTS 
;
FIND3KS  STX VZN
FIND3KS1 LDX VZN
         JSR FINDKSPROC
         STA VZN+1
         ASL
         ASL
         ASL
         TAY 
         LDA NEARTAB,Y
         BMI FIND3KS1
         TAX 
         LDA KSTAB,X
         BPL FIND3KS1
         STX VZN+2
         INY 
         LDA NEARTAB,Y
         BMI FIND3KS1
         TAX 
         LDA KSTAB,X
         BPL FIND3KS1
         STX VZN+3
         LDA VZN
         STA KSTAB,X
         LDX VZN+2
         STA KSTAB,X
         LDX VZN+1
         STA KSTAB,X
         TAX 
         LDA #3
         STA KSZN,X
         LDA VZN+1
         STA ARMPOS,X
         RTS 
;

