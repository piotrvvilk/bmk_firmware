# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(bmk_firmware)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE
  src/main.c
  src/board.c
  src/version.c
  src/matrix_keyboard.c
  src/led_pwm.c
  src/led_strip.c
  src/display.c
  src/lis2dh.c
  src/max17048.c
  src/pictures/gta_picture.c
  src/pictures/vsc_picture.c
  src/pictures/altium_picture.c
)
