// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_PUSH_BUTTON_HPP_INCLUDED
#define CMP_DESKTOP_GUI_PUSH_BUTTON_HPP_INCLUDED

#include <string>
#include <string_view>
#include <functional>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS push_button
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::push_button
    };

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    explicit
    push_button (
        layout& enclosing_layout
    );

    CMP_CONDITIONAL_EXPORT
    push_button (
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

    CMP_CONDITIONAL_EXPORT
    void
    set_trigger_event_handler (
        const std::function<void()>& new_trigger_event_handler
    );

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    void
    trigger ();

private:
    // Private Data -----------------------------------------------------------

    std::function<void()> m_trigger_event_handler;

    // Private Functions ------------------------------------------------------

#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
    void
    initialize();
#endif
}; // class -------------------------------------------------------------------

using push_button_truptr = trusted_ptr<push_button>;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_PUSH_BUTTON_HPP_INCLUDED
