// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/push_button.hpp>

namespace cmp {

namespace impl {

void
handle_push_button_click_signal (
    GtkButton* push_button,
    gpointer user_data
) {
    static_cast<class push_button*>(user_data)->trigger();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// ---------------------------------------------------------- cmp::push_button

// Constructors and Destructor ------------------------------------------------

push_button::push_button (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_native_handle()
                .gtk_layout,
              native_widget_kind::push_button
          )
      }
{
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
    initialize();
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
    get_preferred_size_generically(grab_native_handle(), width, height);
} // function -----------------------------------------------------------------

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
    m_trigger_event_handler = impl::noop<>;
    g_signal_connect(
        grab_native_handle().widget_handle,
        "clicked",
        G_CALLBACK(impl::handle_push_button_click_signal),
        this
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
