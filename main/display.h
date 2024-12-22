#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

class Display {
public:
  Display();
  void begin();
  void menu(int move);
private:
  int _init;
};

#endif