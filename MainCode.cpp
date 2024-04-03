#include <Arduino.h>

const float rx_1 = 6, rx_2 = 5, rx_3 = 3;
const int tx_1 = 11, tx_2 = 10, tx_3 = 9;
long d1, d2, d3;
const int led_1 = 13, led_2 = 8, led_3 = 2;

const float treshold = 300.0;

//flush pointers
long* reads;
int* tx_pins;
int* rx_pins;

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

void readSensorFlush(long *reads, int *rx_pins, int *tx_pins, int size_1, int size_2, int size_3){
  
  //int len_tx = sizeof(tx_pins) / sizeof(tx_pins[0]);
  //int len_rx = sizeof(rx_pins) / sizeof(rx_pins[0]);
  
  for(int i = 0; i < size_2; i++){
    if(reads[i] == NULL || rx_pins[i] == NULL || tx_pins == NULL){
      	Serial.println("ARRAY IS NULL.");
    }
    else{
      	reads[i] = readSensor(tx_pins[i], rx_pins[i]);
    	Serial.println(rx_pins[i]);
    	Serial.println(readSensor(tx_pins[i], rx_pins[i]));
    }
  }
  /*
  for(int i = 0; i < len_tx; i++){
    pinMode(tx_pins[i], OUTPUT); //Clean all TX
    digitalWrite(tx_pins[i], LOW);
  }
  
  delayMicroseconds(2);
  for(int i = 0; i < len_tx; i++){
    digitalWrite(tx_pins[i], HIGH);
  }
  
  delayMicroseconds(10);
  for(int i = 0; i < len_tx; i++){
    digitalWrite(tx_pins[i], LOW);
  }
  
  for(int i = 0; i < len_rx; i++){
    pinMode(rx_pins[i], INPUT);
    reads[i] = pulseIn(rx_pins[i], HIGH) * 0.01723;
    Serial.println(reads[i]);
  } 
  */
}
  
void setup()
{
  Serial.begin(9600);
  
  //Sensors
  pinMode(tx_1, OUTPUT);
  pinMode(tx_2, OUTPUT);
  pinMode(tx_3, OUTPUT);
  pinMode(rx_1, OUTPUT);
  pinMode(rx_2, OUTPUT);
  pinMode(rx_3, OUTPUT);
  
  //OUTPUTs
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  int txs[] = {tx_1, tx_2, tx_3};
  int rxs[] = {rx_1, rx_2, rx_3};
  long rs[] = {d1, d2, d3};
  
  tx_pins = txs;
  rx_pins = rxs;
  reads = rs;

  
}

void loop()
{

  readSensorFlush(reads, rx_pins, tx_pins, 3, 3, 3);
  
  if(d1 < treshold){
    digitalWrite(led_1, HIGH);
  } else digitalWrite(led_1, LOW);
  
  if(d2 < treshold){
    digitalWrite(led_2, HIGH);
  } else digitalWrite(led_2, LOW);
  
  if(d3 < treshold){
    digitalWrite(led_3, HIGH);
  } else digitalWrite(led_3, LOW);
    
}

