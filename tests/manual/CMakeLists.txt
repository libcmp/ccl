# Copyright (C) 2022 Daniel T. McGinnis
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.17)
project(ccl CXX)

# TESTS

add_executable(
    test_platform
        test_platform.cpp
)
target_compile_definitions(
    test_platform PUBLIC
        CMP_CONFIG_TESTS_ENABLED=true
)
set_target_properties(
    test_platform PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_platform
        cmp
)
# test ------------------------------------------------------------------------

add_executable(
    test_uio
        test_uio.cpp
)
target_compile_definitions(
    test_uio PUBLIC
        CMP_CONFIG_TESTS_ENABLED=true
)
set_target_properties(
    test_uio PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_uio
        cmp
)
# test ------------------------------------------------------------------------
