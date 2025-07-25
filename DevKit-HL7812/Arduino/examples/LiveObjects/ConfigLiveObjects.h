/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file ConfigLiveObjects.h
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

#define MQTT_BUFFER             512
#define LIVEOBJECTS_MQTT_PORT   1883
#define LIVEOBJECTS_HOST        "liveobjects.orange-business.com"

#define DEVICE_NAME             "Sample"
#define STREAM_ID_CONFIG        "urn:lo:nsid:SampleConfig"
#define STREAM_ID_DATA          "urn:lo:nsid:SampleData"
#define STREAM_ID_EVENT         "urn:lo:nsid:SampleEvent"

#define MQTT_USER_NAME          "json+device"
#define MQTT_PASSWORD           "<key>"

#define LIVEOBJECTS_DATA_TOPIC  "dev/data"
#define LIVEOBJECTS_CMD_TOPIC   "dev/cmd"

#define TAG_SENSORS             "sensor"
#define TAG_EVENT               "event"
#define TAG_CONFIG              "config"
