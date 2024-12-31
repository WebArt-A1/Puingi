#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SH1107_128X128_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 8, /* dc=*/ 7, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);

  Serial.println("\nStart!");

  delay(10);

  u8g2.begin();

  Serial.println("\nEnd!");
}

void loop() {

  delay(10);

}
