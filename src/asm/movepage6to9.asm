;
         org $100
;
ZN       =   $C0
;
MOVE     SEI
         LDY #$00
MOVE1
         LDA $0600,Y
		 STA $0900,Y
		 INY
		 BNE MOVE1
         CLI 
         RTS 
;
         org $02E2
;
         .WORD MOVE
;
