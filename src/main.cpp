#include <Arduino.h>

#include "Panel.h"
#include "RunPattern.h"

static constexpr uint8_t BRIGHTNESS = 15;

void setup() {
    pinMode(5, OUTPUT);
//    delay(3000); // power-up safety delay

    Serial.begin(115200);
    digitalWrite(5, HIGH);
    delay(100);
    LEDS::strip.Begin();
    LEDS::strip.SetBrightness(BRIGHTNESS);
    LEDS::set_all(HsbColor(0, 0, 0));
    LEDS::strip.SetPixelColor(1, Rgb16Color(100, 0, 100));
    LEDS::strip.Show();

}

void loop() {
//    delay(3000);
//    LEDS::set_all(HsbColor(0, 0, 0));

//    for (int i = 0; i < 481; ++i) {
//        LEDS::strip.SetPixelColor(i, HsbColor(0.3, 1, 1));
//        LEDS::strip.SetPixelColor(i - 1, HsbColor(0.3, 1, 0));
//        LEDS::strip.Show();
//    }
    RunPattern::tick();
}