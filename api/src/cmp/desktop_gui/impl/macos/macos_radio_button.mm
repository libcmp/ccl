// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

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
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
radio_button::get_preferred_width ()
const noexcept
{
    return 100;
} // function -----------------------------------------------------------------

pixval
radio_button::get_preferred_height ()
const noexcept
{
    return 25;
} // function -----------------------------------------------------------------

void
radio_button::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    width = 100;
    height = 25;
} // function -----------------------------------------------------------------

std::u8string
radio_button::get_text ()
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
radio_button::set_text (
    std::u8string_view new_text
) {
    [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle) setTitle:
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(new_text.data())
        ]
    ];
} // function -----------------------------------------------------------------

bool
radio_button::is_checked ()
{
    return [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle) state]
        == NSControlStateValueOn;
} // function -----------------------------------------------------------------

void
radio_button::set_checked (
    bool new_checked
) {
    [reinterpret_cast<NSButton*>(grab_native_handle().widget_handle) setState:
        new_checked ? NSControlStateValueOn : NSControlStateValueOff
    ];
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
