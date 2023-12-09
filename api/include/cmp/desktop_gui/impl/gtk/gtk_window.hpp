// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_GTK_WINDOW_HPP_INCLUDED
#define CMP_DESKTOP_GUI_GTK_WINDOW_HPP_INCLUDED

#include <algorithm>
#include <chrono>
#include <string>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/impl/common/common_desktop_gui_application.hpp>
#include <cmp/desktop_gui/impl/gtk/gtk_window_native_handle.hpp>
#include <cmp/desktop_gui/close_event.hpp>
#include <cmp/desktop_gui/key_event.hpp>

namespace cmp {

class CMP_LIBRARY_NAME window
{
public:
    // Constructors and Destructor --------------------------------------------

    explicit
    window (
        int initial_width = 400,
        int initial_height = 300,
        const std::u8string& initial_title = u8"",
        window_mode initial_mode = window_mode::standard
    );

    ~window ()
    = default;

    // Copy Operations --------------------------------------------------------

    window (
        const window& other
    )
    = delete;

    window&
    operator = (
        const window& other
    )
    = delete;

    // Move Operations --------------------------------------------------------

    window (
        window&& other
    )
    noexcept;

    window&
    operator = (
        window&& other
    )
    noexcept;

    // Accessors --------------------------------------------------------------

    window_native_handle&
    grab_native_handle ()
    noexcept;

    const window_native_handle&
    grab_native_handle ()
    const noexcept;

    std::u8string
    get_title ()
    const;

    void
    set_title (
        const std::u8string& new_title
    );

    // Core -------------------------------------------------------------------

    bool
    open (
        int width,
        int height,
        const std::u8string& title,
        window_mode mode
    );

    void
    show ();

    void
    hide ();

    void
    close ();

    virtual
    void
    update (
        double delta_seconds,
        double total_seconds
    );

    virtual
    void
    handle_key_down_event (
        key_event& ev
    );

    virtual
    void
    handle_key_up_event (
        key_event& ev
    );

    virtual
    void
    handle_resize_event ();

    virtual
    void
    handle_close_event (
        close_event& ev
    );

    // Friends ----------------------------------------------------------------

    friend
    void
    impl::update_window (
        window* w
    );

private:
    // Private Data -----------------------------------------------------------

    window_native_handle m_native_handle;
    std::chrono::steady_clock::time_point m_start_time;
    std::chrono::steady_clock::time_point m_last_time;
    GtkEventController* m_controller;

    // Private Functions ------------------------------------------------------

    void
    fix_association ()
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_GTK_WINDOW_HPP_INCLUDED
