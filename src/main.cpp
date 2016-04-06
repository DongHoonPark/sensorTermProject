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

int16_t gx, gy, gz, ax, ay, az;
float gx_rad, gy_rad, gz_rad, ax_ms2, ay_ms2, az_ms2;
float scaleGyro = (2.0f * PI * 250.0f / 360.0f) / 32768.0f;
float scaleAccel = (2.0f * 9.8f) / 32768.0f;

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
  accelgyro.getMotion6(&ax, &ay, &ax, &gx, &gy, &gz);

  gx_rad = scaleGyro * gx;
  gy_rad = scaleGyro * gy;
  gz_rad = scaleGyro * gz;

  ax_ms2 = scaleAccel * ax;
  ay_ms2 = scaleAccel * ay;
  az_ms2 = scaleAccel * az;

  MadgwickAHRSupdateIMU(gx_rad, gy_rad, gz_rad, ax_ms2, ay_ms2, az_ms2);

}

void controlVehicle(void){
  location.update();
  /* and there will be more control code*/
}
