/******************************************************************************
 * Module: StopWatch Main file
 * File Name: StopWatch.c
 * Description: Source file for The Stop Watch Main File.
 * Author: Mostafa Mahmoud
 * Group:  71
 * Created on: Sep 15, 2022
 *******************************************************************************/

#include <util/delay.h>
#include "gpio.h"
#include "External_Interrupts.h"

/*******************************************************************************
 *                               GLOBAL VARIABLES                              *
 *******************************************************************************/

uint8_t g_Sec = 0;       /* Global variable that represent Seconds count */
uint8_t g_Min = 0;       /* Global variable that represent Minutes count */
uint8_t g_Hour = 0;      /* Global variable that represent Hours count */

/* Volatile --> To Stop Compiler Optimization as (flag is set by hardware event)
 * Flag to be Set if Timer1 interrupt is triggered
 */
volatile uint8_t g_Interrupt_Flag = 0;


/*******************************************************************************
 *                           FUNCTIONS PROTOTYPES                              *
 *******************************************************************************/

void Timer1_CTC_Init(void);
void StopWatch_Multiplexing_Mode(void);
void StopWatch_TimeProcessing(void);
void resetDigits(void);

/*******************************************************************************
 *                                MAIN FUNCTION                                *
 *******************************************************************************/

int main(void)
{
	GPIO_setPortDirection(PORTA_ID, 0x3F); /* Configure (PA0 ... PA5) as O/P pins (Control of the 7 Segment) */

	GPIO_setPortDirection(PORTC_ID, 0x0F); /* Configure (PC0 ... PC3) as O/P pins */

	Timer1_CTC_Init();    /* Initialize TIMER1 Compare mode */

	INT0_Init();          /* Initialize INT0 as RESET interrupt */
	INT1_Init();          /* Initialize INT1 as PAUSE interrupt */
	INT2_Init();          /* Initialize INT2 as RESUME interrupt */

	SET_BIT(SREG, I_BIT); /* Enable global interrupts in MC by setting I-bit */

	while (1)
	{
		StopWatch_Multiplexing_Mode();

		if (g_Interrupt_Flag == 1)
		{
			StopWatch_TimeProcessing();

			g_Interrupt_Flag = 0;     /* Clear flag to be Set when timer interrupt is triggered again */
		}
	}

	return 0;
}

/*******************************************************************************
 *                            FUNCTIONS DEFINITIONS                            *
 *******************************************************************************/

void Timer1_CTC_Init(void)
{
	TCNT1 = 0;              /* Set timer1 initial count to zero */

	OCR1A = 977;            /* Set the Compare value to 977 ( To tigger an interrupt each second ) */

	TIMSK = (1 << OCIE1A);  /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A:
	 * 1. Clear OC1A/OC1B on compare match (Set output to low level)
	      COM1A1=1 COM1A0=0 COM1B0=0 COM1B1=1

	 * 2. FOC1A=1 FOC1B=0
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1 << FOC1A) | (1 << COM1A1);

	/* Configure timer control register TCCR1B:
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/1024
	      CS10=1 CS11=0 CS12=1
	 */
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
}

/* Function that implement the Multiplexing Mode.
 * Description:
 * One 7-segment display is driven by the Microcontroller at a time and the rest are OFF.
 * It keeps switching the displays using transistors.
 */
void StopWatch_Multiplexing_Mode(void)
{
	/* To get first digit of Seconds , Use g_Sec % 10
	 * To get second digit of Seconds , Use g_Sec / 10
	 * That technique is also applied on g_Min , g_Hour
	 */
	uint8_t timeDigits[] = {(g_Sec % 10),(g_Sec / 10),
			                (g_Min % 10),(g_Min / 10),
			                (g_Hour % 10),(g_Hour / 10)};      /* Array that contains the Stop-Watch digits */

	for(uint8_t count = 0; count < 6; count++)
	{

		PORTA = (1 << count);        /* Enable All 7-Segments (one at a time) */

		/* First:  Clearing the display each iteration
		 * Second: Displaying the corresponding count in the enabled 7-Segment
		 */
		PORTC = (PORTC & 0xF0) | timeDigits[count];

		_delay_ms(4);     /* Delay between each 7-segment enable to make the Stop-Watch display looks normal */
	}
}

void StopWatch_TimeProcessing(void)
{
	/* Check if Seconds exceeded the range (0 --> 59) or not */
	if (g_Sec == 59)
	{
		g_Sec = 0;       /* Clear Seconds if exceeded */
		g_Min++;         /* Increment Mintues */
	}
	else
		g_Sec++;         /* Increment Seconds if not exceeded */

	/* Check if Mintues exceeded the range (0 --> 59) or not */
	if (g_Min > 59)
	{
		g_Min = 0;      /* Clear Mintues if exceeded */
		g_Hour++;       /* Increment Hours */
	}

	/* Check if Hours exceeded the range (0 --> 23 in one day) or not */
	if (g_Hour > 23)
	{
		g_Hour = 0;    /* Clear Hours if exceeded */
		               /* This case is like a Reset operation when overflow occurs in Stop-Watch timer */
	}
}

/* Function to reset all Stop-Watch Digits */
void resetDigits(void)
{
	g_Sec = 0;
	g_Min = 0;
	g_Hour = 0;
}


/*******************************************************************************
 *                          INTERRUPT SERVICE ROUTINES                         *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	g_Interrupt_Flag = 1;    /* Set this global interrupt flag as an indication of Timer1 interrupt */
}


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
