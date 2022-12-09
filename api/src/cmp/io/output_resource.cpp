// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/output_resource.hpp>

namespace cmp {

// ------------------------------------------------------ cmp::output_resource

// Constructors and Destructor ------------------------------------------------

output_resource::output_resource (
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

std::size_t
output_resource::write (
    const std::byte* data,
    std::size_t byte_count
) {
    if (m_buffer.get_capacity() > 0) {
        return write_buffered(data, byte_count);
    } else {
        return write_raw(data, byte_count);
    }
} // function -----------------------------------------------------------------

void
output_resource::flush ()
{
    if (m_buffer.is_write_dirty()) {
        write_raw(m_buffer.get_data(), m_buffer.get_position());
        m_buffer.set_write_dirty(false);
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

std::size_t
output_resource::write_buffered (
    const std::byte* data,
    std::size_t byte_count
) {
    /*
        We check whether the buffer has enough space to write all
        the data we want to write. If it doesn't, we need to flush
        it and then write the data to the buffer.
    */
    if (m_buffer.get_position() + byte_count > m_buffer.get_capacity()) {
        flush();

        /*
            If the number of bytes to write is greater than
            what would fit in the buffer then we don't even
            bother writing to the buffer and just write all
            the remaining data directly to the resource.
        */
        if (byte_count > m_buffer.get_capacity()) {
            return write_raw(data, byte_count);
        }
    }

    /*
        Here we know that the buffer has enough room
        to write to, so we simply write to the buffer.
    */
    return m_buffer.write(data, byte_count);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
