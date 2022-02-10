#pragma once

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_DMA

#include <FastLED.h>

constexpr uint32_t CORRECTION = 0xFFB0F0;
constexpr byte SWITCH_PIN = 18;
constexpr byte LED_PIN = 4;
constexpr uint16_t NUM_LEDS = 480;
constexpr uint16_t OVERFLOW_PIXEL = 481;
constexpr uint16_t WIDTH = 30;
constexpr uint16_t HEIGHT = 15;
constexpr uint16_t CENTER_X = WIDTH / 2;
constexpr uint16_t CENTER_Y = HEIGHT / 2;
constexpr uint8_t BRIGHTNESS = 30;

inline CRGB p_leds[NUM_LEDS]; // Pattern LEDs
inline CRGB t_leds[NUM_LEDS]; // DText LEDs
inline CRGB final_leds[NUM_LEDS];

// Could be syntactically improved with templates
uint16_t XY(uint8_t x, uint8_t y) {
    // 7 - y because we count from top and the panels start from bottom left
    // x * 8 because there are 8 columns in the matrix
    // Last part wraps around to second row if y is on second row
    if (x > 29) return OVERFLOW_PIXEL;
    if (y > 14) return OVERFLOW_PIXEL;
    return (7 - y) + (x * 8) + ((y > 7) * 248);
}

uint16_t XY16(uint16_t x, uint16_t y) {
    // 7 - y because we count from top and the panels start from bottom left
    // x * 8 because there are 8 columns in the matrix
    // Last part wraps around to second row if y is on second row
    if (x > 29) return OVERFLOW_PIXEL;
    if (y > 14) return OVERFLOW_PIXEL;
    return (7 - y) + (x * 8) + ((y > 7) * 248);
}
