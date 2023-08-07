// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/general.hpp>

namespace cmp {

class io_general_test_module
    : public test_module<io_general_test_module>
{
public:
    io_general_test_module ()
    noexcept
        : test_module({
              &io_general_test_module
                  :: test_invert_endianness
          })
    {
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_invert_endianness ()
    noexcept
    {
        start_test("test_invert_endianness");

        std::uint16_t value1{0x0102};
        invert_endianness(
            reinterpret_cast<std::byte*>(&value1),
            sizeof (value1)
        );
        if (value1 != 0x0201) {
            std::cout << "invert_endianness did not correctly "
                         "invert the endianness of the data."
                      << std::endl;

            return false;
        }

        end_stage();

        std::uint32_t value2{0x01020304};
        invert_endianness(
            reinterpret_cast<std::byte*>(&value2),
            sizeof (value2)
        );
        if (value2 != 0x04030201) {
            std::cout << "invert_endianness did not correctly "
                         "invert the endianness of the data."
                      << std::endl;

            return false;
        }

        end_stage();

        std::uint64_t value3{0x0102030405060708};
        invert_endianness(
            reinterpret_cast<std::byte*>(&value3),
            sizeof (value3)
        );
        if (value3 != 0x0807060504030201) {
            std::cout << "invert_endianness did not correctly "
                         "invert the endianness of the data."
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
    return cmp::io_general_test_module{}.run_tests();
} // function -----------------------------------------------------------------
