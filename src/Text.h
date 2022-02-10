#pragma once

#include "Panel.h"
#include "FontsDefs.h"
#include <vector>


//class TextObject {
//public:
//    void x(uint16_t);
//
//    void y(uint16_t);
//
//    void color(CRGB new_color);
//
//    void text(const char *new_text);
//
//    void font(FONTS new_font);
//private:
//    static constexpr byte SPACE_WIDTH = 2;
//
//    byte font_height;
//    byte font_bytes[950];
//    uint16_t font_offsets[95];
//    uint16_t font_byte_len;
//    uint16_t font_offset_len;
//    byte cursor_x = 0;
//    byte cursor_y = 4;
//    char message[512];
//    CRGB text_color = CRGB::White;
//
//private:
//    void set_font(FONTS font);
//
//    void type_blank(byte width = 1);
//
//    void type_character(byte font_pos);
//
//    void set_text(const char *str);
//
//    void set_color(CRGB new_color);
//
//    void clear();
//
//    void type_message();
//};