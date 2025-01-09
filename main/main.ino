#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <SdFat.h>
#include <ESP8266WiFi.h>

SdFat sd;

String IsBoot="";
String Name="";
String Version="";
// SPI setupNONE);

U8G2_SH1107_SEEED_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 2, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {

  Serial.begin(9600);
  u8g2.begin();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.drawStr(0, 10, "Initializing...");
  u8g2.sendBuffer();
  delay(100);

  u8g2.setFont(u8g2_font_tiny5_tf);
  u8g2.drawStr(0, 25, "< Ok > Esp load.");
  u8g2.drawStr(0, 32, "< Ok > Display load.");
  u8g2.sendBuffer();
  delay(250);

  u8g2.setPowerSave(true);

  if (!sd.begin(16)) {
    u8g2.setPowerSave(false);
    u8g2.begin();
    u8g2.setFont(u8g2_font_t0_11_tf);
    u8g2.drawStr(0, 10, "Initializing...");

    u8g2.setFont(u8g2_font_tiny5_tf);
    u8g2.drawStr(0, 25, "< Ok > Esp load.");
    u8g2.drawStr(0, 32, "< Ok > Display load.");
    u8g2.drawStr(0, 39, "< No > SD card not load.");
    u8g2.sendBuffer();

    u8g2.setFont(u8g2_font_t0_11_tf);

    u8g2.drawStr(0, 51, "Restart after:");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 9 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 8 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 7 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 6 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 5 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 4 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 3 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 2 ");
    u8g2.sendBuffer();

    delay(1000);

    u8g2.drawStr(50, 63, " 1 ");
    u8g2.sendBuffer();

    delay(1000);

    ESP.restart();
  }

  File32 file = sd.open("/System/boot/boot.sys", FILE_READ);

  if (file) {
    while (file.available()) {
      String line = file.readStringUntil('\n');
      if (line.startsWith("boot=")) {
        IsBoot = line.substring(line.indexOf('=') + 1);
      }
      if (line.startsWith("name=")) {
        Name = line.substring(line.indexOf('=') + 1);
      }
      if (line.startsWith("vers=")) {
        Version = line.substring(line.indexOf('=') + 1);
      }
    }
    file.close();
  } else {
    u8g2.setPowerSave(false);
    u8g2.begin();
    u8g2.setFont(u8g2_font_t0_11_tf);
    u8g2.drawStr(0, 10, "Initializing...");
    
    u8g2.setFont(u8g2_font_tiny5_tf);
    u8g2.drawStr(0, 25, "< Ok > Esp load.");
    u8g2.drawStr(0, 32, "< Ok > Display load.");
    u8g2.drawStr(0, 39, "< Ok > SD load.");
    u8g2.sendBuffer();
    delay(100);

    u8g2.drawStr(0, 46, "< No > Boot file not load.");
    u8g2.sendBuffer();

    delay(5000);

    ESP.restart();
  }



  u8g2.setPowerSave(false);
  u8g2.begin();
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.drawStr(0, 10, "Initializing...");
  
  u8g2.setFont(u8g2_font_tiny5_tf);
  u8g2.drawStr(0, 25, "< Ok > Esp load.");
  u8g2.drawStr(0, 32, "< Ok > Display load.");
  u8g2.drawStr(0, 39, "< Ok > SD load.");
  u8g2.sendBuffer();

  delay(200);

  

  if (IsBoot != "true") {
    IsBoot = "< No > Boot mode: " + IsBoot;
    u8g2.drawStr(0, 46, "< Ok > Boot file load.");
    u8g2.drawStr(0, 53, IsBoot.c_str());
    u8g2.sendBuffer();
    while (true) {
      yield();
      delay(1000);
    }
  }

  IsBoot = "< Ok > Boot mode: " + IsBoot;
  Name = "< Ok > Boot loader name: " + Name;
  Version = "< Ok > Boot loader version: " + Version;

  u8g2.drawStr(0, 46, "< Ok > Boot file load.");
  u8g2.drawStr(0, 53, IsBoot.c_str());
  u8g2.drawStr(0, 60, Name.c_str());
  u8g2.drawStr(0, 67, Version.c_str());
  u8g2.sendBuffer();

  delay(100);

  u8g2.drawStr(0, 74, "Soft-ware load correct.");

  delay(2500);

  u8g2.clearBuffer();
  u8g2.sendBuffer();

  u8g2.setPowerSave(true);

  sd.begin(16);

  String c;

  File32 bm1 = sd.open("/System/Load/Load_1.bm", FILE_READ);

  if (bm1) {
    //while (bm1.available()) {
    c = bm1.readString();
    bm1.close();
  }
  bm1.close();

  char bmc1[c.length() + 1];

  c.toCharArray(bmc1, sizeof(bmc1));

  //uint8_t* buff = reinterpret_cast<uint8_t*>(bmc1);

  uint8_t* buff = {bmc1};

  u8g2.setPowerSave(false);
  u8g2.begin();

  Serial.print(bmc1);

  u8g2.drawXBMP(0, 0, 128, 128, buff);

 

}

void loop(void) {
  delay(1000);
}
