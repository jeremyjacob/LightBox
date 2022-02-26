#pragma once

#include <vector>
#include "Text.h"

namespace TextManager {
    std::vector<TextObject> objects;
    
    uint8_t add() {
        objects.push_back(TextObject());
        // Return index of new object
        return objects.size() - 1;
    }
    
    bool remove(uint8_t index) {
        if (index >= objects.size()) return false;
        objects.erase(objects.begin() + index);
        return 1;
    }
    
    TextObject &get(uint8_t index) {
        return objects[index];
    }
    
    void render() {
        Utils::fill(t_leds, CRGB::Black);
        for (auto &object: objects) {
            object.type_message();
        }
    }
}

