#include "Arduino.h"
#include "Sonos.h"

const unsigned short int __SONOS_PORT = 1400;

PROGMEM const prog_char __AVTRANSPORT_POST[] = "POST /MediaRenderer/AVTransport/Control HTTP/1.1";
PROGMEM const prog_char __CONNECTION_CLOSE[] = "Connection: close";
PROGMEM const prog_char __CONTENT_TYPE[] = "Content-Type: text/xml; charset=\"utf-8\"";
PROGMEM const prog_char __HOST[] = "Host: ";
PROGMEM const prog_char __CONTENT_LENGTH[] = "Content-Length: ";

PROGMEM const prog_char __SOAP_BODY_OPEN[] = "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body>";
PROGMEM const prog_char __SOAP_BODY_CLOSE[] = "</s:Body></s:Envelope>";


Sonos::Sonos(IPAddress ip) {
  _ip = ip;
}

void Sonos::pause() {
  _client.connect(_ip, __SONOS_PORT);
  pauseHttpMessage();
  debugResponse();
  _client.stop();
}

void Sonos::play() {
  _client.connect(_ip, __SONOS_PORT);
  playHttpMessage();
  debugResponse();
  _client.stop();
}

void Sonos::playStream(char *streamUrl) {
  _client.connect(_ip, 1400);
  playURIHttpMessage(streamUrl);
  debugResponse();
  _client.stop();
  
  _client.connect(_ip, __SONOS_PORT);
  playHttpMessage();
  debugResponse();
  _client.stop();
}


void Sonos::clientPWrite(const prog_char *data) {
  while (char c = pgm_read_byte(data++)) {
    Serial.write(c);
    _client.write(c);
  }
}

void Sonos::clientPWriteLn(const prog_char *data) {
  clientPWrite(data);
  _client.println();
  Serial.println();
}

void Sonos::clientWrite(const char *data) {
  Serial.print(data);
  _client.print(data);
}

void Sonos::clientWriteLn(const char *data) {
  clientWrite(data);
  Serial.println();
  _client.println();
}

void Sonos::clientWriteLn() {
  Serial.println();
  _client.println();
}

void Sonos::clientWriteLn(IPAddress ip) {
  char _buffer[25];
  sprintf(_buffer, "%d.%d.%d.%d:%d", ip[0], ip[1], ip[2], ip[3], __SONOS_PORT);
  clientWriteLn(_buffer);
}

void Sonos::clientWriteLn(long number) {
  char _buffer[25];
  sprintf(_buffer, "%d", number);
  clientWriteLn(_buffer);
}
  
void Sonos::debugResponse() {
  unsigned long _timeout = millis() + 1000;
  while ((!_client.available ()) && (millis () < _timeout));
  
  while(_client.available()) {
    char c = _client.read();
    Serial.print(c);
  }
  Serial.println();
  Serial.println();
}


void Sonos::pauseHttpMessage() {
  const char *_payload = PSTR("<u:Pause xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID></u:Pause>");

  clientPWriteLn(__AVTRANSPORT_POST);
  clientPWriteLn(__CONNECTION_CLOSE);
  clientPWrite(__HOST);
  clientWriteLn(_ip);
  clientPWrite(__CONTENT_LENGTH);
  clientWriteLn(strlen_P(__SOAP_BODY_OPEN) + strlen_P(_payload) + strlen_P(__SOAP_BODY_CLOSE));
  clientPWriteLn(__CONTENT_TYPE);
  clientPWriteLn(PSTR("Soapaction: \"urn:schemas-upnp-org:service:AVTransport:1#Pause\""));
  clientWriteLn();
  clientPWrite(__SOAP_BODY_OPEN);
  clientPWrite(_payload);
  clientPWriteLn(__SOAP_BODY_CLOSE);
}

void Sonos::playHttpMessage() {
  const char *_payload = PSTR("<u:Play xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID><Speed>1</Speed></u:Play>");

  clientPWriteLn(__AVTRANSPORT_POST);
  clientPWriteLn(__CONNECTION_CLOSE);
  clientPWrite(__HOST);
  clientWriteLn(_ip);
  clientPWrite(__CONTENT_LENGTH);
  clientWriteLn(strlen_P(__SOAP_BODY_OPEN) + strlen_P(_payload) + strlen_P(__SOAP_BODY_CLOSE));
  clientPWriteLn(__CONTENT_TYPE);
  clientPWriteLn(PSTR("Soapaction: \"urn:schemas-upnp-org:service:AVTransport:1#Play\""));
  clientWriteLn();
  clientPWrite(__SOAP_BODY_OPEN);
  clientPWrite(_payload);
  clientPWriteLn(__SOAP_BODY_CLOSE);
}

void Sonos::playURIHttpMessage(char *uri) {
  const char *_payloadStart = PSTR("<u:SetAVTransportURI xmlns:u=\"urn:schemas-upnp-org:service:AVTransport:1\"><InstanceID>0</InstanceID><CurrentURI>");
  const char *_payloadEnd = PSTR("</CurrentURI><CurrentURIMetaData></CurrentURIMetaData></u:SetAVTransportURI>");
  
  clientPWriteLn(__AVTRANSPORT_POST);
  clientPWriteLn(__CONNECTION_CLOSE);
  clientPWrite(__HOST);
  clientWriteLn(_ip);
  clientPWrite(__CONTENT_LENGTH);
  clientWriteLn(strlen_P(__SOAP_BODY_OPEN) + strlen_P(_payloadStart) + strlen(uri) + strlen_P(_payloadEnd) + strlen_P(__SOAP_BODY_CLOSE));
  clientPWriteLn(__CONTENT_TYPE);
  clientPWriteLn(PSTR("Soapaction: \"urn:schemas-upnp-org:service:AVTransport:1#SetAVTransportURI\""));
  clientWriteLn();
  clientPWrite(__SOAP_BODY_OPEN);
  clientPWrite(_payloadStart);
  clientWrite(uri);
  clientPWrite(_payloadEnd);
  clientPWriteLn(__SOAP_BODY_CLOSE);
  
}
