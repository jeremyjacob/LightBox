#pragma once

#include "Panel.h"

class Off {
public:
    void run();
    static constexpr const char *NAME = "Off";
public:
    Off() = default;
};

void Off::run() {
//    digitalWrite(SWITCH_PIN, 0);
    fill_solid(p_leds, NUM_LEDS, CRGB::Black);
}