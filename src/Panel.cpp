#include "Panel.h"

uint16_t XY(uint8_t x, uint8_t y) {
    // 7 - y because we count from top and the panels start from bottom left
    // x * 8 because there are 8 columns in the matrix
    // Last part wraps around to second row if y is on second row
    if (x > 29) return OVERFLOW_PIXEL;
    if (y > 14) return OVERFLOW_PIXEL;
    return (7 - y) + (x * 8) + ((y > 7) * 248);
}

uint16_t XY16(uint16_t x, uint16_t y) {
    // 7 - y because we count from top and the panels start from bottom left
    // x * 8 because there are 8 columns in the matrix
    // Last part wraps around to second row if y is on second row
    if (x > 29) return OVERFLOW_PIXEL;
    if (y > 14) return OVERFLOW_PIXEL;
    return (7 - y) + (x * 8) + ((y > 7) * 248);
}
