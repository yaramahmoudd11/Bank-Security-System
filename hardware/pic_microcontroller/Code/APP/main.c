/******************************************************************************
* @file main.c
* @brief PIC16F877A Security + Voltage Control - Driver Format
* @target PIC16F877A
******************************************************************************/

#include "../MCAL/GPIO/GPIO_interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/UART/UART_Interface.h"

#include "../HAL/LED/LED_interface.h"
#include "../HAL/SWITCH/SWITCH_interface.h"

#include "../SERVICES/STD_TYPES.h"

/* ========================== PIN MAPPING ================================== */

/* ADC */
#define VOLTAGE_ADC_CHANNEL          ADC_CHANNEL_0     /* RA0 / AN0 */

/*
 * ADC Reference = 5V
 * 1V => (1 / 5) * 1023 = 204.6
 * ADC values 0..204 are below 1V
 */
#define VOLTAGE_1V_THRESHOLD_ADC     205U

/* Inputs */
#define PIR_INPUT_PORT               GPIO_PORTB
#define PIR_INPUT_PIN                GPIO_PIN1         /* RB1 */

#define LOCK_INPUT_PORT              GPIO_PORTB
#define LOCK_INPUT_PIN               GPIO_PIN2         /* RB2 */

#define EXTRA_INPUT_PORT             GPIO_PORTD
#define EXTRA_INPUT_PIN              GPIO_PIN4         /* RD4 */

#define VOLTAGE_INPUT_PORT           GPIO_PORTA
#define VOLTAGE_INPUT_PIN            GPIO_PIN0         /* RA0 / AN0 */

/* Outputs */
#define LOCK_OUTPUT_PORT             GPIO_PORTD
#define LOCK_OUTPUT_PIN              GPIO_PIN0         /* RD0 */

#define ALARM_OUTPUT_PORT            GPIO_PORTD
#define ALARM_OUTPUT_PIN             GPIO_PIN1         /* RD1 */

#define VOLTAGE_OUTPUT_PORT          GPIO_PORTD
#define VOLTAGE_OUTPUT_PIN           GPIO_PIN2         /* RD2 */

#define PIR_LED_PORT                 GPIO_PORTD
#define PIR_LED_PIN                  GPIO_PIN3         /* RD3 */

/* UART pins */
#define UART_TX_PORT                 GPIO_PORTC
#define UART_TX_PIN                  GPIO_PIN6         /* RC6 / TX */

#define UART_RX_PORT                 GPIO_PORTC
#define UART_RX_PIN                  GPIO_PIN7         /* RC7 / RX */

/* ========================== GLOBAL VARIABLES ============================= */

static u8  rb1_state = 0;
static u8  rb2_state = 0;
static u8  rd4_state = 0;
static u16 adc_value = 0;

/* ========================== FUNCTION PROTOTYPES =========================== */

static void System_Init(void);
static void Read_Inputs(void);
static void Apply_Output_Logic(void);
static void Send_ADC_UART(void);

/* ========================== MAIN ========================================= */

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

/* ========================== SYSTEM INIT ================================== */

static void System_Init(void)
{
    /* ================= Inputs ================= */

    SWITCH_Init(PIR_INPUT_PORT, PIR_INPUT_PIN);       /* RB1 input */
    SWITCH_Init(LOCK_INPUT_PORT, LOCK_INPUT_PIN);     /* RB2 input */
    SWITCH_Init(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN);   /* RD4 input */

    GPIO_SetPinDirection(VOLTAGE_INPUT_PORT,
                         VOLTAGE_INPUT_PIN,
                         GPIO_INPUT);                 /* RA0 / AN0 input */

    /* ================= Outputs ================ */

    GPIO_SetPinDirection(LOCK_OUTPUT_PORT,
                         LOCK_OUTPUT_PIN,
                         GPIO_OUTPUT);                /* RD0 output */

    GPIO_SetPinDirection(ALARM_OUTPUT_PORT,
                         ALARM_OUTPUT_PIN,
                         GPIO_OUTPUT);                /* RD1 output */

    GPIO_SetPinDirection(VOLTAGE_OUTPUT_PORT,
                         VOLTAGE_OUTPUT_PIN,
                         GPIO_OUTPUT);                /* RD2 output */

    LED_Init(PIR_LED_PORT, PIR_LED_PIN);              /* RD3 LED only */

    /* ================= UART Pins =============== */

    GPIO_SetPinDirection(UART_TX_PORT,
                         UART_TX_PIN,
                         GPIO_OUTPUT);                /* RC6 / TX */

    GPIO_SetPinDirection(UART_RX_PORT,
                         UART_RX_PIN,
                         GPIO_INPUT);                 /* RC7 / RX */

    /* ================= Initial States ========== */

    GPIO_SetPinValue(LOCK_OUTPUT_PORT,
                     LOCK_OUTPUT_PIN,
                     GPIO_LOW);                       /* RD0 LOW */

    GPIO_SetPinValue(ALARM_OUTPUT_PORT,
                     ALARM_OUTPUT_PIN,
                     GPIO_LOW);                       /* RD1 LOW */

    GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT,
                     VOLTAGE_OUTPUT_PIN,
                     GPIO_LOW);                       /* RD2 LOW */

    LED_Off(PIR_LED_PORT, PIR_LED_PIN);               /* RD3 LOW */

    /* ================= Drivers Init ============ */

    ADC_Init();
    UART_Init();
}

/* ========================== READ INPUTS ================================== */

static void Read_Inputs(void)
{
    rb1_state = SWITCH_GetState(PIR_INPUT_PORT, PIR_INPUT_PIN);
    rb2_state = SWITCH_GetState(LOCK_INPUT_PORT, LOCK_INPUT_PIN);
    rd4_state = SWITCH_GetState(EXTRA_INPUT_PORT, EXTRA_INPUT_PIN);

    adc_value = ADC_ReadChannel(VOLTAGE_ADC_CHANNEL);
}

/* ========================== APPLY LOGIC ================================== */

static void Apply_Output_Logic(void)
{
    /*
     * Same original logic:
     *
     * If RB1 = 1:
     *      RD3 = HIGH
     *      RD0 = HIGH
     *      RD1 = HIGH
     *
     * Else if RB2 = 1 OR RD4 = 1:
     *      RD3 = LOW
     *      RD0 = HIGH
     *      RD1 = LOW
     *
     * Else:
     *      RD3 = LOW
     *      RD0 = LOW
     *      RD1 = LOW
     */

    if(rb1_state == GPIO_HIGH)
    {
        LED_On(PIR_LED_PORT, PIR_LED_PIN);                         /* RD3 */

        GPIO_SetPinValue(LOCK_OUTPUT_PORT,
                         LOCK_OUTPUT_PIN,
                         GPIO_HIGH);                               /* RD0 */

        GPIO_SetPinValue(ALARM_OUTPUT_PORT,
                         ALARM_OUTPUT_PIN,
                         GPIO_HIGH);                               /* RD1 */
    }
    else if((rb2_state == GPIO_HIGH) || (rd4_state == GPIO_HIGH))
    {
        LED_Off(PIR_LED_PORT, PIR_LED_PIN);                        /* RD3 */

        GPIO_SetPinValue(LOCK_OUTPUT_PORT,
                         LOCK_OUTPUT_PIN,
                         GPIO_HIGH);                               /* RD0 */

        GPIO_SetPinValue(ALARM_OUTPUT_PORT,
                         ALARM_OUTPUT_PIN,
                         GPIO_LOW);                                /* RD1 */
    }
    else
    {
        LED_Off(PIR_LED_PORT, PIR_LED_PIN);                        /* RD3 */

        GPIO_SetPinValue(LOCK_OUTPUT_PORT,
                         LOCK_OUTPUT_PIN,
                         GPIO_LOW);                                /* RD0 */

        GPIO_SetPinValue(ALARM_OUTPUT_PORT,
                         ALARM_OUTPUT_PIN,
                         GPIO_LOW);                                /* RD1 */
    }

    /*
     * Voltage logic:
     * ADC < 205  => RA0 voltage < 1V  => RD2 HIGH
     * ADC >= 205 => RA0 voltage >= 1V => RD2 LOW
     */

    if(adc_value < VOLTAGE_1V_THRESHOLD_ADC)
    {
        GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT,
                         VOLTAGE_OUTPUT_PIN,
                         GPIO_HIGH);                               /* RD2 */
    }
    else
    {
        GPIO_SetPinValue(VOLTAGE_OUTPUT_PORT,
                         VOLTAGE_OUTPUT_PIN,
                         GPIO_LOW);                                /* RD2 */
    }
}

/* ========================== UART SEND ==================================== */

static void Send_ADC_UART(void)
{
    /*
     * Send ADC value as 2 binary bytes:
     * First byte  = high byte
     * Second byte = low byte
     */

    UART_SendByte((u8)(adc_value >> 8));
    UART_SendByte((u8)(adc_value & 0xFF));
}