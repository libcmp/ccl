// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/qt/qt_desktop_gui_application.hpp>

namespace cmp {

// ---------------------------------------------- cmp::desktop_gui_application

// Constructors and Destructor ------------------------------------------------

desktop_gui_application::desktop_gui_application (
    int argc,
    char **argv
)
    : application{argc, argv}
{
    m_native_handle.qt_application
      = std::make_unique<QApplication>(argc, argv);
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

desktop_gui_application::native_handle&
desktop_gui_application::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

const desktop_gui_application::native_handle&
desktop_gui_application::grab_native_handle ()
const noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

int
desktop_gui_application::run ()
{
    return m_native_handle.qt_application->exec();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
