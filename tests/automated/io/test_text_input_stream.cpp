// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/text_input_stream.hpp>
#include <cmp/io/file.hpp>

namespace cmp {

class text_input_stream_test_module
    : public test_module<text_input_stream_test_module>
{
public:
    text_input_stream_test_module ()
    noexcept
        : test_module({
              &text_input_stream_test_module
                  :: test_read_line_from_utf8,

              &text_input_stream_test_module
                  :: test_read_line_from_utf16,

              &text_input_stream_test_module
                  :: test_read_line_from_utf32,

              &text_input_stream_test_module
                  :: test_read_all_from_utf8,

              &text_input_stream_test_module
                  :: test_read_all_from_utf16,

              &text_input_stream_test_module
                  :: test_read_all_from_utf32
          })
    {
    } // function -------------------------------------------------------------

    // Test Tooling -----------------------------------------------------------

    template <
        typename CodeUnit,
        typename InputResource
    >
    bool
    test_read_line_generic (
        InputResource& resource,
        std::endian endianness
    )
    noexcept
    {
        encoding_form encoding;
        if constexpr (std::is_same_v<CodeUnit, char8_t>) {
            encoding = utf8;
        } else if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            encoding = utf16;
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            encoding = utf32;
        } else {
            std::cout << "test_read_line_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t or char32_t."
                      << std::endl;

            return false;
        }

        text_input_stream stream{resource, encoding, endianness};

        if (encoding != utf8) {
            stream.read_bom();
        }

        std::u8string utf8_line;
        stream.read_line(utf8_line);
        if (utf8_line != u8"coração\U0001F600¯\\_(ツ)_/¯") {
            std::cout << "The first line read from the file "
                         "does not have the expected content."
                      << std::endl;

            return false;
        }
        if (stream.is_at_end()) {
            std::cout << "The end of file was incorrectly reported "
                         "after reading the first line."
                      << std::endl;

            return false;
        }

        std::u16string utf16_line;
        stream.read_line(utf16_line);
        if (utf16_line != u"coração\U0001F600¯\\_(ツ)_/¯") {
            std::cout << "The second line read from the file "
                         "does not have the expected content."
                      << std::endl;

            return false;
        }
        if (stream.is_at_end()) {
            std::cout << "The end of file was incorrectly reported "
                         "after reading the second line."
                      << std::endl;

            return false;
        }

        std::u32string utf32_line;
        stream.read_line(utf32_line);
        if (utf32_line != U"coração\U0001F600¯\\_(ツ)_/¯") {
            std::cout << "The third line read from the file "
                         "does not have the expected content."
                      << std::endl;

            return false;
        }
        if (!stream.is_at_end()) {
            std::cout << "The end of file was not correctly detected "
                         "after reading the last line."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    template <
        typename CodeUnit,
        typename InputResource
    >
    bool
    test_read_all_generic (
        InputResource& resource,
        std::endian endianness
    )
    noexcept
    {
        encoding_form encoding;
        if constexpr (std::is_same_v<CodeUnit, char8_t>) {
            encoding = utf8;
        } else if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            encoding = utf16;
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            encoding = utf32;
        } else {
            std::cout << "test_read_all_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t or char32_t."
                      << std::endl;

            return false;
        }

        text_input_stream stream{resource, encoding, endianness};

        if (encoding != utf8) {
            stream.read_bom();
        }

        std::u8string utf8_content;
        stream.read_all(utf8_content);
        if (
            utf8_content
                != u8"coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯"
        ) {
            std::cout << "The std::u8string read from the file "
                         "does not have the expected content."
                      << std::endl;

            return false;
        }
        if (!stream.is_at_end()) {
            std::cout << "The end of file was not correctly detected."
                      << std::endl;

            return false;
        }

        stream->set_position(0, position_reference::begin);
        if (encoding != utf8) {
            stream.read_bom();
        }
        std::u16string utf16_content;
        stream.read_all(utf16_content);
        if (
            utf16_content
                != u"coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯"
        ) {
            std::cout << "The std::u16string read from the file "
                         "does not have the expected content."
                      << std::endl;

            return false;
        }
        if (!stream.is_at_end()) {
            std::cout << "The end of file was not correctly detected."
                      << std::endl;

            return false;
        }

        stream->set_position(0, position_reference::begin);
        if (encoding != utf8) {
            stream.read_bom();
        }
        std::u32string utf32_content;
        stream.read_all(utf32_content);
        if (
            utf32_content
                != U"coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯"
        ) {
            std::cout << "The std::u32string read from the file "
                         "does not have the expected content."
                      << std::endl;

            return false;
        }
        if (!stream.is_at_end()) {
            std::cout << "The end of file was not correctly detected."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_read_line_from_utf8 ()
    noexcept
    {
        start_test("test_read_line_from_utf8");

        file f{
            "../../test_data/test_read_utf8_without_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_utf8_without_bom.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_line_generic<char8_t>(f, std::endian::native)) {
            std::cout << "test_read_line_from_utf8 failed when reading from "
                         "file test_read_utf8_without_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_line_from_utf16 ()
    noexcept
    {
        start_test("test_read_line_from_utf16");

        file f{
            "../../test_data/test_read_utf16_with_little_endian_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_utf16_with_little_endian_bom.txt "
                         "could not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_line_generic<char16_t>(f, std::endian::little)) {
            std::cout << "test_read_line_from_utf16 failed when reading from "
                         "file test_read_utf16_with_little_endian_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_line_from_utf32 ()
    noexcept
    {
        start_test("test_read_line_from_utf32");

        file f{
            "../../test_data/test_read_utf32_with_little_endian_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_utf32_with_little_endian_bom.txt "
                         "could not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_line_generic<char32_t>(f, std::endian::little)) {
            std::cout << "test_read_line_from_utf32 failed when reading from "
                         "file test_read_utf32_with_little_endian_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_all_from_utf8 ()
    noexcept
    {
        start_test("test_read_all_from_utf8");

        file f{
            "../../test_data/test_read_utf8_without_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_utf8_without_bom.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_all_generic<char8_t>(f, std::endian::native)) {
            std::cout << "test_read_all_from_utf8 failed when reading from "
                         "file test_read_utf8_without_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_all_from_utf16 ()
    noexcept
    {
        start_test("test_read_all_from_utf16");

        std::u8string utf8_content;
        std::u16string utf16_content;
        std::u32string utf32_content;

        file f1{
            "../../test_data/test_read_utf16_with_little_endian_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f1.is_open()) {
            std::cout << "File test_read_utf16_with_little_endian_bom.txt "
                         "could not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_all_generic<char16_t>(f1, std::endian::little)) {
            std::cout << "test_read_all_from_utf16 failed when reading from "
                         "file test_read_utf16_with_little_endian_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        file f2{
            "../../test_data/test_read_utf16_with_big_endian_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f2.is_open()) {
            std::cout << "File test_read_utf16_with_big_endian_bom.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_all_generic<char16_t>(f2, std::endian::big)) {
            std::cout << "test_read_all_from_utf16 failed when reading from "
                         "file test_read_utf16_with_big_endian_bom.txt."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_all_from_utf32 ()
    noexcept
    {
        start_test("test_read_all_from_utf32");

        std::u8string utf8_content;
        std::u16string utf16_content;
        std::u32string utf32_content;

        file f1{
            "../../test_data/test_read_utf32_with_little_endian_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f1.is_open()) {
            std::cout << "File test_read_utf32_with_little_endian_bom.txt "
                         "could not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_all_generic<char32_t>(f1, std::endian::little)) {
            std::cout << "test_read_all_from_utf32 failed when reading from "
                         "file test_read_utf32_with_little_endian_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        file f2{
            "../../test_data/test_read_utf32_with_big_endian_bom.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f2.is_open()) {
            std::cout << "File test_read_utf32_with_big_endian_bom.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_all_generic<char32_t>(f2, std::endian::big)) {
            std::cout << "test_read_all_from_utf32 failed when reading from "
                         "file test_read_utf32_with_big_endian_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

int
main ()
{
    return cmp::text_input_stream_test_module{}.run_tests();
} // function -----------------------------------------------------------------
