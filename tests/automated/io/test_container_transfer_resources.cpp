// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/transparent_container_input_resource.hpp>
#include <cmp/io/transparent_container_output_resource.hpp>
#include <cmp/io/transparent_container_io_resource.hpp>
#include <cmp/io/opaque_container_input_resource.hpp>
#include <cmp/io/opaque_container_output_resource.hpp>
#include <cmp/io/opaque_container_io_resource.hpp>

namespace cmp {

class container_transfer_resources_test_module
    : public test_module<container_transfer_resources_test_module>
{
public:
    container_transfer_resources_test_module ()
    noexcept
        : test_module({
              &container_transfer_resources_test_module
                  :: test_read_blob,

              &container_transfer_resources_test_module
                  :: test_read_string,

              &container_transfer_resources_test_module
                  :: test_read_u8string,

              &container_transfer_resources_test_module
                  :: test_read_u16string,

              &container_transfer_resources_test_module
                  :: test_read_u32string,

              &container_transfer_resources_test_module
                  :: test_read_wstring,

              &container_transfer_resources_test_module
                  :: test_write_blob,

              &container_transfer_resources_test_module
                  :: test_write_string,

              &container_transfer_resources_test_module
                  :: test_write_u8string,

              &container_transfer_resources_test_module
                  :: test_write_u16string,

              &container_transfer_resources_test_module
                  :: test_write_u32string,

              &container_transfer_resources_test_module
                  :: test_write_wstring,

              &container_transfer_resources_test_module
                  :: test_set_position_blob,

              &container_transfer_resources_test_module
                  :: test_set_position_string,

              &container_transfer_resources_test_module
                  :: test_set_position_u8string,

              &container_transfer_resources_test_module
                  :: test_set_position_u16string,

              &container_transfer_resources_test_module
                  :: test_set_position_u32string,

              &container_transfer_resources_test_module
                  :: test_set_position_wstring
          })
    {
    } // function -------------------------------------------------------------

    // Test Tooling -----------------------------------------------------------

    template <
        typename Resource
    >
    bool
    test_read_generic (
        Resource& resource
    )
    noexcept
    {
        using Element
            = typename Resource::element_type;

        constexpr std::size_t data_size{5 * sizeof (Element)};
        std::byte data[data_size];
        auto bytes_read{resource.read(data, data_size)};

        if (bytes_read != data_size) {
            std::cout << "The data was not fully read."
                      << std::endl;

            return false;
        }

        if (
            static_cast<char>(data[0 * sizeof (Element)]) != 'H'
                || static_cast<char>(data[1 * sizeof (Element)]) != 'e'
                || static_cast<char>(data[2 * sizeof (Element)]) != 'l'
                || static_cast<char>(data[3 * sizeof (Element)]) != 'l'
                || static_cast<char>(data[4 * sizeof (Element)]) != 'o'
        ) {
            std::cout << "The data read does not match the data expected."
                      << std::endl;

            return false;
        }

        bytes_read = resource.read(data, 3 * sizeof (Element));
        if (bytes_read != 2 * sizeof (Element)) {
            std::cout << "We asked for 3 elements when there were only "
                         "2 left and we didn't get back the correct "
                         "number of elements."
                      << std::endl;

            return false;
        }

        if (
            static_cast<char>(data[0 * sizeof (Element)]) != '!'
                || static_cast<char>(data[1 * sizeof (Element)]) != '\n'
        ) {
            std::cout << "The data read does not match the data expected."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    template <
        typename Container
    >
    bool
    test_read ()
    {
        using Element
            = typename Container::value_type;

        Container content;
        if constexpr (std::is_same_v<Container, std::string>) {
            content = "Hello!\n";
        } else if constexpr (std::is_same_v<Container, std::u8string>) {
            content = u8"Hello!\n";
        } else if constexpr (std::is_same_v<Container, std::u16string>) {
            content = u"Hello!\n";
        } else if constexpr (std::is_same_v<Container, std::u32string>) {
            content = U"Hello!\n";
        } else if constexpr (std::is_same_v<Container, std::wstring>) {
            content = L"Hello!\n";
        } else {
            content = {
                static_cast<Element>('H'),
                static_cast<Element>('e'),
                static_cast<Element>('l'),
                static_cast<Element>('l'),
                static_cast<Element>('o'),
                static_cast<Element>('!'),
                static_cast<Element>('\n')
            };
        }

        opaque_container_input_resource<Container> opaque_input{content};
        if (!test_read_generic(opaque_input)) {
            std::cout << "test_read failed to read "
                         "from opaque_input."
                      << std::endl;

            return false;
        }

        opaque_container_io_resource<Container> opaque_io{content};
        if (!test_read_generic(opaque_io)) {
            std::cout << "test_read failed to read "
                         "from opaque_io."
                      << std::endl;

            return false;
        }

        transparent_container_input_resource<Container> transparent_input{
            content
        };
        if (!test_read_generic(transparent_input)) {
            std::cout << "test_read failed to read "
                         "from transparent_input."
                      << std::endl;

            return false;
        }

        transparent_container_io_resource<Container> transparent_io{content};
        if (!test_read_generic(transparent_io)) {
            std::cout << "test_read failed to read "
                         "from transparent_io."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    template <
        typename Resource
    >
    bool
    test_write_generic (
        Resource& resource
    )
    noexcept
    {
        using Container
            = typename Resource::content_type;

        using Element
            = typename Resource::element_type;

        Element data[] = {
            static_cast<Element>('H'),
            static_cast<Element>('e'),
            static_cast<Element>('l'),
            static_cast<Element>('l'),
            static_cast<Element>('o')
        };
        auto bytes_written{
            resource.write(
                reinterpret_cast<std::byte*>(data),
                5 * sizeof (Element)
            )
        };

        if (bytes_written != 5 * sizeof (Element)) {
            std::cout << "The data was not fully written."
                      << std::endl;

            return false;
        }

        resource.flush();
        Container expected_content;
        if constexpr (std::is_same_v<Element, std::byte>) {
            expected_content = {
                static_cast<std::byte>('H'),
                static_cast<std::byte>('e'),
                static_cast<std::byte>('l'),
                static_cast<std::byte>('l'),
                static_cast<std::byte>('o')
            };
        } else if constexpr (std::is_same_v<Element, char>) {
            expected_content = "Hello";
        } else if constexpr (std::is_same_v<Element, char8_t>) {
            expected_content = u8"Hello";
        } else if constexpr (std::is_same_v<Element, char16_t>) {
            expected_content = u"Hello";
        } else if constexpr (std::is_same_v<Element, char32_t>) {
            expected_content = U"Hello";
        } else if constexpr (std::is_same_v<Element, wchar_t>) {
            expected_content = L"Hello";
        } else {
            std::cout << "test_write_generic was called with an "
                         "invalid element type. Please use one of "
                         "std::byte, char, char8_t, char16_t, char32_t or "
                         "wchar_t."
                      << std::endl;

            return false;
        }
        if (resource.grab_content() != expected_content) {
            std::cout << "The final content does not "
                         "match the expected content."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    template <
        typename Container
    >
    bool
    test_write ()
    {
        opaque_container_output_resource<Container> opaque_output;
        if (!test_write_generic(opaque_output)) {
            std::cout << "test_write failed to write "
                         "to opaque_output."
                      << std::endl;

            return false;
        }

        opaque_container_io_resource<Container> opaque_io;
        if (!test_write_generic(opaque_io)) {
            std::cout << "test_write failed to write "
                         "to opaque_io."
                      << std::endl;

            return false;
        }

        Container content_for_output;
        transparent_container_output_resource<Container> transparent_output{
            content_for_output
        };
        if (!test_write_generic(transparent_output)) {
            std::cout << "test_write failed to write "
                         "to transparent_output."
                      << std::endl;

            return false;
        }

        Container content_for_io;
        transparent_container_io_resource<Container> transparent_io{
            content_for_io
        };
        if (!test_write_generic(transparent_io)) {
            std::cout << "test_write failed to write "
                         "to transparent_io."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    template <
        typename Resource
    >
    bool
    test_set_position_generic (
        Resource& resource
    )
    noexcept
    {
        using Container
            = typename Resource::content_type;

        using Element
            = typename Resource::element_type;

        Element data[] = {
            static_cast<Element>('H'),
            static_cast<Element>('e'),
            static_cast<Element>('l'),
            static_cast<Element>('l'),
            static_cast<Element>('o')
        };
        constexpr std::size_t data_size{5 * sizeof (Element)};
        auto bytes_written{
            resource.write(reinterpret_cast<std::byte*>(data), data_size)
        };

        if (bytes_written != data_size) {
            std::cout << "The data was not fully written."
                      << std::endl;

            return false;
        }

        resource.flush();
        Container expected_data;
        if constexpr (std::is_same_v<Element, std::byte>) {
            expected_data = {
                static_cast<std::byte>('H'),
                static_cast<std::byte>('e'),
                static_cast<std::byte>('l'),
                static_cast<std::byte>('l'),
                static_cast<std::byte>('o')
            };
        } else if constexpr (std::is_same_v<Element, char>) {
            expected_data = "Hello";
        } else if constexpr (std::is_same_v<Element, char8_t>) {
            expected_data = u8"Hello";
        } else if constexpr (std::is_same_v<Element, char16_t>) {
            expected_data = u"Hello";
        } else if constexpr (std::is_same_v<Element, char32_t>) {
            expected_data = U"Hello";
        } else if constexpr (std::is_same_v<Element, wchar_t>) {
            expected_data = L"Hello";
        } else {
            std::cout << "test_set_position_generic was called with an "
                         "invalid element type. Please use one of "
                         "std::byte, char, char8_t, char16_t, char32_t or "
                         "wchar_t."
                      << std::endl;

            return false;
        }
        if (resource.grab_content() != expected_data) {
            std::cout << "The data written does not match the data expected."
                      << std::endl;

            return false;
        }

        resource.set_position(0, position_reference::begin);
        Element y{'Y'};
        resource.write(reinterpret_cast<std::byte*>(&y), sizeof (Element));

        resource.set_position(0, position_reference::end);
        Element w{'w'};
        resource.write(reinterpret_cast<std::byte*>(&w), sizeof (Element));

        resource.flush();
        if constexpr (std::is_same_v<Element, std::byte>) {
            expected_data = {
                static_cast<std::byte>('Y'),
                static_cast<std::byte>('e'),
                static_cast<std::byte>('l'),
                static_cast<std::byte>('l'),
                static_cast<std::byte>('o'),
                static_cast<std::byte>('w')
            };
        } else if constexpr (std::is_same_v<Element, char>) {
            expected_data = "Yellow";
        } else if constexpr (std::is_same_v<Element, char8_t>) {
            expected_data = u8"Yellow";
        } else if constexpr (std::is_same_v<Element, char16_t>) {
            expected_data = u"Yellow";
        } else if constexpr (std::is_same_v<Element, char32_t>) {
            expected_data = U"Yellow";
        } else if constexpr (std::is_same_v<Element, wchar_t>) {
            expected_data = L"Yellow";
        } else {
            std::cout << "test_set_position_generic was called with an "
                         "invalid code unit type. Please use one of "
                         "char, char8_t, char16_t, char32_t or wchar_t."
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

    template <
        typename Container
    >
    bool
    test_set_position ()
    {
        opaque_container_io_resource<Container> opaque_io;
        if (!test_set_position_generic(opaque_io)) {
            std::cout << "test_set_position failed "
                         "with opaque_io."
                      << std::endl;

            return false;
        }

        Container content_for_io;
        transparent_container_io_resource<Container> transparent_io{
            content_for_io
        };
        if (!test_set_position_generic(transparent_io)) {
            std::cout << "test_set_position failed "
                         "with transparent_io."
                      << std::endl;

            return false;
        }

        return true;
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_read_blob ()
    noexcept
    {
        start_test("test_read_blob");

        if (!test_read<std::vector<std::byte>>()) {
            std::cout << "test_read_blob failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_string ()
    noexcept
    {
        start_test("test_read_string");

        if (!test_read<std::string>()) {
            std::cout << "test_read_string failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_u8string ()
    noexcept
    {
        start_test("test_read_u8string");

        if (!test_read<std::u8string>()) {
            std::cout << "test_read_u8string failed."
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

        if (!test_read<std::u16string>()) {
            std::cout << "test_read_u16string failed."
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

        if (!test_read<std::u32string>()) {
            std::cout << "test_read_u32string failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read_wstring ()
    noexcept
    {
        start_test("test_read_wstring");

        if (!test_read<std::wstring>()) {
            std::cout << "test_read_wstring failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_blob ()
    noexcept
    {
        start_test("test_write_blob");

        if (!test_write<std::vector<std::byte>>()) {
            std::cout << "test_write_blob failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_string ()
    noexcept
    {
        start_test("test_write_string");

        if (!test_write<std::string>()) {
            std::cout << "test_write_string failed."
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

        if (!test_write<std::u8string>()) {
            std::cout << "test_write_u8string failed."
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

        if (!test_write<std::u16string>()) {
            std::cout << "test_write_u16string failed."
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

        if (!test_write<std::u32string>()) {
            std::cout << "test_write_u32string failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write_wstring ()
    noexcept
    {
        start_test("test_write_wstring");

        if (!test_write<std::wstring>()) {
            std::cout << "test_write_wstring failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_set_position_blob ()
    noexcept
    {
        start_test("test_set_position_blob");

        if (!test_set_position<std::vector<std::byte>>()) {
            std::cout << "test_set_position_blob failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_set_position_string ()
    noexcept
    {
        start_test("test_set_position_string");

        if (!test_set_position<std::string>()) {
            std::cout << "test_set_position_string failed."
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

        if (!test_set_position<std::u8string>()) {
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

        if (!test_set_position<std::u16string>()) {
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

        if (!test_set_position<std::u32string>()) {
            std::cout << "test_set_position_u32string failed."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_set_position_wstring ()
    noexcept
    {
        start_test("test_set_position_wstring");

        if (!test_set_position<std::wstring>()) {
            std::cout << "test_set_position_wstring failed."
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
    return cmp::container_transfer_resources_test_module{}.run_tests();
} // function -----------------------------------------------------------------
