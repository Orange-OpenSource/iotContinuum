#ifndef BSP_MODEM_H
#define BSP_MODEM_H

// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   BSP header for modem module
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
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

///@brief Provides a type to report network state
typedef enum
{
   BSP_MODEM_NETWORK_WAITING_FOR_CONNECTION = 0,
   BSP_MODEM_NETWORK_CONNECTED,
   BSP_MODEM_NETWORK_ERROR,
} BSP_MODEM_ConnectionState_e;

// -------------------------------------------------------------------------------------------------------- //
//
//                            EXTERNAL FUNCTION PROTOTYPES
//
// -------------------------------------------------------------------------------------------------------- //

/**
 * @brief Initialize Modem
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_MODEM_Init(void);

/**
 * @brief Connect to network
 *
 * @param o_pe_State pointer on connection status
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_MODEM_Connect(BSP_MODEM_ConnectionState_e *o_pe_State);

/**
 * @brief Post sensor data to server
 *
 * @param i_cpui8_Payload pointer on payload
 *
 * @param i_cpui8_Url pointer on url path
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_MODEM_Post(char const *i_cpui8_Payload, char const *i_cpui8_Url);

/**
 * @brief Get data from server
 *
 * @param o_pui8_Recive pointer on recive msg
 *
 * @param i_cpui8_Url pointer on url path
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_MODEM_Get(char *o_pui8_Recive, char const *i_cpui8_Url);

/**
 * @brief Disconnect modem
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_MODEM_Disconnect(void);

/**
 * @brief Deinitialize modem
 *
 * @return BSP_RET_SUCCESS in case of success,
 *         BSP_RET_ERROR otherwise
 */
BSP_Ret_e BSP_MODEM_Deinit(void);

#endif // BSP_MODEM_H
