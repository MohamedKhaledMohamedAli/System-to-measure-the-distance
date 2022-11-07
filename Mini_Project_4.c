/*
 ============================================================================
 Name        : Mini_Project_4.c
 Author      : Mohamed Khaled
 Description : System to measure the distance using ultrasonic sensor
 Date        : 10/10/2022
 ============================================================================
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/interrupt.h>

int main(void){

	/* Variable to store Distance */
	uint16 dist = 0;

	/* Initiate Ultrasonic sensor */
	Ultrasonic_init();

	/* Initiate LCD */
	LCD_init();

	/* Display on LCD: "Distance= " */
	LCD_displayString("Distance=    cm");

	/* Enable Global Interrupts */
	SREG |= (1<<7);

	/* Infinite Loop*/
	for(;;){

		/* Get distance value */
		dist = Ultrasonic_readDistance();

		/* Move Cursor */
		LCD_moveCursor(0, 10);

		if(dist < 100){

			/* Display distance value */
			LCD_integerToString(dist);
			LCD_displayCharacter(' ');
		}
		else{

			/* Display distance value */
			LCD_integerToString(dist);
		}
	}
}
