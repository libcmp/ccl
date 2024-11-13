// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/group_box.hpp>

namespace cmp {

// ------------------------------------------------------------ cmp::group_box

// Constructors and Destructor ------------------------------------------------

group_box::group_box (
    const window_native_handle& handle
)
    : widget{
          impl::create_widget(
              handle,
              impl::native_widget_kind::group_box
          )
      }
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

std::u8string
group_box::get_text ()
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
group_box::set_text (
    std::u8string_view new_text
) {
    std::wstring title_wstring{to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, title_wstring.data());
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
