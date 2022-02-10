// Distributed Energetic Light Transmission Apparatus
#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
//#include "Networking.h"
//#include "Spotify.h"
#include "Panel.h"
#include "Palattes.h"
#include "Patterns.h"
#include "Text.h"

void setup() {
    pinMode(SWITCH_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("Starting...");
//    delay(1000);
//    Network::setup();
    digitalWrite(SWITCH_PIN, HIGH);
    delay(50); // power-up safety delay
    randomSeed(analogRead(34));

    CFastLED::addLeds<WS2812, LED_PIN, GRB>(final_leds, OVERFLOW_PIXEL).setCorrection(CORRECTION);
    FastLED.setBrightness(28);
    fill_solid(p_leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    Patterns::set(Patterns::PLASM);
//    Text::set_font(FONTS::VISITOR_TT1);
//    Text::set_text("Flame");
//    Text::set_color(CRGB::OrangeRed);
//    Text::cursor_y = 2;
//    Text::type_message();
//    Spotify::sendRequest();
}

void show() {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        final_leds[i] = p_leds[i];
    }
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        if (t_leds[i]) {
            final_leds[i] = t_leds[i];
        }
    }
    FastLED.show();
}

void loop() {
//    EVERY_N_SECONDS(5) {
//        Spotify::tick();
//    }

    Patterns::tick();
    show();
}