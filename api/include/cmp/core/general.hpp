// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_GENERAL_HPP_INCLUDED
#define CMP_CORE_GENERAL_HPP_INCLUDED

#include <concepts>
#include <cmath>

namespace cmp {

/**
    Description:
        Returns true if the <#parameter>v1</#parameter> and
        <#parameter>v2</#parameter> floating-point values
        are equal up to the given number of decimal places.
        For example, 1.123 and 1.124 are equal up to two
        decimal places because they both end in .12, but
        they are not equal up to three decimal places
        because one ends in .123 and the other ends in
        .124, where the third decimal digit of each number
        is different.

    Parameters:
        value1:
            The first value to consider in the comparison.
        value2:
            The second value to consider in the comparison.
        relevant_decimal_places:
            The number of decimal places that matter in the comparison.
*/
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
noexcept;

/**
    Description:
        Returns true if the <#parameter>v1</#parameter> and
        <#parameter>v2</#parameter> floating-point values
        are not equal up to the given number of decimal places.
        This is implemented as the negation of the result of
        calling <#function>cmp_equal</#function> with the same
        arguments.

    Parameters:
        value1:
            The first value to consider in the comparison.
        value2:
            The second value to consider in the comparison.
        relevant_decimal_places:
            The number of decimal places that matter in the comparison.
*/
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
noexcept;

/**
    Description:
        Returns the number of digits in the input integer.

    Parameters:
        integer:
            The integer to count digits in.
        radix:
            The radix of the integer to count digits in.
*/
template <
    std::integral T
>
unsigned int
count_digits (
    T integer,
    T radix
)
noexcept;

} // namespace ----------------------------------------------------------------

#include <cmp/core/general.ipp>

#endif // CMP_CORE_GENERAL_HPP_INCLUDED
