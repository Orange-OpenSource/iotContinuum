#ifndef BSP_INERTIAL_H
#define BSP_INERTIAL_H

// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   BSP header for LSM6DSO inertial module
 */

#include <zephyr/kernel.h>
#include "bsp.h"

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
 * @brief Initialize LSM6DSO inertial module
 *
 * @return void
 */
BSP_Ret_e BSP_INERTIAL_Init(void);

/**
 * @brief Get acceleration values (in mm/s^2) from the accelerometer of LSM6DSO inertial module
 *
 * @param o_pi32_X Acceleration on X axis
 * @param o_pi32_Y Acceleration on Y axis
 * @param o_pi32_Z Acceleration on Z axis
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_INERTIAL_GetAcceleration(int32_t *o_pi32_X, int32_t *o_pi32_Y, int32_t *o_pi32_Z);

/**
 * @brief Get rotation values (in mrad/s) from the gyroscope of LSM6DSO inertial module
 *
 * @param o_pi32_X rotation on X axis
 * @param o_pi32_Y rotation on Y axis
 * @param o_pi32_Z rotation on Z axis
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_INERTIAL_GetGyroscope(int32_t *o_pi32_X, int32_t *o_pi32_Y, int32_t *o_pi32_Z);

/**
 * @brief Deinitialize LSM6DSO inertial module
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_INERTIAL_Deinit(void);

#endif // BSP_INERTIAL_H
