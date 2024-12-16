#ifndef disp_control_h
#define disp_control_h

#include <Arduino.h>

class disp_control {
   public:
    disp_control();
    void init();
  private:
    int _init;  
};

#endif