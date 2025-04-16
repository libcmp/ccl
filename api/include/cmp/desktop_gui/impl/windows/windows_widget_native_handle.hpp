// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOWS_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOWS_WIDGET_NATIVE_HANDLE_HPP_INCLUDED

#include <Windows.h>

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS widget_native_handle {
public:
    HWND parent_handle;
    HWND widget_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_WINDOWS_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
