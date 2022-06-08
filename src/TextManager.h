#pragma once

#include <vector>


namespace TextManager {
    void setup() {
    }
    
    void render() {
        Utils::fill(t_leds, CRGB::Black);
        EVERY_N_SECONDS(1) {
//            Serial.println(objects.size());
        }
        for (auto &object: State::textComponents) {
            object.typeMessage();
        }
    }
}

