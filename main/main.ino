#include "./display.h"
#include "./Key13.h"

Display disp;
Key13 key13;

void setup(void) {
  disp.begin();
  Serial.begin(115200);
}

void loop(void) {
  Serial.println("1");
  delay(10);
}