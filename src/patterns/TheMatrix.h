#pragma once

#pragma once

#include "Panel.h"

class TheMatrix {
public:
    static constexpr const char *NAME = "The Matrix";
    void run();

private:
    struct Blobs {
        uint8_t _x;
        uint8_t _y;
        bool _right;
    };
    static constexpr uint8_t BLOB_COUNT = 27;
    Blobs blob[BLOB_COUNT]{};
    uint8_t blobCounter = 0;
    const uint8_t blobRate = 1;     // Higher number is fewer blobs
    long previousTime = 0;
};

void TheMatrix::run() {
    // Fade deals with 'tails'
    fadeToBlackBy(p_leds, NUM_LEDS, 10);
    
    if (millis() - previousTime >= 75) {
        // Spawn new vertical blob
        if (random8(blobRate) == 0) {
            uint8_t spawnX = random8(WIDTH);
            blob[blobCounter] = {spawnX, 0, false};
            blobCounter = (blobCounter + 1) % BLOB_COUNT;
        }
        
        // Draw the blobs
        for (auto &i: blob) {
            p_leds[XY(i._x, i._y - 1)] = CRGB(0, 255, 0);
            p_leds[XY(i._x, i._y)] = CHSV(100, 30, random(100, 255));
        }
        
        // Move the blobs
        for (auto &i: blob) {
            i._y++;
        }
        
        previousTime = millis();
    }
//    blur2d(p_leds, WIDTH, HEIGHT, 5);
}