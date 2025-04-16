// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <gtk/gtk.h>

#include <cmp/desktop_gui/impl/common/common_dialog.hpp>

namespace cmp {

namespace impl {

class dialog_context {
public:
    GMainLoop* loop;
    int response;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

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
    auto dc{static_cast<impl::dialog_context*>(user_data)};
    GtkAlertDialog* dialog{GTK_ALERT_DIALOG(source_object)};
    GError* error{nullptr};

    dc->response = gtk_alert_dialog_choose_finish(dialog, result, &error);

    g_main_loop_quit(dc->loop);
} // function -----------------------------------------------------------------

dialog::button
dialog::message_box (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    button_set buttons,
    GtkDialogFlags flags
)
noexcept
{
    GtkAlertDialog* dialog{
        gtk_alert_dialog_new(reinterpret_cast<const char*>(message.data()))
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

    impl::dialog_context dc;
    dc.loop = g_main_loop_new(nullptr, false);
    gtk_alert_dialog_choose(
        dialog,
        GTK_WINDOW(parent->grab_native_handle().gtk_application_window),
        nullptr,
        dialog::on_choose,
        static_cast<gpointer>(&dc)
    );
    g_main_loop_run(dc.loop);
    switch (buttons) {
        case button_set::ok: {
            return button::ok;
        }
        case button_set::ok_cancel: {
            return dc.response == 0 ? button::ok : button::cancel;
        }
        case button_set::yes_no: {
            return dc.response == 0 ? button::yes : button::no;
        }
        case button_set::yes_no_cancel: {
            switch (dc.response) {
                case 0: {
                    return button::yes;
                }
                case 1: {
                    return button::no;
                }
                case 2: {
                    return button::cancel;
                }
            }
        }
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
