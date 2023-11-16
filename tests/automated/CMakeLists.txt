# Copyright (C) 2022 Daniel T. McGinnis
# SPDX-License-Identifier: BSL-1.0

cmake_minimum_required(VERSION 3.17)
project(ccl CXX)

# TESTS / CCL Core

add_executable(
    test_core_general
        core/test_core_general.cpp
)
set_target_properties(
    test_core_general PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_core_general
        cmp
)
add_test(
    core_general_test
        test_core_general
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_core_general
        core/test_core_general.cpp
)
set_target_properties(
    ho_test_core_general PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_core_general PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_core_general PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_core_general PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_core_general_test
        ho_test_core_general
)
# test ------------------------------------------------------------------------

# TESTS / CCL IO

add_executable(
    test_container_transfer_resources
        io/test_container_transfer_resources.cpp
)
set_target_properties(
    test_container_transfer_resources PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_container_transfer_resources
        cmp
)
add_test(
    container_transfer_resources_test
        test_container_transfer_resources
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_container_transfer_resources
        io/test_container_transfer_resources.cpp
)
set_target_properties(
    ho_test_container_transfer_resources PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_container_transfer_resources PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_container_transfer_resources PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_container_transfer_resources PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_container_transfer_resources_test
        ho_test_container_transfer_resources
)
# test ------------------------------------------------------------------------

add_executable(
    test_data_input_stream
        io/test_data_input_stream.cpp
)
set_target_properties(
    test_data_input_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_data_input_stream
        cmp
)
add_test(
    data_input_stream_test
        test_data_input_stream
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_data_input_stream
        io/test_data_input_stream.cpp
)
set_target_properties(
    ho_test_data_input_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_data_input_stream PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_data_input_stream PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_data_input_stream PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_data_input_stream_test
        ho_test_data_input_stream
)
# test ------------------------------------------------------------------------

add_executable(
    test_data_io_stream
        io/test_data_io_stream.cpp
)
set_target_properties(
    test_data_io_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_data_io_stream
        cmp
)
add_test(
    data_io_stream_test
        test_data_io_stream
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_data_io_stream
        io/test_data_io_stream.cpp
)
set_target_properties(
    ho_test_data_io_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_data_io_stream PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_data_io_stream PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_data_io_stream PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_data_io_stream_test
        ho_test_data_io_stream
)
# test ------------------------------------------------------------------------

add_executable(
    test_data_output_stream
        io/test_data_output_stream.cpp
)
set_target_properties(
    test_data_output_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_data_output_stream
        cmp
)
add_test(
    data_output_stream_test
        test_data_output_stream
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_data_output_stream
        io/test_data_output_stream.cpp
)
set_target_properties(
    ho_test_data_output_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_data_output_stream PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_data_output_stream PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_data_output_stream PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_data_output_stream_test
        ho_test_data_output_stream
)
# test ------------------------------------------------------------------------

add_executable(
    test_file
        io/test_file.cpp
)
set_target_properties(
    test_file PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_file
        cmp
)
add_test(
    file_test
        test_file
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_file
        io/test_file.cpp
)
set_target_properties(
    ho_test_file PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_file PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_file PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_file PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_file_test
        ho_test_file
)
# test ------------------------------------------------------------------------

add_executable(
    test_io_general
        io/test_io_general.cpp
)
set_target_properties(
    test_io_general PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_io_general
        cmp
)
add_test(
    io_general_test
        test_io_general
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_io_general
        io/test_io_general.cpp
)
set_target_properties(
    ho_test_io_general PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_io_general PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_io_general PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_io_general PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_io_general_test
        ho_test_io_general
)
# test ------------------------------------------------------------------------

add_executable(
    test_text_input_stream
        io/test_text_input_stream.cpp
)
set_target_properties(
    test_text_input_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_text_input_stream
        cmp
)
add_test(
    text_input_stream_test
        test_text_input_stream
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_text_input_stream
        io/test_text_input_stream.cpp
)
set_target_properties(
    ho_test_text_input_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_text_input_stream PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_text_input_stream PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_text_input_stream PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_text_input_stream_test
        ho_test_text_input_stream
)
# test ------------------------------------------------------------------------

add_executable(
    test_text_io_stream
        io/test_text_io_stream.cpp
)
set_target_properties(
    test_text_io_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_text_io_stream
        cmp
)
add_test(
    text_io_stream_test
        test_text_io_stream
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_text_io_stream
        io/test_text_io_stream.cpp
)
set_target_properties(
    ho_test_text_io_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_text_io_stream PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_text_io_stream PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_text_io_stream PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_text_io_stream_test
        ho_test_text_io_stream
)
# test ------------------------------------------------------------------------

add_executable(
    test_text_output_stream
        io/test_text_output_stream.cpp
)
set_target_properties(
    test_text_output_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_text_output_stream
        cmp
)
add_test(
    text_output_stream_test
        test_text_output_stream
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_text_output_stream
        io/test_text_output_stream.cpp
)
set_target_properties(
    ho_test_text_output_stream PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_text_output_stream PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_text_output_stream PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_text_output_stream PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_text_output_stream_test
        ho_test_text_output_stream
)
# test ------------------------------------------------------------------------

# TESTS / CCL Unicode

add_executable(
    test_algorithms
        unicode/test_algorithms.cpp
)
set_target_properties(
    test_algorithms PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_algorithms
        cmp
)
add_test(
    algorithms_test
        test_algorithms
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_algorithms
        unicode/test_algorithms.cpp
)
set_target_properties(
    ho_test_algorithms PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_algorithms PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_algorithms PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_algorithms PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_algorithms_test
        ho_test_algorithms
)
# test ------------------------------------------------------------------------

add_executable(
    test_by_code_point
        unicode/test_by_code_point.cpp
)
set_target_properties(
    test_by_code_point PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_by_code_point
        cmp
)
add_test(
    by_code_point_test
        test_by_code_point
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_by_code_point
        unicode/test_by_code_point.cpp
)
set_target_properties(
    ho_test_by_code_point PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_by_code_point PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_by_code_point PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_by_code_point PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_by_code_point_test
        ho_test_by_code_point
)
# test ------------------------------------------------------------------------

add_executable(
    test_examiners
        unicode/test_examiners.cpp
)
set_target_properties(
    test_examiners PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_examiners
        cmp
)
add_test(
    examiners_test
        test_examiners
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_examiners
        unicode/test_examiners.cpp
)
set_target_properties(
    ho_test_examiners PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_examiners PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_examiners PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_examiners PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_examiners_test
        ho_test_examiners
)
# test ------------------------------------------------------------------------

add_executable(
    test_formatters
        unicode/test_formatters.cpp
)
set_target_properties(
    test_formatters PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_formatters
        cmp
)
add_test(
    formatters_test
        test_formatters
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_formatters
        unicode/test_formatters.cpp
)
set_target_properties(
    ho_test_formatters PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_formatters PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_formatters PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_formatters PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_formatters_test
        ho_test_formatters
)
# test ------------------------------------------------------------------------

add_executable(
    test_parsers
        unicode/test_parsers.cpp
)
set_target_properties(
    test_parsers PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_parsers
        cmp
)
add_test(
    parsers_test
        test_parsers
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_parsers
        unicode/test_parsers.cpp
)
set_target_properties(
    ho_test_parsers PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_parsers PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_parsers PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_parsers PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_parsers_test
        ho_test_parsers
)
# test ------------------------------------------------------------------------

add_executable(
    test_type_traits
        unicode/test_type_traits.cpp
)
set_target_properties(
    test_type_traits PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_link_libraries(
    test_type_traits
        cmp
)
add_test(
    type_traits_test
        test_type_traits
)
# test ------------------------------------------------------------------------
add_executable(
    ho_test_type_traits
        unicode/test_type_traits.cpp
)
set_target_properties(
    ho_test_type_traits PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS OFF
)
target_include_directories(
    ho_test_type_traits PUBLIC
        ../../api/include
        ../../api/src
)
target_compile_definitions(
    ho_test_type_traits PUBLIC
        CMP_CONFIG_HEADER_ONLY=true
)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        ho_test_type_traits PUBLIC
            /utf-8
    )
endif ()
add_test(
    ho_type_traits_test
        ho_test_type_traits
)
# test ------------------------------------------------------------------------
