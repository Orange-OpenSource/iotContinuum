# Copyright (c) Lacroix Impulse 2023 (France)
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(demo_devkit_iot_continuum)

target_sources(app PRIVATE src/main.c )