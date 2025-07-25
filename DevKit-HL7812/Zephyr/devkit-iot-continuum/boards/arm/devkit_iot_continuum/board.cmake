# Copyright (c) Lacroix Impulse 2023 (France)
# SPDX-License-Identifier: Apache-2.0

board_runner_args(stm32cubeprogrammer "--port=swd" "--reset-mode=hw" --conn-modifiers speed=fast)

board_runner_args(openocd "--tcl-port=6666")
board_runner_args(openocd --cmd-pre-init "gdb_report_data_abort enable")
board_runner_args(openocd "--no-halt")

include(${ZEPHYR_BASE}/boards/common/stm32cubeprogrammer.board.cmake)
# FIXME: openocd runner requires use of STMicro openocd fork.
# Check board documentation for more details.
set(OPENOCD "/mnt/c/sdk_zephyr_windows/xpack-openocd-0.11.0-2/bin/openocd.exe" CACHE FILEPATH "" FORCE)
include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
