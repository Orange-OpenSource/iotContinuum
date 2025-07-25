/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file PCA9534.h
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

#pragma once

#include <arduino.h>

#define PCA9534_ADDRESS           0x38
#define INPUT_POLARITY_INVERSION  0x04

#define DEBUG_PCA9534             1

class PCA9534 {
public:
	/**
	 * Constructor
	 * Creates a PCA9534 object to manage a PCA9534 GPIO expander chipset.
	 * @param {uint8_t} address - Sets the slave address of the PCA9534, the default value is 0x38.
	 */
	PCA9534(uint8_t address = PCA9534_ADDRESS);

	/**
	 * Initializes the device.
	 * This method must be called before using any other methods.
	 *
	 */
	void begin();

	/** 
	 * Checks if the PCA9534 chipset is detected.
	 * 
	 * @returns {bool} Returns true if the PCA9534 is detected, otherwise false.
	 */
	bool exists();

	/**
	 * Configures the mode of the specified pin: input, output, or inverted input.
	 *
	 * @param {uint8_t} pin - The pin number to be configured.
	 * @param {uint8_t} mode - The mode of the specified pin: INPUT, OUTPUT, or INPUT_INVERTED.
	 */
	void pinMode(uint8_t pin, uint8_t mode);

	/**
	 * Writes a HIGH or a LOW value to a digital pin.
	 *
	 * @param {uint8_t} pin - The pin number to be written to.
	 * @param {uint8_t} value - The value to be written to the pin: HIGH or LOW.
	 */
	void digitalWrite(uint8_t pin, uint8_t value);

	/**
	 * Reads the value from a specified digital pin: HIGH or LOW.
	 *
	 * @param {uint8_t} pin - The pin number to be read.
	 * @returns {uint8_t} The status of the pin: HIGH or LOW.
	 */
	uint8_t digitalRead(uint8_t pin);

protected:
  uint8_t mAddress;
  uint8_t mPort;               
  uint8_t mState;   
  uint8_t mPolarityInversion;

  void writeI2C(int i2cRegister, int value);
private:
  
};
