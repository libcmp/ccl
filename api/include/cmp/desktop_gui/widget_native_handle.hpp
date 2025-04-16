// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WIDGET_NATIVE_HANDLE_HPP_INCLUDED

#include <cmp/core/platform.hpp>

#if defined(CMP_OS_WINDOWS)
#   include <cmp/desktop_gui/impl/windows/windows_widget_native_handle.hpp>
#elif defined(CMP_OS_MACOS)
#   include <cmp/desktop_gui/impl/macos/macos_widget_native_handle.hpp>
#elif defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
#   if CMP_CONFIG_USE_QT == true
#       include <cmp/desktop_gui/impl/qt/qt_widget_native_handle.hpp>
#   else
#       include <cmp/desktop_gui/impl/gtk/gtk_widget_native_handle.hpp>
#   endif
#endif

#endif // CMP_DESKTOP_GUI_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
