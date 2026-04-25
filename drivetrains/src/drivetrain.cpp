#include <Arduino.h>
#include <cstdint>
#include "./drivetrain.h"
#include "esp32-hal.h"

#include <array>
#include <cstdint>
#include <string>
using namespace std;



void setMotor(uint8_t in1, uint8_t in2, int val){
    if (val >= 0) {
        analogWrite(in1, val);
        analogWrite(in2, 0);
    } else {
        analogWrite(in2, -val);
        analogWrite(in1, 0);
    }
}


Arcade::Arcade(uint8_t kbr1, uint8_t kbr2, uint8_t kbl1, uint8_t kbl2, uint8_t kfr1, uint8_t kfr2, uint8_t kfl1, uint8_t kfl2){
    
    this->maxSpeed = 255;
    this->turnPower = 255;
        
    this->kbr1 = kbr1;
    this->kbr2 = kbr2;
    this->kbl1 = kbl1;
    this->kbl2 = kbl2;
    this->kfr1 = kfr1;
    this->kfr2 = kfr2;
    this->kfl1 = kfl1;
    this->kfl2 = kfl2;
}


void Arcade::setTurnPower(uint8_t turnPower){
    this->turnPower = turnPower;
}
        
void Arcade::setMaxSpeed(uint8_t maxSpeed){
    this->maxSpeed = maxSpeed;
}

void Arcade::updateMotor(int joyX, int joyY){
    
    // Great source for arcade drive https://xiaoxiae.github.io/Robotics-Simplified-Website/drivetrain-control/arcade-drive/

    joyX = map(joyX,-512,512,-turnPower,turnPower);
    joyY = map(joyY,-512,512,-maxSpeed,maxSpeed);

    int turn = constrain(joyX,-maxSpeed,maxSpeed);
    int drive = constrain(joyY,-turnPower,turnPower);

    int maximum = max(abs(drive), abs(turn));
    int total = drive + turn;
    int difference = drive - turn;

    int rightSide;
    int leftSide;

    if (drive >= 0){
        if (turn >= 0){ // q1
            leftSide = maximum;
            rightSide = difference;
        } else { 
            leftSide = total;
            rightSide = maximum;
        }
    } else {
        if (turn >= 0){
            leftSide = total;
            rightSide = -maximum;
        } else { 
            leftSide = -maximum;
            rightSide = difference;
        }
    }
    
    setMotor(kbr1,kbr2,rightSide);
    setMotor(kfr1,kfr2,rightSide);
    setMotor(kbl1,kbl2,leftSide);
    setMotor(kfl1,kfl2,leftSide);

}


Mecanum::Mecanum(uint8_t kbr1, uint8_t kbr2, uint8_t kbl1, uint8_t kbl2, uint8_t kfr1, uint8_t kfr2, uint8_t kfl1, uint8_t kfl2){
    
    this->maxSpeed = 255;
    this->turnPower = 255;
        
    this->kbr1 = kbr1;
    this->kbr2 = kbr2;
    this->kbl1 = kbl1;
    this->kbl2 = kbl2;
    this->kfr1 = kfr1;
    this->kfr2 = kfr2;
    this->kfl1 = kfl1;
    this->kfl2 = kfl2;
}


void Mecanum::setTurnPower(uint8_t turnPower){
    this->turnPower = turnPower;
}
        
void Mecanum::setMaxSpeed(uint8_t maxSpeed){
    this->maxSpeed = maxSpeed;
}

void Mecanum::updateMotor(int joyX, int joyX2, int joyY){
    
    // Great source for mecanum drive
    //https://gm0.org/en/latest/docs/software/tutorials/mecanum-drive.html

    joyX = map(joyX,-512,512,-maxSpeed, maxSpeed);
    joyX2 = map(joyX2,-512,512,-turnPower,turnPower);
    joyY = map(joyY,-512,512,-maxSpeed,maxSpeed);
    
    int x_drive = constrain(joyX,-maxSpeed,maxSpeed); // horizontal drive
    int y_drive = constrain(joyY,-maxSpeed,maxSpeed); // standard drive
    int turn = constrain(joyX2,-turnPower,turnPower);
    
    // Back right motor, reversed
    setMotor(kbr2,kbr1,y_drive + x_drive - turn);
    // Front right motor, reversed
    setMotor(kfr2,kfr1,y_drive - x_drive - turn);
    // Back left motor
    setMotor(kbl1,kbl2,y_drive - x_drive + turn);
    // Front left motor
    setMotor(kfl1,kfl2,y_drive + x_drive + turn);
}



