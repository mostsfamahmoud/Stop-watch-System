/******************************************************************************
 * Module: GPIO
 * File Name: gpio.h
 * Description: Header file for The Eta32mini GPIO Driver.
 * Author: Mostafa Mahmoud
 * Group:  71
 * Created on: Sep 14, 2022
 *******************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include "Macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_PORTS 			4
#define NUM_OF_PINS_PER_PORT 	8

// To Select Between PORTs (PORT NUM)

#define PORTA_ID         0
#define PORTB_ID         1
#define PORTC_ID         2
#define PORTD_ID         3

#define LOGIC_HIGH       1
#define LOGIC_LOW        0

#define ERROR_VALUE      0xFF

typedef unsigned char uint8_t;


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	 PIN_INPUT, PIN_OUTPUT

}GPIO_PinDirectionType;

typedef enum{

	NONE , PULL_UP

}GPIO_PinInternalResistance;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/*
 * Description :
 * Setup the direction of the required Port.
 * Register(s) : DDRx where x is PORT_NAME.
 * If the input port number ,The function will not handle the request.
 */
void GPIO_setPortDirection(uint8_t portNum, uint8_t direction);


/*
 * Description :
 * Setup the direction of the required pin input/output.
 * Register(s) : DDRx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setPinDirection(uint8_t portNum, uint8_t pinNum, GPIO_PinDirectionType direction);


/*
 * Description :
 * Read the value of the required pin ( 1 or 0 ).
 * Register(s) : PINx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will return an error value (0xFF).
 */
uint8_t GPIO_readPin(uint8_t portNum, uint8_t pinNum);


/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_writePin(uint8_t portNum, uint8_t pinNum, uint8_t data);


/*
 * Description :
 * Enables the internal resistance of the specified I/P pin in the required port.
 * Internal pull up configuration are supported.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_enablePullUp(uint8_t portNum, uint8_t pinNum, GPIO_PinInternalResistance res);


/*
 * Description :
 * Write the given value on the desired port.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8_t portNum, uint8_t value);


/*
 * Description :
 * Set specific bits in the desired port (Insertion) --> by writing 1 to each of them.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setSpecificBits(uint8_t portNum, uint8_t value);


/*
 * Description :
 * Delete specific bits in the desired port (Deletion) --> by writing 0 to each of them.
 * Register(s) : PORTx where x is PORT_NAME.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_deleteSpecificBits(uint8_t portNum, uint8_t value);


/*
 * Description :
 * Reads the current value of the desired port.
 * Register(s) : PINx where x is PORT_NAME.
 * If the input port number is not correct, The function will return an error value (0xFF).
 */
uint8_t GPIO_readPort(uint8_t portNum);



#endif /* GPIO_H_ */

