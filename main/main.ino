#include "./display.h"

Display disp;

void setup(void) {
  disp.begin();
  Serial.begin(115200);
}

void loop(void) {
  disp.menu(Serial.read());
  delay(10);
}