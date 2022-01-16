#pragma once

#include "Panel.h"

class Plasm {
public:
    void run();
};

void Plasm::run() {
    fadeToBlackBy(p_leds, NUM_LEDS, 16);
    double t = millis() / 16;
    for (byte i = 0; i < WIDTH; i++) {
        byte thisVal = inoise8(i * 30, t, t);
        byte thisMax = map(thisVal, 0, 255, 0, WIDTH);
        for (byte j = 0; j < HEIGHT; j++) {
            byte thisVal_ = inoise8(t, j * 30, t);
            byte thisMax_ = map(thisVal_, 0, 255, 0, HEIGHT);
            byte x = (i + thisMax_ - (WIDTH * 2 - WIDTH) / 2) - 1;
            byte y = (j + thisMax - (WIDTH * 2 - WIDTH) / 2);
            byte cx = (i + thisMax_);
            byte cy = (j + thisMax);
            p_leds[XY(i, j)] += ((x - y > -2) && (x - y < 2)) || ((WIDTH - 1 - x - y) > -2 && (WIDTH - 1 - x - y < 2)) ||
                                (WIDTH - cx == 0) || (WIDTH - 1 - cx == 0) ||
                                ((HEIGHT - cy == 0) || (HEIGHT - 1 - cy == 0)) ? CHSV(beat8(5), thisVal_, thisVal) : CHSV(
                    0, 0, 0);
        }
    }
    blur2d(p_leds, WIDTH, HEIGHT, 16);
    Utils::rmirror();
    FastLED.delay(16);
}

