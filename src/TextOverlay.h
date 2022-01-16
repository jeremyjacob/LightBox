#pragma once

#include "Panel.h"
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>

class cMatrix : public cLEDMatrix<WIDTH, HEIGHT + 1, VERTICAL_MATRIX> {
    uint16_t mXY(uint16_t x, uint16_t y) override {
        Serial.println(XY(x, y));
        return XY(x, y);
    }
};

cMatrix matrix;
cLEDText scrolling_msg;

const unsigned char TxtDemo[] = {EFFECT_SCROLL_LEFT "            LEFT SCROLL "
                                 EFFECT_SCROLL_RIGHT "            LLORCS THGIR"
                                 EFFECT_SCROLL_DOWN "            SCROLL DOWN             SCROLL DOWN            " EFFECT_FRAME_RATE "\x04" " SCROLL DOWN            " EFFECT_FRAME_RATE "\x00" " "
                                 EFFECT_SCROLL_UP "             SCROLL UP               SCROLL UP             " EFFECT_FRAME_RATE "\x04" "  SCROLL UP             " EFFECT_FRAME_RATE "\x00" " "
                                 EFFECT_CHAR_UP EFFECT_SCROLL_LEFT "            UP"
                                 EFFECT_CHAR_RIGHT "  RIGHT"
                                 EFFECT_CHAR_DOWN "  DOWN"
                                 EFFECT_CHAR_LEFT "  LEFT"
                                 EFFECT_HSV_CV "\x00\xff\xff\x40\xff\xff" EFFECT_CHAR_UP "           HSV_CV 00-40"
                                 EFFECT_HSV_CH "\x00\xff\xff\x40\xff\xff" "    HSV_CH 00-40"
                                 EFFECT_HSV_AV "\x00\xff\xff\x40\xff\xff" "    HSV_AV 00-40"
                                 EFFECT_HSV_AH "\x00\xff\xff\xff\xff\xff" "    HSV_AH 00-FF"
                                 "           " EFFECT_HSV "\x00\xff\xff" "R" EFFECT_HSV "\x20\xff\xff" "A" EFFECT_HSV "\x40\xff\xff" "I" EFFECT_HSV "\x60\xff\xff" "N" EFFECT_HSV "\xe0\xff\xff" "B" EFFECT_HSV "\xc0\xff\xff" "O"
                                 EFFECT_HSV "\xa0\xff\xff" "W" EFFECT_HSV "\x80\xff\xff" "S " EFFECT_DELAY_FRAMES "\x00\x96" EFFECT_RGB "\xff\xff\xff"};

void setup_text() {
    scrolling_msg.SetFont(MatriseFontData);
    scrolling_msg.Init(&matrix, matrix.Width(), scrolling_msg.FontHeight() + 1, 0, 0);
    scrolling_msg.SetText((unsigned char *) TxtDemo, sizeof(TxtDemo) - 1);
    scrolling_msg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
}

void run_text() {
    if (scrolling_msg.UpdateText() == -1)
        scrolling_msg.SetText((unsigned char *) TxtDemo, sizeof(TxtDemo) - 1);
    else {
//        CRGB *x = matrix[0]
    }
//    FastLED.delay(10);
}