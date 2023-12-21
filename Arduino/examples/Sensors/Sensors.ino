/*
* Software Name : iotContinuum
* SPDX-FileCopyrightText: Copyright (c) 2023 Orange SA
* SPDX-License-Identifier: MIT
*
* This software is distributed under the MIT License,
* the text of which is available at https://spdx.org/licenses/MIT.html
* or see the "LICENSE" file for more details.
*/

/*! @file Sensors.ino
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

#include <Wire.h>
#include "PCA9534.h"
#include <BME280I2C.h>
#include <BME280.h>
#include "LSM6DSOXSensor.h"

/* This example shows the use of sensors (BME280 and LSM6DSOX) as well as the RGB LED */

PCA9534 gpio;
BME280I2C bme;
LSM6DSOXSensor lsm6dsoxSensor = LSM6DSOXSensor(&Wire, LSM6DSOX_I2C_ADD_L);

void setup() { 
  /* Init Serial (Serial Monitor) */
  Serial.begin(115200);

  /* Init GPIOs */
  gpio.begin();

  /* Init I2C */
  Wire.begin();
  
  /* Init BME280 - temperature + humidity + pressure sensor */
  bme.begin();
  
  /* Init LSM6DSOX sensor - accelerometer & gyroscope */
  lsm6dsoxSensor.begin();

  /* Setup LED GPIOs in ouput mode */
  gpio.pinMode(RED_LED, OUTPUT);
  gpio.pinMode(GREEN_LED, OUTPUT);
  gpio.pinMode(BLUE_LED, OUTPUT);

  delay(500);
 
  /* Enable accelerometer and gyroscope, and check success */
  if (lsm6dsoxSensor.Enable_X() == LSM6DSOX_OK && lsm6dsoxSensor.Enable_G() == LSM6DSOX_OK) {
    Serial.println("Success enabling accelero and gyro");
  } else {
    Serial.println("Error enabling accelero and gyro");
  }
 
  /* Read ID of device and check that it is correct */
  uint8_t id;
  lsm6dsoxSensor.ReadID(&id);
  if (id != LSM6DSOX_ID) {
    Serial.println("Wrong ID for LSM6DSOX sensor. Check that device is plugged");
  } else {
    Serial.println("Receviced correct ID for LSM6DSOX sensor");
  }

  Serial.println("Start");
}

void loop() {
  /* Play with LEDs */
  gpio.digitalWrite(RED_LED, LOW);
  delay(200);
  gpio.digitalWrite(GREEN_LED, LOW);
  delay(200);
  gpio.digitalWrite(BLUE_LED, LOW);
  delay(200);
  gpio.digitalWrite(GREEN_LED, HIGH);
  delay(200);
  gpio.digitalWrite(RED_LED, HIGH);
  delay(200);
  gpio.digitalWrite(BLUE_LED, HIGH);
  delay(200);
  
  /* Read temperature, humidity & pressure values */
  float temp = bme.temp();
  float hum = bme.hum();
  float pres = bme.pres();
  /* Plot data (friendly format for the Serial Plotter) */
  Serial.println("Temp:" + String(temp) + "°C, Humidity:" + String(hum) + "%, Pressure:" + String(pres) + "Pa");

  /* Read accelerometer */
  uint8_t acceleroStatus;
  lsm6dsoxSensor.Get_X_DRDY_Status(&acceleroStatus);
  if (acceleroStatus == 1) { /* Status == 1 means a new data is available */
    int32_t acceleration[3];
    lsm6dsoxSensor.Get_X_Axes(acceleration);
    /* Plot data (friendly format for the Serial Plotter) */
    Serial.println("Accel_X:" + String(acceleration[0]) + "mg, Accel_Y:" + String(acceleration[1]) + "mg, Accel_Z:" + String(acceleration[2]) + "mg");
  }

  /* Read gyroscope */
  uint8_t gyroStatus;
  lsm6dsoxSensor.Get_G_DRDY_Status(&gyroStatus);
  if (gyroStatus == 1) { // Status == 1 means a new data is available
    int32_t rotation[3];
    lsm6dsoxSensor.Get_G_Axes(rotation);
    /* Plot data in milli degrees per second (friendly format for the Serial Plotter) */
    Serial.println("Rot_X:" + String(rotation[0]) + "mdps, Rot_Y:" + String(rotation[1]) + "mdps, Rot_Z:" + String(rotation[2]) + "mdps");
  }
}