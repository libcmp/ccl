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
                  :: test_read_line_from_wide,

              &text_input_stream_test_module
                  :: test_read_all_from_utf8,

              &text_input_stream_test_module
                  :: test_read_all_from_utf16,

              &text_input_stream_test_module
                  :: test_read_all_from_utf32,

              &text_input_stream_test_module
                  :: test_read_all_from_wide
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
        } else if constexpr (std::is_same_v<CodeUnit, wchar_t>) {
            if constexpr (sizeof (wchar_t) == 2) {
                encoding = utf16;
            } else {
                encoding = utf32;
            }
        } else {
            std::cout << "test_read_line_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t, char32_t or wchar_t."
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
        if (stream.is_at_end()) {
            std::cout << "The end of file was incorrectly reported "
                         "after reading the third line."
                      << std::endl;

            return false;
        }

        std::wstring wide_line;
        stream.read_line(wide_line);
        if (wide_line != L"coração\U0001F600¯\\_(ツ)_/¯") {
            std::cout << "The fourth line read from the file "
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
        typename CodeUnit
    >
    bool
    test_read_line_multibyte (
        std::endian endianness
    ) {
        std::string encoding_spelled_out;
        if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            encoding_spelled_out = "utf16";
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            encoding_spelled_out = "utf32";
        } else if constexpr (std::is_same_v<CodeUnit, wchar_t>) {
            if constexpr (sizeof (wchar_t) == 2) {
                encoding_spelled_out = "utf16";
            } else {
                encoding_spelled_out = "utf32";
            }
        } else {
            std::cout << "test_read_line_multibyte was called with an "
                         "invalid code unit type. Please use one of "
                         "char16_t, char32_t or wchar_t."
                      << std::endl;

            return false;
        }

        std::string endianness_spelled_out;
        if (endianness == std::endian::little) {
            endianness_spelled_out = "little_endian";
        } else if (endianness == std::endian::big) {
            endianness_spelled_out = "big_endian";
        } else {
            std::cout << "test_read_line_multibyte was called with an "
                         "invalid endianness. Please use one of "
                         "std::endian::little or std::endian::big."
                      << std::endl;

            return false;
        }

        file f{
            "../../test_data/test_read_"
                + encoding_spelled_out
                + "_with_"
                + endianness_spelled_out
                + "_bom.txt",
            read_only,
            if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_"
                      << encoding_spelled_out
                      << "_with_"
                      << endianness_spelled_out
                      << "_bom.txt could not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_line_generic<CodeUnit>(f, endianness)) {
            std::cout << "test_read_line_multibyte failed when reading from "
                         "file test_read_"
                      << encoding_spelled_out
                      << "_with_"
                      << endianness_spelled_out
                      << "_bom.txt."
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
        } else if constexpr (std::is_same_v<CodeUnit, wchar_t>) {
            if constexpr (sizeof (wchar_t) == 2) {
                encoding = utf16;
            } else {
                encoding = utf32;
            }
        } else {
            std::cout << "test_read_all_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t, char32_t or wchar_t."
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

        stream->set_position(0, position_reference::begin);
        if (encoding != utf8) {
            stream.read_bom();
        }
        std::wstring wide_content;
        stream.read_all(wide_content);
        if (
            wide_content
                != L"coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯\n"
                   "coração\U0001F600¯\\_(ツ)_/¯"
        ) {
            std::cout << "The std::wstring read from the file "
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

    template <
        typename CodeUnit
    >
    bool
    test_read_all_multibyte (
        std::endian endianness
    ) {
        std::string encoding_spelled_out;
        if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            encoding_spelled_out = "utf16";
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            encoding_spelled_out = "utf32";
        } else if constexpr (std::is_same_v<CodeUnit, wchar_t>) {
            if constexpr (sizeof (wchar_t) == 2) {
                encoding_spelled_out = "utf16";
            } else {
                encoding_spelled_out = "utf32";
            }
        } else {
            std::cout << "test_read_all_multibyte was called with an "
                         "invalid code unit type. Please use one of "
                         "char16_t, char32_t or wchar_t."
                      << std::endl;

            return false;
        }

        std::string endianness_spelled_out;
        if (endianness == std::endian::little) {
            endianness_spelled_out = "little_endian";
        } else if (endianness == std::endian::big) {
            endianness_spelled_out = "big_endian";
        } else {
            std::cout << "test_read_all_multibyte was called with an "
                         "invalid endianness. Please use one of "
                         "std::endian::little or std::endian::big."
                      << std::endl;

            return false;
        }

        file f{
            "../../test_data/test_read_"
                + encoding_spelled_out
                + "_with_"
                + endianness_spelled_out
                + "_bom.txt",
            read_only,
            if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_"
                      << encoding_spelled_out
                      << "_with_"
                      << endianness_spelled_out
                      << "_bom.txt could not be opened for reading."
                      << std::endl;

            return false;
        }

        if (!test_read_all_generic<CodeUnit>(f, endianness)) {
            std::cout << "test_read_all_multibyte failed when reading from "
                         "file test_read_"
                      << encoding_spelled_out
                      << "_with_"
                      << endianness_spelled_out
                      << "_bom.txt."
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
            if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_utf8_without_bom.txt "
                         "could not be opened for reading."
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

        if (!test_read_line_multibyte<char16_t>(std::endian::little)) {
            std::cout << "test_read_line_from_utf16 failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_read_line_multibyte<char16_t>(std::endian::big)) {
            std::cout << "test_read_line_from_utf16 failed with "
                         "big endian."
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

        if (!test_read_line_multibyte<char32_t>(std::endian::little)) {
            std::cout << "test_read_line_from_utf32 failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_read_line_multibyte<char32_t>(std::endian::big)) {
            std::cout << "test_read_line_from_utf32 failed with "
                         "big endian."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_line_from_wide ()
    noexcept
    {
        start_test("test_read_line_from_wide");

        if (!test_read_line_multibyte<wchar_t>(std::endian::little)) {
            std::cout << "test_read_line_from_wchar_t failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_read_line_multibyte<wchar_t>(std::endian::big)) {
            std::cout << "test_read_line_from_wchar_t failed with "
                         "big endian."
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
            if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_utf8_without_bom.txt "
                         "could not be opened for reading."
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

        if (!test_read_all_multibyte<char16_t>(std::endian::little)) {
            std::cout << "test_read_all_from_utf16 failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_read_all_multibyte<char16_t>(std::endian::big)) {
            std::cout << "test_read_all_from_utf16 failed with "
                         "big endian."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_all_from_utf32 ()
    noexcept
    {
        start_test("test_read_all_from_utf32");

        if (!test_read_all_multibyte<char32_t>(std::endian::little)) {
            std::cout << "test_read_all_from_utf32 failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_read_all_multibyte<char32_t>(std::endian::big)) {
            std::cout << "test_read_all_from_utf32 failed with "
                         "big endian."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_all_from_wide ()
    noexcept
    {
        start_test("test_read_all_from_wide");

        if (!test_read_all_multibyte<wchar_t>(std::endian::little)) {
            std::cout << "test_read_all_from_wide failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_read_all_multibyte<wchar_t>(std::endian::big)) {
            std::cout << "test_read_all_from_wide failed with "
                         "big endian."
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
