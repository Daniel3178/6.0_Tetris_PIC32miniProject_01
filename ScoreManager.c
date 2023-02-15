#include "TetrisGeneral.h"

// Player currentPlayer;

Player topPlayer [4] ={
    {"", 0, "1"},
    {"", 0, "2"},
    {"", 0, "3"},
    {"", 0, "CURRENT"},
};

void playerRegister(){

    clearDisplay();
    printString("NAME", 60, 4 );
    char firstLetter = 'A';
    char secondLetter = 'A';
    while(!(getbtns() & 0x8)){

        if((getbtns() & 0x4) && firstLetter <= 'Z'){
            
            printCharacter(++firstLetter, 50, 13);
        }
        if((getbtns() & 0x2) && firstLetter > 'A'){
            
            printCharacter(--firstLetter, 50, 13);
        }
    }
    delay(2);
    while(!(getbtns() & 0x8)){

        if((getbtns() & 0x4) && secondLetter <= 'Z'){
         
            printCharacter(++secondLetter, 50, 19);
        }
        if((getbtns() & 0x2) && secondLetter > 'A'){
        
            printCharacter(--secondLetter, 50, 19);
        }
    }
    delay(2);

    topPlayer[3].name[0] = firstLetter;
    topPlayer[3].name[1] = secondLetter;
    topPlayer[3].name[2] = 0;
    topPlayer[3].score = currentScore;
    currentScore = 0;
}

void updateLeaderBoard(){
    int i;
    int j;
    for(i = 0; i < 3; i ++){
        if(topPlayer[3].score >= topPlayer[i].score){
            topPlayer[i].name[0] = topPlayer[3].name[0];
            topPlayer[i].name[1] = topPlayer[3].name[1];
            topPlayer[i].name[3] = 0;
            topPlayer[i].score = topPlayer[i].score;
            break;
        }
    }
}

void displayCurrentPlayer(){
    printString("ID", 90, 4);
    printString(topPlayer[3].name, 110, 4);
    printString("SCORE", 40,4);
    printScore(topPlayer[3].score, 100, 4);
    delay(2000000);

}

void endGameRoutine(){
    clearDisplay();
    delay(2);
    printString("GAME", 90, 5);
    printString("OVER", 80, 5 );
    delay(1000);
    clearDisplay();
    playerRegister();
    updateLeaderBoard();
    displayCurrentPlayer();
}

void leaderBoardFieldInitializer(){
    unsigned char i = 0;
    unsigned char j = 0;

    for (i = 0; i < 32; i++){
        for (j = 0; j < 128; j++){
            if(i == 0 || i == 31 || i == 9 || j ==  42 || j== 0 || j == 127){
                renderPixel(j, i, 1);
            }
            else {
                renderPixel(j, i, 0);
            }
        }
    }

}

void displayLeaderBoard(){
    leaderBoardFieldInitializer();
    // print player id  x = 8 y = 7
    // print rank x = 64 y = 7
    // print score x = 99 y = 7
    // print player id x = 24 y = 11
    // print player rank x = 64 y = 11
    // print player score x = 99 y = 11
    //print second player id x = 24 y = 18
    // print second player rank x = 64 y = 18
    // print second player score x = 99 y = 18
    // print third player id  x = 24 y = 25
    // print third player rank x = 64 y = 25
    // print third player score x = 99 y = 25

}
