#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\MCAL\ADC\ADC_Interface.h"

#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\MCAL\GPIO\GPIO_interface.h"
#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\MCAL\GPIO\GPIO_private.h"
#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\MCAL\GPIO\GPIO_config.h"

#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\SERVICES\BIT_MATH.h"
#include "D:\FELO - ZC\YEAR 3\SEMISTER 2\CIE 349 (Embedded Systems)\Project Code\Code\SERVICES\STD_TYPES.h"

void System_Init(void){

    u16 adc_value = 0;
    u16 voltage_mv = 0;
    u8 rb1_state;
    u8 rb2_state;
    u8 rd4_state;


    GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN0, GPIO_OUTPUT);
    GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN1, GPIO_OUTPUT);
    GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN2, GPIO_OUTPUT);
    GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN3, GPIO_OUTPUT);
    GPIO_SetPinDirection(GPIO_PORTC, GPIO_PIN6, GPIO_OUTPUT);

    GPIO_SetPinDirection(GPIO_PORTB, GPIO_PIN1, GPIO_INPUT);
    GPIO_SetPinDirection(GPIO_PORTB, GPIO_PIN2, GPIO_INPUT);
    GPIO_SetPinDirection(GPIO_PORTC, GPIO_PIN7, GPIO_INPUT);
    GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN4, GPIO_INPUT);
    GPIO_SetPinDirection(GPIO_PORTA, GPIO_PIN0, GPIO_INPUT);

    /* Set Initial state to LOW */
    GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN0, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN1, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN2, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN3, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN4, GPIO_LOW);

    GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN6, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTC, GPIO_PIN7, GPIO_LOW);

    GPIO_SetPinValue(GPIO_PORTB, GPIO_PIN1, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTB, GPIO_PIN2, GPIO_LOW);

    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN0, GPIO_LOW);
    

}

void basic_ops(void)
{
 rb1_state = GPIO_GetPinValue(GPIO_PORTB, GPIO_PIN1);
 rb2_state = GPIO_GetPinValue(GPIO_PORTB, GPIO_PIN2);
 rd4_state = GPIO_GetPinValue(GPIO_PORTD, GPIO_PIN4);

 if(rb1_state == 1U && rb2_state == 0U)
 {
  GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN0, GPIO_HIGH);
  GPIO_SetPinValue(GPIO_PORTD, RD0_PIN, GPIO_HIGH);
  GPIO_SetPinValue(GPIO_PORTD, RD1_PIN, GPIO_HIGH);
  GPIO_SetPinValue(GPIO_PORTD, RD4_PIN, GPIO_LOW);
 }

 if(rb1_state == 0U && rb2_state == 0U)
 {
   GPIO_SetPinValue(GPIO_PORTD, RD3_PIN, GPIO_LOW);
   GPIO_SetPinValue(GPIO_PORTD, RD1_PIN, GPIO_LOW);
   GPIO_SetPinValue(GPIO_PORTD, RD0_PIN, GPIO_LOW);
   GPIO_SetPinValue(GPIO_PORTD, RD4_PIN, GPIO_LOW);
 }

 if(rb1_state == 0U && rb2_state == 1U)
 {
    GPIO_SetPinValue(GPIO_PORTD, RD3_PIN, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTD, RD1_PIN, GPIO_LOW);
    GPIO_SetPinValue(GPIO_PORTD, RD0_PIN, GPIO_HIGH);
    GPIO_SetPinValue(GPIO_PORTD, RD4_PIN, GPIO_HIGH);
 }

 if(rb1_state == 1U && rb2_state == 1U)
 {
    GPIO_SetPinValue(GPIO_PORTD, RD3_PIN, GPIO_HIGH);
    GPIO_SetPinValue(GPIO_PORTD, RD0_PIN, GPIO_HIGH);
    GPIO_SetPinValue(GPIO_PORTD, RD1_PIN, GPIO_HIGH);
    GPIO_SetPinValue(GPIO_PORTD, RD4_PIN, GPIO_HIGH);
 }
}

void main() {
    
    System_Init();
    // --- ADC Initialization ---
    // Call the Initialization function from your ADC.c driver
    ADC_Init();

    // Main infinite loop
    while(1) {

        
        // Read the 10-bit raw ADC value from Channel 0 (blocking function)
        adc_value = ADC_ReadChannel(0);

        // Convert the raw ADC value to voltage in millivolts
        // Assuming a standard 5.0V (5000mV) reference voltage (VDD)
        voltage_mv = ADC_ConvertToVoltage(adc_value, 5000);

        // --- Logic condition ---
        // Check if the calculated voltage is less than 1 Volt (1000 mV)
        if (voltage_mv < 1000) {
            PORTD.B0 = 1;  // Make RD0 HIGH
        } else {
            PORTD.B0 = 0;  // Make RD0 LOW
        }

        // Small delay to provide system stability and prevent rapid toggling
        Delay_ms(100);
    }
}