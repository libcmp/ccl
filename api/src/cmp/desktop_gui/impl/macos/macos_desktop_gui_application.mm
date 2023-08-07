// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <AppKit/NSApplication.h>

#include <cmp/desktop_gui/impl/macos/macos_desktop_gui_application.hpp>

@interface cmp_application_delegate : NSObject<NSApplicationDelegate>
- (void)
applicationWillFinishLaunching:
(NSNotification*) notification;

- (void)
applicationDidFinishLaunching:
(NSNotification*) notification;

- (BOOL)
applicationShouldTerminateAfterLastWindowClosed:
(NSApplication*) sender;
@end // interface -------------------------------------------------------------

// -------------------------------------------------- cmp_application_delegate

@implementation cmp_application_delegate
- (void)
applicationWillFinishLaunching:
(NSNotification*) notification
{
    [[notification object] setActivationPolicy:
        NSApplicationActivationPolicyRegular
    ];
} // function -----------------------------------------------------------------

- (void)
applicationDidFinishLaunching:
(NSNotification*) notification
{
    [[notification object] activateIgnoringOtherApps: YES];
} // function -----------------------------------------------------------------

- (BOOL)
applicationShouldTerminateAfterLastWindowClosed:
(NSApplication*) sender
{
    return NO;
} // function -----------------------------------------------------------------
@end // implementation --------------------------------------------------------

namespace cmp {

namespace impl {

NSApplication*
as_nsapplication (
    void* application
) {
    return static_cast<NSApplication*>(application);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// ---------------------------------------------- cmp::desktop_gui_application

// Constructors and Destructor ------------------------------------------------

desktop_gui_application::desktop_gui_application (
    int argc,
    char** argv
)
    : application{argc, argv}
    , m_shared_application{[NSApplication sharedApplication]}
{
    set_instance_ptr(this);

    [impl::as_nsapplication(m_shared_application) setDelegate:
        [[cmp_application_delegate alloc] init]
    ];
    [impl::as_nsapplication(m_shared_application) finishLaunching];
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

desktop_gui_application*
desktop_gui_application::get_instance_ptr ()
noexcept
{
    return static_cast<desktop_gui_application*>(
        application::get_instance_ptr()
    );
} // function -----------------------------------------------------------------

typename desktop_gui_application::native_handle&
desktop_gui_application::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

int
desktop_gui_application::run ()
noexcept
{
    while (!m_native_handle.window_associations.empty()) {
        NSEvent* event = [impl::as_nsapplication(m_shared_application)
            nextEventMatchingMask:
                NSEventMaskAny
                untilDate:[NSDate distantPast]
                inMode:NSDefaultRunLoopMode
                dequeue:YES
        ];
        if (event != nil) {
            [impl::as_nsapplication(m_shared_application) sendEvent:event];
        } else {
            for (
                auto& current_association
                    : m_native_handle.window_associations
            ) {
                impl::update_window(current_association.second);
            }
        }
    }
    return 0;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
