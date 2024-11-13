// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <QRadioButton>

#include <cmp/desktop_gui/radio_button.hpp>

namespace cmp {

// --------------------------------------------------------- cmp::radio_button

// Constructors and Destructor ------------------------------------------------

radio_button::radio_button (
    const window_native_handle& handle
)
    : widget{
          impl::create_widget(
              handle,
              impl::native_widget_kind::radio_button
          )
      }
{
    m_toggle_event_handler = impl::noop<>;
    QObject::connect(
        static_cast<QRadioButton*>(grab_native_handle().widget_handle),
        &QRadioButton::toggled,
        [this] () {
            m_toggle_event_handler();
        }
    );
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
radio_button::get_preferred_width ()
const noexcept
{
    return static_cast<QRadioButton*>(grab_native_handle().widget_handle)
        ->sizeHint().width();
} // function -----------------------------------------------------------------

pixval
radio_button::get_preferred_height ()
const noexcept
{
    return static_cast<QRadioButton*>(grab_native_handle().widget_handle)
        ->sizeHint().height();
} // function -----------------------------------------------------------------

void
radio_button::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    QSize size_hint{
        static_cast<QRadioButton*>(
            grab_native_handle().widget_handle
        )->sizeHint()
    };
    width = size_hint.width();
    height = size_hint.height();
} // function -----------------------------------------------------------------

std::u8string
radio_button::get_text ()
const
{
    return to_u8string(
        static_cast<QRadioButton*>(grab_native_handle().widget_handle)
            ->text().toStdU16String()
    );
} // function -----------------------------------------------------------------

void
radio_button::set_text (
    std::u8string_view new_text
) {
    static_cast<QRadioButton*>(grab_native_handle().widget_handle)->setText(
        QString::fromUtf8(new_text.data())
    );
} // function -----------------------------------------------------------------

bool
radio_button::is_checked ()
{
    return static_cast<QRadioButton*>(grab_native_handle().widget_handle)
        ->isChecked();
} // function -----------------------------------------------------------------

void
radio_button::set_checked (
    bool new_checked
) {
    static_cast<QRadioButton*>(grab_native_handle().widget_handle)
        ->setChecked(new_checked);
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
