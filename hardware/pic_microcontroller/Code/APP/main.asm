
_System_Init:

;main.c,10 :: 		void System_Init(void)
;main.c,13 :: 		GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN0, GPIO_OUTPUT);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	CLRF       FARG_GPIO_SetPinDirection_Pin+0
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,14 :: 		GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN1, GPIO_OUTPUT);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,15 :: 		GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN2, GPIO_OUTPUT);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,16 :: 		GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN3, GPIO_OUTPUT);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,17 :: 		GPIO_SetPinDirection(GPIO_PORTC, GPIO_PIN6, GPIO_OUTPUT);
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      6
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,19 :: 		GPIO_SetPinDirection(GPIO_PORTB, GPIO_PIN1, GPIO_INPUT);
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,20 :: 		GPIO_SetPinDirection(GPIO_PORTB, GPIO_PIN2, GPIO_INPUT);
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,21 :: 		GPIO_SetPinDirection(GPIO_PORTC, GPIO_PIN7, GPIO_INPUT);
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      7
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,22 :: 		GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN4, GPIO_INPUT);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      4
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,23 :: 		GPIO_SetPinDirection(GPIO_PORTA, GPIO_PIN0, GPIO_INPUT);
	CLRF       FARG_GPIO_SetPinDirection_Port+0
	CLRF       FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;main.c,26 :: 		GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN0, GPIO_LOW);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	CLRF       FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,27 :: 		GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN1, GPIO_LOW);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,28 :: 		GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN2, GPIO_LOW);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,29 :: 		GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN3, GPIO_LOW);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,30 :: 		GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN4, GPIO_LOW);
	MOVLW      3
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      4
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,32 :: 		GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN6, GPIO_LOW);
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      6
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,33 :: 		GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN7, GPIO_LOW);
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      7
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,35 :: 		GPIO_SetPinValue(GPIO_PORTB, GPIO_PIN1, GPIO_LOW);
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,36 :: 		GPIO_SetPinValue(GPIO_PORTB, GPIO_PIN2, GPIO_LOW);
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinValue_Port+0
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,38 :: 		GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN0, GPIO_LOW);
	CLRF       FARG_GPIO_SetPinValue_Port+0
	CLRF       FARG_GPIO_SetPinValue_Pin+0
	CLRF       FARG_GPIO_SetPinValue_Value+0
	CALL       _GPIO_SetPinValue+0
;main.c,41 :: 		}
L_end_System_Init:
	RETURN
; end of _System_Init

_main:

;main.c,43 :: 		void main() {
;main.c,47 :: 		u16 adc_value = 0;
;main.c,48 :: 		u16 voltage_mv = 0;
;main.c,50 :: 		System_Init();
	CALL       _System_Init+0
;main.c,53 :: 		ADC_Init();
	CALL       _ADC_Init+0
;main.c,56 :: 		while(1) {
L_main0:
;main.c,58 :: 		adc_value = ADC_ReadChannel(0);
	CLRF       FARG_ADC_ReadChannel_channel+0
	CALL       _ADC_ReadChannel+0
;main.c,62 :: 		voltage_mv = ADC_ConvertToVoltage(adc_value, 5000);
	MOVF       R0+0, 0
	MOVWF      FARG_ADC_ConvertToVoltage_adc_value+0
	MOVLW      136
	MOVWF      FARG_ADC_ConvertToVoltage_vref_mv+0
	CALL       _ADC_ConvertToVoltage+0
;main.c,66 :: 		if (voltage_mv < 1000) {
	MOVLW      128
	MOVWF      R1+0
	MOVLW      128
	XORLW      3
	SUBWF      R1+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__main7
	MOVLW      232
	SUBWF      R0+0, 0
L__main7:
	BTFSC      STATUS+0, 0
	GOTO       L_main2
;main.c,67 :: 		PORTD.B0 = 1;  // Make RD0 HIGH
	BSF        8, 0
;main.c,68 :: 		} else {
	GOTO       L_main3
L_main2:
;main.c,69 :: 		PORTD.B0 = 0;  // Make RD0 LOW
	BCF        8, 0
;main.c,70 :: 		}
L_main3:
;main.c,73 :: 		Delay_ms(100);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      8
	MOVWF      R12+0
	MOVLW      119
	MOVWF      R13+0
L_main4:
	DECFSZ     R13+0, 1
	GOTO       L_main4
	DECFSZ     R12+0, 1
	GOTO       L_main4
	DECFSZ     R11+0, 1
	GOTO       L_main4
;main.c,74 :: 		}
	GOTO       L_main0
;main.c,75 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
