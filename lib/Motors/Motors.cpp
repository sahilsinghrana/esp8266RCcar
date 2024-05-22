
#include "Motors.h"

// Drive Motor connections
int in1 = D1;
int in2 = D2;
int enA = D3;

// Direction Motor connections
int in3 = D5;
int in4 = D6;
int enB = D7;

int getMaxOrValRounded(int val, int max)
{
  return abs(round(val * max / 100));
}

void Motors::stopMotors()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void Motors::moveBackward(int val)
{
  analogWrite(enA, getMaxOrValRounded(val, 245));
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void Motors::moveForward(int val)
{
  analogWrite(enA, getMaxOrValRounded(val, 245));
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void Motors::turnLeft(int val)
{
  analogWrite(enB, getMaxOrValRounded(val, 245));
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Motors::turnRight(int val)
{
  analogWrite(enB, getMaxOrValRounded(val, 245));
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Motors::goStraight()
{
  analogWrite(enB, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void Motors::setupMotorPins()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(enA, 0);
  analogWrite(enB, 0);
}