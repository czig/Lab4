//
// lcd.h
// Author: Caleb Ziegler
// Date: 22 October 2013
// Description: Header file for interaction with LCD
//

#ifndef LCD_H_
#define LCD_H_

//Initializes SPI by setting up ports and pins
void initSPI();

//Initializes the LCD by beginning communications with the LCD
void LCDinit();

//Simply, clear the LCD screen to make it go blank
void LCDclear();

//Sets the cursor in the home position
void MoveCursorLineTwo();

//Sets the cursor in the home position, then moves the cursor
//to the right 40 times to get to the next line. Next, it sets
//the cursor in the home position on line 2.
void MoveCursorLineOne();

//Writes an ascii character (in hex) to the LCD screen.
void writeCharacter(char asciiCharacter);

//Writes a string to the LCD screen. Note, this function will
//only write the first 8 characters of the string to the LCD
//screen.
void writeString(char *string);

//Moves the cursor to line one, writes the first 8 characters
//of string1 to the LCD, and rotates string1 one character to the right. Next,
//it moves the cursor to line 2, writes the first 8 characters of string2 to
//the LCD, and rotates string2 one character to the right. This function runs
//within an infinite loop.
void scrollString(char *string1, char *string2);

#endif /* LCD_H_ */
