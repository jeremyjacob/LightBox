#pragma once

#include "Panel.h"

class Rainbow {
public:
    void run();
    static constexpr const char *NAME = "Rainbow";
private:
    uint16_t _plasmaShift = (random8(0, 5) * 32) + 64;
    uint16_t _plasmaTime = 0;
    const uint8_t _plasmaXfactor = 8;
    const uint8_t _plasmaYfactor = 8;
};

void Rainbow::run() {
    for (int16_t x = 0; x < WIDTH; x++) {
        for (int16_t y = 0; y < HEIGHT; y++) {
            int16_t r = sin16(_plasmaTime) / 256;
            int16_t h = sin16(x * r * _plasmaXfactor + _plasmaTime) + cos16(y * (-r) * _plasmaYfactor + _plasmaTime) +
                        sin16(y * x * (cos16(-_plasmaTime) / 256) / 2);
            p_leds[XY(x, y)] = CHSV((uint8_t) ((h / 256) + 128), 255, 255);
        }
    }
    uint16_t oldPlasmaTime = _plasmaTime;
    _plasmaTime += _plasmaShift;
    if (oldPlasmaTime > _plasmaTime)
        _plasmaShift = (random8(0, 5) * 32) + 64;
}