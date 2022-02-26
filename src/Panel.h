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
constexpr uint8_t MAX_BRIGHTNESS = 255;

inline CRGB p_leds[NUM_LEDS]; // Pattern LEDs
inline CRGB t_leds[NUM_LEDS]; // DText LEDs
inline CRGB final_leds[NUM_LEDS];

// Could be syntactically improved with templates
uint16_t XY(uint8_t x, uint8_t y);
uint16_t XY16(uint16_t x, uint16_t y);