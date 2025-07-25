/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file HL7812Client.h
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

#include "HL7812Base.h"

#define TX_BUFFER_LENGTH			512
#define RX_BUFFER_LENGTH			512

class HL7812Client : public Client, public HL7812Base 
{
public:
	/**
	 * Constructor
	 * Creates HL7812Client object. It allows you to manage all the basic I/O functions of the HL7812.
	 */
	HL7812Client();

	/**
	 * Destructor
	 * Destroys HL7812Client object.	 
	 */
	virtual ~HL7812Client();

	/** 
	 * Initiates a TCP/IP connection
	 * 
	 * @param {IPAddress} ip - IPv4 address (format xxx.xxx.xxx.xxx)
	 * @param {uint16_t} port - Connection port.
	 * @returns {bool} Returns session number (between 1 and 6) otherwise -1 if failed.
	 */
	virtual int connect(IPAddress ip, uint16_t port);

	/** 
	 * Initiates a TCP/IP connection
	 * 
	 * @param {const char*} host - Server host name
	 * @param {uint16_t} port - Connection port.
	 * @returns {bool} Returns session number (between 1 and 6) otherwise -1 if failed.
	 */
	virtual int connect(const char* host, uint16_t port);

	/** 
	 * Write a character
	 * 
	 * @param {uint8_t} data - Character in ASCII format to send
	 * @returns {size_t} Returns the size sent otherwise 0 if failed.
	 */
	virtual size_t write(uint8_t data);

	/** 
	 * Write a binary frame
	 * 
	 * @param {const uint8_t} buf - Binary frame to send
	 * @param {const size_t} size - Size of the binary frame
	 * @returns {size_t} Returns the size sent otherwise 0 if failed.
	 */
	virtual size_t write(const uint8_t *buf, size_t size);

	/** 
	 * Check if the receiving data is available
	 * 
	 * @returns {int} Returns 1 if data received otherwise 0.
	 */
	virtual int available();

	/** 
	 * Read if a character is received
	 * 
	 * @returns {size_t} Returns the ASCII code otherwise -1 if character not received.
	 */
	virtual int read();

	/** 
	 * Read if a binary frame is received
	 * 
	 * @param {const uint8_t} buf - Buffer where binary frame is copied
	 * @param {const size_t} size - Copy buffer size
	 * @returns {int} Returns the size received otherwise 0 if failed.
	 */
	virtual int read(uint8_t *buf, size_t size);

	/** 
	 * Not available: Function not implemented
	 */	
	virtual int peek();

	/** 
	 * Flush all data received stored in FIFO
	 * 
	 * @returns {void} Returns void
	 */
	virtual void flush();

	/** 
	 * Stop the TCP/IP connection
	 * 
	 * @returns {void} Returns void
	 */
	virtual void stop();

	/** 
	 * Get the connection status
	 * 
	* @returns {void} Returns 1 if connected otherwise 0
	 */
	virtual uint8_t connected();

	/** 
	 * Operator bool
	 * 
	 * @returns {operator} 
 	*/
	virtual operator bool();

protected:
	int16_t mLenReadByte;
	int16_t mIndexReadByte;
	bool mAvailableCalled;
	int16_t mSession;

	uint8_t mTxBuffer[TX_BUFFER_LENGTH];
	uint8_t mRxBuffer[RX_BUFFER_LENGTH];

	int setSessionConfig(const char* host, uint16_t port);
	bool sessionExists(int16_t session);
	ATParser* geListSession();
	bool deleteSession(uint16_t session);
	bool deleteAllSession();
	int getSessionCount();

	int getReceiveLength();
	int getSocketState();
	int getTcpState(uint8_t type);
	String getClock(uint8_t type);

	int readReceiveFrame(uint8_t *buffer, size_t size);	
	void flushDataBuffer();
};