
#ifndef _Tetris_Config_H
#define _Tetris_Config_H
#include <stdint.h>
#include <stdlib.h>

/*Definitions*/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define TETRIS_FIELD_WIDTH 30 
#define TETRIS_FIELD_HEIGHT 127
#define FONT_WIDTH 5
#define FONT_HEIGHT 6
#define TET_ID_6X6 1
#define TET_ID_9X9 2
#define TET_ID_12X12 3
#define CLOCKWISE_ROTATION 0
#define COUNTERCLOCKWISE_ROTAION 1
#define PLAY_DOWN 0x8
#define PLAY_RIGHT 0x4
#define PLAY_LEFT 0x2
#define PLAY_ROTATE 0x1
#define TRUE 1
#define FALSE 0
/*Tetrominoes & font declaration */

unsigned char alphabetA_Z[28][30];
unsigned char digits0_9[10][30];
unsigned char tetrisField[32][128];
unsigned char OLED_DisplayBuffer[512];
int currentScore;


typedef struct Tetromino
{
	unsigned char* matrix;
	int width;
	int x;
	int y;
	unsigned char id;
}Tetromino;

typedef struct Player{
	char name [3];
	int score;
	char positionBuffer [8];

}Player;

void rotateMaster(Tetromino inputTet, int rotationDirection);
void quickTimer(int timeout);
void user_isr();
void gameFieldInitializer();

void renderGame();
 void enable_interrupts();
void renderPixel(int xPos, int yPos, unsigned char state);
void OledUpdate();
int getbtns(void);//return the state of btn 1 through 4 where the lsb represents state of btn 1
int DoesFit(Tetromino myAsset);
void spawnNewTet();
 void clearDisplay();
void fetchToTetField();
void uno32Initializer();
void draw();
void play(int btn);
int rand(void);
int getButtonsPress();
void printScore(int currentScore, int x, int y);
void printCharacter(char myChar, int x, int y);
void printString(char *myChar, int x, int y);
void printTetromino(Tetromino tetToPrint, int xPos, int yPos);
void playerRegister();
void displayCurrentPlayer();
void leaderBoardFieldInitializer();

Tetromino tetCollection[7];
Tetromino rotatedTetromino;
Tetromino currentTetromino;
Tetromino tempTetromino;
Tetromino nextTetromino;
int seed;
int timeoutCount;
int isGameActive;
int level;
#endif