// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_GUI_INCLUSION_ASSERT_HPP_INCLUDED
#define CMP_GUI_INCLUSION_ASSERT_HPP_INCLUDED

#include <cmp/core/config.hpp>

static_assert(
    CMP_CONFIG_DESKTOP_GUI_PACKAGE_EXCLUDED == false,
    "The Desktop GUI package must be included for this header to be used."
);

#endif // CMP_GUI_INCLUSION_ASSERT_HPP_INCLUDED
