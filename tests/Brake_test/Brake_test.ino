/*
 * Runs on the ESP32 board
 * Reads velocity and tunes the speed via a PID loop to a set RPM
 * ALWAYS TUNE EVERY MOTOR INDEPENDANTLY. NEVER USE TUNED VARIABLES FROM ONE MOTOR ON ANOTHER. IF ANYTHING CHANGES ON THE MOTOR ALWAYS RETUNE.
 */
#include "src/constants.h"
#include "esp_attr.h"




unsigned long lastTime = 0;
float readPosition = 0;
int lastEncoded = 0;
int PosToCounts(int degrees) {return map(degrees,-360,360,-kEffectivePPR,kEffectivePPR);};
int CountsToPos(int counts) {return map(counts,-kEffectivePPR,kEffectivePPR,-360,360);};

const int setPosition = PosToCounts(90); // Target position in counts

void IRAM_ATTR ChanA() {
  int a = digitalRead(kEncoder1);
  int b = digitalRead(kEncoder2);
  int encoded = (a << 1) | b;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b0001 || sum == 0b0111 || sum == 0b1110 || sum == 0b1000) {
    readPosition++; // Clockwise
  } else if (sum == 0b0010 || sum == 0b1011 || sum == 0b1101 || sum == 0b0100) {
    readPosition--; // Counter-clockwise
  }

  lastEncoded = encoded;
}

void IRAM_ATTR ChanB() {
  ChanA();
}


void setup(){
  Serial.begin(9600);
  // Set up correct pin modes
  pinMode(kIn1, OUTPUT);
  pinMode(kIn2, OUTPUT);
  pinMode(kEncoder1, INPUT_PULLUP);
  pinMode(kEncoder2, INPUT_PULLUP);
  
  // Attach ISR interrupts
  attachInterrupt(kEncoder1, *ChanA, CHANGE);
  attachInterrupt(kEncoder2, *ChanB, CHANGE);
   
};


float integral = 0.0;
float prevError = 0.0;

void loop(){
  


  if (millis() - lastTime >= kSampleTime) {
       
    // Logging for Serial Plotter to monitor PID control.
    Serial.print("ReadPosition:");
    Serial.print(CountsToPos(readPosition),2);
    Serial.print(",DesiredPosition:");
    Serial.print(CountsToPos(setPosition));
    Serial.print("\n");
  

    // Tune PID
    if (abs(setPosition - readPosition) > kPositionTolerance){
      
      long delta = millis()-lastTime;
      float error = setPosition - readPosition;
      integral += error * delta;
      float derivative = (error-prevError) / delta; 
      prevError = error;

      float output = error * kProportional + derivative * kDerivative + integral + kIntegral;

      
    }
      
    


    lastTime = millis();
  }
};
