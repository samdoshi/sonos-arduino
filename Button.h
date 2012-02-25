#ifndef Buttons_h
#define Buttons_h

#include "Arduino.h"

class Button {
  public:
    enum Event { None, SingleClick, LongClick };
    Button(byte pin);
    void turnOnPullUp();
    void turnOffPullUp();
    Event getEvent();
    
  private:
    enum LastEventType { Unknown, Off, SingleClickOn };
    enum MomentaryState { Up, Down };
    byte _pin;
    unsigned int _shortClick;
    unsigned int _longClick;
    unsigned long _lastEventTime;
    LastEventType _lastEventType;
    
    MomentaryState getState();
    
};

#endif
