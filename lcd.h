//
// lcd.h
// Author: Caleb Ziegler
// Date: 22 October 2013
// Description: Header file for interaction with LCD
//

#ifndef LCD_H_
#define LCD_H_

void writeDataByte(char dataByte);

void writeCommandNibble(char commandNibble);

void writeCommandByte(char commandByte);

void initSPI();

void set_SS_hi();

void set_SS_lo();

void LCDinit();

void LCDclear();

void SPI_send(char byteToSend);

void MoveCursorLineTwo();

void MoveCursorLineOne();

void writeCharacter(char asciiCharacter);

void writeString(char *string);

void scrollString(char *string1, char *string2);

#endif /* LCD_H_ */
