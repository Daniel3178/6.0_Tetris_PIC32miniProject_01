
#include <stdint.h>
#include <stdio.h>
#include "TetrisGeneral.h"

unsigned char rotated12x12Matrix[12][12];
unsigned char rotated9x9Matrix[9][9];

unsigned char tetrisField[32][128];

void fieldInitializer() {
	unsigned char i = 0;
	unsigned char j = 0;

	for (i = 0; i < 32; i++) {
		for (j = 0; j < 128; j++) {
			if (i == 0 || i == 31 || j == 0 || j == 127) {
				tetrisField[i][j] = 1;
			}
			else {
				tetrisField[i][j] = 0;
			}
		}
	}
}



#pragma region ROTATION_STUFF

int i;
int j;

void rotateMaster(Asset input)
{
	switch (input.id)
	{
	case SHAPE_ID_6X6:
		// printf("SHAPE_ID_6X6");
		break;
	case SHAPE_ID_9X9:
		// printf("SHAPE_ID_9X9");
		rotate9x9matrix(input.matrix, COUNTERCLOCKWISE_ROTAION);
		break;
	case SHAPE_ID_12X12:
		// printf("SHAPE_ID_12X12");
		rotate12x12matrix(input.matrix, CLOCKWISE_ROTATION);
		break;
	}
}

void rotate9x9matrix(unsigned char *matrixToRotateP, int rotationDirection)
{

	unsigned char tempArray[9][9];
	if (rotationDirection)
	{ // COUNTERCLOCKWISE ROTATION
		// int i;
		// int j;
		for (i = 0; i < 9; i++)
		{
			for (j = 8; j >= 0; j--)
			{
				tempArray[j][i] = *matrixToRotateP++;
			}
		}
	}

	else
	{ // CLOCKWISE ROTATION
		// int i;
		// int j;
		for (i = 8; i >= 0; i--)
		{
			for (j = 0; j < 9; j++)
			{
				tempArray[j][i] = *matrixToRotateP++;
			}
		}
	}
	 memcpy(rotated9x9Matrix, tempArray, sizeof(tempArray));
	currentShape.matrix = &rotated9x9Matrix[0][0];
}

void rotate12x12matrix(unsigned char *matrixToRotateP, int rotationDirection)
{
	unsigned char tempArray[12][12];
	if (rotationDirection)
	{ // COUNTERCLOCKWISE ROTATION
		// int i;
		// int j;
		for (i = 0; i < 12; i++)
		{
			for (j = 11; j >= 0; j--)
			{
				tempArray[j][i] = *matrixToRotateP++;
			}
		}
	}

	else
	{ // CLOCKWISE ROTATION
		// int i;
		// int j;
		for (i = 11; i >= 0; i--)
		{
			for (j = 0; j < 12; j++)
			{
				tempArray[j][i] = *matrixToRotateP++;
			}
		}
	}
	 memcpy(rotated12x12Matrix, tempArray, sizeof(tempArray));
	currentShape.matrix = &rotated12x12Matrix[0][0];
}

#pragma endregion

#pragma region LaborintOnVisualStudio

 void printMatrix(Asset currentAsset)
 {
 	switch (currentAsset.id)
 	{
 	case SHAPE_ID_6X6:
 		// int i;
 		// int j;
 		for (i = 0; i < 6; i++)
 		{
 			for (j = 0; j < 6; j++)
 			{
 				if (*currentAsset.matrix == 0)
 				{

 					printf("0");
 				}
 				else if (*currentAsset.matrix == 1)
 				{

 					printf("1");
 				}
 				currentAsset.matrix++;
 			}
 			printf("\n");
 		}
 		break;
 	case SHAPE_ID_9X9:
 		// int i;
 		// int j;

 		for (i = 0; i < 9; i++)
 		{
 			for (j = 0; j < 9; j++)
 			{
 				if (*currentAsset.matrix == 0)
 				{
 					printf("0");
 				}
 				else if (*currentAsset.matrix == 1)
 				{
 					printf("1");
 				}
 				currentAsset.matrix++;
 			}
 			printf("\n");
 		}

 		break;
 	case SHAPE_ID_12X12:
 		// int i;
 		// int j;
 		for (i = 0; i < 12; i++)
 		{
 			for (j = 0; j < 12; j++)
 			{
 				if (*currentAsset.matrix == 0)
 				{
 					 printf("0");
 				}
 				else if (*currentAsset.matrix == 1)
 				{
 					 printf("1");
 				}
 				currentAsset.matrix++;
 			}
 			 printf("\n");
 		}
 		break;
 	}
 }
 void printTheGame() {
	 unsigned char i;
	 unsigned char j;
	 system("cls");
	 for (i = 0; i < DISPLAY_HEIGHT; i++) {
		 for (j = 0; j < DISPLAY_WIDTH; j++) {
			 if (tetrisField[i][j] == 1) {
				 printf("1");
			 }
			 else if (tetrisField[i][j] == 0) {
				 printf("0");
			 }
		 }
		 printf("\n");
	 }
 }
 void delay(ms) {
	 clock_t timeDelay = ms + clock();
	 while (timeDelay > clock());
 }

#pragma endregion
// check if it fits before roatiting the matrix
/*The following functions need to be implemented
1. collision detector
2. graphic renderer
3. row eliminator i.e when a row completes it should remove
the blocks and pull the above row down
4. Display initializer
5. IOSystem
6. random shape generator
7. Extra work on gameplay machanism
*/