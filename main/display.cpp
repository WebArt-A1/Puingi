#include "disp_control.h"

#include <Wire.h>
#include <U8g2lib.h>

disp_control::disp_control() {
  _init = 0;
}

void init(){
  U8G2_SH1107_SEEED_128X128_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 22, /* data=*/ 23, /* reset=*/ U8X8_PIN_NONE);
}