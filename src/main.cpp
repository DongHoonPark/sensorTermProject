#include "Arduino.h"
#include "DueTimer.h"
#include "MadgwickAHRS.h"

DueTimer gyroTimer = DueTimer(1);
DueTimer controlTimer = DueTimer(6);

void setup(){
  gyroTimer.setFrequency(500);
  controlTimer.setFrequency(200);
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  while(Serial2.available()){
    Serial.println(Serial2.read(), HEX);

  }
}
