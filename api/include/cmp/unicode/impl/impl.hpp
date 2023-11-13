// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_IMPL_HPP_INCLUDED
#define CMP_UNICODE_IMPL_HPP_INCLUDED

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/core/config.hpp>
#include <cmp/unicode/examiners.hpp>
#include <cmp/unicode/exceptions.hpp>

namespace cmp {

namespace impl {

CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
int
initialize_utf8_sequence (
    char8_t leading_code_unit,
    char32_t& initial_code_point_value
);

CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
int
initialize_utf16_sequence (
    char16_t leading_code_unit,
    char32_t& initial_code_point_value
);

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/unicode/impl/impl.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_UNICODE_IMPL_HPP_INCLUDED
