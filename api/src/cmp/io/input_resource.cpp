// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/input_resource.hpp>

namespace cmp {

// ------------------------------------------------------- cmp::input_resource

// Constructors and Destructor ------------------------------------------------

input_resource::input_resource (
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , m_tied_resource{nullptr}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

std::size_t
input_resource::read (
    std::byte* data,
    std::size_t byte_count
) {
    if (m_tied_resource) {
        m_tied_resource->flush();
    }
    if (m_buffer.get_capacity() > 0) {
        return read_buffered(data, byte_count);
    } else {
        return read_raw(data, byte_count, read_request::lean_retrieval);
    }
} // function -----------------------------------------------------------------

void
input_resource::tie (
    output_resource& resource
)
noexcept
{
    m_tied_resource = &resource;
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

std::size_t
input_resource::fill ()
{
    std::size_t bytes_read{
        read_raw(
            m_buffer.get_data_ptr(),
            m_buffer.get_capacity(),
            read_request::fill_buffer
        )
    };
    m_buffer.set_read_dirty(false);
    m_buffer.set_size(bytes_read);
    return bytes_read;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

std::size_t
input_resource::read_buffered (
    std::byte* data,
    std::size_t byte_count
) {
    if (m_buffer.is_read_dirty()) {
        fill();
    }

    /*
        We check whether the buffer has all the data we want
        to read. If it doesn't, we need to read whatever the
        buffer has and then go to the resource for the rest.
    */
    if (m_buffer.get_position() + byte_count > m_buffer.get_size()) {
        /*
            Here we know that the buffer doesn't
            have all the data we want, but may
            potentially have some of it.
        */

        std::size_t bytes_read{0};

        /*
            This 'difference' variable tells how many bytes
            we need to read from the buffer before going to
            the resource.
        */
        std::size_t difference{
            m_buffer.get_size() - m_buffer.get_position()
        };

        /*
            Here we check if there's any bytes in the buffer
            that we can read before going to the resource.
        */
        if (difference > 0) {
            /*
                Here we read all the data we can from the buffer.
            */
            bytes_read += m_buffer.read(data, difference);

            /*
                We keep track of the number of bytes that we want
                to read next by subtracting the number of bytes
                we got from the buffer from the number of bytes
                we want to read in total.
            */
            byte_count -= bytes_read;
        }

        /*
            If the number of bytes left to read is greater
            than what would fit in the buffer then we don't
            even bother filling up the buffer and just read
            all the remaining data directly.
        */
        if (byte_count > m_buffer.get_capacity()) {
            bytes_read += read_raw(
                data + bytes_read,
                byte_count,
                read_request::lean_retrieval
            );
            return bytes_read;
        } else {
            /*
                We now try to fill up the buffer
                by reading data from the resource.
            */
            std::size_t bytes_filled{fill()};

            std::size_t last_byte_count;
            if (bytes_filled < byte_count) {
                /*
                    We weren't able to load as many bytes into the buffer
                    as we wanted to, so we remember to just read all the
                    bytes we can from the buffer.
                */
                last_byte_count = bytes_filled;
            } else {
                /*
                    We were able to load at least as many bytes into
                    the buffer as we wanted to, so we remember to just
                    read the bytes we want from the buffer.
                */
                last_byte_count = byte_count;
            }
            /*
                We now go ahead and read the final bytes.
            */
            bytes_read += m_buffer.read(data + bytes_read, last_byte_count);

            return bytes_read;
        }
    } else {
        /*
            The buffer had all the data we wanted to
            begin with, so we just read from the buffer.
        */
        return m_buffer.read(data, byte_count);
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
