// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <Windows.h>

#include <cmp/desktop_gui/impl/windows/windows_desktop_gui_application.hpp>

namespace cmp {

// ---------------------------------------------- cmp::desktop_gui_application

// Constructors and Destructor ------------------------------------------------

desktop_gui_application::desktop_gui_application (
    int argc,
    char **argv
)
    : application{argc, argv}
{
    m_native_handle.application_instance_handle = GetModuleHandleW(nullptr);
    m_native_handle.command_line = GetCommandLineW();
    m_native_handle.thread_id = GetCurrentThreadId();

    WNDCLASSW window_class;
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = impl::window_procedure;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance
        = m_native_handle.application_instance_handle;
    window_class.hIcon = LoadIcon(0, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    window_class.lpszMenuName = 0;
    window_class.lpszClassName = m_native_handle.window_class_name;

    if (!RegisterClassW(&window_class)) {
        throw "Window class registration failed.";
    }
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
    MSG message;
    ZeroMemory(&message, sizeof (MSG));
    while (!m_native_handle.window_associations.empty()) {
        if (PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessageW(&message);
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
