// Distributed Energetic Light Transmission Aparatus
#define FASTLED_ALLOW_INTERRUPTS 0

#include <Arduino.h>
#include "Panel.h"
#include "Palattes.h"
#include "TextOverlay.h"
#include "Patterns.h"
//#include "Networking.h"

void setup() {
    pinMode(SWITCH_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("Starting...");
//    networkSetup();
    digitalWrite(SWITCH_PIN, HIGH);
    delay(50); // power-up safety delay
    randomSeed(analogRead(5));

    CFastLED::addLeds<WS2812, 3, GRB>(final_leds, OVERFLOW_PIXEL).setCorrection(CORRECTION);
    FastLED.setBrightness(28);
    fill_solid(p_leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    Patterns::set(Patterns::FIREPLACE);
    setup_text();
}

void loop() {
//    blend(&p_leds[0], matrix[0], &final_leds[0], NUM_LEDS, 127);
    Patterns::tick();
//    run_text();
    memcpy(&final_leds, &p_leds, sizeof(CRGB) * NUM_LEDS);
    FastLED.show();
}