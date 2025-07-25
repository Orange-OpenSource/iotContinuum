.. demo_devkit:

Demo DevKit IOT Continuum
#########################

Overview
********

The purpose of this example is to show all the component's basic capability on the DevKit IOT Continuum board (HL7812 Modem, LSM6DSO and BME280)

The demo start with a LED example which turn on/off all the LED.

Then it will use the BME280 module BSP which allows to retrieve and display pression, temperature and humidity data. 

Then it will use the LSM6DSO module BSP which allows to retrieve and display rotation and acceleration data.

At the end, it will use the Modem BSP to create a HTTP connection on www.google.com and ping it.

Build & Run
***********

Requirements
============

Have a SIM card inserted in the DevKit IOT Continuum board.

Build
=====

.. code-block:: bash

   $ cd $(west topdir)/devkit-iot-continuum
   $ west build -b devkit_iot_continuum demo_devkit_iot_continuum/ -p

Run
===

.. code-block:: bash

   $ west flash

Output
======

USB Modem
_________

.. note::
   Output for devkit_iot_continuum board with SIM card

.. code-block:: bash

   [00:00:00.004,000] <inf> pca953x: pca953x@38 init ok
   [00:00:00.005,000] <inf> modem_hl7812: Modem Run
   [00:00:00.015,000] <inf> modem_hl7812: Modem Reset
   [00:00:00.065,000] <inf> modem_hl7812: Sleep State: UNINITIALIZED
   [00:00:00.065,000] <inf> modem_hl7812: Network State: 0 NOT_REGISTERED
   [00:00:00.065,000] <inf> modem_hl7812: Startup State: UNKNOWN
   [00:00:00.065,000] <inf> modem_hl7812: Modem Run
   [00:00:05.580,000] <inf> modem_hl7812: Network State: 2 SEARCHING
   [00:00:06.199,000] <inf> modem_hl7812: Startup State: READY
   [00:00:06.199,000] <inf> modem_hl7812: Sleep State: AWAKE
   [00:00:06.199,000] <inf> modem_hl7812: Modem booted!
   [00:00:07.355,000] <inf> modem_hl7812: Revision: HL7812.5.4.10.0
   [00:00:07.358,000] <inf> modem_hl7812: +KSRAT: 0 (0:CAT-M1, 1:NB-IoT and 2:GSM)
   [00:00:07.378,000] <inf> modem_hl7812: Current band configuration: 0000 00000000 00080818
   [00:00:07.383,000] <inf> modem_hl7812: Bottom band mismatch, want 0808189f got 00080818
   [00:00:07.430,000] <inf> modem_hl7812: Current band configuration: 0000 00000000 0808189f
   [00:00:14.148,000] <inf> modem_hl7812: Network State: 2 SEARCHING
   [00:00:14.839,000] <inf> modem_hl7812: Startup State: READY
   [00:00:14.839,000] <inf> modem_hl7812: Sleep State: AWAKE
   [00:00:14.840,000] <inf> modem_hl7812: Modem booted!
   [00:00:15.167,000] <inf> modem_hl7812: Manufacturer: Sierra Wireless
   [00:00:15.220,000] <inf> modem_hl7812: Model: HL7812
   [00:00:15.273,000] <inf> modem_hl7812: IMEI: 351144440344308
   [00:00:15.277,000] <inf> modem_hl7812: Serial #: AN3021324101B1
   [00:00:15.354,000] <inf> modem_hl7812: ICCID: 89330123107805289340
   [00:00:15.407,000] <inf> modem_hl7812: IMSI: 208012402781283
   [00:00:15.640,000] <inf> modem_hl7812: Network State: 2 SEARCHING
   [00:00:15.664,000] <inf> modem_hl7812: Modem ready!
   [00:00:15.669,000] <inf> LSM6DSO: Initialize device lsm6dso@6a
   [00:00:15.670,000] <inf> LSM6DSO: chip id 0x6c
   *** Booting Zephyr OS build zephyr-v3.4.0-1907-g168de28b40a4 ***
   [00:00:15.675,000] <dbg> demo_devkit:
   [00:00:15.675,000] <dbg> demo_devkit: **************************************
   [00:00:15.675,000] <dbg> demo_devkit: ***** DevKit Iot Continuuum Demo *****
   [00:00:15.675,000] <dbg> demo_devkit: **************************************
   
   [00:00:15.676,000] <dbg> demo_devkit: Led example
   
   [00:00:15.676,000] <dbg> demo_devkit: -> Red LED for 3 seconds
   [00:00:16.143,000] <inf> modem_hl7812: Operator: 0
   [00:00:18.677,000] <dbg> demo_devkit: -> Green LED for 3 seconds
   [00:00:21.677,000] <dbg> demo_devkit: -> Blue LED for 3 seconds
   
   [00:00:24.678,000] <dbg> demo_devkit: BME280 example
   
   [00:00:24.688,000] <dbg> demo_devkit:  Fetch BME280 n°1
   [00:00:24.688,000] <dbg> demo_devkit:  Temperature BME280 305
   [00:00:24.688,000] <dbg> demo_devkit:  Pression BME280 1016
   [00:00:24.688,000] <dbg> demo_devkit:  Humidity BME280 27
   
   [00:00:26.699,000] <dbg> demo_devkit:  Fetch BME280 n°2
   [00:00:26.699,000] <dbg> demo_devkit:  Temperature BME280 305
   [00:00:26.699,000] <dbg> demo_devkit:  Pression BME280 1016
   [00:00:26.699,000] <dbg> demo_devkit:  Humidity BME280 27
   
   [00:00:28.710,000] <dbg> demo_devkit:  Fetch BME280 n°3
   [00:00:28.710,000] <dbg> demo_devkit:  Temperature BME280 305
   [00:00:28.710,000] <dbg> demo_devkit:  Pression BME280 1016
   [00:00:28.710,000] <dbg> demo_devkit:  Humidity BME280 27
   
   [00:00:30.720,000] <dbg> demo_devkit:  Fetch BME280 n°4
   [00:00:30.720,000] <dbg> demo_devkit:  Temperature BME280 305
   [00:00:30.720,000] <dbg> demo_devkit:  Pression BME280 1016
   [00:00:30.720,000] <dbg> demo_devkit:  Humidity BME280 26
   
   [00:00:32.731,000] <dbg> demo_devkit:  Fetch BME280 n°5
   [00:00:32.731,000] <dbg> demo_devkit:  Temperature BME280 306
   [00:00:32.731,000] <dbg> demo_devkit:  Pression BME280 1016
   [00:00:32.731,000] <dbg> demo_devkit:  Humidity BME280 26
   
   [00:00:34.731,000] <dbg> demo_devkit: LSM6DSO example
   
   [00:00:34.734,000] <dbg> demo_devkit:  Fetch LSM6DSO n°1
   [00:00:34.734,000] <dbg> demo_devkit:  Acceleration X:2763, Acceleration Y:7102 , Acceleration Z:6578
   [00:00:34.734,000] <dbg> demo_devkit:  Rotation X:2, Rotation Y:-5 , Rotation Z:-1
   
   [00:00:36.734,000] <dbg> demo_devkit:  Fetch LSM6DSO n°2
   [00:00:36.734,000] <dbg> demo_devkit:  Acceleration X:2768, Acceleration Y:7135 , Acceleration Z:6525
   [00:00:36.734,000] <dbg> demo_devkit:  Rotation X:3, Rotation Y:-6 , Rotation Z:-1
   
   [00:00:38.735,000] <dbg> demo_devkit:  Fetch LSM6DSO n°3
   [00:00:38.735,000] <dbg> demo_devkit:  Acceleration X:2768, Acceleration Y:7142 , Acceleration Z:6528
   [00:00:38.735,000] <dbg> demo_devkit:  Rotation X:3, Rotation Y:-6 , Rotation Z:-1
   
   [00:00:40.736,000] <dbg> demo_devkit:  Fetch LSM6DSO n°4
   [00:00:40.736,000] <dbg> demo_devkit:  Acceleration X:2771, Acceleration Y:7140 , Acceleration Z:6524
   [00:00:40.736,000] <dbg> demo_devkit:  Rotation X:4, Rotation Y:-6 , Rotation Z:-1
   
   [00:00:42.737,000] <dbg> demo_devkit:  Fetch LSM6DSO n°5
   [00:00:42.737,000] <dbg> demo_devkit:  Acceleration X:2771, Acceleration Y:7138 , Acceleration Z:6530
   [00:00:42.737,000] <dbg> demo_devkit:  Rotation X:3, Rotation Y:-6 , Rotation Z:-1
   
   [00:00:44.737,000] <dbg> demo_devkit: Modem example
   
   [00:00:45.125,000] <dbg> bsp_modem_sierra: Writing APN: OK
   [00:00:45.125,000] <dbg> bsp_modem_sierra: Initialization of Sierra LTE Module HL7812 success
   [00:01:00.126,000] <dbg> demo_devkit: Modem try to connect
   [00:01:00.126,000] <dbg> bsp_modem_sierra: Waiting Connection of Sierra LTE Module HL7812
   [00:01:15.126,000] <dbg> demo_devkit: Modem try to connect
   [00:01:15.126,000] <dbg> bsp_modem_sierra: Waiting Connection of Sierra LTE Module HL7812
   [00:01:30.126,000] <dbg> demo_devkit: Modem try to connect
   [00:01:30.126,000] <dbg> bsp_modem_sierra: Waiting Connection of Sierra LTE Module HL7812
   [00:01:33.207,000] <inf> modem_hl7812: Network State: 0 NOT_REGISTERED
   [00:01:33.216,000] <inf> modem_hl7812: Network State: 2 SEARCHING
   [00:01:33.961,000] <inf> modem_hl7812: Operator: 0,0,"Orange F",7
   [00:01:33.965,000] <inf> modem_hl7812: Network State: 1 HOME_NETWORK
   [00:01:34.470,000] <inf> modem_hl7812: Operator: 0,0,"Orange F",7
   [00:01:45.126,000] <dbg> demo_devkit: Modem try to connect
   [00:01:45.126,000] <dbg> bsp_modem_sierra: Connected to HOME NETWORK
   [00:01:45.183,000] <dbg> bsp_modem_sierra: Set HTTP config: OK
   [00:01:45.183,000] <dbg> bsp_modem_sierra: HTTP Connection of Sierra LTE Module HL7812 success
   [00:01:45.841,000] <inf> modem_hl7812: Received message:  200 OK
   [00:01:50.448,000] <dbg> bsp_modem_sierra: Get data success