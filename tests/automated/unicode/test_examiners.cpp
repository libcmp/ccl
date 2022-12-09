// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/unicode/examiners.hpp>

namespace cmp {

class examiners_test_module
    : public test_module<examiners_test_module>
{
public:
    examiners_test_module ()
    noexcept
        : test_module({
              &examiners_test_module
                  :: test_fits_in_7_bits,

              &examiners_test_module
                  :: test_is_standalone_byte,

              &examiners_test_module
                  :: test_is_leading_byte,

              &examiners_test_module
                  :: test_is_trailing_byte,

              &examiners_test_module
                  :: test_is_radix_digit
          })
    {
    }

    // Tests ------------------------------------------------------------------

    bool
    test_fits_in_7_bits ()
    noexcept
    {
        start_test("test_fits_in_7_bits");

        if (fits_in_7_bits(0b1000'0001)) {
            std::cout << "fits_in_7_bits is saying that 1000'0001 "
                         "fits in 7 bits but it doesn't."
                      << std::endl;

            return false;
        }

        if (!fits_in_7_bits(0b0100'0000)) {
            std::cout << "fits_in_7_bits is saying that 0100'0000 "
                         "doesn't fit in 7 bits but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_is_standalone_byte ()
    noexcept
    {
        start_test("test_is_standalone_byte");

        if (is_standalone_byte(0b1000'0001)) {
            std::cout << "is_standalone_byte is saying that 1000'0001 "
                         "is a standalone code unit but it isn't."
                      << std::endl;

            return false;
        }

        if (!is_standalone_byte(0b0100'0000)) {
            std::cout << "is_standalone_byte is saying that 0100'0000 "
                         "isn't a standalone code unit but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_is_leading_byte ()
    noexcept
    {
        start_test("test_is_leading_byte");

        if (is_leading_byte(0b0000'0000)) {
            std::cout << "is_leading_byte is saying that 0000'0000 "
                         "is a leading code unit but it isn't."
                      << std::endl;

            return false;
        }

        if (is_leading_byte(0b1000'0000)) {
            std::cout << "is_leading_byte is saying that 1000'0000 "
                         "is a leading code unit but it isn't."
                      << std::endl;

            return false;
        }

        if (!is_leading_byte(0b1100'0000)) {
            std::cout << "is_leading_byte is saying that 1100'0000 "
                         "isn't a leading code unit but it is."
                      << std::endl;

            return false;
        }

        if (!is_leading_byte(0b1110'0000)) {
            std::cout << "is_leading_byte is saying that 1110'0000 "
                         "isn't a leading code unit but it is."
                      << std::endl;

            return false;
        }

        if (!is_leading_byte(0b1111'0000)) {
            std::cout << "is_leading_byte is saying that 1111'0000 "
                         "isn't a leading code unit but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_is_trailing_byte ()
    noexcept
    {
        start_test("test_is_trailing_byte");

        if (is_trailing_byte(0b0000'0000)) {
            std::cout << "is_trailing_byte is saying that 0000'0000 "
                         "is a trailing code unit but it isn't."
                      << std::endl;

            return false;
        }

        if (is_trailing_byte(0b0100'0000)) {
            std::cout << "is_trailing_byte is saying that 0100'0000 "
                         "is a trailing code unit but it isn't."
                      << std::endl;

            return false;
        }

        if (is_trailing_byte(0b1100'0000)) {
            std::cout << "is_trailing_byte is saying that 1100'0000 "
                         "is a trailing code unit but it isn't."
                      << std::endl;

            return false;
        }

        if (!is_trailing_byte(0b1000'0000)) {
            std::cout << "is_trailing_byte is saying that 1000'0000 "
                         "isn't a trailing code unit but it is."
                      << std::endl;

            return false;
        }

        if (!is_trailing_byte(0b1000'0001)) {
            std::cout << "is_trailing_byte is saying that 1000'0001 "
                         "isn't a trailing code unit but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_is_radix_digit ()
    noexcept
    {
        start_test("test_is_radix_digit");

        if (!is_radix_digit('0', 8)) {
            std::cout << "is_radix_digit is saying that '0' "
                         "is not a base 8 digit but it is."
                      << std::endl;

            return false;
        }

        if (!is_radix_digit('0', 10)) {
            std::cout << "is_radix_digit is saying that '0' "
                         "is not a base 10 digit but it is."
                      << std::endl;

            return false;
        }

        if (!is_radix_digit('0', 12)) {
            std::cout << "is_radix_digit is saying that '0' "
                         "is not a base 12 digit but it is."
                      << std::endl;

            return false;
        }

        if (is_radix_digit('9', 8)) {
            std::cout << "is_radix_digit is saying that '9' "
                         "is a base 8 digit but it isn't."
                      << std::endl;

            return false;
        }

        if (!is_radix_digit('9', 10)) {
            std::cout << "is_radix_digit is saying that '9' "
                         "is not a base 10 digit but it is."
                      << std::endl;

            return false;
        }

        if (is_radix_digit('a', 10)) {
            std::cout << "is_radix_digit is saying that 'a' "
                         "is a base 10 digit but it isn't."
                      << std::endl;

            return false;
        }

        if (!is_radix_digit('C', 16)) {
            std::cout << "is_radix_digit is saying that 'C' "
                         "is not a base 16 digit but it is."
                      << std::endl;

            return false;
        }

        if (!is_radix_digit('p', 26)) {
            std::cout << "is_radix_digit is saying that the 16th letter of "
                         "the alphabet ('p') is not a base 26 digit but it is."
                      << std::endl;

            return false;
        }

        if (is_radix_digit('Q', 26)) {
            std::cout << "is_radix_digit is saying that the 17th letter of "
                         "the alphabet ('Q') is a base 26 digit but it isn't."
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
    return cmp::examiners_test_module{}.run_tests();
}
