
#include <stdint.h>
#include <stdio.h>
#include "TetrisGeneral.h"
#include <time.h>
#include <stdlib.h>

unsigned char tetrisField[32][128];
unsigned char rotated9x9Matrix[9][9];
unsigned char rotated12x12Matrix[12][12];

#pragma region COLLISION&FETCH

int DoesFit(Tetromino inputTet) {
	for (int i = 0; i < inputTet.width; i++) {
		for (int j = 0; j < inputTet.width; j++) {
			if (tetrisField[inputTet.y + i][inputTet.x + j] && *((inputTet.matrix + i * inputTet.width) + j)) {
				return 0;
			}
			//else if ((myAsset.x + j < 0 || myAsset.x + j >= 32 || myAsset.y + i >= 128)) {
			//	if (*(myAsset.myArray + i * myAsset.width) + j) {
			//		return 0;
			//	}
			//}
		}
	}
	return 1;
}

void fetchToTetField() {
	int i;
	int j;
	for (i = 0; i < currentTetromino.width; i++) {
		for (j = 0; j < currentTetromino.width; j++) {
			if (*((currentTetromino.matrix + i * currentTetromino.width) + j)) {
				tetrisField[currentTetromino.y + i][currentTetromino.x + j] = *((currentTetromino.matrix + i * currentTetromino.width) + j);
			}
		}
	}
}

#pragma endregion

#pragma region SPAWNER

void spawnNewTet() {
	currentTetromino = tetCollection[rand() % 7];
	currentTetromino.x = 100;
	currentTetromino.y = 5;
}
#pragma endregion

#pragma region ROTATION
void rotate9x9matrix(unsigned char* matrixToRotateP, int rotationDirection)
{
	int i;
	int j;

	unsigned char tempArray[9][9];
	if (rotationDirection)
	{ // COUNTERCLOCKWISE ROTATION

		for (i = 0; i < 9; i++)
		{
			for (j = 8; j >= 0; j--)
			{
				tempArray[j][i] = *matrixToRotateP++;
			}
		}
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				rotated9x9Matrix[i][j] = tempArray[i][j];
			}
		}
	}

	else
	{ // CLOCKWISE ROTATION

		for (i = 8; i >= 0; i--)
		{
			for (j = 0; j < 9; j++)
			{
				tempArray[j][i] = *matrixToRotateP++;
			}
		}
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				rotated9x9Matrix[i][j] = tempArray[i][j];
			}
		}
	}
	memcpy(rotated9x9Matrix, tempArray, sizeof(tempArray));
	rotatedTetromino.matrix = &rotated9x9Matrix[0][0];
}

void rotate12x12matrix(unsigned char* matrixToRotateP, int rotationDirection)
{
	int i;
	int j;
	unsigned char tempArray[12][12];

	if (rotationDirection)
	{ // COUNTERCLOCKWISE ROTATION
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

		for (i = 11; i >= 0; i--)
		{
			for (j = 0; j < 12; j++)
			{
				tempArray[j][i] = *matrixToRotateP++;
			}
		}
	}
	memcpy(rotated12x12Matrix, tempArray, sizeof(tempArray));
	rotatedTetromino.matrix = &rotated12x12Matrix[0][0];
}

void rotateMaster(Tetromino inputTet, int rotationDirection)
{
	rotatedTetromino = inputTet;
	switch (inputTet.id)
	{
	case TET_ID_6X6:
		// printf("SHAPE_ID_6X6");
		break;
	case TET_ID_9X9:
		// printf("SHAPE_ID_9X9");
		rotate9x9matrix(inputTet.matrix, rotationDirection);
		break;
	case TET_ID_12X12:
		// printf("SHAPE_ID_12X12");
		rotate12x12matrix(inputTet.matrix, rotationDirection);
		break;
	}
}


#pragma endregion

#pragma region SCORE_MECHANISM

void ereaseCompleteRow() {
	int i;
	int j;
	int sum;
	int counter = 0;

	for (i = 1; i < DISPLAY_WIDTH; i++) {
		sum = 0;
		for (j = 1; j < DISPLAY_HEIGHT; j++) {
			sum += tetrisField[j][i];
		}
		if (sum == DISPLAY_HEIGHT) {
			counter++;
			int k;
			int m;
			for (k = i; i >= 1; i--) {
				for (m = 1; m < DISPLAY_HEIGHT; m++) { // all the columns in the right should shift to the left by one
					tetrisField[m][k] = tetrisField[m][k + 1];
				}
			}
			for (m = 1; m < DISPLAY_HEIGHT; m++) { // the last column should be set to zero
				tetrisField[m][k] = 0;
			}
		}
	}
	score += counter;

}

#pragma endregion

#pragma region GAMEPLAY
void play(int btn) {

	tempTetromino = currentTetromino;
	switch (btn)
	{
	case PLAY_RIGHT:
		tempTetromino.y += 3;
		if (DoesFit(tempTetromino)) {
			currentTetromino.y += 3;
		}
		else {
			fetchToTetField();
			ereaseCompleteRow();
			spawnNewTet();
			tempTetromino.y -= 3;
		}
		break;
	case PLAY_LEFT:
		tempTetromino.y -= 3;
		if (DoesFit(tempTetromino)) {
			currentTetromino.y -= 3;
		}
		else {
			tempTetromino.y += 3;
		}
		break;
	case PLAY_DOWN:
		tempTetromino.x -= 3;
		if (DoesFit(tempTetromino)) {
			currentTetromino.x -= 3;
		}
		else {
			tempTetromino.x += 3;
		}
		break;
	case PLAY_ROTATE:
		rotateMaster(tempTetromino, CLOCKWISE_ROTATION);
		if (DoesFit(rotatedTetromino)) {
			rotateMaster(currentTetromino, CLOCKWISE_ROTATION);
			currentTetromino = rotatedTetromino;
		}
		break;
		//case 5:
		//	rotateMaster(tempTetromino, COUNTERCLOCKWISE_ROTAION);
		//	if (DoesFit(rotatedTetromino)) {
		//		rotateMaster(currentTetromino, COUNTERCLOCKWISE_ROTAION);
		//		currentTetromino = rotatedTetromino; 
		//	}
		//	break;
	}
}
#pragma endregion

#pragma region LaborintOnVisualStudio



//void printTheGame() {
   // unsigned char i;
   // unsigned char j;
   // system("cls");
   // for (i = 0; i < DISPLAY_HEIGHT; i++) {
   //	 for (j = 0; j < DISPLAY_WIDTH; j++) {
   //		 if (tetrisField[i][j] == 1) {
   //			 printf("1");
   //		 }
   //		 else if (tetrisField[i][j] == 0) {
   //			 printf("0");
   //		 }
   //	 }
   //	 printf("\n");
   // }
//}


#pragma endregion


// check if it fits before roatiting the matrix // (ref: collision&stuff)
/*The following functions need to be implemented
1. collision detector // (ref: cllision&stuff)
2. graphic renderer // (ref: graphicEngin)
3. row eliminator i.e when a row completes it should remove 
the blocks and pull the above row down // (ref: score_mechanism)
4. Display initializer // (ref: uno32initializer)
5. IOSystem // (ref: uno32initializer)
6. random shape generator // (ref: spawner)
7. Extra work on gameplay machanism
*/