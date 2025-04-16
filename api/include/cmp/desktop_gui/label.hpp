// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_LABEL_HPP_INCLUDED
#define CMP_DESKTOP_GUI_LABEL_HPP_INCLUDED

#include <string>
#include <string_view>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS label
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::label
    };

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    explicit
    label (
        layout& enclosing_layout
    );

    CMP_CONDITIONAL_EXPORT
    label (
        const widget_native_handle& parent_widget_handle,
        layout& enclosing_layout
    );

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    pixval
    get_preferred_width ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_preferred_height ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_preferred_size (
        pixval& width,
        pixval& height
    )
    const noexcept override;

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

using label_truptr = trusted_ptr<label>;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_LABEL_HPP_INCLUDED
