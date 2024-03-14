.. _devkit_iot_continuum_bsp_inertial:

BSP Inertial
############

Overview
========

The **[BSP_INERTIAL]** item provides a simple way to use LSM6DSO inertial module.

API Documentation
=================

.. doxygenfile:: inc/bsp_inertial.h
   :project: devkit_iot_continuum

The **[BSP_INERTIAL]** goal is to control the LSM6DSO inertial sensor.

It allows to:

* Initialize LSM6DSO inertial module

   It initializes the LSM6DSO inertial sensor.
   It is mandatory to use the API and need to be call first.

   .. code-block:: c

      BSP_ret_e BSP_INERTIAL_Init(void);

* Get acceleration values (in mm/s^2)  on the 3 axis from the LSM6DSO inertial module

   .. code-block:: c

      BSP_ret_e BSP_INERTIAL_GetAcceleration(int32_t *o_pi32_X, int32_t *o_pi32_Y, int32_t *o_pi32_Z)

* Get rotation values (in mrad/s) on the 3 axis from the LSM6DSO inertial module

   .. code-block:: c

      BSP_ret_e BSP_INERTIAL_GetGyroscope(int32_t *o_pi32_X, int32_t *o_pi32_Y, int32_t *o_pi32_Z)

* Deinitialize LSM6DSO inertial module

   .. code-block:: c

      BSP_ret_e BSP_INERTIAL_Deinit(void);

You can also remove debug log by setting ``CONFIG_BSP_INERTIAL_LOG_LEVEL_DBG=n``

Shell commands
==============

Activate ``CONFIG_BSP_INERTIAL_SHELL`` to enable the bsp_inertial_shell which proposes the following commands:

* help

   Shows all possible commands.

   Usage: bsp_inertial help

   Example:

   .. code-block:: bash

      uart:~$ bsp_inertial help
      bsp_inertial - bsp_inertial commands
      Subcommands:
      init              :Initialize LSM6DSO inertial module

      get_acceleration  :Get acceleration values (in mm/s^2) from the accelerometer
                           of LSM6DSO

      get_gyroscope     :Get rotation values (in mrad/s) from the gyroscope of
                           LSM6DSO

      deinit            :Deinitialize LSM6DSO inertial module
      uart:~$

* init

   Example:

   .. code-block:: bash

      uart:~$ bsp_inertial init
      SUCCESS: Inertial module LSM6DSO Init
      uart:~$

* get_acceleration

   Example:

   .. code-block:: bash

      uart:~$ bsp_inertial  get_acceleration
      SUCCESS: Acceleration: X = -7554 mm/s^2, Y = 1170 mm/s^2, Z = 6433 mm/s^2
      uart:~$

* get_gyroscope

   Example:

   .. code-block:: bash

      uart:~$ bsp_inertial  get_gyroscope
      SUCCESS: Rotation: X = 15 mrad/s^2, Y = 7 mrad/s^2, Z = -12 mrad/s^2
      uart:~$

* deinit

   Example:

   .. code-block:: bash

      uart:~$ bsp_inertial deinit
      SUCCESS: Inertial module LSM6DSO Deinit
      uart:~$

