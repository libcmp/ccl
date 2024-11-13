// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/push_button.hpp>

namespace cmp {

// ---------------------------------------------------------- cmp::push_button

// Constructors and Destructor ------------------------------------------------

push_button::push_button (
    const window_native_handle& handle
)
    : widget{
          impl::create_widget(
              handle,
              impl::native_widget_kind::push_button
          )
      }
{
    m_trigger_event_handler = impl::noop<>;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
push_button::get_preferred_width ()
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    return to_pixval(
        dotval{static_cast<int>(ideal_size.cx + 16)},
        get_parent_dpi()
    );
} // function -----------------------------------------------------------------

pixval
push_button::get_preferred_height ()
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    return to_pixval(
        dotval{static_cast<int>(ideal_size.cy + 8)},
        get_parent_dpi()
    );
} // function -----------------------------------------------------------------

void
push_button::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    SIZE ideal_size{0L, 0L};
    Button_GetIdealSize(grab_native_handle().widget_handle, &ideal_size);
    auto dpi{get_parent_dpi()};
    width = to_pixval(dotval{static_cast<int>(ideal_size.cx + 16)}, dpi);
    height = to_pixval(dotval{static_cast<int>(ideal_size.cy + 8)}, dpi);
} // function -----------------------------------------------------------------

std::u8string
push_button::get_text ()
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
push_button::set_text (
    std::u8string_view new_text
) {
    std::wstring title_wstring{to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, title_wstring.data());
} // function -----------------------------------------------------------------

void
push_button::set_trigger_event_handler (
    const std::function<void()>& new_trigger_event_handler
) {
    m_trigger_event_handler = new_trigger_event_handler;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
push_button::trigger ()
{
    m_trigger_event_handler();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
