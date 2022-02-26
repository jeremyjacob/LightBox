#pragma once

#include "Panel.h"

class CrossHatch {
public:
    CrossHatch() {};
    
    void run();

private:
    struct Blobs {
        uint8_t _x;
        uint8_t _y;
        bool _right;
        CHSV _colour;
    };
    Blobs blob[20];
    uint8_t blobCounter = 0;
    const uint8_t blobRate = 5;     // Higher number is fewer blobs
    long previousTime = 0;
};

void CrossHatch::run() {
    // Fade deals with 'tails'
    fadeToBlackBy(p_leds, NUM_LEDS, 6);
    
    if (millis() - previousTime >= 50) {
        //Spawn new horizontal blob
        if (random8(blobRate) == 0) {
            uint8_t spawnY = random8(HEIGHT);
            blob[blobCounter] = {0, spawnY, true, CHSV(random8(), 255, 255)};
            blobCounter = (blobCounter + 1) % 20;
        }
        
        // Spawn new vertical blob
        if (random8(blobRate) == 0) {
            uint8_t spawnX = random8(WIDTH);
            blob[blobCounter] = {spawnX, 0, false, CHSV(random8(), 255, 255)};
            blobCounter = (blobCounter + 1) % 20;
        }
        
        // Draw the blobs
        for (int i = 0; i < 20; i++) {
            p_leds[XY(blob[i]._x, blob[i]._y)] = p_leds[XY(blob[i]._x, blob[i]._y)] + blob[i]._colour;
        }
        
        // Move the blobs
        for (int i = 0; i < 20; i++) {
            if (blob[i]._right) { blob[i]._x++; }
            else { blob[i]._y++; }
        }
        
        previousTime = millis();
    }
    
}