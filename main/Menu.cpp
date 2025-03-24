#include "Menu.h"
#include "Setup.h"

String nowMenu = "Main Menu";
int nowIndex = 1;

int x = 0;

bool upFlag = true;
bool clFlag = true;
bool dwFlag = true;

String nowDir = "/";
int itemsFile = 0;

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

String removeLastPathSegment(String path) {
  int lastSlash = path.lastIndexOf('/');
  if (lastSlash > 0) {
      return path.substring(0, lastSlash); // Обрезаем до последнего '/'
  }
  return "/"; // Если достигли корня, возвращаем "/"
}

String getLastPathSegment(String path) {
    int lastSlash = path.lastIndexOf('/');
    if (lastSlash >= 0 && lastSlash < path.length() - 1) {
        return path.substring(lastSlash + 1); // Берём всё после последнего '/'
    }
    return path; // Если слэша нет, возвращаем исходную строку
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
  if(nowMenu == "Files") {
    Serial.println(countLetters(nowDir));
    if(countLetters(nowDir) >= 17) {
      u8g2.drawStr(0, 7, ("/../" + getLastPathSegment(nowDir)).c_str()); 
    } else {
      u8g2.drawStr(0, 7, nowDir.c_str()); 
    }
  } else {
    u8g2.drawStr(64 - (countLetters(nowMenu) * 6) / 2, 7, nowMenu.c_str()); 
  }

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
      x = 0;
      if(i == nowIndex) {
        u8g2.setFont(u8g2_font_7x14B_tr);
        x = 5;
        if(click && clFlag) {
          clFlag = false;
          nowIndex = 1;
          nowDir = "/";
          nowMenu = Menus[i];
        } else if(!click) {
          clFlag = true;
        }
      }
      u8g2.drawStr(x, 14+i*16, Menus[i].c_str());
    }
  }                                                   // Main menu 
  if(nowMenu == "Settings"){
    controlIndex(1);
    for(int i=1; i<=1; i++){
      u8g2.setFont(u8g2_font_7x14_tr);
      x = 0;
      if(i == nowIndex) {
        u8g2.setFont(u8g2_font_7x14B_tr);
        x = 5;
        if(click && clFlag) {
          clFlag = false;
          nowIndex = 1;
          if(Settings[i] == "Back"){
            nowMenu = "Main Menu";
          } else {
            nowMenu = Settings[i];
          }
        } else if(!click) {
          clFlag = true;
        }
      }
      u8g2.drawStr(3, 14+i*16, Settings[i].c_str());
    }
  }
  if(nowMenu == "Files"){
    controlIndex(itemsFile+1);
    if (nowDir == "/") {
      itemsFile = 0;
    } else {
      itemsFile = 1;
    }
    File root = SD.open(nowDir);
    while (File entry = root.openNextFile()) {
      String name = entry.name(); 
      int lastSlash = name.lastIndexOf('/');
      if (lastSlash >= 0) {
        name = name.substring(lastSlash + 1);
      }
      itemsFile++;
      u8g2.setFont(u8g2_font_7x14_tr);
      x = 0;
      if(itemsFile == nowIndex){
        u8g2.setFont(u8g2_font_7x14B_tr);
        x = 5;
        if(click && clFlag) {
          clFlag = false;
          nowIndex = 1;
          if(nowDir == "/"){
            nowDir = nowDir + name;
          } else {
            nowDir = nowDir + "/" + name;
          }
          
        } else if (!click) {
          clFlag = true;
        }
        
      }
      u8g2.drawStr(x, 14+itemsFile*16, name.c_str());
    }
    if(nowIndex == itemsFile+1) {
      u8g2.setFont(u8g2_font_7x14B_tr);
      u8g2.drawStr(0, 30+itemsFile*16, "Back");
      if(click && clFlag) {
        nowIndex = 1;
        clFlag = false;
        nowMenu = "Main Menu";
      } else if (!click){
        clFlag = true;
      }
    } else {
      u8g2.setFont(u8g2_font_7x14_tr);
      u8g2.drawStr(0, 30+itemsFile*16, "Back");
    }
  }
  if(nowDir != "/") {
    if(nowIndex == 1) {
      u8g2.setFont(u8g2_font_7x14B_tr);
      u8g2.drawStr(0, 30, "..");
      if(click && clFlag) {
        nowIndex = 1;
        clFlag = false;
        nowDir = removeLastPathSegment(nowDir);
      } else if (!click){
        clFlag = true;
      }
    } else {
      u8g2.setFont(u8g2_font_7x14_tr);
      u8g2.drawStr(0, 30, "..");
    }
  }

  if(click && up && down) {
    for(int i=4; i !=0; i--) {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_6x12_tr);
      u8g2.drawStr(0, 7, "Restart after: ");
      u8g2.setCursor(90, 7);  
      u8g2.print(i);  
      u8g2.sendBuffer();
      delay(1000);
    }

    esp_restart();  
  }

  u8g2.sendBuffer();
}