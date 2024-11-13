// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <gtk/gtk.h>

#include <cmp/desktop_gui/impl/common/common_dialog.hpp>

namespace cmp {

// --------------------------------------------------------------- cmp::dialog

// Core -----------------------------------------------------------------------

dialog::button
dialog::inform (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    button_set buttons
)
noexcept
{
    return message_box(
        parent,
        title,
        message,
        GTK_MESSAGE_INFO,
        buttons,
        GTK_DIALOG_MODAL
    );
} // function -----------------------------------------------------------------

dialog::button
dialog::warn (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    button_set buttons
)
noexcept
{
    return message_box(
        parent,
        title,
        message,
        GTK_MESSAGE_WARNING,
        buttons,
        GTK_DIALOG_MODAL
    );
} // function -----------------------------------------------------------------

dialog::button
dialog::alert (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    button_set buttons
)
noexcept
{
    return message_box(
        parent,
        title,
        message,
        GTK_MESSAGE_ERROR,
        buttons,
        GTK_DIALOG_MODAL
    );
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
dialog::on_choose (
    GObject* source_object,
    GAsyncResult* result,
    gpointer user_data
)
noexcept
{
    GtkAlertDialog* dialog{GTK_ALERT_DIALOG(source_object)};
    GError* error{nullptr};

    int button{gtk_alert_dialog_choose_finish(dialog, result, &error)};

    if (error) {
        std::cout << "An error occurred.\n"
                  << "Error message: "
                  << error->message
                  << '\n';
        g_main_loop_quit(static_cast<GMainLoop*>(user_data));
        return;
    }

    std::cout << "Response: " << button << std::endl;
    g_main_loop_quit(static_cast<GMainLoop*>(user_data));
} // function -----------------------------------------------------------------

dialog::button
dialog::message_box (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    GtkMessageType type,
    button_set buttons,
    GtkDialogFlags flags
)
noexcept
{
    // /*
    GtkAlertDialog* dialog{
        gtk_alert_dialog_new("Are you sure you wish to exit?")
    };
    gtk_alert_dialog_set_modal(dialog, true);
    switch (buttons) {
        case button_set::ok: {
            const char* button_labels[]{"OK", nullptr};
            gtk_alert_dialog_set_buttons(dialog, button_labels);
            break;
        }
        case button_set::ok_cancel: {
            const char* button_labels[]{"OK", "Cancel", nullptr};
            gtk_alert_dialog_set_buttons(dialog, button_labels);
            break;
        }
        case button_set::yes_no: {
            const char* button_labels[]{"Yes", "No", nullptr};
            gtk_alert_dialog_set_buttons(dialog, button_labels);
            break;
        }
        case button_set::yes_no_cancel: {
            const char* button_labels[]{"Yes", "No", "Cancel", nullptr};
            gtk_alert_dialog_set_buttons(dialog, button_labels);
            break;
        }
    }

    GMainLoop* dialog_gmainloop{g_main_loop_new(nullptr, false)};
    gtk_alert_dialog_choose(
        dialog,
        GTK_WINDOW(parent->grab_native_handle().gtk_application_window),
        nullptr,
        dialog::on_choose,
        static_cast<gpointer>(dialog_gmainloop)
    );
    g_main_loop_run(dialog_gmainloop);
    // */

    /*
    GtkNativeDialog* dialog{
        GTK_NATIVE_DIALOG(
            gtk_message_dialog_new(
                GTK_WINDOW(parent->grab_native_handle().gtk_application_window),
                flags,
                type,
                GTK_BUTTONS_OK,
                reinterpret_cast<const char*>(message.data())
            )
        )
    };
    gtk_window_set_title(
        GTK_WINDOW(dialog),
        reinterpret_cast<const char*>(title.data())
    );
    gtk_native_dialog_show(GTK_NATIVE_DIALOG(dialog));
    gtk_native_dialog_destroy(GTK_NATIVE_DIALOG(dialog));
    // */
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
