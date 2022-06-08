#pragma once

#include "Panel.h"
// add some turqoise

class Pool {
public:
    void run();
    static constexpr const char *NAME = "Pool";
public:
    uint8_t saturation = 255;
    uint8_t hue = 150;
    uint8_t scale = 45;
    int8_t brightness = 0;
private:
    CRGBPalette16 currentPalette;

private:
    void N();
};

void Pool::run() {
    fill_solid(currentPalette, 16, CHSV(hue, saturation, 230));
    currentPalette[9] = CHSV(hue, saturation - 60, 140);
    currentPalette[8] = CHSV(hue, 255 - saturation, 210);
    currentPalette[7] = CHSV(hue, 255 - saturation, 210);
    currentPalette[6] = CHSV(hue, saturation - 60, 140);
    N();
//    FastLED.delay(16);
//    FastLED.show();
}

void Pool::N() {
    for (byte y = 0; y < HEIGHT; y++) {
        for (byte x = 0; x < WIDTH; x++) {
            uint8_t pixelHue8 = inoise8(x * scale, y * scale, millis() / 13);
            if (XY(x, y) == 0) continue; // stops 1st pixel flicker, ???
            p_leds[XY(x, y)] = ColorFromPalette(currentPalette, pixelHue8);
        }
    }
    blur2d(p_leds, WIDTH, HEIGHT, 32);
}
