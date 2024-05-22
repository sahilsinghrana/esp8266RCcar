#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <stdlib.h>
#include <cmath>

#include <webpage.h>
#include <motors.h>

#define INTERNAL_LED 13

ESP8266WiFiMulti wifiMulti; // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);

// void handleControl();

int getMaxOrValRounded(int val, int max)
{
    return abs(round(val * max / 100));
}

void redirectToHome()
{
    server.sendHeader("Location", "/"); // Add a header to respond with a new location for the browser to go to the home page again
    server.send(303);                   // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleForward()
{
    const String args = server.arg("plain");
    int val = getMaxOrValRounded(args.toInt(), 240);
    moveForward(val);
    server.send(200, "text/html", "FORWARD");
}

void handleBackward()
{
    const String args = server.arg("plain");
    int val = getMaxOrValRounded(args.toInt(), 240);
    moveBackward(val);
    server.send(200, "text/html", "BACKWARD");
}

void handleLeft()
{
    const String args = server.arg("plain");
    int val = getMaxOrValRounded(args.toInt(), 240);
    turnLeft(val);
    server.send(200, "text/html", "LEFT");
}

void handleStraight()
{
    goStraight();
    server.send(200, "text/html", "STRAIGHT");
}

void handleRight()
{
    const String args = server.arg("plain");
    int val = getMaxOrValRounded(args.toInt(), 240);
    turnRight(val);
    server.send(200, "text/html", "RIGHT");
}

void handleStop()
{
    stopMotors();
    server.send(200, "text/html", "STOP");
}

void handleRoot()
{
    server.send(200, "text/html", MAIN_page);
}

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void setupRoutes()
{
    server.on("/", handleRoot);
    // server.on("/control", HTTP_POST, handleControl);
    server.on("/forward", HTTP_POST, handleForward);
    server.on("/backward", HTTP_POST, handleBackward);
    server.on("/stop", HTTP_POST, handleStop);
    server.on("/left", HTTP_POST, handleLeft);
    server.on("/right", HTTP_POST, handleRight);
    server.on("/straight", HTTP_POST, handleStraight);
    server.onNotFound(handleNotFound);
}

void setupWebserver(void)
{
    Serial.begin(9600);

    wifiMulti.addAP("sahil", "12345678");
    wifiMulti.addAP("Sahil", "ssssssss");
    wifiMulti.addAP("rexxx", "qqwweerrttyy12345");

    Serial.println("");
    Serial.println("Connecting ...");
    while (wifiMulti.run() != WL_CONNECTED)
    { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
        delay(250);
        Serial.print('.');
    }
    Serial.println('\n');
    Serial.print("Connected to ");
    digitalWrite(INTERNAL_LED, HIGH);
    Serial.println(WiFi.SSID()); // Tell us what network we're connected to
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

    if (MDNS.begin("esp8266"))
    { // Start the mDNS responder for esp8266.local
        Serial.println("mDNS responder started");
    }
    else
    {
        Serial.println("Error setting up MDNS responder!");
    }

    setupRoutes();
    server.begin();
    Serial.println("HTTP server started");
}

void startClient(void)
{
    server.handleClient();
}

// void handleControl()
// {
//     const String args = server.arg("plain");

//     if (args == "FORWARD")
//     {
//         moveForward();
//         server.send(200, "text/plain", "Success -- FORWARD");
//     }
//     else if (args == "BACKWARD")
//     {
//         moveBackward();
//         server.send(200, "text/plain", "Success -- BACKWARD");
//     }
//     else if (args == "LEFT")
//     {
//         turnLeft();
//         server.send(200, "text/plain", "Success -- LEFT");
//     }
//     else if (args == "RIGHT")
//     {
//         turnRight();
//         server.send(200, "text/plain", "Success -- RIGHT");
//     }
//     else if (args == "STRAIGHT")
//     {
//         goStraight();
//         server.send(200, "text/plain", "Success -- STRAIGHT");
//     }
//     else if (args == "STOP")
//     {
//         stopMotors();
//         server.send(200, "text/plain", "Success -- STOP");
//     }
//     else
//     {
//         server.send(200, "text/plain", "FAILED to read command");
//     }
// }
