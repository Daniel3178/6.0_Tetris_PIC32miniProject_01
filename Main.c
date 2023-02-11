// #include <stdint.h>
// #include <stdio.h>
#include "TetrisGeneral.h"
#include "pic32max.h"
// #include <time.h>

void* stdout = (void*)0;

// void delay(ms) {
// 	clock_t timeDelay = ms + clock();
// 	while (timeDelay > clock());
// }



int main() {
	uno32Initializer();
	fieldInitializer();
	spawnNewTet();

	while (1) {

		draw();
		play(getbtns());		

	}
		return 0;
}