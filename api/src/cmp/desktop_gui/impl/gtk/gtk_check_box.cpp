// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

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
              enclosing_layout.grab_native_handle()
                .gtk_layout,
              native_widget_kind::check_box
          )
      }
{
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
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return width;
} // function -----------------------------------------------------------------

pixval
check_box::get_preferred_height ()
const noexcept
{
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return height;
} // function -----------------------------------------------------------------

void
check_box::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    get_preferred_size_generically(grab_native_handle(), width, height);
} // function -----------------------------------------------------------------

std::u8string
check_box::get_text ()
const
{
    std::u8string result;
    for (
        const char* current_character{
            gtk_check_button_get_label(
                GTK_CHECK_BUTTON(grab_native_handle().widget_handle)
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
check_box::set_text (
    std::u8string_view new_text
) {
    gtk_check_button_set_label(
        GTK_CHECK_BUTTON(grab_native_handle().widget_handle),
        reinterpret_cast<const char*>(new_text.data())
    );
} // function -----------------------------------------------------------------

bool
check_box::is_checked ()
{
    return gtk_check_button_get_active(
        GTK_CHECK_BUTTON(grab_native_handle().widget_handle)
    );
} // function -----------------------------------------------------------------

void
check_box::set_checked (
    bool new_checked
) {
    gtk_check_button_set_active(
        GTK_CHECK_BUTTON(grab_native_handle().widget_handle),
        new_checked
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
