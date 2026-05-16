/******************************************************************************
 * @file    main.c
 * @brief   PIC16F877A Security I/O + ADC voltage UART transmission
 * @target  PIC16F877A
 ******************************************************************************/

#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/UART/UART_Interface.h"
#include "../SERVICES/STD_TYPES.h"

/* ========================== PIN MAPPING ================================== */

#define VOLTAGE_ADC_CHANNEL        ADC_CHANNEL_0     /* RA0 / AN0 */
#define VOLTAGE_THRESHOLD_MV       1000U             /* 1V threshold */
#define ADC_VREF_MV                5000U             /* VDD reference = 5V */

/* Inputs */
#define PIR_INPUT_PORT             GPIO_PORTB
#define PIR_INPUT_PIN              GPIO_PIN1         /* RB1 */

#define LOCK_INPUT_PORT            GPIO_PORTB
#define LOCK_INPUT_PIN             GPIO_PIN2         /* RB2 */

#define EXTRA_INPUT_PORT           GPIO_PORTD
#define EXTRA_INPUT_PIN            GPIO_PIN4         /* RD4 */

#define VOLTAGE_INPUT_PORT         GPIO_PORTA
#define VOLTAGE_INPUT_PIN          GPIO_PIN0         /* RA0 */

/* Outputs */
#define LOCK_OUTPUT_PORT           GPIO_PORTD
#define LOCK_OUTPUT_PIN            GPIO_PIN0         /* RD0 */

#define ALARM_OUTPUT_PORT          GPIO_PORTD
#define ALARM_OUTPUT_PIN           GPIO_PIN1         /* RD1 */

#define VOLTAGE_OUTPUT_PORT        GPIO_PORTD
#define VOLTAGE_OUTPUT_PIN         GPIO_PIN2         /* RD2 */

#define PIR_OUTPUT_PORT            GPIO_PORTD
#define PIR_OUTPUT_PIN             GPIO_PIN3         /* RD3 */

/* UART pins */
#define UART_TX_PORT               GPIO_PORTC
#define UART_TX_PIN                GPIO_PIN6         /* RC6 / TX */

#define UART_RX_PORT               GPIO_PORTC
#define UART_RX_PIN                GPIO_PIN7         /* RC7 / RX */

/* ========================== GLOBAL VARIABLES ============================= */

static u16 adc_value = 0;
static u16 voltage_mv = 0;
static u8 rb1_state = 0;
static u8 rb2_state = 0;
static u8 rd4_state = 0;

/* ========================== FUNCTION PROTOTYPES =========================== */

static void System_Init(void);
static void Read_Inputs(void);
static void Apply_Output_Logic(void);
static void Send_ADC_UART(void);

/* ========================== FUNCTION DEFINITIONS ========================== */

static void System_Init(void)
{
    /* Digital inputs */
    GPIO_SetPinDirection(PIR_INPUT_PORT, PIR_INPUT_PIN, GPIO_INPUT);       /* RB1 input */
    GPIO_SetPinDirection(LOCK_INPUT_PORT, LOCK_INPUT_PIN, GPIO_INPUT);     /* RB2 input */
    GPIO_SetPinDirection(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN, GPIO_INPUT);   /* RD4 input */

    /* Analog input */
    GPIO_SetPinDirection(VOLTAGE_INPUT_PORT, VOLTAGE_INPUT_PIN, GPIO_INPUT); /* RA0 input */

    /* Outputs */
    GPIO_SetPinDirection(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_OUTPUT);       /* RD0 output */
    GPIO_SetPinDirection(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_OUTPUT);     /* RD1 output */
    GPIO_SetPinDirection(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_OUTPUT); /* RD2 output */
    GPIO_SetPinDirection(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_OUTPUT);         /* RD3 output */

    /* UART pins */
    GPIO_SetPinDirection(UART_TX_PORT, UART_TX_PIN, GPIO_OUTPUT);   /* RC6 TX output */
    GPIO_SetPinDirection(UART_RX_PORT, UART_RX_PIN, GPIO_INPUT);    /* RC7 RX input */

    /* Initial output states */
    GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_LOW);
    GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_LOW);
    GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_LOW);
    GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_LOW);

    ADC_Init();
    UART_Init();
}

static void Read_Inputs(void)
{
    rb1_state = GPIO_GetPinValue(PIR_INPUT_PORT, PIR_INPUT_PIN);
    rb2_state = GPIO_GetPinValue(LOCK_INPUT_PORT, LOCK_INPUT_PIN);
    rd4_state = GPIO_GetPinValue(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN);

    adc_value = ADC_ReadChannel(VOLTAGE_ADC_CHANNEL);
    voltage_mv = ADC_ConvertToVoltage(adc_value, ADC_VREF_MV);

    /* rd4_state is read because RD4 is required as input.
       No output action is assigned to RD4 in the requested logic. */
    (void)rd4_state;
}

static void Apply_Output_Logic(void)
{
    /* RB2 high -> RD0 high */
    if (rb2_state == GPIO_HIGH)
    {
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);
    }
    else
    {
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_LOW);
    }

    /* RA0 voltage exceeds 1V threshold -> RD2 high */
    if (voltage_mv > VOLTAGE_THRESHOLD_MV)
    {
        GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_HIGH);
    }
    else
    {
        GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_LOW);
    }

    /* RB1 high -> RD3 high and RD1 high */
    if (rb1_state == GPIO_HIGH)
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_HIGH);
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_HIGH);
    }
    else
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_LOW);
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_LOW);
    }
}

static void Send_ADC_UART(void)
{
    /* Send ADC value as 2 binary bytes: high byte then low byte.
       This matches the Raspberry Pi code that reads ser.read(2). */
    UART_SendByte((u8)(adc_value >> 8));
    UART_SendByte((u8)(adc_value & 0xFF));
}

void main(void)
{
    System_Init();

    while (1)
    {
        Read_Inputs();
        Apply_Output_Logic();
        Send_ADC_UART();

        Delay_ms(500);
    }
}
