// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_WINDOWS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
#define CMP_DESKTOP_GUI_WINDOWS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED

#include <vector>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/core/application.hpp>
#include <cmp/desktop_gui/impl/windows/windows_window_native_handle.hpp>
#include <cmp/desktop_gui/general.hpp>

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

class CMP_CONDITIONAL_EXPORT_CLASS desktop_gui_application
    : public application
{
public:
    // Types ------------------------------------------------------------------

    class CMP_CONDITIONAL_EXPORT_CLASS native_handle {
    public:
        // Public Data --------------------------------------------------------

        HINSTANCE application_instance_handle;
        LPWSTR command_line;
        LPCWSTR window_class_name;
        std::vector<std::pair<HWND, window*>> window_associations;
    }; // class ---------------------------------------------------------------

    // Constants --------------------------------------------------------------

    static constexpr const wchar_t* window_class_name{L"CCLWindow"};

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    desktop_gui_application (
        int argc,
        char** argv
    );

    ~desktop_gui_application ()
    override = default;

    // Copy Operations --------------------------------------------------------

    desktop_gui_application (
        const desktop_gui_application& other
    )
    = delete;

    desktop_gui_application&
    operator = (
        const desktop_gui_application& other
    )
    = delete;

    // Move Operations --------------------------------------------------------

    desktop_gui_application (
        desktop_gui_application&& other
    )
    noexcept = default;

    desktop_gui_application&
    operator = (
        desktop_gui_application&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    static
    desktop_gui_application*
    get_instance_ptr ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    native_handle&
    grab_native_handle ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    const native_handle&
    grab_native_handle ()
    const noexcept;

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    int
    run ()
    override;

private:
    // Private Data -----------------------------------------------------------

    native_handle m_native_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_WINDOWS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
