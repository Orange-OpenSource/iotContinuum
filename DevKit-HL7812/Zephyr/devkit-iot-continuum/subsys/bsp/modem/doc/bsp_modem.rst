.. _iot_continuum_bsp_modem:

BSP Modem
#########

Overview
========

The **[BSP_MODEM]** item provides commands to send data with HTTP protocole via Sierra Modem.

API Documentation
=================

The **[BSP_MODEM_SIERRA]** goal is to allow controls over the Sierra LTE Module HL7812.

It allows to:

* Initialize modem

   It updates the apn defined in the modem

   .. code-block:: c

      BSP_Ret_e BSP_MODEM_Init(void);

* Connect to network and configure for https

   It connects to the HL7812 LTE module, enter the certifcate and configures https.
   It returns the connection status.

   .. code-block:: c

      BSP_Ret_e BSP_MODEM_Connect(BSP_MODEM_ConnectionState_e *o_pe_State);

      with enum defined:
      ///@brief Provides a type to report network state.
      typedef enum
      {
         BSP_MODEM_NETWORK_WAITING_FOR_CONNECTION = 0,
         BSP_MODEM_NETWORK_CONNECTED,
         BSP_MODEM_NETWORK_ERROR,
      } BSP_MODEM_ConnectionState_e;

* Post sensor data to server

   It sends data to server to a defined URL

   .. code-block:: c

      BSP_Ret_e BSP_MODEM_Post(char *i_pui8_Payload, char *i_pui8_Url);

* Get data from server

   It gets data from server from a defined URL

   .. code-block:: c

      BSP_Ret_e BSP_MODEM_Get(char *o_pui8_Recive, char const *i_cpui8_Url);

* Disconnect HL7812 LTE module

   It disconnects the HL7812 LTE module from the HTTP connection.

   .. code-block:: c

      BSP_Ret_e BSP_MODEM_Disconnect(void);

* Deinitialize HL7812 LTE module

   It deinitializes the HL7812 LTE module.

   .. code-block:: c

      BSP_Ret_e BSP_MODEM_Deinit(void);

You can also remove debug log by setting ``CONFIG_BSP_MODEM_LOG_LEVEL_DBG=n``