#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <SD.h>

SdFat sd;
SdFile file;

// SPI setupNONE);

U8G2_SH1107_SEEED_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 2, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {

  Serial.begin(9600);
  u8g2.begin(); // Initialize display

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.drawStr(0, 10, "Initializing...");
  u8g2.sendBuffer();
  delay(100);

  u8g2.setFont(u8g2_font_tiny5_tf);
  u8g2.drawStr(5, 25, "Esp load.");
  u8g2.drawStr(5, 32, "Display load.");
  u8g2.sendBuffer();
  delay(1000);

  if (!SD.begin(16)){
    u8g2.begin();
    u8g2.drawStr(5, 25, "Esp load.");
    u8g2.drawStr(5, 32, "Display load.");
    u8g2.drawStr(5, 39, "SD card not find.");
    u8g2.sendBuffer();
  } else {
    u8g2.begin();
    u8g2.drawStr(5, 25, "Esp load.");
    u8g2.drawStr(5, 32, "Display load.");
    u8g2.drawStr(5, 39, "SD card load.");
    u8g2.sendBuffer();
  }

  if (dir.open("/", O_READ)) {
    Serial.println("Files in root directory:");

    // Loop through the directory and print file names
    SdFile entry;
    while (dir.openNext(&entry)) {
      Serial.print("File name: ");
      Serial.println(entry.name());
    }
    dir.close();
  } else {
    Serial.println("Failed to open root directory.");
  }
}

void loop(void) {
  delay(1000);
}
