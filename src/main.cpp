#include <Arduino.h>

#include <webserve.h>

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
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
