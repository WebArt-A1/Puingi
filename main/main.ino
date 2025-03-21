#include "Setup.h"
#include "Boot.h"

Boot boot;

void setup() {
  boot.begin();
}

void loop() {
  delay(1000);
  esp_restart();
}