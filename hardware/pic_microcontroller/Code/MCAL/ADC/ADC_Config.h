/*******************************************************************************
 * File:    ADC_Config.h
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Device:  PIC16F877A
 * Compiler: mikroC PRO for PIC
 *
 * Description:
 *     ADC Configuration File - Contains all user-configurable settings for
 *     the ADC module. Modify these macros to customize ADC behavior.
 *
 * Notes:
 *     - This file contains ONLY configuration options
 *     - All settings are compile-time configurable
 *     - Fosc = 16MHz for this configuration
 ******************************************************************************/

#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/*******************************************************************************
 * ADC CLOCK CONFIGURATION
 *
 * Select ADC conversion clock based on device frequency (16MHz)
 * TAD must be >= 1.6탎 for correct conversion
 *
 * Options:
 *   ADC_FOSC_DIV_2   -> TAD = 2 * TOSC = 2 * 62.5ns = 125ns   (TOO FAST!)
 *   ADC_FOSC_DIV_8   -> TAD = 8 * TOSC = 8 * 62.5ns = 500ns   (TOO FAST!)
 *   ADC_FOSC_DIV_32  -> TAD = 32 * TOSC = 32 * 62.5ns = 2탎   (GOOD)
 *   ADC_RC_CLOCK     -> TAD = 2-6탎 (typical 4탎)             (GOOD)
 *
 * For 16MHz, use FOSC/32 or RC Clock
 ******************************************************************************/
#define ADC_CLOCK_SELECTION     ADC_FOSC_DIV_32     // 2탎 TAD @ 16MHz

/* ADC Clock Options */
#define ADC_FOSC_DIV_2          0x00    // ADCS1:ADCS0 = 00
#define ADC_FOSC_DIV_8          0x01    // ADCS1:ADCS0 = 01
#define ADC_FOSC_DIV_32         0x02    // ADCS1:ADCS0 = 10
#define ADC_RC_CLOCK            0x03    // ADCS1:ADCS0 = 11

/*******************************************************************************
 * ADC VOLTAGE REFERENCE CONFIGURATION
 *
 * Configure voltage reference sources for ADC conversions
 * VREF+ (high reference) and VREF- (low reference)
 ******************************************************************************/
#define ADC_VREF_CONFIG         ADC_VREF_VDD_VSS    // VDD and VSS references

/* Voltage Reference Options */
#define ADC_VREF_VDD_VSS        0x00    // VREF+ = VDD, VREF- = VSS (most common)
#define ADC_VREF_VDD_VREF       0x01    // VREF+ = VDD, VREF- = RA2/AN2/VREF-
#define ADC_VREF_VREFP_VSS      0x02    // VREF+ = RA3/AN3/VREF+, VREF- = VSS
#define ADC_VREF_VREFP_VREF     0x03    // VREF+ = RA3/AN3/VREF+, VREF- = RA2/AN2/VREF-

/*******************************************************************************
 * ADC RESULT JUSTIFICATION
 *
 * Configure how the 10-bit result is stored in the 16-bit register pair
 *
 * RIGHT JUSTIFIED: [ADRESH: 0000 00xx][ADRESL: xxxx xxxx]
 * LEFT JUSTIFIED:  [ADRESH: xxxx xxxx][ADRESL: xx00 0000]
 ******************************************************************************/
#define ADC_RESULT_FORMAT       ADC_RIGHT_JUSTIFIED

/* Result Format Options */
#define ADC_RIGHT_JUSTIFIED     0x01    // Right justified (most common for 10-bit)
#define ADC_LEFT_JUSTIFIED      0x00    // Left justified

/*******************************************************************************
 * ANALOG CHANNEL CONFIGURATION
 *
 * Configure which pins are analog inputs (A) and which are digital I/O (D)
 * PIC16F877A has 8 analog channels: AN0-AN7
 *
 * PCFG[3:0] bits determine the configuration
 * Example: 0x06 = All pins digital except AN0
 ******************************************************************************/
#define ADC_PORT_CONFIG         0x00    // All pins analog (PCFG3:PCFG0 = 0000)

/* Common Port Configurations */
#define ADC_ALL_ANALOG          0x00    // AN0-AN7 all analog, VREF+ = VDD, VREF- = VSS
#define ADC_AN0_TO_AN4_ANALOG   0x04    // AN0-AN4 analog, AN5-AN7 digital
#define ADC_AN0_TO_AN2_ANALOG   0x02    // AN0-AN2 analog, rest digital
#define ADC_ALL_DIGITAL         0x06    // All digital I/O

/*******************************************************************************
 * ADC ACQUISITION TIME CONFIGURATION
 *
 * Minimum acquisition time after channel selection before starting conversion
 * Based on datasheet equation: TACQ = TAMP + TC + TCOFF
 *
 * At 16MHz with Fosc/32: Typical TACQ ~20탎 for Rs = 10k?
 * Delay value is implementation-dependent (use delay_us() in code)
 ******************************************************************************/
#define ADC_ACQUISITION_DELAY_US    20  // Acquisition delay in microseconds

#endif  // ADC_CONFIG_H

/*******************************************************************************
 * END OF FILE
 ******************************************************************************/