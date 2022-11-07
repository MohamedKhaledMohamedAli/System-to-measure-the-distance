 /******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for the AVR ICU driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/

#include "icu.h"
#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                          Global Variable                                    *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void(*g_funcCallBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect){

	if(g_funcCallBackPtr != NULL_PTR){

		/* Call the Call Back function in the application after the edge is detected */
		(*g_funcCallBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
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
void ICU_init(const Icu_ConfigType * config_ptr){

	/*
	 * Configure Timer/Counter1 Control Register A:
	 * 1. Clear Bit 7:6(COM1A1:0) for Normal port operation, OC1A disconnected
	 * 2. Clear Bit 5:4(COM1B1:0) for Normal port operation, OC1B disconnected
	 * 3. Set Bit 3:2(FOC1A/FOC1B) because i will not use PWM mode
	 * 4. Clear  Bit 1:0(WGM11:0) to set Timer1 mode of operation to Normal Mode
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1A);

	/*
	 * Configure Timer/Counter1 Control Register B:
	 * 1. Clear Bit 7(ICNC1) to disable Input Capture Noise Canceler
	 * 2. Clear  Bit 4:3(WGM13:2) to set Timer1 mode of operation to Normal Mode
	 */
	TCCR1B = 0;

	/* Configure ICU Edge Select */
	TCCR1B = (TCCR1B & 0xBF) | (((config_ptr->edgeSelect) & 0x01)<<ICES1);

	/* Configure Timer1 prescaler */
	TCCR1B = (TCCR1B & 0xF8) | (((config_ptr->clockSelect) & 0x07)<<CS10);

	/* Initiate Timer1 counter */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;

	/*
	 * Configure Timer/Counter Interrupt Mask Register:
	 * Set Bit 5(TICIE1) to Enable Timer/Counter1 Input Capture Interrupt
	 */
	TIMSK |= (1<<TICIE1);

	/* Set ICU Pin as input pin */
	GPIO_setupPinDirection(ICU_PORT_ID, ICU_PIN_ID, PIN_INPUT);
}

/*
 * Description:
 * Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*a_funcPtr)(void)){

	/* Set Call Back Function */
	g_funcCallBackPtr = a_funcPtr;
}

/*
 * Description :
 * Set ICU's Input Capture Edge Select
 */
void ICU_setEdgeDetectionType(const Icu_EdgeType edgeSelect){

	/* Configure ICU Edge Select */
	TCCR1B = (TCCR1B & 0xBF) | (((edgeSelect) & 0x01)<<ICES1);
}

/*
 * Description:
 * Function to get the Timer1 Value when the input is captured
 * The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void){
	return ICR1;
}

/*
 * Description :
 * Reset Timer1 Counter(i.e. TCNT1 = 0)
 */
void ICU_clearTimerValue(void){

	/* Reset Timer1 counter */
	TCNT1 = 0;
}

/*
 * Description :
 * Stop Timer1 and ICU Driver
 */
void ICU_DeInit(void){

	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}
