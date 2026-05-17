/******************************************************************************
 * @file    main.c
 * @brief   PIC16F877A Security + Voltage Control with UART ADC transmission
 * @target  PIC16F877A
 ******************************************************************************/

#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/UART/UART_Interface.h"
#include "../SERVICES/STD_TYPES.h"

/* ========================== PIN MAPPING ================================== */

#define VOLTAGE_ADC_CHANNEL        ADC_CHANNEL_0     /* RA0 / AN0 */

/*
 * ADC Reference = 5V
 * 1V => (1 / 5) * 1023 = 204.6
 * ADC values 0..204 are below 1V
 */
#define VOLTAGE_1V_THRESHOLD       205U

/* Inputs */
#define PIR_INPUT_PORT             GPIO_PORTB
#define PIR_INPUT_PIN              GPIO_PIN1         /* RB1 */

#define LOCK_INPUT_PORT            GPIO_PORTB
#define LOCK_INPUT_PIN             GPIO_PIN2         /* RB2 */

#define EXTRA_INPUT_PORT           GPIO_PORTD
#define EXTRA_INPUT_PIN            GPIO_PIN4         /* RD4 */

#define VOLTAGE_INPUT_PORT         GPIO_PORTA
#define VOLTAGE_INPUT_PIN          GPIO_PIN0         /* RA0 / AN0 */

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
static u8 rb1_state = 0;
static u8 rb2_state = 0;
static u8 rd4_state = 0;

/* ========================== FUNCTION PROTOTYPES =========================== */

static void System_Init(void);
static void Read_Inputs(void);
static void Send_ADC_UART(void);
static void Apply_Output_Logic(void);
static void App_Task(void);

/* ========================== INIT ========================================= */

static void System_Init(void)
{
    /* Inputs */
    GPIO_SetPinDirection(VOLTAGE_INPUT_PORT, VOLTAGE_INPUT_PIN, GPIO_INPUT); /* RA0 / AN0 */
    GPIO_SetPinDirection(PIR_INPUT_PORT, PIR_INPUT_PIN, GPIO_INPUT);         /* RB1 */
    GPIO_SetPinDirection(LOCK_INPUT_PORT, LOCK_INPUT_PIN, GPIO_INPUT);       /* RB2 */
    GPIO_SetPinDirection(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN, GPIO_INPUT);     /* RD4 */

    /* Outputs */
    GPIO_SetPinDirection(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_OUTPUT);       /* RD0 */
    GPIO_SetPinDirection(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_OUTPUT);     /* RD1 */
    GPIO_SetPinDirection(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_OUTPUT); /* RD2 */
    GPIO_SetPinDirection(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_OUTPUT);         /* RD3 */

    /* UART pins */
    GPIO_SetPinDirection(UART_TX_PORT, UART_TX_PIN, GPIO_OUTPUT);  /* RC6 / TX */
    GPIO_SetPinDirection(UART_RX_PORT, UART_RX_PIN, GPIO_INPUT);   /* RC7 / RX */

    /* Initial LOW for outputs only */
    GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_LOW);       /* RD0 */
    GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_LOW);     /* RD1 */
    GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_LOW); /* RD2 */
    GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_LOW);         /* RD3 */

    /* Init drivers */
    ADC_Init();
    UART_Init();
}

/* ========================== READ INPUTS ================================== */

static void Read_Inputs(void)
{
    rb1_state = GPIO_GetPinValue(PIR_INPUT_PORT, PIR_INPUT_PIN);     /* RB1 */
    rb2_state = GPIO_GetPinValue(LOCK_INPUT_PORT, LOCK_INPUT_PIN);   /* RB2 */
    rd4_state = GPIO_GetPinValue(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN); /* RD4 */

    adc_value = ADC_ReadChannel(VOLTAGE_ADC_CHANNEL);                /* RA0 / AN0 */
}

/* ========================== UART SEND ==================================== */

static void Send_ADC_UART(void)
{
    /*
     * Same as:
     * UART1_Write(adc_value >> 8);
     * UART1_Write(adc_value & 0xFF);
     */

    UART_SendByte((u8)(adc_value >> 8));      /* High byte */
    UART_SendByte((u8)(adc_value & 0xFF));    /* Low byte */
}

/* ========================== OUTPUT LOGIC ================================= */

static void Apply_Output_Logic(void)
{
    /*
     * Logic copied from the correct behavior:
     *
     * RB1 HIGH  -> RD3 HIGH, RD0 HIGH, RD1 HIGH
     * RB2 HIGH  -> RD0 HIGH
     * RD4 HIGH  -> RD0 HIGH when RB1 = 0 and RB2 = 0
     */

    if((rb1_state == GPIO_HIGH) && (rb2_state == GPIO_LOW) && (rd4_state == GPIO_LOW))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_HIGH);       /* RD3 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);     /* RD0 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_HIGH);   /* RD1 */
    }

    if((rd4_state == GPIO_HIGH) && (rb2_state == GPIO_LOW) && (rb1_state == GPIO_LOW))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_LOW);        /* RD3 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_LOW);    /* RD1 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);     /* RD0 */
    }

    if((rb1_state == GPIO_LOW) && (rb2_state == GPIO_LOW) && (rd4_state == GPIO_LOW))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_LOW);        /* RD3 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_LOW);    /* RD1 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_LOW);      /* RD0 */
    }

    if((rb1_state == GPIO_LOW) && (rb2_state == GPIO_HIGH) && (rd4_state == GPIO_LOW))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_LOW);        /* RD3 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_LOW);    /* RD1 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);     /* RD0 */
    }

    if((rb1_state == GPIO_HIGH) && (rb2_state == GPIO_HIGH) && (rd4_state == GPIO_HIGH))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_HIGH);       /* RD3 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);     /* RD0 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_HIGH);   /* RD1 */
    }

    if((rb1_state == GPIO_HIGH) && (rb2_state == GPIO_HIGH) && (rd4_state == GPIO_LOW))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_HIGH);       /* RD3 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);     /* RD0 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_HIGH);   /* RD1 */
    }

    if((rb1_state == GPIO_LOW) && (rb2_state == GPIO_HIGH) && (rd4_state == GPIO_HIGH))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_LOW);        /* RD3 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);     /* RD0 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_LOW);    /* RD1 */
    }

    if((rb1_state == GPIO_HIGH) && (rb2_state == GPIO_LOW) && (rd4_state == GPIO_HIGH))
    {
        GPIO_SetPinValue(PIR_OUTPUT_PORT, PIR_OUTPUT_PIN, GPIO_HIGH);       /* RD3 */
        GPIO_SetPinValue(LOCK_OUTPUT_PORT, LOCK_OUTPUT_PIN, GPIO_HIGH);     /* RD0 */
        GPIO_SetPinValue(ALARM_OUTPUT_PORT, ALARM_OUTPUT_PIN, GPIO_HIGH);   /* RD1 */
    }

    /*
     * RA0 analog voltage:
     * if V < 1V  -> RD2 HIGH
     * if V >= 1V -> RD2 LOW
     */
    if(adc_value < VOLTAGE_1V_THRESHOLD)
    {
        GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_HIGH); /* RD2 */
    }
    else
    {
        GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT, VOLTAGE_OUTPUT_PIN, GPIO_LOW);  /* RD2 */
    }
}

/* ========================== APP TASK ===================================== */

static void App_Task(void)
{
    Read_Inputs();
    Send_ADC_UART();
    Apply_Output_Logic();

    Delay_ms(500);
}

/* ========================== MAIN ========================================= */

void main(void)
{
    System_Init();

    while(1)
    {
        App_Task();
    }
}
