#include "Setup.h"

int BUTTON_UP_PIN = 35;
int BUTTON_CL_PIN = 34;
int BUTTON_DW_PIN = 13;

int SD_CART_PIN = 5;

int ADC_VOLT_PIN = 14;

U8G2_SH1107_PIMORONI_128X128_F_4W_HW_SPI u8g2(U8G2_R0,/* cs=*/ 15, /* dc=*/ 21, /* reset=*/ 22);