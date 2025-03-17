#include "Boot.h"
#include "Setup.h"

void Boot::begin() {
  Serial.begin(115200);

  pinMode(15, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);

  u8g2.begin();
  u8g2.setFont(u8g2_font_4x6_mr);
  u8g2.clearBuffer();

  if(!SD.begin(12)) {
    SPI.end();
    SPI.begin();
    u8g2.begin();

    u8g2.drawStr(0, 8, "[OK] Main script was inited.");
    u8g2.drawStr(0, 16, "[NO] SD card was inited with error.");
    u8g2.sendBuffer();
    delay(3000);
    ESP.restart();
  }
  SPI.end();
  SPI.begin();
  u8g2.begin();
  u8g2.drawStr(0, 8, "[OK] Main script was inited.");
  u8g2.drawStr(0, 16, "[OK] SD card was inited.");
  u8g2.drawStr(0, 24, "Please click on buttons.");
  u8g2.drawStr(0, 32, "[  ]");
  u8g2.drawStr(0, 40, "[  ]");
  u8g2.drawStr(0, 48, "[  ]");
  u8g2.sendBuffer();
  bool b1 = false;
  bool b2 = false;
  bool b3 = false;
  while(true) {
    if(digitalRead(15)){
      b1 = true;
      u8g2.drawStr(0, 32, "[OK]");
      u8g2.sendBuffer();
    }
    if(digitalRead(2)){
      b2 = true;
      u8g2.drawStr(0, 40, "[OK]");
      u8g2.sendBuffer();
    }
    if(digitalRead(4)){
      b3 = true;
      u8g2.drawStr(0, 48, "[OK]");
      u8g2.sendBuffer();
    }
    if(b1 && b2 && b3) {
      break;
    }
    delay(100);
  }
  u8g2.clearBuffer();
  u8g2.drawStr(0, 8, "[OK] Main script was inited.");
  u8g2.drawStr(0, 16, "[OK] SD card was inited.");
  u8g2.drawStr(0, 24, "[OK] Buttons was inited");
  u8g2.sendBuffer();
}