# IoT Continuum

This page is part of the [IoT Continuum Dev Kit](/) / [Arduino](/Arduino) section

<picture>
 <source media="(prefers-color-scheme: dark)" srcset="/images/DevKit_face1-black.jpg">
 <source media="(prefers-color-scheme: light)" srcset="/images/DevKit_face1-white.jpg">
 <img alt="IoT Continuum Dev Kit" src="/images/DevKit_face1-white.jpg" width="400"/>
</picture>


# Send AT Commands to the HL7812 cellular module

[This sample code](ATCommands_HL7812.ino) reads AT command inputs from the Arduino IDE's Serial Monitor, sends it to the HL7812, read the response back and display it in the Serial Monitor.

You can use this program as a convenient AT command console to the HL7812 from your Arduino IDE.

AT Commands documentation for HL7812 can be found [here](https://source.sierrawireless.com/resources/airprime/software/hl78xx_at_commands_interface_guide/).

Here are few useful commands you may want to test:
* `ATI3` (gives back the firmware version of the HL7812 module)
* `AT+CCID` (gives back the ICCID)
* `AT+CGSN=1` (gives back the EMEI of the module)
* `AT+CREG?` (gives back the registration status to the cellular network)
* `AT+CSQ` (gives back the quality of the cellular signal)
* ...

