#include "TetrisGeneral.h"
#include <stdio.h>

void draw()
{
	unsigned char buffer[32][128];

	int i;
	int j;
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 128; j++)
		{
			buffer[i][j] = 0;
		}
	}
	for (i = 0; i < currentTetromino.width; i++)
	{
		for (j = 0; j < currentTetromino.width; j++)
		{
			if (*((currentTetromino.matrix + i * currentTetromino.width) + j))
			{
				buffer[currentTetromino.y + i][currentTetromino.x + j] = *((currentTetromino.matrix + i * currentTetromino.width) + j);
			}
		}
	}
	for (i = 0; i < 32; i++)
	{
		for (j = 36; j < 128; j++)
		{
			if (tetrisField[i][j] + buffer[i][j])
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

void printCharacter(char myChar, int x, int y)
{
	int index = myChar - 65;
	int i;
	int j;
	if(index >= 0 && index < 28){

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 5; j++)
		{
			renderPixel(x - i, y + j, alphabetA_Z[index][5 * i + j]);
		}
	}
	}
	if(myChar == 32){
		for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 5; j++)
		{
			renderPixel(x - i, y + j, alphabetA_Z[27][5 * i + j]);
		}
	}
	}
}

void printDigit(char myDigit, int x, int y)
{
	int index = myDigit - 48;
	int i;
	int j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 5; j++)
		{
			renderPixel(x - i, y + j, digits0_9[index][5 * i + j]);
		}
	}
}

void printString(char *str, int x, int y)
{
	int tempX = x;
	int tempY = y;
	int i;
	int j;
	while (*str != 0)
	{
		printCharacter(*str, tempX, tempY);
		if (*str == 32)
		{
			for (i = 0; i < 6; i++)
			{
				for (j = 0; j < 5; j++)
				{
					renderPixel(x - i, y + j, digits0_9[27][5 * i + j]);
				}
			}
		}
		str++;
		tempY += 6;
	}
}

void printScore(int currentScore, int x, int y)
{

	int tempY = y;
	int i;

	int counter = 1;
	int tempNum = currentScore;
	int tempNum2 = currentScore;
	while (tempNum /= 10)
	{
		counter++;
	}

	char numberArray[counter];

	for (i = 0; i < counter; i++)
	{
		numberArray[i] = (tempNum2 % 10) + 48;
		tempNum2 /= 10;
	}

	for (i = counter - 1; i >= 0; i--)
	{
		printDigit(numberArray[i], x, tempY);
		tempY += 6;
	}
}
 void clearDisplay()
 {
   int i;
   for(i = 0; i < 512; i++)
     OLED_DisplayBuffer[i] = 0;
 }

void renderPixel(int xPos, int yPos, unsigned char state)
{
	if (xPos < 128 && yPos < 32 && state <= 1)
	{
		short bufferPos = ((yPos / 8) * 128) + xPos;

		if (state == 1)
		{
			OLED_DisplayBuffer[bufferPos] = (OLED_DisplayBuffer[bufferPos] | (0x1 << (yPos % 8)));
		}
		else if (state == 0)
		{
			OLED_DisplayBuffer[bufferPos] = (OLED_DisplayBuffer[bufferPos] & ~(0x1 << (yPos % 8)));
		}
	}
}

void printTetromino(Tetromino tetToPrint, int xPos, int yPos)
{
	int i;
	int j;
	int tempY = yPos;
	int tempX = xPos;
	unsigned char *p = tetToPrint.matrix;
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			renderPixel(tempX + j, tempY + i, 0);
		}
	}
	for (i = 0; i < tetToPrint.width; i++)
	{
		for (j = 0; j < tetToPrint.width; j++)
		{
			renderPixel(tempX + j, tempY + i, *p);
			p++;
		}
	}
}

void renderGame()
{
	unsigned char i = 0;
	unsigned char j = 0;

	for (i = 0; i < DISPLAY_HEIGHT; i++)
	{
		for (j = 0; j < DISPLAY_WIDTH; j++)
		{
			if (tetrisField[i][j] == 1)
			{

				renderPixel(j, i, 1);
			}
			else if (tetrisField[i][j] == 0)
			{
				renderPixel(j, i, 0);
			}
		}
	}
}
