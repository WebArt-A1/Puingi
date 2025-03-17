#include "Boot.h"
#include "Setup.h"

void Boot::begin() {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_mr);
  u8g2.clearBuffer();

  u8g2.drawStr(0, 8, "[ OK ] Display was initialized");
  u8g2.sendBuffer();

  if (!SD.begin(12)) {
    u8g2.drawStr(0, 16, "[ NO ] SD card initialized with error.");
    u8g2.sendBuffer();
    delay(5000);
    ESP.restart(); 
  }
  u8g2.drawStr(0, 16, "[ OK ] SD card was initialized.");
  u8g2.sendBuffer();
}