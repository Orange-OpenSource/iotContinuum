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
#include "bsp.h"

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL CONSTANTS
//
// -------------------------------------------------------------------------------------------------------- //

/// @brief Sample name
#define CAC_SAMPLE_NAME      "demo_devkit switch HL7812"
/// @brief Project name
#define CAC_PROJECT_NAME     "devkit_iot_continuum"
/// @brief Software version
#define CAC_SOFTWARE_VERSION "V0.1.0"
/// @brief Switcom gpio node

#define SWITCHCOM_NODE    	DT_ALIAS(switchcom)
#define BUTTON_NODE    	  	DT_ALIAS(button)

#define SLEEP_TIME_MS		1

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET_OR(BUTTON_NODE, gpios, {0});
static const struct gpio_dt_spec switch_hl7812 = GPIO_DT_SPEC_GET(SWITCHCOM_NODE, gpios);
static struct gpio_callback button_cb_data;


void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{	
	gpio_pin_set_dt(&switch_hl7812, 1);
}

int main(void)
{
	printk(" ");
	printk("*********************************************");
	printk("***** Switch HL7812 Iot Continuuum Demo *****");
	printk("*********************************************\n");
	
	int ret;

	if (!gpio_is_ready_dt(&button)) {
		printk("Error: button device %s is not ready\n", button.port->name);
		return 0;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n", ret, button.port->name, button.pin);
		return 0;
	}	

	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n", ret, button.port->name, button.pin);
		return 0;
	}

	gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
	gpio_add_callback(button.port, &button_cb_data);

   // Configure switch HL7812 GPIO   
	ret = gpio_pin_configure_dt(&switch_hl7812, GPIO_OUTPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n", ret, switch_hl7812.port->name, switch_hl7812.pin);
		return 0;
	}	

	gpio_pin_set_dt(&switch_hl7812, 0);

	printk("Press the button to switch to HL7812 UART\n");
	while (true) {
		k_msleep(SLEEP_TIME_MS);
	}

	return 0;
}
