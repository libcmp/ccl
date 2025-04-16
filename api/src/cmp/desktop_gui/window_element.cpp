// Copyright (C) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/window_element.hpp>
#include <cmp/io/uio.hpp>
namespace cmp {

// ------------------------------------------------------- cmp::window_element

// Constructors and Destructor ------------------------------------------------

window_element::window_element ()
noexcept
    : m_is_dynamically_sized{true}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

void
window_element::set_x (
    pixval new_x
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_x_forcefully(new_x);
} // function -----------------------------------------------------------------

void
window_element::set_y (
    pixval new_y
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_y_forcefully(new_y);
} // function -----------------------------------------------------------------

void
window_element::set_position (
    pixval new_x,
    pixval new_y
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_position_forcefully(new_x, new_y);
} // function -----------------------------------------------------------------

void
window_element::set_width (
    pixval new_width
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_width_forcefully(new_width);
} // function -----------------------------------------------------------------

void
window_element::set_height (
    pixval new_height
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_height_forcefully(new_height);
} // function -----------------------------------------------------------------

void
window_element::set_size (
    pixval new_width,
    pixval new_height
)
noexcept
{
    if (is_geometry_modification_prohibited()) {
        return;
    }
    set_size_forcefully(new_width, new_height);
} // function -----------------------------------------------------------------

bool
window_element::is_dynamically_sized ()
const noexcept
{
    return m_is_dynamically_sized;
} // function -----------------------------------------------------------------

void
window_element::set_dynamically_sized (
    bool new_dynamically_sized
)
noexcept
{
    m_is_dynamically_sized = new_dynamically_sized;
    if (m_is_dynamically_sized) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
window_element::apply_preferred_size ()
noexcept
{
    pixval preferred_width;
    pixval preferred_height;
    get_preferred_size(preferred_width, preferred_height);
    set_size(preferred_width, preferred_height);
} // function -----------------------------------------------------------------

void
window_element::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
