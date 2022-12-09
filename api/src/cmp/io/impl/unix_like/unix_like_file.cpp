// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/unix_like//unix_like_file.hpp>

namespace cmp {

// ----------------------------------------------------------------- cmp::file

// Constructors and Destructor ------------------------------------------------

file::file ()
noexcept
    : transfer_resource{io_buffer::default_buffer_capacity}
    , basic_file{}
    , m_file_descriptor{-1}
{
} // function -----------------------------------------------------------------

file::file (
    const std::filesystem::path &file_path,
    access_mode mode,
    if_not_there if_file_not_there,
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , basic_file{file_path, mode, buffer_capacity}
    , m_file_descriptor{-1}
{
    open(m_file_path, m_access_mode, if_file_not_there);
} // function -----------------------------------------------------------------

file::~file ()
noexcept
{
    close();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
file::is_open ()
const noexcept
{
    return m_file_descriptor != -1;
} // function -----------------------------------------------------------------

std::int64_t
file::get_position ()
const noexcept
{
    return ::lseek(m_file_descriptor, 0, SEEK_CUR) + m_buffer.get_position();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

bool
file::open (
    const std::filesystem::path& file_path,
    access_mode mode,
    if_not_there if_file_not_there
)
noexcept
{
    if (is_open()) {
        close();
    }
    std::error_code ec;
    if (
        if_file_not_there == if_not_there::fail
            && !std::filesystem::exists(file_path, ec)
    ) {
        return false;
    }
    int flags;
    switch (mode) {
        case read_only:
            flags = O_RDONLY;
            break;
        case write_only:
            flags = O_WRONLY;
            break;
        case read_and_write:
            flags = O_RDWR;
            break;
    }
    if (if_file_not_there == if_not_there::create) {
        flags |= O_CREAT;
    }
    m_file_descriptor = ::open(file_path.string().c_str(), flags, 0777);
    m_access_mode = mode;
    return is_open();
} // function -----------------------------------------------------------------

void
file::close ()
noexcept
{
    flush();
    ::close(m_file_descriptor);
    m_file_descriptor = -1;
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

void
file::set_position_raw (
    std::int64_t new_position,
    position_reference pr
)
noexcept
{
    int unix_like_position_reference;
    switch (pr) {
        case position_reference::begin:
            unix_like_position_reference = SEEK_SET;
            if (new_position < 0) {
                new_position = 0;
            }
            break;
        case position_reference::current:
            unix_like_position_reference = SEEK_CUR;
            break;
        case position_reference::end:
            unix_like_position_reference = SEEK_END;
            break;
    }

    ::lseek(m_file_descriptor, new_position, unix_like_position_reference);

    m_last_fill_amount = 0;
} // function -----------------------------------------------------------------

std::size_t
file::read_raw (
    std::byte* data,
    std::size_t byte_count,
    read_request rr
)
noexcept
{
    if (rr == read_request::fill_buffer && m_last_fill_amount > 0) {
        go_forward(m_last_fill_amount);
    }

    std::size_t total_result;
    ssize_t native_bytes_read{0};
    const ssize_t ssize_t_max{std::numeric_limits<ssize_t>::max()};
    if constexpr (std::numeric_limits<std::size_t>::max() <= ssize_t_max) {
        total_result = read_block(data, byte_count);
    } else {
        std::size_t bytes_read{0};
        size_t native_byte_count;
        while (byte_count > 0) {
            if (byte_count <= ssize_t_max) {
                native_byte_count = byte_count;
                byte_count = 0;
            } else {
                native_byte_count = ssize_t_max;
                byte_count -= ssize_t_max;
            }
            native_bytes_read = read_block(data, native_byte_count);
            bytes_read += native_bytes_read;
            if (native_bytes_read != native_byte_count) {
                break;
            }
        }
        total_result = bytes_read;
    }

    /*
        If the read request is meant to fill the buffer
        then we go back by the number of bytes read.
    */
    if (rr == read_request::fill_buffer) {
        go_back(static_cast<position_type>(total_result));
        m_last_fill_amount = total_result;
    }

    return total_result;
} // function -----------------------------------------------------------------

std::size_t
file::write_raw (
    const std::byte* data,
    std::size_t byte_count
)
noexcept
{
    std::size_t total_result;
    ssize_t native_bytes_written{0};
    const ssize_t ssize_t_max{std::numeric_limits<ssize_t>::max()};
    if constexpr (std::numeric_limits<std::size_t>::max() <= ssize_t_max) {
        total_result = write_block(data, byte_count);
    } else {
        std::size_t bytes_written{0};
        ssize_t native_byte_count;
        while (byte_count > 0) {
            if (byte_count <= ssize_t_max) {
                native_byte_count = byte_count;
                byte_count = 0;
            } else {
                native_byte_count = ssize_t_max;
                byte_count -= ssize_t_max;
            }
            native_bytes_written = write_block(data, native_byte_count);
            bytes_written += native_bytes_written;
            if (native_bytes_written != native_byte_count) {
                break;
            }
        }
        total_result = bytes_written;
    }
    return total_result;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

ssize_t
file::read_block (
    std::byte* data,
    size_t byte_count
)
noexcept
{
    ssize_t bytes_read_last;
    ssize_t bytes_read_total{0};
    while (true) {
        bytes_read_last = ::read(m_file_descriptor, data, byte_count);
        if (bytes_read_last == -1 || bytes_read_last == 0) {
            break;
        }
        bytes_read_total += bytes_read_last;
        if (bytes_read_total == byte_count) {
            break;
        }
    }

    return bytes_read_total;
} // function -----------------------------------------------------------------

ssize_t
file::write_block (
    const std::byte* data,
    size_t byte_count
)
noexcept
{
    ssize_t native_bytes_written{::write(m_file_descriptor, data, byte_count)};
    if (native_bytes_written == -1) {
        return 0;
    }
    return native_bytes_written;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
