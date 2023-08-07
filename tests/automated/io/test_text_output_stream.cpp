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
                  :: test_write_to_utf32
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

        encoding_form encoding;
        if constexpr (std::is_same_v<CodeUnit, char8_t>) {
            encoding = utf8;
        } else if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            encoding = utf16;
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            encoding = utf32;
        } else {
            std::cout << "test_write_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t or char32_t."
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
        stream.flush();

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
            cmp::if_not_there::fail
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

        file f1{
            "../../test_data/test_write_utf16_with_little_endian_bom.txt",
            write_only,
            cmp::if_not_there::fail
        };

        if (!f1.is_open()) {
            std::cout << "File test_write_utf16_with_little_endian_bom.txt "
                         "could not be opened for writing."
                      << std::endl;

            return false;
        }

        if (!test_write_generic<char16_t>(f1, std::endian::little)) {
            std::cout << "test_write_to_utf16 failed when writing to file "
                         "test_write_utf16_with_little_endian_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        file f2{
            "../../test_data/test_write_utf16_with_big_endian_bom.txt",
            write_only,
            cmp::if_not_there::fail
        };

        if (!f2.is_open()) {
            std::cout << "File test_write_utf16_with_big_endian_bom.txt "
                         "could not be opened for writing."
                      << std::endl;

            return false;
        }

        if (!test_write_generic<char16_t>(f1, std::endian::big)) {
            std::cout << "test_write_to_utf16 failed when writing to file "
                         "test_write_utf16_with_big_endian_bom.txt."
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

        std::u8string utf8_string{u8"¯\\_(ツ)_/¯"};
        std::u16string utf16_string{u"¯\\_(ツ)_/¯"};
        std::u32string utf32_string{U"¯\\_(ツ)_/¯"};

        file f1{
            "../../test_data/test_write_utf32_with_little_endian_bom.txt",
            write_only,
            cmp::if_not_there::fail
        };

        if (!f1.is_open()) {
            std::cout << "File test_write_utf32_with_little_endian_bom.txt "
                         "could not be opened for writing."
                      << std::endl;

            return false;
        }

        if (!test_write_generic<char32_t>(f1, std::endian::little)) {
            std::cout << "test_write_to_utf32 failed when writing to file "
                         "test_write_utf32_with_little_endian_bom.txt."
                      << std::endl;

            return false;
        }

        end_stage();

        file f2{
            "../../test_data/test_write_utf32_with_big_endian_bom.txt",
            write_only,
            cmp::if_not_there::fail
        };

        if (!f2.is_open()) {
            std::cout << "File test_write_utf32_with_big_endian_bom.txt "
                         "could not be opened for writing."
                      << std::endl;

            return false;
        }

        if (!test_write_generic<char32_t>(f1, std::endian::big)) {
            std::cout << "test_write_to_utf32 failed when writing to file "
                         "test_write_utf32_with_big_endian_bom.txt."
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
