// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

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
    NSButton* result{
        [
            [NSButton alloc] initWithFrame:
                NSRect{
                    {
                        0.0,
                        0.0,
                    },
                    {
                        100.0,
                        25.0
                    }
                }
        ]
    };
    switch (kind) {
        case native_widget_kind::push_button:
            [result setBezelStyle: NSBezelStyleFlexiblePush];
            break;
        case native_widget_kind::check_box:
            [result setButtonType: NSButtonTypeSwitch];
            break;
    }
    [result setHidden: YES];
    [
        reinterpret_cast<NSWindow*>(
            parent_window.cmp_window_handle
        ).contentView addSubview:
            result
    ];
    return {parent_window.cmp_window_handle, result};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    const window_native_handle& handle
)
    : m_native_handle{handle.cmp_window_handle, nullptr}
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
    return [grab_native_handle().widget_handle frame].origin.x;
} // function -----------------------------------------------------------------

void
widget::set_x (
    pixval new_x
)
noexcept
{
    [grab_native_handle().widget_handle setFrameOrigin:
        NSPoint{
            static_cast<CGFloat>(new_x.get_value()),
            [grab_native_handle().widget_handle frame].origin.y
        }
    ];
} // function -----------------------------------------------------------------

pixval
widget::get_y ()
const noexcept
{
    return [grab_native_handle().widget_handle frame].origin.y;
} // function -----------------------------------------------------------------

void
widget::set_y (
    pixval new_y
)
noexcept
{
    [grab_native_handle().widget_handle setFrameOrigin:
        NSPoint{
            [grab_native_handle().widget_handle frame].origin.x,
            static_cast<CGFloat>(new_y.get_value()),
        }
    ];
} // function -----------------------------------------------------------------

void
widget::get_position (
    pixval& x,
    pixval& y
)
const noexcept
{
    auto position{[grab_native_handle().widget_handle frame].origin};
    x = position.x;
    y = position.y;
} // function -----------------------------------------------------------------

void
widget::set_position (
    pixval new_x,
    pixval new_y
)
noexcept
{
    [grab_native_handle().widget_handle setFrameOrigin:
        NSPoint {
            static_cast<CGFloat>(new_x.get_value()),
            static_cast<CGFloat>(new_y.get_value()),
        }
    ];
} // function -----------------------------------------------------------------

pixval
widget::get_width ()
const noexcept
{
    return [grab_native_handle().widget_handle frame].size.width;
} // function -----------------------------------------------------------------

void
widget::set_width (
    pixval new_width
)
noexcept
{
    [grab_native_handle().widget_handle setFrameSize:
        NSSize{
            static_cast<CGFloat>(new_width.get_value()),
            [grab_native_handle().widget_handle frame].size.height
        }
    ];
} // function -----------------------------------------------------------------

pixval
widget::get_height ()
const noexcept
{
    return [grab_native_handle().widget_handle frame].size.height;
} // function -----------------------------------------------------------------

void
widget::set_height (
    pixval new_height
)
noexcept
{
    [grab_native_handle().widget_handle setFrameSize:
        NSSize{
            [grab_native_handle().widget_handle frame].size.width,
            static_cast<CGFloat>(new_height.get_value())
        }
    ];
} // function -----------------------------------------------------------------

void
widget::get_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    auto size{[grab_native_handle().widget_handle frame].size};
    width = size.width;
    height = size.height;
} // function -----------------------------------------------------------------

void
widget::set_size (
    pixval new_width,
    pixval new_height
)
noexcept
{
    [grab_native_handle().widget_handle setFrameSize:
        NSSize{
            static_cast<CGFloat>(new_width.get_value()),
            static_cast<CGFloat>(new_height.get_value())
        }
    ];
} // function -----------------------------------------------------------------

pixval
widget::get_preferred_width ()
const noexcept
{
    return 100;
} // function -----------------------------------------------------------------

pixval
widget::get_preferred_height ()
const noexcept
{
    return 25;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
widget::show ()
noexcept
{
    [grab_native_handle().widget_handle setHidden: NO];
} // function -----------------------------------------------------------------

void
widget::hide ()
noexcept
{
    [grab_native_handle().widget_handle setHidden: YES];
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    widget_native_handle&& handle
)
    : m_native_handle{std::move(handle)}
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
