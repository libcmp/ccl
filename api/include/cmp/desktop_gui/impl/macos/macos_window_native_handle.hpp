// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_MACOS_WINDOW_NATIVE_HANDLE_HPP_INCLUDED
#define CMP_DESKTOP_GUI_MACOS_WINDOW_NATIVE_HANDLE_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

class CMP_LIBRARY_NAME window_native_handle {
public:
    // Public Data ------------------------------------------------------------

    void* cmp_window_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_MACOS_WINDOW_NATIVE_HANDLE_HPP_INCLUDED
