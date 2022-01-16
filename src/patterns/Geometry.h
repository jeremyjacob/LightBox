#pragma once

#include "Panel.h"

class Geometry {
public:
    void run();

public:
    int8_t speed = -5;

private:
    static void drawLine(byte x, byte y, byte x1, byte y1, CRGB color, bool dot, bool grad);

private:

};

void Geometry::run() {
    static byte hue = 0;
    EVERY_N_MILLISECONDS(30) { hue++; }  //30 - speed of hue change

    byte x1 = beatsin8(18 + speed, 0, (WIDTH - 1));
    byte x2 = beatsin8(23 + speed, 0, (WIDTH - 1));
    byte x3 = beatsin8(27 + speed, 0, (WIDTH - 1));
    byte x4 = beatsin8(31 + speed, 0, (WIDTH - 1));
    byte x5 = beatsin8(33 + speed, 0, (WIDTH - 1));

    byte y1 = beatsin8(20 + speed, 0, (HEIGHT - 1));
    byte y2 = beatsin8(26 + speed, 0, (HEIGHT - 1));
    byte y3 = beatsin8(15 + speed, 0, (HEIGHT - 1));
    byte y4 = beatsin8(27 + speed, 0, (HEIGHT - 1));
//    byte y5 = beatsin8(30 + speed, 0, (HEIGHT - 1));

    CRGB color = CHSV(hue, 255, 255);

    fadeToBlackBy(p_leds, NUM_LEDS, 60);

    drawLine(x1, y1, x2, y2, color, true, false); // 1 is white dot 0 is no white dot
    drawLine(x2, y2, x3, y3, color, true, false);
    drawLine(x3, y3, x1, y1, color, 1, false);
    drawLine(x4, y4, x1, y1, color, 1, false);
    drawLine(x4, y4, x2, y2, color, true, false);
    drawLine(x4, y4, x3, y3, color, true, 0);
    blur2d(p_leds, WIDTH, HEIGHT, 8);
    ;
}

void Geometry::drawLine(byte x, byte y, byte x1, byte y1, CRGB color, bool dot,
                        bool grad) {   // my ugly line draw function )))

    byte xsteps = abs8(x - x1) + 1;
    byte ysteps = abs8(y - y1) + 1;
    byte steps = xsteps > ysteps ? xsteps : ysteps;

    for (byte i = 0; i <= steps; i++) {
        byte dx = lerp8by8(x, x1, i * 255 / steps);
        byte dy = lerp8by8(y, y1, i * 255 / steps);
        int index = XY(dx, dy);
        p_leds[index] += color;    // change to += for brightness look
        if (grad) p_leds[index] %= (i * 255 / steps);  //for draw gradient line
    }

    if (dot) {     //add white point at the ends of line
        p_leds[XY(x, y)] += CRGB::White;
        p_leds[XY(x1, y1)] += CRGB::White;
    }
}
