// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   Shell command for the INERTIAL MODULE LSM6DSO BSP
 */

// -------------------------------------------------------------------------------------------------------- //
//
//                            INCLUDED FILES
//
// -------------------------------------------------------------------------------------------------------- //

#include <ctype.h>
#include <stdlib.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>
#include "bsp_bme280.h"

// -------------------------------------------------------------------------------------------------------- //
//
//                            MACRO DECLARATION
//
// -------------------------------------------------------------------------------------------------------- //

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
//                            LOCAL CONSTANTS
//
// -------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL FUNCTIONS DECLARATION
//
// -------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------- //
//
//                            EXTERNAL FUNCTIONS DEFINITION
//
// -------------------------------------------------------------------------------------------------------- //

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL FUNCTION DEFINITIONS
//
// -------------------------------------------------------------------------------------------------------- //

/**
 * @brief "bsp_bme280 init" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void BSP_BME280_SHELL_Cmd_Init(const struct shell *i_cps_Shell, size_t i_z_Argc, char **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);

   if(i_z_Argc > 1)
   {
      shell_help(i_cps_Shell);
   }
   else
   {
      if(BSP_BME280_Init())
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: BME280 Init");
         return;
      }
      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: BME280 module Init");
   }

   return;
}

/**
 * @brief "bsp_bme280 GetTemperature" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void BSP_BME280_SHELL_Cmd_GetTemperature(const struct shell *i_cps_Shell,
                                                size_t              i_z_Argc,
                                                char              **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);

   int32_t i32_Temperature;

   if(i_z_Argc > 1)
   {
      shell_help(i_cps_Shell);
   }
   else
   {
      if(BSP_BME280_GetTemperature(&i32_Temperature))
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: BME280 Get Temperature");
         return;
      }
      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: Temperature:%d 0.1degC", i32_Temperature);
   }
   return;
}

/**
 * @brief "bsp_bme280 Deinit" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void BSP_INERTIAL_SHELL_Cmd_DeInit(const struct shell *i_cps_Shell, size_t i_z_Argc, char **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);

   if(i_z_Argc > 1)
   {
      shell_help(i_cps_Shell);
   }
   else
   {
      if(BSP_BME280_Deinit())
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: BME280 Deinit");
         return;
      }
      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: BME280 module Deinit");
   }

   return;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
        bsp_bme280_subcommands,
        SHELL_CMD(init, NULL, "Initialize BME280  module\n", BSP_BME280_SHELL_Cmd_Init),
        SHELL_CMD(get_temperature,
                  NULL,
                  "Get temperature value (in 0.1degC) from BME280 module\n",
                  BSP_BME280_SHELL_Cmd_GetTemperature),
        SHELL_CMD(deinit, NULL, "Deinitialize BME280 module", BSP_BME280_SHELL_Cmd_DeInit),
        SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(bsp_bme280, &bsp_bme280_subcommands, "bsp_bme280 commands", NULL);