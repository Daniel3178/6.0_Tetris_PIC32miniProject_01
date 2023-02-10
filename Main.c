#include <stdint.h>
// #include <stdio.h>
#include "TetrisGeneral.h"
#include "pic32max.h"
#include <time.h>

    void* stdout = (void*)0;
void user_isr() {
	OledUpdate();
	IFSCLR(0) = 0x100;//0001 0000 0000
	return;
}
void delay(ms) {
    clock_t timeDelay = ms + clock();
    while (timeDelay > clock());
}
    


// void clearDisplay()
// {
//   int i;
//   for(i = 0; i < 512; i++)
//     OLED_DisplayBuffer[i] = 0;
// }
int main() {

    fieldInitializer();

        unsigned char i = 4;
        unsigned char j = 10;
        unsigned char state = 1;
        spawnNewTet();

    while (1) {
               //rotateClockwise(currentShape);

           //if(i < 100){
           //    if (i == 10 || i == 15 ) {

          
           //        //rotateCounterClockwise(currentShape);
           //        //currentShape = rotatedAsset;
           //    //currentShape = rotatedAsset;
           //    currentShape.x -= 3;
           //    }
               //rotateCounterClockwise(currentShape);
               draw();
               currentTetromino.x-=3;
               if (!DoesFit(currentTetromino)) {
                   currentTetromino.x += 3;
                   fetchToTetField();
                   spawnNewTet();
                   
               }
               rotateMaster(currentTetromino, CLOCKWISE_ROTATION);
               if (!DoesFit(rotatedTetromino)) {
                   rotateMaster(rotatedTetromino, COUNTERCLOCKWISE_ROTAION);
                   currentTetromino = rotatedTetromino;
               }
               else if (DoesFit(rotatedTetromino)) {
                   currentTetromino = rotatedTetromino;
               }
               
               //fieldInitializer();

            delay(300);
            i++;
           //}
       
    }

    return 0;
}