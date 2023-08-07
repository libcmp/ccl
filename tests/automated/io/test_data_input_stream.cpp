// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/data_input_stream.hpp>
#include <cmp/io/file.hpp>
#include <fstream>

namespace cmp {

class data_input_stream_test_module
    : public test_module<data_input_stream_test_module>
{
public:
    data_input_stream_test_module ()
    noexcept
        : test_module({
              &data_input_stream_test_module
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

        int value_to_write1{75};
        double value_to_write2{128.25};

        std::ofstream ofstream{
            "../../test_data/test_read_binary.txt",
            std::ios::binary
        };

        if (!ofstream.is_open()) {
            std::cout << "The ofstream could not be opened."
                      << std::endl;

            return false;
        }

        ofstream.write((char*)(&value_to_write1), sizeof (value_to_write1));
        ofstream.write((char*)(&value_to_write2), sizeof (value_to_write2));
        ofstream.close();

        file f{
            "../../test_data/test_read_binary.txt",
            read_only,
            cmp::if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_read_binary.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        data_input_stream stream{f};

        int value_to_read1;
        double value_to_read2;

        stream >> value_to_read1 >> value_to_read2;

        if (value_to_read1 != 75) {
            std::cout << "The first value read from the file "
                         "does not match the expected value."
                      << std::endl;

            return false;
        }

        if (value_to_read2 != 128.25) {
            std::cout << "The second value read from the file "
                         "does not match the expected value."
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
    return cmp::data_input_stream_test_module{}.run_tests();
} // function -----------------------------------------------------------------
