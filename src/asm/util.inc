;
; MODUL: UTIL
;
         org $a400
;

;NOPTPLJOY PLAYERS JOYSTICKS
;0         1       1
;1         2       1
;2         3       1
;3         4       1
;4         2       2
;5         4       2

IS_CURRENT_PLAYER_HUMAN
         LDA GRACZ
IS_PLAYER_HUMAN
         LDX #3
IS_PLAYER_HUMAN_LOOP
         CMP HUMANPL,X
         BEQ IS_PLAYER_HUMAN_FOUND
         DEX
         BPL IS_PLAYER_HUMAN_LOOP
         CPX #3
IS_PLAYER_HUMAN_FOUND
         RTS

IS_SINGLE_HUMAN_PLAYER
         LDA NOPTPLJOY
         RTS

N_PLAYERS_TAB
         .BYTE 1,2,3,4,2,4


GET_N_PLAYERS
         LDY NOPTPLJOY
         LDA N_PLAYERS_TAB,Y
		 RTS


N_JOYSTICKS_TAB
         .BYTE 1,1,1,1,2,2


GET_N_JOYSTICKS
         LDY NOPTPLJOY
         LDA N_JOYSTICKS_TAB,Y
		 RTS


WAIT_FIRE
         JSR GETFIRE
         BNE WAIT_FIRE
WAIT_RELEASE_FIRE
         JSR GETFIRE
         BEQ WAIT_RELEASE_FIRE
         RTS


WAIT_ANY_FIRE
         LDY #0
         JSR GETFIRE
         BEQ WAIT_ANY_FIRE_END

         JSR GET_N_JOYSTICKS
         CMP #2
         BNE WAIT_ANY_FIRE_END

         LDY #1
         JSR GETFIRE

WAIT_ANY_FIRE_END
         RTS


; returns:
; joystick no (0-1) or 255 if not appropriate
;NOPTPLJOY	GRACZ	RESULT
;0			0		0
;0			1		255
;0			2		255
;0			3		255
;0			4+		255
;
;1			0		0
;1			1		0
;1			2		255
;1			3		255
;1			4+		255
;
;2			0		0
;2			1		0
;2			2		0
;2			3		255
;2			4+		255
;
;3			0		0
;3			1		0
;3			2		0
;3			3		0
;3			4+		255
;
;4			0		0
;4			1		1
;4			2		255
;4			3		255
;4			4+		255
;
;5			0		0
;5			1		0
;5			2		1
;5			3		1
;5			4+		255
GET_CURRENT_PLAYER_JOYSTICK
         LDA GRACZ

GET_PLAYER_JOYSTICK
         TAX
         LDA NOPTPLJOY
         CMP #4
         BCS GETPLJOYSTICK_MODE_4

; FOR NOPTPLJOY=0-3 JOYSTICK 0 or 255
         STA VZN
         INC VZN
         CPX VZN
         BCS GETPLJOYSTICKERR
         BCC GETPLJOYSTICK0

GETPLJOYSTICK_MODE_4
; FOR NOPTPLJOY=4 JOYSTICK 0, 1 or 255
         CMP #4
         BNE GETPLJOYSTICK_MODE_5

         CPX #0
         BEQ GETPLJOYSTICK0
         CPX #1
         BEQ GETPLJOYSTICK1
         BNE GETPLJOYSTICKERR

GETPLJOYSTICK_MODE_5
; FOR NOPTPLJOY=5 JOYSTICK 0, 1 or 255
         CMP #5
         BNE GETPLJOYSTICKERR

         CPX #0
         BEQ GETPLJOYSTICK0
         CPX #1
         BEQ GETPLJOYSTICK0
         CPX #2
         BEQ GETPLJOYSTICK1
         CPX #3
         BEQ GETPLJOYSTICK1
         BNE GETPLJOYSTICKERR

GETPLJOYSTICK0
         LDA #0
         RTS         
GETPLJOYSTICK1
         LDA #1
         RTS
GETPLJOYSTICKERR
         LDA #255
         RTS
