#include "Panel.h"

NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> LEDS::strip(LEDS::COUNT + 1);

constexpr uint16_t OVERFLOW_PIXEL = 481;

int LEDS::XY(uint16_t x, uint16_t y) {
    // 7 - y because we count from top and the panels start from bottom left
    // x * 8 because there are 8 columns in the matrix
    // Last part wraps around to second row if y is on second row
    if (x > 29) return OVERFLOW_PIXEL;
    if (y > 15) return OVERFLOW_PIXEL;
    return (7 - y) + (x * 8) + ((y > 7) * 248);
}

void LEDS::set(byte x, byte y, HsbColor hsbColor) {
    LEDS::strip.SetPixelColor(LEDS::XY(x, y), hsbColor);
}

void LEDS::set_all(HsbColor hsbColor) {
    for (int i = 0; i < LEDS::COUNT; ++i) {
        LEDS::strip.SetPixelColor(i, hsbColor);
    }
}

void LEDS::show() {
    LEDS::strip.Show();
}
