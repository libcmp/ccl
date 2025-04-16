// Copyright (C) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/radio_button.hpp>

namespace cmp {

namespace impl {

void
handle_radio_button_toggle_signal (
    GtkCheckButton* radio_button,
    gpointer user_data
) {
    static_cast<class radio_button*>(user_data)->toggle();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------- cmp::radio_button

// Constructors and Destructor ------------------------------------------------

radio_button::radio_button (
    layout& enclosing_layout,
    check_group<radio_button>& group
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_native_handle()
                .gtk_layout,
              native_widget_kind::radio_button
          )
      }
    , m_group{group}
{
    initialize();
} // function -----------------------------------------------------------------

radio_button::radio_button (
    const widget_native_handle& parent_widget_handle,
    layout& enclosing_layout,
    check_group<radio_button>& group
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              parent_widget_handle.widget_handle,
              native_widget_kind::radio_button
          )
      }
    , m_group{group}
{
    initialize();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

pixval
radio_button::get_preferred_width ()
const noexcept
{
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return width;
} // function -----------------------------------------------------------------

pixval
radio_button::get_preferred_height ()
const noexcept
{
    pixval width;
    pixval height;
    get_preferred_size(width, height);
    return height;
} // function -----------------------------------------------------------------

void
radio_button::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    get_preferred_size_generically(grab_native_handle(), width, height);
} // function -----------------------------------------------------------------

std::u8string
radio_button::get_text ()
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
radio_button::set_text (
    std::u8string_view new_text
) {
    gtk_check_button_set_label(
        GTK_CHECK_BUTTON(grab_native_handle().widget_handle),
        reinterpret_cast<const char*>(new_text.data())
    );
} // function -----------------------------------------------------------------

bool
radio_button::is_checked ()
{
    return gtk_check_button_get_active(
        GTK_CHECK_BUTTON(grab_native_handle().widget_handle)
    );
} // function -----------------------------------------------------------------

void
radio_button::set_checked (
    bool new_checked
) {
    gtk_check_button_set_active(
        GTK_CHECK_BUTTON(grab_native_handle().widget_handle),
        new_checked
    );
    if (new_checked) {
        m_group.uncheck_complement(assure(this));
    }
} // function -----------------------------------------------------------------

const check_group<radio_button>&
radio_button::grab_group ()
const noexcept
{
    return m_group;
} // function -----------------------------------------------------------------

check_group<radio_button>&
radio_button::grab_group ()
noexcept
{
    return m_group;
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

void
radio_button::initialize ()
{
    m_toggle_event_handler = impl::noop<>;
    if (!m_group.grab_elements().empty()) {
        gtk_check_button_set_group(
            GTK_CHECK_BUTTON(grab_native_handle().widget_handle),
            GTK_CHECK_BUTTON(
                m_group.grab_elements().front()
                    ->grab_native_handle().widget_handle
            )
        );
    }
    g_signal_connect(
        grab_native_handle().widget_handle,
        "toggled",
        G_CALLBACK(impl::handle_radio_button_toggle_signal),
        this
    );
    m_group.add_element(assure(this));
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
