#include "Setup.h"
#include "Boot.h"
#include "Menu.h"

Boot boot;
Menu menu;

void setup() {
  boot.begin();
  menu.begin();
}

void loop() {
  delay(100);
  menu.main(digitalRead(BUTTON_UP_PIN), digitalRead(BUTTON_CL_PIN), digitalRead(BUTTON_DW_PIN));
}