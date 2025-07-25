/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file HL7812Base.h
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

#include <Arduino.h>
#include <Client.h>
#include "AT/ATParser.h"

#define DEBUG
#define DEBUG_FRAME

#if defined(DEBUG)
#define DEBUG_PRINT(...)    Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)    
#define DEBUG_PRINTLN(...)  
#endif

#if defined(DEBUG_FRAME)
#define DEBUG_FRAME_PRINT(...)    Serial.print(__VA_ARGS__)
#define DEBUG_FRAME_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
#define DEBUG_FRAME_PRINT(...)    
#define DEBUG_FRAME_PRINTLN(...)  
#endif

#define HL7812_DEFAULT_TIMEOUT_MS 	2000
#define ORANGE_DEFAULT_APN          "orange.m2m.spec"

typedef enum _mode {
	LTE, 
	GSM,
	GNSS,
} eMode;

typedef struct _signalInformation {
	String rssi;
	String ber;
	String rscp;
	String ecno;
	String rsrq;	
	String rsrp;
} sSignalInformation;

typedef void (*HL7812BaseCallback)(void* object, uint16_t type , uint32_t value);

class HL7812Base
{
public:
	/**
	 * Constructor
	 * Creates HL7812Base object. It allows you to manage all the basic functions of the HL7812.
	 */
	HL7812Base();

	/**
	 * Destructor
	 * Destroys HL7812Base object.	 
	 */
	virtual ~HL7812Base();

	/** 
	 * Initialize HL7812 module
	 * 
	 * @param {eMode} mode - Sets the antenna mode: LTE, GSM or GNSS
	 * @param {String} apn - Sets the APN name.
	 * @param {bool} isReset - If true, the HL7812 performs a reset.
	 * @param {uint32_t} timeout - Defines the maximum duration at which the network hook must be done.
	 * @returns {bool} Returns true if initialization is successful, otherwise false.
	 */
	bool initialize(eMode mode, String apn, bool isReset, uint32_t timeout);
	/*General AT Commands*/

	/** 
	 * Set the echo mode HL7812 module
	 * 
	 * @param {bool} mode - True to enable, false to disable
	 * @returns {bool} Returns true if successful.
	 */
	bool setEcho(bool mode = true);

	/** 
	 * Ping the HL7812 module
	 * 
	 * @returns {bool} Returns true if successful.
	 */
	bool ping();

	/** 
	 * Performs a reset to the HL7812 module
	 * 
	 * @returns {bool} Returns true if successful.
	 */
	bool reset();

	/** 
	 * Gets the IMSI (Request International Mobile Subscriber Identity)
	 * 
	 * @returns {String} Returns the IMSI in String object, otherwise empty if failed
	*/
	String getIMSI();

	/** 
	 * Gets the IMEI (Request Product Serial Number Identification)
	 * 
	 * @returns {String} Returns the IMEI in String object, otherwise empty if failed
	*/
	String getIMEI();

	/** 
	 * Gets the GMI (Request Manufacturer Identification)
	 * 
	 * @returns {String} Returns the GMI in String object, otherwise empty if failed
	*/	
	String getGMI();

	/** 
	 * Gets the GMR (Request Revision Identification)
	 * 
	 * @returns {String} Returns the GMR in String object, otherwise empty if failed
	*/		
	String getGMR();

	/** 
	 * Gets the current date
	 * 
	 * @returns {String} Returns the date in String object, otherwise empty if failed
	*/		
	String getDate();

	/** 
	 * Gets the current time
	 * 
	 * @returns {String} Returns the current time in String object, otherwise empty if failed
	*/			
	String getTime();

	/** 
	 * Gets the CCID (Request SIM Card Identification)
	 * 
	 * @returns {String} Returns CCID in String object, otherwise empty if failed
	*/			
	 String getCCID();

	/** 
	 * Gets the CFUN (Phone Functionality)
	 * 
	 * @returns {String} Returns CFUN in String object, otherwise empty if failed
	*/	
	String getCFUN();

	/** 
	 * Gets the Pin code
	 * 
	 * @returns {String} Returns pin code in String object, otherwise empty if failed
	*/	
	String getCPIN();

	/** 
	 * Gets the RSSI
	 * 
	 * @returns {String} Returns RSSI in String object, otherwise empty if failed
	*/		
	String getRSSI();

	/** 
	 * Gets all signal information
	 * 
	 * @param {sSignalInformation} signalInformation - Structure where the signal information is stored (RSSI, BER, RSCP, ECNO, RSRQ and RSRP)
	 * @returns {bool} Returns true if successful, otherwise false.
	*/	
	bool getSignalInformation(sSignalInformation* signalInformation);

	/** 
	 * Set the CFUN mode
	 * 
	 * @param {uint8_t} mode - Mode value: 0 — Minimum functionality, SIM powered off, 1 — Full functionality, 4 — Disable radio transmit and receive; SIM powered on. (i.e. "Airplane Mode")
	 * @returns {bool} Returns true if successful, otherwise false
	*/
	bool setCFUN(uint8_t mode);

	/** 
	 * Gets the COPS (Operator selection)
	 * 
	 * @returns {String} Returns list of supported, otherwise empty if failed
	*/	
	String getCOPS();

	/** 
	 * Gets the CREG (Network Registration State) 
	 * 
	 * @returns {String} Returns the network registration state: 0 — Not registered, 1 — Registered, home network, 2 — Not registered, but ME is currently searching a new operator to register to, 3 — Registration denied, 4 — Unknown, 5 — Registered, roaming
	*/		
	String getCREG();

	/** 
	 * Gets the CEREG (EPS Network Registration Status) 
	 * 
	 * @returns {String} Returns the EPS network registration status.
	*/		
	String getCEREG();

	/** 
	 * Set the CREG (Network Registration State) 
	 * 
	 * @param {uint8_t} mode - Mode value
	 * @returns {bool} Returns true if successful, otherwise false.
	*/
	bool setCREG(uint8_t mode);

	/** 
	 * Set the CEREG (EPS Network Registration State) 
	 * 
	 * @param {uint8_t} mode - Mode value
	 * @returns {bool} Returns true if successful, otherwise false.
	*/
	bool setCEREG(uint8_t mode);	

	/** 
	 * Define PDP Context
	 * 
	 * @param {String} apn - APN name
	 * @returns {bool} Returns true if successful, otherwise false.
	*/	
	bool setAPN(String apn);

	/** 
	 * Define GPRS APN
	 * 
	 * @param {String} apn - APN name
	 * @returns {bool} Returns true if successful, otherwise false.
	*/		
	bool setGPRS(String apn);	

	/** 
	 * Gets current APN
	 * 	 
	 * @returns {String} Returns the name of APN
	*/	
	String getAPN();

	/** 
	 * Gets IP address
	 * 	 
	 * @returns {String} Returns the IP address in String object.
	*/		
	String getIpAddress();

	/** 
	 * Set all event HL7812 callback
	 * 	 
	 * @returns {void*} owner - Void pointer. This pointer defines an object attached to the callback. It can be null
	*/	
	void setEventCallback(void* owner, HL7812BaseCallback evtCallbak);
	
protected:
	ATParser mATParser;	
	Stream* mSerial;	
	HL7812BaseCallback mEvtCallbak;
	void* mOwner;

	String getClock(uint8_t type);	

	String getInformationIdentification(String request);	
	String getValueFromCmd(String request, String key, uint8_t index);
	String getValueFromNotif(String command, uint8_t index, uint16_t timeout);
	
	bool getSignalInfoFromCmd(String request, String key, sSignalInformation* signalInformation);

	ATParser* sendCommand(String cmd, uint16_t timeout = HL7812_DEFAULT_TIMEOUT_MS);
	String getFrame(uint32_t timeout);
	uint16_t getBinaryFrame(uint8_t* buffer, uint16_t length, uint32_t timeout);
	ATParser* getNotification(String receivedCmd, uint32_t timeout);
	void flushData();
};