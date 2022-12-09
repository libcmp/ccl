# Copyright (C) 2022 Daniel T. McGinnis
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.17)
project(ccl CXX)

enable_testing()

add_subdirectory(api)
add_subdirectory(tests)

if (DEFINED CMP_DEV)
    add_subdirectory(examples)
endif ()
