# Copyright (C) 2022 Daniel T. McGinnis
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.17)
project(ccl CXX)

# TESTS

add_executable(
    test_platform
        test_platform.cpp
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

# Establish a default value for CMP_BUILD_HO_TESTS.
if (NOT DEFINED CMP_BUILD_HO_TESTS)
    set(CMP_BUILD_HO_TESTS false)
endif ()

# Set CMP_BUILD_HO_TESTS to true during development.
if (DEFINED CMP_DEV)
    set(CMP_BUILD_HO_TESTS true)
endif ()

if (CMP_BUILD_HO_TESTS MATCHES true)
    add_executable(
        ho_test_platform
            test_platform.cpp
    )
    set_target_properties(
        ho_test_platform PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS OFF
    )
    target_include_directories(
        ho_test_platform PUBLIC
            ../../api/include
            ../../api/src
    )
    target_compile_definitions(
        ho_test_platform PUBLIC
            CMP_CONFIG_HEADER_ONLY=true
    )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(
            ho_test_platform PUBLIC
                /utf-8
        )
    endif ()
    add_test(
        ho_platform_test
            ho_test_platform
    )
    # test --------------------------------------------------------------------

    add_executable(
        ho_test_uio
            test_uio.cpp
    )
    set_target_properties(
        ho_test_uio PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS OFF
    )
    target_include_directories(
        ho_test_uio PUBLIC
            ../../api/include
            ../../api/src
    )
    target_compile_definitions(
        ho_test_uio PUBLIC
            CMP_CONFIG_HEADER_ONLY=true
    )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(
            ho_test_uio PUBLIC
                /utf-8
        )
    endif ()
    add_test(
        ho_uio_test
            ho_test_uio
    )
    # test --------------------------------------------------------------------
endif ()
