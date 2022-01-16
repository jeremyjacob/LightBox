#pragma once

#include "Panel.h"

class SolidColor {
public:
    void run();

public:
    SolidColor() = default;
};

void SolidColor::run() {
    fill_solid(p_leds, NUM_LEDS, CRGB::Blue);
    ;
}