// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/text_io_stream.hpp>

namespace cmp {

// ------------------------------------------------------- cmp::text_io_stream

// Constructors and Destructor ------------------------------------------------

template <
    typename IOResource
>
text_io_stream<IOResource>::text_io_stream (
    wrapped_resource_type& resource,
    encoding_form ef,
    std::endian endianness,
    flush_strategy fs
)
noexcept
    : text_input_stream<IOResource>{resource, ef, endianness}
    , text_output_stream<IOResource>{resource, ef, endianness, fs}
    , m_resource{resource}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

template <
    typename IOResource
>
typename text_io_stream<IOResource>::wrapped_resource_type*
text_io_stream<IOResource>::operator -> ()
const noexcept
{
    return &m_resource;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
