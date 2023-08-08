// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/unicode/by_code_point.hpp>

namespace cmp {

class by_code_point_test_module
    : public test_module<by_code_point_test_module>
{
public:
    by_code_point_test_module ()
    noexcept
        : test_module({
              &by_code_point_test_module
                  :: test_by_code_point_char,

              &by_code_point_test_module
                  :: test_by_code_point_utf8,

              &by_code_point_test_module
                  :: test_by_code_point_utf16,

              &by_code_point_test_module
                  :: test_by_code_point_utf32,

              &by_code_point_test_module
                  :: test_by_code_point_wchar
          })
    {
    } // function -------------------------------------------------------------

    // Test Tooling -----------------------------------------------------------

    template <
        typename CodeUnit
    >
    bool
    test_by_code_point_generic (
        std::basic_string<CodeUnit> test_value
    )
    noexcept
    {
        std::cout << "String length: "
                  << test_value.length()
                  << std::endl;

        by_code_point range{test_value};

        try {
            bool found{false};
            for (char32_t current_code_point : range) {
                if (current_code_point == 's') {
                    found = true;
                }
            }

            if (!found) {
                std::cout << "Forward search did not find character."
                          << std::endl;

                return false;
            }
        } catch (const invalid_unicode_encoding& ex) {
            std::cout << "Exception: "
                      << ex.what()
                      << std::endl;

            return false;
        } catch (const iterated_past_end& ex) {
            std::cout << "Exception: "
                      << ex.what()
                      << std::endl;

            return false;
        }

        try {
            bool found{false};
            for (auto i{range.crbegin()}; i != range.crend(); ++i) {
                if (*i == 's') {
                    found = true;
                }
            }

            if (!found) {
                std::cout << "Reverse search did not find character."
                          << std::endl;

                return false;
            }
        } catch (const invalid_unicode_encoding& ex) {
            std::cout << "Exception: "
                      << ex.what()
                      << std::endl;

            return false;
        } catch (const iterated_past_end& ex) {
            std::cout << "Exception: "
                      << ex.what()
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_by_code_point_char ()
    noexcept
    {
        start_test("test_by_code_point_char");

        if (!test_by_code_point_generic<char>("test\nxyz")) {
            std::cout << "test_by_code_point_char has failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_by_code_point_utf8 ()
    noexcept
    {
        start_test("test_by_code_point_utf8");

        if (!test_by_code_point_generic<char8_t>(u8"test\n¯\\_(ツ)_/¯")) {
            std::cout << "test_by_code_point_utf8 has failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_by_code_point_utf16 ()
    noexcept
    {
        start_test("test_by_code_point_utf16");

        if (!test_by_code_point_generic<char16_t>(u"test\n¯\\_(ツ)_/¯")) {
            std::cout << "test_by_code_point_utf16 has failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_by_code_point_utf32 ()
    noexcept
    {
        start_test("test_by_code_point_utf32");

        if (!test_by_code_point_generic<char32_t>(U"test\n¯\\_(ツ)_/¯")) {
            std::cout << "test_by_code_point_utf32 has failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_by_code_point_wchar ()
    noexcept
    {
        start_test("test_by_code_point_wchar");

        if (!test_by_code_point_generic<wchar_t>(L"test\n¯\\_(ツ)_/¯")) {
            std::cout << "test_by_code_point_wchar has failed."
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
    return cmp::by_code_point_test_module{}.run_tests();
} // function -----------------------------------------------------------------
