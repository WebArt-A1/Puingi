#include "Boot.h"
#include "Setup.h"

bool flag = false;


void initDisplay() {
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  SPI.end();
  SPI.begin();
  u8g2.begin();
  u8g2.setFont(u8g2_font_5x7_tr);
}


void primeCheck(){
  analogReadResolution(12);
  if(analogRead(ADC_VOLT_PIN) <= 0.65) {
    initDisplay();
    u8g2.drawStr(0, 16, "Warning!");
    u8g2.drawStr(0, 15, "Low battary level!");
    u8g2.sendBuffer();
    delay(1500);
    esp_sleep_enable_timer_wakeup(30 * 1000000);
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_timer_wakeup(30 * 1000000);
    delay(10)
    esp_deep_sleep_start();
  }
}


void secCheck(){
  if(!SD.begin(SD_CART_PIN)) {
    initDisplay();
    u8g2.drawStr(0, 7, "Display was inited!");
    u8g2.drawStr(0, 16, "SD card wasn't inited!");
    u8g2.sendBuffer();
  }
  initDisplay();
  u8g2.drawStr(0, 7, "Display was inited!");
  u8g2.drawStr(0, 16, "SD card was inited!");
}

void Boot::begin() {
  Serial.begin(115200);

  u8g2.drawStr(0, 7, "Display was inited!");
  u8g2.sendBuffer();

  primeCheck();
  secCheck();
}