#include "Arduino.h"
#include "DueTimer.h"
#include "MadgwickAHRS.h"
#include "Servo.h"

DueTimer gyroTimer = DueTimer(1);
DueTimer controlTimer = DueTimer(6);

void gyroSensing(void);
void controlVehicle(void);

void setup(){

  gyroTimer.attachInterrupt(gyroSensing).start(2000);
  controlTimer.attachInterrupt(controlVehicle).start(5000);

  Serial.begin(115200);
  Serial2.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  while(Serial2.available()){

  }
}

void gyroSensing(void){

}

void controlVehicle(void){

}
