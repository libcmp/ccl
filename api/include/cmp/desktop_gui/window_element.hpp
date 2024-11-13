// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOW_ELEMENT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOW_ELEMENT_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/pixval.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS window_element {
public:
    // Constructors and Destructor --------------------------------------------

    virtual
    ~window_element ()
    = default;

    // Accessors --------------------------------------------------------------

    virtual
    pixval
    get_x ()
    const noexcept = 0;

    virtual
    void
    set_x (
        pixval new_x
    )
    noexcept = 0;

    virtual
    pixval
    get_y ()
    const noexcept = 0;

    virtual
    void
    set_y (
        pixval new_y
    )
    noexcept = 0;

    virtual
    void
    get_position (
        pixval& x,
        pixval& y
    )
    const noexcept = 0;

    virtual
    void
    set_position (
        pixval new_x,
        pixval new_y
    )
    noexcept = 0;

    virtual
    pixval
    get_width ()
    const noexcept = 0;

    virtual
    void
    set_width (
        pixval new_width
    )
    noexcept = 0;

    virtual
    pixval
    get_height ()
    const noexcept = 0;

    virtual
    void
    set_height (
        pixval new_height
    )
    noexcept = 0;

    virtual
    void
    get_size (
        pixval& width,
        pixval& height
    )
    const noexcept = 0;

    virtual
    void
    set_size (
        pixval new_width,
        pixval new_height
    )
    noexcept = 0;

    virtual
    pixval
    get_preferred_width ()
    const noexcept = 0;

    virtual
    pixval
    get_preferred_height ()
    const noexcept = 0;

    virtual
    void
    get_preferred_size (
        pixval& width,
        pixval& height
    )
    const noexcept = 0;

    // Core -------------------------------------------------------------------

    virtual
    void
    show ()
    noexcept = 0;

    virtual
    void
    hide ()
    noexcept = 0;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_WINDOW_ELEMENT_HPP_INCLUDED
