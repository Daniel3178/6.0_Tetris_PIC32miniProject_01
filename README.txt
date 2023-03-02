PROJECT SPECIFICATIONS:

    ID = advanced miniProject "Tetris" 
    Programming languages = C & Assembly 
    Developed by = Daniel Ibrahimi & Naveed Rahman
    Instructor = Marco Chiesa 
    Course ID = IS1200 
    KTH | CINTE1 | 2/3-23

GUIDE: 

    This project is made for UNO32 boards and will require a c compiler called MCB32 toolchain in order to compile
    and install the program on the board. You can find the instructions in the following link:
    http://github.com/is1200-example-projects/mcb32tools/releases/Links. Make sure that you have the right program 
    installed on your machine then run the MCB32 toolchain terminal on your computer and navigate to the project 
    folder. Once you found your way to the folder, type "make" in the terminal and press enter. After that you 
    need to send the compiled code to the UNO32 board using the following command:
    Make install TTYDEV=/dev/"usb address". 

GAME INFO:

    The game itself is meant to be played vertically but the menu and leaderboard will be displayed horizontally. 
    Use btn 1 as ESC.
    btn 4 is used for rotation, btn 2 and 3 are used for moving to the right/left.
    Switches are used for randomization of the next tetromino (seed).
    LEDs are used to display the current level.
    Use btn 2 and 3 for navigating through alphabets or in the menu.
    Use btn 4 as ENTER
    The current Level of the game will be increased after you have gained a certain score.
    
    levels: lvl2 = 100, lvl3 = 500, lvl4 =1000, lvl5 = 2000
