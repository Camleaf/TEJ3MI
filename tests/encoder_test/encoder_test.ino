/*
 * Reads velocity and tunes the speed
 */
#include "src/constants.h"
#include "esp_attr.h"


const int setRPM = 500; // must be smaller than kMotorRPM and greater than 0
volatile int edgeCount = 0;
unsigned long lastTime = 0;
volatile bool dir;

void IRAM_ATTR ChanA() {
  // Read the pin state inside the ISR to determine if it was a RISE or FALL
  if (digitalRead(kEncoder2) == HIGH) { // Rising edge
    dir = 1;
  } else {
    dir = -1;
  }
  edgeCount += 1;
}

void IRAM_ATTR ChanB() {
  edgeCount += 1;
}


void setup(){

  pinMode(kMA1, OUTPUT);
  pinMode(kMA2, OUTPUT);
  pinMode(kEncoder1, INPUT);
  pinMode(kEncoder2, INPUT);
  
  attachInterrupt(kEncoder1, *ChanA,CHANGE);
  attachInterrupt(kEncoder2, *ChanB,CHANGE);

};




void loop(){
  if (millis() - lastTime >= kSampleTime) {

    long currentCount = edgeCount;

    float rpm = (currentCount * 60000.0) / (kEffectivePPR * kSampleTime);
    edgeCount = 0;

    Serial.println(rpm,2); 
    lastTime = millis();
  }
};
