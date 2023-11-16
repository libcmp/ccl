// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/ctr_essence.hpp>

namespace cmp {

namespace impl {

// ---------------------------------------------------- cmp::impl::ctr_essence

// Constructors and Destructor ------------------------------------------------

template <
    typename Container
>
ctr_essence<Container>::ctr_essence (
    const Container* initial_content_ptr
)
    : m_content_ptr{
          reinterpret_cast<void*>(
              const_cast<Container*>(
                  initial_content_ptr
              )
          )
      }
    , m_position{0}
    , m_last_fill_amount{0}
{
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

template <
    typename Container
>
Container*
ctr_essence<Container>::get_content_ptr ()
noexcept
{
    return reinterpret_cast<Container*>(m_content_ptr);
} // function -----------------------------------------------------------------

template <
    typename Container
>
const Container*
ctr_essence<Container>::get_const_content_ptr ()
const noexcept
{
    return reinterpret_cast<const Container*>(m_content_ptr);
} // function -----------------------------------------------------------------

template <
    typename Container
>
bool
ctr_essence<Container>::is_at_end (
    const io_buffer& buffer
)
const noexcept
{
    using element_type = typename Container::value_type;

    return get_position(buffer) ==
        std::size(*get_const_content_ptr()) * sizeof (element_type);
} // function -----------------------------------------------------------------

template <
    typename Container
>
std::int64_t
ctr_essence<Container>::get_position (
    const io_buffer& buffer
)
const noexcept
{
    return m_position + buffer.get_position();
} // function -----------------------------------------------------------------

template <
    typename Container
>
void
ctr_essence<Container>::set_position_raw (
    std::int64_t new_position,
    position_reference pr
)
noexcept
{
    using element_type = typename Container::value_type;

    switch (pr) {
        case position_reference::begin:
            m_position = new_position * sizeof (element_type);
            break;
        case position_reference::current:
            m_position += new_position * sizeof (element_type);
            break;
        case position_reference::end:
            m_position = (std::size(*get_const_content_ptr()) - new_position)
                * sizeof (element_type);
            break;
    }
    m_last_fill_amount = 0;
} // function -----------------------------------------------------------------

template <
    typename Container
>
std::size_t
ctr_essence<Container>::read_raw (
    std::byte *data,
    std::size_t byte_count,
    cmp::read_request rr,
    seekable_input_resource<std::int64_t>& resource
) {
    using element_type = typename Container::value_type;

    const auto& content_ref{*get_const_content_ptr()};

    if (rr == read_request::fill_buffer && m_last_fill_amount > 0) {
        resource.go_forward(m_last_fill_amount);
    }

    /*
        We compute the number of bytes stored in the content.
    */
    const std::size_t content_size{
        std::size(content_ref) * sizeof (element_type)
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
        reinterpret_cast<const std::byte*>(std::data(content_ref))
            + m_position,
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
        resource.go_back(static_cast<std::int64_t>(byte_count));
        m_last_fill_amount = byte_count;
    }

    return byte_count;
} // function -----------------------------------------------------------------

template <
    typename Container
>
std::size_t
ctr_essence<Container>::write_raw (
    const std::byte* data,
    std::size_t byte_count
) {
    using element_type = typename Container::value_type;

    auto& content_ref{*get_content_ptr()};

    /*
        We compute the number of bytes stored in the content.
    */
    const std::size_t content_size{
        std::size(content_ref) * sizeof (element_type)
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
        content_ref.resize(
            std::size(content_ref)
                + (byte_count / sizeof (element_type))
        );
    }

    /*
        Here we copy the bytes from the data array to the content.
    */
    std::memcpy(
        reinterpret_cast<std::byte*>(std::data(content_ref))
            + m_position,
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

} // namespace ----------------------------------------------------------------
