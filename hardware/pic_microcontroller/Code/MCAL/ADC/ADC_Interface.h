/*******************************************************************************
 * File:    ADC_Interface.h
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Device:  PIC16F877A
 * Compiler: mikroC PRO for PIC
 *
 * Description:
 *     ADC Public Interface - Contains all public function prototypes,
 *     enumerations, and definitions for application use.
 *
 * Usage Example:
 *     #include "ADC_Interface.h"
 *
 *     void main() {
 *         u16 adc_value;
 *         ADC_Init();                      // Initialize ADC
 *         adc_value = ADC_ReadChannel(2);  // Read from AN2
 *     }
 ******************************************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "ADC_Private.h"    // For data types (u8, u16)

/*******************************************************************************
 * CHANNEL ENUMERATION
 *
 * Enumeration for ADC channel selection (more readable than using numbers)
 ******************************************************************************/
typedef enum {
    ADC_CHANNEL_0 = 0,  // AN0 - RA0
    ADC_CHANNEL_1 = 1,  // AN1 - RA1
    ADC_CHANNEL_2 = 2,  // AN2 - RA2/VREF-
    ADC_CHANNEL_3 = 3,  // AN3 - RA3/VREF+
    ADC_CHANNEL_4 = 4,  // AN4 - RA5
    ADC_CHANNEL_5 = 5,  // AN5 - RE0
    ADC_CHANNEL_6 = 6,  // AN6 - RE1
    ADC_CHANNEL_7 = 7   // AN7 - RE2
} ADC_Channel_t;

/*******************************************************************************
 * RETURN STATUS ENUMERATION
 ******************************************************************************/
typedef enum {
    ADC_OK = 0,         // Operation successful
    ADC_ERROR = 1       // Operation failed
} ADC_Status_t;

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES
 ******************************************************************************/

/**
 * @brief  Initialize the ADC module
 *
 * @details Configures ADC based on settings in ADC_Config.h:
 *          - Sets conversion clock
 *          - Configures voltage references
 *          - Sets result justification
 *          - Configures analog/digital pins
 *          - Enables ADC module
 *
 * @param  None
 * @return None
 *
 * @note   Must be called before any other ADC function
 * @note   Ensure TRIS bits are set appropriately for analog inputs
 */
void ADC_Init(void);

/**
 * @brief  Enable the ADC module
 *
 * @details Turns on the ADC module by setting the ADON bit
 *
 * @param  None
 * @return None
 */
void ADC_Enable(void);

/**
 * @brief  Disable the ADC module
 *
 * @details Turns off the ADC module to save power by clearing the ADON bit
 *
 * @param  None
 * @return None
 */
void ADC_Disable(void);

/**
 * @brief  Select ADC input channel
 *
 * @details Changes the active ADC channel without starting a conversion
 *          Allows acquisition time before reading
 *
 * @param  channel: Channel number (0-7) or use ADC_CHANNEL_x enum
 * @return None
 *
 * @note   After changing channel, wait for acquisition time before conversion
 */
void ADC_SelectChannel(u8 channel);

/**
 * @brief  Start ADC conversion
 *
 * @details Begins A/D conversion by setting the GO/DONE bit
 *
 * @param  None
 * @return None
 *
 * @note   Ensure acquisition time has elapsed before calling this
 * @note   Use ADC_IsConversionDone() to check completion
 */
void ADC_StartConversion(void);

/**
 * @brief  Check if ADC conversion is complete
 *
 * @details Polls the GO/DONE bit to determine conversion status
 *
 * @param  None
 * @return 1 if conversion is complete, 0 if still in progress
 */
u8 ADC_IsConversionDone(void);

/**
 * @brief  Read 10-bit ADC result
 *
 * @details Reads the conversion result from ADRESH:ADRESL
 *          Handles both left and right justification automatically
 *
 * @param  None
 * @return 10-bit ADC result (0-1023)
 *
 * @note   Should only be called after conversion is complete
 */
u16 ADC_ReadResult(void);

/**
 * @brief  Read ADC value from specified channel (Blocking)
 *
 * @details Complete ADC read sequence:
 *          1. Select channel
 *          2. Wait for acquisition
 *          3. Start conversion
 *          4. Wait for completion
 *          5. Read and return result
 *
 * @param  channel: Channel number (0-7) or use ADC_CHANNEL_x enum
 * @return 10-bit ADC result (0-1023)
 *
 * @note   This is a blocking function (waits for conversion)
 * @note   Most commonly used function for simple ADC reads
 */
u16 ADC_ReadChannel(u8 channel);

/**
 * @brief  Read ADC value from specified channel (Non-blocking start)
 *
 * @details Starts conversion without waiting. User must poll completion.
 *          1. Select channel
 *          2. Wait for acquisition
 *          3. Start conversion
 *          4. Return immediately
 *
 * @param  channel: Channel number (0-7)
 * @return None
 *
 * @note   Use with ADC_IsConversionDone() and ADC_ReadResult()
 * @note   Useful for multitasking applications
 */
void ADC_StartChannelConversion(u8 channel);

/**
 * @brief  Convert ADC reading to voltage (in millivolts)
 *
 * @details Converts 10-bit ADC value to voltage based on VREF
 *          Voltage (mV) = (ADC_Value * VREF_mV) / 1024
 *
 * @param  adc_value: 10-bit ADC reading (0-1023)
 * @param  vref_mv: Reference voltage in millivolts (e.g., 5000 for 5V)
 * @return Voltage in millivolts
 *
 * @note   Example: If VDD = 5V, use vref_mv = 5000
 */
u16 ADC_ConvertToVoltage(u16 adc_value, u16 vref_mv);

#endif  // ADC_INTERFACE_H

/*******************************************************************************
 * END OF FILE
 ******************************************************************************/