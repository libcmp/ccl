// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_GROUP_BOX_HPP_INCLUDED
#define CMP_DESKTOP_GUI_GROUP_BOX_HPP_INCLUDED

#include <string>
#include <string_view>
#include <functional>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS group_box
    : public widget
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    explicit
    group_box (
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

using group_box_truptr = trusted_ptr<group_box>;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_GROUP_BOX_HPP_INCLUDED
