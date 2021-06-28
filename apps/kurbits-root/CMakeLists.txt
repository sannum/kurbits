#
# Copyright 2017, Data61, CSIRO (ABN 41 687 119 230) Viktor Sannum
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

project(kurbits-root C)

find_package(musllibc REQUIRED)
find_package(util_libs REQUIRED)
find_package(seL4_libs REQUIRED)
find_package(sel4_projects_libs REQUIRED)

musllibc_setup_build_environment_with_sel4runtime()
sel4_import_libsel4()
util_libs_import_libraries()
sel4_libs_import_libraries()

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
)
target_compile_options(kurbits-root PRIVATE -Werror -g)

# Set this image as the rootserver
include(rootserver)
DeclareRootserver(kurbits-root)