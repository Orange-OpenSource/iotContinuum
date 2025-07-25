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
#include "bsp_inertial.h"

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
 * @brief "bsp_inertial Init" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void BSP_INERTIAL_SHELL_Cmd_Init(const struct shell *i_cps_Shell, size_t i_z_Argc, char **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);

   if(i_z_Argc > 1)
   {
      shell_help(i_cps_Shell);
   }
   else
   {
      if(BSP_INERTIAL_Init())
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: Inertial module LSM6DSO Init");
         return;
      }

      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: Inertial module LSM6DSO Init ");
   }

   return;
}

/**
 * @brief "bsp_inertial GetAcceleration" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void BSP_INERTIAL_SHELL_Cmd_GetAcceleration(const struct shell *i_cps_Shell,
                                                   size_t              i_z_Argc,
                                                   char              **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);

   int32_t i32_XAxis;
   int32_t i32_YAxis;
   int32_t i32_ZAxis;

   if(i_z_Argc > 1)
   {
      shell_help(i_cps_Shell);
   }
   else
   {
      if(BSP_INERTIAL_GetAcceleration(&i32_XAxis, &i32_YAxis, &i32_ZAxis))
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: Inertial module LSM6DSO Get acceleration values");
         return;
      }

      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: Acceleration: X = %d mm/s^2, Y = %d mm/s^2, Z = %d mm/s^2",
                i32_XAxis,
                i32_YAxis,
                i32_ZAxis);
   }

   return;
}

/**
 * @brief "bsp_inertial GetGyroscope" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void BSP_INERTIAL_SHELL_Cmd_GetGyroscope(const struct shell *i_cps_Shell,
                                                size_t              i_z_Argc,
                                                char              **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);

   int32_t i32_XAxis;
   int32_t i32_YAxis;
   int32_t i32_ZAxis;

   if(i_z_Argc > 1)
   {
      shell_help(i_cps_Shell);
   }
   else
   {
      if(BSP_INERTIAL_GetGyroscope(&i32_XAxis, &i32_YAxis, &i32_ZAxis))
      {
         shell_fprintf(i_cps_Shell, SHELL_ERR, "FAILED: Inertial module LSM6DSO Get rotation values");
         return;
      }

      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: Rotation: X = %d mrad/s^2, Y = %d mrad/s^2, Z = %d mrad/s^2",
                i32_XAxis,
                i32_YAxis,
                i32_ZAxis);
   }

   return;
}

/**
 * @brief "bsp_inertial Deinit" command implementation.
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
      if(BSP_INERTIAL_Deinit())
      {
         shell_fprintf(i_cps_Shell, SHELL_ERR, "FAILED: Inertial module LSM6DSO Deinit");
         return;
      }
      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: Inertial module LSM6DSO Deinit");
   }
   return;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
        bsp_inertial_subcommands,
        SHELL_CMD(init, NULL, "Initialize LSM6DSO inertial module\n", BSP_INERTIAL_SHELL_Cmd_Init),
        SHELL_CMD(get_acceleration,
                  NULL,
                  "Get acceleration values (in mm/s^2) from the accelerometer of LSM6DSO\n",
                  BSP_INERTIAL_SHELL_Cmd_GetAcceleration),
        SHELL_CMD(get_gyroscope,
                  NULL,
                  "Get rotation values (in mrad/s) from the gyroscope of LSM6DSO\n",
                  BSP_INERTIAL_SHELL_Cmd_GetGyroscope),
        SHELL_CMD(deinit, NULL, "Deinitialize LSM6DSO inertial module", BSP_INERTIAL_SHELL_Cmd_DeInit),
        SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(bsp_inertial, &bsp_inertial_subcommands, "bsp_inertial commands", NULL);