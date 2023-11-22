// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/general.hpp>

namespace cmp {

// Free Functions -------------------------------------------------------------

template <
    std::floating_point T1,
    std::floating_point T2
>
bool
cmp_equal (
    T1 value1,
    T2 value2,
    unsigned int relevant_decimal_places
)
noexcept
{
    double power{std::pow(10, relevant_decimal_places)};
    return std::floor(value1 * power) == std::floor(value2 * power);
} // function -----------------------------------------------------------------

template <
    std::floating_point T1,
    std::floating_point T2
>
bool
cmp_not_equal (
    T1 value1,
    T2 value2,
    int relevant_decimal_places
)
noexcept
{
    return !cmp_equal(value1, value2, relevant_decimal_places);
} // function -----------------------------------------------------------------

template <
    std::integral T
>
unsigned int
count_digits (
    T integer,
    T radix
)
noexcept
{
    unsigned int digit_count{0};
    do {
        ++digit_count;
        integer /= radix;
    } while (integer);
    return digit_count;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
