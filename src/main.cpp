#include "Arduino.h"
#include "DueTimer.h"
#include "MadgwickAHRS.h"
#include "Steering.h"
#include "Location.h"
#include "Motor.h"
#include "I2Cdev.h"
#include "MPU6050.h"

DueTimer gyroTimer = DueTimer(1);
DueTimer controlTimer = DueTimer(6);

Steering steering = Steering( 90.0f , 0.0f );
Location location = Location();
Motor dc = Motor(2,3);

MPU6050 accelgyro;

float gx, gy, gz, ax, ay, az;

void gyroSensing(void);
void controlVehicle(void);

void setup(){

  Serial.begin(115200);
  Serial2.begin(115200);

  accelgyro.initialize();

  pinMode(LED_BUILTIN, OUTPUT);

  gyroTimer.attachInterrupt(gyroSensing).start(2000);
  controlTimer.attachInterrupt(controlVehicle).start(5000);


}

void loop(){
  while(Serial2.available()){
    location.pushData(Serial2.read());
  }
}

void gyroSensing(void){

  MadgwickAHRSupdateIMU(gx, gy, gz, ax, ay, az);
}

void controlVehicle(void){
  location.update();
  /* and there will be more control code*/
}
