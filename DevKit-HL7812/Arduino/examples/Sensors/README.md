# IoT Continuum

This page is part of the [IoT Continuum Dev Kit](/) / [Arduino](/Arduino) section

<picture>
 <source media="(prefers-color-scheme: dark)" srcset="/images/DevKit_face1-black.jpg">
 <source media="(prefers-color-scheme: light)" srcset="/images/DevKit_face1-white.jpg">
 <img alt="IoT Continuum Dev Kit" src="/images/DevKit_face1-white.jpg" width="400"/>
</picture>


# Read onboard sensors data and plot them in the Serial Plotter

This [code sample](Sensors.ino) reads the following sensors and sends them to the Serial Monitor in the Arduino IDE in a format that is plottable with the Serial Plotter of the Arduino IDE:
* From BME280 (I2C): temperature, humidity, sensor
* From LSM6DSOX (I2C): Accelerometer, Gyroscope

<img src="/images/Sensors_Acceleration.png" alt="drawing" width="500"/>
<img src="/images/Sensors_Rotation.png" alt="drawing" width="500"/>
<img src="/images/Sensors_Temp.png" alt="drawing" width="500"/>
<img src="/images/Sensors_Values.png" alt="drawing" width="500"/>

