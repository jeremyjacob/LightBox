#pragma once

#include "Utils.h"

class Spirits {
public:
    void run();

    float speed = 0.5;
private:
    uint8_t kBorderWidth = 0;
};

void Spirits::run() {
    uint8_t blurAmount = dim8_raw(beatsin8(3, 64, 192));
    blur2d(p_leds, WIDTH, HEIGHT, blurAmount);

    // Use two out-of-sync sine waves
    uint8_t i = beatsin8(91 * speed, kBorderWidth, CENTER_X - kBorderWidth);
    uint8_t j = beatsin8(109 * speed, kBorderWidth, CENTER_X - kBorderWidth);
    uint8_t k = beatsin8(73 * speed, kBorderWidth, CENTER_X - kBorderWidth);

    // The color of each point shifts over time, each at a different speed.
    uint16_t ms = millis();
    p_leds[XY(i, j)] += CHSV(ms / 29, 200, 255);
    p_leds[XY(j, k)] += CHSV(ms / 41, 200, 255);
    p_leds[XY(k, i)] += CHSV(ms / 73, 200, 255);

    Utils::mirror();
}
