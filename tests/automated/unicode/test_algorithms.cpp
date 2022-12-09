// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class algorithms_test_module
    : public test_module<algorithms_test_module>
{
public:
    algorithms_test_module ()
    noexcept
        : test_module({
              &algorithms_test_module
                  :: test_starts_with,

              &algorithms_test_module
                  :: test_ends_with,

              &algorithms_test_module
                  :: test_append_code_point,

              &algorithms_test_module
                  :: test_prepend_code_point,

              &algorithms_test_module
                  :: test_validate_string
          })
    {
    }

    // Tests ------------------------------------------------------------------

    bool
    test_starts_with ()
    noexcept
    {
        start_test("test_starts_with");

        if (!starts_with(u8"starts with", u8"starts")) {
            std::cout << "starts_with said \"starts with\" doesn't "
                         "start with \"starts\" but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (starts_with(u8"starts with", u8"with")) {
            std::cout << "starts_with said \"starts with\" does "
                         "start with \"with\" but it doesn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!starts_with(u8"starts with", u8"starts with")) {
            std::cout << "starts_with said \"starts with\" doesn't "
                         "start with \"starts  with\" but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (starts_with(u8"starts with", u8"starts with!!!")) {
            std::cout << "starts_with said \"starts with\" does "
                         "start with \"starts with!!!\" but it doesn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (starts_with(u8"", u8"something")) {
            std::cout << "starts_with said that an empty string starts "
                         "with a non-empty string but it doesn't."
                      << std::endl;

            return false;
        }

        if (!starts_with(u8"something", u8"")) {
            std::cout << "starts_with said that a non-empty string doesn't "
                         "start with an empty string but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_ends_with ()
    noexcept
    {
        start_test("test_ends_with");

        if (!ends_with(u8"ends with", u8"with")) {
            std::cout << "ends_with said \"ends with\" doesn't "
                         "end with \"with\" but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (ends_with(u8"ends with", u8"ends")) {
            std::cout << "ends_with said \"ends with\" does "
                         "end with \"ends\" but it doesn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!ends_with(u8"ends with", u8"ends with")) {
            std::cout << "ends_with said \"ends with\" doesn't "
                         "end with \"ends with\" but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        if (ends_with(u8"ends with", u8"!!!ends with")) {
            std::cout << "ends_with said \"ends with\" does "
                         "end with \"!!!ends with\" but it doesn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (ends_with(u8"", u8"something")) {
            std::cout << "ends_with said that an empty string ends "
                         "with a non-empty string but it doesn't."
                      << std::endl;

            return false;
        }

        if (!ends_with(u8"something", u8"")) {
            std::cout << "ends_with said that a non-empty string doesn't "
                         "end with an empty string but it does."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_append_code_point ()
    noexcept
    {
        start_test("test_append_code_point");

        std::u8string utf8_string;
        append_code_point(utf8_string, 'c');
        append_code_point(utf8_string, 0x1F600);
        if (utf8_string != u8"c\U0001F600") {
            std::cout << "append_code_point failed to append the "
                         "correct code point to a UTF-8 string."
                      << std::endl;

            return false;
        }

        end_stage();

        std::u16string utf16_string;
        append_code_point(utf16_string, 'c');
        append_code_point(utf16_string, 0x1F600);
        if (utf16_string != u"c\U0001F600") {
            std::cout << "append_code_point failed to append the "
                         "correct code point to a UTF-16 string."
                      << std::endl;

            return false;
        }

        end_stage();

        std::u32string utf32_string;
        append_code_point(utf32_string, 'c');
        append_code_point(utf32_string, 0x1F600);
        if (utf32_string != U"c\U0001F600") {
            std::cout << "append_code_point failed to append the "
                         "correct code point to a UTF-32 string."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_prepend_code_point ()
    noexcept
    {
        start_test("test_prepend_code_point");

        std::u8string utf8_string;
        prepend_code_point(utf8_string, 0x1F600);
        prepend_code_point(utf8_string, 'c');
        if (utf8_string != u8"c\U0001F600") {
            std::cout << "prepend_code_point failed to prepend the "
                         "correct code point to a UTF-8 string."
                      << std::endl;

            return false;
        }

        end_stage();

        std::u16string utf16_string;
        prepend_code_point(utf16_string, 0x1F600);
        prepend_code_point(utf16_string, 'c');
        if (utf16_string != u"c\U0001F600") {
            std::cout << "prepend_code_point failed to prepend the "
                         "correct code point to a UTF-16 string."
                      << std::endl;

            return false;
        }

        end_stage();

        std::u32string utf32_string;
        prepend_code_point(utf32_string, 0x1F600);
        prepend_code_point(utf32_string, 'c');
        if (utf32_string != U"c\U0001F600") {
            std::cout << "prepend_code_point failed to prepend the "
                         "correct code point to a UTF-32 string."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_validate_string ()
    noexcept
    {
        start_test("test_validate_string");

        const char8_t valid_utf8_string[]{u8"abc\nxyz"};
        by_code_point bcp1{valid_utf8_string};

        if (validate_string(valid_utf8_string) != bcp1.cend()) {
            std::cout << "validate_string is saying that "
                         "valid_utf8_string is not fully valid but it is."
                      << std::endl;

            return false;
        }

        std::u8string invalid_utf8_string{u8"valid portion"};
        invalid_utf8_string.push_back(0b1000'0000);
        by_code_point bcp2{invalid_utf8_string};

        if (validate_string(invalid_utf8_string) == bcp2.cend()) {
            std::cout << "validate_string is saying that "
                         "invalid_utf8_string is fully valid but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        const std::u16string valid_utf16_string{u"abc\nxyz"};
        by_code_point bcp3{valid_utf16_string};

        if (validate_string(valid_utf16_string) != bcp3.cend()) {
            std::cout << "validate_string is saying that "
                         "valid_utf16_string is not fully valid but it is."
                      << std::endl;

            return false;
        }

        std::u16string invalid_utf16_string{u"valid portion"};
        invalid_utf16_string.push_back(0xD83D);
        by_code_point bcp4{invalid_utf16_string};

        if (validate_string(invalid_utf16_string) == bcp4.cend()) {
            std::cout << "validate_string is saying that "
                         "invalid_utf16_string is fully valid but it isn't."
                      << std::endl;

            return false;
        }

        std::u16string invalid_utf16_string2{u"valid portion"};
        invalid_utf16_string2.push_back(0xDC69);
        by_code_point bcp5{invalid_utf16_string2};

        if (validate_string(invalid_utf16_string2) == bcp5.cend()) {
            std::cout << "validate_string is saying that "
                         "invalid_utf16_string2 is fully valid but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        const char32_t valid_utf32_string[]{U"abc\nxyz"};
        by_code_point bcp6{valid_utf32_string};

        if (validate_string(valid_utf32_string) != bcp6.cend()) {
            std::cout << "validate_string is saying that "
                         "valid_utf32_string is not fully valid but it is."
                      << std::endl;

            return false;
        }

        std::u32string invalid_utf32_string{U"valid portion"};
        invalid_utf32_string.push_back(maximum_code_point + 1);
        by_code_point bcp7{invalid_utf32_string};

        if (validate_string(invalid_utf32_string) == bcp7.cend()) {
            std::cout << "validate_string is saying that "
                         "invalid_utf32_string is fully valid but it isn't."
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
    return cmp::algorithms_test_module{}.run_tests();
}
