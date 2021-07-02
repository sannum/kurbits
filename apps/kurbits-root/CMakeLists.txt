#
# Copyright 2017, Data61, CSIRO (ABN 41 687 119 230) Viktor Sannum
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(kurbits-root C)

add_executable(kurbits-root EXCLUDE_FROM_ALL main.c)
target_link_libraries(
    kurbits-root
    PUBLIC
        sel4_autoconf
        muslc
        sel4
        sel4runtime
        sel4utils
        sel4platsupport
        sel4muslcsys
        bcm2835-armctrl-ic-server
)
target_compile_options(kurbits-root PRIVATE -Werror -g)

# Set this image as the rootserver
include(rootserver)
DeclareRootserver(kurbits-root)