#pragma once

namespace Utils {
    static uint32_t rgbToHex(uint8_t r, uint8_t g, uint8_t b) {
        return (r << 16) | (g << 8) | b;
    }
    
    static double millisd() {
        const double m = millis();
        return m;
    }
    
    static double mapd(double x, double in_min, double in_max, double out_min, double out_max) {
        const double dividend = out_max - out_min;
        const double divisor = in_max - in_min;
        const double delta = x - in_min;
        
        return (delta * dividend + (divisor / 2)) / divisor + out_min;
    }
    
    static void fill(CRGB *where, CRGB color) {
        // auto loop where
        for (auto i = 0; i < NUM_LEDS; i++) {
            where[i] = color;
        }
    }
    
    // cheap correction with gamma 2.0
    static void adjust_gamma() {
        // minimal brightness you want to allow
        // make sure to have the global brightnes on maximum and run no other color correction
        // a minimum of min = 1 might work fine for you and allow more contrast
        uint8_t min = 3;
        for (auto &led: p_leds) {
            led.r = dim8_video(led.r);
            led.g = dim8_video(led.g);
            led.b = dim8_video(led.b);
            
            if (led.r < min) led.r = min;
            if (led.g < min) led.g = min;
            if (led.b < min) led.b = min;
        }
    }
    
    static void mirror() {
        for (int x = 0; x < CENTER_X; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
//                Serial.print("mirring: ");
//                Serial.print(x);
//                Serial.print(" ");
//                Serial.println(y);
                
                p_leds[XY(WIDTH - x, y)] = p_leds[XY(x, y)];
            }
        }
    }
    
    static void rmirror() {
        for (int x = WIDTH; x > CENTER_X; --x) {
            for (int y = 0; y < HEIGHT; ++y) {
                p_leds[XY(WIDTH - x, y)] = p_leds[XY(x, y)];
            }
        }
    }

//    static char* identifier() {
//
//    }
};