// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_RADIO_BUTTON_HPP_INCLUDED
#define CMP_DESKTOP_GUI_RADIO_BUTTON_HPP_INCLUDED

#include <string>
#include <string_view>
#include <functional>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/desktop_gui/check_group.hpp>
#include <cmp/unicode/algorithms.hpp>

#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)

#if CMP_CONFIG_USE_QT == true
#include <QButtonGroup>
#else
#include <gtk/gtk.h>
#endif

#endif

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS radio_button
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::radio_button
    };

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    radio_button (
        layout& enclosing_layout,
        check_group<radio_button>& group
    );

    CMP_CONDITIONAL_EXPORT
    radio_button (
        const widget_native_handle& parent_widget_handle,
        layout& enclosing_layout,
        check_group<radio_button>& group
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
    const check_group<radio_button>&
    grab_group ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    check_group<radio_button>&
    grab_group ()
    noexcept;

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

    check_group<radio_button>& m_group;
    std::function<void()> m_toggle_event_handler;
#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
#   if CMP_CONFIG_USE_QT == true
    static QButtonGroup g_button_group;
#   endif
#endif

    // Private Functions ------------------------------------------------------

#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
    void
    initialize();
#endif
}; // class -------------------------------------------------------------------

using radio_button_truptr = trusted_ptr<radio_button>;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_RADIO_BUTTON_HPP_INCLUDED
