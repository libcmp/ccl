// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/layout.hpp>

namespace cmp {

// --------------------------------------------------------------- cmp::layout

// Core -----------------------------------------------------------------------

template <
    typename Widget,
    typename... Arguments
>
requires (std::derived_from<Widget, widget>)
trusted_ptr<Widget>
layout::add_widget (
    Arguments&&... arguments
) {
    auto widget_pointer{
        assure(
            reinterpret_cast<Widget*>(
                m_children.emplace_back(
                    std::make_unique<Widget>(
                        *this,
                        std::forward<Arguments>(arguments)...
                    )
                ).get()
            )
        )
    };
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
    update();
#endif
    return widget_pointer;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
