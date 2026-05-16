#line 1 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_private.h"
#line 19 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_private.h"
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
typedef signed char s8;
typedef signed int s16;
typedef signed long s32;
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_config.h"
#line 33 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_Init(void);
#line 43 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_SendByte(u8 txData);
#line 53 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
u8 UART_ReceiveByte(void);
#line 63 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_SendString(const char* str);
#line 74 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_ReceiveString(char* buffer, u8 maxLength);
#line 83 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
u8 UART_DataReady(void);
#line 93 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
u8 UART_TxReady(void);
#line 106 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_SendNumber(u16 number);
#line 115 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_SendNewLine(void);
#line 122 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_SendChar(char ch);
#line 129 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
char UART_ReceiveChar(void);
#line 143 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
u8 UART_ClearErrors(void);
#line 152 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
u8 UART_CheckErrors(void);
#line 185 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_interface.h"
void UART_Flush(void);
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_private.h"
#line 1 "d:/felo - zc/year 3/semister 2/cie 349 (embedded systems)/project code/code/mcal/uart/uart_config.h"
#line 32 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
void UART_Init(void)
{

  (( (*((volatile u8*)0x18)) ) &= ~(1 << ( 7 ))) ;




  (*((volatile u8*)0x99))  = (u8) (( 16000000UL /(16UL* 9600 ))-1) ;



  (*((volatile u8*)0x98))  = 0x00;



  (( (*((volatile u8*)0x98)) ) &= ~(1 << ( 4 ))) ;
#line 56 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
  (( (*((volatile u8*)0x98)) ) |= (1 << ( 2 ))) ;
#line 65 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
  (( (*((volatile u8*)0x98)) ) &= ~(1 << ( 6 ))) ;




  (( (*((volatile u8*)0x98)) ) |= (1 << ( 5 ))) ;
#line 77 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
  (*((volatile u8*)0x18))  = 0x00;





  (( (*((volatile u8*)0x18)) ) &= ~(1 << ( 6 ))) ;





  (( (*((volatile u8*)0x18)) ) |= (1 << ( 4 ))) ;
#line 96 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
  (( (*((volatile u8*)0x18)) ) |= (1 << ( 7 ))) ;


 UART_ClearErrors();
#line 107 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
 Delay_ms(10);
}
#line 123 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
void UART_SendByte(u8 txData)
{


 while (! ((( (*((volatile u8*)0x0C)) ) >> ( 4 )) & 0x01) )
 {

 }



  (*((volatile u8*)0x19))  = txData;
}
#line 141 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
void UART_SendChar(char ch)
{
 UART_SendByte((u8)ch);
}
#line 154 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
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
#line 188 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
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
#line 220 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
void UART_SendNewLine(void)
{
 UART_SendByte( '\r' );
 UART_SendByte( '\n' );
}
#line 240 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
u8 UART_ReceiveByte(void)
{
 u8 rxData;



 while (! ((( (*((volatile u8*)0x0C)) ) >> ( 5 )) & 0x01) )
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
#line 273 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
char UART_ReceiveChar(void)
{
 return (char)UART_ReceiveByte();
}
#line 287 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
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
#line 329 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
u8 UART_DataReady(void)
{

 return  ((( (*((volatile u8*)0x0C)) ) >> ( 5 )) & 0x01) ;
}
#line 341 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
u8 UART_TxReady(void)
{


 return  ((( (*((volatile u8*)0x98)) ) >> ( 1 )) & 0x01) ;
}
#line 363 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
u8 UART_CheckErrors(void)
{


 if ( ((( (*((volatile u8*)0x18)) ) >> ( 1 )) & 0x01) )
 {
 return  1 ;
 }



 if ( ((( (*((volatile u8*)0x18)) ) >> ( 2 )) & 0x01) )
 {
 return  2 ;
 }

 return  0 ;
}
#line 396 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
u8 UART_ClearErrors(void)
{
 u8 errorCode =  0 ;
 u8 dummyRead;


 if ( ((( (*((volatile u8*)0x18)) ) >> ( 1 )) & 0x01) )
 {
 errorCode =  1 ;


  (( (*((volatile u8*)0x18)) ) &= ~(1 << ( 4 ))) ;
 dummyRead =  (*((volatile u8*)0x1A)) ;
 dummyRead =  (*((volatile u8*)0x1A)) ;
  (( (*((volatile u8*)0x18)) ) |= (1 << ( 4 ))) ;
 }


 if ( ((( (*((volatile u8*)0x18)) ) >> ( 2 )) & 0x01) )
 {
 errorCode =  2 ;


 dummyRead =  (*((volatile u8*)0x1A)) ;
 }


 (void)dummyRead;

 return errorCode;
}
#line 436 "D:/FELO - ZC/YEAR 3/SEMISTER 2/CIE 349 (Embedded Systems)/Project Code/Code/MCAL/UART/UART.c"
void UART_Flush(void)
{
 u8 dummyRead;


 while ( ((( (*((volatile u8*)0x0C)) ) >> ( 5 )) & 0x01) )
 {
 dummyRead =  (*((volatile u8*)0x1A)) ;
 }


 UART_ClearErrors();


 (void)dummyRead;
}
