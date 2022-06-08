#pragma once

#include "FastLED.h"
#include "Panel.h"
#include "Utils.h"

class Andromeda {
public:
//    Andromeda();
    void run();
    static constexpr const char *NAME = "ANDROMEDA";

private:
    float speedx = 1;
    float speedy = 1;
    bool mirror = true;
    uint32_t x{};
    uint32_t y{};
    uint32_t z{};
    uint32_t scale_x{};
    uint32_t scale_y{};
    uint8_t noise[WIDTH][HEIGHT]{};

private:
    void noise_noise1();
};

DEFINE_GRADIENT_PALETTE(pit2) {
        0, 3, 3, 3,
//        30, 50, 3, 3, // red
        64, 13, 255, 13,  //blue
        128, 3, 3, 3,
        192, 130, 255, 3,  //orange
        255, 3, 3, 3
};

void Andromeda::run() {
    speedx = State::speed;
    speedy = State::speed;
    noise_noise1();
}

void Andromeda::noise_noise1() {
    
    CRGBPalette16 Pal(pit2);
    
    //modulate the position so that it increases/decreases x
    //(here based on the top left pixel - it could be any position else)
    //the factor "2" defines the max speed of the x movement
    //the "-255" defines the median moving direction
//    x = x + speedx * (noise[0][0] + 90);
    x = x + speedx * -500;
    //modulate the position so that it increases/decreases y
    //(here based on the top right pixel - it could be any position else)
//    y = y + speedy * (noise[CENTER_X][0] + 90);
    y = y + speedy * 500;
    //z just in one direction but with the additional "1" to make sure to never get stuck
    //in case the movement is stopped by a crazy parameter (noise data) combination
    //(here based on the down left pixel - it could be any position else)
    z += 1 + max(((noise[0][HEIGHT - 1]) / 4), 500);
    //set the scaling based on left and right pixel of the middle line
    //here you can set the range of the zoom in both dimensions
//    scale_x = beatsin88(100 * State::speed, 7000, 10000) + (noise[0][CENTER_Y] * 16);
    scale_x = 8000 + (noise[0][CENTER_Y] * 16);
    scale_y = 8000 + (noise[WIDTH - 1][CENTER_Y] * 16);
    
    for (uint8_t i = 0; i < WIDTH; i++) {
        uint32_t ioffset = scale_x * (i - CENTER_X);
        for (uint8_t j = 0; j < HEIGHT; j++) {
            uint32_t joffset = scale_y * (j - CENTER_Y);
            uint16_t data = inoise16(x + ioffset, y + joffset, z);
            // limit the 16 bit results to the interesting range
            if (data < 11000) data = 11000;
            if (data > 51000) data = 51000;
            // normalize
            data = data - 11000;
            // scale down that the result fits into a byte
            data = data / 161;
            // store the result iyn the array
            noise[i][j] = data;
        }
    }
    
    //map the colors
    for (uint8_t iy = 0; iy < HEIGHT; iy++) {
        for (uint8_t ix = 0; ix < WIDTH; ix++) {
            //I will add this overlay CRGB later for more colors
//            it´s basically a rainbow mapping with an inverted brightness mask
            CRGB overlay = CHSV(noise[ix][iy], 255, noise[ix][iy]);
            //here the actual colormapping happens - note the additional colorshift caused by the down right pixel noise[0][15][15]
            const CRGB &crgb = ColorFromPalette(Pal, noise[WIDTH - 1][HEIGHT - 1] + noise[ix][iy]) + overlay;
            CHSV chsv = rgb2hsv_approximate(crgb);
            chsv.h += millis() / 500;
            chsv.s -= beatsin8(2, 0, 10);
            p_leds[XY(ix, iy)] = chsv;
        }
    }
    
    //make it looking nice
//    Utils::adjust_gamma();
    
    //mirror it!
    if (mirror) Utils::mirror();
}