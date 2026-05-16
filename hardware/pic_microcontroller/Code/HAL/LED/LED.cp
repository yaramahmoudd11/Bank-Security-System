#line 1 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/ALL Drivers/HAL/LED/LED.c"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/led/led_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/led/../../services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 10 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/led/led_interface.h"
void LED_Init(u8 Port, u8 Pin);
void LED_On(u8 Port, u8 Pin);
void LED_Off(u8 Port, u8 Pin);
void LED_Toggle(u8 Port, u8 Pin);
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/led/../../mcal/gpio/gpio_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/led/../../mcal/gpio/../../services/std_types.h"
#line 31 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/led/../../mcal/gpio/gpio_interface.h"
void GPIO_SetPinDirection(unsigned char Port, u8 Pin, u8 Direction);
void GPIO_SetPinValue(u8 Port, u8 Pin, u8 Value);
u8 GPIO_GetPinValue(u8 Port, u8 Pin);
void GPIO_Init(void);
#line 4 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/ALL Drivers/HAL/LED/LED.c"
void LED_Init(u8 Port, u8 Pin)
{
 GPIO_SetPinDirection(Port, Pin,  0 );
}

void LED_On(u8 Port, u8 Pin)
{
 GPIO_SetPinValue(Port, Pin,  1 );
}

void LED_Off(u8 Port, u8 Pin)
{
 GPIO_SetPinValue(Port, Pin,  0 );
}

void LED_Toggle(u8 Port, u8 Pin)
{
 u8 current = GPIO_GetPinValue(Port, Pin);

 if(current ==  1 )
 GPIO_SetPinValue(Port, Pin,  0 );
 else
 GPIO_SetPinValue(Port, Pin,  1 );
}
