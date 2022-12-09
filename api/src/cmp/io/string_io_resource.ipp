// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/string_io_resource.hpp>

namespace cmp {

// --------------------------------------------------- cmp::string_io_resource

// Constructors and Destructor ------------------------------------------------

template <
    writable_unicode_string T
>
string_io_resource<T>::string_io_resource (
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , seekable_io_resource{buffer_capacity}
    , m_content{}
    , m_position{0}
    , m_last_fill_amount{0}
{
} // function -----------------------------------------------------------------

template <
    writable_unicode_string T
>
string_io_resource<T>::string_io_resource (
    string_type initial_content,
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , seekable_io_resource{buffer_capacity}
    , m_content{std::move(initial_content)}
    , m_position{0}
    , m_last_fill_amount{0}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    writable_unicode_string T
>
bool
string_io_resource<T>::is_at_end ()
const noexcept
{
    return get_position() == string_size(m_content) * sizeof (code_unit_type);
} // function -----------------------------------------------------------------

template <
    writable_unicode_string T
>
T&
string_io_resource<T>::grab_content ()
noexcept
{
    return m_content;
} // function -----------------------------------------------------------------

template <
    writable_unicode_string T
>
const T&
string_io_resource<T>::grab_content ()
const noexcept
{
    return m_content;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    writable_unicode_string T
>
std::int64_t
string_io_resource<T>::get_position ()
const noexcept
{
    return m_position + m_buffer.get_position();
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

template <
    writable_unicode_string T
>
void
string_io_resource<T>::set_position_raw (
    std::int64_t new_position,
    position_reference pr
)
noexcept
{
    switch (pr) {
        case position_reference::begin:
            m_position = new_position * sizeof (code_unit_type);
            break;
        case position_reference::current:
            m_position += new_position * sizeof (code_unit_type);
            break;
        case position_reference::end:
            m_position = (string_size(m_content) - new_position)
                * sizeof (code_unit_type);
            break;
    }

    m_last_fill_amount = 0;
} // function -----------------------------------------------------------------

template <
    writable_unicode_string T
>
std::size_t
string_io_resource<T>::read_raw (
    std::byte* data,
    std::size_t byte_count,
    read_request rr
) {
    if (rr == read_request::fill_buffer && m_last_fill_amount > 0) {
        go_forward(m_last_fill_amount);
    }

    /*
        We compute the number of bytes stored in the content.
    */
    const std::size_t content_size{
        string_size(m_content) * sizeof (code_unit_type)
    };

    /*
        We check if the position would spill over the end of the content
        if we actually went ahead and read the requested number of bytes.
    */
    if (m_position + byte_count > content_size) {
        /*
            Here we know that the caller is requesting more bytes than
            there are bytes available. So we adjust the number of bytes
            to read such that we only read until the end of the content.
        */
        byte_count = content_size - m_position;
    }

    /*
        We copy the bytes from the content to the data array.
    */
    std::memcpy(
        data,
        reinterpret_cast<std::byte*>(std::data(m_content)) + m_position,
        byte_count
    );

    /*
        We advance the position by the number of bytes read.
    */
    m_position += byte_count;

    /*
        If the read request is meant to fill the buffer
        then we go back by the number of bytes read.
    */
    if (rr == read_request::fill_buffer) {
        go_back(static_cast<position_type>(byte_count));
        m_last_fill_amount = byte_count;
    }

    return byte_count;
} // function -----------------------------------------------------------------

template <
    writable_unicode_string T
>
std::size_t
string_io_resource<T>::write_raw (
    const std::byte* data,
    std::size_t byte_count
) {
    /*
        We compute the number of bytes stored in the content.
    */
    const std::size_t content_size{
        string_size(m_content) * sizeof (code_unit_type)
    };

    /*
        We check if the position would spill over the end of the content
        if we actually went ahead and wrote the requested number of bytes.
    */
    if (m_position + byte_count > content_size) {
        /*
            Here we know that the caller is trying to write more bytes
            than there are bytes available. So we just make room.
        */
        m_content.resize(
            string_size(m_content) + (byte_count / sizeof (code_unit_type))
        );
    }

    /*
        Here we copy the bytes from the data array to the content.
    */
    std::memcpy(
        reinterpret_cast<std::byte*>(std::data(m_content)) + m_position,
        data,
        byte_count
    );

    /*
        We advance the position by the number of bytes written.
    */
    m_position += byte_count;

    return byte_count;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
