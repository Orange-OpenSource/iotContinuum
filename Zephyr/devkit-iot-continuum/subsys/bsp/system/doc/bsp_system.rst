.. _devkit_iot_continuum_bsp_system:

BSP System
##########

Overview
========

The **[BSP_SYSTEM]** item provides a simple way to propose system services.

API Documentation
=================

.. doxygenfile:: inc/bsp_system.h
   :project: devkit_iot_continuum

The **[BSP_SYSTEM]** goal is to control the system (get uptime or reboot the system).

It allows to:

* Get uptime in seconds

   .. code-block:: c

      BSP_Ret_e BSP_SYSTEM_GetUptimeMSec(void);

* Get uptime in milliseconds

   .. code-block:: c

      BSP_Ret_e BSP_SYSTEM_GetUptimeMs(void);

* Reboot system, do software reset

   .. code-block:: c

      BSP_Ret_e BSP_SYSTEM_Reboot();

You can also remove debug log by setting ``CONFIG_BSP_SYSTEM_LOG_LEVEL_DBG=n``

Shell commands
==============

Activate ``CONFIG_BSP_SYSTEM_SHELL`` to enable the bsp_system_shell which proposes following commands:

* help

   Shows all possible commands

   Usage: bsp_system help

   Example:

   .. code-block:: bash

      uart:~$ bsp_system help
      bsp_system - bsp_system commands
      Subcommands:
      uptime_sec  :Get Uptime in seconds

      uptime_ms   :Get Uptime in milliseconds

      reboot      :Do a software reset
                   bsp_system reboot <delay_ms>
      uart:~$

* uptime_sec

   Example:

   .. code-block:: bash

      uart:~$ bsp_system uptime_sec
      SUCCESS: uptime = 161 sec
      uart:~$

* uptime_ms

   Example:

   .. code-block:: bash

      uart:~$ bsp_system uptime_ms
      SUCCESS: uptime = 186557 ms
      uart:~$

* reboot

   Example:

   .. code-block:: bash

      uart:~$ bsp_system reboot 100
      Do a software reset in 100 ms
      *** Booting Zephyr OS build zephyr-v3.2.0-67-g95d7afeb1bbd  ***

Each command returns ``SUCCESS`` in case of a success or ``FAILED`` in case of a failure.
