// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_QT_WINDOW_NATIVE_HANDLE_HPP_INCLUDED
#define CMP_DESKTOP_GUI_QT_WINDOW_NATIVE_HANDLE_HPP_INCLUDED

#include <QMainWindow>
#include <QKeyEvent>

#include <memory>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/close_event.hpp>
#include <cmp/desktop_gui/key_event.hpp>

namespace cmp {

namespace impl {

class cmp_main_window
    : public QMainWindow
{
public:
    // Constructors and Destructor --------------------------------------------

    explicit
    cmp_main_window (
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = Qt::WindowFlags()
    );

    ~cmp_main_window ()
    override = default;

protected:
    // Protected Functions ----------------------------------------------------

    void
    keyPressEvent (
        QKeyEvent* event
    )
    override;

    void
    keyReleaseEvent (
        QKeyEvent* event
    )
    override;

    void
    resizeEvent (
        QResizeEvent* event
    )
    override;

    void
    closeEvent (
        QCloseEvent* event
    )
    override;
}; // class -------------------------------------------------------------------

void
forward_key_down_event_to_window (
    cmp_main_window* cmp_main_window_handle,
    QKeyEvent* event
);

void
forward_key_up_event_to_window (
    cmp_main_window* cmp_main_window_handle,
    QKeyEvent* event
);

void
forward_resize_event_to_window (
    cmp_main_window* cmp_main_window_handle
);

bool
forward_close_event_to_window (
    cmp_main_window* cmp_main_window_handle
);

} // namespace ----------------------------------------------------------------

class CMP_CONDITIONAL_EXPORT_CLASS window_native_handle {
public:
    // Public Data ------------------------------------------------------------

    impl::cmp_main_window* cmp_main_window_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_QT_WINDOW_NATIVE_HANDLE_HPP_INCLUDED
