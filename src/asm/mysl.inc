;
; MODUL: MYSL
;

RUCHGR   JSR DOCHUP
RUCHGR14
         LDA GRACZ
         CMP HUMANPL
         BEQ RUCHGR11
         CMP HUMANPL+1
         BNE RUCHGR18
RUCHGR11 JMP MENUOBS
RUCHGR18 JSR WOJKUPA
         JSR WOJDIV
         LDA $D20A
         AND #7
         BNE RUCHGR21
         JMP RUCHGR10
RUCHGR21 JSR CHKFRKS
         BEQ RUCHGR1
         TXA 
         PHA 
         JSR WOJARM
         PLA 
         TAX 
         LDA GRACZ
         STA KSTAB,X
         TAY 
         TXA 
         STA ARMPOS,Y
         ASL
         TAX 
         LDA #0
         STA WOJKSTAB,X
         STA WOJKSTAB+1,X
         LDX GRACZ
         INC KSZN,X
         JMP RUCHGR20
RUCHGR1  JSR WOJKUPA
         LDA GRACZ
         ASL
         TAX 
         LDA WOJZN+1,X
         BNE RUCHGR2
         LDA WOJZN,X
         CMP #100
         BCS RUCHGR2
         LDX GRACZ
         LDA KSZN,X
         CMP #3
         BCC RUCHGR3
         JSR WOJDIV
         JSR CHKBDKS
         LDA #3
         CMP GRACZ
         BEQ RUCHGR5
         JSR PROPSELL
         BPL RUCHGR3
RUCHGR5  LDA #2
         CMP GRACZ
         BEQ RUCHGR6
         JSR PROPSELL
         BPL RUCHGR3
RUCHGR6  LDA #1
         CMP GRACZ
         BEQ RUCHGR4
         JSR PROPSELL
         BPL RUCHGR3
RUCHGR4  LDA #0
         CMP GRACZ
         BEQ RUCHGR3
         JSR PROPSELL
         BMI RUCHGR15
RUCHGR3  JMP RUCHGR20
RUCHGR2  JSR WOJDIV
RUCHGR15 LDA $D20A
         TAY 
         CMP #10
         BCS RUCHGR22
         JSR PRWYZWANIE
         JSR TURNIEJOPT
         JMP RUCHGR20
RUCHGR22 TYA 
         BPL RUCHGR7
         JSR WOJARM
         JSR CHKODC
         BEQ RUCHGR19
         LDA $D20A
         AND #3
         BNE RUCHGR8
RUCHGR19 JSR PREPAT
         BEQ RUCHGR9
RUCHGR8  JMP BITWA
RUCHGR9  RTS 
RUCHGR7  CMP #64
         BCC RUCHGR10
         LDA GRACZ
         ASL
         TAX 
         LDA KASAZN+1,X
         BEQ RUCHGR12
         JSR CHKBUY
         BNE RUCHGR13
         BEQ RUCHGR20
RUCHGR10 LDA GRACZ
         ASL
         TAX 
         LDA KASAZN+1,X
         BEQ RUCHGR12
RUCHGR13 LDA $D20A
         AND #1
         BEQ RUCHGR12
         JMP BUYWOJ
RUCHGR12 JMP BUYWOJMAX
RUCHGR20 RTS 
;
WYZWANIETXT .SB "       WYZWA^ CI] NA TURNIEJ ^UCZNICZY  "
;
PRWYZWANIE LDA # <WYZWANIETXT
         LDY # >WYZWANIETXT
         CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDY #1
         LDA GRACZ
         JSR PRINTPLNAME
         LDY #255
         JMP WAITFIRE
;
SOJDOWN  LDX #$00
SOJDOWN1 LDA SOJTAB,X
         BEQ SOJDOWN2
         DEC SOJTAB,X
SOJDOWN2 INX 
         CPX #$10
         BNE SOJDOWN1
         RTS 
;
DOCHUP   LDX GRACZ
         LDA ARMPOS,X
         TAY 
         TXA 
         JSR CRBUF
         LDY #0
         STY ZN
         STY ZN+1
DOCHUP3  LDA BUFFER,Y
         BMI DOCHUP1
         TAX 
         LDA DOCHTAB,X
         CLC 
         ADC ZN
         STA ZN
         BCC DOCHUP2
         INC ZN+1
DOCHUP2  INY 
         CPY #24
         BNE DOCHUP3
DOCHUP1  LDA GRACZ
         TAY 
         ASL
         PHA 
         TAX 
         CPY HUMANPL
         BEQ DOCHUP5
         CPY HUMANPL+1
         BEQ DOCHUP5
         ASL ZN
         ROL ZN+1
DOCHUP5  LDA ZN
         STA DOCHZN,X
         LDA ZN+1
         STA DOCHZN+1,X
         JSR SPISEK
         PLA 
         TAX 
         CLC 
         LDA KASAZN,X
         ADC DOCHZN,X
         STA ZN
         LDA KASAZN+1,X
         ADC DOCHZN+1,X
         STA ZN+1
         BCC DOCHUP4
         LDA #255
         STA ZN
         STA ZN+1
DOCHUP4  LDA ZN
         STA KASAZN,X
         LDA ZN+1
         STA KASAZN+1,X
         RTS 
;
CHKFRKS  LDY #1
         STY ZN
         DEY 
CHKFRKS4 LDA BUFFER,Y
         BMI CHKFRKS5
         TAX 
         TYA 
         PHA 
         TXA 
         ASL
         ASL
         ASL
         TAY 
         LDA #8
         STA ZN+2
CHKFRKS3 LDA NEARTAB,Y
         BMI CHKFRKS1
         TAX 
         LDA KSTAB,X
         BPL CHKFRKS2
         LDA DOCHTAB,X
         CMP ZN
         BCC CHKFRKS2
         STA ZN
         STX ZN+1
CHKFRKS2 INY 
         DEC ZN+2
         BNE CHKFRKS3
CHKFRKS1 PLA 
         TAY 
         INY 
         CPY #24
         BNE CHKFRKS4
CHKFRKS5 LDX ZN+1
         LDY ZN
         CPY #1
         RTS 
;
CRBUF    STA ZN
         STY ZN+1
         JSR CLRBUF
         LDA ZN+1
         JSR PUTBUF
         LDA #0
         STA ZN+1
CRBUF4   LDY ZN+1
         LDA BUFFER,Y
         BMI CRBUF1
         ASL
         ASL
         ASL
         TAY 
         LDA #8
         STA ZN+2
CRBUF3   LDA NEARTAB,Y
         BMI CRBUF2
         TAX 
         LDA KSTAB,X
         CMP ZN
         BNE CRBUF5
         TXA 
         JSR PUTBUF
CRBUF5   INY 
         DEC ZN+2
         BNE CRBUF3
CRBUF2   INC ZN+1
         LDA ZN+1
         CMP #24
         BNE CRBUF4
CRBUF1   RTS 
;
CLRBUF   LDX #23
         LDA #255
CLRBUF1  STA BUFFER,X
         DEX 
         BPL CLRBUF1
         RTS 
;
PUTBUF   LDX #23
PUTBUF1  CMP BUFFER,X
         BEQ PUTBUF2
         DEX 
         BPL PUTBUF1
         PHA 
         LDX #0
PUTBUF3  LDA BUFFER,X
         BMI PUTBUF4
         INX 
         BNE PUTBUF3
PUTBUF4  PLA 
         STA BUFFER,X
PUTBUF2  RTS 
;
WOJKUPA  LDY #0
WOJKUPA1 LDA BUFFER,Y
         BMI WOJKUPA2
         ASL
         TAX 
         TYA 
         PHA 
         LDA GRACZ
         ASL
         TAY 
         CLC 
         LDA WOJZN,Y
         ADC WOJKSTAB,X
         STA ZN
         LDA WOJZN+1,Y
         ADC WOJKSTAB+1,X
         STA ZN+1
         BCC WOJKUPA3
         LDA #255
         STA ZN
         STA ZN+1
WOJKUPA3 LDA ZN
         STA WOJZN,Y
         LDA ZN+1
         STA WOJZN+1,Y
         LDA #0
         STA WOJKSTAB,X
         STA WOJKSTAB+1,X
         PLA 
         TAY 
         INY 
         CPY #24
         BNE WOJKUPA1
WOJKUPA2 RTS 
;
CHKBDKS  LDA #0
         STA ZN
CHKBDKS3 LDA #0
         STA ZN+1
         INC ZN
         LDY #23
CHKBDKS2 LDA GRACZ
         CMP KSTAB,Y
         BNE CHKBDKS1
         TAX 
         TYA 
         CMP ARMPOS,X
         BEQ CHKBDKS1
         LDA DOCHTAB,Y
         CMP ZN
         BNE CHKBDKS1
         INC ZN+1
CHKBDKS1 DEY 
         BPL CHKBDKS2
         LDA ZN+1
         BEQ CHKBDKS3
         LDA #254
         STA ZN+1
         LDY #23
CHKBDKS14 LDA GRACZ
         CMP KSTAB,Y
         BNE CHKBDKS4
         TAX 
         TYA 
         CMP ARMPOS,X
         BEQ CHKBDKS4
         LDA DOCHTAB,Y
         CMP ZN
         BNE CHKBDKS4
         TYA 
         PHA 
         ASL
         ASL
         ASL
         TAY 
         LDA #8
         STA ZN+2
         LDA #0
         STA ZN+3
         STA ZN+4
CHKBDKS7 LDA NEARTAB,Y
         BMI CHKBDKS5
         INC ZN+3
         TAX 
         LDA KSTAB,X
         CMP GRACZ
         BNE CHKBDKS6
         INC ZN+4
CHKBDKS6 INY 
         DEC ZN+2
         BNE CHKBDKS7
         BEQ CHKBDKS5
CHKBDKS4 JMP CHKBDKS12
CHKBDKS5 LDX #1
         LDA ZN+3
         STA ZN+2
CHKBDKS8 LDA ZN+2
         CMP #210
         BCS CHKBDKS9
         ADC ZN+3
         STA ZN+2
         INX 
         BNE CHKBDKS8
CHKBDKS9 LDA ZN+4
         STA ZN+2
CHKBDKS10 DEX 
         BEQ CHKBDKS11
         CLC 
         LDA ZN+2
         ADC ZN+4
         STA ZN+2
         BCC CHKBDKS10
CHKBDKS11 PLA 
         TAY 
         LDA ZN+2
         CMP ZN+1
         BCS CHKBDKS12
         STA ZN+1
         STY ZN+5
CHKBDKS12 DEY 
         BMI CHKBDKS13
         JMP CHKBDKS14
CHKBDKS13 LDA $D20A
         CMP #100
         BCC CHKBDKS13
         LDX ZN+5
         TAY 
         RTS 
;
PROPSELL STA ZN
         STY ZN+1
         STX ZN+2
         LDA #255
         STA ZN+3
         LDX ZN
         LDA KSZN,X
         BEQ PROPSELL2
         CPX HUMANPL
         BEQ PROPSELL11
         CPX HUMANPL+1
         BNE PROPSELL1
PROPSELL11 JMP PROPSELLG
PROPSELL1 LDA ZN+2
         ASL
         ASL
         ASL
         TAY 
         LDA #8
         STA ZN+4
         LDA #0
         STA ZN+5
PROPSELL8 LDA NEARTAB,Y
         BMI PROPSELL9
         TAX 
         LDA KSTAB,X
         BMI PROPSELL10
         CMP ZN
         BNE PROPSELL10
         INC ZN+5
PROPSELL10 INY 
         DEC ZN+4
         BNE PROPSELL8
PROPSELL9 LDA ZN+5
         BEQ PROPSELL2
         LDA $D20A
         AND #1
         BEQ PROPSELL2
         LDA ZN
         ASL
         TAX 
         LDA KASAZN+1,X
         BNE PROPSELL3
         LDA KASAZN,X
         CMP ZN+1
         BCS PROPSELL3
PROPSELL2 JMP PROPSELL4
PROPSELL3 LDA $D20A
         CMP #100
         BCC PROPSELL3
         CMP ZN+1
         BCC PROPSELL2
PROPSELLPROC LDA ZN
         ASL
         TAX 
         SEC 
         LDA KASAZN,X
         SBC ZN+1
         STA KASAZN,X
         BCS PROPSELL5
         DEC KASAZN+1,X
PROPSELL5 LDA GRACZ
         ASL
         TAY 
         CLC 
         LDA KASAZN,Y
         ADC ZN+1
         STA ZN+4
         LDA KASAZN+1,Y
         ADC #0
         STA ZN+5
         BCC PROPSELL6
         LDA #255
         STA ZN+4
         STA ZN+5
PROPSELL6 LDA ZN+4
         STA KASAZN,Y
         LDA ZN+5
         STA KASAZN+1,Y
         LDX ZN+2
         LDA ZN
         STA KSTAB,X
         TXA 
         ASL
         TAX 
         CLC 
         LDA WOJZN,Y
         ADC WOJKSTAB,X
         STA ZN+4
         LDA WOJZN+1,Y
         ADC WOJKSTAB+1,X
         STA ZN+5
         BCC PROPSELL7
         LDA #255
         STA ZN+4
         STA ZN+5
PROPSELL7 LDA ZN+4
         STA WOJZN,Y
         LDA ZN+5
         STA WOJZN+1,Y
         LDA #0
         STA WOJKSTAB,X
         STA WOJKSTAB+1,X
         LDX GRACZ
         DEC KSZN,X
         LDX ZN
         INC KSZN,X
         LDA #0
         STA ZN+3
PROPSELL4 LDY ZN+1
         LDX ZN+2
         LDA ZN+3
         RTS 
;
WOJDIV   LDY #0
         STY ZN
WOJDIV1  LDA BUFFER,Y
         BMI WOJDIV2
         ASL
         ASL
         ASL
         TAX 
         TYA 
         PHA 
         LDA #0
         STA ZN+1
         LDA #8
         STA ZN+2
WOJDIV3  LDA NEARTAB,X
         BMI WOJDIV4
         TAY 
         LDA KSTAB,Y
         BMI WOJDIV5
         CMP GRACZ
         BEQ WOJDIV5
         INC ZN+1
WOJDIV5  INX 
         DEC ZN+2
         BNE WOJDIV3
WOJDIV4  PLA 
         TAY 
         LDA ZN+1
         BEQ WOJDIV6
         LDA BUFFER,Y
         ORA #32
         STA BUFFER,Y
         INC ZN
WOJDIV6  INY 
         CPY #24
         BNE WOJDIV1
WOJDIV2  LDA ZN
         BEQ WOJDIV9
         LDA GRACZ
         ASL
         TAX 
         LDY #0
         STY ZN+1
         STY ZN+2
WOJDIV7  SEC 
         LDA WOJZN,X
         SBC ZN
         STA ZN+3
         LDA WOJZN+1,X
         SBC #0
         STA ZN+4
         BCC WOJDIV8
         LDA ZN+3
         STA WOJZN,X
         LDA ZN+4
         STA WOJZN+1,X
         INC ZN+1
         BNE WOJDIV7
         INC ZN+2
         BNE WOJDIV7
WOJDIV8  LDA BUFFER,Y
         BMI WOJDIV9
         STA ZN+3
         AND #32
         BEQ WOJDIV10
         LDA ZN+3
         STY ZN+3
         AND #31
         STA BUFFER,Y
         ASL
         TAY 
         LDA ZN+1
         STA WOJKSTAB,Y
         LDA ZN+2
         STA WOJKSTAB+1,Y
         LDY ZN+3
WOJDIV10 INY 
         CPY #24
         BNE WOJDIV8
WOJDIV9  RTS 
;
WOJARM   LDY #0
WOJARM1  LDA BUFFER,Y
         BMI WOJARM2
         ASL
         TAX 
         LDA WOJKSTAB+1,X
         LSR
         STA WOJKSTAB+1,X
         STA ZN+1
         LDA WOJKSTAB,X
         ROR
         STA WOJKSTAB,X
         STA ZN
         BCC WOJARM3
         INC ZN
         BNE WOJARM3
         INC ZN+1
WOJARM3  LDA GRACZ
         ASL
         TAX 
         CLC 
         LDA ZN
         ADC WOJZN,X
         STA ZN
         LDA ZN+1
         ADC WOJZN+1,X
         STA ZN+1
         BCC WOJARM4
         LDA #255
         STA WOJZN,X
         STA WOJZN+1,X
         BMI WOJARM2
WOJARM4  LDA ZN
         STA WOJZN,X
         LDA ZN+1
         STA WOJZN+1,X
         INY 
         CPY #24
         BNE WOJARM1
WOJARM2  RTS 
;
CHKODC   LDY #0
         STY ZN
         STY ZN+1
CHKODC1  LDA BUFFER,Y
         BMI CHKODC2
         INC ZN
CHKODC2  LDA KSTAB,Y
         CMP GRACZ
         BNE CHKODC3
         INC ZN+1
CHKODC3  INY 
         CPY #24
         BNE CHKODC1
         SEC 
         LDA ZN+1
         SBC ZN
         BEQ CHKODC4
         LDY #0
CHKODC5  LDA KSTAB,Y
         CMP GRACZ
         BNE CHKODC6
         TYA 
         LDX #23
CHKODC7  CMP BUFFER,X
         BEQ CHKODC6
         DEX 
         BPL CHKODC7
         STA ZN+1
         ASL
         ASL
         ASL
         TAY 
         LDA #8
         STA ZN+2
CHKODC14 LDA NEARTAB,Y
         BMI CHKODC8
         ASL
         ASL
         ASL
         TAX 
         LDA #8
         STA ZN+3
CHKODC13 LDA NEARTAB,X
         BMI CHKODC9
         STA ZN+5
         STX ZN+4
         TAX 
         LDA KSTAB,X
         CMP GRACZ
         BNE CHKODC10
         LDX #23
         LDA ZN+5
CHKODC12 CMP BUFFER,X
         BEQ CHKODC11
         DEX 
         BPL CHKODC12
         BMI CHKODC10
CHKODC11 LDA ZN+4
         LSR
         LSR
         LSR
         TAY 
         LDX ZN+5
         LDA #255
         RTS 
CHKODC10 LDX ZN+4
         INX 
         DEC ZN+3
         BNE CHKODC13
CHKODC9  INY 
         DEC ZN+2
         BNE CHKODC14
CHKODC8  LDY ZN+1
CHKODC6  INY 
         CPY #24
         BNE CHKODC5
CHKODC4  LDA #0
         RTS 
;
PREPAT   LDY #0
         STY ZN+5
         STY ZN+9
PREPAT1  LDA BUFFER,Y
         BMI PREPAT2
         ASL
         ASL
         ASL
         TAX 
         TYA 
         PHA 
         LDA #8
         STA ZN+4
PREPAT3  LDA NEARTAB,X
         BMI PREPAT4
         TAY 
         LDA KSTAB,Y
         BMI PREPAT15
         CMP GRACZ
         BEQ PREPAT15
         ASL
         ASL
         ORA GRACZ
         TAY 
         LDA SOJTAB,Y
         BNE PREPAT15
         INC ZN+5
PREPAT15 INX 
         DEC ZN+4
         BNE PREPAT3
PREPAT4  PLA 
         TAY 
         INY 
         CPY #24
         BNE PREPAT1
PREPAT2  LDA ZN+5
         BNE PREPAT18
         LDA GRACZ
         TAX 
         ASL
         ASL
         TAY 
         LDA #0
         STA SOJTAB,Y
         STA SOJTAB+1,Y
         STA SOJTAB+2,Y
         STA SOJTAB+3,Y
         STA SOJTAB,X
         STA SOJTAB+4,X
         STA SOJTAB+8,X
         STA SOJTAB+12,X
         JMP PREPAT
PREPAT18 LDA $D20A
         BMI PREPAT5
PREPAT6  CMP ZN+5
         BCC PREPAT7
         SBC ZN+5
         JMP PREPAT6
PREPAT7  TAY 
         INY 
         STY ZN+9
PREPAT5  LDY #0
         STY ZN+4
PREPAT10 LDA BUFFER,Y
         BMI PREPAT11
         ASL
         ASL
         ASL
         TAX 
         TYA 
         PHA 
         LDA #8
         STA ZN+6
PREPAT12 LDA NEARTAB,X
         BMI PREPAT13
         TAY 
         LDA KSTAB,Y
         BMI PREPAT14
         CMP GRACZ
         BEQ PREPAT14
         STY ZN+8
         ASL
         ASL
         ORA GRACZ
         TAY 
         LDA SOJTAB,Y
         BNE PREPAT14
         LDY ZN+8
         LDA DOCHTAB,Y
         DEC ZN+9
         BNE PREPAT8
         STA ZN+4
         STY ZN+5
         TXA 
         LSR
         LSR
         LSR
         STA ZN+7
         PLA 
         JMP PREPAT11
PREPAT8  CMP ZN+4
         BCC PREPAT14
         STA ZN+4
         STY ZN+5
         TXA 
         LSR
         LSR
         LSR
         STA ZN+7
PREPAT14 INX 
         DEC ZN+6
         BNE PREPAT12
PREPAT13 PLA 
         TAY 
         INY 
         CPY #24
         BNE PREPAT10
PREPAT11 LDY #3
         LDX ZN+5
         LDA KSTAB,X
         STA ZN+6
PREPAT16 CPY GRACZ
         BEQ PREPAT17
         CPY ZN+6
         BEQ PREPAT17
         LDA KSZN,Y
         BEQ PREPAT17
         TYA 
         ASL
         ASL
         ORA GRACZ
         TAX 
         LDA SOJTAB,X
         BNE PREPAT17
         LDA $D20A
         AND #1
         BNE PREPAT17
         TYA 
         PHA 
         JSR PROPSOJ
         PLA 
         TAY 
PREPAT17 DEY 
         BPL PREPAT16
         LDY ZN+5
         LDX ZN+7
         LDA ZN+4
         RTS 
;
PROPSOJ  LDA KSZN,Y
         SEC 
         BEQ PROPSOJ4
         CPY HUMANPL
         BEQ PROPSOJ6
         CPY HUMANPL+1
         BNE PROPSOJ1
PROPSOJ6 JMP PROPSOJG
PROPSOJ1 LDA $D20A
         PHA 
         LDX GRACZ
         LDA KSZN,Y
         CMP KSZN,X
         PLA 
         BCS PROPSOJ2
         CMP #128
         BCC PROPSOJ3
         BCS PROPSOJ4
PROPSOJ2 CMP #64
         BCS PROPSOJ4
PROPSOJ3
PROPSOJPROC LDA ZN
         PHA 
         LDA ZN+1
         PHA 
         STY ZN
         STX ZN+1
         TYA 
         ASL
         ASL
         ORA ZN+1
         TAY 
         TXA 
         ASL
         ASL
         ORA ZN
         TAX 
PROPSOJ5 LDA $D20A
         AND #$07
         CMP #6
         BCS PROPSOJ5
         ADC #1
         STA SOJTAB,Y
         STA SOJTAB,X
         PLA 
         STA ZN+1
         PLA 
         STA ZN
         CLC 
         LDA #255
PROPSOJ4 TAY 
         RTS 
;
CHKBUY   LDY #1
         STY ZN
         DEY 
CHKBUY1  LDA BUFFER,Y
         BMI CHKBUY2
         ASL
         ASL
         ASL
         TAX 
         TYA 
         PHA 
         LDA #8
         STA ZN+3
CHKBUY3  LDA NEARTAB,X
         BMI CHKBUY4
         TAY 
         LDA KSTAB,Y
         BMI CHKBUY5
         CMP GRACZ
         BEQ CHKBUY5
         LDA DOCHTAB,Y
         CMP ZN
         BCC CHKBUY5
         STA ZN
         STY ZN+1
         LDA KSTAB,Y
         STA ZN+2
CHKBUY5  INX 
         DEC ZN+3
         BNE CHKBUY3
CHKBUY4  PLA 
         TAY 
         INY 
         CPY #24
         BNE CHKBUY1
CHKBUY2  LDA ZN
         CMP #1
         BEQ CHKBUY6
CHKBUY7  LDA $D20A
         CMP #100
         BCC CHKBUY7
         LDY ZN+1
         LDX ZN+2
         JMP PROPBUY
CHKBUY6  RTS 
;
PROPBUY  STA ZN
         STY ZN+1
         STX ZN+2
         LDA #255
         STA ZN+3
         CPX HUMANPL
         BEQ PROPBUY11
         CPX HUMANPL+1
         BNE PROPBUY1
PROPBUY11 JMP PROPBUYG
PROPBUY1 LDA KSZN,X
         CMP #6
         BCC PROPBUY2
         LDA #0
         STA ZN+4
         LDA ZN+1
         ASL
         ASL
         ASL
         TAX 
         LDA #8
         STA ZN+5
PROPBUY4 LDA NEARTAB,X
         BMI PROPBUY3
         TAY 
         LDA KSTAB,Y
         CMP ZN+2
         BNE PROPBUY5
         INC ZN+4
PROPBUY5 INX 
         DEC ZN+5
         BNE PROPBUY4
PROPBUY3 LDA ZN+4
         CMP #3
         BCS PROPBUY2
         LDY ZN+2
         LDA ARMPOS,Y
         CMP ZN+1
         BEQ PROPBUY2
         LDA $D20A
         AND #1
         BNE PROPBUY2
         LDY ZN+1
         LDA DOCHTAB,Y
         ASL
         STA ZN+4
PROPBUY6 LDA $D20A
         CMP ZN+4
         BCC PROPBUY6
         CMP ZN
         BEQ PROPBUY8
         BCC PROPBUY8
PROPBUY2 JMP PROPBUY7
PROPBUY8
PROPBUYPROC LDX GRACZ
         INC KSZN,X
         LDX ZN+2
         DEC KSZN,X
         LDA #0
         STA ZN+3
         TXA 
         ASL
         TAY 
         LDA ZN+1
         ASL
         TAX 
         CLC 
         LDA WOJZN,Y
         ADC WOJKSTAB,X
         STA ZN+4
         LDA WOJZN+1,Y
         ADC WOJKSTAB+1,X
         STA ZN+5
         BCC PROPBUY9
         LDA #255
         STA ZN+4
         STA ZN+5
PROPBUY9 LDA ZN+4
         STA WOJZN,Y
         LDA ZN+5
         STA WOJZN+1,Y
         LDA #0
         STA WOJKSTAB,X
         STA WOJKSTAB+1,X
         LDX ZN+1
         LDA GRACZ
         STA KSTAB,X
         CLC 
         LDA KASAZN,Y
         ADC ZN
         STA ZN+4
         LDA KASAZN+1,Y
         ADC #0
         STA ZN+5
         BCC PROPBUY10
         LDA #255
         STA ZN+4
         STA ZN+5
PROPBUY10 LDA ZN+4
         STA KASAZN,Y
         LDA ZN+5
         STA KASAZN+1,Y
         LDA GRACZ
         ASL
         TAX 
         SEC 
         LDA KASAZN,X
         SBC ZN
         STA KASAZN,X
         BCS PROPBUY7
         DEC KASAZN+1,X
PROPBUY7 LDA ZN+3
         RTS 
;
BUYWOJ   LDA #0
         LDY #1
         BEQ BUYWOJ1
;
BUYWOJMAX LDA #0
         TAY 
;
BUYWOJ1  STA ZN
         STY ZN+1
         LDA GRACZ
         ASL
         TAX 
         SEC 
         LDA KASAZN,X
         SBC ZN
         STA ZN+2
         LDA KASAZN+1,X
         SBC ZN+1
         STA ZN+3
         LDA ZN
         STA KASAZN,X
         LDA ZN+1
         STA KASAZN+1,X
         CLC 
         LDA WOJZN,X
         ADC ZN+2
         STA ZN
         LDA WOJZN+1,X
         ADC ZN+3
         STA ZN+1
         BCC BUYWOJ2
         LDA #255
         STA ZN
         STA ZN+1
BUYWOJ2  LDA ZN
         STA WOJZN,X
         LDA ZN+1
         STA WOJZN+1,X
         RTS 
;

