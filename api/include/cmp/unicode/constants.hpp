// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_CONSTANTS_HPP_INCLUDED
#define CMP_UNICODE_CONSTANTS_HPP_INCLUDED

namespace cmp {

/**
    Description:
        The code point for a BOM (byte order mark).
*/
constexpr char32_t bom{0xFEFF};

/**
    Description:
        The minimum value for a leading surrogate.
*/
constexpr char16_t leading_surrogate_minimum_value{0xD800};

/**
    Description:
        The maximum value for a leading surrogate.
*/
constexpr char16_t leading_surrogate_maximum_value{0xDBFF};

/**
    Description:
        The minimum value for a trailing surrogate.
*/
constexpr char16_t trailing_surrogate_minimum_value{0xDC00};

/**
    Description:
        The maximum value for a trailing surrogate.
*/
constexpr char16_t trailing_surrogate_maximum_value{0xDFFF};

/**
    Description:
        The highest valid code point.
*/
constexpr char32_t maximum_code_point{0x10FFFF};

/**
    Description:
        The highest code point in the basic multilingual plane (BMP).
*/
constexpr char32_t maximum_bmp_code_point{0xFFFF};

} // namespace ----------------------------------------------------------------

#endif // CMP_UNICODE_CONSTANTS_HPP_INCLUDED
