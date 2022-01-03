#include "Blue.h"


void Blue::run() {
    LEDS::set_all(HsbColor(0.7, 1, 1));
    LEDS::show();
}