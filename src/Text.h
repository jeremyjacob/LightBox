#pragma once

#include "Panel.h"
#include <string>
#include "FontsDefs.h"

class TextObject {
public:
    TextObject();
public:
    [[nodiscard]] uint16_t get_x() const;
    void set_x(uint16_t new_x);
    
    [[nodiscard]] uint16_t get_y() const;
    void set_y(uint16_t new_y);
    
    CRGB get_color();
    void set_color(CRGB new_color);
    
    const char *get_text();
    void set_text(const char *str, size_t len);
    void set_text(const char *str);
    
    FONT get_font();
    void set_font(FONT new_font_name);
    
    bool get_enabled();
    void set_enabled(boolean);
    
    void type_message();
private:
    static constexpr byte SPACE_WIDTH = 2;
    bool enabled = true;
    FONT font_name = ADVOCUT;
    Font font{}; // Initialized in constructor
    uint16_t start_x = 0;
    uint16_t start_y = 4;
    uint16_t cursor_x = start_x;
    uint16_t cursor_y = start_y;
    std::string message;
    CRGB text_color = CRGB::White;

private:
    void type_blank(byte width = 1);
    
    void type_character(byte font_pos);
    
    void clear();
    
};