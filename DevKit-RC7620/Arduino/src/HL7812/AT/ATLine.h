/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file ATLine.h
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

#include "ATValue.h"

class ATLine {
private:
	String mLine;
	int mCurrentPos;
	std::vector<ATValue*> mVectorValue;

	void flush();

	String extractValue();
public:	
	/**
 	 * Constructor
 	 * Creates an ATLine object to manage an AT line. This class is used by ATParser.
 	 */
	ATLine(String line);	

	/**
	 * Destructor
 	 * Destroys the ATLine object.	 
 	 */
	~ATLine(void);

	/** 
	 * Gets the number of comma-separated items in the AT line.
	 * 
	 * @returns {int} Returns the item count.
	 */
	int getCount();

	/** 
	 * Checks if the line is labeled ERROR.
	 * 
	 * @returns {bool} Returns true if labeled ERROR, otherwise false.
	 */
	bool isSuccess();

	/** 
	 * Checks if the line is labeled OK.	
 	 * 
	 * @returns {bool} Returns true if labeled OK, otherwise false.
	 */
	bool isOk();

	/** 
	 * Checks if the line is a data frame.
	 * 
	 * @returns {bool} Returns true if it is a data frame, otherwise false.
	 */	
	bool isData();
  
	/** 
	 * Gets the ASCII content of the AT line.
	 * 
 	 * @returns {String} Returns the character string of the AT line in a String object.
 	 */
	String toString();

	/** 
	 * Checks if the line is an AT command.
	 * 
	 * @returns {bool} Returns true if it is an AT command, otherwise false.
	 */	
	bool isCommand();

	/** 
	 * Gets the ASCII content of the AT line.
	 * 
	 * @returns {String} Returns the character string of the AT line in a String object. Returns empty if not a command line.
	 */
	String getCommand();

	/** 
	 * Gets the value of the line object defined by its index.
	 * 
	 * @param {int} index - Corresponds to the ASCII content of an AT line.
	 * 
	 * @returns {ATValue} Returns the ATValue pointer object. Null if index is greater than the count of values.
	 */
	ATValue* getValue(int index);

	/** 
	 * Gets the ASCII content of the AT line.
	 * 
	 * @returns {String} Returns the character string of the AT line in a String object.
	 */
	String getData();

};
