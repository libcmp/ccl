// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <QPushButton>

#include <cmp/desktop_gui/push_button.hpp>

namespace cmp {

// ---------------------------------------------------------- cmp::push_button

// Constructors and Destructor ------------------------------------------------

push_button::push_button (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .cmp_main_window_handle,
              native_widget_kind::push_button
          )
      }
{
    m_trigger_event_handler = impl::noop<>;
    initialize();
} // function -----------------------------------------------------------------

push_button::push_button (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
        enclosing_layout,
        impl::create_widget(
            parent_widget_handle.widget_handle,
            native_widget_kind::push_button
        )
    }
{
    m_trigger_event_handler = impl::noop<>;
    initialize();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
push_button::get_preferred_width ()
const noexcept
{
    return static_cast<QPushButton*>(grab_native_handle().widget_handle)
        ->sizeHint().width();
} // function -----------------------------------------------------------------

pixval
push_button::get_preferred_height ()
const noexcept
{
    return static_cast<QPushButton*>(grab_native_handle().widget_handle)
        ->sizeHint().height();
} // function -----------------------------------------------------------------

void
push_button::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    QSize size_hint{
        static_cast<QPushButton*>(
            grab_native_handle().widget_handle
        )->sizeHint()
    };
    width = size_hint.width();
    height = size_hint.height();
} // function -----------------------------------------------------------------

std::u8string
push_button::get_text ()
const
{
    return to_u8string(
        static_cast<QPushButton*>(grab_native_handle().widget_handle)
            ->text().toStdU16String()
    );
} // function -----------------------------------------------------------------

void
push_button::set_text (
    std::u8string_view new_text
) {
    static_cast<QPushButton*>(grab_native_handle().widget_handle)->setText(
        QString::fromUtf8(new_text.data())
    );
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

void
push_button::initialize ()
{
    QObject::connect(
        static_cast<QPushButton*>(grab_native_handle().widget_handle),
        &QPushButton::clicked,
        [this] () {
            m_trigger_event_handler();
        }
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
