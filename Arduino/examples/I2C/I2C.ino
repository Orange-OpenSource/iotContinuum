/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file I2C.ino
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
#include <Wire.h>

/* This code example performs a scan of all I2C devices */

void setup()
{  
  while(!Serial){
  }
  Serial.begin(115200);
  delay(2000);
  Serial.println("Start test I2C");
  Wire.begin();

  Serial.println("Scan started");
  for(int i = 0; i < 127; i++) {
    Wire.beginTransmission(i);
    uint8_t error = Wire.endTransmission();
    
    if (error == 0) {      
      switch(i) {
        case 0x38:
            Serial.println("");Serial.print("Found PCA9535 (address:"); Serial.print(i, HEX); Serial.println(")");
          break;

        case 0x6A:
            Serial.println("");Serial.print("Found BME280 (address:"); Serial.print(i, HEX); Serial.println(")");
          break;
          
        case 0x76:
            Serial.println("");Serial.print("Found LSM6DSOX (address:"); Serial.print(i, HEX); Serial.println(")");
          break;
          
        default:
          Serial.println("");Serial.print("Found unknown chipset (address:"); Serial.print(i, HEX); Serial.println(")");
          break;
      }
    }
    else {
      Serial.print(".");
    }    
    delay(50);
  }
  Serial.println(""); Serial.println("Scan finished");
}

void loop(){
}
