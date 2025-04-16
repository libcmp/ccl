// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOWS_WINDOW_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOWS_WINDOW_HPP_INCLUDED

#include <chrono>
#include <string>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/impl/common/common_desktop_gui_application.hpp>
#include <cmp/desktop_gui/impl/windows/windows_window_native_handle.hpp>
#include <cmp/desktop_gui/close_event.hpp>
#include <cmp/desktop_gui/key_event.hpp>
#include <cmp/desktop_gui/layout.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

namespace impl {

void
forward_resize_event_to_window (
    HWND window_handle
);

void
forward_root_layout_update_to_window (
    HWND window_handle
);

} // namespace ----------------------------------------------------------------

class CMP_CONDITIONAL_EXPORT_CLASS window
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    window (
        pixval initial_width,
        pixval initial_height,
        const std::u8string& initial_title,
        window_mode initial_mode
    );

    virtual
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

    CMP_CONDITIONAL_EXPORT
    window (
        window&& other
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    window&
    operator = (
        window&& other
    ) &
    noexcept;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    window_native_handle&
    grab_native_handle ()
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const window_native_handle&
    grab_native_handle ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    std::u8string
    get_title ()
    const;

    CMP_CONDITIONAL_EXPORT
    void
    set_title (
        const std::u8string& new_title
    );

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    layout&
    grab_root_layout ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    get_size (
        pixval& width,
        pixval& height
    )
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_size (
        const pixval& new_width,
        const pixval& new_height
    )
    noexcept;

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    bool
    open (
        pixval width,
        pixval height,
        const std::u8string& title,
        window_mode mode
    );

    CMP_CONDITIONAL_EXPORT
    void
    show ();

    CMP_CONDITIONAL_EXPORT
    void
    hide ();

    CMP_CONDITIONAL_EXPORT
    void
    close ();

    CMP_CONDITIONAL_EXPORT
    virtual
    void
    update (
        double delta_seconds,
        double total_seconds
    );

    CMP_CONDITIONAL_EXPORT
    virtual
    void
    handle_key_down_event (
        key_event& ev
    );

    CMP_CONDITIONAL_EXPORT
    virtual
    void
    handle_key_up_event (
        key_event& ev
    );

    CMP_CONDITIONAL_EXPORT
    virtual
    void
    handle_resize_event ();

    CMP_CONDITIONAL_EXPORT
    virtual
    void
    handle_close_event (
        close_event& ev
    );

    CMP_CONDITIONAL_EXPORT
    virtual
    void
    handle_dpi_update_event (
        int old_dpi,
        int new_dpi
    );

    // Friends ----------------------------------------------------------------

    friend
    void
    impl::update_window (
        window* w
    );

    friend
    void
    impl::forward_resize_event_to_window (
        HWND window_handle
    );

    friend
    void
    impl::forward_root_layout_update_to_window (
        HWND window_handle
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
    layout m_root_layout;

    // Private Functions ------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    void
    update_root_layout ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    fix_association ()
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_WINDOWS_WINDOW_HPP_INCLUDED
