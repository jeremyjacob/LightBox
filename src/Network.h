#pragma once

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <asyncHTTPrequest.h>
#include <base64.h>

namespace Network {
//    const char *ssid = "Buick";
//    const char *password = "poppyandpippin!";
    const char *ssid = "Counter Intuitive Wi-Fi";
    const char *password = "ultrajava";
    
    AsyncWebServer server(80);
    AsyncWebSocket ws("/");
    AsyncEventSource sse("/stream");
    asyncHTTPrequest request;

//    std::vector<AsyncWebSocketClient *> wsClients;
//    std::vector<AsyncEventSourceClient *> eventClients;

//    WiFiClientSecure client;
    
    void broadcast(const std::string &string) {
        ws.textAll(string.c_str(), string.length());
    }
    
    void broadcast(const char *string) {
        ws.textAll(string);
    }
    
    void broadcast(char *string) {
        ws.textAll(string);
    }
    
    void sendState(AsyncWebSocketClient *client) {
        std::string string = State::asJsonString();
        client->text(string.c_str(), string.length());
    }
    
    void sendStateAll() {
        std::string string = State::asJsonString();
        ws.textAll(string.c_str(), string.length());
    }
    
    void sendPixels() {
        CRGB *leds;
        switch (State::streamLayer) {
            case 0:leds = final_leds;
                break;
            case 1: leds = p_leds;
                break;
            case 2: leds = t_leds;
                break;
            default: return;
        }
        const size_t size = 1 + (WIDTH * HEIGHT * 3);
        uint8_t package[size];
        package[size - 1] = 0; // null terminator
        uint16_t i = 0;
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                CRGB led = leds[XY(x, y)];
                package[i] = led.red;
                package[i + 1] = led.green;
                package[i + 2] = led.blue;
                i += 3;
            }
        }

//        for (auto client: eventClients) {
        char encoded[base64::encoded_size(size)];
        base64::encode(encoded, package, size);
        sse.send(encoded);
//        }
    }
    
    void onEventConnect(AsyncEventSourceClient *client) {
        Serial.println("Hello SSE client");
//        eventClients.push_back(client);
    }
    
    void parse(const uint8_t *data, const size_t len, AsyncWebSocketClient *client) {
        if (len == 0) return;
        try {
            State::merge(data, len);
            sendState(client);
        } catch (const std::exception &e) {
            std::string str("Invalid JSON: ");
            str.append(e.what());
            client->text(str.c_str());
        }
    }
    
    void onWsEvent(AsyncWebSocket *_server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data,
                   size_t len) {
        if (type == WS_EVT_CONNECT) {
            Serial.println("Websocket client connection received");
            client->text("Greetings");
//            wsClients.push_back(client);
            sendState(client);
            
        } else if (type == WS_EVT_DATA) {
            // Data recieved
            parse(data, len, client);
        } else if (type == WS_EVT_DISCONNECT) {
            Serial.println("Client disconnected");
//            wsClients.erase(std::remove(wsClients.begin(), wsClients.end(), client), wsClients.end());
        }
    }
    
    
    void setup() {
        WiFi.begin(ssid, password);
//        client.setInsecure(); // TODO: Remove this line and implement real cert verification
        while (WiFiClass::status() != WL_CONNECTED) {
            delay(500);
            Serial.print("Connecting to WiFi: ");
            Serial.println(WiFiClass::status());
        }
        
        Serial.println(WiFi.localIP());
        
        ws.onEvent(onWsEvent);
        sse.onConnect(onEventConnect);
        server.addHandler(&ws);
        server.addHandler(&sse);
        
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
            request->send_P(200, "text/html", "hi");
        });
        
        DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
        DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Headers"), F("content-type"));
        server.begin();
    }
}
