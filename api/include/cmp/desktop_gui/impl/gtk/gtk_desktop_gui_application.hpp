// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_GTK_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
#define CMP_DESKTOP_GUI_GTK_DESKTOP_GUI_APPLICATION_HPP_INCLUDED

#include <vector>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/core/application.hpp>
#include <cmp/desktop_gui/impl/gtk/gtk_window_native_handle.hpp>
#include <cmp/desktop_gui/general.hpp>

namespace cmp {

class CMP_LIBRARY_NAME desktop_gui_application
    : public application
{
public:
    // Types ------------------------------------------------------------------

    class native_handle {
    public:
        // Public Data --------------------------------------------------------

        GtkApplication* gtk_application;
        std::vector<std::pair<GtkWidget*, window*>> window_associations;
    }; // class ---------------------------------------------------------------

    // Constructors and Destructor --------------------------------------------

    desktop_gui_application (
        int argc,
        char** argv
    );

    ~desktop_gui_application ()
    override;

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

#endif // CMP_DESKTOP_GUI_GTK_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
