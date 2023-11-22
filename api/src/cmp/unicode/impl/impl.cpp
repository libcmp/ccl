// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/impl/impl.hpp>

namespace cmp {

namespace impl {

// Free Functions -------------------------------------------------------------

int
initialize_utf8_sequence (
    char8_t leading_code_unit,
    char32_t& initial_code_point_value
) {
    if (is_standalone_byte(leading_code_unit)) {
        initial_code_point_value = leading_code_unit;
        return 1;
    } else if ((leading_code_unit >> 5) == 0b110) {
        initial_code_point_value = leading_code_unit & 0b0001'1111;
        return 2;
    } else if ((leading_code_unit >> 4) == 0b1110) {
        initial_code_point_value = leading_code_unit & 0b0000'1111;
        return 3;
    } else if ((leading_code_unit >> 3) == 0b11110) {
        initial_code_point_value = leading_code_unit & 0b0000'0111;
        return 4;
    } else {
        throw invalid_unicode_encoding{};
    }
} // function -----------------------------------------------------------------

int
initialize_utf16_sequence (
    char16_t leading_code_unit,
    char32_t& initial_code_point_value
) {
    if (is_leading_surrogate(leading_code_unit)) {
        initial_code_point_value = (leading_code_unit - 0xD800);
        initial_code_point_value <<= 10;
        return 2;
    } else if (is_trailing_surrogate(leading_code_unit)) {
        throw invalid_unicode_encoding{};
    } else {
        initial_code_point_value = leading_code_unit;
        return 1;
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
