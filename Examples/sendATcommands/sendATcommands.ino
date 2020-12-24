/* This code is an example of how to use the AT command library to
 *  send AT commands (or ASCII commands) to a module via UART (TX/RX)
 *  using software or hardware serial. The commands can be set up to
 *  check for a specified reply from the module as well as a timeout.
 *  
 *  Author: Timothy Woo (botletics.com)
 *  Last Modified: 10/20/2017
 */
 
#include "ATcommands.h"
#include <SoftwareSerial.h>

#define MCU_RX 9 // Remember MCU RX connects to module TX and vice versa
#define MCU_TX 10
#define RST 4 // MCU pin to control module reset

SoftwareSerial moduleSS = SoftwareSerial(MCU_RX, MCU_TX); // MCU RX, TX
SoftwareSerial *moduleSerial = &moduleSS;

// Hardware serial is also possible!
// HardwareSerial *moduleSerial = &Serial1;

ATcommands module = ATcommands(RST, false); // Use "false" if you don't want AT commands with newline, "true" otherwise

void setup() {
  Serial.begin(115200);

  moduleSerial->begin(9600); // Verify your module's baud rate
  module.begin(*moduleSerial);

  // Reset module if needed. This example pulses the reset pin low for 10ms.
  // If left out, the pulse duration is 100ms by default.
  module.reset(LOW, 10); // module.reset(HIGH/LOW, pulseDuration)

  // Blindly send command without checking for reply or timeout
  module.sendBlindCommand("AT");
  delay(1000); // May want to include a small delay depending on what module you're using

  // Send command with timeout but without checking for specific response. Will return false if no reply
  if (!module.sendCommand("AT", 1000)) Serial.println(F("Command failed!"));
  delay(1000);

  // If you leave out the timeout value it defaults to 1000ms, which is usually good enough for most commands
  if (!module.sendCommand("AT")) Serial.println(F("Command failed!"));
  delay(1000);

  // Send command with timeout and check if module's response contains the desired (check the start)
  if (!module.sendCommand("AT", "OK", 1000)) Serial.println(F("Command failed!"));

  // Send command with timeout and check if module's response start with the desired
  if (!module.sendCommand("AT", "OK", true, 1000)) Serial.println(F("Command failed!"));

  // Send command with timeout and check if module's response contains the desired
  if (!module.sendCommand("AT", "OK", false, 1000)) Serial.println(F("Command failed!"));
}

void loop() {
  // Nothing here
}
