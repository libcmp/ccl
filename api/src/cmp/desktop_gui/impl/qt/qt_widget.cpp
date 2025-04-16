// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>

#include <cmp/desktop_gui/impl/common/common_widget.hpp>

namespace cmp {

namespace impl {

widget_native_handle
create_widget (
    QWidget* parent_handle,
    native_widget_kind kind
)
noexcept
{
    QWidget* result;
    switch (kind) {
        case native_widget_kind::label:
            result = new QLabel(parent_handle);
            break;
        case native_widget_kind::push_button:
            result = new QPushButton(parent_handle);
            break;
        case native_widget_kind::check_box:
            result = new QCheckBox(parent_handle);
            break;
        case native_widget_kind::radio_button:
            result = new QRadioButton(parent_handle);
            break;
        case native_widget_kind::group_box:
            result = new QGroupBox(parent_handle);
            break;
    }
    return {parent_handle, result};
} // function -----------------------------------------------------------------

widget*
find_widget (
    QWidget* widget_handle,
    const std::vector<std::unique_ptr<window_element>>& window_elements
) {
    widget* target{nullptr};
    for (const auto& current_window_element : window_elements) {
        auto layout_ptr{dynamic_cast<layout*>(current_window_element.get())};
        if (layout_ptr) {
            target = find_widget(widget_handle, layout_ptr->grab_children());
            if (target) {
                return target;
            }
        } else {
            target = static_cast<widget*>(current_window_element.get());
            if (
                target->grab_native_handle().widget_handle == widget_handle
            ) {
                return target;
            } else {
                auto group_box_ptr{
                    dynamic_cast<group_box*>(current_window_element.get())
                };
                if (group_box_ptr) {
                    target = find_widget(
                        widget_handle,
                        group_box_ptr->grab_content_layout().grab_children()
                    );
                    if (target) {
                        return target;
                    }
                }
            }
        }
    }
    return nullptr;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    layout& enclosing_layout
)
    : m_native_handle{
          enclosing_layout.grab_enclosing_window_handle()
              .cmp_main_window_handle,
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
    return m_native_handle.widget_handle->x();
} // function -----------------------------------------------------------------

pixval
widget::get_y ()
const noexcept
{
    return m_native_handle.widget_handle->y();
} // function -----------------------------------------------------------------

void
widget::get_position (
    pixval& x,
    pixval& y
)
const noexcept
{
    QPoint position{m_native_handle.widget_handle->pos()};
    x = position.x();
    y = position.y();
} // function -----------------------------------------------------------------

pixval
widget::get_width ()
const noexcept
{
    return m_native_handle.widget_handle->width();
} // function -----------------------------------------------------------------

pixval
widget::get_height ()
const noexcept
{
    return m_native_handle.widget_handle->height();
} // function -----------------------------------------------------------------

void
widget::get_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    QSize size{m_native_handle.widget_handle->size()};
    width = size.width();
    height = size.height();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
widget::show ()
noexcept
{
    m_native_handle.widget_handle->show();
} // function -----------------------------------------------------------------

void
widget::hide ()
noexcept
{
    m_native_handle.widget_handle->hide();
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
    QWidget* widget_ptr{m_native_handle.widget_handle};
    return widget_ptr->move(
        new_x.get_value(),
        widget_ptr->y()
    );
} // function -----------------------------------------------------------------

void
widget::set_y_forcefully (
    pixval new_y
)
noexcept
{
    QWidget* widget_ptr{m_native_handle.widget_handle};
    return widget_ptr->move(
        widget_ptr->x(),
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
    QPoint position{new_x.get_value(), new_y.get_value()};
    m_native_handle.widget_handle->move(position.x(), position.y());
} // function -----------------------------------------------------------------

void
widget::set_width_forcefully (
    pixval new_width
)
noexcept
{
    QWidget* widget_ptr{m_native_handle.widget_handle};
    return widget_ptr->resize(
        new_width.get_value(),
        widget_ptr->height()
    );
} // function -----------------------------------------------------------------

void
widget::set_height_forcefully (
    pixval new_height
)
noexcept
{
    QWidget* widget_ptr{m_native_handle.widget_handle};
    return widget_ptr->resize(
        widget_ptr->width(),
        new_height.get_value()
    );
} // function -----------------------------------------------------------------

void
widget::set_size_forcefully (
    pixval new_width,
    pixval new_height
)
noexcept
{
    QSize size{new_width.get_value(), new_height.get_value()};
    m_native_handle.widget_handle->resize(size.width(), size.height());
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
