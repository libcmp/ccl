// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_LAYOUT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_LAYOUT_HPP_INCLUDED

#include <concepts>
#include <vector>
#include <memory>
#include <numeric>
#include <ranges>
#include <algorithm>

#include <cmp/core/trusted_ptr.hpp>
#include <cmp/desktop_gui/window_native_handle.hpp>
#include <cmp/desktop_gui/window_element.hpp>

namespace cmp {

class widget;
class group_box;

class CMP_CONDITIONAL_EXPORT_CLASS layout
    : public window_element
{
public:
    // Types ------------------------------------------------------------------

    enum class kind {
        fixed,
        flow
    }; // enum ----------------------------------------------------------------

    enum class axis {
        horizontal,
        vertical
    }; // enum ----------------------------------------------------------------

    enum class direction {
        forward,
        reverse
    }; // enum ----------------------------------------------------------------

#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
    struct native_handle {
        GtkWidget* gtk_layout;
    };
#else
    struct native_handle {
    };
#endif

    // Constructors and Destructor --------------------------------------------

    layout ()
    noexcept = default;

    CMP_CONDITIONAL_EXPORT
    layout (
        layout& parent,
        kind initial_kind,
        axis initial_axis,
        direction initial_direction
    )
    noexcept;

    ~layout ()
    override = default;

    // Copy Operations --------------------------------------------------------

    layout (
        const layout& other
    )
    = default;

    layout&
    operator = (
        const layout& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    layout (
        layout&& other
    )
    noexcept = default;

    layout&
    operator = (
        layout&& other
    ) &
    noexcept = default;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    native_handle&
    grab_native_handle ()
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const native_handle&
    grab_native_handle ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    layout&
    grab_parent ()
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const layout&
    grab_parent ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    window_native_handle&
    grab_enclosing_window_handle ()
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const window_native_handle&
    grab_enclosing_window_handle ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    std::vector<std::unique_ptr<window_element>>&
    grab_children ()
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const std::vector<std::unique_ptr<window_element>>&
    grab_children ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    kind
    get_kind ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_kind (
        kind new_kind
    )
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    axis
    get_axis ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_axis (
        axis new_axis
    )
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    direction
    get_direction ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_direction (
        direction new_direction
    )
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_x ()
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_y ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_position (
        pixval& x,
        pixval& y
    )
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_width ()
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_height ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_size (
        pixval& width,
        pixval& height
    )
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_preferred_width ()
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_preferred_height ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_preferred_size (
        pixval& width,
        pixval& height
    )
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    bool
    is_empty ()
    const noexcept;

    // Core -------------------------------------------------------------------

    template <
        typename Widget,
        typename... Arguments
    >
    requires (std::derived_from<Widget, widget>)
    trusted_ptr<Widget>
    add_widget (
        Arguments&&... arguments
    );

    CMP_CONDITIONAL_EXPORT
    trusted_ptr<layout>
    add_layout (
        kind initial_kind,
        axis initial_axis,
        direction initial_direction
    );

    CMP_CONDITIONAL_EXPORT
    void
    show ()
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    hide ()
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    update ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    handle_dpi_update_event (
        int old_dpi,
        int new_dpi
    )
    override;

    // Friends ----------------------------------------------------------------

    friend class window;
    friend class group_box;

protected:
    // Protected Functions ----------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    layout (
        const window_native_handle& enclosing_window_handle,
        kind initial_kind,
        axis initial_axis,
        direction initial_direction
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    bool
    is_geometry_modification_prohibited ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_x_forcefully (
        pixval new_x
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_y_forcefully (
        pixval new_y
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_position_forcefully (
        pixval new_x,
        pixval new_y
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_width_forcefully (
        pixval new_width
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_height_forcefully (
        pixval new_height
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_size_forcefully (
        pixval new_width,
        pixval new_height
    )
    noexcept override;

private:
    // Private Data -----------------------------------------------------------

    layout* m_parent;
    window_native_handle m_enclosing_window_handle;
    kind m_kind;
    axis m_axis;
    direction m_direction;
    pixval m_x;
    pixval m_y;
    pixval m_width;
    pixval m_height;
    pixval m_left_margin;
    pixval m_top_margin;
    pixval m_right_margin;
    pixval m_bottom_margin;
    std::vector<std::unique_ptr<window_element>> m_children;
    native_handle m_native_handle;

    // Private Functions ------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    pixval
    get_left_margin ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_left_margin (
        pixval new_left_margin
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_top_margin ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_top_margin (
        pixval new_top_margin
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_right_margin ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_right_margin (
        pixval new_right_margin
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_bottom_margin ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_bottom_margin (
        pixval new_bottom_margin
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    update_layout_horizontally ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    update_layout_vertically ()
    noexcept;

#if (defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)) && CMP_CONFIG_USE_GTK == true
    CMP_CONDITIONAL_EXPORT
    void
    initialize_gtk (
        kind initial_kind,
        axis initial_axis,
        direction initial_direction,
        pixval initial_left_margin,
        pixval initial_top_margin,
        pixval initial_right_margin,
        pixval initial_bottom_margin
    );

    CMP_CONDITIONAL_EXPORT
    void
    change_kind_gtk (
        kind new_kind
    );

    CMP_CONDITIONAL_EXPORT
    void
    change_axis_gtk (
        axis new_axis
    );

    CMP_CONDITIONAL_EXPORT
    void
    change_direction_gtk (
        direction new_direction
    );
#endif
}; // class -------------------------------------------------------------------

using layout_truptr = trusted_ptr<layout>;

} // namespace ----------------------------------------------------------------

#include <cmp/desktop_gui/impl/layout.ipp>

#endif // CMP_DESKTOP_GUI_LAYOUT_HPP_INCLUDED
