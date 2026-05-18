#line 1 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/HAL/SWITCH/SWITCH.c"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/hal/switch/switch_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/hal/switch/../../services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 6 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/hal/switch/switch_interface.h"
void SWITCH_Init(u8 Port, u8 Pin);
u8 SWITCH_GetState(u8 Port, u8 Pin);
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/hal/switch/../../mcal/gpio/gpio_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/hal/switch/../../mcal/gpio/../../services/std_types.h"
#line 31 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/hal/switch/../../mcal/gpio/gpio_interface.h"
void GPIO_SetPinDirection(unsigned char Port, u8 Pin, u8 Direction);
void GPIO_SetPinValue(u8 Port, u8 Pin, u8 Value);
u8 GPIO_GetPinValue(u8 Port, u8 Pin);
void GPIO_Init(void);
#line 4 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/HAL/SWITCH/SWITCH.c"
void SWITCH_Init(u8 Port, u8 Pin)
{

 GPIO_SetPinDirection(Port, Pin,  1 );
}

u8 SWITCH_GetState(u8 Port, u8 Pin)
{

 return GPIO_GetPinValue(Port, Pin);
}
