// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/data_io_stream.hpp>

namespace cmp {

// ------------------------------------------- cmp::data_io_stream<IOResource>

// Constructors and Destructor ------------------------------------------------

template <
    typename IOResource
>
data_io_stream<IOResource>::data_io_stream (
    wrapped_resource_type& resource,
    std::endian endianness
)
noexcept
    : data_input_stream<IOResource>{resource, endianness}
    , data_output_stream<IOResource>{resource, endianness}
    , m_resource{resource}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

template <
    typename IOResource
>
typename data_io_stream<IOResource>::wrapped_resource_type*
data_io_stream<IOResource>::operator -> ()
const noexcept
{
    return &m_resource;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
