;
; MODUL: IO
;

DL       .BYTE 112,96,2+64+128
         .WORD TIMELINE
         .BYTE 0,4+64
DLPEZN   .WORD MAPAPIC+1024
         .BYTE 4,4,4,4,4,4,4,4
         .BYTE 4,4,4,4,4,4,4,4
         .BYTE 4,4,4,4,4,4+128
         .BYTE 0,2+64
         .WORD INFOLINE
         .BYTE 16,2
         .BYTE 65
         .WORD DL
;
STATDL   .BYTE 112,112,112,2+64
         .WORD SCRPE
         .BYTE 2,2,2,2,2,2,2
         .BYTE 2,2,2,2,2,2,2,2
         .BYTE 2,2,2,2,2,2,2,2
         .BYTE 65
         .WORD STATDL
;
CZOLODL  .BYTE 112,112,112,4+64
         .WORD CZOLOPIC+$0400+$28
         .BYTE 4,4,4,4,4,4,4,4
         .BYTE 4,4,4,4,4,4,4,4
         .BYTE 4,32+128
         .BYTE 14+64
         .WORD MIRAGEPIC
         .BYTE 14,14,14,14,14,14,14,14
         .BYTE 14,14,14,14,14,14,14,14
         .BYTE 14,14,14,14,14,14,14
         .BYTE 112,6+64
         .WORD OPTLINETXT
         .BYTE 112,64,2+64+16
         .WORD INFOLINE
         .BYTE 65
         .WORD CZOLODL
;
OPTLINETXT .SB "   GRACZE:   $:     "
;
TRUPPICDL .BYTE 112,112,112,112,112,112,112,112,112,4+64
         .WORD SCRPE+$0200
         .BYTE 4,4,4,4,4,4,4
         .BYTE 65
         .WORD TRUPPICDL
;
PRINTPLNAME ASL
         ASL
         ASL
         TAX 
         LDA #5
PRINTPLNAME1 PHA 
         LDA NAMPLTAB,X
         STA INFOLINE,Y
         INX 
         INY 
         PLA 
         SEC 
         SBC #1
         BNE PRINTPLNAME1
         RTS 
;
GETJOY   LDA $D300
         CPY #0
         BEQ GETJOY1
         LSR
         LSR
         LSR
         LSR
GETJOY1  RTS 
;
GETFIRE  LDA $D010,Y
         RTS 
;
CHKPOZ   LDA POM
         LSR
         LSR
         LSR
         BCS CHKPOZ1
         LDX XCEL
         CPX XCELMIN
         BEQ CHKPOZ1
         DEC XCEL
CHKPOZ1  LSR
         BCS CHKPOZ2
         LDX XCEL
         CPX XCELMAX
         BEQ CHKPOZ2
         INC XCEL
CHKPOZ2  RTS 
;
CHKPION  LDA POM
         LSR
         BCS CHKPION1
         LDX YCEL
         CPX YCELMIN
         BEQ CHKPION1
         DEC YCEL
CHKPION1 LSR
         BCS CHKPION2
         LDX YCEL
         CPX YCELMAX
         BEQ CHKPION2
         INC YCEL
CHKPION2 RTS 
;
CONVDEC  STA VZN
         STY VZN+1
         STX VZN+2
         BEQ CONVDEC1
         LDA #$03
         BNE CONVDEC2
CONVDEC1 LDA #$05
CONVDEC2 STA VZN+3
         LDA # <INFOLINE
         LDY # >INFOLINE
         BCC CONVDEC3
         LDA # <MENULINE
         LDY # >MENULINE
CONVDEC3 STY VZN+5
         CLC 
         ADC VZN+2
         STA VZN+4
         BCC CONVDEC4
         INC VZN+5
CONVDEC4 SEC 
         LDA #$05
         SBC VZN+3
         TAX 
CONVDEC5 LDA LDECTAB,X
         STA VZN+6
         LDA HDECTAB,X
         STA VZN+7
         LDY #$10
CONVDEC6 SEC 
         LDA VZN
         SBC VZN+6
         STA VZN+8
         LDA VZN+1
         SBC VZN+7
         STA VZN+9
         BCC CONVDEC7
         LDA VZN+8
         STA VZN
         LDA VZN+9
         STA VZN+1
         INY 
         BNE CONVDEC6
CONVDEC7 TYA 
         LDY #$00
         STA (VZN+4),Y
         INC VZN+4
         BNE CONVDEC8
         INC VZN+5
CONVDEC8 INX 
         DEC VZN+3
         BNE CONVDEC5
         RTS 
;
LDECTAB  .BYTE  <10000, <1000, <100, <10, <1
HDECTAB  .BYTE  >10000, >1000, >100, >10, >1
;
PRINTNULL LDA # <NULLDAT
         LDY # >NULLDAT
;
PRINT    STA VZN
         STY VZN+1
         LDA # <INFOLINE
         LDX # >INFOLINE
         LDY #39
         BCC PRINT1
         LDA # <MENULINE
         LDX # >MENULINE
PRINT1   STA VZN+2
         STX VZN+3
PRINT2   LDA (VZN),Y
         STA (VZN+2),Y
         DEY 
         BPL PRINT2
         RTS 
;
WAIT     STA VBLTIMER
WAIT1    LDA VBLTIMER
         BNE WAIT1
         RTS 
;
CONVLONGTABL .BYTE 128,64,160,16,232,100,10,1
CONVLONGTABH .BYTE 150,66,134,39,3,0,0,0
CONVLONGTABVH .BYTE 152,15,1,0,0,0,0,0
;
CONVLONG STA ZN
         STY ZN+1
         STX ZN+2
         LDA #0
         STA ZN+3
         STA ZN+4
CONVLONG1 LDY ZN+3
         LDA CONVLONGTABL,Y
         STA ZN+5
         LDA CONVLONGTABH,Y
         STA ZN+6
         LDA CONVLONGTABVH,Y
         STA ZN+7
         LDY ZN+4
         LDA #0
         STA VZN+2,Y
CONVLONG2 SEC 
         LDA ZN
         SBC ZN+5
         STA ZN+8
         LDA ZN+1
         SBC ZN+6
         STA ZN+9
         LDA ZN+2
         SBC ZN+7
         STA ZN+10
         BCC CONVLONG3
         LDA ZN+8
         STA ZN
         LDA ZN+9
         STA ZN+1
         LDA ZN+10
         STA ZN+2
         LDX ZN+4
         INC VZN+2,X
         BNE CONVLONG2
CONVLONG3 LDA VZN+2
         BEQ CONVLONG7
         INC ZN+4
CONVLONG7 INC ZN+3
         LDA ZN+3
         CMP #8
         BNE CONVLONG1
         LDA VZN+2
         BNE CONVLONG4
         INC ZN+4
CONVLONG4 LDY #$00
CONVLONG5 LDA ZN+4
         BEQ CONVLONG6
         LDA VZN+2,Y
         ORA #$10
         STA (VZN),Y
         INY 
         DEC ZN+4
         JMP CONVLONG5
CONVLONG6 RTS 
;
WAITFIRE CPY #255
         BEQ WAITFIRE1
WAITFIRE2 JSR GETFIRE
         BNE WAITFIRE2
WAITFIRE3 JSR GETFIRE
         BEQ WAITFIRE3
         BNE WAITFIRE4
WAITFIRE1 LDY #0
         JSR GETFIRE
         BEQ WAITFIRE5
         INY 
         JSR GETFIRE
         BNE WAITFIRE1
WAITFIRE5 LDX #0
         LDY #0
         JSR GETFIRE
         BNE WAITFIRE6
         INX 
WAITFIRE6 INY 
         JSR GETFIRE
         BNE WAITFIRE7
         INX 
WAITFIRE7 TXA 
         BNE WAITFIRE5
WAITFIRE4 RTS 
;
WAITFIREB CPY #255
         BNE WAITFIRE3
         BEQ WAITFIRE5
;

