#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <SdFat.h>
#include <SPI.h>
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
}
