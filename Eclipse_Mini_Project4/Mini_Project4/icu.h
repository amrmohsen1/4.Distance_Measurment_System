/**************************************
 * Module: ICU
 * File name: icu.h
 * Description: header file for the AVR ICU driver
 * Author: amr mohsen
 *************************************/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/***************************************************
 *                  Types Declaration              *
 ***************************************************/
typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024

}ICU_ClockType;

typedef enum
{
	FALLING,RAISING

}ICU_EdgeType;

typedef struct
{
	ICU_ClockType clock;
	ICU_EdgeType edge;

}ICU_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * 1. Set the required clock.
 * 2. Set the required edge detection.
 * 3. Enable the input capture unit
 * 4. initialize timer1 registers.
 */
void ICU_init(const ICU_ConfigType *Config_Ptr);

/*
 * Description : Function to set the Call Back Function address.
 */
void ICU_setCallBack(void (*a_ptr)(void));

/*
 * Description : Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeType edgeType);

/*
 * Description : Function to get the Timer1 value when the input is captured
 *               where the value is stored in Input Captured Register ICR1
 */
uint16 ICU_getInputCapturedValue(void);

/*
 * Description : Function to clear Timer1 value to start count from zero.
 */
void ICU_clearTimerValue(void);

/*
 * Description : Function to disable Timer1 and stop ICU driver.
 */
void ICU_deinit(void);

#endif /* ICU_H_ */
