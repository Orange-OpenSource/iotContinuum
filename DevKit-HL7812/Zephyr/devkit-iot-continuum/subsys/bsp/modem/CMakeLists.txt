# Copyright (c) Lacroix Impulse 2023 (France)
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(inc)
zephyr_library()

zephyr_library_sources_ifdef(CONFIG_BSP_MODEM src/bsp_modem.c)