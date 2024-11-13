// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/label.hpp>

namespace cmp {

// ---------------------------------------------------------------- cmp::label

// Constructors and Destructor ------------------------------------------------

label::label (
    const window_native_handle& handle
)
    : widget{
          impl::create_widget(
              handle,
              impl::native_widget_kind::label
          )
      }
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
label::get_preferred_width ()
const noexcept
{
    std::wstring text_wstring;
    text_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        text_wstring.data(),
        text_wstring.size() + 1
    );
    SIZE ideal_size{0L, 0L};
    GetTextExtentPoint32W(
        GetDC(grab_native_handle().widget_handle),
        text_wstring.data(),
        text_wstring.size(),
        &ideal_size
    );
    return ideal_size.cx;
} // function -----------------------------------------------------------------

pixval
label::get_preferred_height ()
const noexcept
{
    std::wstring text_wstring;
    text_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        text_wstring.data(),
        text_wstring.size() + 1
    );
    SIZE ideal_size{0L, 0L};
    GetTextExtentPoint32W(
        GetDC(grab_native_handle().widget_handle),
        text_wstring.data(),
        text_wstring.size(),
        &ideal_size
    );
    return ideal_size.cy;
} // function -----------------------------------------------------------------

void
label::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    std::wstring text_wstring;
    text_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        text_wstring.data(),
        text_wstring.size() + 1
    );
    SIZE ideal_size{0L, 0L};
    GetTextExtentPoint32W(
        GetDC(grab_native_handle().widget_handle),
        text_wstring.data(),
        text_wstring.size(),
        &ideal_size
    );
    width = ideal_size.cx;
    height = ideal_size.cy;
} // function -----------------------------------------------------------------

std::u8string
label::get_text ()
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
label::set_text (
    std::u8string_view new_text
) {
    std::wstring title_wstring{to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, title_wstring.data());
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
