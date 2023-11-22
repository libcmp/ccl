// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/opaque_container_output_resource.hpp>

namespace cmp {

// -------------------------- cmp::opaque_container_output_resource<Container>

// Constructors and Destructor ------------------------------------------------

template <
    typename Container
>
opaque_container_output_resource<Container>::opaque_container_output_resource (
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , seekable_output_resource<std::int64_t>{buffer_capacity}
    , impl::ctr_essence<Container>{
          &m_content
      }
    , m_content{}
{
} // function -----------------------------------------------------------------

template <
    typename Container
>
opaque_container_output_resource<Container>::opaque_container_output_resource (
    const content_type& initial_content,
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , seekable_output_resource<std::int64_t>{buffer_capacity}
    , impl::ctr_essence<Container>{
          &m_content
      }
    , m_content{initial_content}
{
} // function -----------------------------------------------------------------

template <
    typename Container
>
opaque_container_output_resource<Container>::opaque_container_output_resource (
    content_type&& initial_content,
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , seekable_output_resource<std::int64_t>{buffer_capacity}
    , impl::ctr_essence<Container>{
          &m_content
      }
    , m_content{std::move(initial_content)}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename Container
>
bool
opaque_container_output_resource<Container>::is_at_end ()
const noexcept
{
    return essence_type::is_at_end(m_buffer);
} // function -----------------------------------------------------------------

template <
    typename Container
>
std::int64_t
opaque_container_output_resource<Container>::get_position ()
const noexcept
{
    return essence_type::get_position(m_buffer);
} // function -----------------------------------------------------------------

template <
    typename Container
>
typename opaque_container_output_resource<Container>::content_type&
opaque_container_output_resource<Container>::grab_content ()
noexcept
{
    return m_content;
} // function -----------------------------------------------------------------

template <
    typename Container
>
const typename opaque_container_output_resource<Container>::content_type&
opaque_container_output_resource<Container>::grab_content ()
const noexcept
{
    return m_content;
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

template <
    typename Container
>
void
opaque_container_output_resource<Container>::set_position_raw (
    std::int64_t new_position,
    position_reference pr
)
noexcept
{
    essence_type::set_position_raw(
        new_position,
        pr
    );
} // function -----------------------------------------------------------------

template <
    typename Container
>
std::size_t
opaque_container_output_resource<Container>::write_raw (
    const std::byte* data,
    std::size_t byte_count
) {
    return essence_type::write_raw(
        data,
        byte_count
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
