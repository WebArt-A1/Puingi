#include <Arduino.h>
#include <U8g2lib.h>
#include <IRremote.hpp> 
#include <SPI.h>

U8G2_SH1107_PIMORONI_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 32, /* dc=*/ 14, /* reset=*/ 27);
char irCodeStr[20]; 
#define IR_RECEIVE_PIN 17 

void setup() {
  Serial.begin(2000000);

  pinMode(2, INPUT);  
  pinMode(16, OUTPUT);  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  u8g2.begin();

  u8g2.setFont(u8g2_font_6x13B_tf);

  u8g2.drawStr(0, 20, "Test");

  u8g2.sendBuffer();
}

void loop() {
  delay(0.1);
  Serial.println(digitalRead(2));
  if ( digitalRead(2) == 1 ) {
    digitalWrite(16, HIGH);  
    u8g2.clearBuffer();
    u8g2.drawStr(0, 20, "On");
    if (IrReceiver.decode()) { // Если получен сигнал
      IrReceiver.printIRResultShort(&Serial); // Вывод краткой информации о сигнале
      Serial.println(); // Перевод строки
      IrReceiver.resume(); // Готовность к приему следующего сигнала
    }
  } else {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 20, "Off");
    digitalWrite(16, LOW);  
  }
  u8g2.sendBuffer();
}
