# IoT Continuum

This page is part of the [IoT Continuum Dev Kit](/) / [Arduino](/Arduino) section

<picture>
 <source media="(prefers-color-scheme: dark)" srcset="/images/DevKit_face1-black.jpg">
 <source media="(prefers-color-scheme: light)" srcset="/images/DevKit_face1-white.jpg">
 <img alt="IoT Continuum Dev Kit" src="/images/DevKit_face1-white.jpg" width="400"/>
</picture>


# Arduino HelloWorld code sample

This simple code displays "Hello World" in the Serial Monitor of the Arduino IDE, and repeatedly blinks the LED in red.
Make sure you have followed the [Getting Started](/Arduino) instructions first before running this code sample.

```c
#include <Wire.h>
#include "PCA9534.h"

PCA9534 gpio;

void setup() { 
  Serial.begin(115200);
  gpio.begin();
  Wire.begin();
  gpio.pinMode(GPIO_PIN_LED_RED, OUTPUT);
  delay(2000);
  Serial.println("Hello world");
}

void loop() {
  // put your main code here, to run repeatedly:
  gpio.digitalWrite(GPIO_PIN_LED_RED, LOW); // LED On
  delay(500);
  gpio.digitalWrite(GPIO_PIN_LED_RED, HIGH); // LED Off
  delay(500);
}
```

