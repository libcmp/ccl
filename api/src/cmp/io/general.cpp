// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/general.hpp>

namespace cmp {

void
invert_endianness (
    std::byte* data,
    std::size_t byte_count
)
noexcept
{
    std::byte* begin{data};
    std::byte* end{data + byte_count - 1};
    while (begin < end) {
        std::swap(*(begin++), *(end--));
    }
} // function -----------------------------------------------------------------

// -------------------------------------------------- cmp::invalid_access_mode

// Core -----------------------------------------------------------------------

const char*
invalid_access_mode::what ()
const noexcept
{
    return "The IO operation attempted is not permitted under the access "
           "mode used. For example, trying to write to a file that was "
           "opened as read-only.";
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
