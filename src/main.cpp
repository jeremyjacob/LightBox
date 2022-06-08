// Distributed Energetic Light Transmission Apparatus
#pragma GCC diagnostic ignored "-Wregister"
#define FASTLED_ALLOW_INTERRUPTS 0
//#define JSON_NOEXCEPTION
#define ARDUINOJSON_ENABLE_STD_STRING 1


#include <Arduino.h>
//#include <LITTLEFS.h>
//#include <cmath>
//#include "Spotify.h"
#include "Panel.h"
#include "Text.h"
#include "State.h"
#include "Palattes.h"
#include "Patterns.h"
#include "TextManager.h"
#include "Network.h"

void updateFromState() {
    Patterns::set(static_cast<Pattern>(State::pattern + 1)); // +1 to skip INIT
    FastLED.setBrightness(State::brightness);
    digitalWrite(SWITCH_PIN, State::enabled);
}


void setup() {
//    FastLED.setMaxRefreshRate(0);
    pinMode(SWITCH_PIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("Starting...");
//    if (!LITTLEFS.begin()) Serial.println("Error mounting LittleFS");
//    delay(1000);
    Network::setup();
    TextManager::setup();
    digitalWrite(SWITCH_PIN, HIGH);
    delay(50); // power-up safety delay
    randomSeed(analogRead(34));
    
    CFastLED::addLeds<WS2812, LED_PIN, GRB>(final_leds, NUM_LEDS + 1).setCorrection(CORRECTION);
    
    FastLED.setBrightness(28);
    
    fill_solid(p_leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    
    Serial.println("Started");
    Patterns::set(Pattern::AMEOBA);

//    TextManager::add();
//    TextManager::objects[0].set_text("Hello");
//    Text::set_font(FONT::VISITOR_TT1);
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
    EVERY_N_SECONDS(1) {
//        Spotify::tick();
//        Network::
//        State::update();
//        Serial.print("callback vector size: ");
//        Serial.println(State::callbacks.size());
//        Serial.print("test vector size: ");
//        Serial.println(State::testvec.size());
        
        Serial.print("Free Heap: ");
        Serial.print(ESP.getFreeHeap());
        Serial.print("  FPS: ");
        Serial.println(FastLED.getFPS());
    }
    
    EVERY_N_MILLIS(1000 / 30) {
        Network::sendPixels();
    }
    
    uint32_t heat = 0;
    EVERY_N_SECONDS(1) {
        heat += State::brightness;
        if (heat > 8000 * 30) {
            // Dim the screen
            FastLED.setBrightness(30);
            State::brightness = 30;
            Network::sendStateAll();
        }
        
        if (heat > 14000 * 30) {
            heat = 0;
            // Turn off the screen
            Patterns::set(Pattern::OFF);
            State::pattern = Pattern::OFF - 1;
            Network::sendStateAll();
        }
    }
    Network::ws.cleanupClients();
    Patterns::tick();
    TextManager::render();
    show();
}