#
# Copyright 2021, Data61, CSIRO (ABN 41 687 119 230), Viktor Sannum
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

include(settings.cmake)

project(kurbits C CXX ASM)

find_package(seL4 REQUIRED)
find_package(elfloader-tool REQUIRED)

sel4_import_kernel()

ApplyData61ElfLoaderSettings(${KernelPlatform} ${KernelSel4Arch})

elfloader_import_project()

find_package(musllibc REQUIRED)
find_package(util_libs REQUIRED)
find_package(seL4_libs REQUIRED)
find_package(sel4_projects_libs REQUIRED)

musllibc_setup_build_environment_with_sel4runtime()
sel4_import_libsel4()
util_libs_import_libraries()
sel4_libs_import_libraries()

add_subdirectory(apps/kurbits-root)
add_subdirectory(apps/bcm2835-armctrl-ic-server)

include(simulation)

GenerateSimulateScript()