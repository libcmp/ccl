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
    return 100;
} // function -----------------------------------------------------------------

pixval
label::get_preferred_height ()
const noexcept
{
    return 25;
} // function -----------------------------------------------------------------

void
label::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    width = 100;
    height = 25;
} // function -----------------------------------------------------------------

std::u8string
label::get_text ()
const
{
    std::u8string result;
    for (
        const char* current_character{
            [[reinterpret_cast<NSTextField*>(grab_native_handle().widget_handle) stringValue]
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
label::set_text (
    std::u8string_view new_text
) {
    [reinterpret_cast<NSTextField*>(grab_native_handle().widget_handle) setStringValue:
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(new_text.data())
        ]
    ];
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
