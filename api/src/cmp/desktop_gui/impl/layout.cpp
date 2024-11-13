// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/general.hpp>
#include <cmp/desktop_gui/layout.hpp>

namespace cmp {

// --------------------------------------------------------------- cmp::layout

// Constructors and Destructor ------------------------------------------------

layout::layout (
    layout& parent,
    kind initial_kind,
    axis initial_axis,
    direction initial_direction
)
noexcept
    : m_parent{&parent}
    , m_enclosing_window_handle{parent.m_enclosing_window_handle}
    , m_kind{initial_kind}
    , m_axis{initial_axis}
    , m_direction{initial_direction}
    , m_x{0}
    , m_y{0}
    , m_width{0}
    , m_height{0}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

layout&
layout::grab_parent ()
noexcept
{
    return *m_parent;
} // function -----------------------------------------------------------------

const layout&
layout::grab_parent ()
const noexcept
{
    return *m_parent;
} // function -----------------------------------------------------------------

window_native_handle&
layout::grab_enclosing_window_handle ()
noexcept
{
    return m_enclosing_window_handle;
} // function -----------------------------------------------------------------

const window_native_handle&
layout::grab_enclosing_window_handle ()
const noexcept
{
    return m_enclosing_window_handle;
} // function -----------------------------------------------------------------

std::vector<std::unique_ptr<window_element>>&
layout::grab_children ()
noexcept
{
    return m_children;
} // function -----------------------------------------------------------------

const std::vector<std::unique_ptr<window_element>>&
layout::grab_children ()
const noexcept
{
    return m_children;
} // function -----------------------------------------------------------------

layout::kind
layout::get_kind ()
const noexcept
{
    return m_kind;
} // function -----------------------------------------------------------------

void
layout::set_kind (
    kind new_kind
)
noexcept
{
    if (m_kind != new_kind) {
        m_kind = new_kind;
        update();
    }
} // function -----------------------------------------------------------------

layout::axis
layout::get_axis ()
const noexcept
{
    return m_axis;
} // function -----------------------------------------------------------------

void
layout::set_axis (
    axis new_axis
)
noexcept
{
    if (m_axis != new_axis) {
        m_axis = new_axis;
        update();
    }
} // function -----------------------------------------------------------------

layout::direction
layout::get_direction ()
const noexcept
{
    return m_direction;
} // function -----------------------------------------------------------------

void
layout::set_direction (
    direction new_direction
)
noexcept
{
    if (m_direction != new_direction) {
        m_direction = new_direction;
        if (m_axis == axis::horizontal) {
            update_layout_horizontally();
        } else {
            update_layout_vertically();
        }
    }
} // function -----------------------------------------------------------------

pixval
layout::get_x ()
const noexcept
{
    return m_x;
} // function -----------------------------------------------------------------

void
layout::set_x (
    pixval new_x
)
noexcept
{
    if (m_x != new_x) {
        m_x = new_x;
        update_layout_horizontally();
    }
} // function -----------------------------------------------------------------

pixval
layout::get_y ()
const noexcept
{
    return m_y;
} // function -----------------------------------------------------------------

void
layout::set_y (
    pixval new_y
)
noexcept
{
    if (m_y != new_y) {
        m_y = new_y;
        update_layout_vertically();
    }
} // function -----------------------------------------------------------------

void
layout::get_position (
    pixval& x,
    pixval& y
)
const noexcept
{
    x = m_x;
    y = m_y;
} // function -----------------------------------------------------------------

void
layout::set_position (
    pixval new_x,
    pixval new_y
)
noexcept
{
    set_x(new_x);
    set_y(new_y);
} // function -----------------------------------------------------------------

pixval
layout::get_width ()
const noexcept
{
    return m_width;
} // function -----------------------------------------------------------------

void
layout::set_width (
    pixval new_width
)
noexcept
{
    if (m_width != new_width) {
        m_width = new_width;
        update_layout_horizontally();
    }
} // function -----------------------------------------------------------------

pixval
layout::get_height ()
const noexcept
{
    return m_height;
} // function -----------------------------------------------------------------

void
layout::set_height (
    pixval new_height
)
noexcept
{
    if (m_height != new_height) {
        m_height = new_height;
        update_layout_vertically();
    }
} // function -----------------------------------------------------------------

void
layout::get_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    width = m_width;
    height = m_height;
} // function -----------------------------------------------------------------

void
layout::set_size (
    pixval new_width,
    pixval new_height
)
noexcept
{
    set_width(new_width);
    set_height(new_height);
} // function -----------------------------------------------------------------

pixval
layout::get_preferred_width ()
const noexcept
{
    pixval width{0};
    for (const auto& current_child : m_children) {
        width += current_child->get_preferred_width();
    }
    return width;
} // function -----------------------------------------------------------------

pixval
layout::get_preferred_height ()
const noexcept
{
    pixval height{0};
    for (const auto& current_child : m_children) {
        height += current_child->get_preferred_height();
    }
    return height;
} // function -----------------------------------------------------------------

void
layout::get_preferred_size (
    pixval &width,
    pixval &height
)
const noexcept
{
    width = get_preferred_width();
    height = get_preferred_height();
} // function -----------------------------------------------------------------


bool
layout::is_empty ()
const noexcept
{
    return m_children.empty();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

trusted_ptr<layout>
layout::add_layout (
    kind initial_kind,
    axis initial_axis,
    direction initial_direction
) {
    auto layout_pointer{
        reinterpret_cast<layout*>(
            m_children.emplace_back(
                std::make_unique<layout>(
                    *this,
                    initial_kind,
                    initial_axis,
                    initial_direction
                )
            ).get()
        )
    };
    update();
    return assure(layout_pointer);
} // function -----------------------------------------------------------------

void
layout::show ()
noexcept
{
    for (auto& current_child : m_children) {
        current_child->show();
    }
} // function -----------------------------------------------------------------

void
layout::hide ()
noexcept
{
    for (auto& current_child : m_children) {
        current_child->hide();
    }
} // function -----------------------------------------------------------------

void
layout::update ()
noexcept
{
    update_layout_horizontally();
    update_layout_vertically();
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

layout::layout (
    const window_native_handle& enclosing_window_handle,
    kind initial_kind,
    axis initial_axis,
    direction initial_direction
)
noexcept
    : m_parent{nullptr}
    , m_enclosing_window_handle{enclosing_window_handle}
    , m_kind{initial_kind}
    , m_axis{initial_axis}
    , m_direction{initial_direction}
    , m_x{0}
    , m_y{0}
    , m_width{0}
    , m_height{0}
{
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
layout::update_layout_horizontally ()
noexcept
{
    if (m_kind == kind::fixed || m_children.empty()) {
        return;
    }

    if (m_parent == nullptr) {
        m_x = 0;
    }

    if (m_axis == axis::horizontal) {
        auto equal_share{m_width / m_children.size()};
        pixval current_x{m_x};
        if (m_direction == direction::forward) {
            for (auto& current_child : m_children) {
                current_child->set_width(equal_share);
                current_child->set_x(current_x);
                current_x += equal_share;
            }
        } else {
            for (auto& current_child : std::ranges::reverse_view{m_children}) {
                current_child->set_width(equal_share);
                current_child->set_x(current_x);
                current_x += equal_share;
            }
        }
    } else {
        for (auto& current_child : m_children) {
            current_child->set_width(m_width);
            current_child->set_x(m_x);
        }
    }
} // function -----------------------------------------------------------------

void
layout::update_layout_vertically ()
noexcept
{
    if (m_kind == kind::fixed || m_children.empty()) {
        return;
    }

    if (m_parent == nullptr) {
        m_y = 0;
    }

    if (m_axis == axis::vertical) {
        auto equal_share{m_height / m_children.size()};
        pixval current_y{m_y};
        if (m_direction == direction::forward) {
            for (auto& current_child : m_children) {
                current_child->set_height(equal_share);
                current_child->set_y(current_y);
                current_y += equal_share;
            }
        } else {
            for (auto& current_child : std::ranges::reverse_view{m_children}) {
                current_child->set_height(equal_share);
                current_child->set_y(current_y);
                current_y += equal_share;
            }
        }
    } else {
        for (auto& current_child : m_children) {
            current_child->set_height(m_height);
            current_child->set_y(m_y);
        }
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
