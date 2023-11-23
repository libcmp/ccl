// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_INCLUSION_ASSERT_HPP_INCLUDED
#define CMP_UNICODE_INCLUSION_ASSERT_HPP_INCLUDED

#include <cmp/core/config.hpp>

static_assert(
    sizeof (wchar_t) == 2 || sizeof (wchar_t) == 4,
    "The size of a wchar_t must be either 2 or 4 bytes."
);

#endif // CMP_UNICODE_INCLUSION_ASSERT_HPP_INCLUDED
