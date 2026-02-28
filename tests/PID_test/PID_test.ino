/*
 * Runs on the ESP32 board
 * Reads velocity and tunes the speed via 
 */

#include "src/motor.h"

// Update for your use with accurate pins
// Update with pins connecting to m1 and m2 on motor driver
#define kIn1 0
#define kIn2 0

// Update with pins connecting to the encoder on motor
#define kEncoder1 0
#define kEncoder2 0

// Update with rated (but preferably self-tested) maximum RPM of motor
#define kMotorMaxRPM 0 
/*
 * Modify these values while tuning.
 * kP is the first one you increment, to get the motor moving to a specific RPM
 * kD is the second, if you overshoot and need to tune it down
 * kI is the third, only if you are consistently not reaching a rpm range
 *
 * Increase by 0.01, maybe by 0.1 or 0.2 if feeling confident. You could damage the motors by setting them too high
 *
 * NEVER reuse tuned values for more than one motor, even if it has the same RPM and load on it.
*/
#define kP 0
#define kI 0
#define kD 0


// DO NOT allocate the RPMController class with new, as that can risk a memory leak.
RPMController motor = RPMController(kIn1, kIn2, kEncoder1, kEncoder2, kMotorMaxRPM);


void setup(){
  Serial.begin(9600);
  motor.setPIDValues(kP,kI,kD);

  // With setDebug, will output plotted values into the arduino Serial Plotter. Use that to help with tuning
  motor.setDebug(true);

  motor.setRPM(0);
  motor.setDir(true);
  delay(2000); // Gives A second before jumping into the mainloop
};


/**
 * The test running is 4 part:
 * 1. Goes from 0 to max RPM
 * 2. Goes from max to 50%
 * 3. Goes from 50% to -Max
 * 4. Goes back to 0
 *
 * 4-second window in between each part
 */

int mode = 0;
long lastTime = 0;

void loop(){
  motor.tick();
  
  if (millis()-lastTime > 4000){
      

      switch (mode){
        case 0:
            motor.setRPM(kMotorMaxRPM);
          break;
        case 1:
            motor.setRPM(kMotorMaxRPM/2);
          break;
        case 2:
            motor.setDir(false);
            motor.setRPM(kMotorMaxRPM);
          break;
        case 3:
            motor.setDir(true);
            motor.setRPM(0);
          break;
      }
      mode += 1;
      mode %= 4;
  }
};
