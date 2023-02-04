
#ifndef _Tetris_Config_H
#define _Tetris_Config_H
#include <stdint.h>
/*Definitions*/
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 32
#define TETRIS_FIELD_WIDTH 30 
#define TETRIS_FIELD_HEIGHT 127
#define FONT_WIDTH 5
#define FONT_HEIGHT 6
#define SHAPE_ID_6X6 1
#define SHAPE_ID_9X9 2
#define SHAPE_ID_12X12 3
#define CLOCKWISE_ROTATION 0
#define COUNTERCLOCKWISE_ROTAION 1

/*Tetrominoes & font declaration */
unsigned char squareT[6][6];
unsigned char straightT[12][12];
unsigned char leftLT[9][9];
unsigned char rightLT[9][9];
unsigned char leftSkewT[9][9];
unsigned char rightSkewT[9][9];
unsigned char tT[9][9];
unsigned char alphabetA_Z[28][30];
unsigned char digits0_9[10][30];

typedef struct Asset
{
	unsigned char* matrix;
	int id;
}Asset;

void rotateMaster(Asset input);
void assetsInitializer();
// void printMatrix(Asset currentAsset);
void rotate12x12matrix(unsigned char* matrixToRotateP, int rotationDirection);
void rotate9x9matrix(unsigned char* matrixToRotateP, int rotationDirection);
void quickTimer(int timeout);
void user_isr();



Asset square_shape;
Asset stright_shape;
Asset left_l_sahpe;
Asset right_l_shape;
Asset left_skew_shape;
Asset right_skew_shape;
Asset t_shape;
Asset currentShape;
#endif