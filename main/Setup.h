#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <SD.h>
#include "FS.h"

//#include <SdFat.h>

extern U8G2_SH1107_PIMORONI_128X128_F_4W_HW_SPI u8g2;

extern int BUTTON_UP_PIN;
extern int BUTTON_CL_PIN;
extern int BUTTON_DW_PIN;
extern int SD_CART_PIN;
extern int ADC_VOLT_PIN;

#endif