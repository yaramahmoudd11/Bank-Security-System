#line 1 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_private.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/../../services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/../../services/bit_math.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_config.h"
#line 33 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_Init(void);
#line 43 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_SendByte(u8 txData);
#line 53 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
u8 UART_ReceiveByte(void);
#line 63 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_SendString(const char* str);
#line 74 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_ReceiveString(char* buffer, u8 maxLength);
#line 83 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
u8 UART_DataReady(void);
#line 93 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
u8 UART_TxReady(void);
#line 106 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_SendNumber(u16 number);
#line 115 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_SendNewLine(void);
#line 122 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_SendChar(char ch);
#line 129 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
char UART_ReceiveChar(void);
#line 143 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
u8 UART_ClearErrors(void);
#line 152 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
u8 UART_CheckErrors(void);
#line 185 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_interface.h"
void UART_Flush(void);
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_private.h"
#line 1 "c:/users/yaram/bank-smart-security-system/hardware/pic_microcontroller/code/mcal/uart/uart_config.h"
#line 32 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_Init(void)
{

  ( ( (*((volatile u8*)0x87)) ) &= ~(1U << ( 6 )) ) ;
  ( ( (*((volatile u8*)0x87)) ) |= (1U << ( 7 )) ) ;


  ( ( (*((volatile u8*)0x18)) ) &= ~(1U << ( 7 )) ) ;




  (*((volatile u8*)0x99))  = (u8) (( 16000000UL /(16UL* 9600 ))-1) ;



  (*((volatile u8*)0x98))  = 0x00;



  ( ( (*((volatile u8*)0x98)) ) &= ~(1U << ( 4 )) ) ;
#line 60 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
  ( ( (*((volatile u8*)0x98)) ) |= (1U << ( 2 )) ) ;
#line 69 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
  ( ( (*((volatile u8*)0x98)) ) &= ~(1U << ( 6 )) ) ;




  ( ( (*((volatile u8*)0x98)) ) |= (1U << ( 5 )) ) ;
#line 81 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
  (*((volatile u8*)0x18))  = 0x00;





  ( ( (*((volatile u8*)0x18)) ) &= ~(1U << ( 6 )) ) ;





  ( ( (*((volatile u8*)0x18)) ) |= (1U << ( 4 )) ) ;
#line 100 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
  ( ( (*((volatile u8*)0x18)) ) |= (1U << ( 7 )) ) ;


 UART_ClearErrors();
#line 111 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
 Delay_ms(10);
}
#line 127 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_SendByte(u8 txData)
{


 while (! ( (( (*((volatile u8*)0x0C)) ) >> ( 4 )) & 1U ) )
 {

 }



  (*((volatile u8*)0x19))  = txData;
}
#line 145 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_SendChar(char ch)
{
 UART_SendByte((u8)ch);
}
#line 158 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_SendString(const char* str)
{
 u8 i = 0;


 if (str == 0)
 {
 return;
 }


 while (str[i] !=  '\0' )
 {
 UART_SendByte((u8)str[i]);
 i++;


 if (i >= 255)
 {
 break;
 }
 }
}
#line 192 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_SendNumber(u16 number)
{
 char buffer[6];
 u8 i = 0;


 if (number == 0)
 {
 UART_SendByte('0');
 return;
 }


 while (number > 0)
 {
 buffer[i] = (number % 10) + '0';
 number = number / 10;
 i++;
 }


 while (i > 0)
 {
 i--;
 UART_SendByte((u8)buffer[i]);
 }
}
#line 224 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_SendNewLine(void)
{
 UART_SendByte( '\r' );
 UART_SendByte( '\n' );
}
#line 244 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
u8 UART_ReceiveByte(void)
{
 u8 rxData;



 while (! ( (( (*((volatile u8*)0x0C)) ) >> ( 5 )) & 1U ) )
 {

 }



 if (UART_CheckErrors() !=  0 )
 {

 UART_ClearErrors();
 rxData =  (*((volatile u8*)0x1A)) ;
 return 0;
 }




 rxData =  (*((volatile u8*)0x1A)) ;

 return rxData;
}
#line 277 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
char UART_ReceiveChar(void)
{
 return (char)UART_ReceiveByte();
}
#line 291 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_ReceiveString(char* buffer, u8 maxLength)
{
 u8 i = 0;
 char receivedChar;


 if (buffer == 0)
 {
 return;
 }


 while (i < (maxLength - 1))
 {
 receivedChar = (char)UART_ReceiveByte();


 if ((receivedChar ==  '\n' ) ||
 (receivedChar ==  '\r' ))
 {
 break;
 }


 buffer[i] = receivedChar;
 i++;
 }


 buffer[i] =  '\0' ;
}
#line 333 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
u8 UART_DataReady(void)
{

 return  ( (( (*((volatile u8*)0x0C)) ) >> ( 5 )) & 1U ) ;
}
#line 345 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
u8 UART_TxReady(void)
{


 return  ( (( (*((volatile u8*)0x98)) ) >> ( 1 )) & 1U ) ;
}
#line 367 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
u8 UART_CheckErrors(void)
{


 if ( ( (( (*((volatile u8*)0x18)) ) >> ( 1 )) & 1U ) )
 {
 return  1 ;
 }



 if ( ( (( (*((volatile u8*)0x18)) ) >> ( 2 )) & 1U ) )
 {
 return  2 ;
 }

 return  0 ;
}
#line 400 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
u8 UART_ClearErrors(void)
{
 u8 errorCode =  0 ;
 u8 dummyRead;


 if ( ( (( (*((volatile u8*)0x18)) ) >> ( 1 )) & 1U ) )
 {
 errorCode =  1 ;


  ( ( (*((volatile u8*)0x18)) ) &= ~(1U << ( 4 )) ) ;
 dummyRead =  (*((volatile u8*)0x1A)) ;
 dummyRead =  (*((volatile u8*)0x1A)) ;
  ( ( (*((volatile u8*)0x18)) ) |= (1U << ( 4 )) ) ;
 }


 if ( ( (( (*((volatile u8*)0x18)) ) >> ( 2 )) & 1U ) )
 {
 errorCode =  2 ;


 dummyRead =  (*((volatile u8*)0x1A)) ;
 }


 (void)dummyRead;

 return errorCode;
}
#line 440 "C:/Users/yaram/Bank-Smart-Security-System/hardware/pic_microcontroller/Code/MCAL/UART/UART.c"
void UART_Flush(void)
{
 u8 dummyRead;


 while ( ( (( (*((volatile u8*)0x0C)) ) >> ( 5 )) & 1U ) )
 {
 dummyRead =  (*((volatile u8*)0x1A)) ;
 }


 UART_ClearErrors();


 (void)dummyRead;
}
