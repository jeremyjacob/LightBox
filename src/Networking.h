#pragma once

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <asyncHTTPrequest.h>

namespace Network {
    const char *ssid = "Buick";
    const char *password = "poppyandpippin!";

    AsyncWebServer server(80);
    AsyncWebSocket ws("/");
    asyncHTTPrequest request;

//    WiFiClientSecure client;

    void
    onWsEvent(AsyncWebSocket *_server, AsyncWebSocketClient *socketClient, AwsEventType type, void *arg, uint8_t *data,
              size_t len) {

        if (type == WS_EVT_CONNECT) {
            Serial.println("Websocket socketClient connection received");
            socketClient->text("Greetings");

        } else if (type == WS_EVT_DISCONNECT) {
            Serial.println("Client disconnected");
        }
    }

    void setup() {
        WiFi.begin(ssid, password);
//        client.setInsecure(); // TODO: Remove this line and implement real cert verification
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print("Connecting to WiFi: ");
            Serial.println(WiFi.status());
        }

        Serial.println(WiFi.localIP());

//        ws.onEvent(onWsEvent);
//        server.addHandler(&ws);
//        server.begin();
    }
}
