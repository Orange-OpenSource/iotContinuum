/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file GPIOInput.ino
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

#include <Arduino.h>
#include <PCA9534.h>

PCA9534 pca9534;

/* This example allows you to control GPIOs 4 and 13 which are managed by the GPIO expander PCA9534 */

void setup()
{  
  while(!Serial){
  }
  Serial.begin(115200);
  delay(2000);
  Serial.println("Input test application");

  pca9534.begin();
  if(!pca9534.exists()) {
      Serial.println("PCA9534 GPIO expander not found");
      while(true);
  }
  Serial.println("PCA9534 GPIO expander found");

  /* GPIO 4 is configured in input mode */
  pca9534.pinMode(IO4, INPUT); 
  /* GPIO 4 is configured in input polarity inversion mode */
  pca9534.pinMode(IO13, INPUT_POLARITY_INVERSION);
}

void loop()
{  
  uint8_t stateIO4 = pca9534.digitalRead(IO4);
  uint8_t stateIO13 = pca9534.digitalRead(IO13);
  
  if(stateIO13 == HIGH) {
    Serial.println("IO13 is HIGH");
  } 
  else {
    Serial.println("IO13 is LOW");    
  }

  if(stateIO4 == HIGH) {
    Serial.println("IO4 is HIGH");
  } 
  else {
    Serial.println("IO4 is LOW");    
  }
  
  delay(1000);
}
