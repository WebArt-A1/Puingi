#ifndef display_h
#define display_h

#include <Arduino.h>

class display {
   public:
    display();
    void init();
    void menu(int move);
    void boot();
  private:
    int _init;  
};

#endif