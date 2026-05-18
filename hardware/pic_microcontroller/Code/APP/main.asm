
_main:

;main.c,77 :: 		void main(void)
;main.c,79 :: 		System_Init();
	CALL       main_System_Init+0
;main.c,81 :: 		while(1)
L_main0:
;main.c,83 :: 		Read_Inputs();
	CALL       main_Read_Inputs+0
;main.c,84 :: 		Apply_Output_Logic();
	CALL       main_Apply_Output_Logic+0
;main.c,85 :: 		Send_ADC_UART();
	CALL       main_Send_ADC_UART+0
;main.c,87 :: 		Delay_ms(500);
	MOVLW      11
	MOVWF      R11+0
	MOVLW      38
	MOVWF      R12+0
	MOVLW      93
	MOVWF      R13+0
L_main2:
	DECFSZ     R13+0, 1
	GOTO       L_main2
	DECFSZ     R12+0, 1
	GOTO       L_main2
	DECFSZ     R11+0, 1
	GOTO       L_main2
	NOP
	NOP
;main.c,88 :: 		}
	GOTO       L_main0
;main.c,89 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

main_System_Init:

;main.c,93 :: 		static void System_Init(void)
;main.c,97 :: 		SWITCH_Init(PIR_INPUT_PORT, PIR_INPUT_PIN);       /* RB1 input */
	MOVLW      1
	MOVWF      FARG_SWITCH_Init_Port+0
	MOVLW      1
	MOVWF      FARG_SWITCH_Init_Pin+0
	CALL       _SWITCH_Init+0
;main.c,98 :: 		SWITCH_Init(LOCK_INPUT_PORT, LOCK_INPUT_PIN);     /* RB2 input */
	MOVLW      1
	MOVWF      FARG_SWITCH_Init_Port+0
	MOVLW      2
	MOVWF      FARG_SWITCH_Init_Pin+0
	CALL       _SWITCH_Init+0
;main.c,99 :: 		SWITCH_Init(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN);   /* RD4 input */
	MOVLW      3
	MOVWF      FARG_SWITCH_Init_Port+0
	MOVLW      4
	MOVWF      FARG_SWITCH_Init_Pin+0
	CALL       _SWITCH_Init+0
;main.c,101 :: 		GPIO_SetPinDirection(VOLTAGE_INPUT_PORT,
	CLRF       FARG_GPIO_SetPinDirection_Port+0
;main.c,102 :: 		VOLTAGE_INPUT_PIN,
	CLRF       FARG_GPIO_SetPinDirection_Pin+0
;main.c,103 :: 		GPIO_INPUT);                 /* RA0 / AN0 input */
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,107 :: 		GPIO_SetPinDirection(LOCK_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
;main.c,108 :: 		LOCK_OUTPUT_PIN,
	CLRF       FARG_GPIO_SetPinDirection_Pin+0
;main.c,109 :: 		GPIO_OUTPUT);                /* RD0 output */
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,111 :: 		GPIO_SetPinDirection(ALARM_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
;main.c,112 :: 		ALARM_OUTPUT_PIN,
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
;main.c,113 :: 		GPIO_OUTPUT);                /* RD1 output */
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,115 :: 		GPIO_SetPinDirection(VOLTAGE_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
;main.c,116 :: 		VOLTAGE_OUTPUT_PIN,
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
;main.c,117 :: 		GPIO_OUTPUT);                /* RD2 output */
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,119 :: 		LED_Init(PIR_LED_PORT, PIR_LED_PIN);              /* RD3 LED only */
	MOVLW      3
	MOVWF      FARG_LED_Init_Port+0
	MOVLW      3
	MOVWF      FARG_LED_Init_Pin+0
	CALL       _LED_Init+0
;main.c,123 :: 		GPIO_SetPinDirection(UART_TX_PORT,
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
;main.c,124 :: 		UART_TX_PIN,
	MOVLW      6
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
;main.c,125 :: 		GPIO_OUTPUT);                /* RC6 / TX */
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,127 :: 		GPIO_SetPinDirection(UART_RX_PORT,
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
;main.c,128 :: 		UART_RX_PIN,
	MOVLW      7
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
;main.c,129 :: 		GPIO_INPUT);                 /* RC7 / RX */
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,133 :: 		GPIO_SetPinValue(LOCK_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,134 :: 		LOCK_OUTPUT_PIN,
	CLRF       FARG_GPIO_SetPinValue_Pin+0
;main.c,135 :: 		GPIO_LOW);                       /* RD0 LOW */
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,137 :: 		GPIO_SetPinValue(ALARM_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,138 :: 		ALARM_OUTPUT_PIN,
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
;main.c,139 :: 		GPIO_LOW);                       /* RD1 LOW */
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,141 :: 		GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,142 :: 		VOLTAGE_OUTPUT_PIN,
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
;main.c,143 :: 		GPIO_LOW);                       /* RD2 LOW */
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,145 :: 		LED_Off(PIR_LED_PORT, PIR_LED_PIN);               /* RD3 LOW */
	MOVLW      3
	MOVWF      FARG_LED_Off_Port+0
	MOVLW      3
	MOVWF      FARG_LED_Off_Pin+0
	CALL       _LED_Off+0
;main.c,149 :: 		ADC_Init();
	CALL       _ADC_Init+0
;main.c,150 :: 		UART_Init();
	CALL       _UART_Init+0
;main.c,151 :: 		}
L_end_System_Init:
	RETURN
; end of main_System_Init

main_Read_Inputs:

;main.c,155 :: 		static void Read_Inputs(void)
;main.c,157 :: 		rb1_state = SWITCH_GetState(PIR_INPUT_PORT, PIR_INPUT_PIN);
	MOVLW      1
	MOVWF      FARG_SWITCH_GetState_Port+0
	MOVLW      1
	MOVWF      FARG_SWITCH_GetState_Pin+0
	CALL       _SWITCH_GetState+0
	MOVF       R0+0, 0
	MOVWF      main_rb1_state+0
;main.c,158 :: 		rb2_state = SWITCH_GetState(LOCK_INPUT_PORT, LOCK_INPUT_PIN);
	MOVLW      1
	MOVWF      FARG_SWITCH_GetState_Port+0
	MOVLW      2
	MOVWF      FARG_SWITCH_GetState_Pin+0
	CALL       _SWITCH_GetState+0
	MOVF       R0+0, 0
	MOVWF      main_rb2_state+0
;main.c,159 :: 		rd4_state = SWITCH_GetState(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN);
	MOVLW      3
	MOVWF      FARG_SWITCH_GetState_Port+0
	MOVLW      4
	MOVWF      FARG_SWITCH_GetState_Pin+0
	CALL       _SWITCH_GetState+0
	MOVF       R0+0, 0
	MOVWF      main_rd4_state+0
;main.c,161 :: 		adc_value = ADC_ReadChannel(VOLTAGE_ADC_CHANNEL);
	CLRF       FARG_ADC_ReadChannel_channel+0
	CALL       _ADC_ReadChannel+0
	MOVF       R0+0, 0
	MOVWF      main_adc_value+0
;main.c,162 :: 		}
L_end_Read_Inputs:
	RETURN
; end of main_Read_Inputs

main_Apply_Output_Logic:

;main.c,166 :: 		static void Apply_Output_Logic(void)
;main.c,187 :: 		if(rb1_state == GPIO_HIGH)
	MOVF       main_rb1_state+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_main_Apply_Output_Logic3
;main.c,189 :: 		LED_On(PIR_LED_PORT, PIR_LED_PIN);                         /* RD3 */
	MOVLW      3
	MOVWF      FARG_LED_On_Port+0
	MOVLW      3
	MOVWF      FARG_LED_On_Pin+0
	CALL       _LED_On+0
;main.c,191 :: 		GPIO_SetPinValue(LOCK_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,192 :: 		LOCK_OUTPUT_PIN,
	CLRF       FARG_GPIO_SetPinValue_Pin+0
;main.c,193 :: 		GPIO_HIGH);                               /* RD0 */
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,195 :: 		GPIO_SetPinValue(ALARM_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,196 :: 		ALARM_OUTPUT_PIN,
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
;main.c,197 :: 		GPIO_HIGH);                               /* RD1 */
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,198 :: 		}
	GOTO       L_main_Apply_Output_Logic4
L_main_Apply_Output_Logic3:
;main.c,199 :: 		else if((rb2_state == GPIO_HIGH) || (rd4_state == GPIO_HIGH))
	MOVF       main_rb2_state+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_main_Apply_Output_Logic11
	MOVF       main_rd4_state+0, 0
	XORLW      1
	BTFSC      STATUS+0, 2
	GOTO       L_main_Apply_Output_Logic11
	GOTO       L_main_Apply_Output_Logic7
L_main_Apply_Output_Logic11:
;main.c,201 :: 		LED_Off(PIR_LED_PORT, PIR_LED_PIN);                        /* RD3 */
	MOVLW      3
	MOVWF      FARG_LED_Off_Port+0
	MOVLW      3
	MOVWF      FARG_LED_Off_Pin+0
	CALL       _LED_Off+0
;main.c,203 :: 		GPIO_SetPinValue(LOCK_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,204 :: 		LOCK_OUTPUT_PIN,
	CLRF       FARG_GPIO_SetPinValue_Pin+0
;main.c,205 :: 		GPIO_HIGH);                               /* RD0 */
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,207 :: 		GPIO_SetPinValue(ALARM_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,208 :: 		ALARM_OUTPUT_PIN,
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
;main.c,209 :: 		GPIO_LOW);                                /* RD1 */
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,210 :: 		}
	GOTO       L_main_Apply_Output_Logic8
L_main_Apply_Output_Logic7:
;main.c,213 :: 		LED_Off(PIR_LED_PORT, PIR_LED_PIN);                        /* RD3 */
	MOVLW      3
	MOVWF      FARG_LED_Off_Port+0
	MOVLW      3
	MOVWF      FARG_LED_Off_Pin+0
	CALL       _LED_Off+0
;main.c,215 :: 		GPIO_SetPinValue(LOCK_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,216 :: 		LOCK_OUTPUT_PIN,
	CLRF       FARG_GPIO_SetPinValue_Pin+0
;main.c,217 :: 		GPIO_LOW);                                /* RD0 */
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,219 :: 		GPIO_SetPinValue(ALARM_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,220 :: 		ALARM_OUTPUT_PIN,
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
;main.c,221 :: 		GPIO_LOW);                                /* RD1 */
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,222 :: 		}
L_main_Apply_Output_Logic8:
L_main_Apply_Output_Logic4:
;main.c,230 :: 		if(adc_value < VOLTAGE_1V_THRESHOLD_ADC)
	MOVLW      205
	SUBWF      main_adc_value+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_main_Apply_Output_Logic9
;main.c,232 :: 		GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,233 :: 		VOLTAGE_OUTPUT_PIN,
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
;main.c,234 :: 		GPIO_HIGH);                               /* RD2 */
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,235 :: 		}
	GOTO       L_main_Apply_Output_Logic10
L_main_Apply_Output_Logic9:
;main.c,238 :: 		GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT,
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
;main.c,239 :: 		VOLTAGE_OUTPUT_PIN,
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
;main.c,240 :: 		GPIO_LOW);                                /* RD2 */
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,241 :: 		}
L_main_Apply_Output_Logic10:
;main.c,242 :: 		}
L_end_Apply_Output_Logic:
	RETURN
; end of main_Apply_Output_Logic

main_Send_ADC_UART:

;main.c,246 :: 		static void Send_ADC_UART(void)
;main.c,254 :: 		UART_SendByte((u8)(adc_value >> 8));
	CLRF       FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;main.c,255 :: 		UART_SendByte((u8)(adc_value & 0xFF));
	MOVLW      255
	ANDWF      main_adc_value+0, 0
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;main.c,256 :: 		}
L_end_Send_ADC_UART:
	RETURN
; end of main_Send_ADC_UART
