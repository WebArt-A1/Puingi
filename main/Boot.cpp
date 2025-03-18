#include "Boot.h"
#include "Setup.h"

void step(int step) {
  u8g2.clearBuffer();

  switch(step) {
    case 0:
      u8g2.drawStr(0, 8, "[OK] Main script was inited.");
      u8g2.drawStr(0, 16, "[NO] SD card was inited with error.");
      break;

    case 1:
      u8g2.drawStr(0, 8, "[OK] Main script was inited.");
      u8g2.drawStr(0, 16, "[OK] SD card was inited.");
      break;
  }

  u8g2.sendBuffer();
}

void initSPI() {
  SPI.end();
  SPI.begin();
  u8g2.begin();
}

void Boot::begin() {
  Serial.begin(115200);

  pinMode(15, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);

  u8g2.begin();
  u8g2.setFont(u8g2_font_4x6_mr);
  u8g2.clearBuffer();

  if(!SD.begin(12)) {
    initSPI();
    step(0);
    delay(3000);
    ESP.restart();
  }
  initSPI();
  step(1);
  u8g2.drawStr(0, 24, "Please click on buttons.");
  for (int i = 0; i < 3; i++) {
    u8g2.drawStr(0, 32 + i * 8, "[  ]");
  }
  u8g2.sendBuffer();
  bool flags[3] = {false};
  int pins[] = {15, 2, 4};
  int yPos[] = {32, 40, 48};

  while (true) {
    bool allTrue = true;

    for (int i = 0; i < 3; i++) {
      if (digitalRead(pins[i]) && !flags[i]) {
        flags[i] = true;
        u8g2.drawStr(0, yPos[i], "[OK]");
        u8g2.sendBuffer();
      }
      allTrue &= flags[i];
    }

    if (allTrue) break;
    delay(100);
  }
  u8g2.clearBuffer();
  step(1);
  u8g2.drawStr(0, 24, "[OK] Buttons was inited.");
  u8g2.sendBuffer();
  ESP.restart();
}