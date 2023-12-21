/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

#include "HL7812Base.h"

#define END_MESSAGE_LEN            18

HardwareSerial SerialHL7812(USART3);

HL7812Base::HL7812Base() : 
    mSerial(&SerialHL7812), 
    mATParser(),
    mEvtCallbak(NULL),
    mOwner(NULL) {    
    SerialHL7812.begin(115200);
}

HL7812Base::~HL7812Base() {
    mSerial = NULL;
}

bool HL7812Base::setEcho(bool mode)
{
    String cmd = "ATE" + String(mode ? "1" : "0");
    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

bool HL7812Base::ping()
{
    String cmd = "AT";
    ATParser* atParser = sendCommand(cmd, 500);
    return atParser->isOk();
}

bool HL7812Base::reset()
{
    String cmd = "AT+CFUN=1,1";
    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

String HL7812Base::getIMSI()
{
    DEBUG_PRINT("IMSI: ");
    return getInformationIdentification("AT+CIMI");
}

String HL7812Base::getIMEI()
{
    DEBUG_PRINT("IMEI: ");
    return getInformationIdentification("AT+GSN");
}

/*Request Manufacturer Identification*/
String HL7812Base::getGMI()
{
    DEBUG_PRINT("Manufacturer: ");
    return getInformationIdentification("AT+GMI");
}

/*Request Firmware Version*/
String HL7812Base::getGMR()
{
    DEBUG_PRINT("Version: ");
    return getInformationIdentification("AT+GMR");
}

String HL7812Base::getDate() {

    DEBUG_PRINT("Date:");
    return getClock(0);
}

String HL7812Base::getTime() {

    DEBUG_PRINT("Date:");
    return getClock(1);
}

String HL7812Base::getClock(uint8_t type) {
    return getValueFromCmd("AT+CCLK?", "+CCLK", type);
}

String HL7812Base::getCCID() {

    DEBUG_PRINT("CCID: ");
    return getValueFromCmd("AT+CCID?", "+CCID", 0);
}

String HL7812Base::getCFUN() {
    
    DEBUG_PRINT("CFUN: ");
    return getValueFromCmd("AT+CFUN?", "+CFUN", 0);
}

bool HL7812Base::setCFUN(uint8_t mode) {
    String cmd = "AT+CFUN=" + String(mode);

    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

String HL7812Base::getCPIN() {
    
    DEBUG_PRINT("CPIN: ");
    //return getValueFromCmd("AT+CPin?", 0, 0);
    return "";
}

String HL7812Base::getRSSI() {
    
    DEBUG_PRINT("CSQ: ");
    return getValueFromCmd("AT+CSQ", "+CSQ", 0);
}

bool HL7812Base::getSignalInformation(sSignalInformation* signalInformation) {
    DEBUG_PRINT("CESQ: ");
    return getSignalInfoFromCmd("AT+CESQ", "+CESQ", signalInformation);
}

String HL7812Base::getCOPS() {
    
    DEBUG_PRINT("COPS: ");
    return getValueFromCmd("AT+COPS?", "+COPS", 2);
}

String HL7812Base::getCREG() {
    
    DEBUG_PRINTLN("CREG: ");
    return getValueFromCmd("AT+CREG?", "+CREG", 1);
}

bool HL7812Base::setCREG(uint8_t mode) {
    String cmd = "AT+CREG=" + String(mode);
    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

String HL7812Base::getCEREG() {
    
    DEBUG_PRINT("CEREG: ");
    return getValueFromCmd("AT+CEREG", "+CEREG", 1);
}

bool HL7812Base::setCEREG(uint8_t mode) {    
    String cmd = "AT+CEREG=" + String(mode);
    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

bool HL7812Base::setAPN(String apn) {
    String cmd = "AT+CGDCONT=1,\"IPV4V6\",\"" + apn + "\"";
    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

String HL7812Base::getAPN() {        
    return getValueFromCmd("AT+CGCONTRDP", "+CGCONTRDP", 2);
}

String HL7812Base::getIpAddress() {        
    return getValueFromCmd("AT+CGCONTRDP", "+CGCONTRDP", 3);
}

bool HL7812Base::setGPRS(String apn) {    
	String cmd = "AT+KCNXCFG=1,\"GPRS\",\"" + apn + "\"";
    ATParser* atParser = sendCommand(cmd);
    return atParser->isOk();
}

bool HL7812Base::initialize(eMode mode, String apn, bool isReset, uint32_t timeout) {
    bool isStarted = true;
    if (isReset)
    {
        bool res = reset();
        while(!res) {
            res = reset();
        }

        while(isStarted) {
            isStarted = ping();
            delay(250);
        }
    }

    while(!isStarted) {
        isStarted = ping();
    }
    uint32_t current = millis();
    if(setEcho(false)) {
        Serial.println("Set Echo OK!");
    }

   if (mode == LTE)
   {
        String creg = "";
        bool isRegistred = false;
        uint16_t delayReg = 0;
        while((!isRegistred) && (millis() - current <= timeout)) {
            creg = getCREG();
            if((creg != "") && (creg.toInt() == 1)) {
                isRegistred = true;
            } else {
                delay(250);
                current = millis();
            }
            delayReg += 250;            
            Serial.print("Time="); Serial.println(delayReg);
            if(mEvtCallbak != NULL) {
                mEvtCallbak(mOwner, 0, 0);
            }
            
        }
        if(apn == "") {
            apn = ORANGE_DEFAULT_APN;
        }
        setAPN(apn);
        setGPRS(apn);
   }
   return true;
}

String HL7812Base::getInformationIdentification(String request)
{
    ATParser* atParser = sendCommand(request);    

    if(atParser->isOk())
    {    
        int count = atParser->getCount();
        if(count >= 2) {
            return atParser->getLine(count - 2)->getData();
        }        
    }

    return "";  
}

String HL7812Base::getValueFromCmd(String request, String key, uint8_t index)
{
    ATParser* atParser = sendCommand(request);
    ATLine* atline = atParser->getLineByKey(key);
    return ((atParser->isOk()) && (atline != NULL) && (atline->getCount() > index)) ? atline->getValue(index)->toString() : "";
}

bool HL7812Base::getSignalInfoFromCmd(String request, String key, sSignalInformation* signalInformation)
{
    ATParser* atParser = sendCommand(request);
    ATLine* atline = atParser->getLineByKey(key);
    Serial.println(atline->getCount());
    if((atParser->isOk()) && (atline != NULL) && (atline->getCount() == 6)) {        
        signalInformation->rssi = atline->getValue(0)->toString();
        signalInformation->ber = atline->getValue(1)->toString();
        signalInformation->rscp = atline->getValue(2)->toString();
        signalInformation->ecno = atline->getValue(3)->toString();
        signalInformation->rsrq = atline->getValue(4)->toString();
        signalInformation->rsrp = atline->getValue(5)->toString();
        return true;
    }

    return false;
}

String HL7812Base::getValueFromNotif(String command, uint8_t index, uint16_t timeout)
{
    ATParser* atParser = getNotification(command, timeout);    

    ATLine* atline = atParser->getLineByKey(command);
    return ((atline != NULL) && (atline->getCount() > index)) ? atline->getValue(index)->toString() : "";
}

ATParser* HL7812Base::sendCommand(String cmd, uint16_t timeout)
{
    this->flushData();    

    DEBUG_FRAME_PRINT("->"); DEBUG_FRAME_PRINTLN(cmd.c_str());
    mSerial->println(cmd.c_str());

    String frame = getFrame(timeout);

    if (frame != "") {
        DEBUG_FRAME_PRINT("<-"); DEBUG_FRAME_PRINTLN(frame);        
    } 
    else {
        DEBUG_FRAME_PRINTLN("<-TIMEOUT");
    }

    mATParser.begin(frame);  
    return &mATParser;
}

String HL7812Base::getFrame(uint32_t timeout)
{
    uint32_t current = millis();
    String frame = "";
    bool finish = false;
    bool frameStarted = false;

    while((millis() - current <= timeout) && (!finish))
    {
        if(mSerial->available())
        {       
            char c = mSerial->read();    

            if(!frameStarted) {
                if((c != '\r') && (c != '\n')) {
                    frame += String(c);
                    frameStarted = true;
                }
            }
            else {
                frame += String(c);
            }            

            if(frame != "")
            {
                current = millis();
                timeout = 100;
            }

            finish = frame.endsWith("OK\r\n");
        }
    }

    return frame;
}

uint16_t HL7812Base::getBinaryFrame(uint8_t* buffer, uint16_t length, uint32_t timeout)
{
    uint32_t current = millis();
    String frame = "";
    uint16_t pos = 0;
    bool finish = false;    
    bool readData = false;
    bool finishReadData = false;
    
    while((millis() - current <= timeout) && (!finish))
    {
        if(mSerial->available())
        {           
            char c = (char)mSerial->read();
            if(!readData)
            {                
                frame += String(c);               
                if(frame.endsWith("CONNECT\r\n")) {  
                    Serial.print("Found Connect");                 
                    readData = true;
                    frame = "";
                }
                else {
                    current = millis();
                    timeout = 100;
                }
            }
            else {
                if(!finishReadData) {
                    buffer[pos] = (uint8_t)c;
                    Serial.print(c, HEX); Serial.print(" ");                    
                    pos++;
                    finishReadData = (pos >= length);
                }
                else {
                    frame += String(c);                   
                    finish = frame.endsWith("--EOF--Pattern--\r\nOK\r\n");                                       
                }
            }
            current = millis();
            timeout = 100;
        }
    }
    Serial.println("");
    return pos;
}

ATParser* HL7812Base::getNotification(String receivedCmd, uint32_t timeout)
{
    uint32_t bakTimeout = timeout;
    uint32_t current = millis();
    String frame = "";
    bool finish = false;
    bool frameStarted = false;

    while((millis() - current <= timeout) && (!finish))
    {
        if(mSerial->available())
        {
            char c = mSerial->read();    

            if(!frameStarted) {
                if((c != '\r') && (c != '\n')) {
                    frame += String(c);
                    frameStarted = true;
                } 
            }
            else {
                frame += String(c);
            }
            
            if(frameStarted)
            {
                current = millis();
                timeout = 100;
            }

            if(frame.endsWith("\r\n")) {
                if(frame.startsWith(receivedCmd)) {
                    finish = true;
                    DEBUG_PRINT(F("Found=")); DEBUG_PRINTLN(frame.c_str());
                }   
                else {
                    DEBUG_PRINT(F("Ignore=")); DEBUG_PRINTLN(frame.c_str());
                    frame = "";
                    timeout = bakTimeout; 
                }
            }
        }
    }

    mATParser.begin(frame);
    return &mATParser;
}

void HL7812Base::flushData() {       
    mATParser.flush();
    // Serial.print("Flush:");
    while(mSerial->available()) {        
    //    Serial.print((char)mSerial->read());
        mSerial->read();
    }
    // Serial.println("End Flush");
    mSerial->flush();
}

void HL7812Base::setEventCallback(void* owner, HL7812BaseCallback evtCallbak) {
    mEvtCallbak = evtCallbak;
    mOwner = owner;
}