
#pragma once

#ifndef REEDSWITCH_H
#define REEDSWITCH_H

#include <Arduino.h>

static const int REED_SWITCH_PIN = 17;

volatile bool door_open = false;

void IRAM_ATTR onPinInterrupt() {
    int reed_switch_state = digitalRead(REED_SWITCH_PIN);
    if (reed_switch_state == HIGH) { // magnet detected
        door_open = false; // door close when magnet is detected
    } else {
        door_open = true;
    }
}

void setup_reed_switch() {
    pinMode(REED_SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(REED_SWITCH_PIN, &onPinInterrupt, CHANGE);
}




//#include <Arduino.h>
//const int REED_PIN = 2;	// Pin connected to reed switch
//const int LED_PIN = 13;	// LED pin
//
//void setup() {
//    Serial.begin(9600);
//    pinMode(REED_PIN, INPUT_PULLUP);	// Enable internal pull-up for the reed switch
//    pinMode(LED_PIN, OUTPUT);
//}
//
//void loop() {
//    int proximity = digitalRead(REED_PIN); // Read the state of the switch
//
//    // If the pin reads low, the switch is closed.
//    if (proximity == LOW) {
//        Serial.println("Switch closed");
//        digitalWrite(LED_PIN, HIGH);	// Turn the LED on
//    }
//    else {
//        Serial.println("Switch opened"); // this code turn off led when magnet approaches
//        digitalWrite(LED_PIN, LOW);		// Turn the LED off
//    }
//}

#endif
