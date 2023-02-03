
#include "TetrisGeneral.h"

#pragma region GLOBAL_FIELD

Asset square_shape = { .matrix = &squareT[0][0], .id = SHAPE_ID_6X6 };
Asset stright_shape = { .matrix = &straightT[0][0], .id = SHAPE_ID_12X12 };
Asset left_l_sahpe = { .matrix = &leftLT[0][0], .id = SHAPE_ID_9X9 };
Asset right_l_shape = { .matrix = &rightLT[0][0], .id = SHAPE_ID_9X9 };
Asset left_skew_shape = { .matrix = &leftSkewT[0][0], .id = SHAPE_ID_9X9 };
Asset right_skew_shape = { .matrix = &rightSkewT[0][0], .id = SHAPE_ID_9X9 };
Asset t_shape = { .matrix = &tT[0][0], .id = SHAPE_ID_9X9 };
#pragma endregion


void assetsInitializer() {
	/*Change the name to spawn new objects
	functionality: randomly choose an object and change the address of the current object to the
	new one*/

	currentShape = right_l_shape;

}