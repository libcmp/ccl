// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_widget.hpp>

namespace cmp {

namespace impl {

widget_native_handle
create_widget (
    GtkWidget* parent_handle,
    native_widget_kind kind
)
noexcept
{
    GtkWidget* result;
    switch (kind) {
        case native_widget_kind::label:
            result = gtk_label_new("");
            break;
        case native_widget_kind::push_button:
            result = gtk_button_new();
            break;
        case native_widget_kind::check_box:
            result = gtk_check_button_new();
            break;
        case native_widget_kind::radio_button:
            result = gtk_check_button_new();
            break;
        case native_widget_kind::group_box:
            result = gtk_frame_new("");
            break;
    }
    gtk_widget_set_visible(result, false);
    gtk_widget_set_hexpand(result, true);
    gtk_widget_set_vexpand(result, true);
    if (GTK_IS_FRAME(parent_handle)) {
        parent_handle = gtk_frame_get_child(GTK_FRAME(parent_handle));
    }
    if (GTK_IS_BOX(parent_handle)) {
        gtk_box_append(GTK_BOX(parent_handle), result);
    } else {
        gtk_fixed_put(
            GTK_FIXED(parent_handle),
            result,
            0.0,
            0.0
        );
    }
    return {parent_handle, result};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    layout& enclosing_layout
)
    : m_native_handle{
          enclosing_layout.grab_enclosing_window_handle()
              .gtk_application_window,
          nullptr
      }
    , m_enclosing_layout{&enclosing_layout}
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

layout&
widget::grab_enclosing_layout ()
noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

const layout&
widget::grab_enclosing_layout ()
const noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

pixval
widget::get_x ()
const noexcept
{
    double current_x;
    double current_y;
    gtk_fixed_get_child_position(
        GTK_FIXED(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        &current_x,
        &current_y
    );
    return current_x;
} // function -----------------------------------------------------------------

pixval
widget::get_y ()
const noexcept
{
    double current_x;
    double current_y;
    gtk_fixed_get_child_position(
        GTK_FIXED(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        &current_x,
        &current_y
    );
    return current_y;
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
        GTK_FIXED(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        &current_x,
        &current_y
    );
    x.set_value(current_x);
    y.set_value(current_y);
} // function -----------------------------------------------------------------

pixval
widget::get_width ()
const noexcept
{
    return gtk_widget_get_size(
        m_native_handle.widget_handle,
        GTK_ORIENTATION_HORIZONTAL
    );
} // function -----------------------------------------------------------------

pixval
widget::get_height ()
const noexcept
{
    return gtk_widget_get_size(
        m_native_handle.widget_handle,
        GTK_ORIENTATION_VERTICAL
    );
} // function -----------------------------------------------------------------

void
widget::get_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    width.set_value(
        gtk_widget_get_size(
            m_native_handle.widget_handle,
            GTK_ORIENTATION_HORIZONTAL
        )
    );
    height.set_value(
        gtk_widget_get_size(
            m_native_handle.widget_handle,
            GTK_ORIENTATION_VERTICAL
        )
    );
} // function -----------------------------------------------------------------

void
widget::get_preferred_size_generically (
    const widget_native_handle& native_handle,
    pixval& width,
    pixval& height
)
noexcept
{
    GtkRequisition minimum_size;
    GtkRequisition natural_size;
    gtk_widget_get_preferred_size(
        native_handle.widget_handle,
        &minimum_size,
        &natural_size
    );
    width = std::max<int>(minimum_size.width, natural_size.width);
    height = std::max<int>(minimum_size.height, natural_size.height);
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

void
widget::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    layout& enclosing_layout,
    widget_native_handle&& widget_handle
)
    : m_native_handle{std::move(widget_handle)}
    , m_enclosing_layout{&enclosing_layout}
{
} // function -----------------------------------------------------------------

bool
widget::is_geometry_modification_prohibited ()
const noexcept
{
    return m_enclosing_layout->get_kind() != layout::kind::fixed;
} // function -----------------------------------------------------------------

void
widget::set_x_forcefully (
    pixval new_x
)
noexcept
{
    gtk_fixed_move(
        GTK_FIXED(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        new_x.get_value(),
        get_y().get_value()
    );
} // function -----------------------------------------------------------------

void
widget::set_y_forcefully (
    pixval new_y
)
noexcept
{
    gtk_fixed_move(
        GTK_FIXED(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        get_x().get_value(),
        new_y.get_value()
    );
} // function -----------------------------------------------------------------

void
widget::set_position_forcefully (
    pixval new_x,
    pixval new_y
)
noexcept
{
    gtk_fixed_move(
        GTK_FIXED(m_native_handle.parent_handle),
        m_native_handle.widget_handle,
        new_x.get_value(),
        new_y.get_value()
    );
} // function -----------------------------------------------------------------

void
widget::set_width_forcefully (
    pixval new_width
)
noexcept
{
    /*
    gtk_widget_allocate(
        m_native_handle.widget_handle,
        new_width.get_value(),
        get_height().get_value(),
        -1,
        nullptr
    );
    gtk_widget_queue_allocate(m_native_handle.widget_handle);
    return;
    */
    gtk_widget_set_size_request(
        m_native_handle.widget_handle,
        new_width.get_value(),
        get_height().get_value()
    );
    // gtk_widget_queue_resize(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

void
widget::set_height_forcefully (
    pixval new_height
)
noexcept
{
    /*
    gtk_widget_allocate(
        m_native_handle.widget_handle,
        get_width().get_value(),
        new_height.get_value(),
        -1,
        nullptr
    );
    gtk_widget_queue_allocate(m_native_handle.widget_handle);
    return;
    */
    gtk_widget_set_size_request(
        m_native_handle.widget_handle,
        get_width().get_value(),
        new_height.get_value()
    );
    // gtk_widget_queue_resize(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

void
widget::set_size_forcefully (
    pixval new_width,
    pixval new_height
)
noexcept
{
    /*
    gtk_widget_allocate(
        m_native_handle.widget_handle,
        new_width.get_value(),
        new_height.get_value(),
        -1,
        nullptr
    );
    gtk_widget_queue_allocate(m_native_handle.widget_handle);
    return;
    */
    gtk_widget_set_size_request(
        m_native_handle.widget_handle,
        new_width.get_value(),
        new_height.get_value()
    );
//    gtk_widget_queue_resize(m_native_handle.widget_handle);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
