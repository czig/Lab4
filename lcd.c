/*
 * lcd.c
 * Author: C2C Caleb Ziegler
 * Date: 22 Oct 2013
 * Description: Implementation for lcd functions
 */

#include "lcd.h"
#include <msp430.h>
#define RS_MASK 0x40

char LCDCON = 0;

void writeDataByte(char dataByte);

void writeCommandNibble(char commandNibble);

void writeCommandByte(char commandByte);

void set_SS_hi();

void set_SS_lo();

void SPI_send(char byteToSend);

void rotateString(char * string);

void initSPI() {
	UCB0CTL1 |= UCSWRST;

	UCB0CTL0 |= UCCKPH | UCMSB | UCMST | UCSYNC;
	UCB0CTL1 |= UCSSEL1;          //Select clock to use
	UCB0STAT |= UCLISTEN;         //Enables internal loopback

	P1DIR |= BIT0;

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;         //Make UCBOCLK available on P1.5

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;         //Make UCBOSSIMO available on P1.7

	P1SEL |= BIT6;
	P1SEL2 |= BIT6;         //Make UCAOSSOMI available on P1.6

	P2DIR |= BIT1;

	UCB0CTL1 &= ~UCSWRST;   //Enable subsystem

}

void set_SS_hi() {
	P1OUT |= BIT0;
}

void set_SS_lo() {
	P1OUT &= ~BIT0;
}

void LCDinit() {
	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x03);

	writeCommandNibble(0x02);

	writeCommandByte(0x28);

	writeCommandByte(0x0C);

	writeCommandByte(0x01);

	writeCommandByte(0x06);

	writeCommandByte(0x01);

	writeCommandByte(0x02);

	SPI_send(0);
	__delay_cycles(45);
}

void LCDclear() {
	writeCommandByte(1);
}

//Thanks to C2C Jason Mossing for helping me figure this one out
void LCD_write_4(char nibbleToSend) {
	unsigned char sendnibble = nibbleToSend;

	sendnibble &= 0x0F;           //Clear upper half of byte but save lower half

	sendnibble |= LCDCON;            //Set LCD control nibble

	sendnibble &= 0x7F;              //Set E low

	SPI_send(sendnibble);

	__delay_cycles(45);

	sendnibble |= 0x80;             //Set E high

	SPI_send(sendnibble);

	__delay_cycles(45);

	sendnibble &= 0x7F;             //Set E low

	SPI_send(sendnibble);

	__delay_cycles(45);
}

void LCD_write_8(char byteToSend) {
	unsigned char sendByte = byteToSend;

	sendByte &= 0xF0;

	sendByte = sendByte >> 4;               // rotate to the right 4 times

	LCD_write_4(sendByte);

	sendByte = byteToSend;

	sendByte &= 0x0F;

	LCD_write_4(sendByte);
}

void SPI_send(char byteToSend) {
	char readByte;

	set_SS_lo();

	UCB0TXBUF = byteToSend;

	while (!(UCB0RXIFG & IFG2)) {
		// wait until you've received a byte
	}

	readByte = UCB0RXBUF;

	set_SS_hi();
}

void writeCommandNibble(char commandNibble) {
	LCDCON &= ~RS_MASK;
	LCD_write_4(commandNibble);
	__delay_cycles(1824);
}

void writeCommandByte(char commandByte) {
	LCDCON &= ~RS_MASK;
	LCD_write_8(commandByte);
	__delay_cycles(1824);
}

void writeDataByte(char dataByte) {
	LCDCON |= RS_MASK;
	LCD_write_8(dataByte);
	__delay_cycles(1824);
}

void MoveCursorLineOne() {
	writeCommandByte(0x02);  //0x02 sets cursor at home
}

void MoveCursorLineTwo() {
	writeCommandByte(0x02); //Set cursor at home
	int i;
	for (i = 0; i < 40; i++) {
		writeCommandByte(0x14); //0x14 shifts cursor to right once, and do this 40 times to get to next line
	}
}

void writeString(char *string) {
	int i;
	for(i = 0; i < 8; i++)              //Will only write the first 8 characters of a string to the LCD
	{
		writeCharacter(string[i]);      //Leverages writeCharacter to write characters of the string to the LCD
	}
}

void writeCharacter(char asiiCharacter) {
	writeDataByte(asiiCharacter);
}

void rotateString(char * string)
{
	char firstChar = string[0];           //Saves first character in string for later use
	int i;

	for (i = 0; string[i+1] != 0; i++)    //Stop once the next character in string is null case stop
	{
		string[i] = string[i+1];          //Rotate string to right by making the current character in string equal the next character in string
	}

	string[i] = firstChar;                //Move previously first character in the string to the end of the string to preserve that character and perform a correct rotate right
}

void scrollString(char *string1, char *string2) {

	while (1) {

		MoveCursorLineOne();
		writeString(string1);
		rotateString(string1);
		MoveCursorLineTwo();
		writeString(string2);
		rotateString(string2);
	}

}

