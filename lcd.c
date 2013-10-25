/*
 * lcd.c
 * Author: C2C Caleb Ziegler
 * Date: 22 Oct 2013
 * Description: Implementation for lcd functions
 */
#include "lcd.h"
#include <msp430.h>
#define RS_MASK 0x40

unsigned int LCDCON = 0;

void initSPI()
{
	UCB0CTL1 |= UCSWRST;

	UCBOCTL0 |= UCCKPH|UCMSB|UCMST|UCSYNC;
	UCBOCTL1 |= UCSSEL1;          //Select clock to use
	UCBOSTAT |= UCLISTEN;         //Enables internal loopback

	P1DIR |= BIT0;

	P1SEL |= BIT5;
	P1SEL2 |= BIT5;         //Make UCBOCLK available on P1.5

	P1SEL |= BIT7;
	P1SEL2 |= BIT7;         //Make UCBOSSIMO available on P1.7

	P1SEL |= BIT6;
	P1SEL2 |= BIT6;         //Make UCAOSSOMI available on P1.6

	P2DIR |= BIT1;

	UCBOCTL1 &= ~UCSWRST;   //Enable subsystem

}

void set_SS_hi()
{
	P1OUT |= BIT0;
}

void set_SS_lo()
{
	P1OUT &= ~BIT0;
}

void LCDinit()
{
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

void LCDclear()
{
	writeCommandByte(1);
}

void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCD_write_4(commandNibble);
    __delay_cycles(1824);
}

void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCD_write_8(commandByte);
    __delay_cycles(1824);
}

void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCD_write_8(dataByte);
    __delay_cycles(1824);
}

void LCDclear()
{
	writeCommandByte(1);
}

//Thanks to C2C Jason Mossing for helping me figure this one out
void LCD_write_4(char nibbleToSend)
{
	unsigned char sendnibble = nibbleToSend;

	    sendnibble &= 0x0F;              //Clear upper half of byte but save lower half

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

void LCD_write_8(char byteToSend)
{
    unsigned char sendByte = byteToSend;

    sendByte &= 0xF0;

    sendByte = sendByte >> 4;               // rotate to the right 4 times

    LCD_write_4(sendByte);

    sendByte = byteToSend;

    sendByte &= 0x0F;

    LCD_write_4(sendByte);
}

void SPI_send(char byteToSend)
{
    char readByte;

    set_SS_lo();

    UCB0TXBUF = byteToSend;

    while(!(UCB0RXIFG & IFG2))
    {
        // wait until you've received a byte
    }

    readByte = UCB0RXBUF;

    set_SS_hi();
}

void MoveCursorLineOne()
{
	writeCommandByte(0x02);  //0x02 sets cursor at home
}

void MoveCursorLineTwo()
{
	writeCommandByte(0x02); //Set cursor at home
	int i;
	for(i = 0; i < 40; i++)
	{
		writeCommandByte(0x14); //0x14 shifts cursor to right once, and do this 40 times to get to next line
	}
}

void writeString(char *string)
{
	while(*string != 0)   //Stops writing string when memory location is 0 (no more characters)
	{
		writeCharacter(*string);
		string++;

	}
}

void writeCharacter(char asiiCharacter)
{
	writeDataByte(asiiCharacter);
}

