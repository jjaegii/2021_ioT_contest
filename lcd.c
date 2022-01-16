#include <stdio.h>
#include <wiringPi.h>
#include "LCD_I2C.h"

int main() {
	wiringPiSetup();

	LCD_begin(0x27, 16, 8, LCD_5x8DOTS);
	LCD_print("    System On");
	return 0;
}
