#ifndef MOTORS_H
#define MOTORS_H
#include <Arduino.h>

class Motors
{
public:
  static void moveForward(int val);
  static void moveBackward(int val);
  static void turnLeft(int val);
  static void turnRight(int val);
  static void goStraight();
  static void stopMotors();

  static void setupMotorPins();
};

#endif