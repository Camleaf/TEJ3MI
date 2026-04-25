/*
 * You need the Bluepad32 Arduino library installed
 */
#include <Arduino.h>
#include "ArduinoBluepad32.h"
#include "ArduinoController.h"
#include <Bluepad32.h>
#include "./controller.h"

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




void SetupBP32(){
    BP32.setup(
            onConnectedController,
            onDisconnectedController
        );
    BP32.forgetBluetoothKeys();
}

void tickControllers(){
    if (BP32.update()){
        processControllers();
    }
}
