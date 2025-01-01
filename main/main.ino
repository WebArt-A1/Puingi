#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <SD.h>


// Настройка для SPI интерфейса с дисплеем SH1107
U8G2_SH1107_SEEED_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 2, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // Инициализация дисплея
  u8g2.begin();
  delay(50);

  u8g2.clearBuffer();

  u8g2.setFont(fntgrpu8g_u8glib_4);
  u8g2.drawStr(0, 9, "Esp load.");
  u8g2.drawStr(0, 18, "Display load.");

  u8g2.sendBuffer();

  if (!SD.begin(0)) {
    u8g2.drawStr(0, 18, "SD card do not connect.")
    u8g2.sendBuffer();
    delay(100);
    u8g2.drawStr(0, 27, "Restart.");
    delay(2000);
    ESP.restart();
  } else {
    u8g2.drawStr(0, 27, "SD card load.");
  }
  delay(300);
}

void loop() {
  // Очищаем экран
  u8g2.clearBuffer();
  
  // Рисуем текст
  u8g2.drawStr(0, 20, "Hello, World!");
  
  // Отображаем на экране
  u8g2.sendBuffer();
  
  // Задержка
  delay(1000);
}
