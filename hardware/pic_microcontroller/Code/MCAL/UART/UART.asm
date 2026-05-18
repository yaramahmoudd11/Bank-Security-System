
_UART_Init:

;UART.c,32 :: 		void UART_Init(void)
;UART.c,35 :: 		CLR_BIT(TRISC, TRISC_TX);           // RC6/TX output
	MOVLW      191
	ANDWF      135, 1
;UART.c,36 :: 		SET_BIT(TRISC, TRISC_RX);           // RC7/RX input
	BSF        135, 7
;UART.c,39 :: 		CLR_BIT(RCSTA, RCSTA_SPEN);
	MOVLW      127
	ANDWF      24, 1
;UART.c,44 :: 		SPBRG = (u8)UART_SPBRG_VALUE;
	MOVLW      103
	MOVWF      153
;UART.c,48 :: 		TXSTA = 0x00;
	CLRF       152
;UART.c,52 :: 		CLR_BIT(TXSTA, TXSTA_SYNC);     // Asynchronous mode
	MOVLW      239
	ANDWF      152, 1
;UART.c,60 :: 		SET_BIT(TXSTA, TXSTA_BRGH);     // High speed mode
	BSF        152, 2
;UART.c,69 :: 		CLR_BIT(TXSTA, TXSTA_TX9);      // 8-bit transmission
	MOVLW      191
	ANDWF      152, 1
;UART.c,74 :: 		SET_BIT(TXSTA, TXSTA_TXEN);     // Enable transmitter
	BSF        152, 5
;UART.c,81 :: 		RCSTA = 0x00;
	CLRF       24
;UART.c,87 :: 		CLR_BIT(RCSTA, RCSTA_RX9);      // 8-bit reception
	MOVLW      191
	ANDWF      24, 1
;UART.c,93 :: 		SET_BIT(RCSTA, RCSTA_CREN); // Enable continuous receive
	BSF        24, 4
;UART.c,100 :: 		SET_BIT(RCSTA, RCSTA_SPEN);         // Serial port enabled
	BSF        24, 7
;UART.c,103 :: 		UART_ClearErrors();
	CALL       _UART_ClearErrors+0
;UART.c,111 :: 		Delay_ms(10);
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
;UART.c,112 :: 		}
L_end_UART_Init:
	RETURN
; end of _UART_Init

_UART_SendByte:

;UART.c,127 :: 		void UART_SendByte(u8 txData)
;UART.c,131 :: 		while (!GET_BIT(PIR1, PIR1_TXIF))
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
;UART.c,134 :: 		}
	GOTO       L_UART_SendByte1
L_UART_SendByte2:
;UART.c,138 :: 		TXREG = txData;
	MOVF       FARG_UART_SendByte_txData+0, 0
	MOVWF      25
;UART.c,139 :: 		}
L_end_UART_SendByte:
	RETURN
; end of _UART_SendByte

_UART_SendChar:

;UART.c,145 :: 		void UART_SendChar(char ch)
;UART.c,147 :: 		UART_SendByte((u8)ch);
	MOVF       FARG_UART_SendChar_ch+0, 0
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,148 :: 		}
L_end_UART_SendChar:
	RETURN
; end of _UART_SendChar

_UART_SendString:

;UART.c,158 :: 		void UART_SendString(const char* str)
;UART.c,160 :: 		u8 i = 0;
	CLRF       UART_SendString_i_L0+0
;UART.c,163 :: 		if (str == 0)
	MOVLW      0
	XORWF      FARG_UART_SendString_str+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__UART_SendString32
	MOVLW      0
	XORWF      FARG_UART_SendString_str+0, 0
L__UART_SendString32:
	BTFSS      STATUS+0, 2
	GOTO       L_UART_SendString3
;UART.c,165 :: 		return;
	GOTO       L_end_UART_SendString
;UART.c,166 :: 		}
L_UART_SendString3:
;UART.c,169 :: 		while (str[i] != UART_NULL_CHAR)
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
;UART.c,171 :: 		UART_SendByte((u8)str[i]);
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
;UART.c,172 :: 		i++;
	INCF       UART_SendString_i_L0+0, 1
;UART.c,175 :: 		if (i >= 255)
	MOVLW      255
	SUBWF      UART_SendString_i_L0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_UART_SendString6
;UART.c,177 :: 		break;
	GOTO       L_UART_SendString5
;UART.c,178 :: 		}
L_UART_SendString6:
;UART.c,179 :: 		}
	GOTO       L_UART_SendString4
L_UART_SendString5:
;UART.c,180 :: 		}
L_end_UART_SendString:
	RETURN
; end of _UART_SendString

_UART_SendNumber:

;UART.c,192 :: 		void UART_SendNumber(u16 number)
;UART.c,195 :: 		u8 i = 0;
	CLRF       UART_SendNumber_i_L0+0
;UART.c,198 :: 		if (number == 0)
	MOVF       FARG_UART_SendNumber_number+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_UART_SendNumber7
;UART.c,200 :: 		UART_SendByte('0');
	MOVLW      48
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,201 :: 		return;
	GOTO       L_end_UART_SendNumber
;UART.c,202 :: 		}
L_UART_SendNumber7:
;UART.c,205 :: 		while (number > 0)
L_UART_SendNumber8:
	MOVF       FARG_UART_SendNumber_number+0, 0
	SUBLW      0
	BTFSC      STATUS+0, 0
	GOTO       L_UART_SendNumber9
;UART.c,207 :: 		buffer[i] = (number % 10) + '0';    // Convert digit to ASCII
	MOVF       UART_SendNumber_i_L0+0, 0
	ADDLW      UART_SendNumber_buffer_L0+0
	MOVWF      FLOC__UART_SendNumber+0
	MOVLW      10
	MOVWF      R4+0
	MOVF       FARG_UART_SendNumber_number+0, 0
	MOVWF      R0+0
	CALL       _Div_8X8_U+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVLW      48
	ADDWF      R0+0, 1
	MOVF       FLOC__UART_SendNumber+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
;UART.c,208 :: 		number = number / 10;
	MOVLW      10
	MOVWF      R4+0
	MOVF       FARG_UART_SendNumber_number+0, 0
	MOVWF      R0+0
	CALL       _Div_8X8_U+0
	MOVF       R0+0, 0
	MOVWF      FARG_UART_SendNumber_number+0
;UART.c,209 :: 		i++;
	INCF       UART_SendNumber_i_L0+0, 1
;UART.c,210 :: 		}
	GOTO       L_UART_SendNumber8
L_UART_SendNumber9:
;UART.c,213 :: 		while (i > 0)
L_UART_SendNumber10:
	MOVF       UART_SendNumber_i_L0+0, 0
	SUBLW      0
	BTFSC      STATUS+0, 0
	GOTO       L_UART_SendNumber11
;UART.c,215 :: 		i--;
	DECF       UART_SendNumber_i_L0+0, 1
;UART.c,216 :: 		UART_SendByte((u8)buffer[i]);
	MOVF       UART_SendNumber_i_L0+0, 0
	ADDLW      UART_SendNumber_buffer_L0+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,217 :: 		}
	GOTO       L_UART_SendNumber10
L_UART_SendNumber11:
;UART.c,218 :: 		}
L_end_UART_SendNumber:
	RETURN
; end of _UART_SendNumber

_UART_SendNewLine:

;UART.c,224 :: 		void UART_SendNewLine(void)
;UART.c,226 :: 		UART_SendByte(UART_CARRIAGE_RETURN);    // Send '\r'
	MOVLW      13
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,227 :: 		UART_SendByte(UART_NEWLINE);            // Send '\n'
	MOVLW      10
	MOVWF      FARG_UART_SendByte_txData+0
	CALL       _UART_SendByte+0
;UART.c,228 :: 		}
L_end_UART_SendNewLine:
	RETURN
; end of _UART_SendNewLine

_UART_ReceiveByte:

;UART.c,244 :: 		u8 UART_ReceiveByte(void)
;UART.c,250 :: 		while (!GET_BIT(PIR1, PIR1_RCIF))
L_UART_ReceiveByte12:
	MOVLW      5
	MOVWF      R0+0
	MOVF       12, 0
	MOVWF      R1+0
	MOVF       R0+0, 0
L__UART_ReceiveByte36:
	BTFSC      STATUS+0, 2
	GOTO       L__UART_ReceiveByte37
	RRF        R1+0, 1
	BCF        R1+0, 7
	ADDLW      255
	GOTO       L__UART_ReceiveByte36
L__UART_ReceiveByte37:
	BTFSC      R1+0, 0
	GOTO       L_UART_ReceiveByte13
;UART.c,253 :: 		}
	GOTO       L_UART_ReceiveByte12
L_UART_ReceiveByte13:
;UART.c,257 :: 		if (UART_CheckErrors() != UART_OK)
	CALL       _UART_CheckErrors+0
	MOVF       R0+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_UART_ReceiveByte14
;UART.c,260 :: 		UART_ClearErrors();
	CALL       _UART_ClearErrors+0
;UART.c,261 :: 		rxData = RCREG;   // Read to clear buffer
	MOVF       26, 0
	MOVWF      UART_ReceiveByte_rxData_L0+0
;UART.c,262 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_UART_ReceiveByte
;UART.c,263 :: 		}
L_UART_ReceiveByte14:
;UART.c,268 :: 		rxData = RCREG;
	MOVF       26, 0
	MOVWF      UART_ReceiveByte_rxData_L0+0
;UART.c,270 :: 		return rxData;
	MOVF       UART_ReceiveByte_rxData_L0+0, 0
	MOVWF      R0+0
;UART.c,271 :: 		}
L_end_UART_ReceiveByte:
	RETURN
; end of _UART_ReceiveByte

_UART_ReceiveChar:

;UART.c,277 :: 		char UART_ReceiveChar(void)
;UART.c,279 :: 		return (char)UART_ReceiveByte();
	CALL       _UART_ReceiveByte+0
;UART.c,280 :: 		}
L_end_UART_ReceiveChar:
	RETURN
; end of _UART_ReceiveChar

_UART_ReceiveString:

;UART.c,291 :: 		void UART_ReceiveString(char* buffer, u8 maxLength)
;UART.c,293 :: 		u8 i = 0;
	CLRF       UART_ReceiveString_i_L0+0
;UART.c,297 :: 		if (buffer == 0)
	MOVF       FARG_UART_ReceiveString_buffer+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_UART_ReceiveString15
;UART.c,299 :: 		return;
	GOTO       L_end_UART_ReceiveString
;UART.c,300 :: 		}
L_UART_ReceiveString15:
;UART.c,303 :: 		while (i < (maxLength - 1))
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
	GOTO       L__UART_ReceiveString40
	MOVF       R1+0, 0
	SUBWF      UART_ReceiveString_i_L0+0, 0
L__UART_ReceiveString40:
	BTFSC      STATUS+0, 0
	GOTO       L_UART_ReceiveString17
;UART.c,305 :: 		receivedChar = (char)UART_ReceiveByte();
	CALL       _UART_ReceiveByte+0
	MOVF       R0+0, 0
	MOVWF      UART_ReceiveString_receivedChar_L0+0
;UART.c,309 :: 		(receivedChar == UART_CARRIAGE_RETURN))
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
;UART.c,311 :: 		break;
	GOTO       L_UART_ReceiveString17
;UART.c,312 :: 		}
L_UART_ReceiveString20:
;UART.c,315 :: 		buffer[i] = receivedChar;
	MOVF       UART_ReceiveString_i_L0+0, 0
	ADDWF      FARG_UART_ReceiveString_buffer+0, 0
	MOVWF      FSR
	MOVF       UART_ReceiveString_receivedChar_L0+0, 0
	MOVWF      INDF+0
;UART.c,316 :: 		i++;
	INCF       UART_ReceiveString_i_L0+0, 1
;UART.c,317 :: 		}
	GOTO       L_UART_ReceiveString16
L_UART_ReceiveString17:
;UART.c,320 :: 		buffer[i] = UART_NULL_CHAR;
	MOVF       UART_ReceiveString_i_L0+0, 0
	ADDWF      FARG_UART_ReceiveString_buffer+0, 0
	MOVWF      FSR
	CLRF       INDF+0
;UART.c,321 :: 		}
L_end_UART_ReceiveString:
	RETURN
; end of _UART_ReceiveString

_UART_DataReady:

;UART.c,333 :: 		u8 UART_DataReady(void)
;UART.c,336 :: 		return GET_BIT(PIR1, PIR1_RCIF);
	MOVLW      5
	MOVWF      R1+0
	MOVF       12, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__UART_DataReady42:
	BTFSC      STATUS+0, 2
	GOTO       L__UART_DataReady43
	RRF        R0+0, 1
	BCF        R0+0, 7
	ADDLW      255
	GOTO       L__UART_DataReady42
L__UART_DataReady43:
	MOVLW      1
	ANDWF      R0+0, 1
;UART.c,337 :: 		}
L_end_UART_DataReady:
	RETURN
; end of _UART_DataReady

_UART_TxReady:

;UART.c,345 :: 		u8 UART_TxReady(void)
;UART.c,349 :: 		return GET_BIT(TXSTA, TXSTA_TRMT);
	MOVF       152, 0
	MOVWF      R0+0
	RRF        R0+0, 1
	BCF        R0+0, 7
	MOVLW      1
	ANDWF      R0+0, 1
;UART.c,350 :: 		}
L_end_UART_TxReady:
	RETURN
; end of _UART_TxReady

_UART_CheckErrors:

;UART.c,367 :: 		u8 UART_CheckErrors(void)
;UART.c,371 :: 		if (GET_BIT(RCSTA, RCSTA_OERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_CheckErrors21
;UART.c,373 :: 		return UART_ERROR_OVERRUN;
	MOVLW      1
	MOVWF      R0+0
	GOTO       L_end_UART_CheckErrors
;UART.c,374 :: 		}
L_UART_CheckErrors21:
;UART.c,378 :: 		if (GET_BIT(RCSTA, RCSTA_FERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_CheckErrors22
;UART.c,380 :: 		return UART_ERROR_FRAMING;
	MOVLW      2
	MOVWF      R0+0
	GOTO       L_end_UART_CheckErrors
;UART.c,381 :: 		}
L_UART_CheckErrors22:
;UART.c,383 :: 		return UART_OK;
	CLRF       R0+0
;UART.c,384 :: 		}
L_end_UART_CheckErrors:
	RETURN
; end of _UART_CheckErrors

_UART_ClearErrors:

;UART.c,400 :: 		u8 UART_ClearErrors(void)
;UART.c,402 :: 		u8 errorCode = UART_OK;
	CLRF       UART_ClearErrors_errorCode_L0+0
;UART.c,406 :: 		if (GET_BIT(RCSTA, RCSTA_OERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_ClearErrors23
;UART.c,408 :: 		errorCode = UART_ERROR_OVERRUN;
	MOVLW      1
	MOVWF      UART_ClearErrors_errorCode_L0+0
;UART.c,411 :: 		CLR_BIT(RCSTA, RCSTA_CREN);     // Disable receiver
	MOVLW      239
	ANDWF      24, 1
;UART.c,414 :: 		SET_BIT(RCSTA, RCSTA_CREN);     // Re-enable receiver
	BSF        24, 4
;UART.c,415 :: 		}
L_UART_ClearErrors23:
;UART.c,418 :: 		if (GET_BIT(RCSTA, RCSTA_FERR))
	MOVF       24, 0
	MOVWF      R1+0
	RRF        R1+0, 1
	BCF        R1+0, 7
	RRF        R1+0, 1
	BCF        R1+0, 7
	BTFSS      R1+0, 0
	GOTO       L_UART_ClearErrors24
;UART.c,420 :: 		errorCode = UART_ERROR_FRAMING;
	MOVLW      2
	MOVWF      UART_ClearErrors_errorCode_L0+0
;UART.c,424 :: 		}
L_UART_ClearErrors24:
;UART.c,429 :: 		return errorCode;
	MOVF       UART_ClearErrors_errorCode_L0+0, 0
	MOVWF      R0+0
;UART.c,430 :: 		}
L_end_UART_ClearErrors:
	RETURN
; end of _UART_ClearErrors

_UART_Flush:

;UART.c,440 :: 		void UART_Flush(void)
;UART.c,445 :: 		while (GET_BIT(PIR1, PIR1_RCIF))
L_UART_Flush25:
	MOVLW      5
	MOVWF      R0+0
	MOVF       12, 0
	MOVWF      R1+0
	MOVF       R0+0, 0
L__UART_Flush48:
	BTFSC      STATUS+0, 2
	GOTO       L__UART_Flush49
	RRF        R1+0, 1
	BCF        R1+0, 7
	ADDLW      255
	GOTO       L__UART_Flush48
L__UART_Flush49:
	BTFSS      R1+0, 0
	GOTO       L_UART_Flush26
;UART.c,448 :: 		}
	GOTO       L_UART_Flush25
L_UART_Flush26:
;UART.c,451 :: 		UART_ClearErrors();
	CALL       _UART_ClearErrors+0
;UART.c,455 :: 		}
L_end_UART_Flush:
	RETURN
; end of _UART_Flush
