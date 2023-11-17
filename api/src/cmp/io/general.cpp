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

} // namespace ----------------------------------------------------------------
