// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/unix_like/unix_like_uout.hpp>

namespace cmp {

// ------------------------------------------------------ cmp::stdout_resource

// Constructors and Destructor ------------------------------------------------

stdout_resource::stdout_resource (
    int file_descriptor,
    std::size_t buffer_capacity
)
noexcept
    : transfer_resource{buffer_capacity}
    , output_resource{buffer_capacity}
    , m_file_descriptor{file_descriptor}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
stdout_resource::is_at_end ()
const noexcept
{
    return false;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

std::size_t
stdout_resource::write_raw (
    const std::byte* data,
    std::size_t byte_count
) {
    ssize_t bytes_written{::write(m_file_descriptor, data, byte_count)};
    if (bytes_written == -1) {
        return 0;
    }
    return bytes_written;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
