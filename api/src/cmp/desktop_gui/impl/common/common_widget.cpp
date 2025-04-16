// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_widget.hpp>

namespace cmp {

namespace impl {

template <
    typename... Args
>
void
noop (
    Args...
)
noexcept
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Accessors ------------------------------------------------------------------

pixval
widget::get_preferred_width ()
const noexcept
{
    return 0;
} // function -----------------------------------------------------------------

pixval
widget::get_preferred_height ()
const noexcept
{
    return 0;
} // function -----------------------------------------------------------------

void
widget::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    width.set_value(0);
    height.set_value(0);
} // function -----------------------------------------------------------------

void
widget::apply_preferred_size ()
noexcept
{
    pixval preferred_width;
    pixval preferred_height;
    get_preferred_size(preferred_width, preferred_height);
    set_size(preferred_width, preferred_height);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
