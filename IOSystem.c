#include "pic32max.h"

void ioInitializer() {
	TRISECLR = 0xff; // the led lamps 0 - 7
	TRISDSET = 0xfe0; //switches and btns 
	TRISFSET = 0x2; //btn 1 
}

int getws(void) { //returns the state of swich 1 through 4 where the lsb represents state of switch 1
	int result = ((((PORTD >> 8) & 0X8) | ((PORTD >> 8) & 0x4) | ((PORTD >> 8) & 0x2) | ((PORTD >> 8) & 0X1)) & 0Xf);
	return result;
}

int getbtns(void) { //return the state of btn 1 through 4 where the lsb represents state of btn 1
	int result = ((((PORTD >> 5) & 0X8) | ((PORTD >> 5) & 0X4) | ((PORTD >> 5) & 0X2)|((PORTF >> 1) & 0X1))&0Xf);
	return result;
}