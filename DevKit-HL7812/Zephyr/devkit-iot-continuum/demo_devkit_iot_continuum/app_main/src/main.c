/*
 * Copyright (c) 2023 Lacroix Impulse
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// -------------------------------------------------------------------------------------------------------- //
//
//                            INCLUDED FILES
//
// -------------------------------------------------------------------------------------------------------- //

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>
#include "bsp.h"
#include "bsp_modem.h"
#include "bsp_bme280.h"
#include "bsp_inertial.h"

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL CONSTANTS
//
// -------------------------------------------------------------------------------------------------------- //

/// @brief Sample name
#define CAC_SAMPLE_NAME      "demo_devkit"
/// @brief Project name
#define CAC_PROJECT_NAME     "devkit_iot_continuum"
/// @brief Software version
#define CAC_SOFTWARE_VERSION "V0.1.0"
/// @brief Switcom gpio node
#define SWITCHCOM_NODE    DT_ALIAS(switchcom)


// -------------------------------------------------------------------------------------------------------- //
//
//                            MACRO DECLARATION
//
// -------------------------------------------------------------------------------------------------------- //

/// @brief Registering sample_modem for log
LOG_MODULE_REGISTER(demo_devkit, CONFIG_DEMO_DEVKIT_LOG_LEVEL);

// -------------------------------------------------------------------------------------------------------- //
//
//                         LOCAL TYPE DEFINITIONS AND DATA STRUCTURES
//
// -------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL VARIABLES
//
// -------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL FUNCTIONS DECLARATION
//
// -------------------------------------------------------------------------------------------------------- //

// Led example
static void LedExample(void);

// BME280 example
static void BME280Example(void);

// Inertial module example
static void LSM6DSOExample(void);

// Modem example
static void ModemExample(void);

// -------------------------------------------------------------------------------------------------------- //
//
//                            EXTERNAL FUNCTIONS DEFINITION
//
// -------------------------------------------------------------------------------------------------------- //

void main(void)
{
   LOG_DBG(" ");
   LOG_DBG("**************************************");
   LOG_DBG("***** DevKit Iot Continuuum Demo *****");
   LOG_DBG("**************************************\n");

   // LED Example 
   // It shows how to use the led and at the same time the gpio on the board.
   // NB : Every GPIO is already declared in the device three file (.dts)          
   LedExample();

   // BME280 Example (Pression, Temperature and humidity)
   // It shows how to use the BSP API for BME280.
   BME280Example();


   // LSM6DSO Example (Inertial and rotation)
   // It shows how to use the BSP API for LSM6DSO.
   LSM6DSOExample();

   // Modem Example
   // WARNING : you need to modify the file bsp_modem_conf.h (in subsys/bsp/modem/inc) to fit your need.
   // -> You can modify BSP_Modem function to fit your needs as it actually fits for http/https connection.
   // -> The BSP_MODEM rely on hl7812.c and hl7812.h (in drivers/modem/hl7812) which is the driver of HL7812.
   // -> In order to use HL7812 your own way, your BSP have to rely on this driver.
   // -> In our example, the modem simply realize a http get to "www.google.com/" which retrieve the home page of google.
   // -> Uncomment the line "# CONFIG_MODEM_LOG_LEVEL_DBG=y" in the "prj.conf" file to see all the modem logs (useful to debug)
   // but a lot of logs.
   ModemExample();

   // You can discuss directly via AT command with HL7812 if you uncomment this 3 lines (but you will not see Application Log)
   // All the AT Command are describes in the manufacturer document:
   // (https://source.sierrawireless.com/resources/airprime/software/hl78xx_at_commands_interface_guide/)

   //const struct gpio_dt_spec cs_SwitchComSpec                    = GPIO_DT_SPEC_GET(SWITCHCOM_NODE, gpios);
   //gpio_pin_configure_dt(&cs_SwitchComSpec, GPIO_OUTPUT);
   //gpio_pin_set_dt(&cs_SwitchComSpec, 1);

   while(1)
   {
      //Sleep for one second to let shell command running
      k_sleep(K_MSEC(1000));
   }

   return;
}

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL FUNCTION DEFINITIONS
//
// -------------------------------------------------------------------------------------------------------- //


static void LedExample(void)
{
   LOG_DBG("Led example\n");

   //Configure red LED
   const struct gpio_dt_spec cs_RedLedExt = GPIO_DT_SPEC_GET(DT_ALIAS(ledredext), gpios);
   gpio_pin_configure_dt(&cs_RedLedExt, GPIO_OUTPUT);

   //Configure green LED
   const struct gpio_dt_spec cs_GreenLedExt = GPIO_DT_SPEC_GET(DT_ALIAS(ledgreenext), gpios);
   gpio_pin_configure_dt(&cs_GreenLedExt, GPIO_OUTPUT);

   //Configure blue LED
   const struct gpio_dt_spec cs_BlueLedExt = GPIO_DT_SPEC_GET(DT_ALIAS(ledblueext), gpios);
   gpio_pin_configure_dt(&cs_BlueLedExt, GPIO_OUTPUT);

   LOG_DBG("-> Red LED for 3 seconds");
   gpio_pin_set_dt(&cs_RedLedExt, 1);
   gpio_pin_set_dt(&cs_GreenLedExt, 0);
   gpio_pin_set_dt(&cs_BlueLedExt, 0);
   k_sleep(K_MSEC(3000));

   LOG_DBG("-> Green LED for 3 seconds");
   gpio_pin_set_dt(&cs_RedLedExt, 0);
   gpio_pin_set_dt(&cs_GreenLedExt, 1);
   gpio_pin_set_dt(&cs_BlueLedExt, 0);
   k_sleep(K_MSEC(3000));

   LOG_DBG("-> Blue LED for 3 seconds\n");
   gpio_pin_set_dt(&cs_RedLedExt, 0);
   gpio_pin_set_dt(&cs_GreenLedExt, 0);
   gpio_pin_set_dt(&cs_BlueLedExt, 1);
   k_sleep(K_MSEC(3000));

   //switch to full white led
   gpio_pin_set_dt(&cs_RedLedExt, 1);
   gpio_pin_set_dt(&cs_GreenLedExt, 1);
   gpio_pin_set_dt(&cs_BlueLedExt, 1);
}

static void LSM6DSOExample(void)
{
   int32_t Accel_X           = 0;
   int32_t Accel_Y           = 0;
   int32_t Accel_Z           = 0;
   int32_t Rot_X             = 0;
   int32_t Rot_Y             = 0;
   int32_t Rot_Z             = 0;

   LOG_DBG("LSM6DSO example\n");

   if(BSP_INERTIAL_Init())
   {
      LOG_DBG("Fail to init LSM6DSO");
      return;
   }

   for(int i=0;i<5;i++)
   {

      if(BSP_INERTIAL_GetAcceleration(&Accel_X,&Accel_Y,&Accel_Z))
      {
         LOG_DBG("Fail to get Acceleration");
      }
      if(BSP_INERTIAL_GetGyroscope(&Rot_X,&Rot_Y,&Rot_Z))
      {
         LOG_DBG("Fail to get Rotation");
      }

      LOG_DBG(" Fetch LSM6DSO n°%d ",i+1);
      LOG_DBG(" Acceleration X:%d, Acceleration Y:%d , Acceleration Z:%d ", Accel_X,Accel_Y,Accel_Z);
      LOG_DBG(" Rotation X:%d, Rotation Y:%d , Rotation Z:%d\n", Rot_X,Rot_Y,Rot_Z);

      k_sleep(K_MSEC(2000));
   }

   BSP_INERTIAL_Deinit();

   return;
}

static void BME280Example(void)
{
   int32_t i32_Temperature   = 0;
   int32_t i32_Pression      = 0;
   int32_t i32_Humidity      = 0;

   LOG_DBG("BME280 example\n");

   if(BSP_BME280_Init())
   {
      LOG_DBG("Fail to init BME280");
      return;
   }

   for(int i=0;i<5;i++)
   {

      if(BSP_BME280_GetTemperature(&i32_Temperature))
      {
         LOG_DBG("Fail to get Temperature");
      }
      if(BSP_BME280_GetPression(&i32_Pression))
      {
         LOG_DBG("Fail to get Temperature");
      }
      if(BSP_BME280_GetHumidity(&i32_Humidity))
      {
         LOG_DBG("Fail to get Temperature");
      }
      LOG_DBG(" Fetch BME280 n°%d ",i+1);
      LOG_DBG(" Temperature BME280 %d ", i32_Temperature);
      LOG_DBG(" Pression BME280 %d ", i32_Pression);
      LOG_DBG(" Humidity BME280 %d \n", i32_Humidity);

      k_sleep(K_MSEC(2000));
   }

   BSP_BME280_Deinit();
}

static void ModemExample(void)
{
   BSP_MODEM_ConnectionState_e ModemStatus = BSP_MODEM_NETWORK_WAITING_FOR_CONNECTION;
   char pc_Data[4092] = {0};
   int LoopLimit = 0;

   LOG_DBG("Modem example\n");

   //Initialize the Modem
   if(BSP_MODEM_Init())
   {
      LOG_DBG("Fail to init modem hl7812");
   }

   while(ModemStatus != BSP_MODEM_NETWORK_CONNECTED)
   {
      k_sleep(K_MSEC(15000));
      LOG_DBG("Modem try to connect");

      // Create http connection with www.google.com (ipv4))
      BSP_MODEM_Connect(&ModemStatus);
      
      LoopLimit++;
      if (LoopLimit == 10)
      {
         LOG_DBG("Modem didn't connect to www.google.com");
         LOG_DBG("End of DevKit Demo");
         return;
      }
   }

   // Get the full home page of google ("www.google.com/") (in the logs)
   // In this demo, act like a ping.
   if(BSP_MODEM_Get(pc_Data,"/"))
   {
      LOG_DBG("Fail HTTP Get");
   }
}