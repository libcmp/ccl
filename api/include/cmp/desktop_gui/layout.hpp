// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_LAYOUT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_LAYOUT_HPP_INCLUDED

#include <concepts>
#include <vector>
#include <memory>
#include <numeric>
#include <ranges>

#include <cmp/core/trusted_ptr.hpp>
#include <cmp/desktop_gui/window_native_handle.hpp>
#include <cmp/desktop_gui/window_element.hpp>

namespace cmp {

class widget;

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

    CMP_CONDITIONAL_EXPORT
    void
    set_x (
        pixval new_x
    )
    noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_y ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_y (
        pixval new_y
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_position (
        pixval& x,
        pixval& y
    )
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_position (
        pixval new_x,
        pixval new_y
    )
    noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_width ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_width (
        pixval new_width
    )
    noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_height ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_height (
        pixval new_height
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_size (
        pixval& width,
        pixval& height
    )
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_size (
        pixval new_width,
        pixval new_height
    )
    noexcept override;

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
        typename Widget
    >
    requires (std::derived_from<Widget, widget>)
    trusted_ptr<Widget>
    add_widget ();

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

    // Friends ----------------------------------------------------------------

    friend class window;

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
    std::vector<std::unique_ptr<window_element>> m_children;

    // Private Functions ------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    void
    update_layout_horizontally ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    update_layout_vertically ()
    noexcept;
}; // class -------------------------------------------------------------------

using layout_truptr = trusted_ptr<layout>;

} // namespace ----------------------------------------------------------------

#include <cmp/desktop_gui/impl/layout.ipp>

#endif // CMP_DESKTOP_GUI_LAYOUT_HPP_INCLUDED
