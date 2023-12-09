// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/unix_like/unix_like_uin.hpp>

namespace cmp {

// ------------------------------------------------------- cmp::stdin_resource

// Constructors and Destructor ------------------------------------------------

stdin_resource::stdin_resource (
    std::size_t buffer_capacity
)
noexcept
    : transfer_resource{buffer_capacity}
    , input_resource{buffer_capacity}
{
    tie(uout_resource);
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
stdin_resource::is_at_end ()
const noexcept
{
    return false;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

std::size_t
stdin_resource::read_raw (
    std::byte* data,
    std::size_t byte_count,
    read_request rr
) {
    return ::read(STDIN_FILENO, data, byte_count);
} // function -----------------------------------------------------------------

// --------------------------------------------------------- cmp::stdin_stream

// Constructors and Destructor ------------------------------------------------

stdin_stream::stdin_stream (
    referenced_resource_type& resource
)
noexcept
    : text_input_stream<stdin_resource>{resource, utf8, std::endian::native}
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
