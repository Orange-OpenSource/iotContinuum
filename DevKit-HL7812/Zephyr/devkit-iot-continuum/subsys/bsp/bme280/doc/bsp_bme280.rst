.. _iot_continuum_bsp_bme280:

BSP BME280
##########

Overview
========

The **[BSP_BME280]** item provides a simple way to use BME280 module.

API Documentation
=================

.. doxygenfile:: inc/bsp_bme280.h
   :project: orange_iot

The **[BSP_BME280]** goal is to control the BME280 sensor.

It allows to:

* Initialize BME280 module

   It initializes the BME280 sensors.
   It is mandatory to use the API and need to be call first.

   .. code-block:: c

      void BSP_BME280_Init(void)

* Get temperature values (in 0.1 degC) from the BME280 module

   .. code-block:: c

      void BSP_BME280_GetTemperature(int32_t *o_pi32_Temperature_degC)

* Get pression value (in mBar or hPa) from BME280 module

   .. code-block:: c

      void BSP_BME280_GetPression(int32_t *o_pi32_Pression_mBar)


* Get humidity value (percentage) from BME280 module

   .. code-block:: c

      void BSP_BME280_GetHumidity(int32_t *o_pi32_Humidity)

* Deinitialize BME280 module

   .. code-block:: c

      void BSP_BME280_Deinit(void)

You can also remove debug log by setting ``CONFIG_BSP_BME280_LOG_LEVEL_DBG=n``

Shell commands
==============

Activate ``CONFIG_BSP_BME280_SHELL`` to enable the bsp_bme280_shell which proposes the following commands:

* help

   Shows all possible commands.

   Usage: bsp_bme280 help

   Example:

   .. code-block:: bash

      uart:~$ bsp_bme280 help
      bsp_bme280 - bsp_bme280 commands
      Subcommands:
      init              :Initialize BME280 module

      get_temperature  :Get temperature value (in 0.1degC) from BME280 module

      deinit            :Deinitialize BME280 module
      uart:~$
