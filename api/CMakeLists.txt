# Copyright (C) 2022 Daniel T. McGinnis
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.17)
project(ccl CXX)

# LIBRARY

# Specify the headers for each package.
set(
    CCL_CORE_HEADERS
        include/cmp/core/application.hpp
        include/cmp/core/compiler.hpp
        include/cmp/core/config.hpp
        include/cmp/core/general.hpp
        include/cmp/core/operating_system.hpp
        include/cmp/core/platform.hpp
        include/cmp/core/test_module.hpp
        include/cmp/core/type_traits.hpp
)
set(
    CCL_IO_HEADERS
        include/cmp/io/impl/common/common_uio.hpp
        include/cmp/io/general.hpp
        include/cmp/io/data_input_stream.hpp
        include/cmp/io/data_io_stream.hpp
        include/cmp/io/data_output_stream.hpp
        include/cmp/io/exceptions.hpp
        include/cmp/io/file.hpp
        include/cmp/io/inclusion_assert.hpp
        include/cmp/io/input_resource.hpp
        include/cmp/io/input_stream.hpp
        include/cmp/io/io_buffer.hpp
        include/cmp/io/io_resource.hpp
        include/cmp/io/output_resource.hpp
        include/cmp/io/output_stream.hpp
        include/cmp/io/seekable_input_resource.hpp
        include/cmp/io/seekable_io_resource.hpp
        include/cmp/io/seekable_output_resource.hpp
        include/cmp/io/seekable_transfer_resource.hpp
        include/cmp/io/string_io_resource.hpp
        include/cmp/io/text_input_stream.hpp
        include/cmp/io/text_io_stream.hpp
        include/cmp/io/text_output_stream.hpp
        include/cmp/io/transfer_resource.hpp
        include/cmp/io/uio.hpp
)
set(
    CCL_UNICODE_HEADERS
        include/cmp/unicode/impl/impl.hpp
        include/cmp/unicode/algorithms.hpp
        include/cmp/unicode/by_code_point.hpp
        include/cmp/unicode/concepts.hpp
        include/cmp/unicode/constants.hpp
        include/cmp/unicode/examiners.hpp
        include/cmp/unicode/exceptions.hpp
        include/cmp/unicode/formats.hpp
        include/cmp/unicode/formatters.hpp
        include/cmp/unicode/parsers.hpp
        include/cmp/unicode/type_traits.hpp
)

# Decide what headers to pass on to the library target.
set(
    CCL_HEADERS
        ${CCL_CORE_HEADERS}
        ${CCL_UNICODE_HEADERS}
)
if (NOT DEFINED CMP_CONFIG_IO_PACKAGE_EXCLUDED)
    set(CMP_CONFIG_IO_PACKAGE_EXCLUDED false)
endif ()
if (CMP_CONFIG_IO_PACKAGE_EXCLUDED MATCHES false)
    set(
        CCL_HEADERS
            ${CCL_HEADERS}
            ${CCL_IO_HEADERS}
    )
endif ()

# Specify the sources for each package.
set(
    CCL_SOURCES
        src/cmp/core/definitions.cpp
        src/cmp/io/definitions.cpp
        src/cmp/unicode/definitions.cpp
)

# Decide how to build the library target.
if (DEFINED CMP_BUILD_STATIC)
    # Create the cmp target as a statically linked library.
    add_library(
        cmp STATIC
            ${CCL_HEADERS}
            ${CCL_SOURCES}
    )
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_IS_STATIC=true
    )
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_IS_DYNAMIC=false
    )
else ()
    # Create the cmp target as a dynamically linked library.
    add_library(
        cmp SHARED
            ${CCL_HEADERS}
            ${CCL_SOURCES}
    )
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_IS_STATIC=false
    )
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_IS_DYNAMIC=true
    )
endif ()

# Specify the include directories.
target_include_directories(
    cmp PUBLIC
        include
        src
        ${PROJECT_BINARY_DIR}/exports
)

# Make sure we're using standard C++20.
set_target_properties(
    cmp PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
        CXX_VISIBILITY_PREFIX hidden
        VISIBILITY_INLINES_HIDDEN YES
)

if (NOT DEFINED CMP_CONFIG_LTO_REQUESTED)
    set(CMP_CONFIG_LTO_REQUESTED true)
endif ()
set(CMP_CONFIG_LTO_ENABLED false)
if (CMP_CONFIG_LTO_REQUESTED MATCHES true)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT lto_supported OUTPUT lto_support_error)
    if (lto_supported)
        set_target_properties(
            cmp PROPERTIES
                INTERPROCEDURAL_OPTIMIZATION TRUE
        )
        set(CMP_CONFIG_LTO_ENABLED true)
    endif ()
endif ()

# Specify the warnings we'd like to see.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        cmp PUBLIC
            /utf-8
            /W4
            #/WX
    )
else ()
    target_compile_options(
        cmp PUBLIC
            -Wall
            -Wextra
            -pedantic
            #-Werror
    )
endif ()

include(GenerateExportHeader)
generate_export_header(cmp EXPORT_FILE_NAME exports/cmp_export.hpp)

# CONSTANTS

#[[
    For each configuration constant, check to see if it is defined,
    and if it is then set a compile-time constant on the cmp target
    with the value that the constant was given.

    The CMP_CONFIG_IO_PACKAGE_EXCLUDED, CMP_CONFIG_LTO_REQUESTED and
    CMP_CONFIG_LTO_ENABLED constants are different from the others
    in that they are guaranteed to be defined at this point in this
    CMakeLists.txt file, so it is not necessary to check whether they
    are defined before passing them onto the cmp target.
]]

if (DEFINED CMP_CONFIG_HEADER_ONLY)
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_HEADER_ONLY=${CMP_CONFIG_HEADER_ONLY}
    )
endif ()

if (DEFINED CMP_CONFIG_DEFAULT_BUFFER_CAPACITY)
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_DEFAULT_BUFFER_CAPACITY=${CMP_CONFIG_DEFAULT_BUFFER_CAPACITY}
    )
endif ()

if (DEFINED CMP_CONFIG_DEFAULT_STDOUT_BUFFER_CAPACITY)
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_DEFAULT_STDOUT_BUFFER_CAPACITY=${CMP_CONFIG_DEFAULT_STDOUT_BUFFER_CAPACITY}
    )
endif ()

if (DEFINED CMP_CONFIG_DEFAULT_STDERR_BUFFER_CAPACITY)
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_DEFAULT_STDERR_BUFFER_CAPACITY=${CMP_CONFIG_DEFAULT_STDERR_BUFFER_CAPACITY}
    )
endif ()

if (DEFINED CMP_CONFIG_DEFAULT_STDIN_BUFFER_CAPACITY)
    target_compile_definitions(
        cmp PUBLIC
            CMP_CONFIG_DEFAULT_STDIN_BUFFER_CAPACITY=${CMP_CONFIG_DEFAULT_STDIN_BUFFER_CAPACITY}
    )
endif ()

target_compile_definitions(
    cmp PUBLIC
        CMP_CONFIG_IO_PACKAGE_EXCLUDED=${CMP_CONFIG_IO_PACKAGE_EXCLUDED}
        CMP_CONFIG_LTO_REQUESTED=${CMP_CONFIG_LTO_REQUESTED}
        CMP_CONFIG_LTO_ENABLED=${CMP_CONFIG_LTO_ENABLED}
)

# DATA

# Make sure the data files get copied when the library is built.
add_custom_command(
    TARGET cmp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/../tests/data
        ${PROJECT_BINARY_DIR}/../test_data
)

#[[
    It is necessary to copy the library file so that
    executables that depend on it have access to it.
]]
if (NOT DEFINED CMP_BUILD_STATIC)
    add_custom_command(
        TARGET cmp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:cmp>
            ${PROJECT_BINARY_DIR}/../tests/automated/$<TARGET_FILE_NAME:cmp>
    )
    add_custom_command(
        TARGET cmp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:cmp>
            ${PROJECT_BINARY_DIR}/../tests/manual/$<TARGET_FILE_NAME:cmp>
    )
    add_custom_command(
        TARGET cmp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:cmp>
            ${PROJECT_BINARY_DIR}/../$<TARGET_FILE_NAME:cmp>
    )
    if (DEFINED CMP_DEV)
        add_custom_command(
            TARGET cmp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:cmp>
                ${PROJECT_BINARY_DIR}/../examples/unicode_stdio_example/$<TARGET_FILE_NAME:cmp>
        )
        add_custom_command(
            TARGET cmp POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:cmp>
                ${PROJECT_BINARY_DIR}/../../[unreleased]/tools/docgen/$<TARGET_FILE_NAME:cmp>
        )
    endif ()
endif ()
