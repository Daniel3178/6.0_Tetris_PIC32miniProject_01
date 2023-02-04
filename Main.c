#include <stdint.h>
#include <stdio.h>
#include "TetrisGeneral.h"


int main() {
    assetsInitializer();
    // printMatrix(currentShape);
    rotateMaster(currentShape);
    // printf("\n");
    // printMatrix(currentShape);
    rotateMaster(currentShape);
    // printf("\n");
    // printMatrix(currentShape);
    currentShape = left_skew_shape;
    // printf("\n");
    // printMatrix(currentShape);
    rotateMaster(currentShape);
    // printf("\n");
    // printMatrix(currentShape);

    return 0;
}