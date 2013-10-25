/*******************************************
 * Author: C2C Caleb Ziegler/CS-39
 * Created: 22 Oct 2013
 * Description: This library interfaces
 * with the LCD on the Geek box and displays
 * a string of characters on the top and bottom
 * lines.
 *******************************************/
#include <msp430.h> 
#include "lcd.h"
#include "button.h"
/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;        // Stop watchdog time

	configureP1PinAsButton(BIT1 | BIT2 | BIT3); // configure pins 1, 2, and 3 as buttons
	initSPI();
	LCDinit();
	LCDclear();
	char string1[] = "ECE382 is my favorite class! ";
	char string2[] = "Here's your sign. ";
	char string3[] = "Git 'er dun. ";
	char string4[] = "Ron White: Tater Salad. ";

	MoveCursorLineOne();
	writeString("Message?");
	MoveCursorLineTwo();
	writeString("Press123");

		char buttons[] = { BIT1, BIT2, BIT3 };
		char pressedButton = pollP1Buttons(buttons, 3);

		switch (pressedButton) {
		case BIT1:
			scrollString(string1,string2);
			break;
		case BIT2:
			scrollString(string1,string3);
			break;
		case BIT3:
			scrollString(string1,string4);
			break;
		}
}
