#line 1 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/ALL Drivers/HAL/SWITCH/SWITCH.c"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/switch/switch_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/switch/../../services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 6 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/switch/switch_interface.h"
void SWITCH_Init(u8 Port, u8 Pin);
u8 SWITCH_GetState(u8 Port, u8 Pin);
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/switch/../../mcal/gpio/gpio_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/switch/../../mcal/gpio/../../services/std_types.h"
#line 31 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/all drivers/hal/switch/../../mcal/gpio/gpio_interface.h"
void GPIO_SetPinDirection(unsigned char Port, u8 Pin, u8 Direction);
void GPIO_SetPinValue(u8 Port, u8 Pin, u8 Value);
u8 GPIO_GetPinValue(u8 Port, u8 Pin);
void GPIO_Init(void);
#line 4 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/ALL Drivers/HAL/SWITCH/SWITCH.c"
void SWITCH_Init(u8 Port, u8 Pin)
{

 GPIO_SetPinDirection(Port, Pin,  1 );
}

u8 SWITCH_GetState(u8 Port, u8 Pin)
{

 return GPIO_GetPinValue(Port, Pin);
}
