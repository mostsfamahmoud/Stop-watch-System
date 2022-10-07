/******************************************************************************
 * Module: External Interrupts
 * File Name: External_Interrupts.c
 * Description: Source file for The Eta32mini External Interrupts Driver.
 * Author: Mostafa Mahmoud
 * Group:  71
 * Created on: Sep 15, 2022
 *******************************************************************************/

#include "External_Interrupts.h"

/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/

/* External INT0 enable and configuration function */
void INT0_Init(void)
{
	GPIO_setPinDirection(PORTD_ID, PD2, PIN_INPUT);   /* Configure INT0/PD2 as I/P pin */
	GPIO_enablePullUp(PORTD_ID, PD2, PULL_UP);        /* Enable Internal Pull Up resistor of PB2 */

	/* Trigger INT0 with the falling edge (ISC01 = 1 , ISC00 = 0) */
	SET_BIT(MCUCR,ISC01);
	CLEAR_BIT(MCUCR,ISC00);

	SET_BIT(GICR,INT0);      /* Enable external interrupt pin INT0 */
}



/* External INT1 enable and configuration function */
void INT1_Init(void)
{
	GPIO_setPinDirection(PORTD_ID, PD3, PIN_INPUT);   /* Configure INT1/PD3 as I/P pin */

	/* Trigger INT1 with the rising edge (ISC11 = 1 , ISC10 = 1) */
	SET_BIT(MCUCR,ISC11);
	SET_BIT(MCUCR,ISC10);

	SET_BIT(GICR,INT1);      /* Enable external interrupt pin INT1 */
}



/* External INT2 enable and configuration function */
void INT2_Init(void)
{
	GPIO_setPinDirection(PORTB_ID, PB2, PIN_INPUT);   /* Configure INT2/PB2 as I/P pin */
	GPIO_enablePullUp(PORTB_ID, PB2, PULL_UP);        /* Enable Internal Pull Up resistor of PB2 */

	/* Trigger INT2 with the falling edge (ISC2 = 0) */
	CLEAR_BIT(MCUCSR,ISC2);

	SET_BIT(GICR,INT2);      /* Enable external interrupt pin INT2 */
}


/*******************************************************************************
 *                          INTERRUPT SERVICE ROUTINES                         *
 *******************************************************************************/

/* INT0 (ISR) that is responsible for RESET the Stop-Watch timer */
ISR(INT0_vect)
{
	resetDigits();       /* Reset all Stop-Watch digits to start from the beginning again */

	PORTC &= 0xF0;       /* Clear all 7-Segment displays */

	_delay_ms(30);       /* Just a 30ms delay due to Button-debouncing */
}


/* INT1 (ISR) that is responsible for PAUSE the Stop-Watch timer */
ISR(INT1_vect)
{
	/* Configure timer control register TCCR1B:
	 * No clock source (Timer/Counter stopped)
	      CS10=0 CS11=0 CS12=0
	 */
	CLEAR_BIT(TCCR1B,CS10);
	CLEAR_BIT(TCCR1B,CS11);
	CLEAR_BIT(TCCR1B,CS12);
}


/* INT2 (ISR) that is responsible for RESUME the Stop-Watch timer if it is paused */
ISR(INT2_vect)
{
	/* Configure timer control register TCCR1B:
	 * Clock Source ON again (F_CLK/1024 (From prescaler))
	      CS10=1 CS11=0 CS12=1
	 */

	/* Check if bit (CS10) in register (TCCR1B) is cleared or not */
	if (BIT_IS_CLEAR(TCCR1B,CS10))
	{
		SET_BIT(TCCR1B,CS10);
	}

	/* Check if bit (CS12) in register (TCCR1B) is cleared or not */
	if (BIT_IS_CLEAR(TCCR1B,CS12))
	{
		SET_BIT(TCCR1B,CS12);
	}
}




