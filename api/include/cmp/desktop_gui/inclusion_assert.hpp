// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_INCLUSION_ASSERT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_INCLUSION_ASSERT_HPP_INCLUDED

#include <cmp/core/platform.hpp>

static_assert(
    CMP_CONFIG_DESKTOP_GUI_PACKAGE_EXCLUDED == false,
    "The Desktop GUI package must be included for this header to be used."
);

static_assert(
    CMP_CONFIG_HEADER_ONLY == false,
    "The Desktop GUI package requires that header-only support be disabled."
);

#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
static_assert(
    CMP_CONFIG_USE_QT != CMP_CONFIG_USE_GTK,
    "On Linux and FreeBSD, you must pick between Qt and GTK."
);
#endif

#endif // CMP_DESKTOP_GUI_INCLUSION_ASSERT_HPP_INCLUDED
