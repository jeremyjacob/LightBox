#pragma once

#include "Panel.h"
#include <string>
#include "FontsDefs.h"


enum TextTypes {
    Text,
    Time,
    Stock,
    Crypto,
    Weather
};

class TextObject {
public:
public:
    TextObject(bool enabled, FONT fontName, uint16_t startX, uint16_t startY, std::string body,
               const CRGB &textColor, TextTypes type);
    
    FONT getFont();
    void setFont(FONT new_font_name);
    
    void typeMessage();
public:
    bool enabled = true;
    TextTypes type = Text;
    uint16_t cursor_x = start_x;
    uint16_t cursor_y = start_y;
    std::string body;
    CRGB text_color = CRGB::White;

private:
    FONT font_name = ADVOCUT;
    static constexpr byte SPACE_WIDTH = 2;
    Font font{}; // Initialized in constructor
    uint16_t start_x = 0;
    uint16_t start_y = 4;

private:
    void typeBlank(byte width = 1);
    
    void typeCharacter(byte font_pos);
    
    void clear();
    
};