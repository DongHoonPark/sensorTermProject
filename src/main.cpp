#include "Arduino.h"
#include "DueTimer.h"
#include "MadgwickAHRS.h"

DueTimer timer = DueTimer(0);

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
