#include <Wire.h>

#include "obd.h"
#include "oled.h"

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    OLED::init();
    OLED::dim(true);

    OLED::displayLogo();
}

static OBD::VehicleData data;
static bool didinit = false;

void loop() {
    if (!didinit) {
        OLED::displayLogo("Initializing...");
        didinit = OBD::init();
        if (didinit) {
            OLED::displayLogo("Standby");
            digitalWrite(LED_BUILTIN, HIGH);
        }
    } else {
        if (OBD::getData(data)) {
            OLED::update(data);
        } else {
            OLED::displayLogo("Standby");
        }
    }

    delay(17);
}
