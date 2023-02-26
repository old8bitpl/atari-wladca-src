;
         org $B800
;
ZN       =   $C0
;
MOVE     LDY #$00
         STY $D40E
         SEI 
         LDA #$FE
         STA $D301
         STY ZN
         STY ZN+2
         LDA #$80
         STA ZN+1
         LDA #$C0
         STA ZN+3
MOVE1    LDA (ZN),Y
         STA (ZN+2),Y
         INY 
         BNE MOVE1
         INC ZN+1
         INC ZN+3
         BEQ MOVE2
         LDA ZN+3
         CMP #$D0
         BNE MOVE1
         LDA #$D8
         STA ZN+3
         BNE MOVE1
MOVE2    LDA #$FF
         STA $D301
         LDA #$40
         STA $D40E
         CLI 
         RTS 
;
         org $02E2
;
         .WORD MOVE
;
