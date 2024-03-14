# Copyright (c) Lacroix Impulse 2023 (France)
# SPDX-License-Identifier: Apache-2.0

zephyr_library()

if (CONFIG_MODEM_HL7812)
  include_directories(${ZEPHYR_BASE}/subsys/net/ip)
  zephyr_include_directories(hl7812/inc)
  zephyr_include_directories(${ZEPHYR_BASE}/drivers/modem)
  zephyr_library_sources(hl7812/src/hl7812.c)
endif()
