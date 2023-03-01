;
; MODUL: GRINT
;

MENUDAT	 .BYTE $58, $59, $5A, $5B, $5C, $5D, $5E, $5F
		 .BYTE $60, $61, $62, $63, $64, $65, $66, $67, $68, $69, $6A, $6B, $6C, $6D, $6E, $6F
		 .BYTE $70, $71, $72, $73, $74, $75, $76, $77, $78, $79, $7A, $7B, $7C, $7D, $7E, $7F

BUYTXT   .SB "      KT", $40, "RE KSI", $3D, "STWO CHCESZ KUPI", $3C, "?      "
BUYTXT2  .SB "     ILE DAJESZ ZA           :          "
BUYTXT3  .SB "                 NALE", $42, "Y DO CIEBIE!      "
SOJTXT3
BUYTXT4  .SB "          ODRZUCI", $3E, " TWOJ", $3B, " PROPOZYCJ", $3D, "     "
BUYTXT5  .SB "         TEGO NIE DA SI", $3D, " KUPI", $3C, "!         "
SELLTXT  .SB "    KT", $40, "RE KSI", $3D, "STWO CHCESZ SPRZEDA", $3C, "?     "
SELLTXT2 .SB "     ILE ", $42, $3B, "DASZ ZA           :          "
SELLTXT3 .SB "   WSZYSCY ODRZUCILI TWOJ", $3B, " PROPOZYCJ", $3D, "   "
SELLTXT4 .SB "          KUPI", $3E, " OD CIEBIE               "
SELLTXT5 .SB "       TEGO NIE DA SI", $3D, " SPRZEDA", $3C, "!        "
SOJTXT   .SB "      Z KIM CHCESZ ZAWRZE", $3C, " SOJUSZ?      "
SOJTXT2  .SB "     : KSI",$3D, "STW:     DOCH", $40, "D:             "
SOJTXT4  .SB "             ZAWAR", $3E, " Z TOB", $3B, " SOJUSZ       "
SOJTXT5  .SB "CHCESZ SOBIE SAMEMU ZAPROPONOWA", $3C, " SOJUSZ?"
SOJTXT6  .SB "         JU", $42, " JEST TWOIM SOJUSZNIKIEM    "
WOJTXT   .SB "   ILE CHCESZ ZACI", $3B, "GN", $3B, $3C, " WOJSKA:         "
ARMTXT   .SB "     TWIERDZA:         ARMIA:           "
ALIENARMTXT .SB "        ARMIA NA OBCYM TERENIE!         "
GOTXT    .SB "  DO KT", $40, "REGO KSI", $3D, "STWA CHCESZ WKROCZY", $3C, "?  "
GOTXT2   .SB "    TO NIE JEST S", $3B, "SIEDNIE KSI", $3D, "STWO!     "
GOTXT3   .SB " CZY CHCESZ PRZEMASZEROWA", $3C, "?  ZGODA NIE  "
GOTXT4   .SB "              BRAK ARMII!               "
PROPBUYTXT .SB "      DAJE ZA                 ZGODA NIE "
PROPSELLTXT .SB "      CHCE ZA                 ZGODA NIE "
PROPSOJTXT .SB "      PROPONUJE CI SOJUSZ     ZGODA NIE "
PROPOPTNAMETXT .SB "                      :                 "
PLUNDERTXT .SB "   KT", $40, "RE KSI", $3D, "STWO CHCESZ SPL", $3B, "DROWA", $3C, "?    "
PLUNDERTXT2 .SB "      TEGO SI", $3D, " NIE DA SPL", $3B, "DROWA", $3C, "!       "
PLUNDERTXT3 .SB "           ZDOBYTE Z", $3E, "OTO:               "
NOANTYTXT .SB "  PRZECIE", $42, " NIE MASZ JU", $42, " PRZECIWNIK", $40, "W!   "
;
MENUOBS  LDY #0
         STY POM+1
         LDA GRACZ
         CMP HUMANPL
         BEQ MENUOBS4
         INC POM+1
         LDA NOPCJA
         CMP #2
         BNE MENUOBS4
         INY 
MENUOBS4 STY POM+2
         LDY GRACZ
         LDA KSZN,Y
         BEQ MENUOBS3
         CMP #24
         BEQ MENUOBS3
         LDA #1
         JSR WAIT
         JSR REFRSCR
         LDA #0
         LDY #9
         STA XCELMIN
         STA XCEL
         STY XCELMAX
MENUOBS1 LDY POM+2
         JSR GETJOY
         STA POM
         JSR CHKPOZ
         LDA # <MENUDAT
         LDY # >MENUDAT
         SEC 
         JSR PRINT
         LDA XCEL
         ASL
         ASL
         TAY 
         LDX #4
MENUOBS2 LDA MENULINE,Y
         ORA #128
         STA MENULINE,Y
         INY 
         DEX 
         BNE MENUOBS2
         LDA XCEL
         JSR PROPTTXT
         LDA #4
         JSR WAIT
         LDY POM+2
         JSR GETFIRE
         BNE MENUOBS1
         JSR WAITFIRE1
         JSR CLROPTTXT
         LDA XCEL
         ASL
         TAX 
         LDA MENUOPTTAB,X
         STA ZN
         LDA MENUOPTTAB+1,X
         STA ZN+1
         JMP (ZN)
MENUOBS3 RTS 
;
MENUOPTTAB .WORD BUYOPT
         .WORD SELLOPT
         .WORD SOJOPT
         .WORD WOJOPT
         .WORD ARMOPT
         .WORD GOOPT
         .WORD PLUNDEROPT
         .WORD TURNIEJOPT
         .WORD NEXTOPT
         .WORD QUITOPT
;
BUYOPT   JSR WHEREARM
         BNE BUYOPT13
         JSR CHKANTY
         BNE BUYOPT12
BUYOPT13 JMP MENUOBS
BUYOPT12 LDA # <BUYTXT
         LDY # >BUYTXT
         CLC 
         JSR PRINT
         JSR GETKSNO
         PHP 
         PHA 
         SEC 
         JSR PRINTNULL
         PLA 
         PLP 
         BNE BUYOPT1
BUYOPT6  LDA # <BUYTXT5
         LDY # >BUYTXT5
         CLC 
         JSR PRINT
         JMP BUYOPT5
BUYOPT1  TAY 
         LDA KSTAB,Y
         BMI BUYOPT6
         CMP GRACZ
         BEQ BUYOPT6
         TYA 
         PHA 
         LDA # <BUYTXT2
         LDY # >BUYTXT2
         CLC 
         JSR PRINT
         PLA 
         PHA 
         LDY #19
         SEC 
         JSR PRINTKSNAME
         LDA #0
         STA XCEL
         STA XCELMIN
         STA YCELMIN
         LDA #2
         STA YCELMAX
         LDX #255
         LDA GRACZ
         ASL
         TAY 
         LDA KASAZN+1,Y
         BNE BUYOPT3
         LDA KASAZN,Y
         TAX 
BUYOPT3  STX XCELMAX
BUYOPT2  LDY POM+2
         JSR GETJOY
         STA POM
         LDA #1
         STA YCEL
         JSR CHKPION
         LDY YCEL
         DEY 
         BEQ BUYOPT8
         BPL BUYOPT9
         SEC 
         LDA XCEL
         SBC #100
         BCS BUYOPT10
         LDA #0
         BEQ BUYOPT10
BUYOPT9  CLC 
         LDA XCEL
         ADC #100
         BCC BUYOPT11
         LDA #255
BUYOPT11 CMP XCELMAX
         BEQ BUYOPT10
         LDA XCELMAX
BUYOPT10 STA XCEL
BUYOPT8  JSR CHKPOZ
         LDA #255
         CLC 
         PHP 
         LDA XCEL
         LDY #0
         LDX #31
         PLP 
         JSR CONVDEC
         LDA #3
         JSR WAIT
         LDY POM+2
         JSR GETFIRE
         BNE BUYOPT2
         JSR WAITFIREB
         PLA 
         PHA 
         TAY 
         LDA KSTAB,Y
         TAX 
         LDA XCEL
         JSR PROPBUY
         BMI BUYOPT4
         LDX GRACZ
         LDA ARMPOS,X
         TAY 
         TXA 
         JSR CRBUF
         JSR REFRSCR
         LDA # <BUYTXT3
         LDY # >BUYTXT3
         CLC 
         JSR PRINT
         PLA 
         LDY #6
         SEC 
         JSR PRINTKSNAME
         JMP BUYOPT7
BUYOPT4  LDA # <BUYTXT4
         LDY # >BUYTXT4
         CLC 
         JSR PRINT
         PLA 
         TAY 
         LDA KSTAB,Y
         LDY #4
         JSR PRINTPLNAME
BUYOPT7  LDY POM+2
         JSR WAITFIRE
         LDA GRACZ
         JMP POSARM
BUYOPT5  LDY POM+2
         JSR WAITFIRE
         JMP MENUOBS
;
SELLOPT  JSR WHEREARM
         BNE SELLOPT13
         JSR CHKANTY
         BNE SELLOPT12
SELLOPT13 JMP MENUOBS
SELLOPT12 LDA # <SELLTXT
         LDY # >SELLTXT
         CLC 
         JSR PRINT
         JSR GETKSNO
         PHP 
         PHA 
         SEC 
         JSR PRINTNULL
         PLA 
         PLP 
         BNE SELLOPT1
SELLOPT2 LDA # <SELLTXT5
         LDY # >SELLTXT5
         CLC 
         JSR PRINT
         JMP SELLOPT3
SELLOPT1 TAY 
         LDA KSTAB,Y
         CMP GRACZ
         BNE SELLOPT2
         TYA 
         PHA 
         LDA # <SELLTXT2
         LDY # >SELLTXT2
         CLC 
         JSR PRINT
         PLA 
         PHA 
         LDY #19
         SEC 
         JSR PRINTKSNAME
         LDA #0
         STA XCEL
         STA XCELMIN
         STA YCELMIN
         LDA #2
         STA YCELMAX
         LDA #255
         STA XCELMAX
SELLOPT4 LDY POM+2
         JSR GETJOY
         STA POM
         LDA #1
         STA YCEL
         JSR CHKPION
         LDY YCEL
         DEY 
         BEQ SELLOPT9
         BPL SELLOPT10
         SEC 
         LDA XCEL
         SBC #100
         BCS SELLOPT11
         LDA #0
         BEQ SELLOPT11
SELLOPT10 CLC 
         LDA XCEL
         ADC #100
         BCC SELLOPT11
         LDA #255
SELLOPT11 STA XCEL
SELLOPT9 JSR CHKPOZ
         LDA #255
         CLC 
         PHP 
         LDA XCEL
         LDY #0
         LDX #31
         PLP 
         JSR CONVDEC
         LDA #3
         JSR WAIT
         LDY POM+2
         JSR GETFIRE
         BNE SELLOPT4
         JSR WAITFIREB
         PLA 
         STA VZN
         LDA #3
         STA POM+4
         LDY XCEL
         LDX VZN
         STX POM+3
SELLOPT5 LDA POM+4
         CMP GRACZ
         BEQ SELLOPT6
         JSR PROPSELL
         BPL SELLOPT7
SELLOPT6 DEC POM+4
         BPL SELLOPT5
         LDA # <SELLTXT3
         LDY # >SELLTXT3
         CLC 
         JSR PRINT
         JMP SELLOPT8
SELLOPT7 LDA POM+3
         PHA 
         LDA POM+4
         PHA 
         LDA GRACZ
         JSR POSARM
         JSR REFRSCR
         LDA # <SELLTXT4
         LDY # >SELLTXT4
         CLC 
         JSR PRINT
         PLA 
         LDY #4
         JSR PRINTPLNAME
         PLA 
         LDY #26
         SEC 
         JSR PRINTKSNAME
SELLOPT8 LDY POM+2
         JSR WAITFIRE
         LDA GRACZ
         JMP POSARM
SELLOPT3 LDY POM+2
         JSR WAITFIRE
         JMP MENUOBS
;
WOJOPT   JSR WHEREARM
         BEQ WOJOPT10
         JMP MENUOBS
WOJOPT10 LDA # <WOJTXT
         LDY # >WOJTXT
         SEC 
         JSR PRINT
         LDA #0
         LDY #2
         STA ZN
         STA ZN+1
         STA XCELMIN
         STA YCELMIN
         STY XCELMAX
         STY YCELMAX
WOJOPT1  LDA #1
         STA XCEL
         STA YCEL
         LDY POM+2
         JSR GETJOY
         STA POM
         JSR CHKPOZ
         JSR CHKPION
         LDY YCEL
         BNE WOJOPT2
         LDA #100
         JSR WOJOPTPROCA
         JMP WOJOPT3
WOJOPT2  DEY 
         BEQ WOJOPT3
         LDA #100
         JSR WOJOPTPROCB
WOJOPT3  LDY XCEL
         BNE WOJOPT4
         LDA #1
         JSR WOJOPTPROCA
         JMP WOJOPT5
WOJOPT4  DEY 
         BEQ WOJOPT5
         LDA #1
         JSR WOJOPTPROCB
WOJOPT5  LDA GRACZ
         ASL
         TAY 
         SEC 
         LDA KASAZN,Y
         SBC ZN
         LDA KASAZN+1,Y
         SBC ZN+1
         BCS WOJOPT6
         LDA KASAZN,Y
         STA ZN
         LDA KASAZN+1,Y
         STA ZN+1
WOJOPT6  LDA #0
         SEC 
         PHP 
         LDA ZN
         LDY ZN+1
         LDX #32
         PLP 
         JSR CONVDEC
         LDA #3
         JSR WAIT
         LDY POM+2
         JSR GETFIRE
         BNE WOJOPT1
         JSR WAITFIREB
         LDA ZN
         ORA ZN+1
         BEQ WOJOPT8
         LDA POM+1
         ASL
         TAY 
         CLC 
         LDA BUYSOLD,Y
         ADC ZN
         STA VZN
         LDA BUYSOLD+1,Y
         ADC ZN+1
         STA VZN+1
         BCC WOJOPT9
         LDA #255
         STA VZN
         STA VZN+1
WOJOPT9  LDA VZN
         STA BUYSOLD,Y
         LDA VZN+1
         STA BUYSOLD+1,Y
         LDA GRACZ
         ASL
         TAY 
         CLC 
         LDA WOJZN,Y
         ADC ZN
         STA VZN
         LDA WOJZN+1,Y
         ADC ZN+1
         STA VZN+1
         BCC WOJOPT7
         LDA #255
         STA VZN
         STA VZN+1
WOJOPT7  LDA VZN
         STA WOJZN,Y
         LDA VZN+1
         STA WOJZN+1,Y
         SEC 
         LDA KASAZN,Y
         SBC ZN
         STA KASAZN,Y
         LDA KASAZN+1,Y
         SBC ZN+1
         STA KASAZN+1,Y
         LDA GRACZ
         JMP POSARM
WOJOPT8  JMP MENUOBS
;
WOJOPTPROCA STA VZN
         SEC 
         LDA ZN
         SBC VZN
         STA VZN
         LDA ZN+1
         SBC #0
         STA VZN+1
         BCS WOJOPTPROCA1
         LDA #0
         STA VZN
         STA VZN+1
WOJOPTPROCA1 LDA VZN
         STA ZN
         LDA VZN+1
         STA ZN+1
         RTS 
;
WOJOPTPROCB CLC 
         ADC ZN
         STA ZN
         BCC WOJOPTPROCB1
         INC ZN+1
         BNE WOJOPTPROCB1
         LDA #255
         STA ZN
         STA ZN+1
WOJOPTPROCB1 RTS 
;
ARMOPT   JSR WHEREARM
         BEQ ARMOPT6
         JMP MENUOBS
ARMOPT6  LDA # <ARMTXT
         LDY # >ARMTXT
         SEC 
         JSR PRINT
         LDA #0
         LDY #2
         STA XCELMIN
         STA YCELMIN
         STY XCELMAX
         STY YCELMAX
         LDA GRACZ
         ASL
         TAY 
         LDA WOJZN,Y
         STA ZN
         LDA WOJZN+1,Y
         STA ZN+1
         LDY GRACZ
         LDA ARMPOS,Y
         ASL
         TAY 
         LDA WOJKSTAB,Y
         STA ZN+2
         LDA WOJKSTAB+1,Y
         STA ZN+3
ARMOPT1  LDA #1
         STA XCEL
         STA YCEL
         LDY POM+2
         JSR GETJOY
         STA POM
         JSR CHKPOZ
         JSR CHKPION
         LDY YCEL
         BNE ARMOPT2
         LDA #100
         JSR ARMOPTPROCA
         JMP ARMOPT3
ARMOPT2  DEY 
         BEQ ARMOPT3
         LDA #100
         JSR ARMOPTPROCB
ARMOPT3  LDY XCEL
         BNE ARMOPT4
         LDA #1
         JSR ARMOPTPROCA
         JMP ARMOPT5
ARMOPT4  DEY 
         BEQ ARMOPT5
         LDA #1
         JSR ARMOPTPROCB
ARMOPT5  LDA #0
         SEC 
         PHP 
         LDA ZN+2
         LDY ZN+3
         LDX #15
         PLP 
         JSR CONVDEC
         LDA #0
         SEC 
         PHP 
         LDA ZN
         LDY ZN+1
         LDX #30
         PLP 
         JSR CONVDEC
         LDA #4
         JSR WAIT
         LDY POM+2
         JSR GETFIRE
         BNE ARMOPT1
         JSR WAITFIREB
         LDA GRACZ
         ASL
         TAY 
         LDA ZN
         STA WOJZN,Y
         LDA ZN+1
         STA WOJZN+1,Y
         LDY GRACZ
         LDA ARMPOS,Y
         ASL
         TAY 
         LDA ZN+2
         STA WOJKSTAB,Y
         LDA ZN+3
         STA WOJKSTAB+1,Y
         JMP MENUOBS
;
ARMOPTPROCA STA VZN+4
         LDA ZN+2
         AND ZN+3
         CMP #$FF
         BEQ ARMOPTPROCA1
         CLC 
         LDA ZN+2
         ADC VZN+4
         STA VZN+2
         LDA ZN+3
         ADC #0
         STA VZN+3
         BCC ARMOPTPROCA2
         CLC 
         LDA VZN+4
         SBC VZN+2
         JMP ARMOPTPROCA
ARMOPTPROCA2 SEC 
         LDA ZN
         SBC VZN+4
         STA VZN
         LDA ZN+1
         SBC #0
         STA VZN+1
         BCS ARMOPTPROCA3
         LDA VZN
         EOR #255
         CLC 
         ADC #1
         STA VZN+5
         SEC 
         LDA VZN+4
         SBC VZN+5
         JMP ARMOPTPROCA
ARMOPTPROCA3 LDA VZN
         LDY VZN+1
         STA ZN
         STY ZN+1
         LDA VZN+2
         LDY VZN+3
         STA ZN+2
         STY ZN+3
ARMOPTPROCA1 RTS 
;
XCHGZN   LDY ZN
         LDX ZN+2
         STY ZN+2
         STX ZN
         LDY ZN+1
         LDX ZN+3
         STY ZN+3
         STX ZN+1
         RTS 
;
ARMOPTPROCB JSR XCHGZN
         JSR ARMOPTPROCA
         JMP XCHGZN
;
DKURDAT  .BYTE $00,$18,$18,$18,$7E,$3C,$18,$00
;
XKURSOJOPTTAB .BYTE 82,82+28,82+28*2,82+28*3
;
WRALSOJTXT .SB "WR", $40, "G  "
		   .SB "ALIANT",
		   .SB "T"+$80, "Y"+$80, "    "
		   .SB "MARTWY"
;
SOJOPT   JSR WHEREARM
         BEQ SOJOPT13
         JMP MENUOBS
SOJOPT13 LDA #2
         JSR SETSCR
         LDA # <SOJTXT
         LDY # >SOJTXT
         CLC 
         JSR PRINT
         LDA # <SOJTXT2
         LDY # >SOJTXT2
         SEC 
         JSR PRINT
         LDA #0
         LDY #3
         STA XCEL
         STA XCELMIN
         STY XCELMAX
         TAY 
SOJOPT2  STA PMBASE+$0400,Y
         INY 
         BNE SOJOPT2
         LDX #0
SOJOPT3  LDA DKURDAT,X
         STA PMBASE+$0400+80,Y
         INY 
         INY 
         INX 
         CPX #8
         BNE SOJOPT3
SOJOPT1  LDY POM+2
         JSR GETJOY
         STA POM
         JSR CHKPOZ
         LDY XCEL
         LDA XKURSOJOPTTAB,Y
         STA $D000
         TYA 
         LDY #40
         JSR PRINTPLNAME
         LDA #255
         SEC 
         PHP 
         LDY XCEL
         LDA KSZN,Y
         LDY #0
         LDX #15
         PLP 
         JSR CONVDEC
         LDA #0
         SEC 
         PHP 
         LDA XCEL
         ASL
         TAX 
         LDA DOCHZN+1,X
         TAY 
         LDA DOCHZN,X
         LDX #27
         PLP 
         JSR CONVDEC
         LDX #0
         LDY XCEL
         LDA KSZN,Y
         LDY #18
         CMP #0
         BEQ SOJOPT4
         LDY #12
         LDA GRACZ
         CMP XCEL
         BEQ SOJOPT4
         ASL
         ASL
         ORA XCEL
         TAY 
         LDA SOJTAB,Y
         TAY 
         BEQ SOJOPT4
         LDY #6
SOJOPT4  LDA WRALSOJTXT,Y
         STA MENULINE+34,X
         INY 
         INX 
         CPX #6
         BNE SOJOPT4
         LDA #4
         JSR WAIT
         LDY XCEL
         LDA KSZN,Y
         BEQ SOJOPT12
         LDY POM+2
         JSR GETFIRE
         BEQ SOJOPT9
SOJOPT12 JMP SOJOPT1
SOJOPT9  JSR WAITFIREB
         SEC 
         JSR PRINTNULL
         LDA XCEL
         CMP GRACZ
         BEQ SOJOPT5
         ASL
         ASL
         ORA GRACZ
         TAY 
         LDA SOJTAB,Y
         BEQ SOJOPT10
         LDA # <SOJTXT6
         LDY # >SOJTXT6
         CLC 
         JSR PRINT
         LDY #3
         BNE SOJOPT7
SOJOPT10 LDY XCEL
         JSR PROPSOJ
         BCC SOJOPT6
         LDA # <SOJTXT3
         LDY # >SOJTXT3
         CLC 
         JSR PRINT
         LDY #4
         BNE SOJOPT7
SOJOPT6  LDA # <SOJTXT4
         LDY # >SOJTXT4
         CLC 
         JSR PRINT
         LDY #7
SOJOPT7  LDA XCEL
         JSR PRINTPLNAME
         JMP SOJOPT8
SOJOPT5  LDA # <SOJTXT5
         LDY # >SOJTXT5
         CLC 
         JSR PRINT
SOJOPT8  LDY POM+2
         JSR WAITFIRE
         LDA #0
         STA $D000
         JSR SETSCR
         LDA XCEL
         CMP GRACZ
         BNE SOJOPT11
         JMP MENUOBS
SOJOPT11 LDA GRACZ
         JMP POSARM
;
GOOPT    LDA GRACZ
         ASL
         TAY 
         LDA WOJZN,Y
         ORA WOJZN+1,Y
         BNE GOOPT10
         LDA # <GOTXT4
         LDY # >GOTXT4
         JMP GOOPT9
GOOPT10  LDA # <GOTXT
         LDY # >GOTXT
         CLC 
         JSR PRINT
         JSR GETKSNO
         BEQ GOOPT1
         PHA 
         LDY GRACZ
         LDA ARMPOS,Y
         ASL
         ASL
         ASL
         TAY 
         LDX #8
         PLA 
GOOPT2   CMP NEARTAB,Y
         BEQ GOOPT3
         INY 
         DEX 
         BNE GOOPT2
GOOPT1   LDA # <GOTXT2
         LDY # >GOTXT2
GOOPT9   CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDY POM+2
         JSR WAITFIRE
         JMP GOOPT4
GOOPT3   STA ZN
         TAY 
         LDA KSTAB,Y
         BPL GOOPT5
         LDA GRACZ
         STA KSTAB,Y
         TAX 
         INC KSZN,X
         TYA 
         STA ARMPOS,X
         RTS 
GOOPT5   CMP GRACZ
         BNE GOOPT6
         TYA 
         LDY GRACZ
         STA ARMPOS,Y
         JMP GOOPT4
GOOPT6   ASL
         ASL
         ORA GRACZ
         TAX 
         LDA SOJTAB,X
         BNE GOOPT7
GOOPT8   LDX GRACZ
         LDA ARMPOS,X
         TAX 
         LDY ZN
         JMP BITWA
GOOPT7   LDA # <GOTXT3
         LDY # >GOTXT3
         CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDX #29
         JSR GETODP
         BNE GOOPT8
         LDY GRACZ
         LDA ZN
         STA ARMPOS,Y
GOOPT4   JMP MENUOBS
;
TURNIEJOPT JSR WHEREARM
         BNE TURNIEJOPT3
         JSR CHKANTY
         BNE TURNIEJOPT2
TURNIEJOPT3 JMP MENUOBS
TURNIEJOPT2 LDA MUSICZN
         ORA #$80
         STA MUSICZN
         JSR MUSICOFF
         LDY #8
         LDA #0
TURNIEJOPT1 STA $D200,Y
         DEY 
         BPL TURNIEJOPT1
         JSR TURNIEJ
         LDA #$01
         JSR MUSICON
         LDA MUSICZN
         AND #$7F
         STA MUSICZN
         LDA GRACZ
         JMP POSARM
;
QUITOPT  LDA #$FF
         STA QUITZN
;
NEXTOPT  LDA GRACZ
;
POSARM   CMP #255
         BEQ POSARM1
         STA ZN
         LDY ZN
         LDA ARMPOS,Y
         TAY 
         LDA KSTAB,Y
         CMP ZN
         BEQ POSARM1
         JSR NEWPOS
         BNE POSARM2
         LDA #255
         BNE POSARM3
POSARM2  TXA 
POSARM3  LDY ZN
         STA ARMPOS,Y
POSARM1  RTS 
;
NEWPOS   LDY ZN
         LDA KSZN,Y
         BEQ NEWPOS5
         STA ZN+1
NEWPOS1  LDA $D20A
         AND #31
         CMP ZN+1
         BCS NEWPOS1
         TAY 
         LDX #0
NEWPOS2  LDA KSTAB,X
         CMP ZN
         BNE NEWPOS3
         DEY 
         BMI NEWPOS4
NEWPOS3  INX 
         CPX #24
         BNE NEWPOS2
NEWPOS4  CPX #24
NEWPOS5  RTS 
;
GETKSNO  LDA #96
         LDY #128
         STA XCEL
         STY YCEL
         LDA #48
         LDY #203
         STA XCELMIN
         STY XCELMAX
         LDA #32
         LDY #211
         STA YCELMIN
         STY YCELMAX
         SEC 
         JSR PRINTNULL
         JSR CLRKUR
GETKSNO1 LDA #1
         JSR WAIT
         LDY POM+2
         JSR GETJOY
         STA POM
         JSR CHKPOZ
         JSR CHKPOZ
         JSR CHKPION
         JSR CHKPION
         JSR CLRKUR
         JSR PRKUR
         JSR PRKSNM
         STA VZN
         LDY POM+2
         JSR GETFIRE
         BNE GETKSNO1
         LDA #0
         STA $D000
         JSR WAITFIREB
         LDA VZN
         CMP #255
         RTS 
;
PRKSNM   SEC 
         JSR PRINTNULL
         SEC 
         LDA YCEL
         SBC #32
         LSR
         LSR
         LSR
         TAX 
         SEC 
         LDA XCEL
         SBC #48
         LSR
         LSR
         CLC 
         ADC # <TERTAB
         PHA 
         LDA # >TERTAB
         ADC #0
         TAY 
         PLA 
PRKSNM1  DEX 
         BMI PRKSNM2
         CLC 
         ADC #40
         BCC PRKSNM1
         INY 
         BNE PRKSNM1
PRKSNM2  STA VZN
         STY VZN+1
         LDY #0
         LDA (VZN),Y
         BMI PRKSNM3
         PHA 
         LDY #52
         CLC 
         JSR PRINTKSNAME
         PLA 
PRKSNM3  RTS 
;
KURDAT   .BYTE 0,224,192,192,224,176,144,0
;
CLRKUR   LDY #0
         TYA 
CLRKUR1  STA PMBASE+$0400,Y
         INY 
         BNE CLRKUR1
         RTS 
;
PRKUR    LDA XCEL
         STA $D000
         LDY YCEL
         DEY 
         LDX #0
PRKUR2   LDA KURDAT,X
         STA PMBASE+$0400,Y
         INY 
         INX 
         CPX #8
         BNE PRKUR2
         RTS 
;
PRINTKSNAME STA VZN
         STY VZN+2
         LDA #0
         STA VZN+1
         LDY #10
         BCS PRINTKSNAME5
         LDA #255
         LDY #16
PRINTKSNAME5 STA VZN+3
         STY VZN+4
         LDX #4
PRINTKSNAME1 ASL VZN
         ROL VZN+1
         DEX 
         BNE PRINTKSNAME1
         CLC 
         LDA VZN
         ADC # <NAMKSTAB
         STA VZN
         LDA VZN+1
         ADC # >NAMKSTAB
         STA VZN+1
         LDY #0
PRINTKSNAME2 LDA (VZN),Y
         CMP VZN+3
         BEQ PRINTKSNAME3
         INY 
         BNE PRINTKSNAME2
PRINTKSNAME3 STY VZN+5
         SEC 
         LDA VZN+4
         SBC VZN+5
         LSR
         CLC 
         ADC VZN+2
         TAX 
         LDY #0
PRINTKSNAME4 LDA (VZN),Y
         CMP VZN+3
         BEQ PRINTKSNAME6
         STA INFOLINE,X
         INY 
         INX 
         BNE PRINTKSNAME4
PRINTKSNAME6 RTS 
;
GETODP   LDA XCEL
         PHA 
         LDA #0
         LDY #1
         STA XCEL
         STA XCELMIN
         STY XCELMAX
         STX VZN
GETODP4  LDY #10
         LDX VZN
GETODP1  LDA INFOLINE,X
         AND #127
         STA INFOLINE,X
         INX 
         DEY 
         BNE GETODP1
         LDA VZN
         LDY XCEL
         BEQ GETODP2
         CLC 
         ADC #5
GETODP2  TAX 
         LDY #5
GETODP3  LDA INFOLINE,X
         ORA #128
         STA INFOLINE,X
         INX 
         DEY 
         BNE GETODP3
         LDY POM+2
         JSR GETJOY
         STA POM
         JSR CHKPOZ
         LDA #4
         JSR WAIT
         LDY POM+2
         JSR GETFIRE
         BNE GETODP4
         JSR WAITFIREB
         LDA #0
         STA $D000
         LDY XCEL
         PLA 
         STA XCEL
         TYA 
         RTS 
;
PRINTPROPPLNAME PHA 
         LDA # <PROPOPTNAMETXT
         LDY # >PROPOPTNAMETXT
         CLC 
         JSR PRINT
         PLA 
         LDY #17
         JMP PRINTPLNAME
;
PROPBUYG LDY #0
         LDA ZN+2
         CMP HUMANPL
         BEQ PROPBUYG2
         LDA NOPCJA
         CMP #2
         BNE PROPBUYG2
         INY 
PROPBUYG2 STY POM+2
         LDA ZN+1
         JSR PLOTKURKS
         LDA ZN+2
         JSR PRINTPROPPLNAME
         LDA # <PROPBUYTXT
         LDY # >PROPBUYTXT
         SEC 
         JSR PRINT
         LDY #40
         LDA GRACZ
         JSR PRINTPLNAME
         LDA ZN+1
         LDY #54
         SEC 
         JSR PRINTKSNAME
         LDA #255
         SEC 
         PHP 
         LDA ZN
         LDY #0
         LDX #25
         PLP 
         JSR CONVDEC
         LDX #70
         JSR GETODP
         BNE PROPBUYG1
         JSR PROPBUYPROC
         PHP 
         LDA ZN+2
         JSR POSARM
         JSR REFRSCR
         PLP 
         RTS 
PROPBUYG1 LDA #255
         RTS 
;
PROPSELLG LDY #0
         LDA ZN
         CMP HUMANPL
         BEQ PROPSELLG2
         LDA NOPCJA
         CMP #2
         BNE PROPSELLG2
         INY 
PROPSELLG2 STY POM+2
         LDA ZN
         ASL
         TAY 
         LDA KASAZN+1,Y
         BNE PROPSELLG3
         LDA KASAZN,Y
         CMP ZN+1
         BCC PROPSELLG1
PROPSELLG3 LDA ZN+2
         JSR PLOTKURKS
         LDA ZN
         JSR PRINTPROPPLNAME
         LDA # <PROPSELLTXT
         LDY # >PROPSELLTXT
         SEC 
         JSR PRINT
         LDY #40
         LDA GRACZ
         JSR PRINTPLNAME
         LDA ZN+2
         LDY #54
         SEC 
         JSR PRINTKSNAME
         LDA #255
         SEC 
         PHP 
         LDA ZN+1
         LDY #0
         LDX #25
         PLP 
         JSR CONVDEC
         LDX #70
         JSR GETODP
         BNE PROPSELLG1
         JSR PROPSELLPROC
         PHP 
         TYA 
         PHA 
         TXA 
         PHA 
         JSR REFRSCR
         PLA 
         TAX 
         PLA 
         TAY 
         PLP 
         RTS 
PROPSELLG1 LDY ZN+1
         LDX ZN+2
         LDA #255
         RTS 
;
PROPSOJG TYA 
         PHA 
         LDY #0
         CMP HUMANPL
         BEQ PROPSOJG2
         LDA NOPCJA
         CMP #2
         BNE PROPSOJG2
         INY 
PROPSOJG2 STY POM+2
         PLA 
         PHA 
         JSR PRINTPROPPLNAME
         LDA # <PROPSOJTXT
         LDY # >PROPSOJTXT
         SEC 
         JSR PRINT
         LDA GRACZ
         LDY #40
         JSR PRINTPLNAME
         LDX #70
         JSR GETODP
         PHA 
         SEC 
         JSR PRINTNULL
         PLA 
         STA VZN
         PLA 
         TAY 
         LDA VZN
         BNE PROPSOJG1
         LDX GRACZ
         JSR PROPSOJPROC
         PHP 
         JSR REFRSCR
         PLP 
         RTS 
PROPSOJG1 SEC 
         RTS 
;
PLOTKURKS STA VZN
         ASL
         TAY 
         LDA FLAGTAB,Y
         STA VZN+1
         LDA FLAGTAB+1,Y
         STA VZN+2
         LDX #0
PLOTKURKS1 LDA VZN+2
         BNE PLOTKURKS2
         LDA VZN+1
         CMP #40
         BCC PLOTKURKS3
PLOTKURKS2 SEC 
         LDA VZN+1
         SBC #40
         STA VZN+1
         LDA VZN+2
         SBC #0
         STA VZN+2
         INX 
         BNE PLOTKURKS1
PLOTKURKS3 TXA 
         ASL
         ASL
         ASL
         CLC 
         ADC #22
         TAX 
         LDY #0
         TYA 
PLOTKURKS4 STA PMBASE+$0400,Y
         INY 
         BNE PLOTKURKS4
PLOTKURKS5 LDA DKURDAT,Y
         STA PMBASE+$0400,X
         INY 
         INX 
         CPY #8
         BNE PLOTKURKS5
         LDA #1
         JSR WAIT
         LDA VZN+1
         ASL
         ASL
         CLC 
         ADC #46
         STA $D000
         RTS 
;
SPISEK   LDA GRACZ
         CMP HUMANPL
         BEQ SPISEK10
         CMP HUMANPL+1
         BNE SPISEK8
SPISEK10 LDY #0
         CMP HUMANPL
         BEQ SPISEK11
         LDA NOPCJA
         CMP #2
         BNE SPISEK11
         INY 
SPISEK11 STY POM+2
         LDA $D20A
         TAY 
         AND #240
         BEQ SPISEK7
SPISEK8  JMP SPISEK1
SPISEK7  TYA 
         AND #15
         PHA 
         LDA #5
         JSR SETSCR
         PLA 
         CMP #5
         BCS SPISEK2
SPISEK6  LDA # <SPISEK1TXT
         LDY # >SPISEK1TXT
         SEC 
         JSR PRINT
         LDA GRACZ
         ASL
         TAX 
         LSR KASAZN+1,X
         ROR KASAZN,X
         JMP SPISEK3
SPISEK2  CMP #10
         BCS SPISEK4
         LDA # <SPISEK2TXT
         LDY # >SPISEK2TXT
         SEC 
         JSR PRINT
         LDA GRACZ
         ASL
         TAX 
         LSR DOCHZN+1,X
         ROR DOCHZN,X
         JMP SPISEK3
SPISEK4  LDX GRACZ
         LDA KSZN,X
         CMP #2
         BCC SPISEK6
SPISEK5  LDA $D20A
         AND #31
         CMP #24
         BCS SPISEK5
         TAY 
         LDA KSTAB,Y
         CMP GRACZ
         BNE SPISEK5
         TYA 
         CMP ARMPOS,X
         BEQ SPISEK5
SPISEKKS PHA 
         LDA # <SPISEK3TXT
         LDY # >SPISEK3TXT
         SEC 
         JSR PRINT
         LDX GRACZ
         DEC KSZN,X
         PLA 
         PHA 
         LDY #64
         SEC 
         JSR PRINTKSNAME
         PLA 
         TAY 
         ASL
         TAX 
         LDA #255
         STA KSTAB,Y
         LDA GRACZ
         ASL
         TAY 
         CLC 
         LDA WOJZN,Y
         ADC WOJKSTAB,X
         STA VZN
         LDA WOJZN+1,Y
         ADC WOJKSTAB+1,X
         STA VZN+1
         BCC SPISEK9
         LDA #255
         STA VZN
         STA VZN+1
SPISEK9  LDA VZN
         STA WOJZN,Y
         LDA VZN+1
         STA WOJZN+1,Y
         LDA #0
         STA WOJKSTAB,X
         STA WOJKSTAB+1,X
         LDA GRACZ
         JSR POSARM
         LDX GRACZ
         LDA ARMPOS,X
         TAY 
         TXA 
         JSR CRBUF
SPISEK3  LDA GRACZ
         JSR PRINTPROPPLNAME
         LDY POM+2
         JSR WAITFIRE
         LDA #0
         JSR SETSCR
         JSR REFRSCR
SPISEK1  RTS 
;
SPISEK1TXT .SB "   UTRACI", $3E, "E", $41, " PO", $3E, "OW", $3D, " POSIADANEGO Z", $3E, "OTA   "
SPISEK2TXT .SB " UTRACI", $3E, "E", $41, " PO", $3E, "OW", $3D, " MIESI", $3D, "CZNEGO DOCHODU  "
SPISEK3TXT .SB "     UTRACI", $3E, "E", $41, " KSI", $3D, "STWO                 "
;
PLUNDEROPT JSR WHEREARM
         BEQ PLUNDEROPT9
         JMP MENUOBS
PLUNDEROPT9 LDX GRACZ
         LDA ARMPOS,X
         TAY 
         TXA 
         JSR CRBUF
         LDA # <PLUNDERTXT
         LDY # >PLUNDERTXT
         CLC 
         JSR PRINT
         JSR GETKSNO
         PHP 
         PHA 
         SEC 
         JSR PRINTNULL
         PLA 
         PLP 
         BNE PLUNDEROPT1
PLUNDEROPT2 LDA # <PLUNDERTXT2
         LDY # >PLUNDERTXT2
PLUNDERTXT10 CLC 
         JSR PRINT
         JMP PLUNDEROPT3
PLUNDEROPT1 LDY #23
PLUNDEROPT7 CMP BUFFER,Y
         BEQ PLUNDEROPT8
         DEY 
         BPL PLUNDEROPT7
         BMI PLUNDEROPT2
PLUNDEROPT8 PHA 
         LDA # <PLUNDERTXT3
         LDY # >PLUNDERTXT3
         CLC 
         JSR PRINT
         PLA 
         PHA 
         TAX 
         LDA DOCHTAB,X
         ASL
         ASL
         STA ZN
         INC ZN
PLUNDEROPT4 LDA $D20A
         CMP ZN
         BCS PLUNDEROPT4
         STA ZN
         PHA 
         LDA GRACZ
         ASL
         TAY 
         CLC 
         LDA KASAZN,Y
         ADC ZN
         STA ZN
         LDA KASAZN+1,Y
         ADC #0
         STA ZN+1
         BCC PLUNDEROPT5
         LDA #255
         STA ZN
         STA ZN+1
PLUNDEROPT5 LDA ZN
         STA KASAZN,Y
         LDA ZN+1
         STA KASAZN+1,Y
         PLA 
         LDY #255
         CLC 
         PHP 
         LDY #0
         LDX #26
         PLP 
         JSR CONVDEC
         LDY POM+2
         JSR WAITFIRE
         PLA 
         LDY $D20A
         BPL PLUNDEROPT6
         PHA 
         LDA #5
         JSR SETSCR
         PLA 
         JSR SPISEKKS
PLUNDEROPT6 LDA GRACZ
         JMP POSARM
PLUNDEROPT3 LDY POM+2
         JSR WAITFIRE
         JMP MENUOBS
;
OPTTXT
         .SB "   KUPNO KSI", $3D, "STWA   "
         .SB " SPRZEDA", $42, " KSI", $3D, "STWA  "
         .SB "  ZAWARCIE SOJUSZU  "
         .SB "   ZACI", $3B, "G WOJSKA    "
         .SB "  TWORZENIE ARMII   "
         .SB "     RUCH ARMII     "
         .SB "PL", $3B, "DROWANIE KSI", $3D, "STWA"
         .SB "  TURNIEJ ", $3E, "UCZNICZY "
         .SB "  NAST", $3D, "PNY MIESI", $3B, "C  "
         .SB "     KONIEC GRY     "
         .SB "                    "
;
CLROPTTXT LDA #10
;
PROPTTXT ASL
         ASL
         STA VZN
         ASL
         ASL
         CLC 
         ADC VZN
         TAY 
         LDX #0
PROPTTXT1 LDA OPTTXT,Y
         STA TIMELINE+18,X
         INY 
         INX 
         CPX #20
         BNE PROPTTXT1
         RTS 
;
CHKANTY  LDY #3
         LDX #0
CHKANTY1 CPY GRACZ
         BEQ CHKANTY2
         LDA KSZN,Y
         BEQ CHKANTY2
         INX 
CHKANTY2 DEY 
         BPL CHKANTY1
         TXA 
         BNE CHKANTY3
         LDA # <NOANTYTXT
         LDY # >NOANTYTXT
         CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDY POM+2
         JSR WAITFIRE
         LDA #0
CHKANTY3 RTS 
;
WHEREARM LDY GRACZ
         LDA ARMPOS,Y
         TAY 
         LDA KSTAB,Y
         CMP GRACZ
         BEQ WHEREARM1
         LDA # <ALIENARMTXT
         LDY # >ALIENARMTXT
         CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDY POM+2
         JSR WAITFIRE
         LDA #255
WHEREARM1 RTS 
;

