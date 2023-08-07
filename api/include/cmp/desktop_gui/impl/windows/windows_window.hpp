// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOWS_WINDOW_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOWS_WINDOW_HPP_INCLUDED

#include <string>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/impl/windows/windows_window_native_handle.hpp>
#include <cmp/desktop_gui/impl/windows/windows_desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>
#include <cmp/io/uio.hpp>
namespace cmp {

namespace impl {

} // namespace ----------------------------------------------------------------

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
        int initial_width,
        int initial_height,
        const std::u8string& initial_title,
        window_mode initial_mode
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

    friend
    LRESULT CALLBACK
    impl::window_procedure (
        HWND window_handle,
        UINT message,
        WPARAM w_param,
        LPARAM l_param
    );

private:
    // Private Data -----------------------------------------------------------

    window_native_handle m_native_handle;
    std::chrono::steady_clock::time_point m_start_time;
    std::chrono::steady_clock::time_point m_last_time;

    // Private Functions ------------------------------------------------------

    void
    update ();

    void
    update_association ()
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_WINDOWS_WINDOW_HPP_INCLUDED