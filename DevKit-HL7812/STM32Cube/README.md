# IoT Continuum

This page is part of the [IoT Continuum Dev Kit](/)

> [!IMPORTANT]
> This section is under construction:
> Only the installation of the IDE is covered for now. In particular, **NO code examples are provided** for now.
> Stay tuned!

<picture>
 <source media="(prefers-color-scheme: dark)" srcset="/images/DevKit_face1-black.jpg">
 <source media="(prefers-color-scheme: light)" srcset="/images/DevKit_face1-white.jpg">
 <img alt="IoT Continuum Dev Kit" src="/images/DevKit_face1-white.jpg" width="400"/>
</picture>

# Getting Started (STM32CubeIDE)

To run this getting started tutorial, you need the following hardware:
* 1 IoT Continuum Dev Kit
* 1 ST-LINK V3 Programmer (J-TAG)
* 1 Orange SIM card already activated and inserted in the SIM holder

## Install STM32CubeIDE

This development environment is compatible with Windows, Mac & Linux.
If the STM32CubeIDE environment is not installed yet, install the latest version from [ST website](https://www.st.com/en/development-tools/stm32cubeide.html)

## Project Setup

1. Launch STM32CubeIDE
2. Create a new STM32 Project: Menu "File" > "New" > "STM32 Project"
3. In the left panel, use the "Commercial Part Number" field and enter "STM32U585CIU6" in order the filter the list of boards on the bottom right

<img src="/images/STM32CubeIDE_setup.png" alt="drawing" width="800"/>

5. Then, select the STM32U585CIU6 board in the list (bottom right panel), and click on the "Next" button
6. Give a name to your project like "HelloWorld" and then click on "Finish"

<img src="/images/STM32CubeIDE_project.png" alt="drawing" width="400"/>

## Hardware Setup

STM32Cube provides a graphical user interface to help with setting up the microcontroller and its peripherals from the main window of the IDE, and generate the code: use the menu on the left to activate and setup each different feature.

Open "System Core" then "ICACHE" and click the "Memory address remap" 

<img src="/images/STM32CubeIDE_pinout_config.png" alt="drawing" width="800"/>

Before using the code generation, you need to log in "My ST" profile or create a new account from the "My ST" upper menu (last one on the right).

To generate the code, just save the configuration with `Ctrl-S` or from the menu: "File" > "Save"

**Note**: STM32CubeIDE is based on EclipseIDE engine which allows different "perspectives" (aka layouts/views). When generating the code, the IDE suggests to switch to the code perspective. Accept it. You will always be able to change perspective using the top right corner icons.

## Code writing

Open the generated `Core/Src/main.c` file. Note the comments `USER CODE BEGIN...` and `USER CODE END...` and take care to add your code in between those tags so that if you change the configuration and regenerate the code, your code will stay safe.

<img src="/images/STM32CubeIDE_code_editing.png" alt="drawing"/>

## Compilation and upload

1. To build your code, use the hammer button ("Build")
2. Make sure the board and the ST-LINK programmer are both connected to your computer with each a USB cable (use data cables, not power-only usb cables). In case of doubt, you can check that both `Silicon Laboratories, Inc. CP2102N USB to UART Bridge Controller` and `STMicroelectronics STLINK-V3` are showing up on the USB:
  * on Windows: open the Device Manager and look in the USB section
  * on Mac and Linux: open a terminal and run `lsusb -v` command.
  * If it does not show up, install the driver from [here](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) and try again. 
3. Upload your program onto the device and run it using the arrow button ("Run")

## Learn more about STM32CubeIDE

To learn more about the STM32CubeIDE features, we recommend you to check out these [how-to & tutorial videos](https://wiki.st.com/stm32mcu/wiki/CubeIDE:Introduction_to_STM32CubeIDE#Videos_related_to_STM32CubeIDE)
