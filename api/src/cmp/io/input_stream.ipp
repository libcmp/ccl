// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/input_stream.hpp>

namespace cmp {

// ------------------------------------------ cmp::input_stream<InputResource>

// Constructors and Destructor ------------------------------------------------

template <
    typename InputResource
>
input_stream<InputResource>::input_stream (
    referenced_resource_type& resource,
    std::endian endianness
)
noexcept
    : m_resource{resource}
    , m_endianness{endianness}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename InputResource
>
typename input_stream<InputResource>::referenced_resource_type&
input_stream<InputResource>::grab_resource ()
noexcept
{
    return m_resource;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
const typename input_stream<InputResource>::referenced_resource_type&
input_stream<InputResource>::grab_resource ()
const noexcept
{
    return m_resource;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
std::endian
input_stream<InputResource>::get_endianness ()
const noexcept
{
    return m_endianness;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
void
input_stream<InputResource>::set_endianness (
    std::endian new_endianness
)
noexcept
{
    m_endianness = new_endianness;
} // function -----------------------------------------------------------------

template <
    typename InputResource
>
bool
input_stream<InputResource>::is_at_end ()
const noexcept
{
    return m_resource.is_at_end();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename InputResource
>
std::size_t
input_stream<InputResource>::read (
    std::byte* data,
    std::size_t byte_count
) {
    std::size_t bytes_read{m_resource.read(data, byte_count)};
    if (m_endianness != std::endian::native) {
        invert_endianness(data, byte_count);
    }
    return bytes_read;
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

template <
    typename InputResource
>
typename input_stream<InputResource>::referenced_resource_type*
input_stream<InputResource>::operator -> ()
const noexcept
{
    return &m_resource;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
