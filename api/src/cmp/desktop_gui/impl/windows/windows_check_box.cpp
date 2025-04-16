// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/check_box.hpp>

namespace cmp {

// ------------------------------------------------------------ cmp::check_box

// Constructors and Destructor ------------------------------------------------

check_box::check_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle().window_handle,
              native_widget_kind::check_box
          )
      }
{
    m_toggle_event_handler = impl::noop<>;
} // function -----------------------------------------------------------------

check_box::check_box (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::check_box
          )
      }
{
    m_toggle_event_handler = impl::noop<>;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
check_box::get_preferred_width ()
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    return to_pixval(
        dotval{static_cast<int>(ideal_size.cx)},
        get_parent_dpi()
    ) + 4;
} // function -----------------------------------------------------------------

pixval
check_box::get_preferred_height ()
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    return to_pixval(
        dotval{static_cast<int>(ideal_size.cy)},
        get_parent_dpi()
    );
} // function -----------------------------------------------------------------

void
check_box::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    auto dpi{get_parent_dpi()};
    width = to_pixval(dotval{static_cast<int>(ideal_size.cx)}, dpi) + 4;
    height = to_pixval(dotval{static_cast<int>(ideal_size.cy)}, dpi);
} // function -----------------------------------------------------------------

std::u8string
check_box::get_text ()
const
{
    std::wstring title_wstring;
    title_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        title_wstring.data(),
        title_wstring.size() + 1
    );
    return to_u8string(title_wstring);
} // function -----------------------------------------------------------------

void
check_box::set_text (
    std::u8string_view new_text
) {
    std::wstring title_wstring{to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, title_wstring.data());

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

bool
check_box::is_checked ()
{
    return Button_GetCheck(grab_native_handle().widget_handle);
} // function -----------------------------------------------------------------

void
check_box::set_checked (
    bool new_checked
) {
    Button_SetCheck(
        grab_native_handle().widget_handle,
        new_checked ? BST_CHECKED : BST_UNCHECKED
    );
} // function -----------------------------------------------------------------

void
check_box::set_toggle_event_handler (
    const std::function<void()>& new_toggle_event_handler
) {
    m_toggle_event_handler = new_toggle_event_handler;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
check_box::toggle ()
{
    m_toggle_event_handler();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
