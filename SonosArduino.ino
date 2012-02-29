#include <SPI.h>
#include <Ethernet.h>

#include "Button.h"
#include "Sonos.h"
#include "MemoryFree.h"

char *singleClickStreams[] = {
  "http://www.bbc.co.uk/radio/listen/live/r4.asx", 
  "http://bbc.co.uk/radio/listen/live/r5l.asx", 
  "http://www.bbc.co.uk/worldservice/meta/tx/nb/live/eneuk.asx", 
  "http://twit.am/listen"
};

char *longClickStreams[] = {
  "http://www.bbc.co.uk/radio/listen/live/r4x.asx", 
  "http://bbc.co.uk/radio/listen/live/r5lsp.asx", 
  "http://www.bbc.co.uk/radio/listen/live/r4x.asx", 
  "http://twit.am/listen.m3u" 
};

byte macAddress[] = { 0x90, 0xA2, 0xDA, 0x00, 0x69, 0x1C };
const IPAddress sonosIP = IPAddress(192, 168, 0, 216);
Sonos *sonos;

const unsigned int noOfButtons = 4;
const byte buttonPins[] = { 2, 3, 5, 6 };
const byte stopPin = 7;
Button *buttons[noOfButtons];
Button *stopButton;

void setup() {
  Serial.begin(9600);
  debugMemory();
  Serial.println("setup()");
  
  // Initalise buttons
  for(int _b=0; _b<noOfButtons; _b++) {
    Button *_button = new Button(buttonPins[_b]); 
    _button->turnOnPullUp();
    buttons[_b] = _button;
  }
  stopButton = new Button(stopPin);
  stopButton->turnOnPullUp();
  
  // Initalise ethernet
  if (Ethernet.begin(macAddress) == 0) {
    // do failure code
  }
  Serial.println(Ethernet.localIP());
  
  // Initalise Sonos
  sonos = new Sonos(sonosIP);
  debugMemory();
}


void loop() {
  Button::Event _stopEvent = stopButton->getEvent();
  if (_stopEvent != Button::None) {
    Serial.print(millis());
    Serial.print(" ");
    switch(_stopEvent) {
      case Button::SingleClick:
        Serial.println("Single click");
        sonos->pause();
        break;
      case Button::LongClick:
        Serial.println("Long click");
        sonos->play();
        break;
      default:
        Serial.println("Unknown");
        break;
    }
    Serial.flush();
    debugMemory();
  }
  
  for(int _b=0; _b<noOfButtons; _b++) {
    Button *_button = buttons[_b];
    Button::Event _event = _button->getEvent();
    if (_event != Button::None) {
      Serial.print(millis());
      Serial.print(" ");
      switch(_event) {
        case Button::SingleClick:
          Serial.println("Single click");
          sonos->playStream(singleClickStreams[_b]);
          break;
        case Button::LongClick:
          Serial.println("Long click");
          sonos->playStream(longClickStreams[_b]);
          break;
        default:
          Serial.println("Unknown");
          break;
      }
      Serial.flush();
      debugMemory();
    }
  }
}
