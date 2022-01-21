// Distributed Energetic Light Transmission Aparatus
#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
#include "Panel.h"
#include "Palattes.h"
#include "Patterns.h"
#include "Text.h"
//#include "Networking.h"

void setup() {
    pinMode(SWITCH_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("Starting...");
//    delay(1000);
//    networkSetup();
    digitalWrite(SWITCH_PIN, HIGH);
    delay(50); // power-up safety delay
    randomSeed(analogRead(5));

    CFastLED::addLeds<WS2812, 3, GRB>(final_leds, OVERFLOW_PIXEL).setCorrection(CORRECTION);
    FastLED.setBrightness(28);
    fill_solid(p_leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    Patterns::set(Patterns::FIREPLACE);
    Text::set_font(FONTS::VISITOR_TT1);
    Text::set_text("Flame");
    Text::set_color(CRGB::OrangeRed);
    Text::cursor_y = 2;
    Text::type_message();
}

void show() {
//    memcpy(&final_leds, &p_leds, sizeof(CRGB) * NUM_LEDS);
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        if (p_leds[i]) {
            final_leds[i] = p_leds[i];
        }
    }
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        if (t_leds[i]) {
            final_leds[i] = t_leds[i];
        }
    }
    FastLED.show();
}

void loop() {
//    Text::set_font(FONTS::VISITOR_TT1);
//    Text::set_text("Fuck");
//    Text::set_color(CRGB::Red);
//    Text::type_message();
//    show();
//    FastLED.delay(1500);
//    Text::clear();
//    Text::set_font(FONTS::VISITOR_TT2);
//    Text::set_text("You!");
//    Text::set_color(CRGB::DarkOliveGreen);
//    Text::type_message();
//    show();
//    FastLED.delay(1500);
//    Text::clear();
//    blend(&p_leds[0], matrix[0], &final_leds[0], NUM_LEDS, 127);
    Patterns::tick();
    show();
//    memcpy(&final_leds, &p_leds, sizeof(CRGB) * NUM_LEDS);
}