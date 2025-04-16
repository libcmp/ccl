// Copyright (C) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/group_box.hpp>

#include <cmp/desktop_gui/main.hpp>
#include <cmp/desktop_gui/window.hpp>
#include <cmp/desktop_gui/layout.hpp>
#include <cmp/desktop_gui/label.hpp>
#include <cmp/desktop_gui/push_button.hpp>
#include <cmp/desktop_gui/check_box.hpp>
#include <cmp/desktop_gui/radio_button.hpp>
#include <cmp/desktop_gui/group_box.hpp>
#include <cmp/desktop_gui/dialog.hpp>
#include <cmp/io/uio.hpp>

class widgets_gallery_window
    : public cmp::window
{
public:
    widgets_gallery_window ()
        : window{
              400,
              300,
              u8"¯\\_(ツ)_/¯",
              cmp::window_mode::standard
          }
    {
        auto& root_layout{grab_root_layout()};

        m_config_layout = root_layout.add_layout(
            cmp::layout::kind::flow,
            cmp::layout::axis::horizontal,
            cmp::layout::direction::forward
        );

        m_kind = m_config_layout->add_widget<cmp::group_box>();
        m_kind->set_text(u8"Kind");

        m_inform_radio_button
            = m_kind->add_widget<cmp::radio_button>(m_kind_group);
        m_inform_radio_button->set_text(u8"Inform");

        m_warn_radio_button
            = m_kind->add_widget<cmp::radio_button>(m_kind_group);
        m_warn_radio_button->set_text(u8"Warn");

        m_alert_radio_button
            = m_kind->add_widget<cmp::radio_button>(m_kind_group);
        m_alert_radio_button->set_text(u8"Alert");

        m_options = m_config_layout->add_widget<cmp::group_box>();
        m_options->set_text(u8"Options");

        m_yes_no_option_radio_button
            = m_options->add_widget<cmp::radio_button>(m_options_group);
        m_yes_no_option_radio_button->set_text(u8"Yes, No");

        m_ok_option_radio_button
            = m_options->add_widget<cmp::radio_button>(m_options_group);
        m_ok_option_radio_button->set_text(u8"OK");

        m_include_cancel_option_check_box
            = m_options->add_widget<cmp::check_box>();
        m_include_cancel_option_check_box->set_text(
            u8"Include Cancel option"
        );

        m_action_layout = root_layout.add_layout(
            cmp::layout::kind::flow,
            cmp::layout::axis::vertical,
            cmp::layout::direction::forward
        );

        m_show_message_push_button
            = m_action_layout->add_widget<cmp::push_button>();
        m_show_message_push_button->set_text(u8"Show Message");
        m_show_message_push_button->set_trigger_event_handler(
            [this] () {
                cmp::dialog::button_set options;
                if (m_yes_no_option_radio_button->is_checked()) {
                    options = m_include_cancel_option_check_box->is_checked()
                        ? cmp::dialog::button_set::yes_no_cancel
                        : cmp::dialog::button_set::yes_no;
                } else if (m_ok_option_radio_button->is_checked()) {
                    options = m_include_cancel_option_check_box->is_checked()
                        ? cmp::dialog::button_set::ok_cancel
                        : cmp::dialog::button_set::ok;
                } else {
                    m_response_label->set_text(
                        u8"Select the options to show."
                    );
                    return;
                }
                cmp::dialog::button response;
                if (m_inform_radio_button->is_checked()) {
                    response = cmp::dialog::inform(
                        this,
                        u8"Title",
                        u8"Message",
                        options
                    );
                } else if (m_warn_radio_button->is_checked()) {
                    response = cmp::dialog::warn(
                        this,
                        u8"Title",
                        u8"Message",
                        options
                    );
                } else if (m_alert_radio_button->is_checked()) {
                    response = cmp::dialog::alert(
                        this,
                        u8"Title",
                        u8"Message",
                        options
                    );
                } else {
                    m_response_label->set_text(
                        u8"Select the kind of message to display."
                    );
                    return;
                }
                if (response == cmp::dialog::button::ok) {
                    m_response_label->set_text(u8"Response: OK");
                } else if (response == cmp::dialog::button::yes) {
                    m_response_label->set_text(u8"Response: Yes");
                } else if (response == cmp::dialog::button::no) {
                    m_response_label->set_text(u8"Response: No");
                } else {
                    m_response_label->set_text(u8"Response: Cancel");
                }
            }
        );

        m_response_label = m_action_layout->add_widget<cmp::label>();
        m_response_label->set_text(
            u8"Configure the dialog and click 'Show Message'."
        );

        cmp::pixval preferred_width;
        cmp::pixval preferred_height;
        root_layout.get_preferred_size(preferred_width, preferred_height);
        set_size(
            preferred_width.get_value() * 1.25,
            preferred_height.get_value() * 1.5
        );

        root_layout.show();
    } // function -------------------------------------------------------------

    void
    handle_close_event (
        cmp::close_event& ev
    )
    override
    {
        if (
            cmp::dialog::warn(
                this,
                u8"Exit Confirmation",
                u8"Are you sure you want to exit?",
                cmp::dialog::button_set::yes_no
            ) == cmp::dialog::button::no
        ) {
            ev.set_should_close(false);
        }
    } // function -------------------------------------------------------------

private:
    cmp::layout_truptr m_config_layout;

    cmp::group_box_truptr m_kind;
    cmp::check_group<cmp::radio_button> m_kind_group;
    cmp::radio_button_truptr m_inform_radio_button;
    cmp::radio_button_truptr m_warn_radio_button;
    cmp::radio_button_truptr m_alert_radio_button;

    cmp::group_box_truptr m_options;
    cmp::check_group<cmp::radio_button> m_options_group;
    cmp::radio_button_truptr m_yes_no_option_radio_button;
    cmp::radio_button_truptr m_ok_option_radio_button;
    cmp::check_box_truptr m_include_cancel_option_check_box;

    cmp::layout_truptr m_action_layout;
    cmp::push_button_truptr m_show_message_push_button;
    cmp::label_truptr m_response_label;
}; // class -------------------------------------------------------------------

int
main (
    int argc,
    char** argv
) {
    cmp::desktop_gui_application app{argc, argv};
    widgets_gallery_window window;
    window.show();
    return app.run();
} // function -----------------------------------------------------------------
