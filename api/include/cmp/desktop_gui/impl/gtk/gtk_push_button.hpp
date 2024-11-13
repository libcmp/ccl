// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_GTK_PUSH_BUTTON_HPP_INCLUDED
#define CMP_DESKTOP_GUI_GTK_PUSH_BUTTON_HPP_INCLUDED

#include <string>
#include <string_view>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS push_button
    : public widget
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    push_button (
        const window_native_handle& handle
    );

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    std::u8string
    get_text ()
    const;

    CMP_CONDITIONAL_EXPORT
    void
    set_text (
        std::u8string_view new_text
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_GTK_PUSH_BUTTON_HPP_INCLUDED
