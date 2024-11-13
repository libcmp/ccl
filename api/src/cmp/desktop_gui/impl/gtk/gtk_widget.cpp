// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_widget.hpp>

namespace cmp {

namespace impl {

GtkFixed*
get_fixed (
    GtkWidget* application_window
)
noexcept
{
    return GTK_FIXED(gtk_window_get_child(GTK_WINDOW(application_window)));
} // function -----------------------------------------------------------------

widget_native_handle
create_widget (
    const window_native_handle& parent_window,
    native_widget_kind kind
)
noexcept
{
    GtkWidget* widget;
    switch (kind) {
        case native_widget_kind::check_box:
            widget = gtk_check_button_new();
            break;
        case native_widget_kind::push_button:
            widget = gtk_button_new();
            break;
    }
    gtk_widget_set_visible(widget, false);
    gtk_fixed_put(
        get_fixed(parent_window.gtk_application_window),
        widget,
        0.0,
        0.0
    );
    return {parent_window.gtk_application_window, widget};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    const window_native_handle& handle
)
    : m_native_handle{handle.gtk_application_window, nullptr}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

widget_native_handle&
widget::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

const widget_native_handle&
widget::grab_native_handle ()
const noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

pixval
widget::get_x ()
const noexcept
{
    double current_x;
    double current_y;
    gtk_fixed_get_child_position(
        impl::get_fixed(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        &current_x,
        &current_y
    );
    return current_x;
} // function -----------------------------------------------------------------

void
widget::set_x (
    pixval new_x
)
noexcept
{
    gtk_fixed_move(
        impl::get_fixed(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        new_x.get_value(),
        get_y().get_value()
    );
} // function -----------------------------------------------------------------

pixval
widget::get_y ()
const noexcept
{
    double current_x;
    double current_y;
    gtk_fixed_get_child_position(
        impl::get_fixed(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        &current_x,
        &current_y
    );
    return current_y;
} // function -----------------------------------------------------------------

void
widget::set_y (
    pixval new_y
)
noexcept
{
    gtk_fixed_move(
        impl::get_fixed(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        get_x().get_value(),
        new_y.get_value()
    );
} // function -----------------------------------------------------------------

void
widget::get_position (
    pixval& x,
    pixval& y
)
const noexcept
{
    double current_x;
    double current_y;
    gtk_fixed_get_child_position(
        impl::get_fixed(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        &current_x,
        &current_y
    );
    x.set_value(current_x);
    y.set_value(current_y);
} // function -----------------------------------------------------------------

void
widget::set_position (
    pixval new_x,
    pixval new_y
)
noexcept
{
    gtk_fixed_move(
        impl::get_fixed(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        new_x.get_value(),
        new_y.get_value()
    );
} // function -----------------------------------------------------------------

pixval
widget::get_width ()
const noexcept
{
    return gtk_widget_get_allocated_width(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

void
widget::set_width (
    pixval new_width
)
noexcept
{
    gtk_widget_allocate(
        m_native_handle.widget_handle,
        new_width.get_value(),
        get_height().get_value(),
        -1,
        nullptr
    );
    gtk_widget_queue_allocate(m_native_handle.widget_handle);
    return;
    gtk_widget_set_size_request(
        m_native_handle.widget_handle,
        new_width.get_value() - 20,
        get_height().get_value() - 20
    );
    gtk_widget_queue_resize(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

pixval
widget::get_height ()
const noexcept
{
    return gtk_widget_get_allocated_height(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

void
widget::set_height (
    pixval new_height
)
noexcept
{
    gtk_widget_allocate(
        m_native_handle.widget_handle,
        get_width().get_value(),
        new_height.get_value(),
        -1,
        nullptr
    );
    gtk_widget_queue_allocate(m_native_handle.widget_handle);
    return;
    gtk_widget_set_size_request(
        m_native_handle.widget_handle,
        get_width().get_value() - 20,
        new_height.get_value() - 20
    );
    gtk_widget_queue_resize(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

void
widget::get_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    width.set_value(get_width().get_value());
    height.set_value(get_height().get_value());
} // function -----------------------------------------------------------------

void
widget::set_size (
    pixval new_width,
    pixval new_height
)
noexcept
{
    set_width(new_width);
    set_height(new_height);
    return;
    gtk_widget_allocate(
        m_native_handle.widget_handle,
        new_width.get_value(),
        new_height.get_value(),
        -1,
        nullptr
    );
    gtk_widget_queue_allocate(m_native_handle.widget_handle);
    return;
    gtk_widget_set_size_request(
        m_native_handle.widget_handle,
        new_width.get_value(),
        new_height.get_value()
    );
    gtk_widget_queue_resize(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

pixval
widget::get_preferred_width ()
const noexcept
{
    return 100;
} // function -----------------------------------------------------------------

pixval
widget::get_preferred_height ()
const noexcept
{
    return 25;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
widget::show ()
noexcept
{
    gtk_widget_show(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

void
widget::hide ()
noexcept
{
    gtk_widget_hide(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    widget_native_handle&& widget_handle
)
    : m_native_handle{std::move(widget_handle)}
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
