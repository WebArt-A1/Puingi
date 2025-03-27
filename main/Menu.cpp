#include "Menu.h"
#include "Setup.h"

String nowMenu = "Main Menu";
int nowIndex = 1;

int x = 0;
int y = 0;
int fileLineX = 0;
int fileLineY = 0;

bool upFlag = true;
bool clFlag = true;
bool dwFlag = true;

String nowDir = "/";
int itemsFile = 0;

File bitmapFile;
uint8_t sel[14];

String Menus[] = {
  "Main Menu",
  "Settings",
  "Files"
};

String Settings[] = {
  "Settings",
  "Wifi-C-C",
  "Back"
};

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

  bitmapFile = SD.open("/system32/bitmap/sel.bm");

  if (!bitmapFile) return;

  bitmapFile.read(sel, sizeof(sel));
  bitmapFile.close();
}

void Menu::main(int up, int click, int down) {

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tr);
  if(nowMenu == "Files") {
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

  u8g2.setFont(u8g2_font_7x14_tr);

  if(nowMenu == "Main Menu"){
    controlIndex(2);
    for(int i=1; i<=2; i++){
      x = 0;
      if(i == nowIndex) {
        x = 8;
        if(click && clFlag) {
          clFlag = false;
          nowIndex = 1;
          nowDir = "/";
          nowMenu = Menus[i];
        } else if(!click) {
          clFlag = true;
        }
      }
      u8g2.drawXBMP(0, nowIndex*16, 4, 14, sel);
      u8g2.drawStr(x, 14+i*16, Menus[i].c_str());
    }
  }                                                   // Main menu 
  if(nowMenu == "Settings"){
    controlIndex(1);
    for(int i=1; i<=2 ; i++){
      u8g2.setFont(u8g2_font_7x14_tr);
      x = 0;
      if(i == nowIndex) {
        x = 8;
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
      u8g2.drawXBMP(0, nowIndex*16, 4, 14, sel);
      u8g2.drawStr(x, 14+i*16, Settings[i].c_str());
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
        x = 8;
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
      u8g2.drawXBMP(0, nowIndex*16, 4, 14, sel);

      u8g2.drawStr(x, 14+itemsFile*16, name.c_str());
    }
    if(nowIndex == itemsFile+1) {
      u8g2.drawXBMP(0, nowIndex*16, 4, 14, sel);
      u8g2.drawStr(8, 30+itemsFile*16, "Back");
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
    if(!root.isDirectory()) {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_6x12_tr);

      int yPos = 6;
      String currentLine;


      while (true) {
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_6x12_tr);

        root.seek(0);
        int currentLine = 0;
        int yPos = 0;
        String lineBuffer;

        while (root.available() && currentLine < fileLineY) {
          if (root.read() == '\n') currentLine++;
        }

        while (root.available() && yPos < 128) {
          char c = root.read();
          
          if (c == '\n') {
            u8g2.drawStr(-fileLineX * 6, yPos + 12, lineBuffer.c_str());
            yPos += 12;
            lineBuffer = "";
            if (yPos >= 64) break;
          } 
          else if (c != '\r') {
            lineBuffer += c;
          }
        }

        if (digitalRead(BUTTON_UP_PIN) && upFlag) {
          delay(300);
          if(digitalRead(BUTTON_UP_PIN)){
            fileLineX -= 6;
          }
          fileLineX += 3;
          upFlag = false;
        } else if (!digitalRead(BUTTON_UP_PIN)) {
            upFlag = true;
        }

        if (digitalRead(BUTTON_DW_PIN) && dwFlag) {
          delay(300);
          if(digitalRead(BUTTON_DW_PIN)){
            fileLineY -= 6;
          }
          fileLineY += 3;
            dwFlag = false;
        } else if (!digitalRead(BUTTON_DW_PIN)) {
          dwFlag = true;
        }

        if (digitalRead(BUTTON_CL_PIN)) {
          nowDir = removeLastPathSegment(nowDir);
          break;
        }

        u8g2.sendBuffer();
        delay(50);
        Serial.println(fileLineX);
        Serial.println(fileLineY);
        Serial.println();
    }

      fileLineX = 0;
      fileLineY = 0;

    }
    if(nowDir != "/") {
      if(nowIndex == 1) {
        u8g2.drawXBMP(0, nowIndex*16, 4, 14, sel);
        u8g2.drawStr(8, 30, "..");
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
  }
  if (nowMenu == "Wifi-C-C") {
    File dir = SD.open("/system32/configs/wifi");
    
    if (!dir || !dir.isDirectory()) {
      u8g2.drawStr(0, 14, "Dir error!");
      u8g2.sendBuffer();
      return;
    }

    u8g2.setFont(u8g2_font_7x14_tr);
    int x = 0;
    int y = 1;

    File file;
    while ((file = dir.openNextFile())) {
      const char* filename = file.name();
      
      if (!file.isDirectory()) {
          u8g2.drawStr(x, 7+y*16, filename);
          y += 1;
      }
      file.close();
      u8g2.sendBuffer();
      delay(50);
    }
    dir.close();
  }


  if(click && up && down) {
    for(int i=3; i !=-1; i--) {
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