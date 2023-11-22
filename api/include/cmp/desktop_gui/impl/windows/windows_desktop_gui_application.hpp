// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOWS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOWS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED

#include <vector>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/core/application.hpp>
#include <cmp/desktop_gui/general.hpp>
#include <cmp/desktop_gui/impl/windows/windows_window_native_handle.hpp>

namespace cmp {

namespace impl {

// Free Functions -------------------------------------------------------------

LRESULT CALLBACK
window_procedure (
    HWND window_handle,
    UINT message,
    WPARAM w_param,
    LPARAM l_param
);

} // namespace ----------------------------------------------------------------

class CMP_LIBRARY_NAME desktop_gui_application
    : public application
{
public:
    // Types ------------------------------------------------------------------

    class native_handle {
    public:
        // Public Data --------------------------------------------------------

        HINSTANCE application_instance_handle;
        LPWSTR command_line;
        LPCWSTR window_class_name;
        std::vector<std::pair<HWND, window*>> window_associations;
    }; // class ---------------------------------------------------------------

    // Constructors and Destructor --------------------------------------------

    desktop_gui_application (
        int argc,
        char** argv
    );

    // Accessors --------------------------------------------------------------

    static
    desktop_gui_application*
    get_instance_ptr ()
    noexcept;

    native_handle&
    grab_native_handle ()
    noexcept;

    const native_handle&
    grab_native_handle ()
    const noexcept;

    // Core -------------------------------------------------------------------

    int
    run ()
    override;

private:
    // Private Data -----------------------------------------------------------

    native_handle m_native_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_WINDOWS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
