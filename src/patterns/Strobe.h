#pragma once

#include "Panel.h"
#include <vector>

class Strobe {
public:
    void run();
    static constexpr const char *NAME = "Strobe";
public:
    std::vector<CRGB> colors = {CRGB::Black, CRGB::White};
    bool smooth = false; // TODO
private:
    uint16_t iter = 0;
};

void Strobe::run() {
    float speed = 5 * State::speed; // Hz
    EVERY_N_MILLIS(floor((1 / speed) * 1000)) {
        if (iter >= colors.size()) iter = 0;
        Utils::fill(p_leds, colors[iter]);
        iter++;
    }
}