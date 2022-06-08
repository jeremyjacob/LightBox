#pragma once

class Oscilloscope {
public:
    void run();
    static constexpr const char *NAME = "Oscilloscope";

private:
    float amplitudeX = 1.0;
    float amplitudeY = 1.0;
    uint16_t frequencyX = 60;
    uint16_t frequencyY = 60;
    uint16_t ephemerality = 9;
    uint16_t phaseX = 1;
    uint16_t phaseY = 1;
    uint16_t iphaseX = phaseX;
    uint16_t iphaseY = phaseY;
};

void Oscilloscope::run() {
    uint16_t sinX = beatsin8(frequencyX * 256, 0, HEIGHT, 0, iphaseX); // 0 to 32
    uint16_t sinY = beatsin8(frequencyY * 256, 0, HEIGHT, 0, iphaseY); // 0 to 16
    if (!sinY) {
        iphaseY += phaseY;
    }
    
    double cX = sinX - CENTER_Y;
    const int32_t x = round(cX * amplitudeX) + CENTER_X;
    double cY = sinY - CENTER_Y;
    const int32_t y = round(cY * amplitudeY) + CENTER_Y;
    p_leds[XY(x, y)] = CHSV(0, 190, 255);
    fadeToBlackBy(p_leds, NUM_LEDS, ephemerality);
//    blur2d(p_leds, WIDTH, HEIGHT, 18);
}
