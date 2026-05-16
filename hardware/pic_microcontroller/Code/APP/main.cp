#line 1 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/APP/main.c"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_private.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/services/bit_math.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 35 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
typedef enum {
 ADC_CHANNEL_0 = 0,
 ADC_CHANNEL_1 = 1,
 ADC_CHANNEL_2 = 2,
 ADC_CHANNEL_3 = 3,
 ADC_CHANNEL_4 = 4,
 ADC_CHANNEL_5 = 5,
 ADC_CHANNEL_6 = 6,
 ADC_CHANNEL_7 = 7
} ADC_Channel_t;
#line 49 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
typedef enum {
 ADC_OK = 0,
 ADC_ERROR = 1
} ADC_Status_t;
#line 74 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
void ADC_Init(void);
#line 84 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
void ADC_Enable(void);
#line 94 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
void ADC_Disable(void);
#line 107 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
void ADC_SelectChannel(u8 channel);
#line 120 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
void ADC_StartConversion(void);
#line 130 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
u8 ADC_IsConversionDone(void);
#line 143 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
u16 ADC_ReadResult(void);
#line 161 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
u16 ADC_ReadChannel(u8 channel);
#line 178 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
void ADC_StartChannelConversion(u8 channel);
#line 192 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
u16 ADC_ConvertToVoltage(u16 adc_value, u16 vref_mv);
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/gpio/gpio_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/gpio/../../services/std_types.h"
#line 31 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/gpio/gpio_interface.h"
void GPIO_SetPinDirection(unsigned char Port, u8 Pin, u8 Direction);
void GPIO_SetPinValue(u8 Port, u8 Pin, u8 Value);
u8 GPIO_GetPinValue(u8 Port, u8 Pin);
void GPIO_Init(void);
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/gpio/gpio_private.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/gpio/gpio_config.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/services/bit_math.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/services/std_types.h"
#line 10 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/APP/main.c"
void System_Init(void)
{

 u16 adc_value = 0;
 u16 voltage_mv = 0;
 u8 rb1_state;
 u8 rb2_state;
 u8 rd4_state;


 GPIO_SetPinDirection( 3 ,  0 ,  0 );
 GPIO_SetPinDirection( 3 ,  1 ,  0 );
 GPIO_SetPinDirection( 3 ,  2 ,  0 );
 GPIO_SetPinDirection( 3 ,  3 ,  0 );
 GPIO_SetPinDirection( 2 ,  6 ,  0 );

 GPIO_SetPinDirection( 1 ,  1 ,  1 );
 GPIO_SetPinDirection( 1 ,  2 ,  1 );
 GPIO_SetPinDirection( 2 ,  7 ,  1 );
 GPIO_SetPinDirection( 3 ,  4 ,  1 );
 GPIO_SetPinDirection( 0 ,  0 ,  1 );


 GPIO_SetPinValue( 3 ,  0 ,  0 );
 GPIO_SetPinValue( 3 ,  1 ,  0 );
 GPIO_SetPinValue( 3 ,  2 ,  0 );
 GPIO_SetPinValue( 3 ,  3 ,  0 );
 GPIO_SetPinValue( 3 ,  4 ,  0 );

 GPIO_SetPinValue( 2 ,  6 ,  0 );
 GPIO_SetPinValue( 2 ,  7 ,  0 );

 GPIO_SetPinValue( 1 ,  1 ,  0 );
 GPIO_SetPinValue( 1 ,  2 ,  0 );

 GPIO_SetPinValue( 0 ,  0 ,  0 );


}

void basic_ops(void)
{
 rb1_state = GPIO_GetPinValue( 1 ,  1 );
 rb2_state = GPIO_GetPinValue( 1 ,  2 );
 rd4_state = GPIO_GetPinValue( 3 ,  4 );

 if(rb1_state == 1U && rb2_state == 0U)
 {
 GPIO_SetPinValue( 3 , RD3_PIN,  1 );
 GPIO_SetPinValue( 3 , RD0_PIN,  1 );
 GPIO_SetPinValue( 3 , RD1_PIN,  1 );
 GPIO_SetPinValue( 3 , RD4_PIN,  0 );
 }

 if(rb1_state == 0U && rb2_state == 0U)
 {
 GPIO_SetPinValue( 3 , RD3_PIN,  0 );
 GPIO_SetPinValue( 3 , RD1_PIN,  0 );
 GPIO_SetPinValue( 3 , RD0_PIN,  0 );
 GPIO_SetPinValue( 3 , RD4_PIN,  0 );
 }

 if(rb1_state == 0U && rb2_state == 1U)
 {
 GPIO_SetPinValue( 3 , RD3_PIN,  0 );
 GPIO_SetPinValue( 3 , RD1_PIN,  0 );
 GPIO_SetPinValue( 3 , RD0_PIN,  1 );
 GPIO_SetPinValue( 3 , RD4_PIN,  1 );
 }

 if(rb1_state == 1U && rb2_state == 1U)
 {
 GPIO_SetPinValue( 3 , RD3_PIN,  1 );
 GPIO_SetPinValue( 3 , RD0_PIN,  1 );
 GPIO_SetPinValue( 3 , RD1_PIN,  1 );
 GPIO_SetPinValue( 3 , RD4_PIN,  1 );
 }
}

void main() {

 System_Init();


 ADC_Init();


 while(1) {



 adc_value = ADC_ReadChannel(0);



 voltage_mv = ADC_ConvertToVoltage(adc_value, 5000);



 if (voltage_mv < 1000) {
  (*((volatile u8*)0x08)) .B0 = 1;
 } else {
  (*((volatile u8*)0x08)) .B0 = 0;
 }


 Delay_ms(100);
 }
}
