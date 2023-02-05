#include <stdint.h>
#include <stdio.h>
#include "TetrisGeneral.h"


int main() {
    assetsInitializer();
    fieldInitializer();
    //printAsset(currentShape, 15, 15);
    //printMatrix(currentShape);
    //printTheGame();

    while (1) {
        char i=0;
        if (i + 9 < DISPLAY_HEIGHT) {
            printAsset(currentShape, i, i);
            delay(1000);
            printTheGame();
            i++;
        }
    }

    return 0;
}