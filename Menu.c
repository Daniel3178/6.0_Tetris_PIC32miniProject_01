#include "TetrisGeneral.h"



void runTheGame(){

    clearDisplay();
    gameFieldInitializer();
    spawnNewTet();
    printString("SCORE", 34, 2, BIG_FONT);
    isGameActive = TRUE;
    while(isGameActive){
        draw();
		play(getbtns());
		printTetromino(nextTetromino, 5, 9);
	printScore(currentScore, 25, 5,BIG_FONT);
    }
    endGameRoutine();
}

void runTheLeaderBoard(){
        displayLeaderBoard();
    while(!(getbtns() & 0x1)){
    }
    clearDisplay();
}


unsigned char getUserOptions(){
    int x = 44;
    int y = 13;
    printString("TETRIS MENU", 44, 4, LITTLE_FONT);
    printString("PLAY", 55, 13, LITTLE_FONT);
    printString("HIGHEST SCORE", 55, 21, LITTLE_FONT);
    // printCharacter(26, 44, 4, LITTLE_FONT);
    while (!(getbtns() & 0x8)){
        switch (getbtns())
        {
        case 2:
            x = 44;
            y = 13;
            break;
        
        case 4:
            x = 44;
            y = 21;
            break;
        }
        printCharacter(32, 44, 13, LITTLE_FONT);
        printCharacter(32, 44, 21, LITTLE_FONT);
        printCharacter(26, x, y, LITTLE_FONT);
    }

    if(y == 13){
        return 1;
    }
    if(y == 21){
        return 2;
    }
}

void runTheMenu(){
    uno32Initializer();
    while (1){
        switch(getUserOptions()){
            case 1:
            runTheGame();
            break;
            case 2:
            runTheLeaderBoard();
            break;
        }
    }
}
