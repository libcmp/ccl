// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>
#include <cmp/io/file.hpp>

namespace cmp {

class file_test_module
    : public test_module<file_test_module>
{
public:
    file_test_module ()
    noexcept
        : test_module({
              &file_test_module
                  :: test_open,

              &file_test_module
                  :: test_position,

              &file_test_module
                  :: test_is_at_end,

              &file_test_module
                  :: test_read,

              &file_test_module
                  :: test_write
          })
    {
    } // function -------------------------------------------------------------

    // Tests ------------------------------------------------------------------

    bool
    test_open ()
    noexcept
    {
        start_test("test_open");

        std::filesystem::path file_path1{"../../test_data/test_open1.txt"};
        std::filesystem::path file_path2{"../../test_data/test_open2.txt"};

        if (std::filesystem::exists(file_path1)) {
            std::filesystem::remove(file_path1);
        }
        if (std::filesystem::exists(file_path2)) {
            std::filesystem::remove(file_path2);
        }

        file f1{file_path1, read_only, if_not_there::create};

        if (!f1.is_open()) {
            std::cout << "File test_open1.txt could not be opened "
                         "for reading the first time around."
                      << std::endl;

            return false;
        }

        if (!std::filesystem::exists(file_path1)) {
            std::cout << "File test_open1.txt was not "
                         "created when it was opened."
                      << std::endl;

            return false;
        }

        end_stage();

        file f2{file_path1, read_only, if_not_there::create};

        if (!f2.is_open()) {
            std::cout << "File test_open1.txt could not be opened "
                         "for reading the second time around."
                      << std::endl;

            return false;
        }

        end_stage();

        file f3{file_path2, read_only, if_not_there::fail};

        if (f3.is_open()) {
            std::cout << "File test_open2.txt was opened for "
                         "reading but should not have been."
                      << std::endl;

            return false;
        }

        if (std::filesystem::exists(file_path2)) {
            std::cout << "File test_open2.txt was created when "
                         "it was opened but should not have been."
                      << std::endl;

            return false;
        }

        end_stage();

        f1.close();
        f2.close();
        f3.close();

        if (std::filesystem::exists(file_path1)) {
            std::filesystem::remove(file_path1);
        }
        if (std::filesystem::exists(file_path2)) {
            std::filesystem::remove(file_path2);
        }

        end_stage();

        file f4{
            u8"../../test_data/Δunicode_name₤.txt",
            read_only,
            if_not_there::fail
        };

        if (!f4.is_open()) {
            std::cout << "File with Unicode name could not be opened "
                         "for reading."
                      << std::endl;

            return false;
        }

        f4.close();

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_position ()
    noexcept
    {
        start_test("test_position");

        file f{
            "../../test_data/test_reading.txt",
            read_only,
            if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_reading.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        if (f.get_position() != 0) {
            std::cout << "The file's position is not where it "
                         "should be, which is position 0."
                      << std::endl;

            return false;
        }

        end_stage();

        std::byte data[2];
        f.read(data, 2);
        if (f.get_position() != 2) {
            std::cout << "The file's position is not where it "
                         "should be, which is position 2."
                      << std::endl;

            return false;
        }

        end_stage();

        f.set_position(0, position_reference::begin);
        if (f.get_position() != 0) {
            std::cout << "The file's position is not where it "
                         "should be, which is position 0."
                      << std::endl;

            return false;
        }

        end_stage();

        f.set_position(0, position_reference::end);
        if (f.get_position() != 4) {
            std::cout << "The file's position is not where it "
                         "should be, which is position 4."
                      << std::endl;

            return false;
        }

        end_stage();

        f.set_position(-1, position_reference::end);
        if (f.get_position() != 3) {
            std::cout << "The file's position is not where it "
                         "should be, which is position 3."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_is_at_end ()
    noexcept
    {
        start_test("test_is_at_end");

        file f{
            "../../test_data/test_reading.txt",
            read_only,
            if_not_there::fail
        };

        if (!f.is_open()) {
            std::cout << "File test_reading.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        if (f.is_at_end()) {
            std::cout << "is_at_end is incorrectly reporting "
                         "that the file is at the end."
                      << std::endl;

            return false;
        }

        end_stage();

        std::byte data[2];
        f.read(data, 2);
        if (f.is_at_end()) {
            std::cout << "is_at_end is incorrectly reporting "
                         "that the file is at the end."
                      << std::endl;

            return false;
        }

        end_stage();

        f.read(data, 2);
        if (!f.is_at_end()) {
            std::cout << "is_at_end is incorrectly reporting "
                         "that the file is not at the end."
                      << std::endl;

            return false;
        }

        end_stage();

        f.set_position(0, position_reference::end);
        if (!f.is_at_end()) {
            std::cout << "is_at_end is incorrectly reporting "
                         "that the file is not at the end."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_read ()
    noexcept
    {
        start_test("test_read");

        file f{
            "../../test_data/test_reading.txt",
            read_only,
            if_not_there::fail,
            2
        };

        if (!f.is_open()) {
            std::cout << "File test_reading.txt could "
                         "not be opened for reading."
                      << std::endl;

            return false;
        }

        std::byte data[4];
        auto bytes_read{f.read(data, 4)};

        if (bytes_read != 4) {
            std::cout << "The data was not fully read."
                      << std::endl;

            return false;
        }

        if (
            static_cast<char>(data[0]) != 'a'
                || static_cast<char>(data[1]) != 'b'
                || static_cast<char>(data[2]) != 'c'
                || static_cast<char>(data[3]) != 'd'
        ) {
            std::cout << "The data read does not match the data expected."
                      << std::endl;

            return false;
        }

        end_stage();

        return true;
    } // function -------------------------------------------------------------

    bool
    test_write ()
    noexcept
    {
        start_test("test_write");

        file f{
            "../../test_data/test_writing.txt",
            write_only,
            if_not_there::fail,
            2
        };

        if (!f.is_open()) {
            std::cout << "File test_writing.txt could "
                         "not be opened for writing."
                      << std::endl;

            return false;
        }

        std::byte data[] = {
            static_cast<std::byte>('x'),
            static_cast<std::byte>('y'),
            static_cast<std::byte>('z'),
            static_cast<std::byte>('w')
        };
        auto bytes_written{f.write(data, 4)};

        if (bytes_written != 4) {
            std::cout << "The data was not fully written."
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
    return cmp::file_test_module{}.run_tests();
} // function -----------------------------------------------------------------
