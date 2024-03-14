// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   Shell command for BSP system

 */

// -------------------------------------------------------------------------------------------------------- //
//
//                            INCLUDED FILES
//
// -------------------------------------------------------------------------------------------------------- //
#include <stdlib.h>
#include <ctype.h>
#include <zephyr/shell/shell.h>
#include "bsp_system.h"

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
 * @brief "bsp_system GetUptimeSec" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void
        BSP_SYSTEM_SHELL_Cmd_GetUptimeSec(const struct shell *i_cps_Shell, size_t i_z_Argc, char **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);
   uint32_t ui32_Uptime_sec;

   if(i_z_Argc == 1)
   {
      if(BSP_SYSTEM_GetUptimeSec(&ui32_Uptime_sec))
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: Get Uptime in seconds");
         return;
      }
      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: uptime = %u sec", ui32_Uptime_sec);
   }
   else
   {
      shell_help(i_cps_Shell);
   }

   return;

}

/**
 * @brief "bsp_system GetUptimeMs" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void
        BSP_SYSTEM_SHELL_Cmd_GetUptimeMs(const struct shell *i_cps_Shell, size_t i_z_Argc, char **i_ppc_Argv)
{
   ARG_UNUSED(i_ppc_Argv);
   uint64_t ui64_Uptime_ms;

   if(i_z_Argc == 1)
   {
      if(BSP_SYSTEM_GetUptimeMs(&ui64_Uptime_ms))
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: Get Uptime in milliseconds");
         return;
      }
      shell_fprintf(i_cps_Shell, SHELL_INFO, "SUCCESS: uptime = %llu ms", ui64_Uptime_ms);
   }
   else
   {
      shell_help(i_cps_Shell);
   }

   return;

}

/**
 * @brief "bsp_system Reboot" command implementation.
 *
 * @note Command usage is documented in the shell with "$ command help"
 */
static void BSP_SYSTEM_SHELL_Cmd_Reboot(const struct shell *i_cps_Shell, size_t i_z_Argc, char **i_ppc_Argv)
{
   uint32_t ui32_Delay_ms = 100;

   ARG_UNUSED(i_ppc_Argv);

   if(i_z_Argc == 2)
   {
      ui32_Delay_ms = strtoul(i_ppc_Argv[1], NULL, 10);
      shell_fprintf(i_cps_Shell, SHELL_INFO, "Do a software reset in %u ms", ui32_Delay_ms);

      if(BSP_SYSTEM_Reboot(ui32_Delay_ms))
      {
         shell_fprintf(i_cps_Shell, SHELL_ERROR, "FAILED: Do a software reset");
      }
   }
   else
   {
      shell_help(i_cps_Shell);
   }
   return;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
        bsp_system_subcommands,
        SHELL_CMD(uptime_sec, NULL, "Get Uptime in seconds\n", BSP_SYSTEM_SHELL_Cmd_GetUptimeSec),
        SHELL_CMD(uptime_ms, NULL, "Get Uptime in milliseconds\n", BSP_SYSTEM_SHELL_Cmd_GetUptimeMs),
        SHELL_CMD(reboot,
                  NULL,
                  "Do a software reset\n"
                  "bsp_system reboot <delay_ms>",
                  BSP_SYSTEM_SHELL_Cmd_Reboot),
        SHELL_SUBCMD_SET_END);
SHELL_CMD_REGISTER(bsp_system, &bsp_system_subcommands, "bsp_system commands", NULL);