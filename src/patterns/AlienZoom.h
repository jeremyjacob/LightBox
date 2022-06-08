#pragma once

#include "Panel.h"
#include "Utils.h"

class AlienZoom {
public:
    static constexpr const char *NAME = "Alien Zoom";
    AlienZoom();
    void run();
private:
    float a1 = 1.1;
    float b1 = 1.5;
    byte ledsbuff[NUM_LEDS]{};
private:
    void rotozum();
    void plasma();
};

void AlienZoom::run() {
    plasma();
    rotozum();
    blur2d(p_leds, WIDTH, HEIGHT, 50);
    Utils::mirror();
}

void AlienZoom::rotozum() {
    CRGBPalette16 myPal = shikon_23_gp2;
    static float a = 0;
    
    float f = (sin(a / 2) + a1) / b1;  // scale factor
    float kosinus = cos(a) * f;
    float sinos = sin(a) * f;
    
    for (int i = 0; i < WIDTH; i++) {
        float u1 = i * kosinus;
        float v1 = i * sinos;
        for (int j = 0; j < HEIGHT; j++) {
            byte u = abs8(u1 - j * sinos) % WIDTH;
            byte v = abs8(v1 + j * kosinus) % HEIGHT;
            p_leds[XY(i, j)] = ColorFromPalette(myPal, ledsbuff[v * WIDTH + u] + millis() / 2000, 255);
        }
    }
    float cubsin = cubicwave8(millis() / 200);
    float sincoef = ((cubsin / 256.0f) - 0.5f) * 2;
    a -= (0.02f * State::speed) * sincoef;  // speed rotation
}

void AlienZoom::plasma() {
    uint16_t ms = millis() / 3;
    
    for (int j = 0; j < HEIGHT; j++) {
        int horindexbuff = j * WIDTH;
        for (int i = 0; i < WIDTH; i++) {
            ledsbuff[horindexbuff + i] = inoise8(i * 40, j * 40, ms / 5);
        }
    }
}

AlienZoom::AlienZoom() {
}
