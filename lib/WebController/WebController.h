#ifndef WEB_CONTROLLER_H
#define WEB_CONTROLLER_H

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <stdlib.h>

#include <pitches.h>
#include <anyrtttl.h>
#include <binrtttl.h>
#include <pitches.h>

#include "Motors.h"
#include "webpage.h"

#define BUZZER_PIN D8

class WebController
{
public:
    WebController();
    static void setupWebserver();
    static void startClient();

    static void redirectToHome();
    static void handleForward();
    static void handleBackward();
    static void handleLeft();
    static void handleStraight();
    static void handleRight();
    static void handleStop();
    static void handleRoot();
    static void handleNotFound();
    static void setupRoutes();

    static void handleHonk();
};

#endif