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
    , m_left_margin{0}
    , m_top_margin{0}
    , m_right_margin{0}
    , m_bottom_margin{0}
    , m_native_handle{}
{
#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
    initialize_gtk(
        m_kind,
        m_axis,
        m_direction,
        m_left_margin,
        m_top_margin,
        m_right_margin,
        m_bottom_margin
    );
#endif
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

layout::native_handle&
layout::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

const layout::native_handle&
layout::grab_native_handle ()
const noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

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
#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
        change_kind_gtk(new_kind);
#else
        m_kind = new_kind;
        update();
#endif
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
#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
        change_axis_gtk(new_axis);
#else
        m_axis = new_axis;
        update();
#endif
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
#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
        change_direction_gtk(new_direction);
#else
        m_direction = new_direction;
        if (m_axis == axis::horizontal) {
            update_layout_horizontally();
        } else {
            update_layout_vertically();
        }
#endif
    }
} // function -----------------------------------------------------------------

pixval
layout::get_x ()
const noexcept
{
    return m_x;
} // function -----------------------------------------------------------------

pixval
layout::get_y ()
const noexcept
{
    return m_y;
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

pixval
layout::get_width ()
const noexcept
{
    return m_width;
} // function -----------------------------------------------------------------

pixval
layout::get_height ()
const noexcept
{
    return m_height;
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

pixval
layout::get_preferred_width ()
const noexcept
{
    if (m_axis == axis::vertical) {
        pixval width{0};
        for (const auto& current_child : m_children) {
            width = std::max<int>(
                width.get_value(),
                current_child->get_preferred_width().get_value()
            );
        }
        width += m_left_margin + m_right_margin;
        return width;
    } else {
        pixval width{m_left_margin + m_right_margin};
        for (const auto& current_child : m_children) {
            width += current_child->get_preferred_width();
        }
        return width;
    }
} // function -----------------------------------------------------------------

pixval
layout::get_preferred_height ()
const noexcept
{
    if (m_axis == axis::vertical) {
        pixval height{m_top_margin + m_bottom_margin};
        for (const auto& current_child : m_children) {
            height += current_child->get_preferred_height();
        }
        return height;
    } else {
        pixval height{0};
        for (const auto& current_child : m_children) {
            height = std::max<int>(
                height.get_value(),
                current_child->get_preferred_height().get_value()
            );
        }
        height += m_top_margin + m_bottom_margin;
        return height;
    }
} // function -----------------------------------------------------------------

void
layout::get_preferred_size (
    pixval& width,
    pixval& height
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
        assure(
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
        )
    };
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
    update();
#endif
    return layout_pointer;
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

void
layout::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
    for (auto& current_child : m_children) {
        current_child->handle_dpi_update_event(old_dpi, new_dpi);
    }
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
    , m_left_margin{0}
    , m_top_margin{0}
    , m_right_margin{0}
    , m_bottom_margin{0}
    , m_native_handle{}
{
#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
    initialize_gtk(
        m_kind,
        m_axis,
        m_direction,
        m_left_margin,
        m_top_margin,
        m_right_margin,
        m_bottom_margin
    );
#endif
} // function -----------------------------------------------------------------

bool
layout::is_geometry_modification_prohibited ()
const noexcept
{
    if (m_parent) {
        return m_parent->m_kind != layout::kind::fixed;
    }
    return false;
} // function -----------------------------------------------------------------

void
layout::set_x_forcefully (
    pixval new_x
)
noexcept
{
    if (m_x != new_x) {
        pixval delta_x{new_x - m_x};
        for (auto& current_child : m_children) {
            current_child->set_x_forcefully(current_child->get_x() + delta_x);
        }
        m_x = new_x;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_horizontally();
#endif
    }
} // function -----------------------------------------------------------------

void
layout::set_y_forcefully (
    pixval new_y
)
noexcept
{
    if (m_y != new_y) {
        pixval delta_y{new_y - m_y};
        for (auto& current_child : m_children) {
            current_child->set_y_forcefully(current_child->get_y() + delta_y);
        }
        m_y = new_y;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_vertically();
#endif
    }
} // function -----------------------------------------------------------------

void
layout::set_position_forcefully (
    pixval new_x,
    pixval new_y
)
noexcept
{
    set_x_forcefully(new_x);
    set_y_forcefully(new_y);
} // function -----------------------------------------------------------------

void
layout::set_width_forcefully (
    pixval new_width
)
noexcept
{
    if (m_width != new_width) {
        m_width = new_width;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_horizontally();
#endif
    }
} // function -----------------------------------------------------------------

void
layout::set_height_forcefully (
    pixval new_height
)
noexcept
{
    if (m_height != new_height) {
        m_height = new_height;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_vertically();
#endif
    }
} // function -----------------------------------------------------------------

void
layout::set_size_forcefully (
    pixval new_width,
    pixval new_height
)
noexcept
{
    set_width_forcefully(new_width);
    set_height_forcefully(new_height);
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

pixval
layout::get_left_margin ()
const noexcept
{
    return m_left_margin;
} // function -----------------------------------------------------------------

void
layout::set_left_margin (
    pixval new_left_margin
)
noexcept
{
    if (m_left_margin != new_left_margin) {
        m_left_margin = new_left_margin;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_horizontally();
#endif
    }
} // function -----------------------------------------------------------------

pixval
layout::get_top_margin ()
const noexcept
{
    return m_top_margin;
} // function -----------------------------------------------------------------

void
layout::set_top_margin (
    pixval new_top_margin
)
noexcept
{
    if (m_top_margin != new_top_margin) {
        m_top_margin = new_top_margin;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_vertically();
#endif
    }
} // function -----------------------------------------------------------------

pixval
layout::get_right_margin ()
const noexcept
{
    return m_right_margin;
} // function -----------------------------------------------------------------

void
layout::set_right_margin (
    pixval new_right_margin
)
noexcept
{
    if (m_right_margin != new_right_margin) {
        m_right_margin = new_right_margin;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_horizontally();
#endif
    }
} // function -----------------------------------------------------------------

pixval
layout::get_bottom_margin ()
const noexcept
{
    return m_bottom_margin;
} // function -----------------------------------------------------------------

void
layout::set_bottom_margin (
    pixval new_bottom_margin
)
noexcept
{
    if (m_bottom_margin != new_bottom_margin) {
        m_bottom_margin = new_bottom_margin;
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        update_layout_vertically();
#endif
    }
} // function -----------------------------------------------------------------

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
        const pixval equal_share{
            std::max<pixval>(
                0,
                (m_width - m_left_margin - m_right_margin) / m_children.size()
            )
        };
        pixval current_x{m_x + m_left_margin};
        if (m_direction == direction::forward) {
            for (auto& current_child : m_children) {
                current_child->set_width_forcefully(equal_share);
                current_child->set_x_forcefully(current_x);
                current_x += equal_share;
            }
        } else {
            for (auto& current_child : std::ranges::reverse_view{m_children}) {
                current_child->set_width_forcefully(equal_share);
                current_child->set_x_forcefully(current_x);
                current_x += equal_share;
            }
        }
    } else {
        const pixval width{
            std::max<pixval>(0, m_width - m_left_margin - m_right_margin)
        };
        const pixval x{m_x + m_left_margin};
        for (auto& current_child : m_children) {
            current_child->set_width_forcefully(width);
            current_child->set_x_forcefully(x);
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
        const pixval equal_share{
            std::max<pixval>(
                0,
                (m_height - m_top_margin - m_bottom_margin) / m_children.size()
            )
        };
        pixval current_y{m_y + m_top_margin};
        if (m_direction == direction::forward) {
            for (auto& current_child : m_children) {
                current_child->set_height_forcefully(equal_share);
                current_child->set_y_forcefully(current_y);
                current_y += equal_share;
            }
        } else {
            for (auto& current_child : std::ranges::reverse_view{m_children}) {
                current_child->set_height_forcefully(equal_share);
                current_child->set_y_forcefully(current_y);
                current_y += equal_share;
            }
        }
    } else {
        const pixval height{
            std::max<pixval>(0, m_height - m_top_margin - m_bottom_margin)
        };
        const pixval y{m_y + m_top_margin};
        for (auto& current_child : m_children) {
            current_child->set_height_forcefully(height);
            current_child->set_y_forcefully(y);
        }
    }
} // function -----------------------------------------------------------------

#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
void
layout::initialize_gtk (
    kind initial_kind,
    axis initial_axis,
    direction initial_direction,
    pixval initial_left_margin,
    pixval initial_top_margin,
    pixval initial_right_margin,
    pixval initial_bottom_margin
) {
    m_kind = initial_kind;
    m_axis = initial_axis;
    m_direction = initial_direction;
    m_left_margin = initial_left_margin;
    m_top_margin = initial_top_margin;
    m_right_margin = initial_right_margin;
    m_bottom_margin = initial_bottom_margin;

    if (m_kind == kind::flow) {
        m_native_handle.gtk_layout = gtk_box_new(
            m_axis == axis::horizontal
                ? GTK_ORIENTATION_HORIZONTAL
                : GTK_ORIENTATION_VERTICAL,
            0
        );
        for (const auto& current_child : m_children) {
            GtkWidget* current_child_native_handle;
            auto layout_ptr{dynamic_cast<layout*>(current_child.get())};
            if (layout_ptr) {
                current_child_native_handle
                    = layout_ptr->grab_native_handle().gtk_layout;
            } else {
                auto widget_ptr{
                    static_cast<widget*>(current_child.get())
                };
                current_child_native_handle
                    = widget_ptr->grab_native_handle().widget_handle;
            }
            if (m_direction == direction::forward) {
                gtk_box_append(
                    GTK_BOX(m_native_handle.gtk_layout),
                    current_child_native_handle
                );
            } else {
                gtk_box_prepend(
                    GTK_BOX(m_native_handle.gtk_layout),
                    current_child_native_handle
                );
            }
        }
    } else {
        m_native_handle.gtk_layout = gtk_fixed_new();
    }

    if (m_parent == nullptr) {
        return;
    }
    if (m_parent->m_kind == kind::flow) {
        if (m_parent->m_direction == direction::forward) {
            gtk_box_append(
                GTK_BOX(m_parent->m_native_handle.gtk_layout),
                m_native_handle.gtk_layout
            );
        } else {
            gtk_box_prepend(
                GTK_BOX(m_parent->m_native_handle.gtk_layout),
                m_native_handle.gtk_layout
            );
        }
    }
} // function -----------------------------------------------------------------

void
layout::change_kind_gtk (
    kind new_kind
) {
    m_kind = new_kind;

    GtkWidget* new_layout;
    if (m_kind == kind::flow) {
        new_layout = gtk_box_new(
            m_axis == axis::horizontal
                ? GTK_ORIENTATION_HORIZONTAL
                : GTK_ORIENTATION_VERTICAL,
            0
        );
    } else {
        new_layout = gtk_fixed_new();
    }

    GtkWidget* child;
    for (auto& current_child : m_children) {
        auto layout_ptr{dynamic_cast<layout*>(current_child.get())};
        if (layout_ptr) {
            child = layout_ptr->grab_native_handle().gtk_layout;
        } else {
            auto widget_ptr{static_cast<widget*>(current_child.get())};
            child = widget_ptr->grab_native_handle().widget_handle;
        }

        GtkAllocation allocation;
        gtk_widget_get_allocation(child, &allocation);

        g_object_ref(child);
        if (m_kind == kind::flow) {
            /*
                We are going from a fixed layout to a flow layout, so
                we remove the element in the existing fixed layout.
            */
            gtk_fixed_remove(GTK_FIXED(m_native_handle.gtk_layout), child);
        } else {
            /*
                We are going from a flow layout to a fixed layout, so
                we remove the element in the existing flow layout.
            */
            gtk_box_remove(GTK_BOX(m_native_handle.gtk_layout), child);
        }

        if (m_kind == kind::flow) {
            if (m_direction == direction::forward) {
                gtk_box_append(
                    GTK_BOX(new_layout),
                    child
                );
            } else {
                gtk_box_prepend(
                    GTK_BOX(new_layout),
                    child
                );
            }
        } else {
            gtk_fixed_put(
                GTK_FIXED(new_layout),
                child,
                allocation.x,
                allocation.y
            );
        }
        g_object_unref(child);
    }
    GtkWidget* parent{gtk_widget_get_parent(m_native_handle.gtk_layout)};
    gtk_window_set_child(
        GTK_WINDOW(parent),
        nullptr
    );
    m_native_handle.gtk_layout = new_layout;
    gtk_window_set_child(
        GTK_WINDOW(parent),
        m_native_handle.gtk_layout
    );
} // function -----------------------------------------------------------------

void
layout::change_axis_gtk (
    axis new_axis
) {
    m_axis = new_axis;
    if (m_kind == kind::fixed) {
        return;
    }
    if (new_axis == axis::horizontal) {
        gtk_orientable_set_orientation(
            GTK_ORIENTABLE(m_native_handle.gtk_layout),
            GTK_ORIENTATION_HORIZONTAL
        );
    } else {
        gtk_orientable_set_orientation(
            GTK_ORIENTABLE(m_native_handle.gtk_layout),
            GTK_ORIENTATION_VERTICAL
        );
    }
} // function -----------------------------------------------------------------

void
layout::change_direction_gtk (
    direction new_direction
) {
    m_direction = new_direction;
    if (m_kind == kind::fixed) {
        return;
    }
    GtkWidget* box{
        gtk_box_new(
            m_axis == axis::horizontal
                ? GTK_ORIENTATION_HORIZONTAL
                : GTK_ORIENTATION_VERTICAL,
            0
        )
    };
    GtkWidget* child;
    for (auto& current_child : m_children) {
        auto layout_ptr{dynamic_cast<layout*>(current_child.get())};
        if (layout_ptr) {
            child = layout_ptr->grab_native_handle().gtk_layout;
        } else {
            auto widget_ptr{static_cast<widget*>(current_child.get())};
            child = widget_ptr->grab_native_handle().widget_handle;
        }

        g_object_ref(child);
        gtk_box_remove(GTK_BOX(m_native_handle.gtk_layout), child);

        if (m_direction == direction::forward) {
            gtk_box_append(
                GTK_BOX(box),
                child
            );
        } else {
            gtk_box_prepend(
                GTK_BOX(box),
                child
            );
        }
        g_object_unref(child);
    }
    GtkWidget* window{
        grab_enclosing_window_handle().gtk_application_window
    };
    gtk_window_set_child(
        GTK_WINDOW(window),
        nullptr
    );
    m_native_handle.gtk_layout = box;
    gtk_window_set_child(
        GTK_WINDOW(window),
        m_native_handle.gtk_layout
    );
} // function -----------------------------------------------------------------
#endif

} // namespace ----------------------------------------------------------------
