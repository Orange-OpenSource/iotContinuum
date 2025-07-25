/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

#include "HL7812Client.h"

#define END_MESSAGE_LEN            18

HL7812Client::HL7812Client() : 
    Client(), 
    HL7812Base(), 
    mIndexReadByte(0),
    mLenReadByte(0),
    mAvailableCalled(false),
    mSession(-1) {    
}

HL7812Client::~HL7812Client() {
}

int HL7812Client::getSessionCount() {            
    return (geListSession()->getCount() - 1);
}

ATParser* HL7812Client::geListSession() {
    String cmd = "AT+KTCPCFG?";
    return sendCommand(cmd);
}

int HL7812Client::setSessionConfig(const char* host, uint16_t port)
{
    if(mSession == -1) {
        String cmd = "AT+KTCPCFG=1,0,\"" + String(host) + "\"," +  String(port);
        String curSession = getValueFromCmd(cmd, "+KTCPCFG", 0);
        mSession =- (curSession != "") ? curSession.toInt() : -1;
    }
    return mSession;
}

bool HL7812Client::sessionExists(int16_t session)
{
    ATParser* atParser = geListSession();

    ATLine* atline = atParser->getLineByKey("+KTCPCFG: " + String(session));
    return (atline != NULL);
}

bool HL7812Client::deleteSession(uint16_t session) {   
    String cmd = "AT+KTCPDEL=" + String(session);
    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

bool HL7812Client::deleteAllSession()
{
    int16_t session[] = {-1, -1, -1, -1, -1, -1};

    Serial.println("deleteAllSession");
    ATParser* atParser = geListSession();
    uint16_t pos = 0;

    for(int16_t i = 1; i <= 6; i++)
    {
        ATLine* atline = atParser->getLineByKey("+KTCPCFG: " + String(i));
        if(atline != NULL) {
            session[pos] = i;            
            pos++;
        }
    }

    bool finish = false;
    int i = 0;
    while((!finish) && (i < 6))
    {
        int16_t sessionId = session[i];
        if(sessionId == -1) {
            finish = true;
        }
        else {
            Serial.print("deleteSession:");Serial.println(sessionId);
            
            if(deleteSession(sessionId) && (sessionId == mSession)) {
                mSession = -1;
            }
            
            i++;
        }
    }

    return true;
}

int HL7812Client::connect(IPAddress ip, uint16_t port) {
    return -1;
}

int HL7812Client::connect(const char* host, uint16_t port) {    
    Serial.println("Connect to server");
    String cmd = "";
    ATParser* atParser;      

    deleteAllSession();
    
    mSession = setSessionConfig(host, port);

    if(mSession != -1) {
       cmd = "AT+KTCPCNX=" + String(mSession);
       atParser = sendCommand(cmd);

       if(atParser->isOk()) {
            String state = getValueFromNotif("+KTCP_IND: " + String(mSession), 1, 5000);

            if ((state != "") && (state.toInt() == 1))
            {
                return mSession;
            }
       }
    }    
    return -1;
}

size_t HL7812Client::write(uint8_t data) {
    return write(&data, 1);
}

size_t HL7812Client::write(const uint8_t *buffer, size_t size) {
    if(mSession == -1) return 0;

    if(size > 0) 
    {
        String cmd = "AT+KTCPSND=" + String(mSession) + "," + String(size);
        ATParser* atParser = sendCommand(cmd);
        
        if((atParser->getCount() == 1) && (atParser->getLine(0)->getData() == "CONNECT")) 
        {
            for(int i = 0; i < size; i++) {
                mSerial->print((char)buffer[i]);
            }
            String eofPattern = "--EOF--Pattern--";
            mSerial->println(eofPattern.c_str());
            
            String frame = getFrame(250);            
            atParser->begin(frame);
            return atParser->isOk() ? size : 0;
        }
        else {
            return 0;
        }
    }  
    return 0;  
}

int HL7812Client::available() {     
    int lenReceive = 0;
    if((mIndexReadByte == 0) || (mIndexReadByte >= mLenReadByte)) {
        lenReceive = getReceiveLength();
    }

    if(lenReceive > 0) {
        mLenReadByte = readReceiveFrame(mRxBuffer, lenReceive);
        mIndexReadByte = 0;
    }

    mAvailableCalled = true;      
    return (mLenReadByte > 0);
}

int HL7812Client::read() {
    int ret = -1;

    if(!mAvailableCalled) available();
    
    mAvailableCalled = false;

    if(mIndexReadByte < mLenReadByte) {        
        ret = (char)mRxBuffer[mIndexReadByte];        
        mIndexReadByte++;

        if(mIndexReadByte >= mLenReadByte) {
            mLenReadByte = 0;
            mIndexReadByte = 0;            
        }
    }

    return ret;
}

int HL7812Client::read(uint8_t *buffer, size_t size) {
    int i = 0;
    bool finish = false;

    while((!finish) && (i < size))
    {                        
        int c = read();        
        if(c != -1) {                
            buffer[i] = (char)c;
            i++;
        }
        else {
            finish = true;
        }
    }

    return i;
}

int HL7812Client::getReceiveLength() {
    return getTcpState(3);
}

int HL7812Client::getSocketState() {
    return getTcpState(0);
}

int HL7812Client::getTcpState(uint8_t type) {
    if(mSession == -1) return -1;
    String value = getValueFromCmd("AT+KTCPSTAT=" + String(mSession), "+KTCPSTAT", type);
    return value.toInt();
}

int HL7812Client::readReceiveFrame(uint8_t *buffer, size_t size) {
    if(mSession == -1) return 0;

    if(size > 0) {
        this->flush();
       
        String cmd = "AT+KTCPRCV=" + String(mSession) + "," + String(size);
        DEBUG_PRINT("->"); DEBUG_PRINTLN(cmd.c_str());

        mSerial->println(cmd.c_str());

        return getBinaryFrame((uint8_t*)buffer, size, 1000);
    }    
    return 0;
}

int HL7812Client::peek() {
    return 0;
}

void HL7812Client::flush() {       
    mATParser.flush();
    // while(mSerial->available()) {
    //     mSerial->read();
    // }
    mSerial->flush();
}

void HL7812Client::stop() {
    if(mSession == -1) return;
    String cmd = "AT+KTCPCLOSE=" + String(mSession);
    sendCommand(cmd);
}

uint8_t HL7812Client::connected() {
    uint8_t state = getSocketState();
    if (state == 3)
    {
        return 1;
    }
    flushDataBuffer();
    return 0;
}

void HL7812Client::flushDataBuffer() {
    while(available())
    {
       read(); 
    }
}

HL7812Client::operator bool(){
    return true;
}

