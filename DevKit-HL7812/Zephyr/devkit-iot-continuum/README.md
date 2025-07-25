# DevKit Iot continuum Application

This repository contains a DevKit Iot continuum example application and the devkit_iot_continuum BSP. The main purpose of this
repository is to serve as a reference on how to structure Zephyr-based applications on DevKit Iot continuum board.

## Getting Started

Before getting started, make sure you have a proper Zephyr development environment. 
WARNING : During the zephyr starting guide, you may experienced some issues:

    - Take care if your OS is windows to be in the "Windows" -> "install globally" section during the chapter "Get Zephyr and install Python dependencie"
    - For Chocolatey installation, we recommend to use Windows powershell prompt with admin rights.
    - Globally, even is they tell you that you can go to non-admin cmd prompt, stay in admin cmd prompt.
    - While installing python dependencies, you can face problem with "west". in that case, you may uninstall and install again.

Follow the official [Zephyr Getting Started Guide] (https://docs.zephyrproject.org/latest/getting_started/index.html) for your OS until you reach the chapter "Build the Blinky Sample".

In order to check that you have working environnement, you can use the board "nucleo_u575zi_q" for the "<your-board-name>" in the chapter "Build the Blinky Sample" of the zephyr getting started guide.

### Initialization

Create a folder which will be your workspace (for example : ``my-workspace``).

WARNING: 

    - For the following command (west init), please make sure to have your github credentials.
    - You can either use https or ssh connetion for cloning the repositorie.

The first step is to initialize the workspace folder (``my-workspace``) where
the ``devkit_iot_continuum`` application and all Zephyr modules will be cloned. Open a cmd prompt in ``my-workspace`` folder and run the following
command:

```shell or command prompt
# initialize my-workspace for the devkit_iot_continuum application (main branch)
cd ..
west init -m https://github.com/lacroix-group/Orange-Zephyr-devkit.git --mr main my-workspace
# update Zephyr modules
cd my-workspace
cd devkit-iot-continuum
west update
```
### STM32Cube programmer installation

In order to flash devkit_iot_continuum board, we recommend to use STM32CubeProgrammer.
You can find STM32CubeProgrammer software on STM32 website [here](https://www.st.com/en/development-tools/stm32cubeprog.html)

### Building and running

To build the application, run the following command:

```shell
cd <my-workspace>/devkit-iot-continuum/demo_devkit_iot_continuum/<demo>
west build -b devkit_iot_continuum -p
```

Before running, you have to :

    (1) : Connect USB-C cable between devkit_iot_continuum board and your computer.

    (2) : Connect STLINK/V2 device on the board(connector J2) and your computer. (you have have to install [STLINK/V2 device driver](https://www.st.com/en/development-tools/stsw-link009.html))

    (3) : Insert a SIM Card into the device (only for Modem demo or it will failled).

Once you have built the application, run the following command to flash it :

```shell
west flash
```
In case of an error with STM32CubeProgrammer, you may want to add STM32_Programmer_CLI to your PATH.

In order to see logs, you have to install USB Uart driver [install link](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) and a UART communication programm like TeraTerm or Minicom.

Once the board is flashed, use one of the previous UART Communication program and listen to the COM port called (Silicon Labs CP210x USB to UART Bridge) with a baudrate of 115200.

Reset the board to see the log from the beggining.

In case of succesfull manipulation, you should see something like this with the devkit_iot_continuum demo application:
```shell
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
```
