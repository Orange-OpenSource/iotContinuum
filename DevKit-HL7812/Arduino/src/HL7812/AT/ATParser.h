/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file ATParser.h
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

#include "Arduino.h"
#include "ATLine.h"

class ATParser {
public:	
	/**
	 * Constructor
	 * Creates an ATParser object to manage an AT frame.
	 */
	ATParser();		

	/**
	 * Destructor
	 * Destroys the ATParser object.
	 */
	virtual ~ATParser(void);

	/**
	 * Initializes the device.
	 * This method must be called before using any other methods.
	 * 
	 * @param {String} frame - Corresponds to the ASCII content of an AT command to parse.
	 */
	void begin(String frame);

	/** 
	 * Gets the number of lines in the AT frame. The carriage return is not counted.
	 * 
	 * @returns {int} Returns the line number.
	 */
	int getCount();

	/** 
	 * Gets the frame row object defined by its index.
	 * 
	 * @param {int} index - Corresponds to the ASCII content of an AT command to parse.
	 * 
	 * @returns {ATLine} Returns the line pointer object. Null if index is greater than the count of lines.
	 */
	ATLine* getLine(int index);

	/** 
	 * Gets the frame row object defined by its AT name.
	 * 
	 * @param {String} key - Corresponds to the AT key name (e.g.: +CEREG, +CGCONTRDP, +CESQ ...) of the line.
	 * 
	 * @returns {ATLine} Returns the line pointer object. Null if key does not exist.
	 */
	ATLine* getLineByKey(String key);

	/** 
	 * Clears the AT frame. The parser is reset.
	 * 
	 */
	void flush();

	/** 
	 * Gets the ASCII content of the AT Frame.
	 * 
	 * @returns {String} Returns the character string of the AT frame in a String object.
	 */
	String toString();

	/** 
	 * Checks if the AT frame responded OK.
	 * 
	 * @returns {bool} Returns true if OK, otherwise false.
	 */
	bool isOk();

	/** 
	 * Checks if the AT frame did not respond with ERROR.
	 * 
	 * @returns {bool} Returns true if successful, otherwise false.
	 */
	bool isSuccess();
protected:
	String mFrame;
	int mCurrentPos;		
	std::vector<ATLine*> mVectorLine;

	String extractLine();

};
