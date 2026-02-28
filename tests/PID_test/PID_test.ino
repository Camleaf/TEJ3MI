/*
 * Runs on the ESP32 board
 * Reads velocity and tunes the speed via a PID loop to a set RPM
 */
#include "src/constants.h"
#include "esp_attr.h"



const int setRPM = 500; // must be smaller than kMotorRPM and greater than 0
const int setDir = 1; // 1 for forwards, -1 for backwards
volatile int edgeCount = 0;
unsigned long lastTime = 0;
volatile bool dir; // read direction from encoder
float rpm = 0;
int RPMToOut(int rpm) {return map(rpm,0,kMotorMaxRPM,0,255);};
int outValue = RPMToOut(setRPM);

void IRAM_ATTR ChanA() {
  // Read the pin state inside the ISR to determine if it was a RISE or FALL
  if (digitalRead(kEncoder2) == HIGH) { // Will need to determine in testing which way counts as forwards
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
  Serial.begin(9600);
  // Set up correct pin modes
  pinMode(kIn1, OUTPUT);
  pinMode(kIn2, OUTPUT);
  pinMode(kEncoder1, INPUT);
  pinMode(kEncoder2, INPUT);
  
  // Attach ISR interrupts
  attachInterrupt(kEncoder1, *ChanA,CHANGE);
  attachInterrupt(kEncoder2, *ChanB,CHANGE);
  if (setDir == 1){
    analogWrite(kIn1,outValue);
    analogWrite(kIn2,0);
  } else {
    analogWrite(kIn1,0);
    analogWrite(kIn2,outValue);
  }
};


float integral = 0.0;
float prevError = 0.0;

void loop(){
  
  // Logging for Serial Plotter to monitor PID control.
  Serial.print("ReadRPM:");
  Serial.print(rpm,2);
  Serial.print(",DesiredRPM:");
  Serial.print(setRPM);
  Serial.print("\n");


  if (millis() - lastTime >= kSampleTime) {

    long currentCount = edgeCount;
    
    rpm = (currentCount * 60000.0) / (kEffectivePPR * kSampleTime);
    edgeCount = 0;
    

    // If direction isn't correct
    if (dir != setDir){
      // Flush the signal on direction change so that the motor driver doesn't get overloaded
      analogWrite(kIn1,0);
      analogWrite(kIn2,0);
      delay(10);
    }


    // PID tuning if outside tolerance
    if (abs(rpm-setRPM)>kRPMTolerance){
      // Handle PID tuning
      long delta = millis()-lastTime;
      float error = rpm-setRPM;
      integral += error * delta;
      float derivative = (error-prevError) / delta; 
      prevError = error;

      // Handle proportional error;
      outValue = RPMToOut((int)(error*kProportional + derivative * kDerivative + integral * kIntegral));

      if (outValue < 0) outValue = 0;
      if (outValue > 255) outValue = 255;
    }


    // If direction modified or PID tuned, modify the output signal
    if (dir != setDir || abs(rpm-setRPM) > kRPMTolerance){      
      if (setDir == 1){
        analogWrite(kIn1,outValue);
        analogWrite(kIn2, 0);
      } else {
        analogWrite(kIn1, 0);
        analogWrite(kIn2, outValue);
      }

    }

    lastTime = millis();  
  }
};
