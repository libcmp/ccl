// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <QGroupBox>

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
    return to_u8string(
        static_cast<QGroupBox*>(grab_native_handle().widget_handle)
            ->title().toStdU16String()
    );
} // function -----------------------------------------------------------------

void
group_box::set_text (
    std::u8string_view new_text
) {
    static_cast<QGroupBox*>(grab_native_handle().widget_handle)->setTitle(
        QString::fromUtf8(new_text.data())
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
