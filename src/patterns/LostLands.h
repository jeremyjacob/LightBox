#pragma once

#include "Panel.h"

class LostLands {
public:
    void run();
    static constexpr const char *NAME = "Lost Lands";
private:
    void ImEff();
    
    void background();
    
    void backgroundObjects();
};

void LostLands::run() {
    background();
    backgroundObjects();
    ImEff();
}

extern const TProgmemRGBPalette16 HeLLthy
        FL_PROGMEM = {0x000000, 0x000033, 0x000099, 0x0000cc, 0x0000ff, 0x3300ff, 0x9900ff, 0xcc00ff, 0xff00ff,
                      0xff33ff,
                      0xff99ff, 0xffccff, 0xffffff, 0xCDDEDD, 0xDEDFE0, 0xB2BAB9};


void LostLands::background() {
    for (byte x = 0; x < WIDTH; x++) {
        for (byte y = 0; y < HEIGHT; y++) {
            p_leds[XY(x, y)] = ColorFromPalette(CloudColors_p,
                                                inoise8((x * 100), (y * 10) - (millis() / 10) * State::speed),
                                                255 - (abs(x - WIDTH / 2) * (255 / WIDTH * 2)));
        }
    }
}

void LostLands::backgroundObjects() {
    for (byte x = 0; x < WIDTH; x++) {
        for (byte y = 0; y < HEIGHT; y++) {
            p_leds[XY(x, y)] -= CHSV(0, 0, inoise8(x * 50, y * 50, (millis() / 10) * State::speed));
        }
    }
}

void LostLands::ImEff() {
    blur2d(p_leds, WIDTH, HEIGHT, 8);
}