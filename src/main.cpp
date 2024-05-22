#include <Arduino.h>

#include "WebController.h"

WebController webController;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  webController.setupWebserver();
}

void loop()
{
  webController.startClient();
}
