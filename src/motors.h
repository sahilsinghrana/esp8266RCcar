#include <Arduino.h>
#include <string>

// Drive Motor connections
int in1 = D1;
int in2 = D2;
int enA = D3;

// Direction Motor connections
int in3 = D5;
int in4 = D6;
int enB = D7;

void moveForward(int val);
void moveBackward(int val);
void turnLeft(int val);
void turnRight(int val);
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

void moveBackward(int val)
{
    analogWrite(enA, val);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
}

void moveForward(int val)
{
    analogWrite(enA, val);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
}

void turnLeft(int val)
{
    analogWrite(enB, val);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void turnRight(int val)
{
    analogWrite(enB, val);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}

void goStraight()
{
    analogWrite(enB, 0);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}
