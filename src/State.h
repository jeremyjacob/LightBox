#pragma once

#include <ArduinoJson.h>

//#include "Patterns.h"
//#include "StateFile.h"

namespace Network {
    void broadcast(char *string);
    void broadcast(const char *string);
}

namespace Utils {
    static uint32_t rgbToHex(uint8_t r, uint8_t g, uint8_t b);
}
void updateFromState();

struct TextComponent {
    uint8_t type = 0;
    uint8_t font = 0;
    int8_t x = 0;
    int8_t y = 0;
    boolean enabled = true;
    uint32_t color = 16777215;
    std::string body;
};

void convertToJson(std::vector<TextObject> src, JsonVariant dst) {
    for (auto obj: src) {
        auto ref = dst.addElement();
        ref["type"] = obj.type;
        ref["font"] = obj.getFont();
        ref["x"] = obj.cursor_x;
        ref["y"] = obj.cursor_y;
        ref["enabled"] = obj.enabled;
        ref["color"] = Utils::rgbToHex(obj.text_color.r, obj.text_color.g, obj.text_color.b);
        ref["body"] = obj.body;
    }
}

namespace State {
    using namespace ArduinoJson6194_F1;
    
    bool enabled = true;
    uint8_t streamLayer = 0;
    uint8_t brightness = 30;
    float speed = 1.0;
    uint8_t pattern = 1;
    std::vector<TextObject> textComponents;
    
    void merge(const uint8_t *data, const size_t len) {
        const std::string str(reinterpret_cast<const char *>(data), len);
        try {
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, str);
            enabled = doc["enabled"] | true;
            streamLayer = doc["streamLayer"] | streamLayer;
            brightness = doc["brightness"] | brightness;
            speed = doc["speed"] | speed;
            pattern = doc["pattern"] | pattern;
            if (doc["text"]) {
                textComponents.clear();
                JsonArray text = doc["text"];
                for (JsonVariant v: text) {
                    TextObject t(v["enabled"] | true, static_cast<FONT>(v["font"] | 0), v["x"] | 0,
                                 v["y"] | 0, v["body"] | "", v["color"] | 16777215,
                                 static_cast<TextTypes>(v["type"] | 0)
                    );
                    
                    Network::broadcast("Adding text: ");
                    Network::broadcast(t.body.c_str());
                    
                    textComponents.push_back(t);
                }
            }
        } catch (std::exception &e) {
            Serial.println(e.what());
        }
        updateFromState();
    }
    
    std::basic_string<char> asJsonString() {
        DynamicJsonDocument doc(1024);
        doc["enabled"] = enabled;
        doc["streamLayer"] = streamLayer;
        doc["brightness"] = brightness;
        doc["speed"] = speed;
        doc["pattern"] = pattern;
        doc["text"] = textComponents;
//        for (const auto &text: textComponents) {
//            ArrayRef array = doc.createNestedArray("text");
//            array.add(text);
//        }
        std::string str;
        serializeJson(doc, str);
        return str;
    }
}