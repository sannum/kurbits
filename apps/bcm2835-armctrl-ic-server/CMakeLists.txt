#
# Copyright 2021 Viktor Sannum
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(bcm2835-armctrl-ic-server C)

add_library(bcm2835-armctrl-ic-server EXCLUDE_FROM_ALL src/server.c)

target_include_directories(bcm2835-armctrl-ic-server PUBLIC "include")
target_link_libraries(
    bcm2835-armctrl-ic-server
    PUBLIC
        sel4_autoconf
        muslc
        sel4
        sel4runtime
        sel4utils
        sel4platsupport
        sel4muslcsys
)
target_compile_options(bcm2835-armctrl-ic-server PRIVATE -Werror -g)
