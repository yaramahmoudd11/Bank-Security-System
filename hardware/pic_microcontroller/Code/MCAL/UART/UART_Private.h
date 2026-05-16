/******************************************************************************
 * File:    UART_Private.h
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Description: UART Private Definitions for PIC16F877A
 *              Contains register addresses, bit positions, and internal macros
 * MCU:     PIC16F877A
 * Compiler: mikroC PRO for PIC
 *
 * IMPORTANT: This file should NOT be modified by users
 ******************************************************************************/

#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#include "../../SERVICES/STD_TYPES.h"
#include "../../SERVICES/BIT_MATH.h"

/******************************************************************************
 *                      UART REGISTER ADDRESSES
 ******************************************************************************/
/* UART Data Registers */
#define TXREG               (*((volatile u8*)0x19))     // Transmit Register
#define RCREG               (*((volatile u8*)0x1A))     // Receive Register
#define SPBRG               (*((volatile u8*)0x99))     // Baud Rate Generator

/* UART Control and Status Registers */
#define TXSTA               (*((volatile u8*)0x98))     // Transmit Status and Control
#define RCSTA               (*((volatile u8*)0x18))     // Receive Status and Control

/* Interrupt Registers */
#define PIR1                (*((volatile u8*)0x0C))     // Peripheral Interrupt Request 1
#define PIE1                (*((volatile u8*)0x8C))     // Peripheral Interrupt Enable 1
#define INTCON              (*((volatile u8*)0x0B))     // Interrupt Control Register

/* TRIS Registers for Pin Configuration */
#define TRISC               (*((volatile u8*)0x87))     // PORTC Direction Register

/******************************************************************************
 *                      TXSTA REGISTER BIT POSITIONS
 ******************************************************************************/
#define TXSTA_CSRC          7       // Clock Source Select bit
#define TXSTA_TX9           6       // 9-bit Transmit Enable bit
#define TXSTA_TXEN          5       // Transmit Enable bit
#define TXSTA_SYNC          4       // UART Mode Select bit
#define TXSTA_BRGH          2       // High Baud Rate Select bit
#define TXSTA_TRMT          1       // Transmit Shift Register Status bit
#define TXSTA_TX9D          0       // 9th bit of Transmit Data

/******************************************************************************
 *                      RCSTA REGISTER BIT POSITIONS
 ******************************************************************************/
#define RCSTA_SPEN          7       // Serial Port Enable bit
#define RCSTA_RX9           6       // 9-bit Receive Enable bit
#define RCSTA_SREN          5       // Single Receive Enable bit
#define RCSTA_CREN          4       // Continuous Receive Enable bit
#define RCSTA_ADDEN         3       // Address Detect Enable bit
#define RCSTA_FERR          2       // Framing Error bit
#define RCSTA_OERR          1       // Overrun Error bit
#define RCSTA_RX9D          0       // 9th bit of Received Data

/******************************************************************************
 *                      PIR1 REGISTER BIT POSITIONS
 ******************************************************************************/
#define PIR1_TXIF           4       // UART Transmit Interrupt Flag
#define PIR1_RCIF           5       // UART Receive Interrupt Flag

/******************************************************************************
 *                      PIE1 REGISTER BIT POSITIONS
 ******************************************************************************/
#define PIE1_TXIE           4       // UART Transmit Interrupt Enable
#define PIE1_RCIE           5       // UART Receive Interrupt Enable

/******************************************************************************
 *                      INTCON REGISTER BIT POSITIONS
 ******************************************************************************/
#define INTCON_GIE          7       // Global Interrupt Enable
#define INTCON_PEIE         6       // Peripheral Interrupt Enable

/******************************************************************************
 *                      TRISC REGISTER BIT POSITIONS
 ******************************************************************************/
#define TRISC_TX            6       // RC6/TX pin direction (output when 0)
#define TRISC_RX            7       // RC7/RX pin direction (input when 1)

/******************************************************************************
 *                      UART STATUS MACROS
 ******************************************************************************/
/* Check if transmit register is empty */
#define UART_TX_READY()         (GET_BIT(PIR1, PIR1_TXIF))

/* Check if transmit shift register is empty */
#define UART_TX_COMPLETE()      (GET_BIT(TXSTA, TXSTA_TRMT))

/* Check if receive data is available */
#define UART_RX_AVAILABLE()     (GET_BIT(PIR1, PIR1_RCIF))

/* Check for framing error */
#define UART_FRAMING_ERROR()    (GET_BIT(RCSTA, RCSTA_FERR))

/* Check for overrun error */
#define UART_OVERRUN_ERROR()    (GET_BIT(RCSTA, RCSTA_OERR))

/******************************************************************************
 *                      ERROR CODES
 ******************************************************************************/
#define UART_OK                 0
#define UART_ERROR_OVERRUN      1
#define UART_ERROR_FRAMING      2
#define UART_ERROR_TIMEOUT      3

/******************************************************************************
 *                      SPECIAL CHARACTERS
 ******************************************************************************/
#define UART_NULL_CHAR          '\0'
#define UART_NEWLINE            '\n'
#define UART_CARRIAGE_RETURN    '\r'

#endif /* UART_PRIVATE_H */