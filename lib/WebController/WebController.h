#ifndef WEB_CONTROLLER_H
#define WEB_CONTROLLER_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <stdlib.h>

#include <webpage.h>
#include <Motors.h>

class WebController {
    public:
        WebController();
        void setupWebserver();
        void startClient();
    private :
        void redirectToHome();
        void handleForward();
        void handleBackward();
        void handleLeft();
        void handleStraight();
        void handleRight();
        void handleStop();
        void handleRoot();
        void handleNotFound();
        void setupRoutes();
};

#endif