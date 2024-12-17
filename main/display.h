#ifndef display_h
#define display_h

#include <Arduino.h>

class display {
   public:
    display();
    void init();
    void menu(int move);
  private:
    int _init;  
};

#endif