// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/qt/qt_window_native_handle.hpp>

namespace cmp {

namespace impl {

// ------------------------------------------------ cmp::impl::cmp_main_window

// Constructors and Destructor ------------------------------------------------

cmp_main_window::cmp_main_window (
    QWidget* parent,
    Qt::WindowFlags flags
)
    : QMainWindow{parent, flags}
{
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

void
cmp_main_window::keyPressEvent (
    QKeyEvent* event
) {
    forward_key_down_event_to_window(this, event);
} // function -----------------------------------------------------------------

void
cmp_main_window::keyReleaseEvent (
    QKeyEvent* event
) {
    forward_key_up_event_to_window(this, event);
} // function -----------------------------------------------------------------

void
cmp_main_window::resizeEvent (
    QResizeEvent* event
) {
    forward_resize_event_to_window(this);
} // function -----------------------------------------------------------------

void
cmp_main_window::closeEvent (
    QCloseEvent* event
) {
    if (forward_close_event_to_window(this)) {
        event->ignore();
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
