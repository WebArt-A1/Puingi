#include "./display.h"

display disp;

void setup() {
  Serial.begin(115200);
  disp.init();
}

void loop() {
  disp.menu(0);
  delay(100);
  Serial.println("ArduBlock RU EN");
}