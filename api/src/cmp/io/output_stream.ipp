// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/output_stream.hpp>

namespace cmp {

// ---------------------------------------- cmp::output_stream<OutputResource>

// Constructors and Destructor ------------------------------------------------

template <
    typename OutputResource
>
output_stream<OutputResource>::output_stream (
    wrapped_resource_type& resource,
    std::endian endianness
)
noexcept
    : m_resource{resource}
    , m_endianness{endianness}
{
} // function -----------------------------------------------------------------

template <
    typename OutputResource
>
output_stream<OutputResource>::~output_stream ()
{
    this->flush();
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

// Free Functions -------------------------------------------------------------

template <
    typename OutputResource
>
output_stream<OutputResource>&
operator << (
    output_stream<OutputResource>& stream,
    flush_t flush_v
) {
    stream.flush();
    return stream;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
