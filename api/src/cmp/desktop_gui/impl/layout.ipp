// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/layout.hpp>

namespace cmp {

// --------------------------------------------------------------- cmp::layout

// Core -----------------------------------------------------------------------

template <
    typename Widget
>
requires (std::derived_from<Widget, widget>)
trusted_ptr<Widget>
layout::add_widget ()
{
    auto widget_pointer{
        reinterpret_cast<Widget*>(
            m_children.emplace_back(
                std::make_unique<Widget>(
                    m_enclosing_window_handle
                )
            ).get()
        )
    };
    update();
    return assure(widget_pointer);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
