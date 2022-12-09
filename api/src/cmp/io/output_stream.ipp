// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/output_stream.hpp>

namespace cmp {

// -------------------------------------------------------- cmp::output_stream

// Constructors and Destructor ------------------------------------------------

template <
    typename OutputResource
>
output_stream<OutputResource>::output_stream (
    wrapped_resource_type& resource,
    std::endian endianness,
    flush_strategy fs
)
noexcept
    : m_resource{resource}
    , m_endianness{endianness}
    , m_flush_strategy{fs}
{
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
output_stream<OutputResource>::~output_stream ()
{
    flush();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename OutputResource
>
typename output_stream<OutputResource>::wrapped_resource_type&
output_stream<OutputResource>::grab_resource ()
noexcept
{
    return m_resource;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
const typename output_stream<OutputResource>::wrapped_resource_type&
output_stream<OutputResource>::grab_resource ()
const noexcept
{
    return m_resource;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
std::endian
output_stream<OutputResource>::get_endianness ()
const noexcept
{
    return m_endianness;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
output_stream<OutputResource>::set_endianness (
    std::endian new_endianness
)
noexcept
{
    m_endianness = new_endianness;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
flush_strategy
output_stream<OutputResource>::get_flush_strategy ()
const noexcept
{
    return m_flush_strategy;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
output_stream<OutputResource>::set_flush_strategy (
    flush_strategy new_flush_strategy
)
noexcept
{
    m_flush_strategy = new_flush_strategy;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
bool
output_stream<OutputResource>::is_at_end ()
const noexcept
{
    return m_resource.is_at_end();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename OutputResource
>
std::size_t
output_stream<OutputResource>::write (
    const std::byte* data,
    std::size_t byte_count
) {
    std::size_t bytes_written{m_resource.write(data, byte_count)};
    if (m_flush_strategy == flush_strategy::automatic) {
        m_resource.flush();
    }
    return bytes_written;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
std::size_t
output_stream<OutputResource>::reverse_write (
    std::byte* data,
    std::size_t byte_count
) {
    invert_endianness(data, byte_count);
    std::size_t bytes_written{m_resource.write(data, byte_count)};
    if (m_flush_strategy == flush_strategy::automatic) {
        m_resource.flush();
    }
    return bytes_written;
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
void
output_stream<OutputResource>::flush ()
{
    m_resource.flush();
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

template <
    typename OutputResource
>
typename output_stream<OutputResource>::wrapped_resource_type*
output_stream<OutputResource>::operator -> ()
const noexcept
{
    return &m_resource;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
