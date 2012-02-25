#include "Arduino.h"
#include "Button.h"

Button::Button(byte pin) {
  _shortClick = 35;
  _longClick = 400;
  
  _pin = pin;
  pinMode(_pin, INPUT);
  
  _lastEventTime = 0;
  _lastEventType = Unknown;
}

void Button::turnOnPullUp() {
  digitalWrite(_pin, HIGH);
}

void Button::turnOffPullUp() {
  digitalWrite(_pin, LOW);
}

Button::Event Button::getEvent() {
  MomentaryState _state = getState();
  unsigned long _currentTime = millis();
  
  if (_lastEventType == Unknown || _lastEventType == Off) {
    if (_state == Up) {
      _lastEventTime = _currentTime;
      _lastEventType = Off;
      return None;
    }
    else {
      _lastEventTime = _currentTime;
      _lastEventType = SingleClickOn;
      return None;
    } 
  }
  else if (_lastEventType == SingleClickOn) {
    if (_state == Down) { // we're still clicking
      return None;
    } 
    else { // button has been released
      if (_currentTime > _lastEventTime + _longClick) {
        _lastEventTime = _currentTime;
        _lastEventType = Off;
        return LongClick;
      }
      else if (_currentTime > _lastEventTime + _shortClick) {
        _lastEventTime = _currentTime;
        _lastEventType = Off;
        return SingleClick;
      }
      else {
        _lastEventTime = _currentTime;
        _lastEventType = Off;
        return None;
      }
    }
  }

}

Button::MomentaryState Button::getState() {
  byte _state = digitalRead(_pin);
  if (_state == LOW)
    return Down;
  else
    return Up;
}
