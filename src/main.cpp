#include <Arduino.h>

#include "connections.h"

#include <webserve.h>

void setup()
{
  // Motor 1
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Motor 2
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(enA, 255);
  analogWrite(enB, 255);

  // Turn off motors - Initial state
  stopMotors();
  setupWebserver();
}

void loop()
{
  startClient();
}
