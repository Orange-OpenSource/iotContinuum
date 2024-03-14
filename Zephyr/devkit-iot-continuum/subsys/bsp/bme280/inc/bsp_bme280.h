// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

#ifndef BSP_BME280_H
#define BSP_BME280_H

/**
 * @file
 * @brief   BSP header for BME280 multisensor module
 */

#include <zephyr/kernel.h>
#include <bsp.h>

// -------------------------------------------------------------------------------------------------------- //
//
//                            GLOBAL CONSTANTS
//
// -------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------- //
//
//                            TYPES DEFINITIONS AND DATA STRUCTURES
//
// -------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------- //
//
//                            EXTERNAL FUNCTION PROTOTYPES
//
// -------------------------------------------------------------------------------------------------------- //

/**
 * @brief Initialize BME280 multisensor module
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_BME280_Init(void);

/**
 * @brief Get temperature value (in 0,1 degC) from BME280 module
 *
 * @param o_pi32_Temperature_degC Temperature (unit = 0.1 degC)
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_BME280_GetTemperature(int32_t *o_pi32_Temperature_degC);

/**
 * @brief Get pression value (in mBar or hPa) from BME280 module
 *
 * @param o_pi32_Pression_mBar pression (unit = mBar or hPa)
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_BME280_GetPression(int32_t *o_pi32_Pression_mBar);

/**
 * @brief Get humidity value (percentage) from BME280 module
 *
 * @param o_pi32_Humidity humidity temperature in degree (unit = 0.1 degC)
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_BME280_GetHumidity(int32_t *o_pi32_Humidity);

/**
 * @brief Deinitialize LSM6DSO inertial module
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_BME280_Deinit(void);

#endif // BSP_INERTIAL_H
