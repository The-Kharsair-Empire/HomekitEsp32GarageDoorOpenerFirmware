#include <Arduino.h>
#include "GarageDoorOpener.h"
#include "RangeFinder.h"
#include "system.h"
#include "Relay.h"

GarageDoorOpenerAccessory* garageDoorOpenerAccessory;

xTaskHandle rangeFinderSampleTaskHandle;


// struct LED : Service::LightBulb {
//     int led_pin;
//     SpanCharacteristic *power;

//     LED(int pin): Service::LightBulb() {
//         power =  new Characteristic::On();
//         this->led_pin = pin;
//         pinMode(pin, OUTPUT);
//     }

//     boolean update() {
//         digitalWrite(led_pin, power->getNewVal());
//         return true;
//     }
// };

void setup() {
    Serial.begin(115200);

    initialize_relay();

    homeSpan.setPairingCode("11122333"); // todo, use cli to set this number
    homeSpan.begin(Category::GarageDoorOpeners, "Garage Door");

    garageDoorOpenerAccessory = new GarageDoorOpenerAccessory();

    Serial.println("setting up...");

    xTaskCreatePinnedToCore(&sample_loop, "range finder",
                            2048, nullptr, 1,
                            &rangeFinderSampleTaskHandle, app_cpu);

}

void loop() {
    homeSpan.poll();
//    Serial.println("Polling...");
}