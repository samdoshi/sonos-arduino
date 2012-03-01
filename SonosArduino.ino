#include <SPI.h>
#include <Ethernet.h>

#include "Button.h"
#include "Sonos.h"
#include "MemoryFree.h"

// Single click streams
char *singleClickStreams[] = {
  "http://www.bbc.co.uk/radio/listen/live/r4.asx", 
  "http://bbc.co.uk/radio/listen/live/r5l.asx", 
  "http://www.bbc.co.uk/worldservice/meta/tx/nb/live/eneuk.asx", 
  "http://www.bbc.co.uk/radio/listen/live/r4.asx"
};

// Long click streams
char *longClickStreams[] = {
  "http://www.bbc.co.uk/radio/listen/live/r4x.asx", 
  "http://bbc.co.uk/radio/listen/live/r5lsp.asx", 
  "http://www.bbc.co.uk/radio/listen/live/r4.asx", 
  "http://www.bbc.co.uk/radio/listen/live/r4.asx" 
};

// Your Arduino MAC address
byte macAddress[] = { 0x90, 0xA2, 0xDA, 0x00, 0x69, 0x1C };

// The IP address of your Sonos box
const IPAddress sonosIP = IPAddress(192, 168, 0, 216);

// Pin assignments
const unsigned int noOfButtons = 4;
const byte buttonPins[] = { 2, 3, 5, 6 };
const byte stopPin = 7;
byte greenLedPin = 8;
byte redLedPin = 9;

Sonos *sonos;
Button *buttons[noOfButtons];
Button *stopButton;

void redLedOn();
void redLedOff();
void greenLedOn();
void greenLedOff();

void setup() {
  Serial.begin(9600);
  Serial.println("setup()");
  debugMemory();
  
  // Setup LEDs
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  
  redLedOn();
  
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
    while(1) {
       redLedOn();
       delay(500);
       redLedOff();
       delay(500);
    }
  }
  Serial.println(Ethernet.localIP());
  
  // Initalise Sonos
  sonos = new Sonos(sonosIP);
  debugMemory();
  
  redLedOff();
}


void loop() {
  Button::Event _stopEvent = stopButton->getEvent();
  if (_stopEvent != Button::None) {
    redLedOn();
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
    redLedOff();
    greenLedOn();
    delay(500);
    greenLedOff();
  }
  
  for(int _b=0; _b<noOfButtons; _b++) {
    Button *_button = buttons[_b];
    Button::Event _event = _button->getEvent();
    if (_event != Button::None) {
      redLedOn();
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
      redLedOff();
      greenLedOn();
      delay(500);
      greenLedOff();
    }
  }
}

void redLedOn() {
  digitalWrite(redLedPin, HIGH);
}

void redLedOff() {
  digitalWrite(redLedPin, LOW);
}

void greenLedOn() {
  digitalWrite(greenLedPin, HIGH);
}

void greenLedOff() {
  digitalWrite(greenLedPin, LOW);
}
