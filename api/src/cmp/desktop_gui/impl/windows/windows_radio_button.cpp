// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <windowsx.h>

#include <cmp/desktop_gui/radio_button.hpp>

namespace cmp {

// --------------------------------------------------------- cmp::radio_button

// Constructors and Destructor ------------------------------------------------

radio_button::radio_button (
    layout& enclosing_layout,
    check_group<radio_button>& group
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle().window_handle,
              native_widget_kind::radio_button
          )
      }
    , m_group{group}
{
    m_toggle_event_handler = impl::noop<>;
    group.add_element(assure(this));
} // function -----------------------------------------------------------------

radio_button::radio_button (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout,
    check_group<radio_button>& group
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::radio_button
          )
      }
    , m_group{group}
{
    m_toggle_event_handler = impl::noop<>;
    group.add_element(assure(this));
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
radio_button::get_preferred_width ()
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    return to_pixval(
        dotval{static_cast<int>(ideal_size.cx)},
        get_parent_dpi()
    ) + 2;
} // function -----------------------------------------------------------------

pixval
radio_button::get_preferred_height ()
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
radio_button::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    auto dpi{get_parent_dpi()};
    width = to_pixval(dotval{static_cast<int>(ideal_size.cx)}, dpi) + 2;
    height = to_pixval(dotval{static_cast<int>(ideal_size.cy)}, dpi);
} // function -----------------------------------------------------------------

std::u8string
radio_button::get_text ()
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
radio_button::set_text (
    std::u8string_view new_text
) {
    std::wstring title_wstring{to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, title_wstring.data());

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

bool
radio_button::is_checked ()
{
    return Button_GetCheck(grab_native_handle().widget_handle);
} // function -----------------------------------------------------------------

void
radio_button::set_checked (
    bool new_checked
) {
    Button_SetCheck(
        grab_native_handle().widget_handle,
        new_checked ? BST_CHECKED : BST_UNCHECKED
    );
    if (new_checked) {
        m_group.uncheck_complement(assure(this));
    }
} // function -----------------------------------------------------------------

const check_group<radio_button>&
radio_button::grab_group ()
const noexcept
{
    return m_group;
} // function -----------------------------------------------------------------

check_group<radio_button>&
radio_button::grab_group ()
noexcept
{
    return m_group;
} // function -----------------------------------------------------------------

void
radio_button::set_toggle_event_handler (
    const std::function<void()>& new_toggle_event_handler
) {
    m_toggle_event_handler = new_toggle_event_handler;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
radio_button::toggle ()
{
    m_toggle_event_handler();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
