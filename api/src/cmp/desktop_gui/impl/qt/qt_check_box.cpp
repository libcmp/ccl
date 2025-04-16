// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <QCheckBox>

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
              enclosing_layout.grab_enclosing_window_handle()
                  .cmp_main_window_handle,
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
    return static_cast<QCheckBox*>(grab_native_handle().widget_handle)
        ->sizeHint().width();
} // function -----------------------------------------------------------------

pixval
check_box::get_preferred_height ()
const noexcept
{
    return static_cast<QCheckBox*>(grab_native_handle().widget_handle)
        ->sizeHint().height();
} // function -----------------------------------------------------------------

void
check_box::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    QSize size_hint{
        static_cast<QCheckBox*>(
            grab_native_handle().widget_handle
        )->sizeHint()
    };
    width = size_hint.width();
    height = size_hint.height();
} // function -----------------------------------------------------------------

std::u8string
check_box::get_text ()
const
{
    return to_u8string(
        static_cast<QCheckBox*>(grab_native_handle().widget_handle)
            ->text().toStdU16String()
    );
} // function -----------------------------------------------------------------

void
check_box::set_text (
    std::u8string_view new_text
) {
    static_cast<QCheckBox*>(grab_native_handle().widget_handle)->setText(
        QString::fromUtf8(new_text.data())
    );
} // function -----------------------------------------------------------------

bool
check_box::is_checked ()
{
    return static_cast<QCheckBox*>(grab_native_handle().widget_handle)
        ->isChecked();
} // function -----------------------------------------------------------------

void
check_box::set_checked (
    bool new_checked
) {
    static_cast<QCheckBox*>(grab_native_handle().widget_handle)
        ->setChecked(new_checked);
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
