
#include "Button.h"

const unsigned int noOfButtons = 4;
const byte buttonPins[] = {2,3,5,6};
const byte stopPin = 7;
Button *buttons[noOfButtons];
Button *stopButton;

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
  for(int _b=0; _b<noOfButtons; _b++) {
    Button *_button = new Button(buttonPins[_b]); 
    _button->turnOnPullUp();
    buttons[_b] = _button;
  }
  stopButton = new Button(stopPin);
  stopButton->turnOnPullUp();
}


void loop() {
  for(int _b=0; _b<noOfButtons; _b++) {
    Button *_button = buttons[_b];
    Button::Event _event = _button->getEvent();
    if (_event != Button::None) {
      Serial.print(millis());
      Serial.print(" ");
      switch(_event) {
        case Button::SingleClick:
          Serial.println("Single click");
          break;
        case Button::LongClick:
          Serial.println("Long click");
          break;
        default:
          Serial.println("Unknown");
          break;
      }
      Serial.flush();
    }
  }
}
