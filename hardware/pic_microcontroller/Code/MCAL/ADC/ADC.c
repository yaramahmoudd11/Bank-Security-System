/*******************************************************************************
 * File:    ADC.c
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Device:  PIC16F877A
 * Compiler: mikroC PRO for PIC
 *
 * Description:
 *     ADC Driver Implementation - Contains all ADC function implementations
 *     using pure register-level programming.
 *
 * Features:
 *     - Complete register-level control
 *     - Configurable via ADC_Config.h
 *     - Blocking and non-blocking read functions
 *     - Voltage conversion utility
 *     - Fully documented code
 ******************************************************************************/

/*******************************************************************************
 * INCLUDES
 ******************************************************************************/
#include "ADC_Config.h"
#include "ADC_Private.h"
#include "ADC_Interface.h"

/*******************************************************************************
 * FUNCTION: ADC_Init
 *
 * DESCRIPTION:
 *     Initializes the ADC module with settings from ADC_Config.h
 *
 * IMPLEMENTATION:
 *     1. Turn off ADC module (ADON = 0)
 *     2. Configure ADCON1 register:
 *        - Set result justification (ADFM bit)
 *        - Configure analog/digital pins (PCFG bits)
 *     3. Configure ADCON0 register:
 *        - Set ADC clock (ADCS bits)
 *        - Clear channel selection (will be set when reading)
 *        - Clear GO/DONE bit
 *     4. Turn on ADC module (ADON = 1)
 *
 * PARAMETERS: None
 * RETURNS:    None
 ******************************************************************************/
void ADC_Init(void) {
    u8 temp_adcon0 = 0;
    u8 temp_adcon1 = 0;

    /* Step 1: Ensure ADC is initially OFF for safe configuration */
    CLR_BIT(ADCON0_REG, ADON);

    /* Step 2: Configure ADCON1 Register (Bank 1 - 0x9F) */

    /* Configure result justification (ADFM bit) */
    #if (ADC_RESULT_FORMAT == ADC_RIGHT_JUSTIFIED)
        temp_adcon1 |= (1 << ADFM);     // Set ADFM = 1 for right justified
    #else
        temp_adcon1 &= ~(1 << ADFM);    // Clear ADFM = 0 for left justified
    #endif

    /* Configure port pins as analog or digital (PCFG3:PCFG0 bits) */
    temp_adcon1 |= (ADC_PORT_CONFIG & PCFG_MASK);

    /* Write to ADCON1 register */
    ADCON1_REG = temp_adcon1;

    /* Step 3: Configure ADCON0 Register (Bank 0 - 0x1F) */

    /* Configure ADC clock selection (ADCS1:ADCS0 bits) */
    temp_adcon0 = (ADC_CLOCK_SELECTION << ADCS0);

    /* Clear channel selection bits (will be set when reading channel) */
    temp_adcon0 &= ~CHS_MASK;

    /* Clear GO/DONE bit (no conversion in progress) */
    temp_adcon0 &= ~GO_DONE_MASK;

    /* Write to ADCON0 register (ADC still OFF) */
    ADCON0_REG = temp_adcon0;

    /* Step 4: Enable ADC Module */
    SET_BIT(ADCON0_REG, ADON);          // ADON = 1, turn ADC ON

    /* Small delay to allow ADC module to stabilize */
    Delay_us(20);
}

/*******************************************************************************
 * FUNCTION: ADC_Enable
 *
 * DESCRIPTION:
 *     Enables the ADC module by setting the ADON bit
 *
 * PARAMETERS: None
 * RETURNS:    None
 ******************************************************************************/
void ADC_Enable(void) {
    SET_BIT(ADCON0_REG, ADON);          // Set ADON bit to turn ADC ON
}

/*******************************************************************************
 * FUNCTION: ADC_Disable
 *
 * DESCRIPTION:
 *     Disables the ADC module to save power by clearing the ADON bit
 *
 * PARAMETERS: None
 * RETURNS:    None
 ******************************************************************************/
void ADC_Disable(void) {
    CLR_BIT(ADCON0_REG, ADON);        // Clear ADON bit to turn ADC OFF
}

/*******************************************************************************
 * FUNCTION: ADC_SelectChannel
 *
 * DESCRIPTION:
 *     Selects the ADC input channel without starting conversion
 *
 * IMPLEMENTATION:
 *     1. Mask out current channel selection (CHS2:CHS0)
 *     2. Set new channel value in bits 5:3 of ADCON0
 *
 * PARAMETERS:
 *     channel - ADC channel number (0-7)
 *
 * RETURNS: None
 ******************************************************************************/
void ADC_SelectChannel(u8 channel) {
    /* Ensure channel is within valid range (0-7) */
    channel &= 0x07;

    /* Clear current channel selection bits (CHS2:CHS0) */
    ADCON0_REG &= ~CHS_MASK;

    /* Set new channel (shift channel value to bits 5:3) */
    ADCON0_REG |= (channel << CHS0);
}

/*******************************************************************************
 * FUNCTION: ADC_StartConversion
 *
 * DESCRIPTION:
 *     Starts ADC conversion by setting the GO/DONE bit
 *
 * IMPLEMENTATION:
 *     - Set bit 2 (GO/DONE) of ADCON0 to start conversion
 *     - This bit will be automatically cleared by hardware when done
 *
 * PARAMETERS: None
 * RETURNS:    None
 ******************************************************************************/
void ADC_StartConversion(void) {
    SET_BIT(ADCON0_REG, GO_DONE);       // Set GO/DONE bit to start conversion
}

/*******************************************************************************
 * FUNCTION: ADC_IsConversionDone
 *
 * DESCRIPTION:
 *     Checks if ADC conversion is complete
 *
 * IMPLEMENTATION:
 *     - Read GO/DONE bit (bit 2) of ADCON0
 *     - Returns 1 if conversion is complete (GO/DONE = 0)
 *     - Returns 0 if conversion is in progress (GO/DONE = 1)
 *
 * PARAMETERS: None
 * RETURNS:    1 if done, 0 if in progress
 ******************************************************************************/
u8 ADC_IsConversionDone(void) {
    /* GO/DONE bit is 0 when conversion is complete */
    /* Return the inverse: 1 when done, 0 when busy */
    return !GET_BIT(ADCON0_REG, GO_DONE);
}

/*******************************************************************************
 * FUNCTION: ADC_ReadResult
 *
 * DESCRIPTION:
 *     Reads the 10-bit ADC conversion result from ADRESH:ADRESL
 *
 * IMPLEMENTATION:
 *     - Check result format (right or left justified)
 *     - Combine ADRESH and ADRESL appropriately
 *     - Return 10-bit result
 *
 * RIGHT JUSTIFIED:
 *     ADRESH = [0 0 0 0 0 0 b9 b8]
 *     ADRESL = [b7 b6 b5 b4 b3 b2 b1 b0]
 *     Result = (ADRESH << 8) | ADRESL
 *
 * LEFT JUSTIFIED:
 *     ADRESH = [b9 b8 b7 b6 b5 b4 b3 b2]
 *     ADRESL = [b1 b0 0 0 0 0 0 0]
 *     Result = ((ADRESH << 8) | ADRESL) >> 6
 *
 * PARAMETERS: None
 * RETURNS:    10-bit ADC result (0-1023)
 ******************************************************************************/
u16 ADC_ReadResult(void) {
    u16 result = 0;

    /* Check result format from ADCON1 register */
    #if (ADC_RESULT_FORMAT == ADC_RIGHT_JUSTIFIED)
        /* Right justified: Combine ADRESH (upper 2 bits) and ADRESL (lower 8 bits) */
        result = ((u16)ADRESH_REG << 8) | ADRESL_REG;
    #else
        /* Left justified: Combine and shift right by 6 */
        result = (((u16)ADRESH_REG << 8) | ADRESL_REG) >> 6;
    #endif

    /* Mask to ensure only 10 bits are returned */
    result &= 0x03FF;

    return result;
}

/*******************************************************************************
 * FUNCTION: ADC_ReadChannel
 *
 * DESCRIPTION:
 *     Performs a complete ADC read from the specified channel (BLOCKING)
 *
 * IMPLEMENTATION:
 *     1. Select the desired channel
 *     2. Wait for acquisition time (from ADC_Config.h)
 *     3. Start conversion
 *     4. Wait for conversion to complete (polling GO/DONE bit)
 *     5. Read and return result
 *
 * TIMING (@ 16MHz with Fosc/32):
 *     - Channel selection: ~1µs
 *     - Acquisition delay: 20µs (configurable)
 *     - Conversion time: 12 TAD = 12 × 2µs = 24µs
 *     - Total: ~45µs
 *
 * PARAMETERS:
 *     channel - ADC channel number (0-7)
 *
 * RETURNS:
 *     10-bit ADC result (0-1023)
 ******************************************************************************/
u16 ADC_ReadChannel(u8 channel) {
    u16 adc_result = 0;

    /* Step 1: Select ADC channel */
    ADC_SelectChannel(channel);

    /* Step 2: Wait for acquisition time */
    /* This allows the holding capacitor to charge to the input voltage */
    Delay_us(ADC_ACQUISITION_DELAY_US);

    /* Step 3: Start A/D conversion */
    ADC_StartConversion();

    /* Step 4: Wait for conversion to complete (polling) */
    /* GO/DONE bit is automatically cleared by hardware when done */
    while (!ADC_IsConversionDone()) {
        // Busy wait - could add timeout here for robustness
    }

    /* Step 5: Read the result */
    adc_result = ADC_ReadResult();

    return adc_result;
}

/*******************************************************************************
 * FUNCTION: ADC_StartChannelConversion
 *
 * DESCRIPTION:
 *     Starts ADC conversion on specified channel (NON-BLOCKING)
 *     User must separately check completion and read result
 *
 * IMPLEMENTATION:
 *     1. Select channel
 *     2. Wait for acquisition
 *     3. Start conversion
 *     4. Return immediately (don't wait)
 *
 * USAGE PATTERN:
 *     ADC_StartChannelConversion(2);
 *     // Do other work...
 *     while (!ADC_IsConversionDone());
 *     result = ADC_ReadResult();
 *
 * PARAMETERS:
 *     channel - ADC channel number (0-7)
 *
 * RETURNS: None
 ******************************************************************************/
void ADC_StartChannelConversion(u8 channel) {
    /* Select the channel */
    ADC_SelectChannel(channel);

    /* Wait for acquisition time */
    Delay_us(ADC_ACQUISITION_DELAY_US);

    /* Start conversion (non-blocking) */
    ADC_StartConversion();

    /* Return immediately - user must poll for completion */
}

/*******************************************************************************
 * FUNCTION: ADC_ConvertToVoltage
 *
 * DESCRIPTION:
 *     Converts 10-bit ADC value to voltage in millivolts
 *
 * FORMULA:
 *     Voltage (mV) = (ADC_Value × VREF_mV) / 1024
 *
 * EXAMPLE:
 *     If VREF = 5.0V (5000mV) and ADC reads 512:
 *     Voltage = (512 × 5000) / 1024 = 2500mV = 2.5V
 *
 * PARAMETERS:
 *     adc_value - 10-bit ADC reading (0-1023)
 *     vref_mv   - Reference voltage in millivolts (e.g., 5000 for 5V)
 *
 * RETURNS:
 *     Voltage in millivolts
 *
 * NOTES:
 *     - Uses integer math for efficiency
 *     - For VREF = VDD = 5V, use vref_mv = 5000
 *     - For external VREF, use actual reference voltage
 ******************************************************************************/
u16 ADC_ConvertToVoltage(u16 adc_value, u16 vref_mv) {
    u16 voltage_mv = 0;

    /* Ensure ADC value is within valid range */
    if (adc_value > ADC_10BIT_MAX) {
        adc_value = ADC_10BIT_MAX;
    }

    /* Calculate voltage using integer math */
    /* voltage_mv = (adc_value * vref_mv) / 1024 */
    /* To avoid overflow, use long intermediate result */
    voltage_mv = (u16)(((unsigned long)adc_value * vref_mv) >> 10);

    return voltage_mv;
}

/*******************************************************************************
 * END OF FILE
 ******************************************************************************/