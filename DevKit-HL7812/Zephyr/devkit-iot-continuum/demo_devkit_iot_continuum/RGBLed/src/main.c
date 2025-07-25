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

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL CONSTANTS
//
// -------------------------------------------------------------------------------------------------------- //

/// @brief Sample name
#define CAC_SAMPLE_NAME      "demo_devkit led"
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


/* This code example shows how to control the RGB LED which is managed by the PCA9534 GPIO expander */

// -------------------------------------------------------------------------------------------------------- //
//
//                            EXTERNAL FUNCTIONS DEFINITION
//
// -------------------------------------------------------------------------------------------------------- //

void main(void)
{
   LOG_DBG(" ");
   LOG_DBG("**************************************");
   LOG_DBG("******** RGB test application ********");
   LOG_DBG("**************************************\n");

   // LED Example 
   // It shows how to use the led and at the same time the gpio on the board.
   // NB : Every GPIO is already declared in the device three file (.dts)          
   
   LedExample();
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

	while(true) {
	   LOG_DBG("-> Red LED for 500 ms");
	   gpio_pin_set_dt(&cs_RedLedExt, 1);
	   gpio_pin_set_dt(&cs_GreenLedExt, 0);
	   gpio_pin_set_dt(&cs_BlueLedExt, 0);
	   k_sleep(K_MSEC(500));

	   LOG_DBG("-> Green LED for 500 ms");
	   gpio_pin_set_dt(&cs_RedLedExt, 0);
	   gpio_pin_set_dt(&cs_GreenLedExt, 1);
	   gpio_pin_set_dt(&cs_BlueLedExt, 0);
	   k_sleep(K_MSEC(500));

	   LOG_DBG("-> Blue LED for 500 ms\n");
	   gpio_pin_set_dt(&cs_RedLedExt, 0);
	   gpio_pin_set_dt(&cs_GreenLedExt, 0);
	   gpio_pin_set_dt(&cs_BlueLedExt, 1);
	   k_sleep(K_MSEC(500));

	   //switch to full white led
	   gpio_pin_set_dt(&cs_RedLedExt, 1);
	   gpio_pin_set_dt(&cs_GreenLedExt, 1);
	   gpio_pin_set_dt(&cs_BlueLedExt, 1);
	}
}
