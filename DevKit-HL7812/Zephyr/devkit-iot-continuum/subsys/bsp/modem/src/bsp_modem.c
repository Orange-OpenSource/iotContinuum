// Copyright (C) Lacroix Impulse 2023 (France)
// SPDX-License-Identifier: Apache-2.0

/**
 * @file
 * @brief   BSP for the Sierra LTE Module HL7812
 */

// -------------------------------------------------------------------------------------------------------- //
//
//                            INCLUDED FILES
//
// -------------------------------------------------------------------------------------------------------- //

#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include "bsp_modem.h"
#include "bsp_modem_conf.h"
#include "hl7812.h"

// -------------------------------------------------------------------------------------------------------- //
//
//                            MACRO DECLARATION
//
// -------------------------------------------------------------------------------------------------------- //

/// @brief Registering bsp_modem_sierra for log
LOG_MODULE_REGISTER(bsp_modem_sierra, CONFIG_BSP_MODEM_LOG_LEVEL);

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

/// @brief Max HTTP header size
#define BSP_MODEM_SIERRA_MAX_HEADER_SIZE 256

// --------------------------------------------------------------------------------------------------------
//
//
//                            LOCAL FUNCTIONS DECLARATION
//
// --------------------------------------------------------------------------------------------------------

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

BSP_Ret_e BSP_MODEM_Init(void)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   /* Writing APN */
   if(mdm_hl7812_set_apn(l_cpc_Apn))
   {
      LOG_ERR("Fail to set apn");
      e_RetVal = BSP_RET_ERROR;
   }
   else
   {
      LOG_DBG("Writing APN: OK");
      LOG_DBG("Initialization of Sierra LTE Module HL7812 success");
   }

   return e_RetVal;

}

BSP_Ret_e BSP_MODEM_Connect(BSP_MODEM_ConnectionState_e *o_pe_State)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;
   int8_t i8_NetworkState = 0;

   if(o_pe_State == NULL)
   {
      LOG_ERR("%s: NULL POINTER", __FUNCTION__);
      return BSP_RET_ERROR;
   }

   i8_NetworkState = mdm_hl7812_get_network_state();

   if(i8_NetworkState == HL7812_UNABLE_TO_CONFIGURE)
   {
      *o_pe_State = BSP_MODEM_NETWORK_ERROR;
      LOG_DBG("HL7812_UNABLE_TO_CONFIGURE");
      e_RetVal = BSP_RET_ERROR;
   }
   else if(i8_NetworkState == HL7812_HOME_NETWORK)
   {
      LOG_DBG("Connected to HOME NETWORK");

      // Comment to realize a simple http get with google (not hhtps)

      // /* Send Certificate */
      // if(mdm_hl7812_send_certificate(l_cpc_Certificate))
      // {
      //    LOG_DBG("Configuration of Sierra LTE Module HL7812 failed (send certificate)");
      //    e_RetVal = BSP_RET_ERROR;
      // }
      // else
      // {
      //    LOG_DBG("Sending certificate: OK");
      //    /* Send sslcrypto */
      //    if(mdm_hl7812_send_sslcrypto())
      //    {
      //       LOG_DBG("Configuration of Sierra LTE Module HL7812 failed (send sslcrypto)");
      //       e_RetVal = BSP_RET_ERROR;
      //    }
      //    else
      //    {
      //       LOG_DBG("Sending ssl crypto conf: OK");
            /* Set HTTP config */
            if(mdm_hl7812_set_http_cfg(l_cpc_UrlDomain))
            {
               LOG_DBG("Configuration of Sierra LTE Module HL7812 failed ");
               e_RetVal = BSP_RET_ERROR;
            }
            else
            {
               LOG_DBG("Set HTTP config: OK");
               LOG_DBG("HTTP Connection of Sierra LTE Module HL7812 success");
               *o_pe_State = BSP_MODEM_NETWORK_CONNECTED;
            }
      //    }
      // }  
   }
   else
   {
      LOG_DBG("Waiting Connection of Sierra LTE Module HL7812");
      *o_pe_State = BSP_MODEM_NETWORK_WAITING_FOR_CONNECTION;
   }

   return e_RetVal;
}

BSP_Ret_e BSP_MODEM_Post(char const *i_cpui8_Payload, char const *i_cpui8_Url)
{
   BSP_Ret_e e_RetVal                                      = BSP_RET_SUCCESS;
   char  pc_DataHeader[BSP_MODEM_SIERRA_MAX_HEADER_SIZE] = {0};
   int32_t i32_JsonSize                                    = strlen(i_cpui8_Payload);

   // Send HTTP header
   snprintk(pc_DataHeader, sizeof(pc_DataHeader), BSP_MODEM_SIERRA_POST_HEADER, i32_JsonSize);

   LOG_DBG("%d", i32_JsonSize);
   LOG_DBG("%s", i_cpui8_Url);
   if(mdm_hl7812_send_http_header(pc_DataHeader))
   {
      LOG_DBG("Modem Post of Sierra LTE Module HL7812 failed (http header)");
      e_RetVal = BSP_RET_ERROR;
   }
   else
   {
      LOG_DBG("Send HTTP header: OK");
      // Send Data
      if(mdm_hl7812_send_http_post(i_cpui8_Url, i_cpui8_Payload))
      {
         LOG_DBG("Modem Post of Sierra LTE Module HL7812 failed");
         e_RetVal = BSP_RET_ERROR;
      }
      else
      {
         LOG_DBG("Post data success");
      }
   }
   return e_RetVal;
}

BSP_Ret_e BSP_MODEM_Get(char *o_pui8_Recive, char const *i_cpui8_Url)
{
   BSP_Ret_e e_RetVal                                     = BSP_RET_SUCCESS;
   //char pc_DataHeader[BSP_MODEM_SIERRA_MAX_HEADER_SIZE] = {0};

   /* Disable Header fr simple http get for demo*/
   // Send HTTP header
   // snprintk(pc_DataHeader, sizeof(pc_DataHeader), BSP_MODEM_SIERRA_GET_HEADER);
   
   // if(mdm_hl7812_send_http_header(pc_DataHeader))
   // {
   //    LOG_DBG("Modem HTTP Get of Sierra LTE Module HL7812 failed (http header)");
   //    e_RetVal = BSP_RET_ERROR;
   // }
   // else
   // {
   //    LOG_DBG("Send HTTP header: OK");
      if(mdm_hl7812_send_http_get(i_cpui8_Url))
      {
         LOG_DBG("Modem HTTP Get of Sierra LTE Module HL7812 failed");
         e_RetVal = BSP_RET_ERROR;
      }
      else
      {
         LOG_DBG("Get data success");
      }
   // }
   return e_RetVal;
}

BSP_Ret_e BSP_MODEM_Disconnect(void)
{
   BSP_Ret_e e_RetVal = BSP_RET_SUCCESS;

   if(mdm_hl7812_close_http())
   {
      LOG_DBG("Disconnect from HTPP of Sierra LTE Module HL7812 failed");
      e_RetVal = BSP_RET_ERROR;
   }
   else
   {
      LOG_DBG("Disconnect from HTPP of Sierra LTE Module HL7812 success");
   }

   return e_RetVal;
}

BSP_Ret_e BSP_MODEM_Deinit(void)
{
   // Nothing to do for the moment

   LOG_DBG("Deinitialization of Sierra LTE Module HL7812 success");

   return BSP_RET_SUCCESS;
}

// -------------------------------------------------------------------------------------------------------- //
//
//                            LOCAL FUNCTION DEFINITIONS
//
// -------------------------------------------------------------------------------------------------------- //