// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/data_io_stream.hpp>
#include <cmp/io/opaque_container_io_resource.hpp>

namespace cmp {

class data_io_stream_test_module
    : public test_module<data_io_stream_test_module>
{
public:
    data_io_stream_test_module ()
    noexcept
        : test_module({
              &data_io_stream_test_module
                  :: test_read
          })
    {
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_read ()
    noexcept
    {
        start_test("test_read");

        opaque_u8string_io_resource resource{u8"Hello, world!"};
        data_io_stream stream{resource, std::endian::native};

        stream->set_position(5, position_reference::current);
        const char8_t data{';'};
        stream << data;
        stream->flush();
        if (resource.grab_content() != u8"Hello; world!") {
            std::cout << "The data was not written correctly."
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
    return cmp::data_io_stream_test_module{}.run_tests();
} // function -----------------------------------------------------------------
