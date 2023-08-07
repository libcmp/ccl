// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/core/general.hpp>

namespace cmp {

class core_general_test_module
    : public test_module<core_general_test_module>
{
public:
    core_general_test_module ()
    noexcept
        : test_module({
              &core_general_test_module
                  :: test_cmp_equal,

              &core_general_test_module
                  :: test_count_decimal_digits,

              &core_general_test_module
                  :: test_count_hexadecimal_digits
          })
    {
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_cmp_equal ()
    noexcept
    {
        start_test("test_cmp_equal");

        if (!cmp::cmp_equal(1.123, 1.124, 2)) {
            std::cout << "cmp::cmp_equal is saying that 1.123 and 1.124 are "
                         "not equal up to 2 decimal places but they are."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!cmp::cmp_equal(1.1234, 1.1235, 3)) {
            std::cout << "cmp::cmp_equal is saying that 1.1234 and 1.1235 are "
                         "not equal up to 3 decimal places but they are."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::cmp_equal(1.12, 1.14, 2)) {
            std::cout << "cmp::cmp_equal is saying that 1.12 and 1.14 are "
                         "equal up to 2 decimal places but they aren't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::cmp_equal(1.123, 1.124, 3)) {
            std::cout << "cmp::cmp_equal is saying that 1.123 and 1.124 are "
                         "equal up to 3 decimal places but they aren't."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_count_decimal_digits ()
    noexcept
    {
        start_test("test_count_decimal_digits");

        if (cmp::count_digits(0, 10) != 1) {
            std::cout << "cmp::count_digits is saying that 0 "
                         "doesn't have 1 decimal digit but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(9, 10) != 1) {
            std::cout << "cmp::count_digits is saying that 9 "
                         "doesn't have 1 decimal digit but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(15, 10) != 2) {
            std::cout << "cmp::count_digits is saying that 15 "
                         "doesn't have 2 decimal digits but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(-15, 10) != 2) {
            std::cout << "cmp::count_digits is saying that -15 "
                         "doesn't have 2 decimal digits but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(1024, 10) != 4) {
            std::cout << "cmp::count_digits is saying that 1024 "
                         "doesn't have 4 decimal digits but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_count_hexadecimal_digits ()
    noexcept
    {
        start_test("test_count_hexadecimal_digits");

        if (cmp::count_digits(0x0, 16) != 1) {
            std::cout << "cmp::count_digits is saying that 0x0 "
                         "doesn't have 1 hexadecimal digit but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(0xC, 16) != 1) {
            std::cout << "cmp::count_digits is saying that 0xC "
                         "doesn't have 1 hexadecimal digit but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(0x21, 16) != 2) {
            std::cout << "cmp::count_digits is saying that 0x21 "
                         "doesn't have 2 hexadecimal digits but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(-0x21, 16) != 2) {
            std::cout << "cmp::count_digits is saying that -0x21 "
                         "doesn't have 2 hexadecimal digits but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (cmp::count_digits(0xCAFE, 16) != 4) {
            std::cout << "cmp::count_digits is saying that 0xCAFE "
                         "doesn't have 4 hexadecimal digits but it does."
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
    return cmp::core_general_test_module{}.run_tests();
} // function -----------------------------------------------------------------
