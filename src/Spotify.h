#pragma once

namespace Spotify {
    uint16_t bpm = 0;

    void setBPM() {
    }

    void requestCB(void *optParm, asyncHTTPrequest *request, int readyState) {
        if (readyState == 4) {
            Serial.println(request->responseText());
            Serial.println();
            request->setDebug(false);
        } else {
            //print readyState
            Serial.print("cb-readyState: ");
            Serial.println(readyState);
        }
    }

    void sendRequest() {
        if (Network::request.readyState() == 0 || Network::request.readyState() == 4) {
            Network::request.open("GET", "https://api.spotify.com:443/v1/audio-features/4VbDJMkAX3dWNBdn3KH6Wx");
//            Network::request.setReqHeader("Accept", "application/json");
//            Network::request.setReqHeader("Authorization",
//                                          "Bearer BQDqi7DyTb2p-nPxvXi7Iz4ZPlQksg4K8t9_vtfOJghTnADPROcXMegvlfE6X-nX1JuzAUmbpJZpwpub6fapduX864A_pwNp9bi721vpt9tPwtYxHSa1F66cikP9VyA_nvDZxhihUjf1M73521uPMc0PxXlkGY-pwFDqhIkIUd2sHkYcLHft2eE-3SS1BWLYwVvYqfpLbW3c6-IF3XOhl9Z_xqGPcHOwuhxZ-oN67HrEr9GjKRlxvpyU2NyDaRNU6i2CNeiKrp8rijmUqdj-Y57bQ3pPILqK_0B0pDeKKH5C");
            Network::request.send();
        }
        Network::request.onReadyStateChange(requestCB);
    }

    void tick() {

    }
}