
#include "TetrisGeneral.h"

#pragma region GLOBAL_FIELD

#pragma endregion


void assetsInitializer() {
	/*Change the name to spawn new objects
	functionality: randomly choose an object and change the address of the current object to the
	new one*/

	currentShape.myArray = leftLT;
	currentShape.width = 9;
	currentShape.x = 70;
	currentShape.y = 5;
}