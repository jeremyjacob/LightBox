#pragma once

#include "Panel.h"

class EnergyBalls {
public:
    void run();
};

void EnergyBalls::run() {
    fadeToBlackBy(p_leds, NUM_LEDS, 16);
    for(byte i=8; i > 0;i--){ p_leds[XY(beatsin8(12 + i, 0, WIDTH - 1), beatsin8(15 - i, 0, HEIGHT - 1))]+=CHSV(beatsin8(12, 0, 255), 255, 255);
        if(WIDTH >24 || HEIGHT >24){
            p_leds[XY(beatsin8(12 + i, 0, WIDTH - 1) + 1, beatsin8(15 - i, 0, HEIGHT - 1))]+=CHSV(beatsin8(12, 0, 255), 255, 255);
            p_leds[XY(beatsin8(12 + i, 0, WIDTH - 1) - 1, beatsin8(15 - i, 0, HEIGHT - 1))]+=CHSV(beatsin8(12, 0, 255), 255, 255);
            p_leds[XY(beatsin8(12 + i, 0, WIDTH - 1), beatsin8(15 - i, 0, HEIGHT - 1) + 1)]+=CHSV(beatsin8(12, 0, 255), 255, 255);
            p_leds[XY(beatsin8(12 + i, 0, WIDTH - 1), beatsin8(15 - i, 0, HEIGHT - 1) - 1)]+=CHSV(beatsin8(12, 0, 255), 255, 255);
        }
    }blur2d(p_leds, WIDTH, HEIGHT, 16);
    FastLED.delay(16);
}
