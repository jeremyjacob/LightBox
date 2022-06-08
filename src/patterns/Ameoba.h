#pragma once

#include "FastLED.h"
#include "Panel.h"
#include "Utils.h"


#define AMEOBA_LAYERS 2

class Ameoba {
public:
    Ameoba();
    static constexpr const char *NAME = "Ameoba";
    void run();

private:
    void noise_noise2();
    
    [[nodiscard]] CRGB shifting_colors(uint8_t value, bool inverse) const;
    
    [[maybe_unused]] void show_palette();
    
    void setup_tables();

private:
    float baseSpeed = 17.0;
    CRGB buffer1[OVERFLOW_PIXEL]{};
    CRGB buffer2[OVERFLOW_PIXEL]{};
    float a[1024]{};
    float b[1024]{};
    float c[1024]{};
    float ctrl[6]{};
    double x[AMEOBA_LAYERS] = {(double) random(60000), (double) random(60000)};
    double y[AMEOBA_LAYERS] = {(double) random(60000), (double) random(60000)};
    double z[AMEOBA_LAYERS] = {(double) random(60000), (double) random(60000)};
    double scale_x[AMEOBA_LAYERS]{};
    double scale_y[AMEOBA_LAYERS]{};
    float noise[AMEOBA_LAYERS][WIDTH][HEIGHT]{};
};


// could alternatate color ratios over time?

Ameoba::Ameoba() {
    setup_tables();
//    FastLED.setDither(DISABLE_DITHER);
}

void Ameoba::run() {
    noise_noise2();
}

void Ameoba::setup_tables() {
    /*
      for (uint16_t i = 0; i < 1024; i++) {
        a[i] = sin8(i/4) ;
        b[i] = 0;
        c[i] = cubicwave8( i/2) ;
      }
    */
    for (uint16_t i = 256; i < 768; i++) {
        a[i] = triwave8(127 + (i / 2));
        //b[i] = 0;
        //c[i] = triwave8(127 + (i / 2)) ;
    }
}

// check the "palette"
[[maybe_unused]] void Ameoba::show_palette() {
    
    for (uint8_t _y = 0; _y < HEIGHT; _y++) {
        for (uint8_t _x = 0; _x < HEIGHT; _x++) {
            p_leds[XY(_x, _y)] = CRGB(a[((_x * 16) + _y) * 4], b[((_x * 16) + _y) * 4], c[((_x * 16) + _y) * 4]);
        }
    }
    Utils::adjust_gamma();;
}


CRGB Ameoba::shifting_colors(uint8_t value, bool inverse) const {
    const double interval = 100000 / (State::speed * baseSpeed);
    const double v = (interval / 25) ? (interval / 25) : 1;
    double offset = millis() / v;
    long double ms = fmod(millis(), interval);
    double mapped = Utils::mapd(ms, 0, interval, 0, 255);
    CRGB rgb = CRGB(value, 0, 0);
    CHSV hsv = rgb2hsv_approximate(rgb);
    hsv.hue += mapped;
    if (inverse) {
        hsv.h = hsv.h + offset;
    }
    hsv2rgb_rainbow(hsv, rgb);
    return rgb;
}

// highly experimental
// note that the noise values are in the range of 0-1023 when using them
void Ameoba::noise_noise2() {
    // LAYER ONE
    //top left
    ctrl[0] =
            (ctrl[0] + noise[0][0][0] + noise[0][1][0] + noise[0][0][1] + noise[0][1][1]) / (State::speed * baseSpeed);
    //top right
    ctrl[1] = (ctrl[1] + noise[0][WIDTH - 1][0] + noise[0][WIDTH - 2][0] + noise[0][WIDTH - 1][1] +
               noise[0][WIDTH - 2][1]) / (State::speed * baseSpeed);
    //down left
    ctrl[2] = (ctrl[2] + noise[0][0][HEIGHT - 1] + noise[0][0][HEIGHT - 2] + noise[0][1][HEIGHT - 1] +
               noise[0][1][HEIGHT - 2]) / (State::speed * baseSpeed);
    //middle left
    ctrl[3] = (ctrl[3] + noise[0][0][CENTER_Y] + noise[0][1][CENTER_Y] + noise[0][0][CENTER_Y + 1] +
               noise[0][1][CENTER_Y + 1]) / (State::speed * baseSpeed);
    //center
    ctrl[4] =
            (ctrl[4] + noise[0][WIDTH - 1][CENTER_Y] + noise[0][WIDTH - 2][CENTER_Y] +
             noise[0][WIDTH - 1][CENTER_Y + 1] +
             noise[0][WIDTH - 2][CENTER_Y + 1]) / (State::speed * baseSpeed);
    ctrl[5] = (ctrl[5] + ctrl[0] + ctrl[1]) / 11;
    
    x[0] = x[0] + (ctrl[0] * 2) - 127;
    y[0] = y[0] + (ctrl[1] * 2) - 127;
    z[0] += 1 + (ctrl[2] / 4);
    scale_x[0] = 8000 + (ctrl[3] * 16);
    scale_y[0] = 8000 + (ctrl[4] * 16);
    
    //calculate the noise data
    uint8_t layer = 0;
    for (uint8_t i = 0; i < WIDTH; i++) {
        double ioffset = scale_x[layer] * (i - CENTER_X);
        for (uint8_t j = 0; j < HEIGHT; j++) {
            double joffset = scale_y[layer] * (j - CENTER_Y);
            uint16_t data = inoise16(x[layer] + ioffset, y[layer] + joffset, z[layer]);
            if (data < 11000) data = 11000;
            if (data > 51000) data = 51000;
            data = data - 11000;
            data = data / 41;
            noise[layer][i][j] = (noise[layer][i][j] + data) / 2;
        }
    }
    
    //map the colors
    //here the red layer
    for (uint8_t _y = 0; _y < HEIGHT; _y++) {
        for (uint8_t _x = 0; _x < WIDTH; _x++) {
            uint16_t i = noise[0][_x][_y];
            buffer1[XY(_x, _y)] = shifting_colors(a[i], true);
        }
    }
    
    // LAYER TWO
    //top left
    ctrl[0] = (ctrl[0] + noise[1][0][0] + noise[1][1][0] + noise[1][0][1] + noise[1][1][1]) / 20;
    //top right
    ctrl[1] = (ctrl[1] + noise[1][WIDTH - 1][0] + noise[1][WIDTH - 2][0] + noise[1][WIDTH - 1][1] +
               noise[1][WIDTH - 2][1]) / 20;
    //down left
    ctrl[2] = (ctrl[2] + noise[1][0][HEIGHT - 1] + noise[1][0][HEIGHT - 2] + noise[1][1][HEIGHT - 1] +
               noise[1][1][HEIGHT - 2]) / 20;
    //middle left
    ctrl[3] = (ctrl[3] + noise[1][0][CENTER_Y] + noise[1][1][CENTER_Y] + noise[1][0][CENTER_Y + 1] +
               noise[1][1][CENTER_Y + 1]) / 20;
    //center
    ctrl[4] =
            (ctrl[4] + noise[1][WIDTH - 1][CENTER_Y] + noise[1][WIDTH - 2][CENTER_Y] +
             noise[1][WIDTH - 1][CENTER_Y + 1] +
             noise[1][WIDTH - 2][CENTER_Y + 1]) / 20;
    ctrl[5] = (ctrl[5] + ctrl[0] + ctrl[1]) / 12;
    
    x[1] = x[1] + (ctrl[0]) - 127;
    y[1] = y[1] + (ctrl[1]) - 127;
    z[1] += 1 + (ctrl[2] / 4);
    scale_x[1] = 8000 + (ctrl[3] * 16);
    scale_y[1] = 8000 + (ctrl[4] * 16);
    
    //calculate the noise data
    layer = 1;
    for (uint8_t i = 0; i < WIDTH; i++) {
        double ioffset = scale_x[layer] * (i - CENTER_X);
        for (uint8_t j = 0; j < HEIGHT; j++) {
            double joffset = scale_y[layer] * (j - CENTER_Y);
            uint16_t data = inoise16(x[layer] + ioffset, y[layer] + joffset, z[layer]);
            if (data < 11000) data = 11000;
            if (data > 51000) data = 51000;
            data = data - 11000;
            data = data / 41;
            noise[layer][i][j] = (noise[layer][i][j] + data) / 2;
        }
    }
    
    //map the colors
    //here the blue layer
    for (uint8_t _y = 0; _y < HEIGHT; _y++) {
        for (uint8_t _x = 0; _x < WIDTH; _x++) {
            uint16_t i = noise[1][_x][_y];
            buffer2[XY(_x, _y)] = shifting_colors(a[i], false);
        }
    }
    
    // blend
    //for (uint16_t i = 0; i < NUM_LEDS; i++) {p_leds[i] = buffer1[i] + buffer2[i];}
    for (uint8_t _y = 0; _y < HEIGHT; _y++) {
        for (uint8_t _x = 0; _x < WIDTH; _x++) {
//            p_leds[XY(_x, _y)] = blend(buffer1[XY(_x, _y)], buffer2[XY(_x, _y)], noise[1][_y][_x] / 4);
            // you could also just add them:
            p_leds[XY(_x, _y)] = buffer1[XY(_x, _y)] + buffer2[XY(_x, _y)];
        }
    }
    
    //make it looking nice
    Utils::adjust_gamma();
}