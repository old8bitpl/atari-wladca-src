;
; MODUL: мацхина
;
;
KULEDAT  .SBYTE "         KULE DO KATAPULTY:             "
;
MACHINA  LDA ZN
         PHA 
         LDA ZN+1
         PHA 
         LDA ZN+2
         PHA 
         LDA ZN+3
         PHA 
         LDX #0
         LDA GRACZ
         CMP HUMANPL
         BEQ MACHINA11
         INX 
MACHINA11 STX ZN+3
         INC NOBL,X
         BNE MACHINA8
         LDA #255
         STA NOBL,X
MACHINA8 LDA $D20A
         AND #1
         CLC 
         ADC #3
         JSR SETSCR
         LDA #0
         JSR PLMURFAZA
         LDA #0
         JSR PLMACHPOS
         LDA # <KULEDAT
         LDY # >KULEDAT
         CLC 
         JSR PRINT
         SEC 
         JSR PRINTNULL
         LDA #13
         LDY #9
         LDX #0
         STA ZN
         STY ZN+1
         STX ZN+2
MACHINA2 LDA #0
         LDY #9
         STA YCELMIN
         STY YCEL
         STY YCELMAX
         DEC ZN
         LDA #255
         CLC 
         PHP 
         LDA ZN
         LDY #0
         LDX #28
         PLP 
         JSR CONVDEC
         SEC 
         LDA ZN+1
         BEQ MACHINA15
         CLC 
         LDA ZN
         BNE MACHINA1
MACHINA15 JMP MACHINA5
MACHINA1 LDY #0
         LDA NOPCJA
         CMP #2
         BNE MACHINA12
         LDY ZN+3
MACHINA12 JSR GETJOY
         STA POM
         JSR CHKPION
         SEC 
         LDA #9
         SBC YCEL
         JSR PLMACHPOS
         LDA #2
         JSR WAIT
         LDA IMMZN
         BNE MACHINA10
         LDA $D01F
         AND #$07
         CMP #$03
         BEQ MACHINA5
MACHINA10 LDY #0
         LDA NOPCJA
         CMP #2
         BNE MACHINA13
         LDY ZN+3
MACHINA13 JSR GETFIRE
         BNE MACHINA1
         SEC 
         LDA #9
         SBC YCEL
MACHINA3 CMP #12
         BEQ MACHINA4
         PHA 
         JSR PLMACHPOS
         LDA #2
         JSR WAIT
         PLA 
         CLC 
         ADC #1
         BNE MACHINA3
MACHINA4 LDA YCEL
         JSR LOTKULA
         LDA YCEL
         CMP ZN+1
         BNE MACHINA6
         DEC ZN+1
         INC ZN+2
         LDA ZN+2
         JSR PLMURFAZA
MACHINA6 LDA #30
         JSR WAIT
         LDA #11
MACHINA7 PHA 
         JSR PLMACHPOS
         LDA #3
         JSR WAIT
         PLA 
         SEC 
         SBC #1
         BPL MACHINA7
         JMP MACHINA2
MACHINA5 ADC #0
         STA VZN
         BEQ MACHINA9
         LDX ZN+3
         INC NWINOBL,X
         BNE MACHINA9
         LDA #255
         STA NWINOBL,X
MACHINA9 LDY #0
         LDA NOPCJA
         CMP #2
         BNE MACHINA14
         LDY ZN+3
MACHINA14 JSR WAITFIRE
         PLA 
         STA ZN+3
         PLA 
         STA ZN+2
         PLA 
         STA ZN+1
         PLA 
         STA ZN
         LDA VZN
         RTS 
;
PLMACHPOS ASL A
         ASL A
         ASL A
         CLC 
         ADC # <KATANIMBUF
         STA VZN
         LDA # >KATANIMBUF
         ADC #0
         STA VZN+1
         LDX #0
         LDA #15
         STA VZN+2
PLMACHPOS1 LDY #0
PLMACHPOS2 LDA (VZN),Y
         STA ZAMEK1PIC+86*8,X
         STA ZAMEK2PIC+86*8,X
         INY 
         INX 
         CPY #8
         BNE PLMACHPOS2
         CLC 
         LDA VZN
         ADC #96
         STA VZN
         BCC PLMACHPOS3
         INC VZN+1
PLMACHPOS3 DEC VZN+2
         BNE PLMACHPOS1
         RTS 
;
LICZKULAPOS LDY XCEL
         LDA (VZN),Y
         STA POM
         LDA #168
         SEC 
         SBC POM
         TAY 
         JSR POSKULA
         INC XCEL
         RTS 
;
POSKULA  LDX #$00
         TXA 
POSKULA1 STA PMBASE+$0400,X
         STA PMBASE+$0500,X
         INX 
         BNE POSKULA1
         JSR CHKPOZKULA
         LDA #$10
POSKULA2 PHA 
         LDA KULASPRDATA,X
         STA PMBASE+$0400,Y
         LDA KULASPRDATB,X
         STA PMBASE+$0500,Y
         INX 
         INY 
         PLA 
         SEC 
         SBC #$01
         BNE POSKULA2
         RTS 
;
CHKPOZKULA LDA #$00
         LDX XCEL
         CPX #36
         BCC CHKPOZKULA1
         ADC #$0F
         CPX #80
         BCC CHKPOZKULA1
         ADC #$0F
         CPX #92
         BCC CHKPOZKULA1
         ADC #$0F
CHKPOZKULA1 TAX 
         RTS 
;
KULASPRDATA .BYTE $00,$00,$00,$00,$00,$00,$04,$0E
         .BYTE $0E,$0E,$1E,$1E,$1C,$1C,$18,$00
;
         .BYTE $00,$00,$00,$00,$00,$00,$04,$0C
         .BYTE $0C,$1C,$1C,$18,$00,$00,$00,$00
;
         .BYTE $00,$00,$00,$00,$00,$00,$00,$08
         .BYTE $08,$18,$00,$00,$00,$00,$00,$00
;
         .BYTE $00,$00,$00,$00,$00,$00,$00,$00
         .BYTE $10,$00,$00,$00,$00,$00,$00,$00
;
KULASPRDATB .BYTE $00,$00,$00,$00,$18,$18,$38,$78
         .BYTE $70,$70,$60,$60,$20,$20,$00,$00
;
         .BYTE $00,$00,$00,$00,$18,$3C,$38,$30
         .BYTE $30,$20,$20,$00,$00,$00,$00,$00
;
         .BYTE $00,$00,$00,$00,$00,$00,$18,$10
         .BYTE $10,$00,$00,$00,$00,$00,$00,$00
;
         .BYTE $00,$00,$00,$00,$00,$00,$00,$10
         .BYTE $00,$00,$00,$00,$00,$00,$00,$00
;
LOTKULA  TAY 
         LDA # <LOTDAT
         LDX # >LOTDAT
LOTKULA2 DEY 
         BMI LOTKULA3
         CLC 
         ADC #$80
         BCC LOTKULA2
         INX 
         BNE LOTKULA2
LOTKULA3 STA VZN
         STX VZN+1
         LDA #$02
         STA XCEL
         STA $D012
         STA $D008
         STA $D009
         LDA #$04
         STA $D013
         LDA #138
         STA $D000
         STA $D001
LOTKULA1 JSR LICZKULAPOS
         LDA #1
         JSR WAIT
         LDA POM
         BEQ LOTKULA4
         LDA XCEL
         CMP #98
         BCC LOTKULA1
LOTKULA4 LDA #0
         STA $D000
         STA $D001
         RTS 
;
PLMURFAZA ASL A
         ASL A
         ASL A
         CLC 
         ADC # <MURANIMBUF
         STA VZN
         LDA # >MURANIMBUF
         ADC #0
         STA VZN+1
         LDX #0
         LDA #27
         STA VZN+2
PLMURFAZA1 LDY #0
PLMURFAZA2 LDA (VZN),Y
         STA ZAMEK1PIC+101*8,X
         STA ZAMEK2PIC+101*8,X
         INY 
         INX 
         CPY #8
         BNE PLMURFAZA2
         CLC 
         LDA VZN
         ADC #96
         STA VZN
         BCC PLMURFAZA3
         INC VZN+1
PLMURFAZA3 DEC VZN+2
         BNE PLMURFAZA1
         RTS 
;
