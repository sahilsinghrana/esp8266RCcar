

#include "Motors.h"
#include "globals.h"

void Motors::stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void Motors::moveBackward(int val) {
  analogWrite(enA, val);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void Motors::moveForward(int val) {
  analogWrite(enA, val);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void Motors::turnLeft(int val) {
  analogWrite(enB, val);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Motors::turnRight(int val) {
  analogWrite(enB, val);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Motors::goStraight() {
  analogWrite(enB, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
