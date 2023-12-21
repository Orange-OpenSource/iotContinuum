/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file HelloWorld.ino
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

/* This Hello World example allows you to control the RGB LED which is managed by the PCA9534 GPIO expander */

#include <Wire.h>
#include "PCA9534.h"

PCA9534 gpio;

void setup() { 
  Serial.begin(115200);
  gpio.begin();
  Wire.begin();
  gpio.pinMode(RED_LED, OUTPUT);
  gpio.digitalWrite(RED_LED, HIGH); // LED Off
  gpio.pinMode(GREEN_LED, OUTPUT);
  gpio.digitalWrite(GREEN_LED, HIGH); // LED Off
  gpio.pinMode(BLUE_LED, OUTPUT);
  gpio.digitalWrite(BLUE_LED, HIGH); // LED Off
  delay(2000);
  Serial.println("Hello world");
}

void loop() {
  // put your main code here, to run repeatedly:
  gpio.digitalWrite(RED_LED, LOW); // LED On
  delay(500);
  gpio.digitalWrite(RED_LED, HIGH); // LED Off
  delay(500);
}
