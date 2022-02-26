#pragma once

#define ARDUINOJSON_DECODE_UNICODE 0
#define ARDUINOJSON_ENABLE_PROGMEM 0

#include <vector>
#include <map>
#include <any>
#include "Text.h"
#include "Patterns.h"
#include <ArduinoJson.h>
//#include <ArduinoJson.h/>


namespace State {
//    using namespace ArduinoJson6192_70;
    constexpr const char *CONFIG_PATH = "config.json";
    
    struct Config {
        uint8_t brightness = 30;
        std::vector<TextObject> text;
        Pattern pattern = Pattern::AMEOBA;
        std::map<std::string, std::map<std::string, std::any>> patterns;
    };
    Config config;
    
    void loadConfig() {
        File file = LITTLEFS.open(CONFIG_PATH);
        if (!file || file.isDirectory()) {
            Serial.println("Failed to open file for reading");
            return;
        }
        
        DynamicJsonDocument doc(2048);
        // Deserialize the JSON document
        DeserializationError error = deserializeJson(doc, file);
        if (error) Serial.println("Failed to deserialize from FS");
        
        config.brightness = doc["brightness"];
        config.pattern = (Pattern) doc["pattern"];
        JsonArray textArray = doc["text"];
        std::vector<TextObject> textVec;
        for (JsonObject textJSON: textArray) {
            TextObject textObject;
            if (!textJSON["color"].isNull()) textObject.set_color(textJSON["color"].isNull());
        }
    }
    
    
    void onUpdate() {
        if (config.pattern != Patterns::selected_pattern) {
            Patterns::set(config.pattern);
        }
    }
    
    void merge(JsonVariant dst, JsonVariantConst src) {
        if (src.is<JsonObject>()) {
            for (auto kvp: src.as<JsonObject>()) {
                merge(dst.getOrAddMember(kvp.key()), kvp.value());
            }
        } else {
            dst.set(src);
        }
    }
    
    void merge(JsonVariantConst patch) {
        merge(doc.as<JsonVariant>(), patch);
    }
    
    char json[] = R"json({
      "brightness": 30,
      "text": [
        {
          "type": 0,
          "font": 0,
          "x": 0,
          "y": 0,
          "color": 12415515,
          "body": "Hello!"
        }
      ],
      "pattern": 0,
      "patterns": {
        "Ameoba": {
          "speed": 1.0
        },
        "AssortedNoise": {
          "cycleTime": 1,
          "cycle": true,
          "mode": 1
        },
        "BlockPuzzle": {
          "speed": 1.0
        },
        "CrossHatch": {
          "speed": 1.0
        },
        "EnergyBalls": {},
        "Fireplace": {
          "scale": 1.0,
          "speed": 1.0
        },
        "FireRings": {},
        "Galaxy": {
          "speed": 1.0
        },
        "Geometry": {
          "speed": 1.0
        },
        "IcyNoise": {
          "speed": 1.0
        },
        "InfinitySign": {
          "speed": 1.0
        },
        "Living": {
          "speed": 1.0,
          "mirror": true
        },
        "LostLands": {},
        "Metaballs": {
          "speed": 1.0
        },
        "Off": {},
        "Plasm": {
          "speed": 1.0
        },
        "PlasmaWaves": {
          "speed": 1.0
        },
        "Police": {
          "speed": 1.0
        },
        "Pool": {
          "speed": 1.0,
          "scale": 1.0
        },
        "Rainbow": {},
        "SmokeCurtains": {
          "speed": 1.0,
          "scale": 1.0
        },
        "Spirits": {
          "speed": 1.0
        },
        "SolidColor": {
          "color": 14791283
        },
        "Strobe": {
          "colors": [
            14791283,
            28579123
          ],
          "hertz": 5.0,
          "smooth": true
        },
        "TheMatrix": {}
      }
    })json";
    
    void setup() {
        deserializeJson(doc, json);
        delay(10);
    }
    
}