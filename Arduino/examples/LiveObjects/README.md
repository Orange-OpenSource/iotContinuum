# IoT Continuum

This page is part of the [IoT Continuum Dev Kit](/) / [Arduino](/Arduino) section

<picture>
 <source media="(prefers-color-scheme: dark)" srcset="/images/DevKit_face1-black.jpg">
 <source media="(prefers-color-scheme: light)" srcset="/images/DevKit_face1-white.jpg">
 <img alt="IoT Continuum Dev Kit" src="/images/DevKit_face1-white.jpg" width="400"/>
</picture>


# LiveObjects MQTT

[This sample code](LiveObjects.ino) shows how to send sensors data using MQTT protocol with the HL7812 to LiveObjects servers.
NOTE: LiveObjects credentials must be replaced in [ConfigLiveObjects.h](ConfigLiveObjects.h) file first:

Replace the term "KeyBox" in the following strings with your device name on LiveObject:
```c
#define DEVICE_NAME             "KeyBox"
#define STREAM_ID_CONFIG        "urn:lo:nsid:KeyBoxConfig"
#define STREAM_ID_DATA          "urn:lo:nsid:KeyBoxData"
#define STREAM_ID_EVENT         "urn:lo:nsid:KeyBoxEvent"
```
and put your LiveObjects API key in:
```c
#define MQTT_PASSWORD           "<liveobjects key>"
```

All done! Connect to [Live Objects](https://liveobjects.orange-business.com/) to access your data feed:
 
<img src="/images/LiveObjects_data.png" alt="drawing" width="800"/>
