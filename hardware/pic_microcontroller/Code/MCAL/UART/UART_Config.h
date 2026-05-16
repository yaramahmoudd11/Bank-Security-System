/******************************************************************************
 * File:    UART_Config.h
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Description: UART Configuration File for PIC16F877A
 *              Contains all user-configurable settings for UART driver
 * MCU:     PIC16F877A
 * Clock:   16MHz Crystal Oscillator
 * Compiler: mikroC PRO for PIC
 ******************************************************************************/

#ifndef UART_CONFIG_H
#define UART_CONFIG_H

/******************************************************************************
 *                      SYSTEM CONFIGURATION
 ******************************************************************************/
#define F_CPU                   16000000UL      // 16MHz system clock

/******************************************************************************
 *                      BAUD RATE CONFIGURATION
 ******************************************************************************/
/*
 * Common Baud Rates for 16MHz:
 * 9600   -> SPBRG = 25  (BRGH = 1, Error = 0.16%)
 * 19200  -> SPBRG = 12  (BRGH = 1, Error = 0.16%)
 * 38400  -> SPBRG = 25  (BRGH = 0, Error = 0.16%)
 * 57600  -> SPBRG = 3   (BRGH = 1, Error = 0%)
 * 115200 -> SPBRG = 8   (BRGH = 0, Error = 3.55%)
 */
#define UART_BAUD_RATE          9600            // Default baud rate

/******************************************************************************
 *                      UART MODE CONFIGURATION
 ******************************************************************************/
/* UART Communication Mode */
#define UART_MODE_ASYNC         0               // Asynchronous mode
#define UART_MODE_SYNC          1               // Synchronous mode
#define UART_MODE               UART_MODE_ASYNC // Selected mode

/* Baud Rate Speed Selection */
#define UART_SPEED_LOW          0               // Low speed (BRGH = 0)
#define UART_SPEED_HIGH         1               // High speed (BRGH = 1)
#define UART_SPEED              UART_SPEED_HIGH // Selected speed

/******************************************************************************
 *                      TRANSMISSION CONFIGURATION
 ******************************************************************************/
/* Transmitter Enable/Disable */
#define UART_TX_ENABLE          1               // 1 = Enable TX, 0 = Disable
#define UART_TX_DISABLE         0

/* Receiver Enable/Disable */
#define UART_RX_ENABLE          1               // 1 = Enable RX, 0 = Disable
#define UART_RX_DISABLE         0

/* Data Bits Configuration */
#define UART_DATA_BITS_8        0               // 8-bit transmission
#define UART_DATA_BITS_9        1               // 9-bit transmission
#define UART_DATA_BITS          UART_DATA_BITS_8

/******************************************************************************
 *                      INTERRUPT CONFIGURATION
 ******************************************************************************/
/* UART Interrupt Enable/Disable */
#define UART_INTERRUPT_ENABLE   0               // 1 = Enable, 0 = Disable
#define UART_INTERRUPT_DISABLE  0

/* TX Interrupt Enable */
#define UART_TX_INT_ENABLE      0               // 1 = Enable TX interrupt

/* RX Interrupt Enable */
#define UART_RX_INT_ENABLE      0               // 1 = Enable RX interrupt

/******************************************************************************
 *                      RECEIVE MODE CONFIGURATION
 ******************************************************************************/
/* Continuous Receive Mode */
#define UART_CONT_RX_ENABLE     1               // 1 = Continuous receive mode
#define UART_CONT_RX_DISABLE    0

/******************************************************************************
 *                      ERROR HANDLING CONFIGURATION
 ******************************************************************************/
/* Enable Error Detection and Recovery */
#define UART_ERROR_DETECT       1               // 1 = Enable error detection
#define UART_AUTO_RECOVERY      1               // 1 = Auto recover from errors

/******************************************************************************
 *                      BUFFER CONFIGURATION
 ******************************************************************************/
/* String Buffer Size */
#define UART_STRING_BUFFER_SIZE 64              // Maximum string length

/******************************************************************************
 *                      PIN CONFIGURATION
 ******************************************************************************/
/* UART uses RC6 (TX) and RC7 (RX) pins - configured automatically by SPEN bit */

/******************************************************************************
 *                      CALCULATED VALUES (DO NOT MODIFY)
 ******************************************************************************/
/* Calculate SPBRG value based on baud rate and mode */
#if (UART_MODE == UART_MODE_ASYNC)
    #if (UART_SPEED == UART_SPEED_HIGH)
        /* Asynchronous High Speed: SPBRG = (Fosc/(16*BaudRate)) - 1 */
        #define UART_SPBRG_VALUE    ((F_CPU/(16UL*UART_BAUD_RATE))-1)
    #else
        /* Asynchronous Low Speed: SPBRG = (Fosc/(64*BaudRate)) - 1 */
        #define UART_SPBRG_VALUE    ((F_CPU/(64UL*UART_BAUD_RATE))-1)
    #endif
#else
    /* Synchronous Mode: SPBRG = (Fosc/(4*BaudRate)) - 1 */
    #define UART_SPBRG_VALUE        ((F_CPU/(4UL*UART_BAUD_RATE))-1)
#endif

#endif /* UART_CONFIG_H */