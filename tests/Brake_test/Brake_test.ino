/*
 * Runs on the ESP32 board
 * Reads velocity and tunes the speed via a PID loop to a set RPM
 */
#include "src/constants.h"
#include "esp_attr.h"



const int setPosition = 90; // Target position in degrees

unsigned long lastTime = 0;
float readPosition = 0;

void IRAM_ATTR ChanA() {
  
}

void IRAM_ATTR ChanB() {

}


void setup(){
  Serial.begin(9600);
  // Set up correct pin modes
  pinMode(kIn1, OUTPUT);
  pinMode(kIn2, OUTPUT);
  pinMode(kEncoder1, INPUT);
  pinMode(kEncoder2, INPUT);
  
  // Attach ISR interrupts
  attachInterrupt(kEncoder1, *ChanA,RISING);
  attachInterrupt(kEncoder2, *ChanB, RISING);
   
};


float integral = 0.0;
float prevError = 0.0;

void loop(){
  
  // Logging for Serial Plotter to monitor PID control.
  Serial.print("ReadPosition:");
  Serial.print(readPosition,2);
  Serial.print(",DesiredPosition:");
  Serial.print(setPosition);
  Serial.print("\n");


  if (millis() - lastTime >= kSampleTime) {
  }
};
