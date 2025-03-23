#include "Menu.h"
#include "Setup.h"

String nowMenu = "Main Menu";
int nowIndex = 1;

bool upFlag = true;
bool clFlag = true;
bool dwFlag = true;

int dropFlag = 0;

int countLetters(const String& str) {
  int count = 0;
  for (int i = 0; i < str.length(); i++) {
    char ch = str.charAt(i);
    // Проверяем, является ли символ буквой
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      count++;
    }
  }
  return count;
}

String Menus[] = {
  "Main Menu",
  "Settings",
  "Files"
};

String Settings[] = {
  "Settings",
  "Back"
};

void Menu::begin() {
  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_CL_PIN, INPUT);
  pinMode(BUTTON_DW_PIN, INPUT);
}

void Menu::main(int up, int click, int down) {
  dropFlag++;

  if(dropFlag == 3){
    dropFlag = 0;
    upFlag = true;
    clFlag = true;
    dwFlag = true;
  }

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(64 - (countLetters(nowMenu) * 6) / 2, 7, nowMenu.c_str()); 

  if(up && upFlag) {
    upFlag = false;
    nowIndex -= 1;
  }
  if(down && dwFlag) {
    dwFlag = false;
    nowIndex += 1;
  }

  if(nowMenu == "Main Menu"){
    if(nowIndex == 0) {
      nowIndex = 2;
    }
    if(nowIndex == 3) {
      nowIndex = 1;
    }
    for(int i=1; i<=2; i++){
      u8g2.setFont(u8g2_font_7x14_tr);
      if(i == nowIndex) {
        u8g2.setFont(u8g2_font_7x14B_tr);
        if(click) {
          nowMenu = Menus[i];
          delay(250);
        }
      }
      u8g2.drawStr(0, 14+i*16, Menus[i].c_str());
    }
  }                                                   // Main menu 
  if(nowMenu == "Settings"){
    if(nowIndex == 0) {
      nowIndex = 2;
    }
    if(nowIndex == 3) {
      nowIndex = 1;
    }
    for(int i=1; i<=2; i++){
      u8g2.setFont(u8g2_font_7x14_tr);
      if(i == nowIndex) {
        u8g2.setFont(u8g2_font_7x14B_tr);
        if(click) {
          if(Settings[i] == "Back"){
            nowMenu = "Main Menu";
            delay(250);
          } else {
            nowMenu = Settings[i];
            delay(250);
          }
        }
      }
      u8g2.drawStr(0, 14+i*16, Settings[i].c_str());
    }
  }

  if(click && up && down) {
    esp_restart();  
  }

  u8g2.sendBuffer();
}