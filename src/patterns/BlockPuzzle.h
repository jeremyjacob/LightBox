#pragma once

class BlockPuzzle {
public:
    void run();

public:
    uint16_t delay = 250;

private:
    float speed_move = 0.5;

    void drawPixelXYF(float x, float y, const CRGB &color);

    static void draw_square(byte x1, byte y1, byte x2, byte y2, byte col);

    void draw_squareF(float x1, float y1, float x2, float y2, byte col);

private:
    static const uint8_t PSizeX = 4;
    static const uint8_t PSizeY = 4;
    constexpr static const float Ecols = (WIDTH / PSizeX);
    constexpr static const float Erows = (HEIGHT / PSizeY);
    static const bool Ca = (WIDTH % PSizeX) ? true : false;
    static const bool Ra = (HEIGHT % PSizeY) ? true : false;
    static constexpr int PCols = Ecols + Ca;
    static constexpr int PRows = Erows + Ra;

    byte puzzle[PCols][PRows];
    byte tmpp;
    byte z_dot[2];
    byte etap;
    int8_t move[2];
    float shift[2] = {0, 0};
    bool XorY;
    bool setup = true;
};

void BlockPuzzle::run() {
    if (setup) {
        etap = 0;
        for (byte x = 0; x < PCols; x++) {
            for (byte y = 0; y < PRows; y++) { puzzle[x][y] = random8(16, 255); }
        }
        z_dot[0] = random(0, PCols);
        z_dot[1] = random(0, PRows);
        puzzle[z_dot[0]][z_dot[1]] = 0;
        setup = false;
    }

    for (byte x = 0; x < PCols; x++) {
        for (byte y = 0; y < PRows; y++) {
            draw_square(x * PSizeX, y * PSizeY, (x + 1) * PSizeX, (y + 1) * PSizeY, puzzle[x][y]);
        }
    }
    switch (etap) {
        case 0:
            FastLED.delay(delay);
            XorY = !XorY;
            if (XorY) {
                if (z_dot[0] == PCols - 1)
                    move[0] = -1;
                else if (z_dot[0] == 0) move[0] = 1;
                else move[0] = (move[0] == 0) ? (random() % 2) * 2 - 1 : move[0];
            } else {
                if (z_dot[1] == PRows - 1)
                    move[1] = -1;
                else if (z_dot[1] == 0) move[1] = 1;
                else move[1] = (move[1] == 0) ? (random() % 2) * 2 - 1 : move[1];
            }
            move[(XorY) ? 1 : 0] = 0;
            etap = 1;
            break;
        case 1:
            tmpp = puzzle[z_dot[0] + move[0]][z_dot[1] + move[1]];
            puzzle[z_dot[0] + move[0]][z_dot[1] + move[1]] = 0;
            etap = 2;
            break;
        case 2:
            draw_squareF(((z_dot[0] + move[0]) * PSizeX) + shift[0], ((z_dot[1] + move[1]) * PSizeY) + shift[1],
                         ((z_dot[0] + move[0] + 1) * PSizeX) + shift[0], (z_dot[1] + move[1] + 1) * PSizeY + shift[1],
                         tmpp);
            shift[0] -= (move[0] * speed_move);
            shift[1] -= (move[1] * speed_move);
            if ((fabs(shift[0]) >= WIDTH / PCols) || (fabs(shift[1]) >= HEIGHT / PRows)) {
                shift[0] = 0;
                shift[1] = 0;
                puzzle[z_dot[0]][z_dot[1]] = tmpp;
                etap = 3;
            }
            break;
        case 3:
            z_dot[0] += move[0];
            z_dot[1] += move[1];
            etap = 0;
            break;
    }
}

void BlockPuzzle::drawPixelXYF(float x, float y,
                               const CRGB &color) {
    // extract the fractional parts and derive their inverses
    uint8_t xx = (x - (int) x) * 255, yy = (y - (int) y) * 255, ix = 255 - xx, iy = 255 - yy;
    // calculate the intensities for each affected pixel
#define WU_WEIGHT(a, b)((uint8_t)(((a) * (b) + (a) + (b)) >> 8))
    uint8_t wu[4] = {
            WU_WEIGHT(ix, iy),
            WU_WEIGHT(xx, iy),
            WU_WEIGHT(ix, yy),
            WU_WEIGHT(xx, yy)
    };
    // multiply the intensities by the colour, and saturating-add them to the pixels
    for (uint8_t i = 0; i < 4; i++) {
        int16_t xn = x + (i & 1), yn = y + ((i >> 1) & 1);
        CRGB clr = p_leds[XY(xn, yn)];
        clr.r = qadd8(clr.r, (color.r * wu[i]) >> 8);
        clr.g = qadd8(clr.g, (color.g * wu[i]) >> 8);
        clr.b = qadd8(clr.b, (color.b * wu[i]) >> 8);
        p_leds[XY(xn, yn)] = clr;
    }
#undef WU_WEIGHT
}

void BlockPuzzle::draw_square(byte x1, byte y1, byte x2, byte y2, byte col) {
    for (byte x = x1; x < x2; x++) {
        for (byte y = y1; y < y2; y++) {
            if (col == 0) { p_leds[XY(x, y)] = CRGB(0, 0, 0); }
            else if ((x == x1 || x == x2 - 1) || (y == y1 || y == y2 - 1))
                p_leds[XY(x, y)] = ColorFromPalette(RainbowColors_p, col - 26).subtractFromRGB(10);
            else p_leds[XY(x, y)] = ColorFromPalette(RainbowColors_p, col);
        }
    }
}

void BlockPuzzle::draw_squareF(float x1, float y1, float x2, float y2, byte col) {
    byte Lx = x2 - x1;
    byte Ly = y2 - y1;
    for (byte x = 0; x < Lx; x++) {
        for (byte y = 0; y < Ly; y++) {
            if (col == 0) { p_leds[XY(x, y)] = CRGB(0, 0, 0); }
            else if ((x == 0 || x == Lx - 1) || (y == 0 || y == Ly - 1))
                drawPixelXYF(x1 + x, y1 + y, ColorFromPalette(RainbowColors_p, col - 26).subtractFromRGB(10));
            else drawPixelXYF(x1 + x, y1 + y, ColorFromPalette(RainbowColors_p, col));
        }
    }
}
