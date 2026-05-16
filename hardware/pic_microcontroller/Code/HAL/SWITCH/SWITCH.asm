
_SWITCH_Init:

;SWITCH.c,4 :: 		void SWITCH_Init(u8 Port, u8 Pin)
;SWITCH.c,7 :: 		GPIO_SetPinDirection(Port, Pin, GPIO_INPUT);
	MOVF       FARG_SWITCH_Init_Port+0, 0
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVF       FARG_SWITCH_Init_Pin+0, 0
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;SWITCH.c,8 :: 		}
L_end_SWITCH_Init:
	RETURN
; end of _SWITCH_Init

_SWITCH_GetState:

;SWITCH.c,10 :: 		u8 SWITCH_GetState(u8 Port, u8 Pin)
;SWITCH.c,13 :: 		return GPIO_GetPinValue(Port, Pin);
	MOVF       FARG_SWITCH_GetState_Port+0, 0
	MOVWF      FARG_GPIO_GetPinValue_Port+0
	MOVF       FARG_SWITCH_GetState_Pin+0, 0
	MOVWF      FARG_GPIO_GetPinValue_Pin+0
	CALL       _GPIO_GetPinValue+0
;SWITCH.c,14 :: 		}
L_end_SWITCH_GetState:
	RETURN
; end of _SWITCH_GetState
