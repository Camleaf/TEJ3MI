/*
 * Reads velocity and tunes the speed
 */
#include "Arduino.h"
#include "src/constants.h"
#include "esp_attr.h"


const int setRPM = 500; // must be smaller than kMotorRPM and greater than 0

volatile uint32_t RiseTime[2];
volatile uint32_t OldRise[2];
volatile uint32_t FallTime[2];
volatile uint32_t Period[2];
volatile bool NewPulse[2];

void IRAM_ATTR ChanA() {
  // Read the pin state inside the ISR to determine if it was a RISE or FALL
  if (digitalRead(kEncoder1) == HIGH) { // Rising edge
    OldRise[0] = RiseTime[0];
    RiseTime[0] = micros();
    Period[0] = RiseTime[0] - OldRise[0];
  }
  else {
    FallTime[0]=micros();
    NewPulse[0]=true;
  }
}

void IRAM_ATTR ChanB() {
  if (digitalRead(kEncoder2) == HIGH) { // Rising edge
    OldRise[1] = RiseTime[1];
    RiseTime[1] = micros();
    Period[1] = RiseTime[1] - OldRise[1];

  }
  else {
    FallTime[1]=micros();
    NewPulse[1]=true;

  }
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

  uint32_t PChanA = Period[0];
  uint32_t PChanB = Period[1];

  bool dir = RiseTime[1] > RiseTime[0]; // If A leads B, then positive, else negative
  // Read velocity of quadrature encoders 
  
  uint32_t RPMA = 1000000UL/(PChanA*K_ENCODER_RATING); // Not a fan of this divison here.
  uint32_t RPMB = 1000000UL/(PChanB*K_ENCODER_RATING);
  uint32_t RPM = (RPMA+RPMB) / 2;

  
};
