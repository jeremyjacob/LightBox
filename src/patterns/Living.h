#pragma once

#include "FastLED.h"
#include "Panel.h"
#include "Utils.h"

#define LIVING_LAYERS 1

class Living {
public:
    Living();

    void run();

public:
    uint8_t speed = 18;

private:
    uint32_t x[LIVING_LAYERS]{};
    uint32_t y[LIVING_LAYERS]{};
    uint32_t z[LIVING_LAYERS]{};
    uint32_t scale_x[LIVING_LAYERS]{};
    uint32_t scale_y[LIVING_LAYERS]{};
    uint8_t noise[LIVING_LAYERS][WIDTH][HEIGHT]{};

private:
    void noise_noise1();
};

DEFINE_GRADIENT_PALETTE(pit) {
        0, 3, 3, 3,
        64, 13, 50, 255,  //blue
        128, 3, 3, 3,
        192, 255, 130, 3,  //orange
        255, 3, 3, 3
};

Living::Living() = default;

void Living::run() {
    noise_noise1();
}

//as shown on youtube
//a noise controlled & modulated by itself
void Living::noise_noise1() {

    CRGBPalette16 Pal(pit);

    //modulate the position so that it increases/decreases x
    //(here based on the top left pixel - it could be any position else)
    //the factor "2" defines the max speed of the x movement
    //the "-255" defines the median moving direction
    x[0] = x[0] + (speed * 1.5 * noise[0][0][0]) - 255;
    //modulate the position so that it increases/decreases y
    //(here based on the top right pixel - it could be any position else)
    y[0] = y[0] + (speed * noise[0][WIDTH - 1][0]) - 255;
    //z just in one directio n but with the additional "1" to make sure to never get stuck
    //in case the movement is stopped by a crazy parameter (noise data) combination
    //(here based on the down left pixel - it could be any position else)
    z[0] += 1 + ((noise[0][0][HEIGHT - 1]) / 4);
    //set the scaling based on left and right pixel of the middle line
    //here you can set the range of the zoom in both dimensions
    scale_x[0] = 8000 + (noise[0][0][CENTER_Y] * 16);
    scale_y[0] = 8000 + (noise[0][WIDTH - 1][CENTER_Y] * 16);

    //calculate the noise data
    uint8_t layer = 0;
    for (uint8_t i = 0; i < WIDTH; i++) {
        uint32_t ioffset = scale_x[layer] * (i - CENTER_X);
        for (uint8_t j = 0; j < HEIGHT; j++) {
            uint32_t joffset = scale_y[layer] * (j - CENTER_Y);
            uint16_t data = inoise16(x[layer] + ioffset, y[layer] + joffset, z[layer]);
            // limit the 16 bit results to the interesting range
            if (data < 11000) data = 11000;
            if (data > 51000) data = 51000;
            // normalize
            data = data - 11000;
            // scale down that the result fits into a byte
            data = data / 161;
            // store the result in the array
            noise[layer][i][j] = data;
        }
    }

    //map the colors
    for (uint8_t y = 0; y < HEIGHT; y++) {
        for (uint8_t x = 0; x < WIDTH; x++) {
            //I will add this overlay CRGB later for more colors
            //it´s basically a rainbow mapping with an inverted brightness mask
            CRGB overlay = CHSV(noise[0][y][x], 255, noise[0][x][y]);
            //here the actual colormapping happens - note the additional colorshift caused by the down right pixel noise[0][15][15]
            p_leds[XY(x, y)] = ColorFromPalette(Pal, noise[0][WIDTH - 1][HEIGHT - 1] + noise[0][x][y]) + overlay;
        }
    }

    //make it looking nice
    Utils::adjust_gamma();

    //mirror it!
    Utils::mirror();

    //and show it!
    ;
}

