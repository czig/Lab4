Lab4
====

Lab 4 - C - "An LCD Device Driver"

This library comes complete with a header and implementation file that allow communication with an LCD.

The main.c file utilizes the header and implementation files to call up functions and write to the LCD.

The flow of operations in main.c is as follows:

1) Initialize SPI

2) Initialize the LCD

3) Clear the LCD

4) Define strings

5) Write to LCD using writeString(string) for non scrolling operations or using scrollString(string) for operations that require scrolling

    a) scrollString(string1,string2) is already configured to work with two strings so no cursor functions need to be used 
      with scrollString(string1,string2), but cursor functions like MoveCursorLineOne() or MoveCursorLineTwo() will need 
      to be used with writeString(string). scrollString(string1,string2) will run until program is stopped by user, but 
      writeString(string) needs to be used with other operations or an infinite loop to prevent the computer from crashing
