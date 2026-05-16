#include "SWITCH_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

void SWITCH_Init(u8 Port, u8 Pin)
{
    /* Initialize switch pin as input */
    GPIO_SetPinDirection(Port, Pin, GPIO_INPUT);
}

u8 SWITCH_GetState(u8 Port, u8 Pin)
{
    /* Return the logical state of the switch pin */
    return GPIO_GetPinValue(Port, Pin);
}
