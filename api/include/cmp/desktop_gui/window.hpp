// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOW_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOW_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/core/platform.hpp>

#if defined(CMP_OS_WINDOWS)
#   include <cmp/desktop_gui/impl/windows/windows_window.hpp>
#elif defined(CMP_OS_MACOS)
#   include <cmp/desktop_gui/impl/macos/macos_window.hpp>
#elif defined(CMP_OS_LINUX_BASED)
#   include <cmp/desktop_gui/impl/gtk/gtk_window.hpp>
#endif

#endif // CMP_DESKTOP_GUI_WINDOW_HPP_INCLUDED
