#ifndef _Tetris_Config_H
#define _Tetris_Config_H

/*Definitions*/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define FONT_WIDTH 5
#define FONT_HEIGHT 6
#define TET_ID_6X6 1
#define TET_ID_9X9 2
#define TRUE 1
#define FALSE 0
#define BIG_FONT 0
#define LITTLE_FONT 1
#define TET_ID_12X12 3
#define PLAY_EXIT 0x1
#define PLAY_RIGHT 0x2
#define PLAY_LEFT 0x4
#define PLAY_ROTATE 0x8
#define TETRIS_FIELD_WIDTH 30
#define TETRIS_FIELD_HEIGHT 127
#define CLOCKWISE_ROTATION 0
#define COUNTERCLOCKWISE_ROTAION 1

typedef struct Tetromino
{
	unsigned char *matrix;
	int width;
	int x;
	int y;
	unsigned char id;

} Tetromino;

typedef struct Player
{
	char name[3];
	int score;
	char positionBuffer[8];

} Player;

/*Tetrominoes & font declaration */
unsigned char digits[10][15];
unsigned char alphabet[28][15];
unsigned char digits0_9[10][30];
unsigned char alphabetA_Z[28][30];
unsigned char tetrisField[32][128];
unsigned char OLED_DisplayBuffer[512];

Tetromino tetCollection[7];
Tetromino rotatedTetromino;
Tetromino currentTetromino;
Tetromino tempTetromino;
Tetromino nextTetromino;


int seed;
int timeoutCount;
int currentScore;
unsigned char level;
unsigned char isGameActive;

/* Functions */
int GetButtons(void); // return the state of btn 1 through 4 where the lsb represents state of btn 1
int Rand(void);
void user_isr();
void InitializeTetrisField();
void enable_interrupts();
void SpawnNewTet();
void ClearDisplay();
void InitializeUNO32();
void DrawTheGame();
void DisplayCurrentPlayer();
void InitializeLeaderBoardField();
void DisplayLeaderBoard();
void EndGameRoutine();
void RunTetris();
void Play(int aButton);
void QuickTimer(int timeout);
void RenderPixel(int xPos, int yPos, unsigned char state);
void RotateMatrix(Tetromino inputTet, int rotationDirection);
void PrintNumber(int aNumber, int xPosition, int yPosition, unsigned char aFont);
void PrintCharacter(char aChar, int xPosition, int yPosition, unsigned char aFont);
void PrintString(char *aString, int xPosition, int yPosition, unsigned char aFont);
void PrintTetromino(Tetromino myTetromino, int xPosition, int yPosition);
//test
#endif