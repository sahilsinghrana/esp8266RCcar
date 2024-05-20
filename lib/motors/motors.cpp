
#include "motors.h"


void fullSpeed()
{
    analogWrite(enA, 255);
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

void stopMotors()
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}



