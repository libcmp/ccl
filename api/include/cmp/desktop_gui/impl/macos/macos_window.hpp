// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_MACOS_WINDOW_HPP_INCLUDED
#define CMP_DESKTOP_GUI_MACOS_WINDOW_HPP_INCLUDED

#include <string>
#include <chrono>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/impl/macos/macos_window_native_handle.hpp>
#include <cmp/desktop_gui/impl/macos/macos_desktop_gui_application.hpp>

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
    noexcept = default;

    // Accessors --------------------------------------------------------------

    window_native_handle&
    grab_native_handle ()
    noexcept;

    std::u8string
    get_title ()
    const;

    void
    set_title (
        const std::u8string& new_title
    );

    // Core -------------------------------------------------------------------

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
        key event_key
    );

    virtual
    void
    handle_key_up_event (
        key event_key
    );

    virtual
    void
    handle_resize_event ();

    virtual
    close_window
    handle_close_event ();

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

    // Private Functions ------------------------------------------------------

    void
    update ();
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_MACOS_WINDOW_HPP_INCLUDED
