#pragma once

#include "Panel.h"

class Fireplace {
public:
    void run();

public:
    int8_t scale = 64;
    int8_t speed = 37 ;
private:
    uint32_t t;
};

void Fireplace::run() {
    t += speed;
    for (byte x = 0; x < WIDTH; x++) {
        for (byte y = 0; y < HEIGHT; y++) {
            int16_t Bri = inoise8(x * scale, (y * scale) - t) - (y * (255 / HEIGHT));
            byte Col = Bri;// inoise8(x * scale, (y * scale) - t) - (y * (255 / LED_ROWS));
            if (Bri < 0) Bri = 0;
            if (Bri != 0) Bri = 256 - (Bri * 0.2);
            nblend(p_leds[XY(x, HEIGHT - y - 1)], ColorFromPalette(HeatColors_p, Col, Bri), speed);
        }
    }
    ;
}