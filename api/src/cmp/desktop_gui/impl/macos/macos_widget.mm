// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_widget.hpp>

@interface cmp_stack_view : NSStackView
- (BOOL)
isFlipped;
@end // interface -------------------------------------------------------------

@interface cmp_box_view : NSView
- (BOOL)
isFlipped;

- (void)
handleAction:
    (NSView*) sender;
@end // interface -------------------------------------------------------------

@interface cmp_text_field_cell : NSTextFieldCell
@end // interface -------------------------------------------------------------

namespace cmp {

namespace impl {

void
forward_action_to_widget (
    NSView* widget_handle
);

widget_native_handle
create_widget (
    NSResponder* parent_handle,
    native_widget_kind kind
)
noexcept
{
    NSView* result;
    if (kind == native_widget_kind::label) {
        result = [NSTextField labelWithString: @""];
    } else if (kind == native_widget_kind::group_box) {
        result = [[NSBox alloc] init];
        [result
            setContentView: [
                [cmp_box_view alloc]
                    initWithFrame: [
                        [result contentView] bounds
                    ]
            ]
        ];
    } else {
        result = [
            [NSButton alloc] initWithFrame:
                NSRect{
                    {
                        0.0,
                        0.0
                    },
                    {
                        100.0,
                        25.0
                    }
                }
        ];
    }
    switch (kind) {
        case native_widget_kind::label:
            break;
        case native_widget_kind::push_button:
            [result setBezelStyle: NSBezelStyleFlexiblePush];
            break;
        case native_widget_kind::check_box:
            [result setButtonType: NSButtonTypeSwitch];
            break;
        case native_widget_kind::radio_button:
            [result setButtonType: NSButtonTypeRadio];
            break;
        case native_widget_kind::group_box:
            break;
    }
    [result setHidden: YES];
    if (kind != native_widget_kind::group_box) {
        if ([parent_handle isKindOfClass:[NSWindow class]]) {
            [result setTarget: reinterpret_cast<NSWindow*>(parent_handle)];
        } else if ([parent_handle isKindOfClass:[NSBox class]]) {
            [result setTarget: reinterpret_cast<NSBox*>(parent_handle).contentView];
        }
        [result setAction: @selector(handleAction:)];
    }
    NSView* parent_content_view{nullptr};
    if ([parent_handle isKindOfClass:[NSWindow class]]) {
        parent_content_view = static_cast<NSWindow*>(parent_handle).contentView;
    } else if ([parent_handle isKindOfClass:[NSBox class]]) {
        parent_content_view = static_cast<NSBox*>(parent_handle).contentView;
    }
    if (kind == native_widget_kind::label) {
        auto nstextfield{static_cast<NSTextField*>(result)};
        [nstextfield setCell: [[cmp_text_field_cell alloc] init]];
        [nstextfield setStringValue: @""];
        [parent_content_view addSubview: result];
    } else if (kind == native_widget_kind::radio_button) {
        result.translatesAutoresizingMaskIntoConstraints = NO;
        cmp_stack_view* containing_view{[[cmp_stack_view alloc] init]};
        containing_view.orientation = NSUserInterfaceLayoutOrientationVertical;
        containing_view.spacing = 0;
        containing_view.translatesAutoresizingMaskIntoConstraints = NO;
        [containing_view addSubview: result];
        [parent_content_view addSubview: containing_view];
        [
            NSLayoutConstraint activateConstraints: @[
                [containing_view.leadingAnchor
                    constraintEqualToAnchor: parent_content_view.leadingAnchor
                    constant: 0
                ],
                [containing_view.topAnchor
                    constraintEqualToAnchor: parent_content_view.topAnchor
                    constant: 0
                ],
                [containing_view.trailingAnchor
                    constraintEqualToAnchor: parent_content_view.trailingAnchor
                    constant: 0
                ],
                [containing_view.bottomAnchor
                    constraintEqualToAnchor: parent_content_view.bottomAnchor
                    constant: 0
                ]
            ]
        ];
    } else {
        [parent_content_view addSubview: result];
    }
    return {parent_handle, result};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    layout& enclosing_layout
)
    : m_native_handle{
          enclosing_layout.grab_enclosing_window_handle().cmp_window_handle,
          nullptr
      }
    , m_enclosing_layout{&enclosing_layout}
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

layout&
widget::grab_enclosing_layout ()
noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

const layout&
widget::grab_enclosing_layout ()
const noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

pixval
widget::get_x ()
const noexcept
{
    return [grab_native_handle().widget_handle frame].origin.x;
} // function -----------------------------------------------------------------

pixval
widget::get_y ()
const noexcept
{
    return [grab_native_handle().widget_handle frame].origin.y;
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

pixval
widget::get_width ()
const noexcept
{
    return [grab_native_handle().widget_handle frame].size.width;
} // function -----------------------------------------------------------------

pixval
widget::get_height ()
const noexcept
{
    return [grab_native_handle().widget_handle frame].size.height;
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

void
widget::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    layout& enclosing_layout,
    widget_native_handle&& widget_handle
)
    : m_native_handle{std::move(widget_handle)}
    , m_enclosing_layout{&enclosing_layout}
{
} // function -----------------------------------------------------------------

void
widget::get_preferred_size_generically (
    const widget_native_handle& native_handle,
    pixval& width,
    pixval& height
)
noexcept
{
    NSSize preferred_size{
        [native_handle.widget_handle fittingSize]
    };
    width = preferred_size.width;
    height = preferred_size.height;
} // function -----------------------------------------------------------------

bool
widget::is_geometry_modification_prohibited ()
const noexcept
{
    return m_enclosing_layout->get_kind() != layout::kind::fixed;
} // function -----------------------------------------------------------------

void
widget::set_x_forcefully (
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

void
widget::set_y_forcefully (
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
widget::set_position_forcefully (
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

void
widget::set_width_forcefully (
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

void
widget::set_height_forcefully (
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
widget::set_size_forcefully (
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

} // namespace ----------------------------------------------------------------

// ------------------------------------------------------------ cmp_stack_view

@implementation cmp_stack_view
- (BOOL)
isFlipped
{
    return YES;
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

// -------------------------------------------------------------- cmp_box_view

@implementation cmp_box_view
- (BOOL)
isFlipped
{
    return YES;
} // function -----------------------------------------------------------------

- (void)
handleAction:
    (NSView*) sender
{
    cmp::impl::forward_action_to_widget(sender);
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

// ------------------------------------------------------- cmp_text_field_cell

@implementation cmp_text_field_cell
- (NSRect)
drawingRectForBounds:
    (NSRect)bounds
{
    NSRect target_rect{[super drawingRectForBounds: bounds]};
    NSSize text_size{[self cellSizeForBounds: bounds]};
    double height_difference{target_rect.size.height - text_size.height};
    if (height_difference > 0) {
        target_rect.origin.y += (height_difference / 2);
    }
    return target_rect;
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------
