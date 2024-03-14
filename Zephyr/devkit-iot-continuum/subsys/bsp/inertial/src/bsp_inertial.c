// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   BSP for the inertial module LSM6DSO
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
#include "bsp_inertial.h"

// -------------------------------------------------------------------------------------------------------- //
//
//                            MACRO DECLARATION
//
// -------------------------------------------------------------------------------------------------------- //

/// @brief Registering bsp_inertial for log
LOG_MODULE_REGISTER(bsp_inertial, CONFIG_BSP_INERTIAL_LOG_LEVEL);

#define BSP_INERTIAL_SAMPLING_FREQUENCY_HERTZ 12

// -------------------------------------------------------------------------------------------------------- //
//
//                         LOCAL TYPE DEFINITIONS AND DATA STRUCTURES
//
// -------------------------------------------------------------------------------------------------------- //

// Structure that holds variables of inertial module
typedef struct
{
   /// @brief Accelerometer output data rate structure.
   struct sensor_value s_OdrAttrAccel;
   /// @brief Gyroscope output data rate structure.
   struct sensor_value s_OdrAttrGyro;
   /// @brief Acceleration data structure.
   struct sensor_value s_AccelXYZ[3];
   /// @brief Gyroscope data structure.
   struct sensor_value s_GyroXYZ[3];
   /// @brief Temperature data structure.
   struct sensor_value s_Temperature;
} InertialContext_s;

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL VARIABLES
//
// -------------------------------------------------------------------------------------------------------- //

// Declaration of the inertial context structure
static InertialContext_s l_s_InertialContext;

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL CONSTANTS
//
// -------------------------------------------------------------------------------------------------------- //

// Initialization of the constant and static device structure
static const struct device *const l_cps_Lsm6dsoxDevice = DEVICE_DT_GET_ONE(st_lsm6dso);

// --------------------------------------------------------------------------------------------------------
//
//
//                            LOCAL FUNCTIONS DECLARATION
//
// --------------------------------------------------------------------------------------------------------

/**
 * @internal
 *
 * @brief Convert the value contained in the sensor_value structure for acceleration and gyroscope values into
 *        an int32_t with an accuracy of 0.001
 *
 * @param i_ps_SensorVal Pointer to the sensor_value structure to convert
 *
 * @return Sensor value in an int32_t
 */
static int32_t InertialSensorValueToInt32T(struct sensor_value *i_ps_SensorVal);

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

BSP_Ret_e BSP_INERTIAL_Init(void)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   // Checking if inertial module is ready
   if(true != device_is_ready(l_cps_Lsm6dsoxDevice))
   {
      LOG_DBG("\nError: Device \"%s\" is not ready; "
              "check the driver initialization logs for errors.\n",
              l_cps_Lsm6dsoxDevice->name);
      e_RetVal = BSP_RET_ERROR;
   }

   // Set accel sampling frequency to 12 Hz
   l_s_InertialContext.s_OdrAttrAccel.val1 = BSP_INERTIAL_SAMPLING_FREQUENCY_HERTZ;
   l_s_InertialContext.s_OdrAttrAccel.val2 = 0;

   if(0 != sensor_attr_set(l_cps_Lsm6dsoxDevice,
                                       SENSOR_CHAN_ACCEL_XYZ,
                                       SENSOR_ATTR_SAMPLING_FREQUENCY,
                                       &l_s_InertialContext.s_OdrAttrAccel))
   {
      LOG_DBG("LSM6DSO attr set fail");
      e_RetVal = BSP_RET_ERROR;
   }

   // Set gyroscope sampling frequency to 12 Hz
   l_s_InertialContext.s_OdrAttrGyro.val1 = BSP_INERTIAL_SAMPLING_FREQUENCY_HERTZ;
   l_s_InertialContext.s_OdrAttrGyro.val2 = 0;

   if(0 != sensor_attr_set(l_cps_Lsm6dsoxDevice,
                                       SENSOR_CHAN_GYRO_XYZ,
                                       SENSOR_ATTR_SAMPLING_FREQUENCY,
                                       &l_s_InertialContext.s_OdrAttrGyro))
   {
      LOG_DBG("LSM6DSO attr set fail");
      e_RetVal = BSP_RET_ERROR;
   }

   if(e_RetVal == BSP_RET_SUCCESS)
   {
      LOG_DBG("Inertial module LSM6DSO Init success");
   }
   else
   {
      LOG_DBG("Inertial module LSM6DSO Init failed");
   }

   return e_RetVal;
}

BSP_Ret_e BSP_INERTIAL_GetAcceleration(int32_t *o_pi32_X, int32_t *o_pi32_Y, int32_t *o_pi32_Z)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   if((o_pi32_X == NULL) || (o_pi32_Y == NULL) || (o_pi32_Z == NULL))
   {
      LOG_DBG("%s: NULL POINTER", __FUNCTION__);
      return BSP_RET_ERROR;
   }

   // LSM6DSO accel
   if(0 != sensor_sample_fetch_chan(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_ACCEL_XYZ))
   {
      LOG_DBG("LSM6DSO data fetch fail");
      e_RetVal = BSP_RET_ERROR;
   }
   if(sensor_channel_get(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_ACCEL_X, &l_s_InertialContext.s_AccelXYZ[0]))
   {
      LOG_DBG("LSM6DSO data get fail");
      e_RetVal = BSP_RET_ERROR;
   }
   if(sensor_channel_get(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_ACCEL_Y, &l_s_InertialContext.s_AccelXYZ[1]))
   {
      LOG_DBG("LSM6DSO data get fail");
      e_RetVal = BSP_RET_ERROR;
   }
   if(sensor_channel_get(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_ACCEL_Z, &l_s_InertialContext.s_AccelXYZ[2]))
   {
      LOG_DBG("LSM6DSO data get fail");
      e_RetVal = BSP_RET_ERROR;
   }

   if(e_RetVal == BSP_RET_SUCCESS)
   {
      *o_pi32_X = InertialSensorValueToInt32T(&l_s_InertialContext.s_AccelXYZ[0]);
      *o_pi32_Y = InertialSensorValueToInt32T(&l_s_InertialContext.s_AccelXYZ[1]);
      *o_pi32_Z = InertialSensorValueToInt32T(&l_s_InertialContext.s_AccelXYZ[2]);
      LOG_DBG("Get acceleration values success");
   }
   else
   {
      LOG_DBG("Get acceleration values failed");
   }

   return e_RetVal;
}

BSP_Ret_e BSP_INERTIAL_GetGyroscope(int32_t *o_pi32_X, int32_t *o_pi32_Y, int32_t *o_pi32_Z)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   if((o_pi32_X == NULL) || (o_pi32_Y == NULL) || (o_pi32_Z == NULL))
   {
      LOG_DBG("%s: NULL POINTER", __FUNCTION__);
      return BSP_RET_ERROR;
   }

   // LSM6DSO gyro
   if(0 != sensor_sample_fetch_chan(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_GYRO_XYZ))
   {
      LOG_DBG("LSM6DSO data fetch fail");
      e_RetVal = BSP_RET_ERROR;
   }
   if(sensor_channel_get(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_GYRO_X, &l_s_InertialContext.s_GyroXYZ[0]))
   {
      LOG_DBG("LSM6DSO data get fail");
      e_RetVal = BSP_RET_ERROR;
   }
   if(sensor_channel_get(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_GYRO_Y, &l_s_InertialContext.s_GyroXYZ[1]))
   {
      LOG_DBG("LSM6DSO data get fail");
      e_RetVal = BSP_RET_ERROR;
   }
   if(sensor_channel_get(l_cps_Lsm6dsoxDevice, SENSOR_CHAN_GYRO_Z, &l_s_InertialContext.s_GyroXYZ[2]))
   {
      LOG_DBG("LSM6DSO data get fail");
      e_RetVal = BSP_RET_ERROR;
   }

   if(e_RetVal == BSP_RET_SUCCESS)
   {
      *o_pi32_X = InertialSensorValueToInt32T(&l_s_InertialContext.s_GyroXYZ[0]);
      *o_pi32_Y = InertialSensorValueToInt32T(&l_s_InertialContext.s_GyroXYZ[1]);
      *o_pi32_Z = InertialSensorValueToInt32T(&l_s_InertialContext.s_GyroXYZ[2]);
      LOG_DBG("Get gyroscope values success");
   }
   else
   {
      LOG_DBG("Get gyroscope values failed");
   }

   return e_RetVal;
}

BSP_Ret_e BSP_INERTIAL_Deinit(void)
{
   // Nothing to do for the moment

   LOG_DBG("Inertial module LSM6DSO Deinit success");

   return BSP_RET_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL FUNCTION DEFINITIONS
//
// -------------------------------------------------------------------------------------------------------- //

static int32_t InertialSensorValueToInt32T(struct sensor_value *i_ps_SensorVal)
{
   int32_t i32_Value;
   if(i_ps_SensorVal->val1 < 0)
   {
      i32_Value = (int32_t)i_ps_SensorVal->val1 * 1000 + (int32_t)((i_ps_SensorVal->val2 / 100 - 5) / 10);
   }
   else
   {
      i32_Value = (int32_t)i_ps_SensorVal->val1 * 1000 + (int32_t)((i_ps_SensorVal->val2 / 100 + 5) / 10);
   }
   return i32_Value;
}