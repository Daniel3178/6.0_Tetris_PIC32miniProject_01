#include <stdint.h>
// #include <stdio.h>
#include "TetrisGeneral.h"
#include "pic32max.h"
#include <time.h>

void* stdout = (void*)0;

void delay(ms) {
	clock_t timeDelay = ms + clock();
	while (timeDelay > clock());
}



int main() {

	fieldInitializer();

	unsigned char i = 4;
	unsigned char j = 10;
	unsigned char state = 1;
	spawnNewTet();

	while (1) {

		draw();
		currentTetromino.x -= 3;
		if (!DoesFit(currentTetromino)) {
			currentTetromino.x += 3;
			fetchToTetField();
			spawnNewTet();

		}
		rotateMaster(currentTetromino, CLOCKWISE_ROTATION);
		if (!DoesFit(rotatedTetromino)) {
			rotateMaster(rotatedTetromino, COUNTERCLOCKWISE_ROTAION);
			currentTetromino = rotatedTetromino;
		}
		else if (DoesFit(rotatedTetromino)) {
			currentTetromino = rotatedTetromino;


			delay(300);
			i++;


		}

	}
		return 0;
}