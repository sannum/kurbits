#
# Copyright 2019, Data61, CSIRO (ABN 41 687 119 230), Viktor Sannum
#
# SPDX-License-Identifier: BSD-2-Clause
#

cmake_minimum_required(VERSION 3.7.2)

set(project_dir "${CMAKE_CURRENT_LIST_DIR}/../../")
file(GLOB project_modules ${project_dir}/projects/*)
list(
    APPEND
        CMAKE_MODULE_PATH
        ${project_dir}/kernel
        ${project_dir}/tools/seL4/cmake-tool/helpers/
        ${project_dir}/tools/seL4/elfloader-tool/
        ${project_modules}
)

# set(NANOPB_SRC_ROOT_FOLDER "${project_dir}/tools/nanopb" CACHE INTERNAL "")

include(application_settings)

include(${CMAKE_CURRENT_LIST_DIR}/easy-settings.cmake)

correct_platform_strings()

find_package(seL4 REQUIRED)
sel4_configure_platform_settings()

ApplyCommonReleaseVerificationSettings(${RELEASE} ${VERIFICATION})

if(SMP)
    if(NUM_NODES MATCHES "^[0-9]+$")
        set(KernelMaxNumNodes ${NUM_NODES} CACHE STRING "" FORCE)
    else()
        set(KernelMaxNumNodes 4 CACHE STRING "" FORCE)
    endif()
else()
    set(KernelMaxNumNodes 1 CACHE STRING "" FORCE)
endif()

if(MCS)
    set(KernelIsMCS ON CACHE BOOL "" FORCE)
else()
    set(KernelIsMCS OFF CACHE BOOL "" FORCE)
endif()
