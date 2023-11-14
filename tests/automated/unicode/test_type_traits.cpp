// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/unicode/type_traits.hpp>

namespace cmp {

class type_traits_test_module
    : public test_module<type_traits_test_module>
{
public:
    type_traits_test_module ()
    noexcept
        : test_module({
              &type_traits_test_module
                  :: test_is_unicode_text_object_v,

              &type_traits_test_module
                  :: test_is_raii_unicode_text_object_v,

              &type_traits_test_module
                  :: test_is_writable_raii_unicode_text_object_v
          })
    {
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_is_unicode_text_object_v ()
    noexcept
    {
        start_test("test_is_unicode_text_object_v");

        if (!is_unicode_text_object_v<std::u8string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "std::u8string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const std::u8string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const std::u8string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile std::u8string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile std::u8string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile std::u8string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile std::u8string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<std::u16string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "std::u16string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const std::u16string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const std::u16string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile std::u16string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile std::u16string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile std::u16string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile std::u16string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<std::u32string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "std::u32string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const std::u32string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const std::u32string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile std::u32string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile std::u32string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile std::u32string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile std::u32string "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<std::u8string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "std::u8string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const std::u8string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const std::u8string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile std::u8string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile std::u8string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile std::u8string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile std::u8string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<std::u16string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "std::u16string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const std::u16string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const std::u16string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile std::u16string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile std::u16string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile std::u16string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile std::u16string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<std::u32string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "std::u32string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const std::u32string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const std::u32string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile std::u32string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile std::u32string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile std::u32string_view>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile std::u32string_view "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<char8_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "char8_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const char8_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const char8_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile char8_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile char8_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile char8_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile char8_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<char8_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "char8_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const char8_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const char8_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile char8_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile char8_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile char8_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile char8_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<char16_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "char16_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const char16_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const char16_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile char16_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile char16_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile char16_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile char16_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<char16_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "char16_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const char16_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const char16_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile char16_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile char16_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile char16_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile char16_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<char32_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "char32_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const char32_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const char32_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile char32_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile char32_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile char32_t*>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile char32_t* "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_unicode_text_object_v<char32_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "char32_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const char32_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const char32_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<volatile char32_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "volatile char32_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_unicode_text_object_v<const volatile char32_t* const>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "const volatile char32_t* const "
                         "is not a Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_unicode_text_object_v<std::string>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "std::string "
                         "is a Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_unicode_text_object_v<char>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "char "
                         "is a Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_unicode_text_object_v<int>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "int "
                         "is a Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_unicode_text_object_v<double>) {
            std::cout << "is_unicode_text_object_v "
                         "is saying that "
                         "double "
                         "is a Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_is_raii_unicode_text_object_v ()
    noexcept
    {
        start_test("test_is_raii_unicode_text_object_v");

        if (!is_raii_unicode_text_object_v<std::u8string>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u8string "
                         "is not an RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_raii_unicode_text_object_v<const std::u8string>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u8string "
                         "is not an RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_raii_unicode_text_object_v<std::u16string>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u16string "
                         "is not an RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_raii_unicode_text_object_v<const std::u16string>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u16string "
                         "is not an RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_raii_unicode_text_object_v<std::u32string>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u32string "
                         "is not an RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (!is_raii_unicode_text_object_v<const std::u32string>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u32string "
                         "is not an RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_raii_unicode_text_object_v<std::u8string_view>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u8string_view "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<const std::u8string_view>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u8string_view "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_raii_unicode_text_object_v<std::u16string_view>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u16string_view "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<const std::u16string_view>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u16string_view "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_raii_unicode_text_object_v<std::u32string_view>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u32string_view "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<const std::u32string_view>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u32string_view "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_raii_unicode_text_object_v<char8_t[3]>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "char8_t[3] "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<const char8_t[3]>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const char8_t[3] "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<char8_t*>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "char8_t* "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<const char8_t*>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const char8_t* "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<char8_t* const>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "char8_t* const "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<const char8_t* const>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "const char8_t* const "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<std::string>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "std::string "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<char>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "char "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<int>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "int "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_raii_unicode_text_object_v<double>) {
            std::cout << "is_raii_unicode_text_object_v "
                         "is saying that "
                         "double "
                         "is an RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_is_writable_raii_unicode_text_object_v ()
    noexcept
    {
        start_test("test_is_writable_raii_unicode_text_object_v");

        if (!is_writable_raii_unicode_text_object_v<std::u8string>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u8string "
                         "is not a writable RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const std::u8string>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u8string "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_writable_raii_unicode_text_object_v<std::u16string>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u16string "
                         "is not a writable RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const std::u16string>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u16string "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (!is_writable_raii_unicode_text_object_v<std::u32string>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u32string "
                         "is not a writable RAII Unicode text object type "
                         "but it is."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const std::u32string>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u32string "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_writable_raii_unicode_text_object_v<std::u8string_view>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u8string_view "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const std::u8string_view>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u8string_view "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_writable_raii_unicode_text_object_v<std::u16string_view>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u16string_view "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const std::u16string_view>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u16string_view "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_writable_raii_unicode_text_object_v<std::u32string_view>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "std::u32string_view "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const std::u32string_view>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const std::u32string_view "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        end_stage();

        if (is_writable_raii_unicode_text_object_v<char8_t[3]>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "char8_t[3] "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const char8_t[3]>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const char8_t[3] "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<char8_t*>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "char8_t* "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const char8_t*>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const char8_t* "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<char8_t* const>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "char8_t* const "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<const char8_t* const>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "const char8_t* const "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<std::string>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "std::string "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<char>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "char "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<int>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "int "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
                      << std::endl;

            return false;
        }

        if (is_writable_raii_unicode_text_object_v<double>) {
            std::cout << "is_writable_raii_unicode_text_object_v "
                         "is saying that "
                         "double "
                         "is a writable RAII Unicode text object type "
                         "but it isn't."
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
    return cmp::type_traits_test_module{}.run_tests();
} // function -----------------------------------------------------------------
