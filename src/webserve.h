#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>

#include <webpage.h>
#include <motors.h>

ESP8266WiFiMulti wifiMulti; // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);

void handleControl();

void redirectToHome()
{
    server.sendHeader("Location", "/"); // Add a header to respond with a new location for the browser to go to the home page again
    server.send(303);                   // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleForward()
{
    moveForward();
    redirectToHome();
}

void handleBackward()
{
    moveBackward();
    redirectToHome();
}

void handleLeft()
{
    redirectToHome();
    turnLeft();
}

void handleStraight()
{
    goStraight();
    redirectToHome();
}

void handleRight()
{
    redirectToHome();
    turnRight();
}

void handleStop()
{
    stopMotors();
    redirectToHome();
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
    server.on("/control", HTTP_POST, handleControl);
    server.on("/forward", handleForward);
    server.on("/backward", handleBackward);
    server.on("/stop", handleStop);
    server.on("/left", handleLeft);
    server.on("/right", handleRight);
    server.on("/straight", handleStraight);
    server.onNotFound(handleNotFound);
}

void setupWebserver(void)
{
    Serial.begin(9600);

    wifiMulti.addAP("sahil", "12345678"); // add Wi-Fi networks you want to connect to
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

void handleControl()
{
    const String args = server.arg("plain");
    // Serial.print(args);

    if (args == "FORWARD")
    {
        moveForward();
        server.send(200, "text/plain", "Success -- FORWARD");
    }
    else if (args == "BACKWARD")
    {
        moveBackward();
        server.send(200, "text/plain", "Success -- BACKWARD");
    }
    else if (args == "LEFT")
    {
        turnLeft();
        server.send(200, "text/plain", "Success -- LEFT");
    }
    else if (args == "RIGHT")
    {
        turnRight();
        server.send(200, "text/plain", "Success -- RIGHT");
    }
    else if (args == "STRAIGHT")
    {
        goStraight();
        server.send(200, "text/plain", "Success -- STRAIGHT");
    }
    else if (args == "STOP")
    {
        stopMotors();
        server.send(200, "text/plain", "Success -- STOP");
    }
    else
    {
        server.send(200, "text/plain", "FAILED to read command");
    }
}
