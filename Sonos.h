#ifndef Sonos_h
#define Sonos_h

#include "Arduino.h"
#include <Ethernet.h>

class Sonos {
  public:
    Sonos(IPAddress ip);
    void pause();
    void play();
    void playStream(char *streamUrl);
    
  private:
    IPAddress _ip;
    EthernetClient _client;
    void clientPWrite(const prog_char *data);
    void clientPWriteLn(const prog_char *data);
    void clientWrite(const char *data);
    void clientWriteLn(const char *data);
    void clientWriteLn();
    void clientWriteLn(IPAddress ip);
    void clientWriteLn(long number);
    void debugResponse();
    void pauseHttpMessage();
    void playHttpMessage();
    void playURIHttpMessage(char *uri);
};

#endif
