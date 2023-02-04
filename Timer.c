
#include "pic32max.h"
#include <stdint.h>
/*Methods for time handeling in the game*/

void quickTimer(int timeout) {

    while (timeout) {
        timeout--;
    }
}