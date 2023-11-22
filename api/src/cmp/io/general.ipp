// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/general.hpp>

namespace cmp {

// Free Functions -------------------------------------------------------------

constexpr
std::endian
get_opposite_endianness (
    std::endian endianness
)
noexcept
{
    return endianness == std::endian::little
        ? std::endian::big
        : std::endian::little;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
