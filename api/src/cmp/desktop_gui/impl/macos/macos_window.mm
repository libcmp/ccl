// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <AppKit/NSWindow.h>

#include <cmp/desktop_gui/impl/macos/macos_window.hpp>

@interface cmp_window : NSWindow
- (void)
keyDown:
(NSEvent*) event;

- (void)
keyUp:
(NSEvent*) event;
@end // interface -------------------------------------------------------------

@interface cmp_window_delegate : NSObject<NSWindowDelegate>
- (void)
windowDidResize:
(NSNotification*) notification;

- (BOOL)
windowShouldClose:
(NSWindow*) sender;
@end // interface -------------------------------------------------------------

namespace cmp {

namespace impl {

key
translate_key_code (
    unsigned short key_code
) {
    switch (key_code) {
        case 122:
            return key::f1;
        case 120:
            return key::f2;
        case 99:
            return key::f3;
        case 118:
            return key::f4;
        case 96:
            return key::f5;
        case 97:
            return key::f6;
        case 98:
            return key::f7;
        case 100:
            return key::f8;
        case 101:
            return key::f9;
        case 109:
            return key::f10;
        case 103:
            return key::f11;
        case 111:
            return key::f12;
        case 105:
            return key::f13;
        case 107:
            return key::f14;
        case 113:
            return key::f15;
        case 106:
            return key::f16;
        case 64:
            return key::f17;
        case 79:
            return key::f18;
        case 80:
            return key::f19;
        case 90:
            return key::f20;
        case 29:
            return key::number_0;
        case 18:
            return key::number_1;
        case 19:
            return key::number_2;
        case 20:
            return key::number_3;
        case 21:
            return key::number_4;
        case 23:
            return key::number_5;
        case 22:
            return key::number_6;
        case 26:
            return key::number_7;
        case 28:
            return key::number_8;
        case 25:
            return key::number_9;
        case 82:
            return key::numpad_0;
        case 83:
            return key::numpad_1;
        case 84:
            return key::numpad_2;
        case 85:
            return key::numpad_3;
        case 86:
            return key::numpad_4;
        case 87:
            return key::numpad_5;
        case 88:
            return key::numpad_6;
        case 89:
            return key::numpad_7;
        case 91:
            return key::numpad_8;
        case 92:
            return key::numpad_9;
        case 0:
            return key::a;
        case 11:
            return key::b;
        case 8:
            return key::c;
        case 2:
            return key::d;
        case 14:
            return key::e;
        case 3:
            return key::f;
        case 5:
            return key::g;
        case 4:
            return key::h;
        case 34:
            return key::i;
        case 38:
            return key::j;
        case 40:
            return key::k;
        case 37:
            return key::l;
        case 46:
            return key::m;
        case 45:
            return key::n;
        case 31:
            return key::o;
        case 35:
            return key::p;
        case 12:
            return key::q;
        case 15:
            return key::r;
        case 1:
            return key::s;
        case 17:
            return key::t;
        case 32:
            return key::u;
        case 9:
            return key::v;
        case 13:
            return key::w;
        case 7:
            return key::x;
        case 16:
            return key::y;
        case 6:
            return key::z;
        case 49:
            return key::space_bar;
        default:
            return key::unknown;
    }
} // function -----------------------------------------------------------------

cmp_window*
as_cmp_window (
    void* cmp_window_ptr
) {
    return static_cast<cmp_window*>(cmp_window_ptr);
} // function -----------------------------------------------------------------

void
forward_key_down_event_to_window (
    cmp_window* cmp_window_ptr,
    NSEvent* event
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == cmp_window_ptr) {
            key_event ev{
                key_event_type::key_down,
                translate_key_code([event keyCode])
            };
            current_association.second->handle_key_down_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_key_up_event_to_window (
    cmp_window* cmp_window_ptr,
    NSEvent* event
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == cmp_window_ptr) {
            key_event ev{
                key_event_type::key_up,
                translate_key_code([event keyCode])
            };
            current_association.second->handle_key_up_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_resize_event_to_window (
    cmp_window* cmp_window_ptr
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == cmp_window_ptr) {
            current_association.second->handle_resize_event();
            break;
        }
    }
} // function -----------------------------------------------------------------

BOOL
forward_close_event_to_window (
    cmp_window* cmp_window_ptr
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (
        auto current_association{std::begin(window_associations)};
        current_association != std::end(window_associations);
        ++current_association
    ) {
        if (current_association->first == cmp_window_ptr) {
            close_event ev{true};
            current_association->second->handle_close_event(ev);
            if (ev.should_close()) {
                window_associations.erase(current_association);
                return YES;
            } else {
                return NO;
            }
        }
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::window

// Constructors and Destructor ------------------------------------------------

window::window (
    int initial_width,
    int initial_height,
    const std::u8string& initial_title,
    window_mode initial_mode
) {
    m_native_handle.cmp_window_handle = nullptr;
    open(initial_width, initial_height, initial_title, initial_mode);
} // function -----------------------------------------------------------------

// Move Operations ------------------------------------------------------------

window::window (
    window&& other
)
noexcept
    : m_native_handle{other.m_native_handle}
    , m_start_time{other.m_start_time}
    , m_last_time{other.m_last_time}
{
    if (m_native_handle.cmp_window_handle != nullptr) {
        fix_association();
    }

    other.m_native_handle.cmp_window_handle = nullptr;
} // function -----------------------------------------------------------------

window&
window::operator = (
    window&& other
)
noexcept
{
    if (this != &other) {
        close();

        m_native_handle = other.m_native_handle;
        m_start_time = other.m_start_time;
        m_last_time = other.m_last_time;

        if (m_native_handle.cmp_window_handle != nullptr) {
            fix_association();
        }

        other.m_native_handle.cmp_window_handle = nullptr;
    }

    return *this;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

window_native_handle&
window::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

const window_native_handle&
window::grab_native_handle ()
const noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

std::u8string
window::get_title ()
const
{
    std::u8string result;
    for (
        const char* current_character{
            [[impl::as_cmp_window(m_native_handle.cmp_window_handle) title]
                UTF8String
            ]
        };
        *current_character != '\0';
        ++current_character
    ) {
        result.push_back(*current_character);
    }
    return result;
} // function -----------------------------------------------------------------

void
window::set_title (
    const std::u8string& new_title
) {
    [impl::as_cmp_window(m_native_handle.cmp_window_handle) setTitle:
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(new_title.data())
        ]
    ];
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

bool
window::open (
    int width,
    int height,
    const std::u8string& title,
    window_mode mode
) {
    if (m_native_handle.cmp_window_handle != nullptr) {
        return false;
    }

    auto& application_native_handle{dgui_app()->grab_native_handle()};

    m_native_handle.cmp_window_handle = [[cmp_window alloc]
        initWithContentRect:
            NSRect{
                {
                    0.0,
                    0.0
                },
                {
                    static_cast<CGFloat>(width),
                    static_cast<CGFloat>(height)
                }
            }
            styleMask:
                NSWindowStyleMaskTitled
                    | NSWindowStyleMaskClosable
                    | NSWindowStyleMaskMiniaturizable
                    | NSWindowStyleMaskResizable
            backing: NSBackingStoreBuffered
            defer: NO
    ];

    cmp_window* w{impl::as_cmp_window(m_native_handle.cmp_window_handle)};

    [w setDelegate: [[cmp_window_delegate alloc] init]];
    [w setTitle:
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(title.data())
        ]
    ];
    [w center];
    if (mode == window_mode::maximized) {
        [w zoom: w];
    }
    else if (mode == window_mode::minimized) {
        [w miniaturize: w];
    }

    m_start_time = std::chrono::steady_clock::now();
    m_last_time = m_start_time;

    application_native_handle.window_associations.emplace_back(
        m_native_handle.cmp_window_handle,
        this
    );

    return true;
} // function -----------------------------------------------------------------

void
window::show ()
{
    if ([impl::as_cmp_window(m_native_handle.cmp_window_handle) isVisible]) {
        return;
    }

    [impl::as_cmp_window(m_native_handle.cmp_window_handle)
        makeKeyAndOrderFront:
            nil
    ];
} // function -----------------------------------------------------------------

void
window::hide ()
{
    [impl::as_cmp_window(m_native_handle.cmp_window_handle) orderOut:
        impl::as_cmp_window(m_native_handle.cmp_window_handle)
    ];
} // function -----------------------------------------------------------------

void
window::close ()
{
    [impl::as_cmp_window(m_native_handle.cmp_window_handle) performClose:
        impl::as_cmp_window(m_native_handle.cmp_window_handle)
    ];
} // function -----------------------------------------------------------------

void
window::update (
    double delta_seconds,
    double total_seconds
) {
} // function -----------------------------------------------------------------

void
window::handle_key_down_event (
    key_event& ev
) {
} // function -----------------------------------------------------------------

void
window::handle_key_up_event (
    key_event& ev
) {
} // function -----------------------------------------------------------------

void
window::handle_resize_event ()
{
} // function -----------------------------------------------------------------

void
window::handle_close_event (
    close_event& ev
) {
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
window::fix_association ()
noexcept
{
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    auto association_iterator{
        std::find_if(
            std::begin(window_associations),
            std::end(window_associations),
            [this] (const auto& element) {
                return element.first == m_native_handle.cmp_window_handle;
            }
        )
    };
    association_iterator->second = this;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// ---------------------------------------------------------------- cmp_window

@implementation cmp_window
- (void)
keyDown:
(NSEvent*) event
{
    cmp::impl::forward_key_down_event_to_window(self, event);
} // function -----------------------------------------------------------------

- (void)
keyUp:
(NSEvent*) event
{
    cmp::impl::forward_key_up_event_to_window(self, event);
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

// ------------------------------------------------------- cmp_window_delegate

@implementation cmp_window_delegate
- (void)
windowDidResize:
(NSNotification*) notification
{
    cmp::impl::forward_resize_event_to_window([notification object]);
} // function -----------------------------------------------------------------

- (BOOL)
windowShouldClose:
(NSWindow*) sender
{
    return cmp::impl::forward_close_event_to_window(
        cmp::impl::as_cmp_window(sender)
    );
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------
