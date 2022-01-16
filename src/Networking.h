#pragma once

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "Buick";
const char *password = "poppyandpippin!";

AsyncWebServer server(80);
AsyncWebSocket ws("/");

void onWsEvent(AsyncWebSocket *_server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data,
               size_t len) {

    if (type == WS_EVT_CONNECT) {
        Serial.println("Websocket client connection received");
        client->text("Greetings");

    } else if (type == WS_EVT_DISCONNECT) {
        Serial.println("Client disconnected");
    }
}

void networkSetup() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("Connecting to WiFi: ");
        Serial.println(WiFi.status());
    }

    Serial.println(WiFi.localIP());

    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.begin();
//    WiFiClient
}