// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/text_io_stream.hpp>
#include <cmp/io/string_io_resource.hpp>
#include <cmp/io/file.hpp>

namespace cmp {

class text_io_stream_test_module
    : public test_module<text_io_stream_test_module>
{
public:
    text_io_stream_test_module ()
    noexcept
        : test_module({
              &text_io_stream_test_module
                  :: test_stream
          })
    {
    }

    // Tests ------------------------------------------------------------------

    bool
    test_stream ()
    noexcept
    {
        start_test("test_stream");

        u8string_io_resource string_resource{u8"Hello, world!"};
        text_io_stream stream1{string_resource, utf8, std::endian::native};
        stream1->set_position(7, position_reference::begin);
        stream1 << u8"there!";
        stream1->set_position(0, position_reference::begin);
        std::u8string result1;
        stream1.read_all(result1);

        if (result1 != u8"Hello, there!") {
            std::cout << "The first result is not what it was supposed to be: "
                      << to_string(result1)
                      << std::endl;

            return false;
        }

        end_stage();

        file file_resource{
            "../../test_data/test_stream.txt",
            read_and_write,
            cmp::if_not_there::fail
        };

        if (!file_resource.is_open()) {
            std::cout << "File test_stream.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        text_io_stream stream2{file_resource, utf8, std::endian::native};
        stream2->set_position(7, position_reference::begin);
        stream2 << u8"there!";
        stream2->set_position(0, position_reference::begin);
        std::u8string result2;
        stream2.read_all(result2);

        if (result2 != u8"Hello, there!") {
            std::cout << "The second result is not "
                         "what it was supposed to be: "
                      << to_string(result2)
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
    return cmp::text_io_stream_test_module{}.run_tests();
}
