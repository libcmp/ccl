// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/push_button.hpp>

namespace cmp {

// ---------------------------------------------------------- cmp::push_button

// Constructors and Destructor ------------------------------------------------

push_button::push_button (
    const window_native_handle& handle
)
    : widget{
          impl::create_widget(
              handle,
              impl::native_widget_kind::push_button
          )
      }
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

std::u8string
push_button::get_text ()
const
{
    std::u8string result;
    for (
        const char* current_character{
            gtk_button_get_label(
                GTK_BUTTON(grab_native_handle().widget_handle)
            )
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
    gtk_button_set_label(
        GTK_BUTTON(grab_native_handle().widget_handle),
        reinterpret_cast<const char*>(new_text.data())
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
