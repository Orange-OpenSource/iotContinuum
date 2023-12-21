/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

#include "LiveObjects.h"

LiveObjects::LiveObjects() : mHl7812client(), mMqttClient(MQTT_BUFFER) {        
    mMqttClient.begin(mHl7812client);
    mMqttClient.setTimeout(5000);
}

LiveObjects::~LiveObjects() {
}

void LiveObjects::begin() {

    delay(1000);
    if(mHl7812client.initialize(LTE, "", true, 80000)) {
        Serial.println("HL7812 initialized");
    }
    else {
        Serial.println("HL7812 not initialized");
    }
}

bool LiveObjects::connect() {
    mMqttClient.setHost(LIVEOBJECTS_HOST, LIVEOBJECTS_MQTT_PORT);
    return mMqttClient.connect(DEVICE_NAME, MQTT_USER_NAME, MQTT_PASSWORD);
}

bool LiveObjects::publish(const char* streamId, const char* value, const char* tag) {
    String request = "{\"s\":\"" + String (streamId) + "\",\"v\":" + String(value) + ", \"tags\":[\"" + String(tag) + "\"]}";
    return mMqttClient.publish(LIVEOBJECTS_DATA_TOPIC, request);
}

bool LiveObjects::subscribeCommand()
{
    return mMqttClient.subscribe(LIVEOBJECTS_CMD_TOPIC);
}

void LiveObjects::setReceivedMessageCallback(MQTTClientCallbackSimple callback)
{
    mMqttClient.onMessage(callback);
}

bool LiveObjects::disconnect() {
    return mMqttClient.disconnect();      
}

bool LiveObjects::loop() {
    return mMqttClient.loop();
}

HL7812Base* LiveObjects::getHl7812() {
    return &mHl7812client;
}