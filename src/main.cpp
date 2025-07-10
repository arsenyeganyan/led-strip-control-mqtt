#include <Arduino.h>
#include "ledStrip.h"
#include "mqttSetup.h"

void setup() {
  Serial.begin(115200);

  ledSetup();
  mqttSetup();
}

void loop() {
  // ledLoop();

  mqttLoop();
}