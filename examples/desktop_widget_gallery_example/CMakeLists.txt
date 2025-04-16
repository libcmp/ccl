# Copyright (C) 2025 Daniel T. McGinnis
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.17)
project(ccl CXX)

if (NOT DEFINED CMP_DEV)
    add_subdirectory(../../api cmp_build)
endif ()

add_executable(
    desktop_widget_gallery_example
        src/main.cpp
)
set_target_properties(
    desktop_widget_gallery_example PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    desktop_widget_gallery_example
        cmp
)

