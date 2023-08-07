// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/string_io_resource.hpp>

namespace cmp {

class string_io_resource_test_module
    : public test_module<string_io_resource_test_module>
{
public:
    string_io_resource_test_module ()
    noexcept
        : test_module({
              &string_io_resource_test_module
                  :: test_read_u8string,

              &string_io_resource_test_module
                  :: test_read_u16string,

              &string_io_resource_test_module
                  :: test_read_u32string,

              &string_io_resource_test_module
                  :: test_write_u8string,

              &string_io_resource_test_module
                  :: test_write_u16string,

              &string_io_resource_test_module
                  :: test_write_u32string,

              &string_io_resource_test_module
                  :: test_set_position_u8string,

              &string_io_resource_test_module
                  :: test_set_position_u16string,

              &string_io_resource_test_module
                  :: test_set_position_u32string
          })
    {
    } // function -------------------------------------------------------------

    // Test Tooling -----------------------------------------------------------

    template <
        typename CodeUnit,
        typename InputResource
    >
    bool
    test_read_generic (
        InputResource& resource
    )
    noexcept
    {
        constexpr std::size_t data_size{5 * sizeof (CodeUnit)};
        std::byte data[data_size];
        auto bytes_read{resource.read(data, data_size)};

        if (bytes_read != data_size) {
            std::cout << "The data was not fully read."
                      << std::endl;

            return false;
        }

        if (
            static_cast<char>(data[0 * sizeof (CodeUnit)]) != 'H'
                || static_cast<char>(data[1 * sizeof (CodeUnit)]) != 'e'
                || static_cast<char>(data[2 * sizeof (CodeUnit)]) != 'l'
                || static_cast<char>(data[3 * sizeof (CodeUnit)]) != 'l'
                || static_cast<char>(data[4 * sizeof (CodeUnit)]) != 'o'
        ) {
            std::cout << "The data read does not match the data expected."
                      << std::endl;

            return false;
        }

        end_stage();

        bytes_read = resource.read(data, 3 * sizeof (CodeUnit));
        if (bytes_read != 2 * sizeof (CodeUnit)) {
            std::cout << "We asked for 3 code units when there were only "
                         "2 left and we didn't get back the correct "
                         "number of code units."
                      << std::endl;

            return false;
        }

        if (
            static_cast<char>(data[0 * sizeof (CodeUnit)]) != '!'
                || static_cast<char>(data[1 * sizeof (CodeUnit)]) != '\n'
        ) {
            std::cout << "The data read does not match the data expected."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    template <
            typename CodeUnit,
            typename OutputResource
    >
    bool
    test_write_generic (
        OutputResource& resource
    )
    noexcept
    {
        CodeUnit data[] = {
            static_cast<CodeUnit>('H'),
            static_cast<CodeUnit>('e'),
            static_cast<CodeUnit>('l'),
            static_cast<CodeUnit>('l'),
            static_cast<CodeUnit>('o')
        };
        auto bytes_written{
            resource.write(
                reinterpret_cast<std::byte*>(data),
                5 * sizeof (CodeUnit)
            )
        };

        if (bytes_written != 5 * sizeof (CodeUnit)) {
            std::cout << "The data was not fully written."
                      << std::endl;

            return false;
        }

        resource.flush();
        std::basic_string_view<CodeUnit> expected_data;
        if constexpr (std::is_same_v<CodeUnit, char8_t>) {
            expected_data = u8"Hello";
        } else if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            expected_data = u"Hello";
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            expected_data = U"Hello";
        } else {
            std::cout << "test_write_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t or char32_t."
                      << std::endl;

            return false;
        }
        if (resource.grab_content() != expected_data) {
            std::cout << "The data written does not match the data expected."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    template <
        typename CodeUnit,
        typename OutputResource
    >
    bool
    test_set_position_generic (
        OutputResource& resource
    )
    noexcept
    {
        CodeUnit data[] = {
            static_cast<CodeUnit>('H'),
            static_cast<CodeUnit>('e'),
            static_cast<CodeUnit>('l'),
            static_cast<CodeUnit>('l'),
            static_cast<CodeUnit>('o')
        };
        constexpr std::size_t data_size{5 * sizeof (CodeUnit)};
        auto bytes_written{
            resource.write(reinterpret_cast<std::byte*>(data), data_size)
        };

        if (bytes_written != data_size) {
            std::cout << "The data was not fully written."
                      << std::endl;

            return false;
        }

        resource.flush();
        std::basic_string_view<CodeUnit> expected_data;
        if constexpr (std::is_same_v<CodeUnit, char8_t>) {
            expected_data = u8"Hello";
        } else if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            expected_data = u"Hello";
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            expected_data = U"Hello";
        } else {
            std::cout << "test_set_position_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t or char32_t."
                      << std::endl;

            return false;
        }
        if (resource.grab_content() != expected_data) {
            std::cout << "The data written does not match the data expected."
                      << std::endl;

            return false;
        }

        resource.set_position(0, position_reference::begin);
        CodeUnit y{'Y'};
        resource.write(reinterpret_cast<std::byte*>(&y), sizeof (CodeUnit));

        resource.set_position(0, position_reference::end);
        CodeUnit w{'w'};
        resource.write(reinterpret_cast<std::byte*>(&w), sizeof (CodeUnit));

        resource.flush();
        if constexpr (std::is_same_v<CodeUnit, char8_t>) {
            expected_data = u8"Yellow";
        } else if constexpr (std::is_same_v<CodeUnit, char16_t>) {
            expected_data = u"Yellow";
        } else if constexpr (std::is_same_v<CodeUnit, char32_t>) {
            expected_data = U"Yellow";
        } else {
            std::cout << "test_set_position_generic was called with a "
                         "non-Unicode code unit type. Please use one of "
                         "char8_t, char16_t or char32_t."
                      << std::endl;

            return false;
        }
        if (resource.grab_content() != expected_data) {
            std::cout << "The data written does not match the data expected."
                      << std::endl;

            return false;
        }

        if (!resource.is_at_end()) {
            std::cout << "is_at_end is incorrectly reporting "
                         "that the resource is not at the end."
                      << std::endl;

            return false;
        }

        resource.set_position(0, position_reference::begin);
        constexpr std::size_t final_data_size{data_size + 1};
        std::byte data_read_back[final_data_size];
        resource.read(data_read_back, final_data_size);

        if (resource.grab_content() != expected_data) {
            std::cout << "The string content is not what was expected."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_read_u8string ()
    noexcept
    {
        start_test("test_read_u8string");

        u8string_io_resource resource{u8"Hello!\n"};

        if (!test_read_generic<char8_t>(resource)) {
            std::cout << "test_read_u8string failed to read "
                         "from the string IO resource."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_u16string ()
    noexcept
    {
        start_test("test_read_u16string");

        u16string_io_resource resource{u"Hello!\n"};

        if (!test_read_generic<char16_t>(resource)) {
            std::cout << "test_read_u16string failed to read "
                         "from the string IO resource."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_u32string ()
    noexcept
    {
        start_test("test_read_u32string");

        u32string_io_resource resource{U"Hello!\n"};

        if (!test_read_generic<char32_t>(resource)) {
            std::cout << "test_read_u32string failed to read "
                         "from the string IO resource."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_u8string ()
    noexcept
    {
        start_test("test_write_u8string");

        u8string_io_resource resource;

        if (!test_write_generic<char8_t>(resource)) {
            std::cout << "test_write_u8string failed to write "
                         "to the string IO resource."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_u16string ()
    noexcept
    {
        start_test("test_write_u16string");

        u16string_io_resource resource;

        if (!test_write_generic<char16_t>(resource)) {
            std::cout << "test_write_u16string failed to write "
                         "to the string IO resource."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_u32string ()
    noexcept
    {
        start_test("test_write_u32string");

        u32string_io_resource resource;

        if (!test_write_generic<char32_t>(resource)) {
            std::cout << "test_write_u32string failed to write "
                         "to the string IO resource."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_set_position_u8string ()
    noexcept
    {
        start_test("test_set_position_u8string");

        u8string_io_resource resource;

        if (!test_set_position_generic<char8_t>(resource)) {
            std::cout << "test_set_position_u8string failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_set_position_u16string ()
    noexcept
    {
        start_test("test_set_position_u16string");

        u16string_io_resource resource;

        if (!test_set_position_generic<char16_t>(resource)) {
            std::cout << "test_set_position_u16string failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_set_position_u32string ()
    noexcept
    {
        start_test("test_set_position_u32string");

        u32string_io_resource resource;

        if (!test_set_position_generic<char32_t>(resource)) {
            std::cout << "test_set_position_u32string failed."
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
    return cmp::string_io_resource_test_module{}.run_tests();
} // function -----------------------------------------------------------------
