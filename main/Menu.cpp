#include "Menu.h"
#include "Setup.h"

int nowMenu = 0;
int nowIndex = 0;

String MainMenu[] = {
  "Main Menu",
  "Settings",
  "Files"
};

void Menu::begin() {
  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_CL_PIN, INPUT);
  pinMode(BUTTON_DW_PIN, INPUT);
}

void Menu::main(int up, int click, int down) {
  u8g2.clearBuffer();

  if(nowMenu == 0){
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(54, 7, MainMenu[0].c_str()); 
    u8g2.setFont(u8g2_font_7x14_tr);
    for(int i=1; i<=2; i++){
      u8g2.drawStr(0, 9+i*9, MainMenu[i].c_str());
    }
  }

  u8g2.sendBuffer();
}