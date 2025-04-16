// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

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
                  .cmp_window_handle,
              native_widget_kind::push_button
          )
      }
{
    m_trigger_event_handler = impl::noop<>;
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
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
push_button::get_preferred_width ()
const noexcept
{
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return width;
} // function -----------------------------------------------------------------

pixval
push_button::get_preferred_height ()
const noexcept
{
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return height;
} // function -----------------------------------------------------------------

void
push_button::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    get_preferred_size_generically(
        grab_native_handle(),
        width,
        height
    );
} // function -----------------------------------------------------------------

std::u8string
push_button::get_text ()
const
{
    std::u8string result;
    for (
        const char* current_character{
            [[reinterpret_cast<NSButton*>(grab_native_handle().widget_handle) title]
                UTF8String
            ]
        };
        *current_character != '\0';
        ++current_character
    ) {
        result.push_back(*current_character);
    }
    return result;
} // function -----------------------------------------------------------------

void
push_button::set_text (
    std::u8string_view new_text
) {
    [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle) setTitle:
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(new_text.data())
        ]
    ];
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
