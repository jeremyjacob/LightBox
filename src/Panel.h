#pragma once

#include <NeoPixelBrightnessBus.h>

#define CHIPSET WS2812
#define CORRECTION 0xFFB0F0

class LEDS {
public:
    static constexpr unsigned short COUNT = 480;

    static NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> strip;

public:
    static int XY(uint16_t x, uint16_t y);

    static void set(byte x, byte y, HsbColor hsbColor);

    static void set_all(HsbColor hsbColor);

    static void show();

//    static void show();
};

