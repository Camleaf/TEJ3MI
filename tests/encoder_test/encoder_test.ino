#include "Arduino.h"
#include "src/constants.h"
#include "esp_attr.h"


const int setRPM = 500; // must be smaller than kMotorRPM and greater than 0

volatile uint32_t RiseTime[2];
volatile uint32_t FallTime[2];
volatile bool NewPulse[2];

void IRAM_ATTR ChanA() {
  // Read the pin state inside the ISR to determine if it was a RISE or FALL
  if (digitalRead(kEncoder1) == HIGH) { // Rising edge
    RiseTime[0] = micros();
  }
  else {
    FallTime[0]=micros();
    NewPulse[0]=true;
  }
}

void IRAM_ATTR ChanB() {
  if (digitalRead(kEncoder2) == HIGH) { // Rising edge
    RiseTime[1] = micros();
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
  pinMode(kEncoder1, INPUT);
  
  analogWrite(kMA1,0);
  analogWrite(kMA2,0);
  
  attachInterrupt(kEncoder1, *ChanA,CHANGE);
  attachInterrupt(kEncoder2, *ChanB,CHANGE);

};




void loop(){


  // Read velocity of quadrature encoders 

  
};
