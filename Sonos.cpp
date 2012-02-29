#include "Arduino.h"
#include "Sonos.h"


Sonos::Sonos(IPAddress ip) {
  _ip = ip;
}

void Sonos::pause() {
  _client.connect(_ip, 1400);
  pauseHttpMessage(_client);
  debugResponse(_client);
  _client.stop();
}

void Sonos::play() {
  _client.connect(_ip, 1400);
  playHttpMessage(_client);
  debugResponse(_client);
  _client.stop();
}

void Sonos::playStream(char *streamUrl) {
  _client.connect(_ip, 1400);
  playURIHttpMessage(_client, streamUrl);
  debugResponse(_client);
  _client.stop();
  
  _client.connect(_ip, 1400);
  playHttpMessage(_client);
  debugResponse(_client);
  _client.stop();
}



void Sonos::debugResponse(EthernetClient client) {
  unsigned long _timeout = millis() + 1000;
  while ((!client.available ()) && (millis () < _timeout));
  
  while(client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.println();
  Serial.println();
}

void Sonos::pauseHttpMessage(EthernetClient client) {
  char *_payload = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:Pause xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID></u:Pause></s:Body></s:Envelope>\n";
  
  client.println("POST /MediaRenderer/AVTransport/Control HTTP/1.1");
  client.println("Connection: close");
  client.print("Host: ");
  client.print(_ip[0]);
  client.print(".");
  client.print(_ip[1]);
  client.print(".");
  client.print(_ip[2]);
  client.print(".");
  client.print(_ip[3]);
  client.println(":1400");
  client.print("Content-Length: ");
  client.println(strlen(_payload));
  client.println("Content-Type: text/xml; charset=\"utf-8\"");
  client.println("Soapaction: \"urn:schemas-upnp-org:service:AVTransport:1#Pause\"");
  client.println();
  client.println(_payload);
}

void Sonos::playHttpMessage(EthernetClient client) {
  char *_payload = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:Play xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID><Speed>1</Speed></u:Play></s:Body></s:Envelope>\n";
  
  client.println("POST /MediaRenderer/AVTransport/Control HTTP/1.1");
  client.println("Connection: close");
  client.print("Host: ");
  client.print(_ip[0]);
  client.print(".");
  client.print(_ip[1]);
  client.print(".");
  client.print(_ip[2]);
  client.print(".");
  client.print(_ip[3]);
  client.println(":1400");
  client.print("Content-Length: ");
  client.println(strlen(_payload));
  client.println("Content-Type: text/xml; charset=\"utf-8\"");
  client.println("Soapaction: \"urn:schemas-upnp-org:service:AVTransport:1#Play\"");
  client.println();
  client.println(_payload);
}

void Sonos::playURIHttpMessage(EthernetClient client, char *uri) {
  char *_payload1 = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetAVTransportURI xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID><CurrentURI>";
  char *_payload2 = uri;
  char *_payload3 = "</CurrentURI><CurrentURIMetaData></CurrentURIMetaData></u:SetAVTransportURI></s:Body></s:Envelope>\n";
  
  client.println("POST /MediaRenderer/AVTransport/Control HTTP/1.1");
  client.println("Connection: close");
  client.print("Host: ");
  client.print(_ip[0]);
  client.print(".");
  client.print(_ip[1]);
  client.print(".");
  client.print(_ip[2]);
  client.print(".");
  client.print(_ip[3]);
  client.println(":1400");
  client.print("Content-Length: ");
  client.println(strlen(_payload1) + strlen(_payload2) + strlen(_payload3));
  client.println("Content-Type: text/xml; charset=\"utf-8\"");
  client.println("Soapaction: \"urn:schemas-upnp-org:service:AVTransport:1#SetAVTransportURI\"");
  client.println();
  client.print(_payload1);
  client.print(_payload2);
  client.print(_payload3);
  client.println();
  
}
