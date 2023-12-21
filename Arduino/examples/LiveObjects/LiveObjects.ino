/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file LiveObjects.ino
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
#include <HL7812.h>
#include <LiveObjects.h>

#define DELAY_INFO      60000

LiveObjects* mLiveObjects = NULL;

/* This code example shows how to send data to LiveObjects servers using MQTT protocol with the HL7812.
IMPORTANT: LiveObjects credentials must be replaced in ConfigLiveObjects.h file first. */

void hl7812Callback(void* object, uint16_t type , uint32_t value) {
   Serial.println("hl7812Callback callback"); 
}

void mqttMessageReceived(String &topic, String &payload) {
    Serial.println("incoming: " + topic + " - " + payload);    
}

void schedule() {
    uint32_t countBeforeReset = 0;
    uint32_t current = millis();

    while(true) {
        bool state = mLiveObjects->loop();   
        
        if(!state) {
            Serial.println("Module disconnected");
            Serial.println("Attempt to reconnect");

            mLiveObjects->disconnect();
            delay(3000);

            if(!mLiveObjects->connect()) {
                countBeforeReset++;
                if(countBeforeReset > 3) {
                    NVIC_SystemReset();
                }
            }

            delay(2000);
        }        
     
        if(millis() - current > DELAY_INFO) {
            Serial.println("Publish info device");
            publishDeviceInfo();
            delay(250);            
            current = millis();           
        }
        
        delay(250);
    }
}

bool publishDeviceInfo() {
    HL7812Base* hl7812 = mLiveObjects->getHl7812();

    String imsi = hl7812->getIMSI();
    Serial.print("ISMI="); Serial.println(imsi); 

    String rssi = hl7812->getRSSI();
    Serial.print("RSSI="); Serial.println(rssi); 

    String imei = hl7812->getIMEI();
    Serial.print("IMEI="); Serial.println(imei); 

    String apn = hl7812->getAPN();
    Serial.print("APN="); Serial.println(apn); 

    String deviceInfo = "{\"imsi\":\"" + imsi + "\",\"imei\":\"" + imei + "\",\"rssi\":" + rssi + ",\"apn\":" + apn + "}";
    
    return mLiveObjects->publish(String(STREAM_ID_CONFIG).c_str(), deviceInfo.c_str(), TAG_CONFIG);    
}

void execute() {       
    mLiveObjects = new LiveObjects();
    Serial.println("Connect to LiveObjects");
    HL7812Base* hl7812 = mLiveObjects->getHl7812();
    mLiveObjects->begin();    

    if(!mLiveObjects->connect()) {
        Serial.println("Connection to LiveObjects failed");
        while(true);
    }     
    
    Serial.println("Connected to LiveObjects");
    mLiveObjects->setReceivedMessageCallback(mqttMessageReceived);
    mLiveObjects->subscribeCommand();
      
    if(!publishDeviceInfo()) {
        Serial.println("publishDeviceInfo failed");
        return;
    }
    else {
        Serial.println("publishDeviceInfo success");
    }
    
    schedule();
}

void setup()
{  
  while(!Serial){
  }
  
  Serial.begin(115200);
  delay(2000);
  Serial.println("Start test Liveobjects");

  execute();
}

void loop(){
}
