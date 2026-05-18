
_ADC_Init:

;ADC.c,47 :: 		void ADC_Init(void) {
;ADC.c,48 :: 		u8 temp_adcon0 = 0;
;ADC.c,49 :: 		u8 temp_adcon1 = 0;
	CLRF       ADC_Init_temp_adcon1_L0+0
;ADC.c,52 :: 		CLR_BIT(ADCON0_REG, ADON);
	MOVLW      254
	ANDWF      31, 1
;ADC.c,58 :: 		temp_adcon1 |= (1 << ADFM);     // Set ADFM = 1 for right justified
	MOVLW      128
	IORWF      ADC_Init_temp_adcon1_L0+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      ADC_Init_temp_adcon1_L0+0
;ADC.c,64 :: 		temp_adcon1 |= (ADC_PORT_CONFIG & PCFG_MASK);
	MOVLW      14
	IORWF      R0+0, 1
	MOVF       R0+0, 0
	MOVWF      ADC_Init_temp_adcon1_L0+0
;ADC.c,67 :: 		ADCON1_REG = temp_adcon1;
	MOVF       R0+0, 0
	MOVWF      159
;ADC.c,81 :: 		ADCON0_REG = temp_adcon0;
	MOVLW      128
	MOVWF      31
;ADC.c,84 :: 		SET_BIT(ADCON0_REG, ADON);          // ADON = 1, turn ADC ON
	BSF        31, 0
;ADC.c,87 :: 		Delay_us(20);
	MOVLW      26
	MOVWF      R13+0
L_ADC_Init0:
	DECFSZ     R13+0, 1
	GOTO       L_ADC_Init0
	NOP
;ADC.c,88 :: 		}
L_end_ADC_Init:
	RETURN
; end of _ADC_Init

_ADC_Enable:

;ADC.c,99 :: 		void ADC_Enable(void) {
;ADC.c,100 :: 		SET_BIT(ADCON0_REG, ADON);          // Set ADON bit to turn ADC ON
	BSF        31, 0
;ADC.c,101 :: 		}
L_end_ADC_Enable:
	RETURN
; end of _ADC_Enable

_ADC_Disable:

;ADC.c,112 :: 		void ADC_Disable(void) {
;ADC.c,113 :: 		CLR_BIT(ADCON0_REG, ADON);        // Clear ADON bit to turn ADC OFF
	MOVLW      254
	ANDWF      31, 1
;ADC.c,114 :: 		}
L_end_ADC_Disable:
	RETURN
; end of _ADC_Disable

_ADC_SelectChannel:

;ADC.c,131 :: 		void ADC_SelectChannel(u8 channel) {
;ADC.c,133 :: 		channel &= 0x07;
	MOVLW      7
	ANDWF      FARG_ADC_SelectChannel_channel+0, 0
	MOVWF      R2+0
	MOVF       R2+0, 0
	MOVWF      FARG_ADC_SelectChannel_channel+0
;ADC.c,136 :: 		ADCON0_REG &= ~CHS_MASK;
	MOVLW      199
	ANDWF      31, 1
;ADC.c,139 :: 		ADCON0_REG |= (channel << CHS0);
	MOVF       R2+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	IORWF      31, 1
;ADC.c,140 :: 		}
L_end_ADC_SelectChannel:
	RETURN
; end of _ADC_SelectChannel

_ADC_StartConversion:

;ADC.c,155 :: 		void ADC_StartConversion(void) {
;ADC.c,156 :: 		SET_BIT(ADCON0_REG, GO_DONE);       // Set GO/DONE bit to start conversion
	BSF        31, 2
;ADC.c,157 :: 		}
L_end_ADC_StartConversion:
	RETURN
; end of _ADC_StartConversion

_ADC_IsConversionDone:

;ADC.c,173 :: 		u8 ADC_IsConversionDone(void) {
;ADC.c,176 :: 		return !GET_BIT(ADCON0_REG, GO_DONE);
	MOVF       31, 0
	MOVWF      R0+0
	RRF        R0+0, 1
	BCF        R0+0, 7
	RRF        R0+0, 1
	BCF        R0+0, 7
	MOVLW      1
	ANDWF      R0+0, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	MOVLW      1
	BTFSS      STATUS+0, 2
	MOVLW      0
	MOVWF      R0+0
;ADC.c,177 :: 		}
L_end_ADC_IsConversionDone:
	RETURN
; end of _ADC_IsConversionDone

_ADC_ReadResult:

;ADC.c,203 :: 		u16 ADC_ReadResult(void) {
;ADC.c,204 :: 		u16 result = 0;
;ADC.c,209 :: 		result = ((u16)ADRESH_REG << 8) | ADRESL_REG;
	MOVF       158, 0
	MOVWF      R0+0
;ADC.c,216 :: 		result &= 0x03FF;
	MOVLW      255
	ANDWF      R0+0, 1
;ADC.c,218 :: 		return result;
;ADC.c,219 :: 		}
L_end_ADC_ReadResult:
	RETURN
; end of _ADC_ReadResult

_ADC_ReadChannel:

;ADC.c,246 :: 		u16 ADC_ReadChannel(u8 channel) {
;ADC.c,247 :: 		u16 adc_result = 0;
;ADC.c,250 :: 		ADC_SelectChannel(channel);
	MOVF       FARG_ADC_ReadChannel_channel+0, 0
	MOVWF      FARG_ADC_SelectChannel_channel+0
	CALL       _ADC_SelectChannel+0
;ADC.c,254 :: 		Delay_us(ADC_ACQUISITION_DELAY_US);
	MOVLW      26
	MOVWF      R13+0
L_ADC_ReadChannel1:
	DECFSZ     R13+0, 1
	GOTO       L_ADC_ReadChannel1
	NOP
;ADC.c,257 :: 		ADC_StartConversion();
	CALL       _ADC_StartConversion+0
;ADC.c,261 :: 		while (!ADC_IsConversionDone()) {
L_ADC_ReadChannel2:
	CALL       _ADC_IsConversionDone+0
	MOVF       R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_ADC_ReadChannel3
;ADC.c,263 :: 		}
	GOTO       L_ADC_ReadChannel2
L_ADC_ReadChannel3:
;ADC.c,266 :: 		adc_result = ADC_ReadResult();
	CALL       _ADC_ReadResult+0
;ADC.c,268 :: 		return adc_result;
;ADC.c,269 :: 		}
L_end_ADC_ReadChannel:
	RETURN
; end of _ADC_ReadChannel

_ADC_StartChannelConversion:

;ADC.c,295 :: 		void ADC_StartChannelConversion(u8 channel) {
;ADC.c,297 :: 		ADC_SelectChannel(channel);
	MOVF       FARG_ADC_StartChannelConversion_channel+0, 0
	MOVWF      FARG_ADC_SelectChannel_channel+0
	CALL       _ADC_SelectChannel+0
;ADC.c,300 :: 		Delay_us(ADC_ACQUISITION_DELAY_US);
	MOVLW      26
	MOVWF      R13+0
L_ADC_StartChannelConversion4:
	DECFSZ     R13+0, 1
	GOTO       L_ADC_StartChannelConversion4
	NOP
;ADC.c,303 :: 		ADC_StartConversion();
	CALL       _ADC_StartConversion+0
;ADC.c,306 :: 		}
L_end_ADC_StartChannelConversion:
	RETURN
; end of _ADC_StartChannelConversion

_ADC_ConvertToVoltage:

;ADC.c,333 :: 		u16 ADC_ConvertToVoltage(u16 adc_value, u16 vref_mv) {
;ADC.c,334 :: 		u16 voltage_mv = 0;
;ADC.c,337 :: 		if (adc_value > ADC_10BIT_MAX) {
	MOVLW      128
	XORLW      3
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__ADC_ConvertToVoltage16
	MOVF       FARG_ADC_ConvertToVoltage_adc_value+0, 0
	SUBLW      255
L__ADC_ConvertToVoltage16:
	BTFSC      STATUS+0, 0
	GOTO       L_ADC_ConvertToVoltage5
;ADC.c,338 :: 		adc_value = ADC_10BIT_MAX;
	MOVLW      255
	MOVWF      FARG_ADC_ConvertToVoltage_adc_value+0
;ADC.c,339 :: 		}
L_ADC_ConvertToVoltage5:
;ADC.c,344 :: 		voltage_mv = (u16)(((unsigned long)adc_value * vref_mv) >> 10);
	MOVF       FARG_ADC_ConvertToVoltage_adc_value+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	CLRF       R0+2
	CLRF       R0+3
	MOVF       FARG_ADC_ConvertToVoltage_vref_mv+0, 0
	MOVWF      R4+0
	CLRF       R4+1
	CLRF       R4+2
	CLRF       R4+3
	CALL       _Mul_32x32_U+0
	MOVLW      10
	MOVWF      R8+0
	MOVF       R0+0, 0
	MOVWF      R4+0
	MOVF       R0+1, 0
	MOVWF      R4+1
	MOVF       R0+2, 0
	MOVWF      R4+2
	MOVF       R0+3, 0
	MOVWF      R4+3
	MOVF       R8+0, 0
L__ADC_ConvertToVoltage17:
	BTFSC      STATUS+0, 2
	GOTO       L__ADC_ConvertToVoltage18
	RRF        R4+3, 1
	RRF        R4+2, 1
	RRF        R4+1, 1
	RRF        R4+0, 1
	BCF        R4+3, 7
	ADDLW      255
	GOTO       L__ADC_ConvertToVoltage17
L__ADC_ConvertToVoltage18:
;ADC.c,346 :: 		return voltage_mv;
	MOVF       R4+0, 0
	MOVWF      R0+0
;ADC.c,347 :: 		}
L_end_ADC_ConvertToVoltage:
	RETURN
; end of _ADC_ConvertToVoltage
