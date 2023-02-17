#include "TetrisGeneral.h"

void runTheGame()
{

    clearDisplay();
    gameFieldInitializer();
    spawnNewTet();
    printString("SCORE", 34, 2, BIG_FONT);
    isGameActive = TRUE;
    while (isGameActive)
    {
        draw();
        play(getbtns());
        printTetromino(nextTetromino, 5, 9);
        printScore(currentScore, 25, 5, BIG_FONT);
    }
    endGameRoutine();
}

void runTheLeaderBoard()
{
    displayLeaderBoard();
    while (!(getbtns() & 0x1))
    {
    }
    clearDisplay();
}

unsigned char getUserOptions()
{
    int x = 40;
    int y = 13;
    printString("TETRIS MENU", 44, 4, LITTLE_FONT);
    printString("PLAY", 48, 13, LITTLE_FONT);
    printString("HIGHEST SCORE", 48, 21, LITTLE_FONT);
    // printCharacter(26, 44, 4, LITTLE_FONT);
    while (!(getbtns() & 0x8))
    {
        switch (getbtns())
        {
        case 2:
            x = 40;
            y = 13;
            break;

        case 4:
            x = 40;
            y = 21;
            break;
        }
        printCharacter(32, 40, 13, LITTLE_FONT);
        printCharacter(32, 40, 21, LITTLE_FONT);
        printCharacter(26, x, y, LITTLE_FONT);
    }

    if (y == 13)
    {
        return 1;
    }
    if (y == 21)
    {
        return 2;
    }
}
void developersIntro(){
    clearDisplay();
    printString("DEVELOPED BY", 44, 7, LITTLE_FONT);
    printString("NAVEED AND DANIEL", 35, 17, LITTLE_FONT);
    quickTimer(10000000);
    clearDisplay(); 
}
void runTheMenu()
{
    uno32Initializer();
    developersIntro();
    while (1)
    {
        switch (getUserOptions())
        {
        case 1:
            runTheGame();
            break;
        case 2:
            runTheLeaderBoard();
            break;
        }
    }
}
