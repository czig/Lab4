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
/*
 * main.c
 */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    char string1[] = "ECE382 is my favorite class! ";
    char string2[] = "They call me tater salad. ";
    initSPI();
    LCDinit();
    LCDclear();
    scrollString(string1,string2);

    while(1)
    {

    }
	
	return 0;
}




