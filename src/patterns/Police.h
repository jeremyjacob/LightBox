#pragma once

#include "Panel.h"
#include <vector>

class Police {
public:
    void run();
private:
    bool alt = false;
};

void Police::run() {
    EVERY_N_MILLIS(250)
    {
        alt = !alt;
        for (int x = 0; x < WIDTH; ++x) {
            CRGB color = ((x < WIDTH / 2) ^ alt) ? CRGB::Red : CRGB::Blue;
            for (int y = 0; y < HEIGHT; ++y) {
                p_leds[XY(x, y)] = color;
            }
        }
    }
}