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

add_subdirectory(apps/kurbits-root)

include(simulation)

GenerateSimulateScript()