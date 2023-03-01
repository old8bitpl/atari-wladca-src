;
; MODUL: BITWA
;

BITWA    STY ZN      ; <- TEREN BITWY
         STX ZN+1    ; <- SKAD ATAK
         LDA KSTAB,Y
         STA ZN+2    ; <- OBRONCA
         JSR BITWAON
         JSR PREPBITWA
         JMP BITWAPROC
;
BITWATXT1 .SB "          :                 :           "
BITWATXT2 .SB "        "
		  .SB " "+$80, " "+$80, "A"+$80, "T"+$80, "A"+$80, "K"+$80, " "+$80, " "+$80
		  .SB " OBRONA "
		  .SB " ODWR", $40, "T "
		  .SB "        "
BITWATXT3 .SB "        "
		  .SB "  ATAK  "
		  .SB " "+$80, "O"+$80, "B"+$80, "R"+$80, "O"+$80, "N"+$80, "A"+$80, " "+$80
		  .SB "        "
		  .SB "        "
BITWATXT4 .SB "        "
		  .SB " "+$80, "W"+$80, "A"+$80, "L"+$80, "K"+$80, "A"+$80, " "+$80, " "+$80
		  .SB " ODWR", $40, "T "
		  .SB "        "
		  .SB "        "
         ;   
CHKBITWA LDY #0
         LDA GRACZ
         CMP HUMANPL
         BEQ CHKBITWA1
         CMP HUMANPL+1
         BNE CHKBITWA2
CHKBITWA1 INY 
CHKBITWA2 LDA ZN+2
         CMP HUMANPL
         BEQ CHKBITWA3
         CMP HUMANPL+1
         BNE CHKBITWA4
CHKBITWA3 INY 
         INY 
CHKBITWA4 TYA 
         RTS 
;
CHKBITWAB LDA HUMANPL,X
         CMP GRACZ
         BEQ CHKBITWAB1
         CMP ZN+2
         BNE CHKBITWAB2
CHKBITWAB1 INC NBITEW,X
         BNE CHKBITWAB2
         LDA #255
         STA NBITEW,X
CHKBITWAB2 RTS 
;
PREPBITWA LDA #0
         STA XCELMIN
         JSR CHKBITWA
         STY ZN+3
         BEQ PREPBITWA1
         LDA #1
         JSR SETSCR
         LDA # <BITWATXT1
         LDY # >BITWATXT1
         CLC 
         JSR PRINT
         LDA GRACZ
         LDY #5
         JSR PRINTPLNAME
         LDA ZN+2
         LDY #23
         JSR PRINTPLNAME
         LDY ZN+3
         DEY 
         BNE PREPBITWA2
         LDA # <BITWATXT2
         LDY # >BITWATXT2
         SEC 
         JSR PRINT
         LDA #0
         LDX #2
         BNE PREPBITWA3
PREPBITWA2 DEY 
         BNE PREPBITWA4
         LDA # <BITWATXT3
         LDY # >BITWATXT3
         SEC 
         JSR PRINT
         LDA #1
         TAX 
         BNE PREPBITWA3
PREPBITWA4 LDA # <BITWATXT4
         LDY # >BITWATXT4
         SEC 
         JSR PRINT
         LDA #0
         LDX #1
PREPBITWA3 STA XCEL
         STX XCELMAX
PREPBITWA1 LDX #0
         JSR CHKBITWAB
         INX 
         JSR CHKBITWAB
         LDA GRACZ
         ASL
         ASL
         ORA ZN+2
         TAY 
         LDA ZN+2
         ASL
         ASL
         ORA GRACZ
         TAX 
         LDA #0
         STA SOJTAB,Y
         STA SOJTAB,X
         LDY ZN+2
         LDA ZN
         CMP ARMPOS,Y
         BNE PREPBITWA5
         TYA 
         ASL
         TAY 
         LDA ZN
         ASL
         TAX 
         CLC 
         LDA WOJZN,Y
         ADC WOJKSTAB,X
         STA VZN
         LDA WOJZN+1,Y
         ADC WOJKSTAB+1,X
         STA VZN+1
         BCC PREPBITWA6
         LDA #255
         STA VZN
         STA VZN+1
PREPBITWA6 LDA VZN
         STA WOJKSTAB,X
         LDA VZN+1
         STA WOJKSTAB+1,X
         LDA #0
         STA WOJZN,Y
         STA WOJZN+1,Y
PREPBITWA5 LDA #150
         LDY #200
         STA ZN+4
         STY ZN+5
         RTS 
;
SELBITWA LDA #6
SELBITWA1 PHA 
         LDA GRACZ
         ASL
         TAX 
         LDA #0
         CLC 
         PHP 
         LDA WOJZN+1,X
         TAY 
         LDA WOJZN,X
         LDX #12
         PLP 
         JSR CONVDEC
         LDA ZN
         ASL
         TAX 
         LDA #0
         CLC 
         PHP 
         LDA WOJKSTAB+1,X
         TAY 
         LDA WOJKSTAB,X
         LDX #30
         PLP 
         JSR CONVDEC
         LDA ZN+3
         LSR
         BCC SELBITWA2
         LDA GRACZ
         BPL SELBITWA3
SELBITWA2 LDA ZN+2
SELBITWA3 LDY #0
         CMP HUMANPL
         BEQ SELBITWA4
         LDA NOPCJA
         CMP #2
         BNE SELBITWA4
         INY 
SELBITWA4 JSR GETJOY
         STA POM
         JSR CHKPOZ
         LDY #23
SELBITWA5 LDA MENULINE+8,Y
         AND #127
         STA MENULINE+8,Y
         DEY 
         BPL SELBITWA5
         LDA XCEL
         ASL
         ASL
         ASL
         TAY 
         LDX #8
SELBITWA6 LDA MENULINE+8,Y
         ORA #128
         STA MENULINE+8,Y
         INY 
         DEX 
         BNE SELBITWA6
         LDA #4
         JSR WAIT
         PLA 
         SEC 
         SBC #1
         BNE SELBITWA1
         LDY ZN+3
         CPY #3
         BEQ SELBITWA7
         LDX XCEL
         BNE SELBITWA8
         LDA #150
         LDY #200
         BNE SELBITWA11
SELBITWA8 DEX 
         BNE SELBITWA10
         LDA #50
         LDY #100
SELBITWA11 STA ZN+4
         STY ZN+5
         BNE SELBITWA9
SELBITWA10 DEX 
         BEQ SELBITWA9
SELBITWA7 LDY XCEL
         DEY 
SELBITWA9 RTS 
;
BITWAPROC LDA ZN+3
         BEQ BITWAPROC1
         JSR SELBITWA
         BEQ BITWAPROC7
BITWAPROC1 LDA GRACZ
         ASL
         TAY 
         LDA WOJZN,Y
         ORA WOJZN+1,Y
         BNE BITWAPROC2
BITWAPROC7 LDY GRACZ
         LDA ZN+1
         STA ARMPOS,Y
         TYA 
         JSR POSARM
         JSR BITWAOFF
         JMP BITWAPROC3
BITWAPROC2 LDA ZN
         ASL
         TAY 
         LDA WOJKSTAB,Y
         ORA WOJKSTAB+1,Y
         BNE BITWAPROC4
         JSR BITWAOFF
         LDY ZN
         LDA DOCHTAB,Y
         CMP #40
         BCC BITWAPROC5
         LDA ZN+3
         LSR
         BCC BITWAPROC6
         JSR MACHINA
         BNE BITWAPROC5
         BEQ BITWAPROC7
BITWAPROC6 LDA $D20A
         AND #3
         BEQ BITWAPROC7
BITWAPROC5 LDX #0
         LDA GRACZ
         CMP HUMANPL
         BEQ BITWAPROC8
         CMP HUMANPL+1
         BNE BITWAPROC9
         INX 
BITWAPROC8 INC NWINBITEW,X
         BNE BITWAPROC9
         LDA #255
         STA NWINBITEW,X
BITWAPROC9 LDX GRACZ
         INC KSZN,X
         LDA ZN
         STA ARMPOS,X
         TXA 
         LDY ZN
         STA KSTAB,Y
         LDX ZN+2
         DEC KSZN,X
         LDA ARMPOS,X
         CMP ZN
         BNE BITWAPROC10
         TXA 
         JSR POSARM
BITWAPROC10 JMP BITWAPROC3
BITWAPROC4 LDA GRACZ
         ASL
         TAX 
         LDY ZN+4
         LDA WOJZN+1,X
         BNE BITWAPROC11
         LDA WOJZN,X
         CMP ZN+4
         BCS BITWAPROC11
         TAY 
BITWAPROC11 INY 
         STY ZN+6
         LDA ZN
         ASL
         TAX 
         LDY ZN+5
         LDA WOJKSTAB+1,X
         BNE BITWAPROC12
         LDA WOJKSTAB,X
         CMP ZN+5
         BCS BITWAPROC12
         TAY 
BITWAPROC12 INY 
         STY ZN+7
BITWAPROC16 LDA $D20A
         CMP ZN+6
         BCS BITWAPROC16
         STA ZN+6
BITWAPROC17 LDA $D20A
         CMP ZN+7
         BCS BITWAPROC17
         STA ZN+7
         SEC 
         LDA WOJKSTAB,X
         SBC ZN+6
         STA WOJKSTAB,X
         LDA WOJKSTAB+1,X
         SBC #0
         STA WOJKSTAB+1,X
         BCS BITWAPROC13
         LDA #0
         STA WOJKSTAB,X
         STA WOJKSTAB+1,X
BITWAPROC13 LDA GRACZ
         ASL
         TAY 
         LDA WOJZN,Y
         SBC ZN+7
         STA WOJZN,Y
         LDA WOJZN+1,Y
         SBC #0
         STA WOJZN+1,Y
         BCS BITWAPROC14
         LDA #0
         STA WOJZN,Y
         STA WOJZN+1,Y
BITWAPROC14 JMP BITWAPROC
BITWAPROC3 JMP BITWAQUIT
;
BITWAON  LDA ZN
         JSR BITWAONOFFPROC
         LDA #218
         STA (VZN),Y
         LDX GRACZ
         LDA ARMPOS,X
         JSR BITWAONOFFPROC
         LDA #128
         STA (VZN),Y
         LDA #100
         JMP WAIT
;
BITWAOFF LDA ZN+3
         BEQ BITWAOFF1
         LDY #255
         CMP #3
         BEQ BITWAOFF2
         CMP #1
         BNE BITWAOFF3
         LDA GRACZ
         JSR BITWAOFFPROC
         JMP BITWAOFF2
BITWAOFF3 LDA ZN+2
         JSR BITWAOFFPROC
BITWAOFF2 JSR WAITFIRE
BITWAOFF1 RTS 
;
BITWAQUIT LDA ZN+3
         BEQ BITWAQUIT1
         LDA #0
         JSR SETSCR
         JSR REFRSCR
BITWAQUIT1 RTS 
;
BITWAOFFPROC LDY #0
         CMP HUMANPL
         BEQ BITWAOFFPROC1
         LDA NOPCJA
         CMP #2
         BNE BITWAOFFPROC1
         INY 
BITWAOFFPROC1 RTS 
;
BITWAONOFFPROC ASL
         TAX 
         CLC 
         LDA SHIELDTAB,X
         ADC <MAPAPIC+1024
         STA VZN
         LDA SHIELDTAB+1,X
         ADC >MAPAPIC+1024
         STA VZN+1
         LDY #0
         RTS 
;

