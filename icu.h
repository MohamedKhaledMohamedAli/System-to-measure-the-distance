 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for the AVR ICU driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ICU_PORT_ID PORTD_ID
#define ICU_PIN_ID  PIN6_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* enum for all selection options for Input Capture Edge Select */
typedef enum{
	FALLING_EDGE, RISING_EDGE
}Icu_Clock;

/* enum for all selection options for Timer1 prescaler */
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Icu_EdgeType;

/* Structure that contain members to set the configurations of ICU */
typedef struct{
	Icu_EdgeType edgeSelect;
	Icu_Clock clockSelect;
}Icu_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize ICU:
 * 1. Configure Timer1 to Normal Mode
 * 2. Select ICU Edge Select
 * 3. Select Timer1 prescaler
 * 4. Enable Timer/Counter1 Input Capture Interrupt
 * 5. Set ICU Pin as input pin
 */
void ICU_init(const Icu_ConfigType * config_ptr);

/*
 * Description:
 * Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_ptr)(void));

/*
 * Description :
 * Set ICU's Input Capture Edge Select
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType edgeSelect);

/*
 * Description:
 * Function to get the Timer1 Value when the input is captured
 * The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description :
 * Reset Timer1 Counter(i.e. TCNT1 = 0)
 */
void ICU_clearTimerValue(void);

/*
 * Description :
 * Stop Timer1 and ICU Driver
 */
void ICU_DeInit(void);

#endif /* ICU_H_ */
