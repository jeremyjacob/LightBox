#pragma once

#include "Panel.h"
#include "FontsDefs.h"

class TextObject {
public:
    void x(uint16_t);
    uint16_t x();

    void y(uint16_t);
    uint16_t y();

    void color(CRGB new_color);
    CRGB color();

    void text(const char *new_text);
    const char *text();

    void font(FONTS new_font);
    FONTS font();
};

namespace Text {
    static constexpr byte SPACE_WIDTH = 2;

    static byte font_height;
    static byte font_bytes[950];
    static uint16_t font_offsets[95];
    static uint16_t font_byte_len;
    static uint16_t font_offset_len;

    static byte cursor_x = 0;
    static byte cursor_y = 4;
    static char message[512];
    static CRGB color = CRGB::White;

    void set_font(FONTS font) {
        switch (font) {
            case ADVOCUT: //
                memcpy_P(font_bytes, advocut::bytes, advocut::byte_len * sizeof(byte));
                memcpy_P(font_offsets, advocut::offsets, advocut::offset_len * sizeof(uint16_t));
                font_byte_len = advocut::byte_len;
                font_offset_len = advocut::offset_len;
                font_height = advocut::height;
                break;
            case AUX_DOTBITC: //
                memcpy_P(font_bytes, aux_dotbitc::bytes, aux_dotbitc::byte_len * sizeof(byte));
                memcpy_P(font_offsets, aux_dotbitc::offsets, aux_dotbitc::offset_len * sizeof(uint16_t));
                font_byte_len = aux_dotbitc::byte_len;
                font_offset_len = aux_dotbitc::offset_len;
                font_height = aux_dotbitc::height;
                break;
            case AUX_DOTBITC_XTRA: //
                memcpy_P(font_bytes, aux_dotbitc_xtra::bytes, aux_dotbitc_xtra::byte_len * sizeof(byte));
                memcpy_P(font_offsets, aux_dotbitc_xtra::offsets, aux_dotbitc_xtra::offset_len * sizeof(uint16_t));
                font_byte_len = aux_dotbitc_xtra::byte_len;
                font_offset_len = aux_dotbitc_xtra::offset_len;
                font_height = aux_dotbitc_xtra::height;
                break;
            case AUX_DOTBITC_XTRA_BOLD: //
                memcpy_P(font_bytes, aux_dotbitc_xtra_bold::bytes, aux_dotbitc_xtra_bold::byte_len * sizeof(byte));
                memcpy_P(font_offsets, aux_dotbitc_xtra_bold::offsets,
                         aux_dotbitc_xtra_bold::offset_len * sizeof(uint16_t));
                font_byte_len = aux_dotbitc_xtra_bold::byte_len;
                font_offset_len = aux_dotbitc_xtra_bold::offset_len;
                font_height = aux_dotbitc_xtra_bold::height;
                break;
            case AUX_DOTBITC_XTRA_SMALLCAPS: //
                font_byte_len = aux_dotbitc_xtra_smallcaps::byte_len;
                font_offset_len = aux_dotbitc_xtra_smallcaps::offset_len;
                font_height = aux_dotbitc_xtra_smallcaps::height;
                memcpy_P(font_bytes, aux_dotbitc_xtra_smallcaps::bytes,
                         aux_dotbitc_xtra_smallcaps::byte_len * sizeof(byte));
                memcpy_P(font_offsets, aux_dotbitc_xtra_smallcaps::offsets,
                         aux_dotbitc_xtra_smallcaps::offset_len * sizeof(uint16_t));
                break;
            case BM_TUBE: //
                memcpy_P(font_bytes, bm_tube::bytes, bm_tube::byte_len * sizeof(byte));
                memcpy_P(font_offsets, bm_tube::offsets, bm_tube::offset_len * sizeof(uint16_t));
                font_byte_len = bm_tube::byte_len;
                font_offset_len = bm_tube::offset_len;
                font_height = bm_tube::height;
                break;
            case COMMODORE_64_PIXELISED: //

                memcpy_P(font_bytes, commodore_64_pixelised::bytes, commodore_64_pixelised::byte_len * sizeof(byte));
                memcpy_P(font_offsets, commodore_64_pixelised::offsets,
                         commodore_64_pixelised::offset_len * sizeof(uint16_t));
                font_byte_len = commodore_64_pixelised::byte_len;
                font_offset_len = commodore_64_pixelised::offset_len;
                font_height = commodore_64_pixelised::height;
                break;
            case HOMESPUN: //
                memcpy_P(font_bytes, homespun::bytes, homespun::byte_len * sizeof(byte));
                memcpy_P(font_offsets, homespun::offsets, homespun::offset_len * sizeof(uint16_t));
                font_byte_len = homespun::byte_len;
                font_offset_len = homespun::offset_len;
                font_height = homespun::height;
                break;
            case NAYUPIXEL: //
                memcpy_P(font_bytes, nayupixel::bytes, nayupixel::byte_len * sizeof(byte));
                memcpy_P(font_offsets, nayupixel::offsets, nayupixel::offset_len * sizeof(uint16_t));
                font_byte_len = nayupixel::byte_len;
                font_offset_len = nayupixel::offset_len;
                font_height = nayupixel::height;
                break;
            case SG05: //
                memcpy_P(font_bytes, sg05::bytes, sg05::byte_len * sizeof(byte));
                memcpy_P(font_offsets, sg05::offsets, sg05::offset_len * sizeof(uint16_t));
                font_byte_len = sg05::byte_len;
                font_offset_len = sg05::offset_len;
                font_height = sg05::height;
                break;
            case VISITOR_TT1: //
                memcpy_P(font_bytes, visitor_tt1::bytes, visitor_tt1::byte_len * sizeof(byte));
                memcpy_P(font_offsets, visitor_tt1::offsets, visitor_tt1::offset_len * sizeof(uint16_t));
                font_byte_len = visitor_tt1::byte_len;
                font_offset_len = visitor_tt1::offset_len;
                font_height = visitor_tt1::height;
                break;
            case VISITOR_TT2: //
                memcpy_P(font_bytes, visitor_tt2::bytes, visitor_tt2::byte_len * sizeof(byte));
                memcpy_P(font_offsets, visitor_tt2::offsets, visitor_tt2::offset_len * sizeof(uint16_t));
                font_byte_len = visitor_tt2::byte_len;
                font_offset_len = visitor_tt2::offset_len;
                font_height = visitor_tt2::height;
                break;
        }
    }


    void type_blank(byte width = 1) {
        for (int w = 0; w < width; ++w) {
            for (int row = 0; row < font_height; row++) {
                uint16_t led_pos = XY(cursor_x, row + cursor_y);
                t_leds[led_pos] = CRGB::Black;
            }
            cursor_x++;
        }
    }

    void type_character(byte font_pos) {
        Serial.print("typechar: ");
        Serial.println(font_pos + 33);
        Serial.print("cursor_x: ");
        Serial.println(cursor_x);

        uint16_t start_bit = font_offsets[font_pos]; //first bit of character
        uint16_t endBit = font_offsets[font_pos + 1]; //start of next char (or dummy char at end)
        Serial.print("start_bit: ");
        Serial.println(start_bit);
        Serial.print("endBit: ");
        Serial.println(endBit);
        Serial.print("font_offsets: ");
        for (int i = 0; i < font_offset_len; i++) {
            Serial.print(font_offsets[i]);
            Serial.print(" ");
        }
        Serial.println("");

        for (int colStart = start_bit; colStart < endBit; colStart += font_height) {
            Serial.print("colStart: ");
            Serial.println(colStart);
            for (int row = 0; row < font_height; row++) {
                Serial.print("row ");
                Serial.println(row);
                //calculate the bit position
                int bitPos = colStart + row;
                int byteOffset = bitPos / 8;
                int bitOffset = bitPos % 8;
                //read the individual bit
                uint16_t led_pos = XY(cursor_x, row + cursor_y);
                if (((font_bytes[byteOffset]) & (1 << bitOffset)) == 0) {
                    t_leds[led_pos] = CRGB::Black;
                    Serial.println("Black ");
                    Serial.print(cursor_x);
                    Serial.print(":");
                    Serial.println(cursor_y - row);
                } else {
                    t_leds[led_pos] = color;
                    Serial.println("White ");
                    Serial.print(cursor_x);
                    Serial.print(":");
                    Serial.println(cursor_y - row);
                }
            }
            cursor_x++;
        }
    }

    void set_text(const char *str) {
        strcpy(message, str);
    }

    void set_color(CRGB new_color) {
        color = new_color;
    }

    void clear() {
        cursor_x = 0;
        memset(t_leds, 0, sizeof(t_leds));
    }

    void type_message() {
        for (int letterPos = 0; letterPos < strlen(message); letterPos++) {

            //use ascii charcode to index font information starting with 33 = first printable char
            int font_pos = int(message[letterPos]) - 33;
            Serial.println("font_pos: " + String(font_pos));
            //draw space or letter
            if (font_pos == -1) {
                //it's a space
                type_blank(SPACE_WIDTH);
            } else {
                //it's a printable character. draw it
                type_character(font_pos);
            }
            type_blank(1);
        }
    }
};