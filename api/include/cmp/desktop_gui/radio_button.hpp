// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_RADIO_BUTTON_HPP_INCLUDED
#define CMP_DESKTOP_GUI_RADIO_BUTTON_HPP_INCLUDED

#include <string>
#include <string_view>
#include <functional>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS radio_button
    : public widget
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    radio_button (
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

using radio_button_truptr = trusted_ptr<radio_button>;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_RADIO_BUTTON_HPP_INCLUDED
