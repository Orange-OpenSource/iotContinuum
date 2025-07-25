#ifndef BSP_SYSTEM_H
#define BSP_SYSTEM_H

// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   BSP header for system services
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
 * @brief Get uptime in seconds
 *
 * @param o_pui32_Sec Pointer time from startup in seconds
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_SYSTEM_GetUptimeSec(uint32_t *o_pui32_Sec);

/**
 * @brief Get uptime in milli-seconds
 *
 * @param o_pui64_Ms Pointer time from startup in milliseconds
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_SYSTEM_GetUptimeMs(uint64_t *o_pui64_Ms);

/**
 * @brief Do a software reset
 *
 * @param i_ui32_Delay_ms Delay in ms before reboot system
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_SYSTEM_Reboot(uint32_t i_ui32_Delay_ms);

#endif // BSP_SYSTEM_H
