#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <stdlib.h>

#include <Motors.h>
#include <webpage.h>

#include "WebController.h";

ESP8266WiFiMulti wifiMulti; // Create an instance of the ESP8266WiFiMulti class,
                            // called 'wifiMulti'

ESP8266WebServer server(80);
Motors motors;

WebController::WebController() {}

void WebController::redirectToHome() {
  server.sendHeader("Location",
                    "/"); // Add a header to respond with a new location for the
                          // browser to go to the home page again
  server.send(303); // Send it back to the browser with an HTTP status 303 (See
                    // Other) to redirect
}

void WebController::handleForward() {
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.moveForward(val);
  server.send(200, "text/html", "FORWARD");
}

void WebController::handleBackward() {
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.moveBackward(val);
  server.send(200, "text/html", "BACKWARD");
}

void WebController::handleLeft() {
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.turnLeft(val);
  server.send(200, "text/html", "LEFT");
}

void WebController::handleStraight() {
  motors.goStraight();
  server.send(200, "text/html", "STRAIGHT");
}

void WebController::handleRight() {
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.turnRight(val);
  server.send(200, "text/html", "RIGHT");
}

void WebController::handleStop() {
  motors.stopMotors();
  server.send(200, "text/html", "STOP");
}

// -----------------------------------------------

//  WEB PAGE

// -----------------------------------------------

void WebController::handleRoot() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //   server.send(200, "text/html", MAIN_page);
}

void WebController::handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void WebController::setupRoutes() {
  handleRoot();
  // server.on("/control", HTTP_POST, handleControl);
  server.on("/forward", HTTP_POST, this->handleForward);
  server.on("/backward", HTTP_POST, this->handleBackward);
  server.on("/stop", HTTP_POST, this->handleStop);
  server.on("/left", HTTP_POST, this->handleLeft);
  server.on("/right", HTTP_POST, this->handleRight);
  server.on("/straight", HTTP_POST, this->handleStraight);
  server.onNotFound(this->handleNotFound);
}

void WebController::setupWebserver() {
  Serial.begin(9600);

  wifiMulti.addAP("sahil", "12345678");
  wifiMulti.addAP("Sahil", "ssssssss");
  wifiMulti.addAP("rexxx", "qqwweerrttyy12345");

  Serial.println("");
  Serial.println("Connecting ...");
  while (
      wifiMulti.run() !=
      WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks,
                      // and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(WiFi.SSID()); // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(
      WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) { // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  this->setupRoutes();
  server.begin();
  Serial.println("HTTP server started");
}

void WebController::startClient(void) { server.handleClient(); }