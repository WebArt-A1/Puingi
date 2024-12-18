#include "./display.h"

display disp;

void setup(void) {
  Serial.begin(9600);
  disp.init();
  disp.boot();
}

void loop(void) {
  disp.menu(Serial.read());
  delay(100);
}