#include <msp430.h> 

/*
 * main.c
 */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	return 0;
}

#define RS_MASK 0x40


