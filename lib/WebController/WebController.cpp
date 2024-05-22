#include "WebController.h"

ESP8266WiFiMulti wifiMulti;

ESP8266WebServer server(80);
Motors motors;

WebController::WebController() {}

void WebController::redirectToHome()
{
  server.sendHeader("Location", "/");

  server.send(303);
}

void WebController::handleForward()
{
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.moveForward(val);
  server.send(200, "text/html", "FORWARD");
}

void WebController::handleBackward()
{
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.moveBackward(val);
  server.send(200, "text/html", "BACKWARD");
}

void WebController::handleLeft()
{
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.turnLeft(val);
  server.send(200, "text/html", "LEFT");
}

void WebController::handleStraight()
{
  motors.goStraight();
  server.send(200, "text/html", "STRAIGHT");
}

void WebController::handleRight()
{
  const String args = server.arg("plain");
  int val = args.toInt();
  motors.turnRight(val);
  server.send(200, "text/html", "RIGHT");
}

void WebController::handleStop()
{
  motors.stopMotors();
  server.send(200, "text/html", "STOP");
}

// -----------------------------------------------

//  WEB PAGE

// -----------------------------------------------

void WebController::handleRoot()
{
  server.send(200, "text/html", MAIN_page);
}

void WebController::handleNotFound()
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

void WebController::setupRoutes()
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

void setupMotors()
{
  motors.setupMotorPins();
  // Turn off motors - Initial state
  motors.stopMotors();
}

void WebController::setupWebserver()
{
  Serial.begin(9600);
  setupMotors();

  wifiMulti.addAP("sahil", "12345678");
  wifiMulti.addAP("Sahil", "ssssssss");
  wifiMulti.addAP("rexxx", "qqwweerrttyy12345");

  Serial.println("");
  Serial.println("Connecting ...");
  while (
      wifiMulti.run() !=
      WL_CONNECTED)
  {
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(
      WiFi.localIP());

  if (MDNS.begin("esp8266"))
  {
    Serial.println("mDNS responder started");
  }
  else
  {
    Serial.println("Error setting up MDNS responder!");
  }

  setupRoutes();
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(LED_BUILTIN, HIGH);
}

void WebController::startClient(void) { server.handleClient(); }