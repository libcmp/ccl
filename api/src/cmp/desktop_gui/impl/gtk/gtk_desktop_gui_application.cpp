// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/gtk/gtk_desktop_gui_application.hpp>

namespace cmp {

namespace impl {

// Free Functions -------------------------------------------------------------

void
activate (
    GApplication* application,
    gpointer* user_data
)
noexcept
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// ---------------------------------------------- cmp::desktop_gui_application

// Constructors and Destructor ------------------------------------------------

desktop_gui_application::desktop_gui_application (
    int argc,
    char **argv
)
    : application{argc, argv}
{
    m_native_handle.gtk_application = gtk_application_new(
        NULL,
        G_APPLICATION_DEFAULT_FLAGS
    );
    g_signal_connect(
        m_native_handle.gtk_application,
        "activate",
        G_CALLBACK(impl::activate),
        NULL
    );
    g_application_register(
        G_APPLICATION(m_native_handle.gtk_application),
        NULL,
        NULL
    );
    g_application_activate(G_APPLICATION(m_native_handle.gtk_application));
} // function -----------------------------------------------------------------

desktop_gui_application::~desktop_gui_application ()
noexcept
{
    g_object_unref(m_native_handle.gtk_application);
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
    GMainContext* context{g_main_context_default()};
    while (g_list_model_get_n_items(gtk_window_get_toplevels()) > 0) {
        if (g_main_context_pending(context)) {
            g_main_context_dispatch(context);
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
