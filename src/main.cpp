#include <Arduino.h>
#include "GarageDoorOpener.h"
#include "system.h"
#include "Relay.h"

GarageDoorOpenerAccessory* garageDoorOpenerAccessory;

xTaskHandle rangeFinderSampleTaskHandle;


void setup() {
    Serial.begin(115200);

    initialize_relay();
    setup_reed_switch();

    homeSpan.setPairingCode("23452345"); // todo, use cli to set this number
    homeSpan.begin(Category::GarageDoorOpeners, "Garage Door Opener");

    homeSpan.setLogLevel(2);

    garageDoorOpenerAccessory = new GarageDoorOpenerAccessory();

    Serial.println("setting up...");

}

void loop() {
    homeSpan.poll();
}