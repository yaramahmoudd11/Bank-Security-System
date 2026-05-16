/******************************************************************************
 * File:    UART_Interface.h
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Description: UART Public Interface for PIC16F877A
 *              Contains all public function prototypes and user APIs
 * MCU:     PIC16F877A
 * Compiler: mikroC PRO for PIC
 ******************************************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "UART_Private.h"
#include "UART_Config.h"

/******************************************************************************
 *                      CORE UART FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Initializes the UART module with configured settings
 * @param  None
 * @retval None
 *
 * This function configures the UART module based on settings in UART_Config.h:
 * - Sets baud rate
 * - Configures asynchronous/synchronous mode
 * - Enables/disables transmitter and receiver
 * - Configures data bits (8 or 9 bit)
 * - Sets up interrupts if enabled
 */
void UART_Init(void);

/**
 * @brief  Sends a single byte via UART
 * @param  data: Byte to be transmitted
 * @retval None
 *
 * This function transmits one byte of data. It waits for the transmit
 * register to be empty before sending.
 */
void UART_SendByte(u8 txData);

/**
 * @brief  Receives a single byte via UART
 * @param  None
 * @retval Received byte
 *
 * This function waits for data to be available and then reads one byte
 * from the receive register. It's a blocking function.
 */
u8 UART_ReceiveByte(void);

/**
 * @brief  Sends a null-terminated string via UART
 * @param  str: Pointer to the string to be transmitted
 * @retval None
 *
 * This function transmits a complete string character by character
 * until the null terminator is encountered.
 */
void UART_SendString(const char* str);

/**
 * @brief  Receives a string via UART until newline or max length
 * @param  buffer: Pointer to buffer where received string will be stored
 * @param  maxLength: Maximum number of characters to receive
 * @retval None
 *
 * This function receives characters until a newline character is received
 * or the maximum buffer length is reached. The string is null-terminated.
 */
void UART_ReceiveString(char* buffer, u8 maxLength);

/**
 * @brief  Checks if data is available in receive buffer
 * @param  None
 * @retval 1 if data is ready, 0 otherwise
 *
 * This is a non-blocking function that checks the RCIF flag.
 */
u8 UART_DataReady(void);

/**
 * @brief  Checks if transmit buffer is empty
 * @param  None
 * @retval 1 if TX buffer is empty, 0 otherwise
 *
 * This function checks if the transmit shift register has completed
 * sending the last byte.
 */
u8 UART_TxReady(void);

/******************************************************************************
 *                      UTILITY FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Sends an unsigned integer as ASCII string via UART
 * @param  number: Integer to be sent (0-65535)
 * @retval None
 *
 * This function converts the number to ASCII and transmits it.
 */
void UART_SendNumber(u16 number);

/**
 * @brief  Sends a newline character (CR+LF) via UART
 * @param  None
 * @retval None
 *
 * This function sends both carriage return (\r) and line feed (\n).
 */
void UART_SendNewLine(void);

/**
 * @brief  Sends a single character via UART (alias for UART_SendByte)
 * @param  ch: Character to be transmitted
 * @retval None
 */
void UART_SendChar(char ch);

/**
 * @brief  Receives a single character via UART (alias for UART_ReceiveByte)
 * @param  None
 * @retval Received character
 */
char UART_ReceiveChar(void);

/******************************************************************************
 *                      ERROR HANDLING FUNCTIONS
 ******************************************************************************/

/**
 * @brief  Clears UART receive errors (overrun and framing errors)
 * @param  None
 * @retval Error code: UART_OK, UART_ERROR_OVERRUN, or UART_ERROR_FRAMING
 *
 * This function checks for errors and clears them by resetting CREN bit
 * if an overrun error is detected.
 */
u8 UART_ClearErrors(void);

/**
 * @brief  Checks for UART errors
 * @param  None
 * @retval Error code: UART_OK, UART_ERROR_OVERRUN, or UART_ERROR_FRAMING
 *
 * This function checks the error flags without clearing them.
 */
u8 UART_CheckErrors(void);

/******************************************************************************
 *                      ADVANCED FUNCTIONS (OPTIONAL)
 ******************************************************************************/

#if (UART_INTERRUPT_ENABLE == 1)
/**
 * @brief  Enables UART interrupts
 * @param  None
 * @retval None
 *
 * This function enables UART TX and/or RX interrupts based on configuration.
 */
void UART_EnableInterrupt(void);

/**
 * @brief  Disables UART interrupts
 * @param  None
 * @retval None
 *
 * This function disables UART TX and RX interrupts.
 */
void UART_DisableInterrupt(void);
#endif

/**
 * @brief  Flushes the receive buffer
 * @param  None
 * @retval None
 *
 * This function reads and discards all data in the receive buffer.
 */
void UART_Flush(void);

#endif /* UART_INTERFACE_H */