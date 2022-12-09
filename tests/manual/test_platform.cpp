// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <iostream>

#include <cmp/core/test_module.hpp>
#include <cmp/core/platform.hpp>

namespace cmp {

class platform_test_module
    : public test_module<platform_test_module>
{
public:
    platform_test_module ()
    noexcept
        : test_module({
              &platform_test_module
                  :: test_compiler,

              &platform_test_module
                  :: test_operating_system
          })
    {
    }

    // Tests ------------------------------------------------------------------

    bool
    test_compiler ()
    noexcept
    {
        start_test("test_compiler");

        std::cout << "This target was compiled by "
                  << CMP_COMPILER_NAME
                  << '.'
                  << std::endl;

        end_stage();

        return true;
    }

    bool
    test_operating_system ()
    noexcept
    {
        start_test("test_operating_system");

        std::cout << "This machine's operating system is "
                  << CMP_OS_NAME
                  << '.'
                  << std::endl;

        end_stage();

        return true;
    }
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

int
main ()
{
    return cmp::platform_test_module{}.run_tests();
}
