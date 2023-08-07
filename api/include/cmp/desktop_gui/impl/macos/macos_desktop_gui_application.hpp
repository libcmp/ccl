// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_MACOS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
#define CMP_DESKTOP_GUI_MACOS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED

#include <vector>
#include <type_traits>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/core/application.hpp>
#include <cmp/desktop_gui/general.hpp>
#include <cmp/desktop_gui/impl/macos/macos_window_native_handle.hpp>

namespace cmp {

class window;

class CMP_LIBRARY_NAME desktop_gui_application
    : public application
{
public:
    // Types ------------------------------------------------------------------

    class native_handle {
    public:
        // Public Data --------------------------------------------------------

        std::vector<std::pair<void*, window*>> window_associations;
    }; // class ---------------------------------------------------------------

    // Constructors and Destructor --------------------------------------------

    desktop_gui_application (
        int argc,
        char** argv
    );

    ~desktop_gui_application ()
    = default;

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
    noexcept override;

private:
    // Private Data -----------------------------------------------------------

    void* m_shared_application;
    native_handle m_native_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_MACOS_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
