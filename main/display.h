#ifndef display_h
#define display_h

#include <Arduino.h>

class display {
   public:
    display();
    void init();
  private:
    int _init;  
};

#endif
