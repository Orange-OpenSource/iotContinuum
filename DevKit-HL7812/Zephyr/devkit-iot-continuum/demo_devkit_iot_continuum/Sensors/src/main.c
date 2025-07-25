/*
 * Copyright (c) 2024 Orange
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

// -------------------------------------------------------------------------------------------------------- //
//
//                            EXTERNAL FUNCTIONS DEFINITION
//
// -------------------------------------------------------------------------------------------------------- //

void main(void)
{
   LOG_DBG(" ");
   LOG_DBG("**********************************************");
   LOG_DBG("***** DevKit Iot Continuuum Sensors Demo *****");
   LOG_DBG("**********************************************\n");

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
   k_sleep(K_MSEC(1000));

   LOG_DBG("-> Green LED for 3 seconds");
   gpio_pin_set_dt(&cs_RedLedExt, 0);
   gpio_pin_set_dt(&cs_GreenLedExt, 1);
   gpio_pin_set_dt(&cs_BlueLedExt, 0);
   k_sleep(K_MSEC(1000));

   LOG_DBG("-> Blue LED for 3 seconds\n");
   gpio_pin_set_dt(&cs_RedLedExt, 0);
   gpio_pin_set_dt(&cs_GreenLedExt, 0);
   gpio_pin_set_dt(&cs_BlueLedExt, 1);
   k_sleep(K_MSEC(1000));

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

      LOG_DBG(" Fetch LSM6DSO number%d ",i+1);
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
      LOG_DBG(" Fetch BME280 number %d ",i+1);
      LOG_DBG(" Temperature BME280 %d ", i32_Temperature);
      LOG_DBG(" Pression BME280 %d ", i32_Pression);
      LOG_DBG(" Humidity BME280 %d \n", i32_Humidity);

      k_sleep(K_MSEC(2000));
   }

   BSP_BME280_Deinit();
}
