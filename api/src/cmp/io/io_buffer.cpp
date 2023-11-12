// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/io_buffer.hpp>

namespace cmp {

// ------------------------------------------------------------ cmp::io_buffer

// Constructors and Destructor ------------------------------------------------

io_buffer::io_buffer (
    std::size_t buffer_capacity
)
    : m_size{0}
    , m_position{0}
    , m_read_dirty_flag{true}
    , m_write_dirty_flag{false}
{
    m_data.shrink_to_fit();
    m_data.resize(buffer_capacity);
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

std::size_t
io_buffer::get_capacity ()
const noexcept
{
    return m_data.capacity();
} // function -----------------------------------------------------------------

std::size_t
io_buffer::get_size ()
const noexcept
{
    return m_size;
} // function -----------------------------------------------------------------

void
io_buffer::set_size (
    std::size_t new_size
)
noexcept
{
    m_size = new_size;
} // function -----------------------------------------------------------------

std::size_t
io_buffer::get_position ()
const noexcept
{
    return m_position;
} // function -----------------------------------------------------------------

void
io_buffer::set_position (
    std::size_t new_position
)
noexcept
{
    m_position = new_position;
} // function -----------------------------------------------------------------

std::byte*
io_buffer::get_data ()
noexcept
{
    return m_data.data();
} // function -----------------------------------------------------------------

bool
io_buffer::is_read_dirty ()
const noexcept
{
    return m_read_dirty_flag;
} // function -----------------------------------------------------------------

void
io_buffer::set_read_dirty (
    bool new_read_dirty_flag
)
noexcept
{
    m_position = 0;
    m_read_dirty_flag = new_read_dirty_flag;
} // function -----------------------------------------------------------------

bool
io_buffer::is_write_dirty ()
const noexcept
{
    return m_write_dirty_flag;
} // function -----------------------------------------------------------------

void
io_buffer::set_write_dirty (
    bool new_write_dirty_flag
)
noexcept
{
    m_write_dirty_flag = new_write_dirty_flag;
    if (!m_write_dirty_flag) {
        m_position = 0;
    }
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

std::size_t
io_buffer::read (
    std::byte* data,
    std::size_t byte_count
) {
    std::size_t boundary{m_position + byte_count};
    if (boundary > m_size) {
        std::size_t excess{boundary - m_size};
        byte_count -= excess;
    }
    std::memcpy(data, m_data.data() + m_position, byte_count);
    m_position += byte_count;
    return byte_count;
} // function -----------------------------------------------------------------

std::size_t
io_buffer::write (
    const std::byte* data,
    std::size_t byte_count
) {
    std::memcpy(m_data.data() + m_position, data, byte_count);
    m_position += byte_count;
    set_write_dirty(true);
    return byte_count;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
