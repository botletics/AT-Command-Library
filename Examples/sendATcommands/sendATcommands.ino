/* This code is for blahhh
 *  
 */
 
#include "ATcommands.h"
#include <SoftwareSerial.h>

#define MCU_TX 10 // Remember MCU TX connects to module RX and vice versa
#define MCU_RX 9
#define RST 4 // MCU pin to control module reset

SoftwareSerial moduleSS = SoftwareSerial(MCU_TX, MCU_RX); // Module RX, TX
SoftwareSerial *moduleSerial = &moduleSS;

// Hardware serial is also possible!
// HardwareSerial *moduleSerial = &Serial1;

ATcommands module = ATcommands(RST);

//uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

void setup() {
  Serial.begin(115200);

  moduleSerial->begin(9600); // Verify your module's baud rate
  module.begin(*moduleSerial);

  module.reset(LOW, 10); // Reset module if needed. This example pulses the reset pin low for 10ms

  // Execute a series of AT commands and print module responses
  // The functions return a logic true/false to indicate if it was successful
  // Use an if statement to check for this, or ignore it and omit the if statement
  if (!sendCommand(F("AT"), ok_reply, 1000)) Serial.println("Command failed!");
//  sendCommand(F("AT"), ok_reply, 1000); // Ignore if statement and just send the command without checking if successful
}

void loop() {
  // Nothing here
}
