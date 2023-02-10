#include "TetrisGeneral.h"
#include <stdio.h>

void draw() {
	unsigned char buffer [32][128] = { 0 };
	int i;
	int j; 
	for (i = 0; i < currentTetromino.width; i++) {
		for (j = 0; j < currentTetromino.width; j++) {
			if (* ((currentTetromino.matrix + i* currentTetromino.width) + j)) {
				buffer[currentTetromino.y + i][currentTetromino.x + j] = *((currentTetromino.matrix + i* currentTetromino.width) + j);
			}
		}
	}
	system("cls");
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 128; j++) {
			printf("%c", (tetrisField[i][j] + buffer[i][j]) ? '1' : '0');
		}
		printf("\n");
	}
}

void renderPixel(unsigned char xPos, unsigned char yPos, unsigned char state) {
	if (xPos < 128 && yPos < 32 && state <= 1) {
		short bufferPos = ((yPos/8)* 128) + xPos;
			
		if (state == 1) {
			OLED_DisplayBuffer[bufferPos] = (OLED_DisplayBuffer[bufferPos] | (0x1 << (yPos % 8)));
			
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

