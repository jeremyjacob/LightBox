#pragma once

#pragma once

#include "Panel.h"

class ConwaysLife {
public:
    ConwaysLife();
    void run();
    static constexpr const char *NAME = "Conways Life";
private:
    float speed = 1.0;
    CRGB color = CRGB::White;
    byte grid[NUM_LEDS]{};
    byte next[NUM_LEDS]{};
    CRGB lifebuf[NUM_LEDS]{};

private:
    void initarr();
    void updatelife();
    byte countNeighbors(byte x, byte y);
    static size_t hash_c_string(byte *p, size_t s);
};

ConwaysLife::ConwaysLife() {
    initarr();
}

void ConwaysLife::initarr() {
    for (byte &i: grid) i = (random8(6) == 0);
}

byte ConwaysLife::countNeighbors(byte x, byte y) {
    byte sum = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            byte col = (x + i + WIDTH) % (WIDTH);
            byte row = (y + j + HEIGHT) % (HEIGHT);
            sum += grid[XY(col, row)];
        }
    }
    sum -= grid[XY(x, y)];
    return sum;
}

void ConwaysLife::updatelife() {
    for (byte i = 0; i < WIDTH; i++) {
        for (byte j = 0; j < HEIGHT; j++) {
            byte state = grid[XY(i, j)];
            byte neighbors = countNeighbors(i, j);
            if (state == 0 && neighbors == 3) {
                next[XY(i, j)] = 1;
            } else if (state == 1 && (neighbors < 2 || neighbors > 3)) {
                next[XY(i, j)] = 0;
//                lifebuf[XY(i, j)] = CHSV(150, 180, 90);
            } else {
                next[XY(i, j)] = state;
            }
        }
    }
    
    for (int i = 0; i < NUM_LEDS; i++) {
        grid[i] = next[i];
        if (grid[i]) lifebuf[i] = color;
    }
}

void ConwaysLife::run() {
    static uint8_t repeat_count = 0;
    static size_t old_hash = 0;
    nblend(p_leds, lifebuf, NUM_LEDS, 25);
    
    if (repeat_count > 4) {
        initarr();
        repeat_count = 0;
    }
    
    EVERY_N_MILLISECONDS_I(timer, 100) {
        timer.setPeriod(100 / (speed * State::speed));
        static bool counter = false;
        counter = !counter;
        if (counter) {
            if (hash_c_string(grid, NUM_LEDS) == old_hash)
                repeat_count++;
            old_hash = hash_c_string(grid, NUM_LEDS);
        }
        
        fadeToBlackBy(lifebuf, NUM_LEDS, 145);
        // blur2d (leds,LED_COLS, LED_ROWS, 14);
        updatelife();
    }
}

size_t ConwaysLife::hash_c_string(byte *p, size_t s) {
    size_t result = 0;
    const size_t prime = 31;
    for (size_t i = 0; i < s; ++i)
        result = p[i] + (result * prime);
    return result;
}