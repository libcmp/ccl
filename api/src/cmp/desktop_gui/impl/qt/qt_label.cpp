// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <QLabel>

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
    return static_cast<QLabel*>(grab_native_handle().widget_handle)
        ->sizeHint().width();
} // function -----------------------------------------------------------------

pixval
label::get_preferred_height ()
const noexcept
{
    return static_cast<QLabel*>(grab_native_handle().widget_handle)
        ->sizeHint().height();
} // function -----------------------------------------------------------------

void
label::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    QSize size_hint{
        static_cast<QLabel*>(
            grab_native_handle().widget_handle
        )->sizeHint()
    };
    width = size_hint.width();
    height = size_hint.height();
} // function -----------------------------------------------------------------

std::u8string
label::get_text ()
const
{
    return to_u8string(
        static_cast<QLabel*>(grab_native_handle().widget_handle)
            ->text().toStdU16String()
    );
} // function -----------------------------------------------------------------

void
label::set_text (
    std::u8string_view new_text
) {
    static_cast<QLabel*>(grab_native_handle().widget_handle)->setText(
        QString::fromUtf8(new_text.data())
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
