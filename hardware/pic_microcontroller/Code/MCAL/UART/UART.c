/******************************************************************************
 * File:    UART.c
 * Author:  Embedded Systems Engineer
 * Date:    2026
 * Description: UART Driver Implementation for PIC16F877A
 *              Complete register-level implementation of UART driver
 * MCU:     PIC16F877A
 * Clock:   16MHz Crystal Oscillator
 * Compiler: mikroC PRO for PIC
 ******************************************************************************/

#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Config.h"

/******************************************************************************
 *                      UART INITIALIZATION
 ******************************************************************************/

/**
 * Function: UART_Init
 * Description: Initializes UART module with configured parameters
 *
 * Steps:
 * 1. Disable UART (clear SPEN) during configuration
 * 2. Configure baud rate generator (SPBRG register)
 * 3. Configure TXSTA register (TX settings, mode, speed)
 * 4. Configure RCSTA register (RX settings, serial port enable)
 * 5. Clear error flags
 * 6. Enable interrupts if configured
 */
void UART_Init(void)
{
    /* Step 1: Disable serial port during configuration */
    CLR_BIT(RCSTA, RCSTA_SPEN);

    /* Step 2: Set baud rate by loading SPBRG register */
    /* Formula: SPBRG = (Fosc / (baud_rate * divisor)) - 1 */
    /* Divisor = 64 (BRGH=0) or 16 (BRGH=1) for async mode */
    SPBRG = (u8)UART_SPBRG_VALUE;

    /* Step 3: Configure TXSTA Register */
    /* Clear TXSTA to reset all bits */
    TXSTA = 0x00;

    /* Set asynchronous mode (SYNC = 0) */
    #if (UART_MODE == UART_MODE_ASYNC)
        CLR_BIT(TXSTA, TXSTA_SYNC);     // Asynchronous mode
    #else
        SET_BIT(TXSTA, TXSTA_SYNC);     // Synchronous mode
        SET_BIT(TXSTA, TXSTA_CSRC);     // Master mode (internal clock)
    #endif

    /* Set baud rate speed (High or Low) */
    #if (UART_SPEED == UART_SPEED_HIGH)
        SET_BIT(TXSTA, TXSTA_BRGH);     // High speed mode
    #else
        CLR_BIT(TXSTA, TXSTA_BRGH);     // Low speed mode
    #endif

    /* Configure 8-bit or 9-bit transmission */
    #if (UART_DATA_BITS == UART_DATA_BITS_9)
        SET_BIT(TXSTA, TXSTA_TX9);      // 9-bit transmission
    #else
        CLR_BIT(TXSTA, TXSTA_TX9);      // 8-bit transmission
    #endif

    /* Enable transmitter */
    #if (UART_TX_ENABLE == 1)
        SET_BIT(TXSTA, TXSTA_TXEN);     // Enable transmitter
    #else
        CLR_BIT(TXSTA, TXSTA_TXEN);     // Disable transmitter
    #endif

    /* Step 4: Configure RCSTA Register */
    /* Clear RCSTA to reset all bits */
    RCSTA = 0x00;

    /* Configure 8-bit or 9-bit reception */
    #if (UART_DATA_BITS == UART_DATA_BITS_9)
        SET_BIT(RCSTA, RCSTA_RX9);      // 9-bit reception
    #else
        CLR_BIT(RCSTA, RCSTA_RX9);      // 8-bit reception
    #endif

    /* Enable continuous receive mode */
    #if (UART_RX_ENABLE == 1)
        #if (UART_CONT_RX_ENABLE == 1)
            SET_BIT(RCSTA, RCSTA_CREN); // Enable continuous receive
        #else
            CLR_BIT(RCSTA, RCSTA_CREN); // Disable continuous receive
        #endif
    #endif

    /* Enable serial port - This also configures RC6/TX and RC7/RX pins */
    SET_BIT(RCSTA, RCSTA_SPEN);         // Serial port enabled

    /* Step 5: Clear any existing errors */
    UART_ClearErrors();

    /* Step 6: Configure interrupts if enabled */
    #if (UART_INTERRUPT_ENABLE == 1)
        UART_EnableInterrupt();
    #endif

    /* Small delay to allow module to stabilize */
    Delay_ms(10);
}

/******************************************************************************
 *                      BASIC TRANSMIT FUNCTIONS
 ******************************************************************************/

/**
 * Function: UART_SendByte
 * Description: Transmits a single byte via UART
 *
 * Steps:
 * 1. Wait for transmit register to be empty (TXIF = 1)
 * 2. Load data into TXREG register
 * 3. TXIF flag is automatically cleared on TXREG write
 */
void UART_SendByte(u8 txData)
{
    /* Wait for transmit register to be empty */
    /* TXIF flag indicates TXREG is empty and ready for new data */
    while (!GET_BIT(PIR1, PIR1_TXIF))
    {
        /* Wait until TXIF is set */
    }

    /* Load data into transmit register */
    /* Writing to TXREG automatically clears TXIF flag */
    TXREG = txData;
}

/**
 * Function: UART_SendChar
 * Description: Sends a single character (alias for UART_SendByte)
 */
void UART_SendChar(char ch)
{
    UART_SendByte((u8)ch);
}

/**
 * Function: UART_SendString
 * Description: Transmits a null-terminated string
 *
 * Steps:
 * 1. Loop through string until null terminator
 * 2. Send each character using UART_SendByte
 */
void UART_SendString(const char* str)
{
    u8 i = 0;

    /* Check for null pointer */
    if (str == 0)
    {
        return;
    }

    /* Transmit characters until null terminator */
    while (str[i] != UART_NULL_CHAR)
    {
        UART_SendByte((u8)str[i]);
        i++;

        /* Safety check to prevent infinite loop */
        if (i >= 255)
        {
            break;
        }
    }
}

/**
 * Function: UART_SendNumber
 * Description: Converts unsigned integer to ASCII and transmits it
 *
 * Algorithm:
 * 1. Handle special case of zero
 * 2. Extract digits by repeated division by 10
 * 3. Store digits in reverse order
 * 4. Send digits in correct order
 */
void UART_SendNumber(u16 number)
{
    char buffer[6];     // Max 5 digits for u16 + null terminator
    u8 i = 0;

    /* Handle special case of zero */
    if (number == 0)
    {
        UART_SendByte('0');
        return;
    }

    /* Extract digits in reverse order */
    while (number > 0)
    {
        buffer[i] = (number % 10) + '0';    // Convert digit to ASCII
        number = number / 10;
        i++;
    }

    /* Send digits in correct order (reverse the buffer) */
    while (i > 0)
    {
        i--;
        UART_SendByte((u8)buffer[i]);
    }
}

/**
 * Function: UART_SendNewLine
 * Description: Sends carriage return and line feed
 */
void UART_SendNewLine(void)
{
    UART_SendByte(UART_CARRIAGE_RETURN);    // Send '\r'
    UART_SendByte(UART_NEWLINE);            // Send '\n'
}

/******************************************************************************
 *                      BASIC RECEIVE FUNCTIONS
 ******************************************************************************/

/**
 * Function: UART_ReceiveByte
 * Description: Receives a single byte via UART (blocking)
 *
 * Steps:
 * 1. Wait for receive flag to be set (RCIF = 1)
 * 2. Check for errors
 * 3. Read data from RCREG register
 * 4. RCIF flag is automatically cleared when RCREG is empty
 */
u8 UART_ReceiveByte(void)
{
    u8 rxData;

    /* Wait for data to be received */
    /* RCIF flag indicates data is available in RCREG */
    while (!GET_BIT(PIR1, PIR1_RCIF))
    {
        /* Wait until RCIF is set */
    }

    /* Check for errors before reading data */
    #if (UART_ERROR_DETECT == 1)
        if (UART_CheckErrors() != UART_OK)
        {
            /* Clear error and discard data */
            UART_ClearErrors();
            rxData = RCREG;   // Read to clear buffer
            return 0;
        }
    #endif

    /* Read received data */
    /* Reading RCREG clears RCIF if FIFO becomes empty */
    rxData = RCREG;

    return rxData;
}

/**
 * Function: UART_ReceiveChar
 * Description: Receives a single character (alias for UART_ReceiveByte)
 */
char UART_ReceiveChar(void)
{
    return (char)UART_ReceiveByte();
}

/**
 * Function: UART_ReceiveString
 * Description: Receives a string until newline or max length
 *
 * Steps:
 * 1. Receive characters one by one
 * 2. Store in buffer until newline or max length
 * 3. Null-terminate the string
 */
void UART_ReceiveString(char* buffer, u8 maxLength)
{
    u8 i = 0;
    char receivedChar;

    /* Check for null pointer */
    if (buffer == 0)
    {
        return;
    }

    /* Receive characters until newline or buffer full */
    while (i < (maxLength - 1))
    {
        receivedChar = (char)UART_ReceiveByte();

        /* Check for newline or carriage return */
        if ((receivedChar == UART_NEWLINE) ||
            (receivedChar == UART_CARRIAGE_RETURN))
        {
            break;
        }

        /* Store character in buffer */
        buffer[i] = receivedChar;
        i++;
    }

    /* Null-terminate the string */
    buffer[i] = UART_NULL_CHAR;
}

/******************************************************************************
 *                      STATUS CHECK FUNCTIONS
 ******************************************************************************/

/**
 * Function: UART_DataReady
 * Description: Checks if data is available in receive buffer
 *
 * Returns: 1 if data ready, 0 otherwise
 */
u8 UART_DataReady(void)
{
    /* Check RCIF flag in PIR1 register */
    return GET_BIT(PIR1, PIR1_RCIF);
}

/**
 * Function: UART_TxReady
 * Description: Checks if transmit shift register is empty
 *
 * Returns: 1 if TSR empty (transmission complete), 0 otherwise
 */
u8 UART_TxReady(void)
{
    /* Check TRMT flag in TXSTA register */
    /* TRMT = 1 means TSR is empty */
    return GET_BIT(TXSTA, TXSTA_TRMT);
}

/******************************************************************************
 *                      ERROR HANDLING FUNCTIONS
 ******************************************************************************/

/**
 * Function: UART_CheckErrors
 * Description: Checks for UART errors without clearing them
 *
 * Returns: Error code indicating type of error
 *
 * Error types:
 * - UART_OK: No error
 * - UART_ERROR_OVERRUN: Overrun error (OERR = 1)
 * - UART_ERROR_FRAMING: Framing error (FERR = 1)
 */
u8 UART_CheckErrors(void)
{
    /* Check for overrun error */
    /* OERR = 1 indicates receive buffer overflow */
    if (GET_BIT(RCSTA, RCSTA_OERR))
    {
        return UART_ERROR_OVERRUN;
    }

    /* Check for framing error */
    /* FERR = 1 indicates invalid stop bit */
    if (GET_BIT(RCSTA, RCSTA_FERR))
    {
        return UART_ERROR_FRAMING;
    }

    return UART_OK;
}

/**
 * Function: UART_ClearErrors
 * Description: Clears UART receive errors
 *
 * Returns: Error code that was present before clearing
 *
 * Overrun Error Recovery:
 * 1. Clear CREN bit to reset receive logic
 * 2. Read RCREG to clear FIFO
 * 3. Set CREN bit to re-enable receiver
 *
 * Framing Error Recovery:
 * 1. Read RCREG to clear error flag
 */
u8 UART_ClearErrors(void)
{
    u8 errorCode = UART_OK;
    u8 dummyRead;

    /* Check and clear overrun error */
    if (GET_BIT(RCSTA, RCSTA_OERR))
    {
        errorCode = UART_ERROR_OVERRUN;

        /* Clear overrun error by resetting CREN */
        CLR_BIT(RCSTA, RCSTA_CREN);     // Disable receiver
        dummyRead = RCREG;               // Read to clear buffer
        dummyRead = RCREG;               // Read again (double buffered)
        SET_BIT(RCSTA, RCSTA_CREN);     // Re-enable receiver
    }

    /* Check and clear framing error */
    if (GET_BIT(RCSTA, RCSTA_FERR))
    {
        errorCode = UART_ERROR_FRAMING;

        /* Clear framing error by reading RCREG */
        dummyRead = RCREG;
    }

    /* Suppress unused variable warning */
    (void)dummyRead;

    return errorCode;
}

/**
 * Function: UART_Flush
 * Description: Flushes the receive buffer
 *
 * Steps:
 * 1. Read RCREG until no more data available
 * 2. Clear any error flags
 */
void UART_Flush(void)
{
    u8 dummyRead;

    /* Read all data in receive buffer */
    while (GET_BIT(PIR1, PIR1_RCIF))
    {
        dummyRead = RCREG;
    }

    /* Clear any errors */
    UART_ClearErrors();

    /* Suppress unused variable warning */
    (void)dummyRead;
}

/******************************************************************************
 *                      INTERRUPT FUNCTIONS (OPTIONAL)
 ******************************************************************************/

#if (UART_INTERRUPT_ENABLE == 1)

/**
 * Function: UART_EnableInterrupt
 * Description: Enables UART interrupts
 *
 * Steps:
 * 1. Enable peripheral interrupts (PEIE)
 * 2. Enable global interrupts (GIE)
 * 3. Enable TX/RX interrupts as configured
 */
void UART_EnableInterrupt(void)
{
    /* Enable peripheral interrupts */
    SET_BIT(INTCON, INTCON_PEIE);

    /* Enable global interrupts */
    SET_BIT(INTCON, INTCON_GIE);

    /* Enable TX interrupt if configured */
    #if (UART_TX_INT_ENABLE == 1)
        SET_BIT(PIE1, PIE1_TXIE);
    #endif

    /* Enable RX interrupt if configured */
    #if (UART_RX_INT_ENABLE == 1)
        SET_BIT(PIE1, PIE1_RCIE);
    #endif
}

/**
 * Function: UART_DisableInterrupt
 * Description: Disables UART interrupts
 */
void UART_DisableInterrupt(void)
{
    /* Disable TX interrupt */
    CLR_BIT(PIE1, PIE1_TXIE);

    /* Disable RX interrupt */
    CLR_BIT(PIE1, PIE1_RCIE);
}

#endif /* UART_INTERRUPT_ENABLE */

/******************************************************************************
 *                      END OF FILE
 ******************************************************************************/