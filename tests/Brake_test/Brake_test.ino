
/*
 * Runs on the ESP32 board
 * DC motor maintaining position test 
 * Unfortunately due to the limitations of the encoders on the motors that Mechmania is using this year, accuracy is limited to ~8 degrees. If used in any application, a 1-1 ratio is not recommended.
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


// DO NOT allocate the PositionController class with new, as that can risk a memory leak.
PositionController motor = PositionController(kIn1, kIn2, kEncoder1, kEncoder2, kMotorMaxRPM);


void setup(){
  Serial.begin(9600);
  motor.setPIDValues(kP,kI,kD);

  // With setDebug, will output plotted values into the arduino Serial Plotter. Use that to help with tuning
  motor.setDebug(true);

  motor.setPosition(0);
  delay(2000); // Gives A second before jumping into the mainloop
};


/**
 * The test running is 4 part:
 * 1. Goes from 0 to ~90 deg
 * 2. Goes from ~90 deg to ~45 deg
 * 3. Goes from ~45 deg to -180 deg
 * 4. Goes back to 0 deg
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
            motor.setPosition(90);
          break;
        case 1:
            motor.setPosition(45);
          break;
        case 2:
            motor.setPosition(-180);
          break;
        case 3:
            motor.setPosition(0);
          break;
      }
      mode += 1;
      mode %= 4;
  }
};
