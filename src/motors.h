#include <Arduino.h>

// Drive Motor connections
int in1 = D1;
int in2 = D2;
int enA = D3;

// Direction Motor connections
int in3 = D5;
int in4 = D6;
int enB = D7;

void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void goStraight();
void stopMotors();

void fullSpeed()
{
    analogWrite(enA, 255);
}

void stopMotors()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void moveBackward()
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
}

void moveForward()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
}

void turnLeft()
{
    analogWrite(enB, 255);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnRight()
{
    analogWrite(enB, 255);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void goStraight()
{
    analogWrite(enB, 0);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
