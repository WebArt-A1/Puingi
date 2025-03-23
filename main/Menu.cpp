#include "Menu.h"
#include "Setup.h"

String nowMenu = "Main Menu";
int nowIndex = 1;

bool upFlag = true;
bool clFlag = true;
bool dwFlag = true;

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

void controlIndex(int max){
  if(nowIndex == 0) {
    nowIndex = max;
  }
  if(nowIndex > max) {
    nowIndex = 1;
  }
}

void Menu::begin() {
  pinMode(BUTTON_UP_PIN, INPUT);
  pinMode(BUTTON_CL_PIN, INPUT);
  pinMode(BUTTON_DW_PIN, INPUT);
}

void Menu::main(int up, int click, int down) {

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(64 - (countLetters(nowMenu) * 6) / 2, 7, nowMenu.c_str()); 

  if (up && upFlag) {
    upFlag = false;
    nowIndex--;
  } else if(!up) {
    upFlag = true;
  }

  if (down && dwFlag) {
    dwFlag = false;
    nowIndex++;
  } else if(!down) {
    dwFlag = true;
  }

  if(nowMenu == "Main Menu"){
    controlIndex(2);
    for(int i=1; i<=2; i++){
      u8g2.setFont(u8g2_font_7x14_tr);
      if(i == nowIndex) {
        u8g2.setFont(u8g2_font_7x14B_tr);
        if(click && clFlag) {
          clFlag = false;
          nowMenu = Menus[i];
        } else if(!click) {
          clFlag = true;
        }
      }
      u8g2.drawStr(0, 14+i*16, Menus[i].c_str());
    }
  }                                                   // Main menu 
  if(nowMenu == "Settings"){
    controlIndex(1);
    for(int i=1; i<=1; i++){
      u8g2.setFont(u8g2_font_7x14_tr);
      if(i == nowIndex) {
        u8g2.setFont(u8g2_font_7x14B_tr);
        if(click && clFlag) {
          clFlag = false;
          if(Settings[i] == "Back"){
            nowMenu = "Main Menu";
          } else {
            nowMenu = Settings[i];
          }
        } else if(!click) {
          clFlag = true;
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