# Copyright (c) Lacroix Impulse 2023 (France)
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(inc)
zephyr_library()
zephyr_library_sources(src/bsp_inertial.c)
zephyr_library_sources_ifdef(CONFIG_BSP_INERTIAL_SHELL src/bsp_inertial_shell.c)
