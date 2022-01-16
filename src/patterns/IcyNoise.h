#pragma once

#include "Panel.h"

class IcyNoise {
public:
    void run();

    byte speed = 5;
    byte scale = 30;
    byte hue_shift = 0;
private:
    byte hue{};
    uint16_t x = 0, y = 0, z = 0;
private:
    void FillNoise(bool ShiftX, bool ShiftY, bool ShiftZ, const CRGBPalette16 &palette, bool ShiftHue, bool BriNoise);
};

void IcyNoise::run() {
    FillNoise(false, false, true, CloudColors_p, hue_shift, true);
    ;
}

void
IcyNoise::FillNoise(bool ShiftX, bool ShiftY, bool ShiftZ, const CRGBPalette16 &palette, bool ShiftHue, bool BriNoise) {
    z += (ShiftZ) ? speed : 0;
    x += (ShiftX) ? speed : ((ShiftZ) ? speed * 0.125 : 0);
    y -= (ShiftY) ? speed : ((ShiftZ) ? speed * 0.0625 : 0);
    for (uint8_t i = 0; i < WIDTH; i++) {
        for (uint8_t j = 0; j < HEIGHT; j++) {
            byte noise = inoise8((i * scale) + x, (j * scale) + y, z);
            byte Inoise = inoise8((j * scale) + y, (i * scale) + x, z);
            p_leds[XY(i, j)] = ColorFromPalette(palette, noise + hue,
                                              (!BriNoise || Inoise > 127) ? 255 : dim8_raw(Inoise * 2));
        }
    }
    if (ShiftHue) { hue++; } else { hue = 0; }
}