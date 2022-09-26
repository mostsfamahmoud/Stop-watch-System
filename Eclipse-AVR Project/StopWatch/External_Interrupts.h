/******************************************************************************
 * Module: External Interrupts
 * File Name: External_Interrupts.h
 * Description: Header file for The Eta32mini External Interrupts Driver.
 * Author: Mostafa Mahmoud
 * Group:  71
 * Created on: Sep 15, 2022
 *******************************************************************************/

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_

#include "gpio.h"
#include "avr/interrupt.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define I_BIT   7

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* External INT0 enable and configuration function */
void INT0_Init(void);

/* External INT1 enable and configuration function */
void INT1_Init(void);

/* External INT2 enable and configuration function */
void INT2_Init(void);


#endif /* EXTERNAL_INTERRUPTS_H_ */
