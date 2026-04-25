#include <Arduino.h>

#include "src/drivetrain.h"
#include "src/controller.h"
#include <Bluepad32.h>

// Back right
#define kbr1 0
#define kbr2 0
// Back left
#define kbl1 0
#define kbl2 0
// Front right
#define kfr1 0
#define kfr2 0
// Front left
#define kfl1 0
#define kfl2 0

// Misc vars
#define maxSpeed 128
#define turnPower 128


Mecanum drivetrain(kbr1,kbr2,kbl1,kbl2,kfr1,kfr2,kfl1,kfl2);


void setup(){
    Serial.begin(115200);

    SetupBP32();
    drivetrain.setMaxSpeed(maxSpeed);
    drivetrain.setTurnPower(turnPower);
}



void loop(){
    
}
