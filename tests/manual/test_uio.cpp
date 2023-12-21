// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/uio.hpp>

namespace cmp {

class uio_test_module
    : public test_module<uio_test_module>
{
public:
    uio_test_module ()
    noexcept
        : test_module({
              &uio_test_module
                  :: test_output,

              &uio_test_module
                  :: test_input,

              &uio_test_module
                  :: test_parsing_and_formatting
          })
    {
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_output ()
    noexcept
    {
        start_test("test_output");

        std::u8string utf8_string{u8"¯\\_(ツ)_/¯1"};
        std::u16string utf16_string{u"¯\\_(ツ)_/¯2"};
        std::u32string utf32_string{U"¯\\_(ツ)_/¯3"};

        uout << utf8_string << u8".\n";
        uout << utf16_string << u".\n";
        uout << utf32_string << U".\n";
        uout << cmp::flush;

        end_stage();

        uerr << utf8_string << u8".\n";
        uerr << utf16_string << u".\n";
        uerr << utf32_string << U".\n";
        uerr << cmp::flush;

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_input ()
    noexcept
    {
        start_test("test_input");

        uout << u8"Enter ツ: ";
        std::u8string input;
        uin.read_line(input);
        uout << "Entered line: " << input << '\n' << cmp::flush;

        if (input != u8"ツ") {
            std::cout << "The input does not match the expected content."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_parsing_and_formatting ()
    noexcept
    {
        start_test("test_parsing_and_formatting");

        double input1;
        int input2;

        uout << u8"Enter 5.5: ";
        uin >> input1;
        uout << "Entered value: " << input1 << '\n' << cmp::flush;

        if (input1 != 5.5) {
            std::cout << "The parsed input does not match the expected value."
                      << std::endl;

            return false;
        }

        end_stage();

        uout << u8"Enter -75: ";
        uin >> input2;
        uout << "Entered value: " << input2 << '\n' << cmp::flush;

        if (input2 != -75) {
            std::cout << "The parsed input does not match the expected value."
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
    return cmp::uio_test_module{}.run_tests();
} // function -----------------------------------------------------------------
