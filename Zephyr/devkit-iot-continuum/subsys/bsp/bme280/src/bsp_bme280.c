// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   BSP for the multisensor module BME280
 */

// -------------------------------------------------------------------------------------------------------- //
//
//                            INCLUDED FILES
//
// -------------------------------------------------------------------------------------------------------- //

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "bsp_bme280.h"

// -------------------------------------------------------------------------------------------------------- //
//
//                            MACRO DECLARATION
//
// -------------------------------------------------------------------------------------------------------- //

/// @brief Registering bsp_bme280 for log
LOG_MODULE_DECLARE(bsp_bme280, CONFIG_BSP_BME280_LOG_LEVEL);

// -------------------------------------------------------------------------------------------------------- //
//
//                         LOCAL TYPE DEFINITIONS AND DATA STRUCTURES
//
// -------------------------------------------------------------------------------------------------------- //

// Structure that holds variables of bme280 module
typedef struct
{
   /// @brief Pression output data structure.
   struct sensor_value s_Pression;
   /// @brief Humidity output data structure.
   struct sensor_value s_Humidity;
   /// @brief Temperature data structure.
   struct sensor_value s_Temperature;
} Bme280Context_s;

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL VARIABLES
//
// -------------------------------------------------------------------------------------------------------- //

// Declaration of the inertial context structure
static Bme280Context_s l_s_Bme280Context;

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL CONSTANTS
//
// -------------------------------------------------------------------------------------------------------- //

// Initialization of the constant and static device structure
static const struct device *const l_cps_BME280Device = DEVICE_DT_GET_ONE(bosch_bme280);

// --------------------------------------------------------------------------------------------------------
//
//
//                            LOCAL FUNCTIONS DECLARATION
//
// --------------------------------------------------------------------------------------------------------

/**
 * @internal
 *
 * @brief Convert the temperature value contained in the sensor_value structure into an int32_t with an
 * accuracy of 0.1 -> Example : an actual temperature of 28,5 C° will return 285.
 *
 * @param i_ps_SensorVal Pointer to the sensor_value structure to convert
 *
 * @return Sensor value in an int32_t
 */
static int32_t TemperatureValueToInt32T(struct sensor_value *i_ps_SensorVal);

/**
 * @internal
 *
 * @brief Convert the pression value contained in the sensor_value structure into an int32_t with an accuracy
 * of 0.001 bar
 *
 *
 * @param i_ps_SensorVal Pointer to the sensor_value structure to convert
 *
 * @return Sensor value in an int32_t
 */
static int32_t PressionValueToInt32T(struct sensor_value *i_ps_SensorVal);

/**
 * @internal
 *
 * @brief Convert humidity value contained in the sensor_value structure into an int32_t with an accuracy of 1
 *
 * @param i_ps_SensorVal Pointer to the sensor_value structure to convert
 *
 * @return Sensor value in an uint8_t
 */
static int32_t HumidityValueToInt32T(struct sensor_value *i_ps_SensorVal);

// --------------------------------------------------------------------------------------------------------
//
//
//                            SYSTEM INITIALISATION FUNCTION
//
// --------------------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------------------
//
//
//                            EXTERNAL FUNCTIONS DEFINITION
//
// --------------------------------------------------------------------------------------------------------

BSP_Ret_e BSP_BME280_Init(void)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   // Check is the device exist
   if(l_cps_BME280Device == NULL)
   {
      /* No such node, or the node does not have status "okay". */
      LOG_DBG("\nError: no device found.\n");
      e_RetVal = BSP_RET_ERROR;
   }

   // Checking if inertial module is ready
   if(!device_is_ready(l_cps_BME280Device))
   {
      LOG_DBG("\nError: Device \"%s\" is not ready; "
              "check the driver initialization logs for errors.\n",
              l_cps_BME280Device->name);
      e_RetVal = BSP_RET_ERROR;
   }

   if(e_RetVal == BSP_RET_SUCCESS)
   {
      LOG_DBG("BME280 module init success");
   }
   else
   {
      LOG_DBG("BME280 module init failed");
   }

   return e_RetVal;
}

BSP_Ret_e BSP_BME280_GetTemperature(int32_t *o_pi32_Temperature_degC)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   if(o_pi32_Temperature_degC == NULL)
   {
      LOG_DBG("%s: NULL POINTER", __FUNCTION__);
      return BSP_RET_ERROR;
   }

   // BME280 fetch temperature
   if(sensor_sample_fetch_chan(l_cps_BME280Device, SENSOR_CHAN_AMBIENT_TEMP) != 0)
   {
      LOG_DBG("BME280 data fetch fail");
      e_RetVal = BSP_RET_ERROR;
   }

   // BME280 get temperature
   if(sensor_channel_get(l_cps_BME280Device, SENSOR_CHAN_AMBIENT_TEMP, &l_s_Bme280Context.s_Temperature) != 0)
   {
      LOG_DBG("BME280 data get fail");
      e_RetVal = BSP_RET_ERROR;
   }

   if(e_RetVal == BSP_RET_SUCCESS)
   {
      *o_pi32_Temperature_degC = TemperatureValueToInt32T(&l_s_Bme280Context.s_Temperature);
      LOG_DBG("Get temperature value success");
   }
   else
   {
      LOG_DBG("Get temperature value failed");
   }
   
   return e_RetVal;
}

BSP_Ret_e BSP_BME280_GetPression(int32_t *o_pi32_Pression_mBar)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   if(o_pi32_Pression_mBar == NULL)
   {
      LOG_DBG("%s: NULL POINTER", __FUNCTION__);
      return BSP_RET_ERROR;
   }

   // BME280 fetch pression
   if(sensor_sample_fetch_chan(l_cps_BME280Device, SENSOR_CHAN_PRESS) != 0)
   {
      LOG_DBG("BME280 data fetch fail");
      e_RetVal = BSP_RET_ERROR;
   }

   // BME280 get pression
   if(sensor_channel_get(l_cps_BME280Device, SENSOR_CHAN_PRESS, &l_s_Bme280Context.s_Pression) != 0)
   {
      LOG_DBG("BME280 data get fail");
      e_RetVal = BSP_RET_ERROR;
   }

   if(e_RetVal == BSP_RET_SUCCESS)
   {
      *o_pi32_Pression_mBar = PressionValueToInt32T(&l_s_Bme280Context.s_Pression);
      LOG_DBG("Get pression value success");
   }
   else
   {
      LOG_DBG("Get pression value failed");
   }

   return e_RetVal;
}

BSP_Ret_e BSP_BME280_GetHumidity(int32_t *o_pi32_Humidity)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;
   
   if(o_pi32_Humidity == NULL)
   {
      LOG_DBG("%s: NULL POINTER", __FUNCTION__);
      return BSP_RET_ERROR;
   }

   // BME280 fetch humidity
   if(sensor_sample_fetch_chan(l_cps_BME280Device, SENSOR_CHAN_HUMIDITY) != 0)
   {
      LOG_DBG("BME280 data fetch fail");
      e_RetVal = BSP_RET_ERROR;
   }

   // BME280 get humidity
   if(sensor_channel_get(l_cps_BME280Device, SENSOR_CHAN_HUMIDITY, &l_s_Bme280Context.s_Humidity) != 0)
   {
      LOG_DBG("BME280 data get fail");
      e_RetVal = BSP_RET_ERROR;
   }

   if(e_RetVal == BSP_RET_SUCCESS)
   {
      *o_pi32_Humidity = HumidityValueToInt32T(&l_s_Bme280Context.s_Humidity);
      LOG_DBG("Get humidity value success");
   }
   else
   {
      LOG_DBG("Get humidity value failed");
   }

   return e_RetVal;
}

BSP_Ret_e BSP_BME280_Deinit(void)
{
   // Nothing to do for the moment

   LOG_DBG("BME280 module deinit success");

   return BSP_RET_SUCCESS;;
}

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL FUNCTION DEFINITIONS
//
// -------------------------------------------------------------------------------------------------------- //

static int32_t TemperatureValueToInt32T(struct sensor_value *i_ps_SensorVal)
{
   int32_t i32_Value;

   if(i_ps_SensorVal->val1 < 0)
   {
      i32_Value = (int32_t)i_ps_SensorVal->val1 * 10 + (int32_t)((i_ps_SensorVal->val2 / 10000 - 5) / 10);
   }
   else
   {
      i32_Value = (int32_t)i_ps_SensorVal->val1 * 10 + (int32_t)((i_ps_SensorVal->val2 / 10000 + 5) / 10);
   }
   return i32_Value;
}

static int32_t PressionValueToInt32T(struct sensor_value *i_ps_SensorVal)
{
   int32_t i32_Value;

   i32_Value = (int32_t)i_ps_SensorVal->val1 * 10 + (int32_t)((i_ps_SensorVal->val2 / 10000 + 5) / 10);

   return i32_Value;
}

static int32_t HumidityValueToInt32T(struct sensor_value *i_ps_SensorVal)
{
   return (int32_t)(i_ps_SensorVal->val1 + (i_ps_SensorVal->val2 / 100000 + 5) / 10);
}