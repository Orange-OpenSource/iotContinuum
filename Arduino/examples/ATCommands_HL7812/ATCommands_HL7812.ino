/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file ATCommands_HL7812.ino
 Copyright (c) 2023 ORANGE

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include <SoftwareSerial.h>


/* This example allows you to send AT commands from the host machine connected via USB to the HL7812 */

/* RX/TX Serial Pins to the HL7812 */
const int rxPin = PA10;
const int txPin = PA9;

SoftwareSerial hl7812Serial(rxPin, txPin);

void setup() {
  Serial.begin(115200);
  hl7812Serial.begin(115200);
  delay(2000);
}

/* Get AT commands from the arduino's serial monitor and send them to the HL7812 (must be set in 115200 bauds) */
void loop() {
  Serial.println("Enter an AT command");

  /* wait for the user to input the command and read the command */
  while (Serial.available() == 0) {
  }
  String input = Serial.readString();

  /* echoing the AT command received from the user to the Serial Monitor */
  Serial.print("AT command: ");
  Serial.println(input);
  
  /* convert the string into a char[] and send it to the HL7812 */
  char c[64];
  input.toCharArray(c, sizeof(c));

  sendATCommand(c);
}

/* Send an AT command to the HL7812 and print the response into arduino's serial monitor */
void sendATCommand(const char* command) {
  char buffer[1024];              /* buffer containing the response from the HL -- size can be increased if needed */
  int i=0;                        /* iterator on the buffer */
  unsigned long time = millis();  /* store current time for later */

  /* send the command to the HL7812 */
  hl7812Serial.println(command);

  /* read the answer from the HL "1 byte at a time, when available" until we've spent enough time waiting or we run out of buffer */
  while((millis() - time < 1000) && i < sizeof(buffer)) {
    if (hl7812Serial.available()) {
      buffer[i] = hl7812Serial.read();
      i++;
    }
  }

  /* write our buffer to the serial monitor */
  Serial.write(buffer, i);

  /* check if we overflowed and print an error to the serial monitor */
  if (hl7812Serial.overflow() || i >= sizeof(buffer)) {
    Serial.print("\n** HL7812 serial overflow (");
    Serial.print(i);
    Serial.println(") **");
  }
}



