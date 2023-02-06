#include "TetrisGeneral.h"

void printAsset(Asset assetToPrint, int xPos, int yPos) {
	char i; 
	char j;
	unsigned char* tempP = assetToPrint.matrix;
	unsigned char* tempPf= &tetrisField[4][119] - yPos - ((xPos ) * 32);
	unsigned char* pointer = &tetrisField[4][128] - yPos - ((xPos) * 32);
	switch (assetToPrint.id) {
	case SHAPE_ID_9X9:
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				//if (tetrisField[yPos + i][xPos + j] == 0) {
					/*tetrisField[yPos + i][xPos + j] = *tempP++;*/
			

				*tempPf++ = *tempP++;
				
				//}
			}
			tempPf += 128 - 9;
		}
		
		for (i = 0; i < 9; i++) {
			*pointer= 0;
			pointer += 128;
		}
		break;
	default:
		break;
	}
}

void renderPixel(unsigned char xPos, unsigned char yPos, unsigned char state) {
	if (xPos < 128 && yPos < 32 && state <= 1) {
		short bufferPos = ((yPos/8)* 128) + xPos;
			// OLED_DisplayBuffer[4] = 1;

		if (state == 1) {
			OLED_DisplayBuffer[bufferPos] = (OLED_DisplayBuffer[bufferPos] | (0x1 << (yPos % 8)));
			// OLED_DisplayBuffer[4] = 1;
		}
		else if(state == 0) {
			OLED_DisplayBuffer[bufferPos] = (OLED_DisplayBuffer[bufferPos] & ~(0x1 << (yPos % 8)));
		}
	}
}

void renderGame() {
	unsigned char i = 0;
	unsigned char j = 0; 

	for (i = 0; i < DISPLAY_HEIGHT; i++) {
		for (j = 0; j < DISPLAY_WIDTH; j++) {
			if (tetrisField[i][j] == 1){

			renderPixel(j, i, 1);
			}
			else if (tetrisField[i][j] == 0){
				renderPixel(j, i, 0);
			}
		}
	}
}

