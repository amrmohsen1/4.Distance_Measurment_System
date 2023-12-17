/**************************************
 * Module: ICU
 * File name: icu.c
 * Description: source file for the AVR ICU driver
 * Author: amr mohsen
 *************************************/
#include <avr\io.h>
#include "icu.h"
#include "common_macros.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/

/* Global pointer to function to hold the address of the call back function in the application */

static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*******************************************************************************
 *                         Interrupt Service routines                          *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}


/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/
/*
 * Description :
 * 1. Set the required clock.
 * 2. Set the required edge detection.
 * 3. Enable the input capture unit
 * 4. initialize timer1 registers.
 */
void ICU_init(const ICU_ConfigType *Config_Ptr)
{
	/* Configure ICP1/PD6  as input pin */
	DDRD&=~(1<<6);

	/* Timer1 always operate on normal mode */
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);

	/* insert the required CLOCK in first 3 bits in TCCR1B register */
	TCCR1B=(TCCR1B & 0xF8) | (Config_Ptr->clock);

	/* insert the required edge type in ICES1 bit ( Bit 6 ) in TCCR1B register */
	TCCR1B=(TCCR1B & 0xBF)| ((Config_Ptr->edge)<<6);


	/* initial value of Timer1 */
	TCNT1=0;

	/* initial value Input Capture Register */
	ICR1=0;

	/* Enable the input Capture interrupt to generate interrupt when edge is detected on ICP1/PD6 */
	/* TIMSK|=(1<<5); */
	SET_BIT(TIMSK,TICIE1);
}

/*
 * Description : Function to set the Call Back Function address.
 */
void ICU_setCallBack(void (*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}

/*
 * Description : Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	/* insert the required edge type in ICES1 bit ( Bit 6 ) in TCCR1B register */
	TCCR1B=(TCCR1B & 0xBF)| (a_edgeType<<6);
}

/*
 * Description : Function to get the Timer1 value when the input is captured
 *               where the value is stored in Input Captured Register ICR1
 */
uint16 ICU_getInputCapturedValue(void)
{
	return ICR1;
}

/*
 * Description : Function to clear Timer1 value to start count from zero.
 */
void ICU_clearTimerValue(void)
{
	TCNT1=0;
}

/*
 * Description : Function to disable Timer1 and stop ICU driver.
 */
void ICU_deinit(void)
{
	/* Clear all Timer1 registers */
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	ICR1=0;

	/* Disable the Input Capture interrupt */
	TIMSK&=~(1<<TICIE1);

	/* Reset tge global pointer value */
	g_callBackPtr=NULL_PTR;
}


