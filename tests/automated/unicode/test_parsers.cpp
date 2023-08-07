// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/unicode/parsers.hpp>

namespace cmp {

class parsers_test_module
    : public test_module<parsers_test_module>
{
public:
    parsers_test_module ()
    noexcept
        : test_module({
              &parsers_test_module
                  :: test_parse_bool,

              &parsers_test_module
                  :: test_parse_integer,

              &parsers_test_module
                  :: test_parse_floating_point
          })
    {
    } // function -------------------------------------------------------------

    // Test Tooling -----------------------------------------------------------

    static
    bool
    expect_successful_bool_parse (
        std::u8string text,
        bool_format format,
        bool expected_value
    )
    noexcept
    {
        bool result;
        try {
            result = parse_bool(text, format);
        } catch (const parse_failed& ex) {
            return false;
        }
        return result == expected_value;
    } // function -------------------------------------------------------------

    static
    bool
    expect_failed_bool_parse (
        std::u8string text,
        bool_format format,
        parse_failed::type expected_error
    )
    noexcept
    {
        bool result;
        try {
            result = parse_bool(text, format);
        } catch (const parse_failed& ex) {
            return ex.get_type() == expected_error;
        }
        return false;
    } // function -------------------------------------------------------------

    template <
        typename T
    >
    static
    bool
    expect_successful_integer_parse (
        std::u8string text,
        integer_format format,
        T expected_value
    )
    noexcept
    {
        T result;
        try {
            result = parse_integer<T>(text, format);
        } catch (const parse_failed& ex) {
            return false;
        }
        return result == expected_value;
    } // function -------------------------------------------------------------

    template <
        typename T
    >
    static
    bool
    expect_failed_integer_parse (
        std::u8string text,
        integer_format format,
        parse_failed::type expected_error
    )
    noexcept
    {
        T result;
        try {
            result = parse_integer<T>(text, format);
        } catch (const parse_failed& ex) {
            return ex.get_type() == expected_error;
        }
        return false;
    } // function -------------------------------------------------------------

    template <
        typename T
    >
    static
    bool
    expect_successful_floating_point_parse (
        std::u8string text,
        floating_point_format format,
        T expected_value
    )
    noexcept
    {
        T result;
        try {
            result = parse_floating_point<T>(text, format);
        } catch (const parse_failed& ex) {
            return false;
        }
        return result == expected_value;
    } // function -------------------------------------------------------------

    template <
        typename T
    >
    static
    bool
    expect_successful_floating_point_parse_approximated (
        std::u8string text,
        floating_point_format format,
        T expected_value,
        int relevant_decimal_places
    )
    noexcept
    {
        T result;
        try {
            result = parse_floating_point<T>(text, format);
        } catch (const parse_failed& ex) {
            return false;
        }
        return cmp_equal(result, expected_value, relevant_decimal_places);
    } // function -------------------------------------------------------------

    template <
        typename T
    >
    static
    bool
    expect_failed_floating_point_parse (
        std::u8string text,
        floating_point_format format,
        parse_failed::type expected_error
    )
    noexcept
    {
        T result;
        try {
            result = parse_floating_point<T>(text, format);
        } catch (const parse_failed& ex) {
            return ex.get_type() == expected_error;
        }
        return false;
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_parse_bool ()
    noexcept
    {
        start_test("test_parse_bool");

        std::u8string test_text;
        bool_format f;

        test_text = u8"yes";
        f.set_true_string(u8"yes");
        f.set_false_string(u8"no");
        if (!expect_successful_bool_parse(test_text, f, true)) {
            std::cout << "parse_bool failed on case #1."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"no";
        f.set_true_string(u8"yes");
        f.set_false_string(u8"no");
        if (!expect_successful_bool_parse(test_text, f, false)) {
            std::cout << "parse_bool failed on case #2."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"1";
        f.set_true_string(u8"true");
        f.set_false_string(u8"false");
        if (
            !expect_failed_bool_parse(
                test_text,
                f,
                parse_failed::type::neither_boolean
            )
        ) {
            std::cout << "parse_bool failed on case #3."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_parse_integer ()
    noexcept
    {
        start_test("test_parse_integer");

        std::u8string test_text;
        integer_format f;

        test_text = u8"+11";
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::none);
        if (!expect_successful_integer_parse<int>(test_text, f, 9)) {
            std::cout << "parse_integer failed on case #1."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"-2,317";
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        if (!expect_successful_integer_parse<int>(test_text, f, -1231)) {
            std::cout << "parse_integer failed on case #2."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"8A";
        f.set_radix(16);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        if (!expect_successful_integer_parse<int>(test_text, f, 138)) {
            std::cout << "parse_integer failed on case #3."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"-10";
        f.set_radix(36);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        if (!expect_successful_integer_parse<int>(test_text, f, -36)) {
            std::cout << "parse_integer failed on case #4."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"-100";
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        if (!expect_successful_integer_parse<int>(test_text, f, -100)) {
            std::cout << "parse_integer failed on case #5."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"97";
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        if (!expect_successful_integer_parse<int>(test_text, f, 97)) {
            std::cout << "parse_integer failed on case #6."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"-1000";
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::none);
        if (
            !expect_failed_integer_parse<unsigned int>(
                test_text,
                f,
                parse_failed::type::negative_unsigned
            )
        ) {
            std::cout << "parse_integer failed on case #7."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"+101";
        f.set_radix(16);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        if (
            !expect_successful_integer_parse<unsigned int>(test_text, f, 257)
        ) {
            std::cout << "parse_integer failed on case #8."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"+";
        f.set_radix(20);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::period);
        if (
            !expect_failed_integer_parse<unsigned int>(
                test_text,
                f,
                parse_failed::type::digit_character_expected
            )
        ) {
            std::cout << "parse_integer failed on case #9."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"59";
        f.set_radix(8);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::period);
        if (
            !expect_failed_integer_parse<unsigned int>(
                test_text,
                f,
                parse_failed::type::digit_character_expected
            )
        ) {
            std::cout << "parse_integer failed on case #10."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_parse_floating_point ()
    noexcept
    {
        start_test("test_parse_floating_point");

        std::u8string test_text;
        floating_point_format f;

        test_text = u8"+11";
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse<double>(test_text, f, 9.0)
        ) {
            std::cout << "parse_floating_point failed on case #1."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"-2,317";
        f.set_radix(8);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse<double>(
                test_text,
                f,
                -1231.0
            )
        ) {
            std::cout << "parse_floating_point failed on case #2."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"8A";
        f.set_radix(16);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse<double>(
                test_text,
                f,
                138.0
            )
        ) {
            std::cout << "parse_floating_point failed on case #3."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"-10";
        f.set_radix(36);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse<double>(
                test_text,
                f,
                -36.0
            )
        ) {
            std::cout << "parse_floating_point failed on case #4."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"-100";
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse<double>(
                test_text,
                f,
                -100.0
            )
        ) {
            std::cout << "parse_floating_point failed on case #5."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"41.5";
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::comma);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse<double>(
                test_text,
                f,
                41.5
            )
        ) {
            std::cout << "parse_floating_point failed on case #6."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"95.124";
        f.set_radix(10);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse_approximated<double>(
                test_text,
                f,
                95.124,
                3
            )
        ) {
            std::cout << "parse_floating_point failed on case #7."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"+33.0625";
        f.set_radix(10);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse_approximated<double>(
                test_text,
                f,
                33.0625,
                4
            )
        ) {
            std::cout << "parse_floating_point failed on case #8."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"+33.06";
        f.set_radix(10);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::up_to);
        f.set_radix_place_count(2);
        if (
            !expect_successful_floating_point_parse_approximated<double>(
                test_text,
                f,
                33.06,
                2
            )
        ) {
            std::cout << "parse_floating_point failed on case #9."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"+33.06250";
        f.set_radix(10);
        f.set_sign_status(sign_status::always_show);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::exactly_equal);
        f.set_radix_place_count(5);
        if (
            !expect_successful_floating_point_parse_approximated<double>(
                test_text,
                f,
                33.0625,
                4
            )
        ) {
            std::cout << "parse_floating_point failed on case #10."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"10.8";
        f.set_radix(16);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::none);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_successful_floating_point_parse_approximated<double>(
                test_text,
                f,
                16.5,
                1
            )
        ) {
            std::cout << "parse_floating_point failed on case #11."
                      << std::endl;

            return false;
        }

        end_stage();

        test_text = u8"59.8";
        f.set_radix(8);
        f.set_sign_status(sign_status::only_when_negative);
        f.set_thousands_separator(thousands_separator::period);
        f.set_radix_character(radix_character::period);
        f.set_radix_place_limit(radix_place_limit::none);
        f.set_radix_place_count(0);
        if (
            !expect_failed_floating_point_parse<double>(
                test_text,
                f,
                parse_failed::type::digit_character_expected
            )
        ) {
            std::cout << "parse_floating_point failed on case #12."
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
    return cmp::parsers_test_module{}.run_tests();
} // function -----------------------------------------------------------------
