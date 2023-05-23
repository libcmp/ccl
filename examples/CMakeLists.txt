# Copyright (C) 2022 Daniel T. McGinnis
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.17)
project(ccl CXX)

if (NOT DEFINED CMP_CONFIG_LTO_REQUESTED)
    set(CMP_CONFIG_LTO_REQUESTED true)
endif ()
set(CMP_CONFIG_LTO_ENABLED false)
if (CMP_CONFIG_LTO_REQUESTED MATCHES true)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT lto_supported OUTPUT lto_support_error)
    if (lto_supported)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        set(CMP_CONFIG_LTO_ENABLED true)
    endif ()
endif ()

add_subdirectory(gui_example)
add_subdirectory(unicode_stdio_example)
