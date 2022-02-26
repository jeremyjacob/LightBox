#include "Text.h"

void TextObject::set_font(FONT new_font_name) {
    font_name = new_font_name;
    switch (new_font_name) {
        case ADVOCUT: //
            font.bytes = advocut::bytes;
            font.byte_len = advocut::byte_len;
            font.offsets = advocut::offsets;
            font.offset_len = advocut::offset_len;
            font.height = advocut::height;
            break;
        case AUX_DOTBITC: //
            font.bytes = aux_dotbitc::bytes;
            font.byte_len = aux_dotbitc::byte_len;
            font.offsets = aux_dotbitc::offsets;
            font.offset_len = aux_dotbitc::offset_len;
            font.height = aux_dotbitc::height;
            break;
        case AUX_DOTBITC_XTRA: //
            font.bytes = aux_dotbitc_xtra::bytes;
            font.byte_len = aux_dotbitc_xtra::byte_len;
            font.offsets = aux_dotbitc_xtra::offsets;
            font.offset_len = aux_dotbitc_xtra::offset_len;
            font.height = aux_dotbitc_xtra::height;
            break;
        case AUX_DOTBITC_XTRA_BOLD: //
            font.bytes = aux_dotbitc_xtra_bold::bytes;
            font.byte_len = aux_dotbitc_xtra_bold::byte_len;
            font.offsets = aux_dotbitc_xtra_bold::offsets;
            font.offset_len = aux_dotbitc_xtra_bold::offset_len;
            font.height = aux_dotbitc_xtra_bold::height;
            font.height = aux_dotbitc_xtra_bold::height;
            break;
        case AUX_DOTBITC_XTRA_SMALLCAPS: //
            font.bytes = aux_dotbitc_xtra_smallcaps::bytes;
            font.byte_len = aux_dotbitc_xtra_smallcaps::byte_len;
            font.offsets = aux_dotbitc_xtra_smallcaps::offsets;
            font.offset_len = aux_dotbitc_xtra_smallcaps::offset_len;
            font.height = aux_dotbitc_xtra_smallcaps::height;
        case BM_TUBE: //
            font.bytes = bm_tube::bytes;
            font.byte_len = bm_tube::byte_len;
            font.offsets = bm_tube::offsets;
            font.offset_len = bm_tube::offset_len;
            font.height = bm_tube::height;
            break;
        case COMMODORE_64_PIXELISED: //
            
            font.bytes = commodore_64_pixelised::bytes;
            font.byte_len = commodore_64_pixelised::byte_len;
            font.offsets = commodore_64_pixelised::offsets;
            font.offset_len = commodore_64_pixelised::offset_len;
            font.height = commodore_64_pixelised::height;
            font.height = commodore_64_pixelised::height;
            break;
        case HOMESPUN: //
            font.bytes = homespun::bytes;
            font.byte_len = homespun::byte_len;
            font.offsets = homespun::offsets;
            font.offset_len = homespun::offset_len;
            font.height = homespun::height;
            break;
        case NAYUPIXEL: //
            font.bytes = nayupixel::bytes;
            font.byte_len = nayupixel::byte_len;
            font.offsets = nayupixel::offsets;
            font.offset_len = nayupixel::offset_len;
            font.height = nayupixel::height;
            break;
        case SG05: //
            font.bytes = sg05::bytes;
            font.byte_len = sg05::byte_len;
            font.offsets = sg05::offsets;
            font.offset_len = sg05::offset_len;
            font.height = sg05::height;
            break;
        case VISITOR_TT1: //
            font.bytes = visitor_tt1::bytes;
            font.byte_len = visitor_tt1::byte_len;
            font.offsets = visitor_tt1::offsets;
            font.offset_len = visitor_tt1::offset_len;
            font.height = visitor_tt1::height;
            break;
        case VISITOR_TT2: //
            font.bytes = visitor_tt2::bytes;
            font.byte_len = visitor_tt2::byte_len;
            font.offsets = visitor_tt2::offsets;
            font.offset_len = visitor_tt2::offset_len;
            font.height = visitor_tt2::height;
            break;
    }
}

void TextObject::type_blank(byte width) {
    for (int w = 0; w < width; ++w) {
        for (int row = 0; row < font.height; row++) {
            uint16_t led_pos = XY(cursor_x, row + cursor_y);
            t_leds[led_pos] = CRGB::Black;
        }
        cursor_x++;
    }
}

void TextObject::type_character(byte font_pos) {
    uint16_t start_bit = font.offsets[font_pos]; //first bit of character
    uint16_t endBit = font.offsets[font_pos + 1]; //start of next char (or dummy char at end)
    
    for (int colStart = start_bit; colStart < endBit; colStart += font.height) {
        for (int row = 0; row < font.height; row++) {
            //calculate the bit position
            int bitPos = colStart + row;
            int byteOffset = bitPos / 8;
            int bitOffset = bitPos % 8;
            //read the individual bit
            uint16_t led_pos = XY(cursor_x, row + cursor_y);
            if (((font.bytes[byteOffset]) & (1 << bitOffset)) == 0) {
                t_leds[led_pos] = CRGB::Black;
            } else {
                t_leds[led_pos] = text_color;
            }
        }
        cursor_x++;
    }
}

void TextObject::set_text(const char *str, const size_t len) {
    message.assign(str, len);
}

void TextObject::set_text(const char *str) {
    message = str;
}

void TextObject::set_color(CRGB new_color) {
    text_color = new_color;
}

void TextObject::clear() {
    cursor_x = 0;
    memset(t_leds, 0, sizeof(t_leds));
}

void TextObject::type_message() {
    cursor_x = start_x;
    cursor_y = start_y;
    for (char letterPos: message) {
        
        //use ascii charcode to index font information starting with 33 = first printable char
        int font_pos = int(letterPos) - 33;
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

FONT TextObject::get_font() {
    return VISITOR_TT2;
}

void TextObject::set_x(uint16_t new_x) {
    start_x = new_x;
}

uint16_t TextObject::get_x() const {
    return start_x;
}

void TextObject::set_y(uint16_t new_y) {
    start_y = new_y;
}

uint16_t TextObject::get_y() const {
    return start_y;
}

CRGB TextObject::get_color() {
    return text_color;
}

const char *TextObject::get_text() {
    return message.c_str();
}

bool TextObject::get_enabled() {
    return enabled;
}

void TextObject::set_enabled(boolean) {
    enabled = true;
}

TextObject::TextObject() {
    set_font(font_name);
}
