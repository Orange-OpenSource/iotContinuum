/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file RGBLed.ino
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
#include <PCA9534.h>

PCA9534 pca9534;

/* This code example shows how to control the RGB LED which is managed by the PCA9534 GPIO expander */

void setup()
{  
  while(!Serial){
  }
  Serial.begin(115200);
  delay(2000);
  Serial.println("RGB test application");

  pca9534.begin();
  if(!pca9534.exists()) {
      Serial.println("PCA9534 GPIO expander not found");
      while(true);
  }
  Serial.println("PCA9534 GPIO expander found");

  pca9534.digitalWrite(RED_LED, HIGH);
  pca9534.digitalWrite(GREEN_LED, HIGH);
  pca9534.digitalWrite(BLUE_LED, HIGH); 
  
  pca9534.pinMode(RED_LED, OUTPUT);
  pca9534.pinMode(GREEN_LED, OUTPUT);
  pca9534.pinMode(BLUE_LED, OUTPUT);
}

void loop()
{
  pca9534.digitalWrite(BLUE_LED, HIGH);
  pca9534.digitalWrite(RED_LED, LOW);
  delay(500);
  pca9534.digitalWrite(RED_LED, HIGH);
  pca9534.digitalWrite(GREEN_LED, LOW);
  delay(500);
  pca9534.digitalWrite(GREEN_LED, HIGH);
  pca9534.digitalWrite(BLUE_LED, LOW);
  delay(500); 
}
