# Copyright (c) Lacroix Impulse 2023 (France)
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(inc)

add_subdirectory_ifdef(CONFIG_BSP_INERTIAL inertial)
add_subdirectory_ifdef(CONFIG_BSP_MODEM modem)
add_subdirectory_ifdef(CONFIG_BSP_BME280 bme280)
add_subdirectory_ifdef(CONFIG_BSP_SYSTEM system)
