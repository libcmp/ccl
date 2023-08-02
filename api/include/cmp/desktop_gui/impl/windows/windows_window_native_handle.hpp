// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOWS_WINDOW_NATIVE_HANDLE_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOWS_WINDOW_NATIVE_HANDLE_HPP_INCLUDED

#include <Windows.h>

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

class CMP_LIBRARY_NAME window_native_handle {
public:
    // Public Data ------------------------------------------------------------

    int show_command;
    HWND window_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_WINDOWS_WINDOW_NATIVE_HANDLE_HPP_INCLUDED
