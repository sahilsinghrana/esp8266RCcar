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

bool isPlayingSong = false;

void WebController::handleHonk()
{ // If we are not playing something
  if (isPlayingSong)
  {
    anyrtttl::nonblocking::stop();
    isPlayingSong = false;
    server.send(200, "text/html", "STOPPED_HONKING");
  }
  else
  {
    anyrtttl::nonblocking::begin(BUZZER_PIN, F("Mission Impossible:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d"));

    anyrtttl::nonblocking::play();
    isPlayingSong = true;
    server.send(200, "text/html", "HONKING");
  }
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
  server.on("/honk", HTTP_POST, handleHonk);

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

void WebController::startClient(void)
{
  server.handleClient();
  if (isPlayingSong)
  {
    if (anyrtttl::nonblocking::done())
    {
      anyrtttl::nonblocking::stop();
      isPlayingSong = false;
    }
    else
    {
      isPlayingSong = true;
      anyrtttl::nonblocking::play();
    }
  }
  else
  {
    isPlayingSong = false;
    anyrtttl::nonblocking::stop();
  }
}