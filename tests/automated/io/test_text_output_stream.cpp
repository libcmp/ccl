// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/text_output_stream.hpp>
#include <cmp/io/file.hpp>

namespace cmp {

class text_output_stream_test_module
    : public test_module<text_output_stream_test_module>
{
public:
    text_output_stream_test_module ()
    noexcept
        : test_module({
              &text_output_stream_test_module
                  :: test_write_to_utf8,

              &text_output_stream_test_module
                  :: test_write_to_utf16,

              &text_output_stream_test_module
                  :: test_write_to_utf32,

              &text_output_stream_test_module
                  :: test_write_to_wide
          })
    {
    } // function -------------------------------------------------------------

    // Test Tooling -----------------------------------------------------------

    template <
        typename CodeUnit,
        typename OutputResource
    >
    bool
    test_write_generic (
        OutputResource& resource,
        std::endian endianness
    )
    noexcept
    {
        std::u8string utf8_string{u8"¯\\_(ツ)_/¯"};
        std::u16string utf16_string{u"¯\\_(ツ)_/¯"};
        std::u32string utf32_string{U"¯\\_(ツ)_/¯"};
        std::wstring wide_string{L"¯\\_(ツ)_/¯"};

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
            std::cout << "test_write_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t, char32_t or wchar_t."
                      << std::endl;

            return false;
        }

        text_output_stream stream{resource, encoding, endianness};

        if (encoding != utf8) {
            stream.write_bom();
        }
        stream << utf8_string << '\n';
        stream << utf16_string << '\n';
        stream << utf32_string << '\n';
        stream << wide_string << '\n';
        stream.flush();

        return true;
    } // function -------------------------------------------------------------

    template <
        typename CodeUnit
    >
    bool
    test_write_multibyte (
        std::endian endianness
    ) {
        std::string encoding_spelled_out;
        if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            encoding_spelled_out = "utf16";
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            encoding_spelled_out = "utf32";
        } else if constexpr (std::is_same_v<CodeUnit, wchar_t>) {
            encoding_spelled_out = "wide";
        } else {
            std::cout << "test_write_multibyte was called with an "
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
            std::cout << "test_write_multibyte was called with an "
                         "invalid endianness. Please use one of "
                         "std::endian::little or std::endian::big."
                      << std::endl;

            return false;
        }

        file f{
            "../../test_data/test_write_"
                + encoding_spelled_out
                + "_with_"
                + endianness_spelled_out
                + "_bom.txt",
            write_only,
            if_not_there::create
        };

        if (!f.is_open()) {
            std::cout << "File test_write_"
                      << encoding_spelled_out
                      << "_with_"
                      << endianness_spelled_out
                      << "_bom.txt could not be opened for writing."
                      << std::endl;

            return false;
        }

        if (!test_write_generic<CodeUnit>(f, endianness)) {
            std::cout << "test_write_multibyte failed when writing to file "
                         "test_write_"
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
    test_write_to_utf8 ()
    noexcept
    {
        start_test("test_write_to_utf8");

        file f{
            "../../test_data/test_write_utf8.txt",
            write_only,
            if_not_there::create
        };

        if (!f.is_open()) {
            std::cout << "File test_write_utf8.txt could "
                         "not be opened for writing."
                      << std::endl;

            return false;
        }

        if (!test_write_generic<char8_t>(f, std::endian::native)) {
            std::cout << "test_write_to_utf8 failed when writing to file "
                         "test_write_utf8.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_to_utf16 ()
    noexcept
    {
        start_test("test_write_to_utf16");

        if (!test_write_multibyte<char16_t>(std::endian::little)) {
            std::cout << "test_write_to_utf16 failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_write_multibyte<char16_t>(std::endian::big)) {
            std::cout << "test_write_to_utf16 failed with "
                         "big endian."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_to_utf32 ()
    noexcept
    {
        start_test("test_write_to_utf32");

        if (!test_write_multibyte<char32_t>(std::endian::little)) {
            std::cout << "test_write_to_utf32 failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_write_multibyte<char32_t>(std::endian::big)) {
            std::cout << "test_write_to_utf32 failed with "
                         "big endian."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_to_wide ()
    noexcept
    {
        start_test("test_write_to_wide");

        if (!test_write_multibyte<wchar_t>(std::endian::little)) {
            std::cout << "test_write_to_wide failed with "
                         "little endian."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!test_write_multibyte<wchar_t>(std::endian::big)) {
            std::cout << "test_write_to_wide failed with "
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
    return cmp::text_output_stream_test_module{}.run_tests();
} // function -----------------------------------------------------------------
