#pragma once

#include "Panel.h"

class PlasmaWaves {
public:
    void run();
    static constexpr const char *NAME = "Plasma Waves";
};

void PlasmaWaves::run() {
    CRGBPalette16 myPal = heatmap_gp;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // XY tells us the index of a given X/Y coordinate
            int index = XY(x, y);
            int hue = x * 10 + y * 10;
            hue += sin8(millis() / 50 + y * 5 + x * 7);
            p_leds[index] = ColorFromPalette(myPal, hue);
        }
    }
}
