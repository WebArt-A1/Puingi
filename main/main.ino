#include <Arduino.h>
#include <U8g2lib.h>
#include <SdFat.h>
#include <SPI.h>
<<<<<<< HEAD
#include <Wire.h>
#include <Adafruit_MCP23X17.h>

U8G2_SH1107_PIMORONI_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 2, /* reset=*/ U8X8_PIN_NONE);

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(2000000);

  Wire.begin();
  mcp.begin_I2C();

  mcp.pinMode(0, OUTPUT);
  mcp.digitalWrite(0, LOW);

  u8g2.begin();

  u8g2.setFont(u8g2_font_6x13B_tf);

  u8g2.drawStr(0, 20, "Test");

  u8g2.sendBuffer();
}

void loop() {
  // Основной цикл  
=======
#include <SdFat.h>
#include <ESP8266WiFi.h>

SdFat sd;

String IsBoot="";
String Name="";
String Version="";

uint8_t* data;
uint8_t* data1;
uint8_t* data2;
uint8_t* data3;
uint8_t* data4;
uint8_t* data5;
uint8_t* data6;
uint8_t* data7;
uint8_t* data8;
uint8_t* data9;
uint8_t* data10;

U8G2_SH1107_SEEED_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* cs=*/ 15, /* dc=*/ 2, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {

  Serial.begin(921600);
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

  if (true) { // 1

    File32 hexFile = sd.open("/System/Load/Load_1.bm", FILE_READ);

    uint16_t maxSize = hexFile.size();  // Get the size of the file
    data = (uint8_t*) malloc(maxSize);

    int index = 0;
    String hexString = "";

    while (hexFile.available() && index < maxSize) {
      char c = hexFile.read();

      if (c == ',' || c == '\n' || c == '\r') {
        if (hexString.length() > 0) {
          data[index] = strtol(hexString.c_str(), NULL, 16);
          index++;
          hexString = "";
        }
      } else if (c != ' ' && c != 'x') {
        hexString += c;
      }
      yield();
    }

    hexFile.close();

    if (hexString.length() > 0 && index < maxSize) {
      data[index] = strtol(hexString.c_str(), NULL, 16);
      index++;
    }
  }

  if (true) { // 2

    File32 hexFile = sd.open("/System/Load/Load_2.bm", FILE_READ);

    uint16_t maxSize = hexFile.size();  // Get the size of the file
    data1 = (uint8_t*) malloc(maxSize);

    int index = 0;
    String hexString = "";

    while (hexFile.available() && index < maxSize) {
      char c = hexFile.read();

      if (c == ',' || c == '\n' || c == '\r') {
        if (hexString.length() > 0) {
          data1[index] = strtol(hexString.c_str(), NULL, 16);
          index++;
          hexString = "";
        }
      } else if (c != ' ' && c != 'x') {
        hexString += c;
      }
      yield();
    }

    hexFile.close();

    if (hexString.length() > 0 && index < maxSize) {
      data1[index] = strtol(hexString.c_str(), NULL, 16);
      index++;
    }
  }




  u8g2.setPowerSave(false);
  u8g2.begin();

  u8g2.drawXBMP(0, 0, 128, 128, data);
  u8g2.sendBuffer();
  free(data);

  delay(500);

  u8g2.drawXBMP(0, 0, 128, 128, data1);
  u8g2.sendBuffer();
  free(data1);

}

void loop(void) {
  delay(1000);
>>>>>>> c8dab592dc454db0d0d7ea7a81987cc1ed856037
}
