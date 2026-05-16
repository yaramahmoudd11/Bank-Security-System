#line 1 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_config.h"
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
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/adc/adc_private.h"
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
#line 47 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
void ADC_Init(void) {
 u8 temp_adcon0 = 0;
 u8 temp_adcon1 = 0;


  ( ( (*((volatile u8*)0x1F)) ) &= ~(1U << ( 0 )) ) ;





 temp_adcon1 |= (1 <<  7 );
#line 64 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
 temp_adcon1 |= ( 0x00  &  0x0F );


  (*((volatile u8*)0x9F))  = temp_adcon1;




 temp_adcon0 = ( 0x02  <<  6 );


 temp_adcon0 &= ~ 0x38 ;


 temp_adcon0 &= ~ 0x04 ;


  (*((volatile u8*)0x1F))  = temp_adcon0;


  ( ( (*((volatile u8*)0x1F)) ) |= (1U << ( 0 )) ) ;


 Delay_us(20);
}
#line 99 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
void ADC_Enable(void) {
  ( ( (*((volatile u8*)0x1F)) ) |= (1U << ( 0 )) ) ;
}
#line 112 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
void ADC_Disable(void) {
  ( ( (*((volatile u8*)0x1F)) ) &= ~(1U << ( 0 )) ) ;
}
#line 131 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
void ADC_SelectChannel(u8 channel) {

 channel &= 0x07;


  (*((volatile u8*)0x1F))  &= ~ 0x38 ;


  (*((volatile u8*)0x1F))  |= (channel <<  3 );
}
#line 155 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
void ADC_StartConversion(void) {
  ( ( (*((volatile u8*)0x1F)) ) |= (1U << ( 2 )) ) ;
}
#line 173 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
u8 ADC_IsConversionDone(void) {


 return ! ( (( (*((volatile u8*)0x1F)) ) >> ( 2 )) & 1U ) ;
}
#line 203 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
u16 ADC_ReadResult(void) {
 u16 result = 0;




 result = ((u16) (*((volatile u8*)0x1E))  << 8) |  (*((volatile u8*)0x9E)) ;
#line 216 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
 result &= 0x03FF;

 return result;
}
#line 246 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
u16 ADC_ReadChannel(u8 channel) {
 u16 adc_result = 0;


 ADC_SelectChannel(channel);



 Delay_us( 20 );


 ADC_StartConversion();



 while (!ADC_IsConversionDone()) {

 }


 adc_result = ADC_ReadResult();

 return adc_result;
}
#line 295 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
void ADC_StartChannelConversion(u8 channel) {

 ADC_SelectChannel(channel);


 Delay_us( 20 );


 ADC_StartConversion();


}
#line 333 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/ADC/ADC.c"
u16 ADC_ConvertToVoltage(u16 adc_value, u16 vref_mv) {
 u16 voltage_mv = 0;


 if (adc_value >  1023 ) {
 adc_value =  1023 ;
 }




 voltage_mv = (u16)(((unsigned long)adc_value * vref_mv) >> 10);

 return voltage_mv;
}
