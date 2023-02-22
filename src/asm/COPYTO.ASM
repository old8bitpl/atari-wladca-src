         .OPT NO LIST
;
         *=  $3000
;
ZN       =   $C0
;
FNO      *=  *+1
LEN      *=  *+2
;
IDTAB    .BYTE "D1:MAC65.COM",$9B
         .BYTE "D1:GLUS.COM",$9B
         .BYTE "D1:GM25.COM",$9B
         .BYTE "D1:LABELS.M65",$9B
         .BYTE "D1:IO.M65",$9B
         .BYTE "D1:MAIN.M65",$9B
         .BYTE "D1:MYSL.M65",$9B
         .BYTE "D1:GRINT.M65",$9B
         .BYTE "D1:CZOLO.M65",$9B
         .BYTE "D1:GRA.M65",$9B
         .BYTE "D1:BITWA.M65",$9B
         .BYTE "D1:MACHINA.M65",$9B
         .BYTE "D1:TURNIEJ.M65",$9B
         .BYTE "D1:KONIEC.M65",$9B
         .BYTE 0
;
FINDNO   LDA # <IDTAB
         LDY # >IDTAB
         STA ZN
         STY ZN+1
         LDX FNO
         LDY #0
FINDNO1  DEX 
         BMI FINDNO2
FINDNO4  LDA (ZN),Y
         BEQ FINDNO5
         INC ZN
         BNE FINDNO3
         INC ZN+1
FINDNO3  CMP #$9B
         BNE FINDNO4
         BEQ FINDNO1
FINDNO2  LDA ZN
         LDY ZN+1
FINDNO5  RTS 
;
CLOSE    LDX #$10
         LDA #$0C
         STA $0342,X
         JMP $E456
;
OPENR    JSR FINDNO
         BEQ OPENR1
         LDX #$10
         STA $0344,X
         TYA 
         STA $0345,X
         LDA #$03
         STA $0342,X
         LDA #$04
         STA $034A,X
         JSR $E456
         LDY #$01
OPENR1   RTS 
;
OPENW    JSR FINDNO
         LDX #$10
         STA $0344,X
         TYA 
         STA $0345,X
         LDA #$03
         STA $0342,X
         LDA #$08
         STA $034A,X
         LDY #$01
         LDA #'8
         STA (ZN),Y
         JMP $E456
;
GETBLOK  LDX #$10
         LDA #$07
         STA $0342,X
         LDA # <BUFFER
         STA $0344,X
         LDA # >BUFFER
         STA $0345,X
         LDA #$00
         STA $0348,X
         LDA #$80
         STA $0349,X
         JSR $E456
         LDA $0348,X
         STA LEN
         LDA $0349,X
         STA LEN+1
         RTS 
;
PUTBLOK  LDX #$10
         LDA #$0B
         STA $0342,X
         LDA # <BUFFER
         STA $0344,X
         LDA # >BUFFER
         STA $0345,X
         LDA LEN
         STA $0348,X
         LDA LEN+1
         STA $0349,X
         JMP $E456
;
PR       LDA $D01F
         AND #$07
         CMP #$07
         BNE PR2
         LDA #$00
         STA FNO
PR1      JSR OPENR
         BEQ PR2
         JSR GETBLOK
         JSR CLOSE
         JSR OPENW
         JSR PUTBLOK
         JSR CLOSE
         INC FNO
         JMP PR1
PR2      LDY #$00
         STY $0244
         INY 
         STY $09
         JMP ($0A)
;
BUFFER
;
         *=  $02E0
;
         .WORD PR
;
