
_UART_Init:

;UART.c,32 :: 		void UART_Init(void)
;UART.c,35 :: 		CLR_BIT(RCSTA, RCSTA_SPEN);
	BCF        24, 7
;UART.c,40 :: 		SPBRG = (u8)UART_SPBRG_VALUE;
	MOVLW      103
	MOVWF      153
;UART.c,44 :: 		TXSTA = 0x00;
	CLRF       152
;UART.c,48 :: 		CLR_BIT(TXSTA, TXSTA_SYNC);     // Asynchronous mode
	BCF        152, 4
;UART.c,56 :: 		SET_BIT(TXSTA, TXSTA_BRGH);     // High speed mode
	BSF        152, 2
;UART.c,65 :: 		CLR_BIT(TXSTA, TXSTA_TX9);      // 8-bit transmission
	BCF        152, 6
;UART.c,70 :: 		SET_BIT(TXSTA, TXSTA_TXEN);     // Enable transmitter
	BSF        152, 5
;UART.c,77 :: 		RCSTA = 0x00;
	CLRF       24
;UART.c,83 :: 		CLR_BIT(RCSTA, RCSTA_RX9);      // 8-bit reception
	BCF        24, 6
;UART.c,89 :: 		SET_BIT(RCSTA, RCSTA_CREN); // Enable continuous receive
	BSF        24, 4
;UART.c,96 :: 		SET_BIT(RCSTA, RCSTA_SPEN);         // Serial port enabled
	BSF        24, 7
;UART.c,99 :: 		UART_ClearErrors();
	CALL       _UART_ClearErrors+0
;UART.c,107 :: 		Delay_ms(10);
	MOVLW      52
	MOVWF      R12+0
	MOVLW      241
	MOVWF      R13+0
L_UART_Init0:
	DECFSZ     R13+0, 1
	GOTO       L_UART_Init0
	DECFSZ     R12+0, 1
	GOTO       L_UART_Init0
	NOP
	NOP
;UART.c,108 :: 		}
L_end_UART_Init:
	RETURN
; end of _UART_Init

_UART_SendByte:

;UART.c,123 :: 		void UART_SendByte(u8 txData)
;UART.c,127 :: 		while (!GET_BIT(PIR1, PIR1_TXIF))
L_UART_SendByte1:
	MOVF       12, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	RRF        R1+0, 1
	BCF        R1+0, 7
	RRF        R1+0, 1
	BCF        R1+0, 7
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSC      R1+0, 0
	GOTO       L_UART_SendByte2
;UART.c,130 :: 		}
	GOTO       L_UART_SendByte1
L_UART_SendByte2:
;UART.c,134 :: 		TXREG = txData;
	MOVF       FARG_UART_SendByte_txData+0, 0
	MOVWF      25
;UART.c,135 :: 		}
L_end_UART_SendByte:
	RETURN
; end of _UART_SendByte

_UART_SendChar:

;UART.c,141 :: 		void UART_SendChar(char ch)
;UART.c,143 :: 		UART_SendByte((u8)ch);
	MOVF       FARG_UART_SendChar_ch+0, 0
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,144 :: 		}
L_end_UART_SendChar:
	RETURN
; end of _UART_SendChar

_UART_SendString:

;UART.c,154 :: 		void UART_SendString(const char* str)
;UART.c,156 :: 		u8 i = 0;
	CLRF       UART_SendString_i_L0+0
;UART.c,159 :: 		if (str == 0)
	MOVLW      0
	XORWF      FARG_UART_SendString_str+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__UART_SendString32
	MOVLW      0
	XORWF      FARG_UART_SendString_str+0, 0
L__UART_SendString32:
	BTFSS      STATUS+0, 2
	GOTO       L_UART_SendString3
;UART.c,161 :: 		return;
	GOTO       L_end_UART_SendString
;UART.c,162 :: 		}
L_UART_SendString3:
;UART.c,165 :: 		while (str[i] != UART_NULL_CHAR)
L_UART_SendString4:
	MOVF       UART_SendString_i_L0+0, 0
	ADDWF      FARG_UART_SendString_str+0, 0
	MOVWF      R0+0
	MOVF       FARG_UART_SendString_str+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_UART_SendString5
;UART.c,167 :: 		UART_SendByte((u8)str[i]);
	MOVF       UART_SendString_i_L0+0, 0
	ADDWF      FARG_UART_SendString_str+0, 0
	MOVWF      R0+0
	MOVF       FARG_UART_SendString_str+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,168 :: 		i++;
	INCF       UART_SendString_i_L0+0, 1
;UART.c,171 :: 		if (i >= 255)
	MOVLW      255
	SUBWF      UART_SendString_i_L0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_UART_SendString6
;UART.c,173 :: 		break;
	GOTO       L_UART_SendString5
;UART.c,174 :: 		}
L_UART_SendString6:
;UART.c,175 :: 		}
	GOTO       L_UART_SendString4
L_UART_SendString5:
;UART.c,176 :: 		}
L_end_UART_SendString:
	RETURN
; end of _UART_SendString

_UART_SendNumber:

;UART.c,188 :: 		void UART_SendNumber(u16 number)
;UART.c,191 :: 		u8 i = 0;
	CLRF       UART_SendNumber_i_L0+0
;UART.c,194 :: 		if (number == 0)
	MOVLW      0
	XORWF      FARG_UART_SendNumber_number+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__UART_SendNumber34
	MOVLW      0
	XORWF      FARG_UART_SendNumber_number+0, 0
L__UART_SendNumber34:
	BTFSS      STATUS+0, 2
	GOTO       L_UART_SendNumber7
;UART.c,196 :: 		UART_SendByte('0');
	MOVLW      48
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,197 :: 		return;
	GOTO       L_end_UART_SendNumber
;UART.c,198 :: 		}
L_UART_SendNumber7:
;UART.c,201 :: 		while (number > 0)
L_UART_SendNumber8:
	MOVF       FARG_UART_SendNumber_number+1, 0
	SUBLW      0
	BTFSS      STATUS+0, 2
	GOTO       L__UART_SendNumber35
	MOVF       FARG_UART_SendNumber_number+0, 0
	SUBLW      0
L__UART_SendNumber35:
	BTFSC      STATUS+0, 0
	GOTO       L_UART_SendNumber9
;UART.c,203 :: 		buffer[i] = (number % 10) + '0';    // Convert digit to ASCII
	MOVF       UART_SendNumber_i_L0+0, 0
	ADDLW      UART_SendNumber_buffer_L0+0
	MOVWF      FLOC__UART_SendNumber+0
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       FARG_UART_SendNumber_number+0, 0
	MOVWF      R0+0
	MOVF       FARG_UART_SendNumber_number+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVLW      48
	ADDWF      R0+0, 1
	MOVF       FLOC__UART_SendNumber+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
;UART.c,204 :: 		number = number / 10;
	MOVLW      10
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	MOVF       FARG_UART_SendNumber_number+0, 0
	MOVWF      R0+0
	MOVF       FARG_UART_SendNumber_number+1, 0
	MOVWF      R0+1
	CALL       _Div_16X16_U+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART_SendNumber_number+0
	MOVF       R0+1, 0
	MOVWF      FARG_UART_SendNumber_number+1
;UART.c,205 :: 		i++;
	INCF       UART_SendNumber_i_L0+0, 1
;UART.c,206 :: 		}
	GOTO       L_UART_SendNumber8
L_UART_SendNumber9:
;UART.c,209 :: 		while (i > 0)
L_UART_SendNumber10:
	MOVF       UART_SendNumber_i_L0+0, 0
	SUBLW      0
	BTFSC      STATUS+0, 0
	GOTO       L_UART_SendNumber11
;UART.c,211 :: 		i--;
	DECF       UART_SendNumber_i_L0+0, 1
;UART.c,212 :: 		UART_SendByte((u8)buffer[i]);
	MOVF       UART_SendNumber_i_L0+0, 0
	ADDLW      UART_SendNumber_buffer_L0+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,213 :: 		}
	GOTO       L_UART_SendNumber10
L_UART_SendNumber11:
;UART.c,214 :: 		}
L_end_UART_SendNumber:
	RETURN
; end of _UART_SendNumber

_UART_SendNewLine:

;UART.c,220 :: 		void UART_SendNewLine(void)
;UART.c,222 :: 		UART_SendByte(UART_CARRIAGE_RETURN);    // Send '\r'
	MOVLW      13
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,223 :: 		UART_SendByte(UART_NEWLINE);            // Send '\n'
	MOVLW      10
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,224 :: 		}
L_end_UART_SendNewLine:
	RETURN
; end of _UART_SendNewLine

_UART_ReceiveByte:

;UART.c,240 :: 		u8 UART_ReceiveByte(void)
;UART.c,246 :: 		while (!GET_BIT(PIR1, PIR1_RCIF))
L_UART_ReceiveByte12:
	MOVLW      5
	MOVWF      R0+0
	MOVF       12, 0
	MOVWF      R1+0
	MOVF       R0+0, 0
L__UART_ReceiveByte38:
	BTFSC      STATUS+0, 2
	GOTO       L__UART_ReceiveByte39
	RRF        R1+0, 1
	BCF        R1+0, 7
	ADDLW      255
	GOTO       L__UART_ReceiveByte38
L__UART_ReceiveByte39:
	BTFSC      R1+0, 0
	GOTO       L_UART_ReceiveByte13
;UART.c,249 :: 		}
	GOTO       L_UART_ReceiveByte12
L_UART_ReceiveByte13:
;UART.c,253 :: 		if (UART_CheckErrors() != UART_OK)
	CALL       _UART_CheckErrors+0
	MOVF       R0+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_UART_ReceiveByte14
;UART.c,256 :: 		UART_ClearErrors();
	CALL       _UART_ClearErrors+0
;UART.c,257 :: 		rxData = RCREG;   // Read to clear buffer
	MOVF       26, 0
	MOVWF      UART_ReceiveByte_rxData_L0+0
;UART.c,258 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_UART_ReceiveByte
;UART.c,259 :: 		}
L_UART_ReceiveByte14:
;UART.c,264 :: 		rxData = RCREG;
	MOVF       26, 0
	MOVWF      UART_ReceiveByte_rxData_L0+0
;UART.c,266 :: 		return rxData;
	MOVF       UART_ReceiveByte_rxData_L0+0, 0
	MOVWF      R0+0
;UART.c,267 :: 		}
L_end_UART_ReceiveByte:
	RETURN
; end of _UART_ReceiveByte

_UART_ReceiveChar:

;UART.c,273 :: 		char UART_ReceiveChar(void)
;UART.c,275 :: 		return (char)UART_ReceiveByte();
	CALL       _UART_ReceiveByte+0
;UART.c,276 :: 		}
L_end_UART_ReceiveChar:
	RETURN
; end of _UART_ReceiveChar

_UART_ReceiveString:

;UART.c,287 :: 		void UART_ReceiveString(char* buffer, u8 maxLength)
;UART.c,289 :: 		u8 i = 0;
	CLRF       UART_ReceiveString_i_L0+0
;UART.c,293 :: 		if (buffer == 0)
	MOVF       FARG_UART_ReceiveString_buffer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_UART_ReceiveString15
;UART.c,295 :: 		return;
	GOTO       L_end_UART_ReceiveString
;UART.c,296 :: 		}
L_UART_ReceiveString15:
;UART.c,299 :: 		while (i < (maxLength - 1))
L_UART_ReceiveString16:
	MOVLW      1
	SUBWF      FARG_UART_ReceiveString_maxLength+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	BTFSS      STATUS+0, 0
	DECF       R1+1, 1
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      R1+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__UART_ReceiveString42
	MOVF       R1+0, 0
	SUBWF      UART_ReceiveString_i_L0+0, 0
L__UART_ReceiveString42:
	BTFSC      STATUS+0, 0
	GOTO       L_UART_ReceiveString17
;UART.c,301 :: 		receivedChar = (char)UART_ReceiveByte();
	CALL       _UART_ReceiveByte+0
	MOVF       R0+0, 0
	MOVWF      UART_ReceiveString_receivedChar_L0+0
;UART.c,305 :: 		(receivedChar == UART_CARRIAGE_RETURN))
	MOVF       R0+0, 0
	XORLW      10
	BTFSC      STATUS+0, 2
	GOTO       L__UART_ReceiveString27
	MOVF       UART_ReceiveString_receivedChar_L0+0, 0
	XORLW      13
	BTFSC      STATUS+0, 2
	GOTO       L__UART_ReceiveString27
	GOTO       L_UART_ReceiveString20
L__UART_ReceiveString27:
;UART.c,307 :: 		break;
	GOTO       L_UART_ReceiveString17
;UART.c,308 :: 		}
L_UART_ReceiveString20:
;UART.c,311 :: 		buffer[i] = receivedChar;
	MOVF       UART_ReceiveString_i_L0+0, 0
	ADDWF      FARG_UART_ReceiveString_buffer+0, 0
	MOVWF      FSR
	MOVF       UART_ReceiveString_receivedChar_L0+0, 0
	MOVWF      INDF+0
;UART.c,312 :: 		i++;
	INCF       UART_ReceiveString_i_L0+0, 1
;UART.c,313 :: 		}
	GOTO       L_UART_ReceiveString16
L_UART_ReceiveString17:
;UART.c,316 :: 		buffer[i] = UART_NULL_CHAR;
	MOVF       UART_ReceiveString_i_L0+0, 0
	ADDWF      FARG_UART_ReceiveString_buffer+0, 0
	MOVWF      FSR
	CLRF       INDF+0
;UART.c,317 :: 		}
L_end_UART_ReceiveString:
	RETURN
; end of _UART_ReceiveString

_UART_DataReady:

;UART.c,329 :: 		u8 UART_DataReady(void)
;UART.c,332 :: 		return GET_BIT(PIR1, PIR1_RCIF);
	MOVLW      5
	MOVWF      R1+0
	MOVF       12, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__UART_DataReady44:
	BTFSC      STATUS+0, 2
	GOTO       L__UART_DataReady45
	RRF        R0+0, 1
	BCF        R0+0, 7
	ADDLW      255
	GOTO       L__UART_DataReady44
L__UART_DataReady45:
	MOVLW      1
	ANDWF      R0+0, 1
;UART.c,333 :: 		}
L_end_UART_DataReady:
	RETURN
; end of _UART_DataReady

_UART_TxReady:

;UART.c,341 :: 		u8 UART_TxReady(void)
;UART.c,345 :: 		return GET_BIT(TXSTA, TXSTA_TRMT);
	MOVF       152, 0
	MOVWF      R0+0
	RRF        R0+0, 1
	BCF        R0+0, 7
	MOVLW      1
	ANDWF      R0+0, 1
;UART.c,346 :: 		}
L_end_UART_TxReady:
	RETURN
; end of _UART_TxReady

_UART_CheckErrors:

;UART.c,363 :: 		u8 UART_CheckErrors(void)
;UART.c,367 :: 		if (GET_BIT(RCSTA, RCSTA_OERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_CheckErrors21
;UART.c,369 :: 		return UART_ERROR_OVERRUN;
	MOVLW      1
	MOVWF      R0+0
	GOTO       L_end_UART_CheckErrors
;UART.c,370 :: 		}
L_UART_CheckErrors21:
;UART.c,374 :: 		if (GET_BIT(RCSTA, RCSTA_FERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_CheckErrors22
;UART.c,376 :: 		return UART_ERROR_FRAMING;
	MOVLW      2
	MOVWF      R0+0
	GOTO       L_end_UART_CheckErrors
;UART.c,377 :: 		}
L_UART_CheckErrors22:
;UART.c,379 :: 		return UART_OK;
	CLRF       R0+0
;UART.c,380 :: 		}
L_end_UART_CheckErrors:
	RETURN
; end of _UART_CheckErrors

_UART_ClearErrors:

;UART.c,396 :: 		u8 UART_ClearErrors(void)
;UART.c,398 :: 		u8 errorCode = UART_OK;
	CLRF       UART_ClearErrors_errorCode_L0+0
;UART.c,402 :: 		if (GET_BIT(RCSTA, RCSTA_OERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_ClearErrors23
;UART.c,404 :: 		errorCode = UART_ERROR_OVERRUN;
	MOVLW      1
	MOVWF      UART_ClearErrors_errorCode_L0+0
;UART.c,407 :: 		CLR_BIT(RCSTA, RCSTA_CREN);     // Disable receiver
	BCF        24, 4
;UART.c,410 :: 		SET_BIT(RCSTA, RCSTA_CREN);     // Re-enable receiver
	BSF        24, 4
;UART.c,411 :: 		}
L_UART_ClearErrors23:
;UART.c,414 :: 		if (GET_BIT(RCSTA, RCSTA_FERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_ClearErrors24
;UART.c,416 :: 		errorCode = UART_ERROR_FRAMING;
	MOVLW      2
	MOVWF      UART_ClearErrors_errorCode_L0+0
;UART.c,420 :: 		}
L_UART_ClearErrors24:
;UART.c,425 :: 		return errorCode;
	MOVF       UART_ClearErrors_errorCode_L0+0, 0
	MOVWF      R0+0
;UART.c,426 :: 		}
L_end_UART_ClearErrors:
	RETURN
; end of _UART_ClearErrors

_UART_Flush:

;UART.c,436 :: 		void UART_Flush(void)
;UART.c,441 :: 		while (GET_BIT(PIR1, PIR1_RCIF))
L_UART_Flush25:
	MOVLW      5
	MOVWF      R0+0
	MOVF       12, 0
	MOVWF      R1+0
	MOVF       R0+0, 0
L__UART_Flush50:
	BTFSC      STATUS+0, 2
	GOTO       L__UART_Flush51
	RRF        R1+0, 1
	BCF        R1+0, 7
	ADDLW      255
	GOTO       L__UART_Flush50
L__UART_Flush51:
	BTFSS      R1+0, 0
	GOTO       L_UART_Flush26
;UART.c,444 :: 		}
	GOTO       L_UART_Flush25
L_UART_Flush26:
;UART.c,447 :: 		UART_ClearErrors();
	CALL       _UART_ClearErrors+0
;UART.c,451 :: 		}
L_end_UART_Flush:
	RETURN
; end of _UART_Flush
