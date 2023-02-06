#include <stdint.h>
#include <stdio.h>
#include "TetrisGeneral.h"
#include "pic32max.h"

    //void* stdout = (void*)0;


    //Function to initialize everything
    void init() {
        //Set button 1 as input
        TRISFSET = 0x00000002;

        //Set button 2-4 as inputs and the switches
        TRISDSET = 0x00000fe0;

        //Setup for lamps
        TRISECLR = 0x000000ff;
        PORTECLR = 0x000000ff;

        PORTE = 0;

        //Set the seed for the random
        //srand(getSwitches());

        //Setup display
        OledHostInit();
        OledDspInit();

        //Initialize Timer2
        T2CONSET = 0x70; //0111 0000, Sets prescale to 1:256
        IFSCLR(0) = 0x100;//0001 0000 0000
        PR2 = 7812; //40 FPS
        TMR2 = 0;
        T2CONSET = 0x08000; // 1000 0000 0000 0000, Start timer

        IPCSET(2) = 0x1f; //0001 1111 - Bit 4:2 Priority, Bit 1:0 Subpriority.
        IECSET(0) = 0x100; // 0001 0000 0000 - Bit 8 enable interupts from Timer2

        //enable_interrupts();

        IPCSET(2) = 0x1f;
        IECSET(0) = 0x100;
    }


int main() {
    init();
    assetsInitializer();
    fieldInitializer();
    //printAsset(currentShape, 15, 15);
    //printMatrix(currentShape);
    //printTheGame();

        int i=2;
    while (1 && i < 32) {
            
            printAsset(currentShape, 14, i);
            renderGame();
            delay(1000);
            //printTheGame();
            i++;
       
    }

    return 0;
}