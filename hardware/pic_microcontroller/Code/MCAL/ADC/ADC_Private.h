/*******************************************************************************
 * File:    ADC_Private.h
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Device:  PIC16F877A
 * Compiler: mikroC PRO for PIC
 *
 * Description:
 *     ADC Private Header - Contains register definitions, bit positions,
 *     and internal macros. DO NOT modify unless you know what you're doing.
 *
 * Notes:
 *     - Register addresses are from PIC16F877A datasheet
 *     - This file is for internal driver use only
 *     - Application code should NOT include this file directly
 ******************************************************************************/

#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\SERVICES\BIT_MATH.h"
#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\SERVICES\STD_TYPES.h"

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
//typedef unsigned char   u8;     // 8-bit unsigned integer
//typedef unsigned int    u16;    // 16-bit unsigned integer

/*******************************************************************************
 * ADC REGISTER ADDRESSES (PIC16F877A Memory Map)
 ******************************************************************************/

/* ADC Control Register 0 - Address: 0x1F (Bank 0) */
#define ADCON0_REG      (*((volatile u8*)0x1F))

/* ADC Control Register 1 - Address: 0x9F (Bank 1) */
#define ADCON1_REG      (*((volatile u8*)0x9F))

/* ADC Result High Register - Address: 0x1E (Bank 0) */
#define ADRESH_REG      (*((volatile u8*)0x1E))

/* ADC Result Low Register - Address: 0x9E (Bank 1) */
#define ADRESL_REG      (*((volatile u8*)0x9E))

/*******************************************************************************
 * ADCON0 REGISTER BIT DEFINITIONS (Address: 0x1F)
 *
 * Bit 7-6: ADCS1:ADCS0 - A/D Conversion Clock Select
 * Bit 5-3: CHS2:CHS0   - Analog Channel Select
 * Bit 2:   GO/DONE     - A/D Conversion Status
 * Bit 1:   Unimplemented
 * Bit 0:   ADON        - A/D Module Enable
 ******************************************************************************/

/* Bit Positions */
#define ADCS1       7   // ADC Clock Select bit 1
#define ADCS0       6   // ADC Clock Select bit 0
#define CHS2        5   // Channel Select bit 2
#define CHS1        4   // Channel Select bit 1
#define CHS0        3   // Channel Select bit 0
#define GO_DONE     2   // GO/DONE bit (start conversion / conversion status)
// Bit 1 is unimplemented
#define ADON        0   // ADC ON bit

/* Bit Masks */
#define ADCS_MASK       0xC0    // Bits 7-6: 1100 0000
#define CHS_MASK        0x38    // Bits 5-3: 0011 1000
#define GO_DONE_MASK    0x04    // Bit 2:    0000 0100
#define ADON_MASK       0x01    // Bit 0:    0000 0001

/*******************************************************************************
 * ADCON1 REGISTER BIT DEFINITIONS (Address: 0x9F)
 *
 * Bit 7:   ADFM         - Result Format Select
 * Bit 6-4: Unimplemented
 * Bit 3-0: PCFG3:PCFG0 - Port Configuration
 ******************************************************************************/

/* Bit Positions */
#define ADFM        7   // A/D Result Format Select
#define PCFG3       3   // Port Configuration bit 3
#define PCFG2       2   // Port Configuration bit 2
#define PCFG1       1   // Port Configuration bit 1
#define PCFG0       0   // Port Configuration bit 0

/* Bit Masks */
#define ADFM_MASK       0x80    // Bit 7:    1000 0000
#define PCFG_MASK       0x0F    // Bits 3-0: 0000 1111

/*******************************************************************************
 * HELPER MACROS FOR BIT MANIPULATION
 ******************************************************************************/

/* Set a bit in a register */
//#define SET_BIT(REG, BIT)       ((REG) |= (1 << (BIT)))

/* Clear a bit in a register */
//#define CLEAR_BIT(REG, BIT)     ((REG) &= ~(1 << (BIT)))

/* Toggle a bit in a register */
//#define TOGGLE_BIT(REG, BIT)    ((REG) ^= (1 << (BIT)))

/* Read a bit from a register */
//#define READ_BIT(REG, BIT)      (((REG) >> (BIT)) & 0x01)

/* Write multiple bits using mask */
#define WRITE_BITS(REG, MASK, VALUE)    ((REG) = ((REG) & ~(MASK)) | ((VALUE) & (MASK)))

/*******************************************************************************
 * CHANNEL SELECT VALUES (for ADCON0 CHS2:CHS0 bits)
 ******************************************************************************/
#define CHANNEL_0       0x00    // 000 - AN0 (RA0)
#define CHANNEL_1       0x01    // 001 - AN1 (RA1)
#define CHANNEL_2       0x02    // 010 - AN2 (RA2)
#define CHANNEL_3       0x03    // 011 - AN3 (RA3)
#define CHANNEL_4       0x04    // 100 - AN4 (RA5)
#define CHANNEL_5       0x05    // 101 - AN5 (RE0)
#define CHANNEL_6       0x06    // 110 - AN6 (RE1)
#define CHANNEL_7       0x07    // 111 - AN7 (RE2)

/*******************************************************************************
 * ADC CONVERSION PARAMETERS
 ******************************************************************************/
#define ADC_10BIT_MAX       1023    // Maximum 10-bit value (2^10 - 1)
#define ADC_CONVERSION_BITS 10      // ADC resolution in bits

#endif  // ADC_PRIVATE_H

/*******************************************************************************
 * END OF FILE
 ******************************************************************************/