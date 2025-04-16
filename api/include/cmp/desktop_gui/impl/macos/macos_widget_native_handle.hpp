// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_MACOS_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
#define CMP_DESKTOP_GUI_MACOS_WIDGET_NATIVE_HANDLE_HPP_INCLUDED

#include <AppKit/AppKit.h>

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS widget_native_handle {
public:
    NSResponder* parent_handle;
    NSView* widget_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_MACOS_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
