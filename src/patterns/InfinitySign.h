#pragma once

class InfinitySign {
public:
    void run();

public:
    int8_t speed = 25;
};

void InfinitySign::run() {
    CRGB color = CHSV(millis() / (1500 / speed), 100, 130);
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1), beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4))] += color;
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) + 1, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4))] += color;
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) - 1, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4))] += color;
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1), beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) + 1)] += color;
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1), beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) - 1)] += color;
//    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) + 2, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4))] += color.subtractFromRGB(4);
//    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) - 2, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4))] += color.subtractFromRGB(4);
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1),
            beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) + 2)] += color.subtractFromRGB(4);
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1),
            beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) - 2)] += color.subtractFromRGB(4);

    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) + 1, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) + 1)] += color;
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) - 1, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) - 1)] += color;
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) - 1, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) + 1)] += color;
    p_leds[XY(beatsin8(speed, 0, WIDTH - 1) + 1, beatsin8(speed * 2, HEIGHT / 4, HEIGHT - 1 - HEIGHT / 4) - 1)] += color;
    //    blur2d(p_leds, WIDTH, HEIGHT, 15);
    fadeToBlackBy(p_leds, NUM_LEDS, 8);
//    FastLED.delay(5);
}
