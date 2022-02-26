#pragma once

#include "Panel.h"
#include <vector>

class Strobe {
public:
    void run();

public:
    std::vector<CRGB> colors = {CRGB::Black, CRGB::White};
    float speed = 5; // Hz
    bool smooth = false; // TODO
private:
    uint16_t iter = 0;
};

void Strobe::run() {
    EVERY_N_MILLIS(floor((1 / speed) * 1000)) {
        if (iter >= colors.size()) iter = 0;
        Utils::fill(p_leds, colors[iter]);
        iter++;
    }
}