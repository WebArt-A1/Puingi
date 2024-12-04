#ifndef WIFI_h
#define WIFI_h

#include <Arduino.h>

class WIFI {
   public:
    WIFI();
    void init();
  private:
    int _init;  
};

#endif
