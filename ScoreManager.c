#include "TetrisGeneral.h"
#include "pic32max.h"
// Player currentPlayer;

Player topPlayer[4] = {
    {"", 0, "FIRST"},
    {"", 0, "SECOND"},
    {"", 0, "THIRD"},
    {"", 0, "CURRENT"},
};

void playerRegister()
{

    clearDisplay();
    printString("NAME", 60, 4, BIG_FONT);
    char firstLetter = 'A';
    char secondLetter = 'A';
    while (!(getbtns() & 0x8))
    {
        if ((getbtns() & 0x4) && firstLetter <= 'Z')
        {
            printCharacter(++firstLetter, 50, 10, BIG_FONT);
        }
        if ((getbtns() & 0x2) && firstLetter > 'A')
        {
            printCharacter(--firstLetter, 50, 10, BIG_FONT);
        }
    }
    delay(2);
    while (!(getbtns() & 0x8))
    {

        if ((getbtns() & 0x4) && secondLetter <= 'Z')
        {
            printCharacter(++secondLetter, 50, 16, BIG_FONT);
        }
        if ((getbtns() & 0x2) && secondLetter > 'A')
        {
            printCharacter(--secondLetter, 50, 16, BIG_FONT);
        }
    }
    delay(2);

    topPlayer[3].name[0] = firstLetter;
    topPlayer[3].name[1] = secondLetter;
    topPlayer[3].name[2] = 0;
    topPlayer[3].score = currentScore;
    currentScore = 0;
}

void updateLeaderBoard()
{
    int i;
    int j;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = i;
        for (j = i + 1; j < 4; j++)
        {

            if (topPlayer[j].score >= topPlayer[i].score)
            {
                m = j;
            }
        }
        if (m != i)
        {

            Player temp;
            temp.name[0] = topPlayer[i].name[0];
            temp.name[1] = topPlayer[i].name[1];
            temp.name[2] = 0;
            temp.score = topPlayer[i].score;

            topPlayer[i].name[0] = topPlayer[m].name[0];
            topPlayer[i].name[1] = topPlayer[m].name[1];
            topPlayer[i].name[3] = 0;
            topPlayer[i].score = topPlayer[m].score;

            topPlayer[m].name[0] = temp.name[0];
            topPlayer[m].name[1] = temp.name[1];
            topPlayer[m].name[2] = 0;
            topPlayer[m].score = temp.score;
        }
    }
}

void displayCurrentPlayer()
{
    clearDisplay();
    printString("ID", 90, 4, BIG_FONT);
    printString(&topPlayer[3].name[0], 80, 4, BIG_FONT);
    printString("SCORE", 60, 4, BIG_FONT);
    printScore(topPlayer[3].score, 50, 4, BIG_FONT);
    quickTimer(20000000);
}

void endGameRoutine()
{
    clearDisplay();
    delay(1000);
    printString("GAME", 90, 5, BIG_FONT);
    printString("OVER", 80, 5, BIG_FONT);
    delay(5000);
    clearDisplay();
    playerRegister();
    displayCurrentPlayer();
    updateLeaderBoard();
    delay(5000);
    clearDisplay();
    level =1;
    PORTECLR = 0xff;
}

void leaderBoardFieldInitializer()
{
    unsigned char i = 0;
    unsigned char j = 0;
    clearDisplay();

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 128; j++)
        {
            if (i == 0 || i == 31 || i == 9 || j == 42 || j == 0 || j == 127)
            {
                renderPixel(j, i, 1);
            }
            else
            {
                renderPixel(j, i, 0);
            }
        }
    }
}

void displayLeaderBoard()
{
    leaderBoardFieldInitializer();
    printString("PLAYER ID", 3, 2, LITTLE_FONT);
    printString("RANK", 64, 2, LITTLE_FONT);
    printString("SCORE", 99, 2, LITTLE_FONT);

    if (topPlayer[0].name[0] != 0 && topPlayer[0].score > 0)
    {
        printString(&topPlayer[0].name[0], 19, 11, LITTLE_FONT);
        printString(&topPlayer[0].positionBuffer[0], 64, 11, LITTLE_FONT);
        printScore(topPlayer[0].score, 99, 11, LITTLE_FONT);
    }
    if (topPlayer[1].name[0] != 0 && topPlayer[1].score > 0)
    {
        printString(&topPlayer[1].name[0], 19, 18, LITTLE_FONT);
        printString(&topPlayer[1].positionBuffer[0], 64, 18, LITTLE_FONT);
        printScore(topPlayer[1].score, 99, 18, LITTLE_FONT);
    }
    if (topPlayer[2].name[0] != 0 && topPlayer[2].score > 0)
    {
        printString(&topPlayer[2].name[0], 19, 25, LITTLE_FONT);
        printString(&topPlayer[2].positionBuffer[0], 64, 25, LITTLE_FONT);
        printScore(topPlayer[2].score, 99, 25, LITTLE_FONT);
    }
}
