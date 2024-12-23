#ifndef KEY13_H
#define KEY13_H

#include <Arduino.h>

class Key13 {
public:
  Key13();
  void begin();
  void read();
private:
  int _init;
};

#endif