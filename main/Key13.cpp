#include "Key13.h"

#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include <SPI.h>
#include <MFRC522.h>

Adafruit_MCP23X17 mcp;
MFRC522 rfid(0, -1);

Key13::Key13() {
    _init = 1;
}

void Key13::begin(){
  Serial.begin(115200);
  Wire.begin(0, 1);
  
  if (!mcp.begin_I2C()) {
    Serial.println("MCP23017 initialization failed!");
    while (1);
  }

  mcp.pinMode(0, OUTPUT); // SDA
  pinMode(3, OUTPUT); // SCK
  pinMode(4, OUTPUT); // MOSI
  pinMode(6, INPUT);  // MISO

  SPI.begin();           // Инициализация SPI
  rfid.PCD_Init();       // Инициализация RC522
  Serial.println("Place your card near the reader...");
}

void Key13::read(){
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Выводим UID карты
  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  rfid.PICC_HaltA(); // Останавливаем считывание карты
}