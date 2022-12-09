// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/unicode/formatters.hpp>

namespace cmp {

class formatters_test_module
    : public test_module<formatters_test_module>
{
public:
    formatters_test_module ()
    noexcept
        : test_module({
              &formatters_test_module
                  :: test_format_bool,

              &formatters_test_module
                  :: test_format_integer,

              &formatters_test_module
                  :: test_format_floating_point
          })
    {
    }

    // Tests ------------------------------------------------------------------

    bool
    test_format_bool ()
    noexcept
    {
        start_test("test_format_bool");

        bool test_value;
        bool_format f;
        std::u8string text;

        test_value = true;
        f.set_true_string(u8"yes");

        text = format_bool<std::u8string>(test_value, f);
        if (text != u8"yes") {
            std::cout << "format_bool did not format "
                         "the first bool correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = false;
        f.set_false_string(u8"no");

        text = format_bool<std::u8string>(test_value, f);
        if (text != u8"no") {
            std::cout << "format_bool did not format "
                         "the second bool correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_format_integer ()
    noexcept
    {
        start_test("test_format_integer");

        int test_value1;
        unsigned int test_value2;
        integer_format f;
        std::u8string text;

        test_value1 = 9;
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        text = format_integer<std::u8string>(test_value1, f);
        if (text != u8"+11") {
            std::cout << "format_integer did not format "
                         "the first number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value1 = -1231;
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        text = format_integer<std::u8string>(test_value1, f);
        if (text != u8"-2,317") {
            std::cout << "format_integer did not format "
                         "the second number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value1 = 138;
        f.set_radix(16);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        text = format_integer<std::u8string>(test_value1, f);
        if (text != u8"8A") {
            std::cout << "format_integer did not format "
                         "the third number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value1 = -36;
        f.set_radix(36);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        text = format_integer<std::u8string>(test_value1, f);
        if (text != u8"-10") {
            std::cout << "format_integer did not format "
                         "the fourth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value1 = -100;
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        text = format_integer<std::u8string>(test_value1, f);
        if (text != u8"-100") {
            std::cout << "format_integer did not format "
                         "the fifth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value2 = 97;
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        text = format_integer<std::u8string>(test_value2, f);
        if (text != u8"97") {
            std::cout << "format_integer did not format "
                         "the sixth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_format_floating_point ()
    noexcept
    {
        start_test("test_format_floating_point");

        double test_value;
        floating_point_format f;
        std::u8string text;

        test_value = 9.0;
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"+11") {
            std::cout << "format_floating_point did not format "
                         "the first number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = -1231;
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"-2,317") {
            std::cout << "format_floating_point did not format "
                         "the second number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = 138;
        f.set_radix(16);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"8A") {
            std::cout << "format_floating_point did not format "
                         "the third number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = -36;
        f.set_radix(36);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"-10") {
            std::cout << "format_floating_point did not format "
                         "the fourth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = -100;
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"-100") {
            std::cout << "format_floating_point did not format "
                         "the fifth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = 41.5;
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"41.5") {
            std::cout << "format_floating_point did not format "
                         "the sixth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = 95.125;
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"95.125") {
            std::cout << "format_floating_point did not format "
                         "the seventh number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = 33.0625;
        f.set_radix(10);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"+33.0625") {
            std::cout << "format_floating_point did not format "
                         "the eighth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = 33.0625;
        f.set_radix(10);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::up_to);
        f.set_radix_place_count(2);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"+33.06") {
            std::cout << "format_floating_point did not format "
                         "the ninth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = 33.0625;
        f.set_radix(10);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::exactly_equal);
        f.set_radix_place_count(5);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"+33.06250") {
            std::cout << "format_floating_point did not format "
                         "the tenth number correctly."
                      << std::endl;

            return false;
        }

        end_stage();

        test_value = 16.5;
        f.set_radix(16);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        text = format_floating_point<std::u8string>(test_value, f);
        if (text != u8"10.8") {
            std::cout << "format_floating_point did not format "
                         "the eleventh number correctly."
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
    return cmp::formatters_test_module{}.run_tests();
}
