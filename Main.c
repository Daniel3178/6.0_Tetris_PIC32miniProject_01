#include "TetrisGeneral.h"
#include "pic32max.h"


void *stdout = (void *)0;

// void delay(ms) {
// 	clock_t timeDelay = ms + clock();
// 	while (timeDelay > clock());
// }

int main()
{
	uno32Initializer();
	fieldInitializer();
	spawnNewTet();
	isGameActive = TRUE;

	printString("SCORE", 33, 1);
	while (1)
	{

		draw();
		play(getbtns());
		printScore(score, 25, 5);
		printTetromino(nextTetromino, 5, 9);
		
	}
	return 0;
}