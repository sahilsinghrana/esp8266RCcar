#include <Arduino.h>

#include <webserve.h>
// #include <motors.h>

void setup()
{
  // Set all the motor control pins to outputs
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

  // directionControl();
  // delay(2000);
  // goStraight();
  // delay(2000);
  // moveForward();
  // delay(2000);
  // stopMotors();
  // delay(2000);
  // speedControl();
}
