#include <Arduino.h>
#include <L298NX2.h>

//L298NX2(EN, IN1, IN2);
L298NX2 motors(7, 6, 5);
const int trig_1 = 0, trig_2 = 1, trig_3 = 2; //Trigger pins
const int echo_1 = 3, echo_2 = 4, echo_3 = 5; //Echo pins
const int treshold = 300; //maximum proximity

//Distance variables for sensor reading;
float d_1, d_2, d_3;

long readSensor(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH) * 0.01723;
}


void setup(){

}

void loop(){

}


