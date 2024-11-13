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
    const window_native_handle& parent_window,
    native_widget_kind kind
)
noexcept
{
    QWidget* result;
    switch (kind) {
        case native_widget_kind::label:
            result = new QLabel(parent_window.cmp_main_window_handle);
            break;
        case native_widget_kind::push_button:
            result = new QPushButton(parent_window.cmp_main_window_handle);
            break;
        case native_widget_kind::check_box:
            result = new QCheckBox(parent_window.cmp_main_window_handle);
            break;
        case native_widget_kind::radio_button:
            result = new QRadioButton(parent_window.cmp_main_window_handle);
            break;
        case native_widget_kind::group_box:
            result = new QGroupBox(parent_window.cmp_main_window_handle);
            break;
    }
    return {parent_window.cmp_main_window_handle, result};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    const window_native_handle& handle
)
    : m_native_handle{handle.cmp_main_window_handle, nullptr}
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
    return m_native_handle.widget_handle->x();
} // function -----------------------------------------------------------------

void
widget::set_x (
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

pixval
widget::get_y ()
const noexcept
{
    return m_native_handle.widget_handle->y();
} // function -----------------------------------------------------------------

void
widget::set_y (
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

void
widget::set_position (
    pixval new_x,
    pixval new_y
)
noexcept
{
    QPoint position{new_x.get_value(), new_y.get_value()};
    m_native_handle.widget_handle->move(position.x(), position.y());
} // function -----------------------------------------------------------------

pixval
widget::get_width ()
const noexcept
{
    return m_native_handle.widget_handle->width();
} // function -----------------------------------------------------------------

void
widget::set_width (
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

pixval
widget::get_height ()
const noexcept
{
    return m_native_handle.widget_handle->height();
} // function -----------------------------------------------------------------

void
widget::set_height (
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

void
widget::set_size (
    pixval new_width,
    pixval new_height
)
noexcept
{
    QSize size{new_width.get_value(), new_height.get_value()};
    m_native_handle.widget_handle->resize(size.width(), size.height());
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

// Protected Functions --------------------------------------------------------

widget::widget (
    widget_native_handle&& widget_handle
)
    : m_native_handle{std::move(widget_handle)}
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
