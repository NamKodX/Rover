/*
  L298ND.ino
  ver. 2022.01
  namik.can@hotmail.com
*/
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// include these libraries
// #include <stduint8_t const.h>
// #include <avr/uint8_t consterrupt.h>
#include "L298ND.h"

// declaration of the pins
// Motor Right connections
uint8_t const enB = 8;	// Enable Motor B
uint8_t const in4 = 7;	// RightMotorForward
uint8_t const in3 = 6;	// RightMotorBackward
// Motor Left connections
uint8_t const in2 = 5;	// LeftMotorForward
uint8_t const in1 = 4;	// LeftMotorBackward
uint8_t const enA = 3;	// Enable Motor A
// declaration of variables
int8_t  direction;
int16_t angle;
// declaration of constants
uint16_t delayTime = 1000;
uint16_t turnDelay =  500;

L298ND::L298ND() {
  // Constructor
}

L298ND::~L298ND() {
  // Destructor
}
//
void L298ND::initialization() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Turn off motors, initial state
	  fastStop();
}
//
void L298ND::testing(uint8_t velocity) {
  toForward(255);
  delay(3000);
  toBackward(255);
  delay(3000);
  toLeft(255);
  delay(3000);
  toRight(255);
  delay(3000);
}
//
void L298ND::toForward(uint8_t velocity) {
  digitalWrite(in1, LOW);  digitalWrite(in4, HIGH);
  digitalWrite(in2, HIGH); digitalWrite(in3, LOW);
  analogWrite(enA, velocity);
  analogWrite(enB, velocity);
}
//
void L298ND::toBackward(uint8_t velocity) {
  digitalWrite(in1, HIGH); digitalWrite(in4, LOW);
  digitalWrite(in2, LOW);  digitalWrite(in3, HIGH);
  analogWrite(enA, velocity);
  analogWrite(enB, velocity);
}
//
void L298ND::toLeft(uint8_t velocity) {
  digitalWrite(in1, LOW);  digitalWrite(in4, LOW);
  digitalWrite(in2, HIGH); digitalWrite(in3, HIGH);
	analogWrite(enA, velocity);
  analogWrite(enB, velocity);
}
//
void L298ND::toRight(uint8_t velocity) {
  digitalWrite(in1, HIGH); digitalWrite(in4, HIGH);
  digitalWrite(in2, LOW);  digitalWrite(in3, LOW );
	analogWrite(enA, velocity);
  analogWrite(enB, velocity);
}
//
void L298ND::fastStop() {
  digitalWrite(in1, LOW); digitalWrite(in4, LOW);
  digitalWrite(in2, LOW);  digitalWrite(in3, LOW );
}
//
void L298ND::toStop() {
  analogWrite(enA, LOW);
  analogWrite(enB, LOW);
}
