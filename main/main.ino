#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <SD.h>


// Настройка для SPI интерфейса с дисплеем SH1107
U8G2_SH1107_PIMORONI_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 2, /* reset=*/ U8X8_PIN_NONE);

File myFile;

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g2_font_t0_11_t_all);
  delay(50);

  u8g2.clearBuffer();

  u8g2.setCursor(0, 9);
  u8g2.print("Esp load.");

  delay(100);

  u8g2.setCursor(0, 18);
  u8g2.print("Display load.");

  u8g2.sendBuffer();
}

void loop() {

}
