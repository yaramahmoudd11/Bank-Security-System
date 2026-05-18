#line 1 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/APP/main.c"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/gpio/gpio_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/gpio/../../services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 31 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/gpio/gpio_interface.h"
void GPIO_SetPinDirection(unsigned char Port, u8 Pin, u8 Direction);
void GPIO_SetPinValue(u8 Port, u8 Pin, u8 Value);
u8 GPIO_GetPinValue(u8 Port, u8 Pin);
void GPIO_Init(void);
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_private.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/../../services/bit_math.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/../../services/std_types.h"
#line 35 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
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
#line 49 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
typedef enum {
 ADC_OK = 0,
 ADC_ERROR = 1
} ADC_Status_t;
#line 74 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
void ADC_Init(void);
#line 84 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
void ADC_Enable(void);
#line 94 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
void ADC_Disable(void);
#line 107 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
void ADC_SelectChannel(u8 channel);
#line 120 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
void ADC_StartConversion(void);
#line 130 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
u8 ADC_IsConversionDone(void);
#line 143 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
u16 ADC_ReadResult(void);
#line 161 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
u16 ADC_ReadChannel(u8 channel);
#line 178 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
void ADC_StartChannelConversion(u8 channel);
#line 192 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/adc/adc_interface.h"
u16 ADC_ConvertToVoltage(u16 adc_value, u16 vref_mv);
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_private.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/../../services/std_types.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/../../services/bit_math.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_config.h"
#line 33 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_Init(void);
#line 43 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_SendByte(u8 txData);
#line 53 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
u8 UART_ReceiveByte(void);
#line 63 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_SendString(const char* str);
#line 74 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_ReceiveString(char* buffer, u8 maxLength);
#line 83 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
u8 UART_DataReady(void);
#line 93 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
u8 UART_TxReady(void);
#line 106 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_SendNumber(u16 number);
#line 115 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_SendNewLine(void);
#line 122 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_SendChar(char ch);
#line 129 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
char UART_ReceiveChar(void);
#line 143 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
u8 UART_ClearErrors(void);
#line 152 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
u8 UART_CheckErrors(void);
#line 185 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../mcal/uart/uart_interface.h"
void UART_Flush(void);
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../hal/led/led_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../hal/led/../../services/std_types.h"
#line 10 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../hal/led/led_interface.h"
void LED_Init(u8 Port, u8 Pin);
void LED_On(u8 Port, u8 Pin);
void LED_Off(u8 Port, u8 Pin);
void LED_Toggle(u8 Port, u8 Pin);
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../hal/switch/switch_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../hal/switch/../../services/std_types.h"
#line 6 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../hal/switch/switch_interface.h"
void SWITCH_Init(u8 Port, u8 Pin);
u8 SWITCH_GetState(u8 Port, u8 Pin);
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/app/../services/std_types.h"
#line 63 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/APP/main.c"
static u8 rb1_state = 0;
static u8 rb2_state = 0;
static u8 rd4_state = 0;
static u16 adc_value = 0;



static void System_Init(void);
static void Read_Inputs(void);
static void Apply_Output_Logic(void);
static void Send_ADC_UART(void);



void main(void)
{
 System_Init();

 while(1)
 {
 Read_Inputs();
 Apply_Output_Logic();
 Send_ADC_UART();

 Delay_ms(500);
 }
}



static void System_Init(void)
{


 SWITCH_Init( 1 ,  1 );
 SWITCH_Init( 1 ,  2 );
 SWITCH_Init( 3 ,  4 );

 GPIO_SetPinDirection( 0 ,
  0 ,
  1 );



 GPIO_SetPinDirection( 3 ,
  0 ,
  0 );

 GPIO_SetPinDirection( 3 ,
  1 ,
  0 );

 GPIO_SetPinDirection( 3 ,
  2 ,
  0 );

 LED_Init( 3 ,  3 );



 GPIO_SetPinDirection( 2 ,
  6 ,
  0 );

 GPIO_SetPinDirection( 2 ,
  7 ,
  1 );



 GPIO_SetPinValue( 3 ,
  0 ,
  0 );

 GPIO_SetPinValue( 3 ,
  1 ,
  0 );

 GPIO_SetPinValue( 3 ,
  2 ,
  0 );

 LED_Off( 3 ,  3 );



 ADC_Init();
 UART_Init();
}



static void Read_Inputs(void)
{
 rb1_state = SWITCH_GetState( 1 ,  1 );
 rb2_state = SWITCH_GetState( 1 ,  2 );
 rd4_state = SWITCH_GetState( 3 ,  4 );

 adc_value = ADC_ReadChannel( ADC_CHANNEL_0 );
}



static void Apply_Output_Logic(void)
{
#line 187 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/APP/main.c"
 if(rb1_state ==  1 )
 {
 LED_On( 3 ,  3 );

 GPIO_SetPinValue( 3 ,
  0 ,
  1 );

 GPIO_SetPinValue( 3 ,
  1 ,
  1 );
 }
 else if((rb2_state ==  1 ) || (rd4_state ==  1 ))
 {
 LED_Off( 3 ,  3 );

 GPIO_SetPinValue( 3 ,
  0 ,
  1 );

 GPIO_SetPinValue( 3 ,
  1 ,
  0 );
 }
 else
 {
 LED_Off( 3 ,  3 );

 GPIO_SetPinValue( 3 ,
  0 ,
  0 );

 GPIO_SetPinValue( 3 ,
  1 ,
  0 );
 }
#line 230 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/APP/main.c"
 if(adc_value <  205U )
 {
 GPIO_SetPinValue( 3 ,
  2 ,
  1 );
 }
 else
 {
 GPIO_SetPinValue( 3 ,
  2 ,
  0 );
 }
}



static void Send_ADC_UART(void)
{
#line 254 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/APP/main.c"
 UART_SendByte((u8)(adc_value >> 8));
 UART_SendByte((u8)(adc_value & 0xFF));
}
