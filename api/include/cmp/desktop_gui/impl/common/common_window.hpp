// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_COMMON_WINDOW_HPP_INCLUDED
#define CMP_DESKTOP_GUI_COMMON_WINDOW_HPP_INCLUDED

#include <cmp/core/platform.hpp>

#if defined(CMP_OS_WINDOWS)
#   include <cmp/desktop_gui/impl/windows/windows_window.hpp>
#elif defined(CMP_OS_MACOS)
#   include <cmp/desktop_gui/impl/macos/macos_window.hpp>
#elif defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
#   include <cmp/desktop_gui/impl/gtk/gtk_window.hpp>
#endif

#endif // CMP_DESKTOP_GUI_COMMON_WINDOW_HPP_INCLUDED
