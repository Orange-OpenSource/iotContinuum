/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

#include "Wire.h"
#include "PCA9534.h"

#define PCA9534_INPUT_REG               0x00
#define PCA9534_OUTPUT_REG              0x01
#define PCA9534_POLARITY_INVERSION_REG  0x02
#define PCA9534_CONFIGURATION_REG       0x03

#define PCA9534_PIN_COUNT               8

#if defined(DEBUG_PCA9534)
#define DEBUG_PCA9534_PRINT(...)    Serial.print(__VA_ARGS__)
#define DEBUG_PCA9534_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
#define DEBUG_PCA9534_PRINT(...)    
#define DEBUG_PCA9534_PRINTLN(...)  
#endif

PCA9534::PCA9534(uint8_t address) : 
  mAddress(address),
  mPort(0b00000000),
  mState(0b00000000),
  mPolarityInversion(0b00000000)
{
}

void PCA9534::begin() {  
  Wire.begin();
}

bool PCA9534::exists() {
    Wire.beginTransmission(mAddress);
    uint8_t error = Wire.endTransmission();
    if (error == 0) {
      DEBUG_PCA9534_PRINTLN("PCA9534 found");
    }
    else {
      DEBUG_PCA9534_PRINTLN("PCA9534 not found");
    }

    return (error == 0);
}

void PCA9534::pinMode(uint8_t pin, uint8_t mode) {
  if(pin >= PCA9534_PIN_COUNT) {
    DEBUG_PCA9534_PRINTLN("Pin Greather");
    return;
  }

  if((mode != INPUT) && (mode != OUTPUT) && (mode != INPUT_POLARITY_INVERSION)) {
    DEBUG_PCA9534_PRINTLN("Incorrect pin mode");
    return;
  }
  
  switch (mode) {
    case INPUT:      
      mPort |= (1 << pin);
      mPolarityInversion &= ~(1 << pin);
      writeI2C(PCA9534_POLARITY_INVERSION_REG, mPolarityInversion);
      break;

    case OUTPUT:
      mPort &= ~(1 << pin);
      break;

    case INPUT_POLARITY_INVERSION:      
      mPort |= (1 << pin);      
      mPolarityInversion |= (1 << pin);
      writeI2C(PCA9534_POLARITY_INVERSION_REG, mPolarityInversion);
      break;
  }

  writeI2C(PCA9534_CONFIGURATION_REG, mPort);

  DEBUG_PCA9534_PRINT("Port: ");
  DEBUG_PCA9534_PRINTLN(mPort, BIN);
}

void PCA9534::digitalWrite(uint8_t pin, uint8_t value) {
  if(pin >= PCA9534_PIN_COUNT) return;
  
  if(value == LOW) {
    mState &= ~(1 << pin);
  } 
  else {
    mState |= (1 << pin);
  }  
  writeI2C(PCA9534_OUTPUT_REG, mState);
}

uint8_t PCA9534::digitalRead(uint8_t pin) {
  if(pin >= PCA9534_PIN_COUNT) return -1;

  writeI2C(PCA9534_INPUT_REG, mPort);  
  Wire.requestFrom((int)mAddress, (int)1);
  return (Wire.read() & (1 << pin)) ? HIGH : LOW;
}

void PCA9534::writeI2C(int i2cRegister, int value) {
  Wire.beginTransmission(mAddress);
  Wire.write(i2cRegister);
  Wire.write(value);
  Wire.endTransmission();
}
