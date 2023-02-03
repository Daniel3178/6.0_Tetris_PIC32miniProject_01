
#include "pic32max.h"
#include <stdint.h>
/*Methods for time handeling in the game*/

void quickTimer(uint8_t timeout) {

    while (timeout) {
        timeout--;
    }
}