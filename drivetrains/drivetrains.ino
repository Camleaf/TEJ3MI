/*
 * You need the Bluepad32 Arduino library installed
 */
#include <Arduino.h>

#include "src/drivetrain.h"
#include "src/arm.h"
#include <Bluepad32.h>

// use gpios 4-18, 21, 38, 39, 40, 41, 42, 47,48 for pwm
//// drivetrain
// Back right
#define kbr1 4
#define kbr2 5
// Back left
#define kbl1 6
#define kbl2 7
// Front right
#define kfr1 8
#define kfr2 9
// Front left
#define kfl1 10
#define kfl2 11

// Misc vars
#define maxSpeed 128
#define turnPower 128

//// Arm
#define kbase1 0
#define kmid1 0
#define kclrot1 0
#define kclaw1 0
const int baseJointLength = 0; // mm
const int upperJointLength = 0; // mm
const int clawLength = 0; // mm
const int baseHeight = 10; // mm 




Mecanum drivetrain(kbr1,kbr2,kbl1,kbl2,kfr1,kfr2,kfl1,kfl2);
//Arm arm(kbase1,kmid1,kclrot1,kclaw1,baseJointLength,upperJointLength,clawLength,baseHeight);




ControllerPtr contr[BP32_MAX_CONTROLLERS];

void onConnectedController(ControllerPtr cptr) {
    for (int i = 0; i < BP32_MAX_CONTROLLERS; i++){
        if (contr[i] == nullptr) {
            contr[i] = cptr;
            return;
        }
    }
}

void onDisconnectedController(ControllerPtr cptr) {    
    for (int i = 0; i < BP32_MAX_CONTROLLERS; i++){
        if (contr[i] == cptr) {
            contr[i] = nullptr;
            return;
        }
    }
}

void processControllers(){
    for (auto cptr: contr) {
        if (!cptr) continue;

        if (cptr->isConnected() && cptr->hasData()){
            if (cptr->isGamepad()){
                drivetrain.updateMotor(
                    cptr->axisX(),
                    cptr->axisRX(),
                    cptr->axisY()
                ); 
                
            }
        }

    }
}




void setup(){
    Serial.begin(115200);

    BP32.setup(
            onConnectedController,
            onDisconnectedController
        );
    BP32.forgetBluetoothKeys();

    
    drivetrain.setMaxSpeed(maxSpeed);
    drivetrain.setTurnPower(turnPower);
    drivetrain.invertMotor(0,true); // invert backright
    drivetrain.invertMotor(1,true); // invert frontright
    /*
    arm.setBaseJointRange(0,135);
    arm.setClawOCpoint(0,180);
    arm.setUpperJointRange(0,180);
    */
  }



void loop(){
    
    if (BP32.update()){
        processControllers();
    }
}
