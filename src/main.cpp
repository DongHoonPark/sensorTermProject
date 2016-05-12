#include "Arduino.h"
#include "DueTimer.h"
#include "MadgwickAHRS.h"
#include "Steering.h"
#include "Location.h"
#include "Motor.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "EulerAngle.h"
#include "CourseVector.h"

#define DEBUG_MSG_ON //debug message switch

DueTimer gyroTimer = DueTimer(1);
DueTimer controlTimer = DueTimer(6);

Steering steering = Steering( 170.0f , 10.0f );
Location location = Location();
Motor dc = Motor(3,2);
EulerAngle ea = EulerAngle();
CourseVector coursevector = CourseVector(10000,20000,17200,78700,5000); //new course

MPU6050 accelgyro;

int16_t gx, gy, gz, ax, ay, az;

int pastXvalue;
int pastYvalue;
int nowXvalue;
int nowYvalue;
int errorvalue;
int nowvector;

float dt = 0.02f;
float Kp = 0.6f;
float Ki = 0.03f;
float Kp_v = 0.0f;
float Ki_v = 0.0f;
float error_int = 0.0f;

float gx_rad, gy_rad, gz_rad, ax_ms2, ay_ms2, az_ms2;
float scaleGyro = (2.0f * PI * 250.0f / 360.0f) / 32768.0f;
float scaleAccel = (2.0f * 9.8f) / 32768.0f;

void gyroSensing(void);
void controlVehicle(void);

void setup(){

   pastXvalue = 0;
   pastYvalue = 0;
   nowXvalue = 0;
   nowYvalue = 0;
   errorvalue = 10000;
   nowvector = 0;

  Serial.begin(115200);
  Serial3.begin(115200);
  steering.attach(8);

//  accelgyro.initialize();

  pinMode(LED_BUILTIN, OUTPUT);

  //gyroTimer.attachInterrupt(gyroSensing).start(2500);
  controlTimer.attachInterrupt(controlVehicle).start(20000); //real test 50000 -> 20000
}

void loop(){

    while(Serial3.available()){
    char buf  = Serial3.read();
    Serial.println(buf,HEX);
    location.pushData(buf);

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
  ea.updateQuaternion(q0, q1, q2, q3);

}

void controlVehicle(void){

  location.update();
  /* and there will be more control code*/
  /*Do Filter*/
  if (location.getXpos() != 0){
    if (pastXvalue == 0){
      pastXvalue = location.getXpos();
      nowXvalue = location.getXpos();
    }
    else{
      if((abs(location.getXpos()-pastXvalue)) >= errorvalue){
        nowXvalue = pastXvalue;
      }
      else{
        nowXvalue = location.getXpos();
        pastXvalue = location.getXpos();
      }
    }
  }
  if (location.getYpos() != 0){
    if (pastYvalue == 0){
      pastYvalue = location.getYpos();
      nowYvalue = location.getYpos();
    }
    else{
      if((abs(location.getYpos()-pastYvalue)) >= errorvalue){
        nowYvalue = pastYvalue;
      }
      else{
        nowYvalue = location.getYpos();
        pastYvalue = location.getYpos();
      }
    }
  }
  /*Filter End*/
  //nowvector = coursevector.getDistanceFromCourse(nowXvalue, nowYvalue);
  nowvector = coursevector.getDistanceFromCourse(location.getXpos(), location.getYpos());
  /*moving action*/
  if (nowXvalue != 0){
    //steering.setDirection((-0.7*(float(nowvector))/2500.0f));
    Kp_v = Kp * float(nowvector);
    error_int += float(nowvector) * dt;
    if(error_int > 300){
      error_int = 0;
    }
    steering.setDirection((Kp_v+(Ki* error_int))/2000.0f);
    if (coursevector.sector == 1 || coursevector.sector == 3 || coursevector.sector == 7 || coursevector.sector == 9){
    //steering.setDirection(-(Kp_v+(Ki* error_int))/2000.0f);
    //dc.setSpeed(0.2f);
    }
    else{
    //steering.setDirection((Kp_v+(Ki* error_int))/2000.0f);
    //dc.setSpeed(0.3f);
    }
  }


  #ifdef DEBUG_MSG_ON

  Serial.print("x : ");
  Serial.print(location.getXpos());
  //Serial.print(nowXvalue);
  Serial.print("\t");
  Serial.print("y :");
  Serial.print(location.getYpos());
  //Serial.print(nowYvalue);
  Serial.print("\t");
  //Serial.print(coursevector.getDistanceFromCourse(location.getXpos(), location.getYpos()));
  //Serial.print(coursevector.getDistanceFromCourse(nowXvalue, nowYvalue));
  Serial.print(nowvector);
  Serial.print("\n");
  Serial.print(coursevector.sector);
  #endif
//debug
}
