#include "TetrisGeneral.h"
#include "pic32max.h"


void *stdout = (void *)0;

// void delay(ms) {
// 	clock_t timeDelay = ms + clock();
// 	while (timeDelay > clock());
// }

int main()
{
	currentScore = 0;
	uno32Initializer();
	gameFieldInitializer();
	spawnNewTet();

	playerRegister();
	displayCurrentPlayer();
	delay(1000000);
//  leaderBoardFieldInitializer();
	clearDisplay();
	printString("SCORE", 33, 1);
	isGameActive = TRUE;
	while (1)
	{

		draw();
		play(getbtns());
		printScore(currentScore, 25, 5);
		printTetromino(nextTetromino, 5, 9);
		
	}
	return 0;
}