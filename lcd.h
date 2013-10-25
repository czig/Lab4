//
// lcd.h
// Author: Caleb Ziegler
// Date: 22 October 2013
// Description: Header file for interaction with LCD
//

void writeDataByte(char dataByte);

void writeCommandNibble(char commandNibble);

void writeCommandByte(char commandByte);

void initSPI();

void set_SS_hi();

void set_SS_lo();

void LCDinit();

void LCDclear();

void MoveCursorLineTwo();

void MoveCursorLineOne();

void writeCharacter(char asciiCharacter);

void writeString(char *string);

void scrollString(char *string1, char *string2);

