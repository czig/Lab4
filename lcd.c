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
    delayMicro();
}

void LCDclear(writebyte)
{
	LCDCON = 0;
	LCDSEND =1;
	LCD_write_8(char writebyte)
}
void writeCommandNibble(char commandNibble)
{
    LCDCON &= ~RS_MASK;
    LCD_write_4(commandNibble);
    delayMilli();
}

void writeCommandByte(char commandByte)
{
    LCDCON &= ~RS_MASK;
    LCD_write_8(commandByte);
    delayMilli();
}

void writeDataByte(char dataByte)
{
    LCDCON |= RS_MASK;
    LCD_write_8(dataByte);
    delayMilli();
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
