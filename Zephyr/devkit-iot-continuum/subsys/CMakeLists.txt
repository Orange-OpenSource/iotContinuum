# Copyright (c) Lacroix Impulse 2023 (France)
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(inc)

add_subdirectory_ifdef(CONFIG_BSP bsp)
