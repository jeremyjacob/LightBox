#pragma once

#include "Panel.h"

class Galaxy {
public:
    void run();
};

void Galaxy::run() {
    fadeToBlackBy(p_leds, NUM_LEDS, 32);
    double t = (float) (millis()) / 128;
    for (byte i = 0; i < 8; i++) {
        for (byte j = 0; j < 4; j++) {
            p_leds[XY(beatsin8(10, (j * 2), WIDTH - 1 - (j * 2), 0, ((j % 2) ? 128 : 0) + t * (i + j)),
                      beatsin8(5, (j * 2), HEIGHT - 1 - (j * 2), 0, ((j % 2) ? 192 : 64) + t * (i + j)))] += CHSV(
                    i * 32, 255, 255);
        }
    }
    blur2d(p_leds, WIDTH, HEIGHT, 16);
}
