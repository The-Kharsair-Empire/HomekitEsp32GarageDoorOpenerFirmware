#include <Arduino.h>
#include "GarageDoorOpener.h"
#include "RangeFinder.h"
#include "system.h"
#include "Relay.h"

GarageDoorOpenerAccessory* garageDoorOpenerAccessory;

xTaskHandle rangeFinderSampleTaskHandle;


void setup() {
    Serial.begin(115200);

    initialize_relay();

    homeSpan.setPairingCode("23452345"); // todo, use cli to set this number
    homeSpan.begin(Category::GarageDoorOpeners, "Garage Door Opener");

    garageDoorOpenerAccessory = new GarageDoorOpenerAccessory();

    Serial.println("setting up...");

    xTaskCreatePinnedToCore(&sample_loop, "range finder",
                            2048, nullptr, 1,
                            &rangeFinderSampleTaskHandle, app_cpu);

}

void loop() {
    homeSpan.poll();
}