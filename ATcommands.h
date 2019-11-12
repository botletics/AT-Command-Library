#ifndef ATcommands_h
#define ATcommands_h

#include "Arduino.h"

#define default_pulse_ms 100
#define default_timeout_ms 1000


class ATcommands {
  public:
    ATcommands(int8_t rst, bool newline = false);
    void begin(Stream &port);
    void reset(uint8_t pulse, uint16_t duration = default_pulse_ms);
    bool sendBlindCommand(char *command);
    bool sendCommand(char *command, uint16_t timeout = default_timeout_ms);
    bool sendCommand(char *command, char *reply, uint16_t timeout = default_timeout_ms);
  
  private:
    int8_t _rst;
    bool newline = false;
    char replybuffer[255];
    unsigned long timer;
    Stream *mySerial;
};

#endif
