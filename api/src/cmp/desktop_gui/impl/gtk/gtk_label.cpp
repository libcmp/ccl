// Copyright (C) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/label.hpp>

#include <gtk/gtk.h>

namespace cmp {

// ---------------------------------------------------------------- cmp::label

// Constructors and Destructor ------------------------------------------------

label::label (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_native_handle()
                  .gtk_layout,
              native_widget_kind::label
          )
      }
{
} // function -----------------------------------------------------------------

label::label (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::label
          )
      }
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
label::get_preferred_width ()
const noexcept
{
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return width;
} // function -----------------------------------------------------------------

pixval
label::get_preferred_height ()
const noexcept
{
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return height;
} // function -----------------------------------------------------------------

void
label::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    get_preferred_size_generically(grab_native_handle(), width, height);
} // function -----------------------------------------------------------------

std::u8string
label::get_text ()
const
{
    std::u8string result;
    for (
        const char* current_character{
            gtk_label_get_text(
                GTK_LABEL(grab_native_handle().widget_handle)
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
label::set_text (
    std::u8string_view new_text
) {
    gtk_label_set_text(
        GTK_LABEL(grab_native_handle().widget_handle),
        reinterpret_cast<const char*>(new_text.data())
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
