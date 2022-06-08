#pragma once

#include "Panel.h"

class FireRings {
public:
    void run();
    static constexpr const char *NAME = "Fire Rings";
};

void FireRings::run() {
    unsigned long t = millis() / 100;
    for (byte x = 0; x < WIDTH; x++) {
        for (byte y = 0; y < HEIGHT; y++) {
            byte col = inoise8(x * 16 + t, y * 16 + t);
            //
            int8_t cx = x - beatsin8(5, 0, WIDTH - 1);
            int8_t cy = y - beatsin8(6, 0, HEIGHT - 1, 0, 64);
            col += sin8(16 * sqrt16(cx * cx + cy * cy));
            //
            cx = x - beatsin8(5, 0, WIDTH - 1, 0, 64);
            cy = y - beatsin8(6, 0, HEIGHT - 1);
            col += sin8(16 * sqrt16(cx * cx + cy * cy));
            //
            col += sin8(cx - t);
            col += cos8(cy - t);
            //
            uint8_t bri = col;
            p_leds[XY(x, y)] = ColorFromPalette(LavaColors_p, col, bri);
        }
    }
    blur2d(p_leds, WIDTH, HEIGHT, 20);;
}