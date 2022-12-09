// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/examiners.hpp>

namespace cmp {

constexpr
bool
fits_in_7_bits (
    char32_t code_point
)
noexcept
{
    return code_point <= 0b0111'1111;
} // function -----------------------------------------------------------------

constexpr
bool
is_standalone_byte (
    char8_t code_unit
)
noexcept
{
    return fits_in_7_bits(code_unit);
} // function -----------------------------------------------------------------

constexpr
bool
is_leading_byte (
    char8_t code_unit
)
noexcept
{
    return (code_unit >> 5) == 0b110
        || (code_unit >> 4) == 0b1110
        || (code_unit >> 3) == 0b11110;
} // function -----------------------------------------------------------------

constexpr
bool
is_trailing_byte (
    char8_t code_unit
)
noexcept
{
    return (code_unit >> 6) == 0b10;
} // function -----------------------------------------------------------------

constexpr
bool
is_leading_surrogate (
    char16_t code_unit
)
noexcept
{
    return code_unit >= leading_surrogate_minimum_value
        && code_unit <= leading_surrogate_maximum_value;
} // function -----------------------------------------------------------------

constexpr
bool
is_trailing_surrogate (
    char16_t code_unit
)
noexcept
{
    return code_unit >= trailing_surrogate_minimum_value
        && code_unit <= trailing_surrogate_maximum_value;
} // function -----------------------------------------------------------------

constexpr
bool
is_surrogate (
    char16_t code_unit
)
noexcept
{
    return code_unit >= leading_surrogate_minimum_value
        && code_unit <= trailing_surrogate_maximum_value;
} // function -----------------------------------------------------------------

constexpr
bool
is_code_point_valid (
    char32_t code_point
)
noexcept
{
    return code_point <= maximum_code_point
        && !is_surrogate(code_point);
} // function -----------------------------------------------------------------

constexpr
bool
is_whitespace (
    char32_t code_point
)
noexcept
{
    return code_point == 9
        || code_point == 10
        || code_point == 11
        || code_point == 12
        || code_point == 13
        || code_point == 32
        || code_point == 133
        || code_point == 160
        || code_point == 5760
        || code_point == 8192
        || code_point == 8193
        || code_point == 8194
        || code_point == 8195
        || code_point == 8196
        || code_point == 8197
        || code_point == 8198
        || code_point == 8199
        || code_point == 8200
        || code_point == 8201
        || code_point == 8202
        || code_point == 8232
        || code_point == 8233
        || code_point == 8239
        || code_point == 8287
        || code_point == 12288;
} // function -----------------------------------------------------------------

constexpr
bool
is_radix_digit (
    char32_t character,
    unsigned int radix
)
noexcept
{
    if (radix < 10) {
        return character >= '0' && character < ('0' + radix);
    } else {
        char32_t lowercase_character{
            static_cast<char32_t>(
                std::tolower(static_cast<int>(character))
            )
        };
        return (character >= '0' && character <= '9')
            || (
                lowercase_character >= 'a'
                    && lowercase_character < ('a' + radix - 10)
            );
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
