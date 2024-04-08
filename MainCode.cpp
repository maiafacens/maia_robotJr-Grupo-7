/*
ARDUINO UGV (DONKEY)
TODO: Create movement hierarchy based on smallest distance value compared to treshold.
Develop function to calculate rotation time for 45,90,125,180... etc degrees (based on motor speed);
*/

const int motor_1A = 12, motor_1B = 11; //Motor direction pins
const int motor_2A = 10, motor_2B = 9;
const int EN_1 = 13, EN_2 = 8; //Activate controllers

const int trig_1 = 2, trig_2 = 4, trig_3 = 6;
const int echo_1 = 3, echo_2 = 5, echo_3 = 7;

const long treshold = 15;
long dist_1, dist_2, dist_3;

long pulseDist(int trig, int echo){
  
  pinMode(trig, OUTPUT);  // Clear the trigger
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echo, HIGH) * 0.0173;
}



void setup()
{
  pinMode(motor_1A, OUTPUT);
  pinMode(motor_1B, OUTPUT);
  pinMode(motor_2A, OUTPUT);
  pinMode(motor_2B, OUTPUT);
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);
  
  //Activate
  
  digitalWrite(EN_1, HIGH);
  digitalWrite(EN_2, HIGH);
  
  Serial.begin(9600);
}

void loop()
{
  dist_1 = pulseDist(trig_1, echo_1);
  dist_2 = pulseDist(trig_2, echo_2);
  dist_3 = pulseDist(trig_3, echo_3);
  
  Serial.println("\n d1: ");
  Serial.println(dist_1);
  
  Serial.println("\n d2: ");
  Serial.println(dist_2);
  
  Serial.println("\n d3: ");
  Serial.println(dist_3);
  
  
  if(dist_2 < treshold || dist_1 < treshold && dist_3 < treshold){
    reposition(10000);
  }
  else if(dist_1 < treshold){
    rotateCounterClockwise(800);
  }
  else if(dist_3 < treshold){
    rotateClockwise(800);
  }
  else{
    moveForwards();
  }
  
  delay(300);
}


void moveForwards(){
  digitalWrite(motor_1A, HIGH);
  digitalWrite(motor_1B, LOW);
  digitalWrite(motor_2A, LOW);
  digitalWrite(motor_2B, HIGH);
}


void moveBackwards(){
  digitalWrite(motor_1A, LOW);
  digitalWrite(motor_1B, HIGH);
  digitalWrite(motor_2A, HIGH);
  digitalWrite(motor_2B, LOW);
}

void reposition(unsigned long delay){
  
  for(int i = 0; i < delay; i += 100){
    digitalWrite(motor_1A, LOW);
  	digitalWrite(motor_1B, HIGH);
  	digitalWrite(motor_2A, LOW);
  	digitalWrite(motor_2B, HIGH);
  }
  
  rotateClockwise(delay / 2);
}

void rotateClockwise(unsigned long delay){
  for(int i = 0; i < delay; i += 100){
    digitalWrite(motor_1A, LOW);
  	digitalWrite(motor_1B, HIGH);
  	digitalWrite(motor_2A, LOW);
  	digitalWrite(motor_2B, LOW);
  }
}

void rotateCounterClockwise(unsigned long delay){
  for(int i = 0; i < delay; i+= 100){
    digitalWrite(motor_1A, LOW);
  	digitalWrite(motor_1B, LOW);
  	digitalWrite(motor_2A, HIGH);
  	digitalWrite(motor_2B, LOW);
  }
}
