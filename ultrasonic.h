 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the AVR ULTRASONIC driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Speed of Sound */
#define ULTRASONIC_SPEED_OF_SOUND	34000

/* 1 Second equals 1M clock cycle
 * since F(ICU) = 1 MHz
 * Therefore T(ICU) = 1 micro second
 */
#define ULTRASONIC_SEC_TO_CLK 1000000

/* Factor for measuring the distance in ultrasonic */
/* there is multiply 2 since the time calculated by ICU contains the Time taken by wave to
 * reach object then return
 */
#define ULTRASONIC_CALIBRATION_FACTOR ((uint8)((ULTRASONIC_SEC_TO_CLK * 2)/ULTRASONIC_SPEED_OF_SOUND))

/* Trigger port pin */
#define ULTRASONIC_TRIGGER_PORT_ID	PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID	PIN5_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize Ultrasonic sensor:
 * 1. Initialize the ICU driver
 * 2. Setup the ICU call back function
 * 3. Setup the direction for the trigger pin as output pin through the GPIO driver
 */
void Ultrasonic_init(void);

/*
 * Description :
 * 1. Send the trigger pulse by using Ultrasonic_Trigger function
 * 2. Start the measurements by the ICU from this moment
 */
uint16 Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */
