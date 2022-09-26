
/******************************************************************************
 * Module: GPIO
 * File Name: gpio.c
 * Description: Source file for The Eta32mini GPIO Driver.
 * Author: Mostafa Mahmoud
 * Group:  71
 * Created on: Sep 14, 2022
 *******************************************************************************/

#include "gpio.h"

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/


/*
 * Description :
 * Setup the direction of the required Port.
 * Register(s) : DDRx where x is PORT_NAME.
 * If the input port number ,The function will not handle the request.
 */
void GPIO_setPortDirection(uint8_t portNum, uint8_t direction)
{
	if (portNum >= NUM_OF_PORTS) {
		/* Do Nothing */
		return;
	}

	switch (portNum)
	{
	case PORTA_ID:
		DDRA |= direction;
		break;
	case PORTB_ID:
		DDRB |= direction;
		break;
	case PORTC_ID:
		DDRC |= direction;
		break;
	case PORTD_ID:
		DDRD |= direction;
		break;
	}
}


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * Register(s) : DDRx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setPinDirection(uint8_t portNum, uint8_t pinNum, GPIO_PinDirectionType direction)
{

    if ((pinNum >= NUM_OF_PINS_PER_PORT) || (portNum >= NUM_OF_PORTS))
    {
        /* Do Nothing */
        return;
    }

    if (direction == PIN_OUTPUT)
    {
        switch (portNum)
        {
        case PORTA_ID:
            SET_BIT(DDRA, pinNum);
            break;
        case PORTB_ID:
            SET_BIT(DDRB, pinNum);
            break;
        case PORTC_ID:
            SET_BIT(DDRC, pinNum);
            break;
        case PORTD_ID:
            SET_BIT(DDRD, pinNum);
            break;
        }
    }
    else if (direction == PIN_INPUT)
    {
        switch (portNum)
        {
        case PORTA_ID:
            CLEAR_BIT(DDRA, pinNum);
            break;
        case PORTB_ID:
            CLEAR_BIT(DDRB, pinNum);
            break;
        case PORTC_ID:
            CLEAR_BIT(DDRC, pinNum);
            break;
        case PORTD_ID:
            CLEAR_BIT(DDRD, pinNum);
            break;
        }
    }
    else
        return;
}


/*
 * Description :
 * Read the value of the required pin ( 1 or 0 ).
 * Register(s) : PINx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will return an error value (0xFF).
 */
uint8_t GPIO_readPin(uint8_t portNum, uint8_t pinNum)
{

    if ((pinNum >= NUM_OF_PINS_PER_PORT) || (portNum >= NUM_OF_PORTS))
    {
        return ERROR_VALUE;
    }

    switch (portNum)
    {
    case PORTA_ID:
        return GET_BIT(PINA, pinNum);

    case PORTB_ID:
        return GET_BIT(PINB, pinNum);

    case PORTC_ID:
        return GET_BIT(PINC, pinNum);

    case PORTD_ID:
        return GET_BIT(PIND, pinNum);
    }
    return 0;
}


/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_writePin(uint8_t portNum, uint8_t pinNum, uint8_t data)
{

    if ((pinNum >= NUM_OF_PINS_PER_PORT) || (portNum >= NUM_OF_PORTS))
    {
        return;
    }

    if(data == LOGIC_HIGH)
    {
        switch (portNum)
        {
        case PORTA_ID:
            SET_BIT(PORTA, pinNum);
            break;
        case PORTB_ID:
            SET_BIT(PORTB, pinNum);
            break;
        case PORTC_ID:
            SET_BIT(PORTC, pinNum);
            break;
        case PORTD_ID:
            SET_BIT(PORTD, pinNum);
            break;
        }
    }
    else if(data == LOGIC_LOW)
    {
        switch (portNum)
        {
        case PORTA_ID:
            CLEAR_BIT(PORTA, pinNum);
            break;
        case PORTB_ID:
            CLEAR_BIT(PORTB, pinNum);
            break;
        case PORTC_ID:
            CLEAR_BIT(PORTC, pinNum);
            break;
        case PORTD_ID:
            CLEAR_BIT(PORTD, pinNum);
            break;
        }
    }
    else
    	return;
}

/*
 * Description :
 * Enables the internal resistance of the specified I/P pin in the required port.
 * Internal pull up configuration are supported.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_enablePullUp(uint8_t portNum, uint8_t pinNum, GPIO_PinInternalResistance res)
{
    if ((pinNum >= NUM_OF_PINS_PER_PORT) || (portNum >= NUM_OF_PORTS))
    {
        /* Do Nothing */
        return;
    }

    if (res == PULL_UP)
    {
        switch (portNum)
        {
        case PORTA_ID:
            SET_BIT(PORTA, pinNum);
            break;
        case PORTB_ID:
            SET_BIT(PORTB, pinNum);
            break;
        case PORTC_ID:
            SET_BIT(PORTC, pinNum);
            break;
        case PORTD_ID:
            SET_BIT(PORTD, pinNum);
            break;
        }
    }
    else
        return;

}


/*
 * Description :
 * Write the given value on the desired port.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8_t portNum, uint8_t value)
{
    if (portNum >= NUM_OF_PORTS)
    {
        /* Do Nothing */
        return;
    }

    switch (portNum)
    {
    case PORTA_ID:
        PORTA = value;
        break;
    case PORTB_ID:
        PORTB = value;
        break;
    case PORTC_ID:
        PORTC = value;
        break;
    case PORTD_ID:
        PORTD = value;
        break;
    }
}


/*
 * Description :
 * Set specific bits in the desired port (Insertion) --> by writing 1 to each of them.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setSpecificBits(uint8_t portNum, uint8_t value)
{
    if (portNum >= NUM_OF_PORTS)
    {
        /* Do Nothing */
        return;
    }

    switch (portNum)
    {
    case PORTA_ID:
        PORTA |= value;
        break;
    case PORTB_ID:
        PORTB |= value;
        break;
    case PORTC_ID:
        PORTC |= value;
        break;
    case PORTD_ID:
        PORTD |= value;
        break;
    }
}


/*
 * Description :
 * Delete specific bits in the desired port (Deletion) --> by writing 0 to each of them.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_deleteSpecificBits(uint8_t portNum, uint8_t value)
{
    if (portNum >= NUM_OF_PORTS)
    {
        /* Do Nothing */
        return;
    }

    switch (portNum)
    {
    case PORTA_ID:
        PORTA &= value;
        break;
    case PORTB_ID:
        PORTB &= value;
        break;
    case PORTC_ID:
        PORTC &= value;
        break;
    case PORTD_ID:
        PORTD &= value;
        break;
    }
}


/*
 * Description :
 * Reads the current value of the desired port.
 * Register(s) : PINx where x is PORT_NAME.
 * If the input port number is not correct, The function will return an error value (0xFF).
 */
uint8_t GPIO_readPort(uint8_t portNum)
{
    if (portNum >= NUM_OF_PORTS)
    {
        /* Do Nothing */
        return ERROR_VALUE;
    }

    switch (portNum)
    {
    case PORTA_ID:
        return PINA & 0xFF;

    case PORTB_ID:
        return PINB & 0xFF;

    case PORTC_ID:
        return PINC & 0xFF;

    case PORTD_ID:
        return PIND & 0xFF;
    }
		return 0;
}




