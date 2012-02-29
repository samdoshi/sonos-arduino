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
    void debugResponse(EthernetClient client);
    void pauseHttpMessage(EthernetClient client);
    void playHttpMessage(EthernetClient client);
    void playURIHttpMessage(EthernetClient client, char *uri);
};

#endif
