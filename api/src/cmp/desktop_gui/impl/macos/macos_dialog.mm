// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <AppKit/AppKit.h>

#include <cmp/desktop_gui/impl/common/common_dialog.hpp>

namespace cmp {

namespace impl {

enum class message_box_kind {
    informative,
    warning,
    alert
}; // enum --------------------------------------------------------------------

dialog::button
message_box (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    dialog::button_set buttons,
    message_box_kind kind
)
noexcept
{
    NSString* title_nsstring{
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(title.data())
        ]
    };
    NSString* message_nsstring{
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(message.data())
        ]
    };
    NSAlert* alert{[[NSAlert alloc] init]};
    [alert setMessageText: title_nsstring];
    [alert setInformativeText: message_nsstring];
    switch (kind) {
        case message_box_kind::informative:
            [alert setAlertStyle: NSAlertStyleInformational];
            break;
        case message_box_kind::warning:
            [alert setAlertStyle: NSAlertStyleWarning];
            break;
        case message_box_kind::alert:
            [alert setAlertStyle: NSAlertStyleCritical];
            break;
    }
    switch (buttons) {
        case dialog::button_set::ok:
            [alert addButtonWithTitle: @"OK"];
            switch ([alert runModal]) {
                case NSAlertFirstButtonReturn:
                    return dialog::button::ok;
            }
            break;
        case dialog::button_set::ok_cancel:
            [alert addButtonWithTitle: @"OK"];
            [alert addButtonWithTitle: @"Cancel"];
            switch ([alert runModal]) {
                case NSAlertFirstButtonReturn:
                    return dialog::button::ok;
                case NSAlertSecondButtonReturn:
                    return dialog::button::cancel;
            }
            break;
        case dialog::button_set::yes_no:
            [alert addButtonWithTitle: @"Yes"];
            [alert addButtonWithTitle: @"No"];
            switch ([alert runModal]) {
                case NSAlertFirstButtonReturn:
                    return dialog::button::yes;
                case NSAlertSecondButtonReturn:
                    return dialog::button::no;
            }
            break;
        case dialog::button_set::yes_no_cancel:
            [alert addButtonWithTitle: @"Yes"];
            [alert addButtonWithTitle: @"No"];
            [alert addButtonWithTitle: @"Cancel"];
            switch ([alert runModal]) {
                case NSAlertFirstButtonReturn:
                    return dialog::button::yes;
                case NSAlertSecondButtonReturn:
                    return dialog::button::no;
                case NSAlertThirdButtonReturn:
                    return dialog::button::cancel;
            }
            break;
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::dialog

dialog::button
dialog::inform (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    button_set buttons
)
noexcept
{
    return impl::message_box(
        parent,
        title,
        message,
        buttons,
        impl::message_box_kind::informative
    );
} // function -----------------------------------------------------------------

dialog::button
dialog::warn (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    button_set buttons
)
noexcept
{
    return impl::message_box(
        parent,
        title,
        message,
        buttons,
        impl::message_box_kind::warning
    );
} // function -----------------------------------------------------------------

dialog::button
dialog::alert (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    button_set buttons
)
noexcept
{
    return impl::message_box(
        parent,
        title,
        message,
        buttons,
        impl::message_box_kind::alert
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
