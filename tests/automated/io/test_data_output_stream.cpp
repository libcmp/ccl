// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/data_output_stream.hpp>
#include <cmp/io/file.hpp>
#include <fstream>

namespace cmp {

class data_output_stream_test_module
    : public test_module<data_output_stream_test_module>
{
public:
    data_output_stream_test_module ()
    noexcept
        : test_module({
              &data_output_stream_test_module
                  :: test_write
          })
    {
    }

    // Tests ------------------------------------------------------------------

    bool
    test_write ()
    noexcept
    {
        start_test("test_write");

        int value_to_write1{75};
        double value_to_write2{128.25};

        file f{
            "../../test_data/test_write_binary.txt",
           write_only,
           cmp::if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_write_binary.txt could "
                         "not be opened for writing."
                      << std::endl;

            return false;
        }

        data_output_stream stream{f, std::endian::native};
        stream << value_to_write1 << value_to_write2;
        stream.flush();

        int value_to_read1;
        double value_to_read2;

        std::ifstream ifstream{
            "../../test_data/test_write_binary.txt",
            std::ios::binary
        };

        if (!ifstream.is_open()) {
            std::cout << "The ifstream could not be opened."
                      << std::endl;

            return false;
        }

        ifstream.read((char*)(&value_to_read1), sizeof (value_to_read1));
        ifstream.read((char*)(&value_to_read2), sizeof (value_to_read2));

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
    return cmp::data_output_stream_test_module{}.run_tests();
}
