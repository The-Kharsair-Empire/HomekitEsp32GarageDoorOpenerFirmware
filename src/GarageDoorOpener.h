#pragma once
#ifndef GARAGE_DOOR_OPENER_H
#define GARAGE_DOOR_OPENER_H

#include <HomeSpan.h>
#include "RangeFinder.h"
#include "Relay.h"

#define TIME_TAKEN_TO_OPEN_N_CLOSE 8000  // 8s for the door to completely open and closed

struct AccessoryInformation: Service::AccessoryInformation {
    SpanCharacteristic* name;
    SpanCharacteristic* identity;


    explicit AccessoryInformation(const char* accessory_name): Service::AccessoryInformation() {
        name = new Characteristic::Name(accessory_name);
        identity = new Characteristic::Identify();
    }

};

struct GarageDoorOpener: Service::GarageDoorOpener {

    SpanCharacteristic* current;
    SpanCharacteristic* target;
    SpanCharacteristic* obstruction;

    GarageDoorOpener(): Service::GarageDoorOpener() {
        current = new Characteristic::CurrentDoorState(1);
        target = new Characteristic::TargetDoorState(1);
        obstruction = new Characteristic::ObstructionDetected(false);

        Serial.println("Setting up Garage Door Opener");

    }

    boolean update() override {
        if (target->getNewVal() == 0 && current->getVal() == 1) {
            switch_on_relay(200);
            current->setVal(2);
            Serial.println("Home app is opening the garage door");

        } else if (target->getNewVal() == 1 && current->getVal() == 0) {
            switch_on_relay(200);
            current->setVal(3);
            Serial.println("Home app is closing the garage door");
        }

        return true;
    }

    void loop() override {
        if (current->timeVal() > TIME_TAKEN_TO_OPEN_N_CLOSE) {

            Serial.println("Wait time up");

            if (infer_is_door_open()) {
                Serial.println("door is open");
                current->setVal(0);

            } else {
                Serial.println("door is closed");
                current->setVal(1);

            }

            // if (target->getVal() == current->getVal())
            //     obstruction->setVal(false);

            // if (target->getVal() != current->getVal()) {
            //     obstruction->setVal(true);
            //     current->setVal(4);
            //     Serial.println("door obstructed");
            // }


        }
    }
};

struct GarageDoorOpenerAccessory: SpanAccessory {
    SpanService* garageDoorOpener;
    SpanService* accessoryInformation;

    GarageDoorOpenerAccessory(): SpanAccessory() {
        accessoryInformation = new AccessoryInformation("Garage Door Opener");
        garageDoorOpener = new GarageDoorOpener();
    }


};



#endif