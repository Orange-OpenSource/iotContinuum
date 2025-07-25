/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file LiveObjects.h
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
#include "HL7812.h"
#include "ConfigLiveObjects.h"
#include "MQTT.h"

/* This code example shows how to send data to LiveObjects servers using MQTT protocol with the HL7812.
IMPORTANT: LiveObjects credentials must be replaced in ConfigLiveObjects.h file first. */

class LiveObjects {
public:
    LiveObjects();
    virtual ~LiveObjects();

    void begin();
    bool connect();
    bool disconnect();

    bool publish(const char* streamId, const char* value, const char* tag);
    bool subscribeCommand();
    void setReceivedMessageCallback(MQTTClientCallbackSimple callback);
    bool loop();
    HL7812Base* getHl7812();

protected:
    uint8_t rx_buffer[512];
    uint8_t tx_buffer[512];

    MQTTClient mMqttClient;
    HL7812Client mHl7812client;
private:

};