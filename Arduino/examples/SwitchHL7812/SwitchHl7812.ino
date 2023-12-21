/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file SwitchHl7812.ino
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
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION */

#include <Arduino.h>

/* This code example shows how to use of the devkit switch */
void setup()
{  
  while(!Serial){
  }
  Serial.begin(115200);
  delay(2000);
  Serial.println("Start Switch to HL7812 Application");

  pinMode(SWITCH_TO_HL7812, OUTPUT);
  pinMode(USER_BTN, INPUT);
}

void loop()
{
  Serial.println("Press User Button to switch to HL7812");

  uint32_t button = digitalRead(USER_BTN);
  while(button == LOW) {
      button = digitalRead(USER_BTN);
  }
    
  Serial.println("button is Pressed");
  Serial.println("Switch to HL7812. You can type AT commands");

  digitalWrite(SWITCH_TO_HL7812, HIGH);
  
  delay(1000);
}
