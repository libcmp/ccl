// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_CHECK_BOX_HPP_INCLUDED
#define CMP_DESKTOP_GUI_CHECK_BOX_HPP_INCLUDED

#include <string>
#include <string_view>
#include <functional>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS check_box
    : public widget
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    check_box (
        const window_native_handle& handle
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

    CMP_CONDITIONAL_EXPORT
    bool
    is_checked ();

    CMP_CONDITIONAL_EXPORT
    void
    set_checked (
        bool new_checked
    );

    CMP_CONDITIONAL_EXPORT
    void
    set_toggle_event_handler (
        const std::function<void()>& new_toggle_event_handler
    );

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    void
    toggle ();

private:
    // Private Data -----------------------------------------------------------

    std::function<void()> m_toggle_event_handler;
}; // class -------------------------------------------------------------------

using check_box_truptr = trusted_ptr<check_box>;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_CHECK_BOX_HPP_INCLUDED
