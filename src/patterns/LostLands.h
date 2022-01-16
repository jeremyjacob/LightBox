#pragma once

#include "Panel.h"

class LostLands {
public:
    void run();

private:
    void ImEff();

    void background();

    void backgroundObjects();
};

#define variant 2

void LostLands::run() {
    background();
    backgroundObjects();
    //Person();
    //Objects();
    ImEff();
    ;
}

extern const TProgmemRGBPalette16 HeLLthy
        FL_PROGMEM = {0x000000, 0x000033, 0x000099, 0x0000cc, 0x0000ff, 0x3300ff, 0x9900ff, 0xcc00ff, 0xff00ff,
                      0xff33ff,
                      0xff99ff, 0xffccff, 0xffffff, 0xCDDEDD, 0xDEDFE0, 0xB2BAB9};


void LostLands::background() {
    for (byte x = 0; x < WIDTH; x++) {
        for (byte y = 0; y < HEIGHT; y++) {
            switch (variant) {
                case 0:
                    p_leds[XY(x, y)] = ColorFromPalette(HeatColors_p, inoise8(x * 10, (y * 50) + millis() / 100),
                                                      y * (255 / HEIGHT));
                    break;
                case 1:
                    p_leds[XY(x, y)] = ColorFromPalette(OceanColors_p, inoise8((x * 50), (y * 10) + millis() / 10) / 2.5,
                                                      255 - y * (255 / HEIGHT));
                    break;
                case 2:
                    p_leds[XY(x, y)] = ColorFromPalette(CloudColors_p, inoise8((x * 100), (y * 10) - millis() / 10),
                                                      255 - (abs(x - WIDTH / 2) * (255 / WIDTH * 2)));
                    break;
                case 3:
                    p_leds[XY(x, y)] = ColorFromPalette(PartyColors_p, inoise8((x * (HEIGHT - 1 - y)) + (y * 10),
                                                                             (y * 50) + millis() / 100),
                                                      y * (255 / HEIGHT));
                    break;
                case 4:
                    p_leds[XY(x, y)] = CHSV(0, 0, inoise8(x * 100, (y * 100) - millis() / 100));
                    break;
                case 5:
                    p_leds[XY(x, y)] = CHSV(150, 150, inoise8(x * 100, y * 100, millis() / 10));
                    break;
                case 6:
                    p_leds[XY(x, y)] = ColorFromPalette(HeLLthy, 255 - inoise8(x * 100, y * 10, millis() / 10));
                    break;
            }
        }
    }
}

void LostLands::backgroundObjects() {
    for (byte x = 0; x < WIDTH; x++) {
        for (byte y = 0; y < HEIGHT; y++) {
            switch (variant) {
                case 0:
                    p_leds[XY(x, y)] -= CHSV(0, 0, inoise8(x * 50, y * 10, millis() / 100));
                    break;
                case 2:
                    p_leds[XY(x, y)] -= CHSV(0, 0, inoise8(x * 50, y * 50, millis() / 10));
                    break;
                case 3:
                    p_leds[XY(x, y)] -= CHSV(0, 0, inoise8(y * 50, (x * (HEIGHT - 1 - y)) + (y * 10), millis() / 10));
                    break;
                case 4:
                    p_leds[XY(x, y)] -= CHSV(0, ((abs(y - HEIGHT / 2) + abs(x - WIDTH / 2))) *
                                                (255 / ((WIDTH * 2) + (HEIGHT * 2))),
                                             inoise8(abs(WIDTH / 2 - x) * 50, y * 50, millis() / 10));
                    break;
            }
        }
    }
}

void LostLands::ImEff() {
    blur2d(p_leds, WIDTH, HEIGHT, 8);
}