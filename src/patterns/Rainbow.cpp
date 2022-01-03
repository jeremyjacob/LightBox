#include "Rainbow.h"

//uint8_t Rainbow::starthue = 0;

void Rainbow::run() {
//    fill_rainbow(LEDS::leds, LEDS::COUNT, --starthue, 20);
    LEDS::set_all(HsbColor(235 / 360, 0, 1));
    LEDS::show();
}