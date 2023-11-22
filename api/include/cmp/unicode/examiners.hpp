// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_EXAMINERS_HPP_INCLUDED
#define CMP_UNICODE_EXAMINERS_HPP_INCLUDED

#include <cctype>

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/core/config.hpp>
#include <cmp/unicode/constants.hpp>

namespace cmp {

// Free Functions -------------------------------------------------------------

/**
    Description:
        Returns true if the given code point fits
        in 7 bits. Otherwise, returns false.

    Parameters:
        code_point:
            The code point to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
fits_in_7_bits (
    char32_t code_point
)
noexcept;

/**
    Description:
        Returns true if the given UTF-8 code unit is standalone (meaning that
        it stands on its own and is not part of a sequence of code units).
        Otherwise, returns false.

    Parameters:
        code_unit:
            The UTF-8 code unit to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_standalone_byte (
    char8_t code_unit
)
noexcept;

/**
    Description:
        Returns true if the given UTF-8 code unit is a leading byte (meaning
        that it marks the beginning of a sequence of code units). Otherwise,
        returns false.

    Parameters:
        code_unit:
            The UTF-8 code unit to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_leading_byte (
    char8_t code_unit
)
noexcept;

/**
    Description:
        Returns true if the given UTF-8 code unit is a trailing byte (meaning
        that it follows a leading byte). Otherwise, returns false.

    Parameters:
        code_unit:
            The UTF-8 code unit to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_trailing_byte (
    char8_t code_unit
)
noexcept;

/**
    Description:
        Returns true if the given UTF-16 code unit is a leading
        surrogate (meaning the first code unit of a surrogate pair).
        Otherwise, returns false.

    Parameters:
        code_unit:
            The UTF-16 code unit to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_leading_surrogate (
    char16_t code_unit
)
noexcept;

/**
    Description:
        Returns true if the given UTF-16 code unit is a trailing
        surrogate (meaning the last code unit of a surrogate pair).
        Otherwise, returns false.

    Parameters:
        code_unit:
            The UTF-16 code unit to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_trailing_surrogate (
    char16_t code_unit
)
noexcept;

/**
    Description:
        Returns true if the given UTF-16 code unit
        is a surrogate. Otherwise, returns false.

    Parameters:
        code_unit:
            The UTF-16 code unit to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_surrogate (
    char16_t code_unit
)
noexcept;

/**
    Description:
        Returns true if the given code point
        is valid. Otherwise, returns false.

    Parameters:
        code_point:
            The code point to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_code_point_valid (
    char32_t code_point
)
noexcept;

/**
    Description:
        Returns true if the given code point represents
        a whitespace character, and false if it does not.

    Parameters:
        code_point:
            The code point to examine.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_whitespace (
    char32_t code_point
)
noexcept;

/**
    Description:
        Returns true if the given character represents a
        digit in the number system with the given radix.
        Otherwise, returns false. For example, '7' is a
        valid base-8 digit, 'F' is a valid base-16 digit,
        'G' is a valid base-17 digit, and so on.

    Parameters:
        character:
            The character (code point) to examine.
        radix:
            The radix to consider.
*/
CMP_LIBRARY_NAME
constexpr
bool
is_radix_digit (
    char32_t character,
    unsigned int radix
)
noexcept;

} // namespace ----------------------------------------------------------------

#include <cmp/unicode/examiners.ipp>

#endif // CMP_UNICODE_EXAMINERS_HPP_INCLUDED
