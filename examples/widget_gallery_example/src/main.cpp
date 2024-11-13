// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/main.hpp>
#include <cmp/desktop_gui/layout.hpp>
#include <cmp/desktop_gui/label.hpp>
#include <cmp/desktop_gui/push_button.hpp>
#include <cmp/desktop_gui/check_box.hpp>
#include <cmp/desktop_gui/radio_button.hpp>
#include <cmp/desktop_gui/group_box.hpp>
#include <cmp/desktop_gui/dialog.hpp>

class widgets_gallery_window
    : public cmp::window
{
public:
    widgets_gallery_window ()
        : window{
              500,
              375,
              u8"Widget Gallery Example",
              cmp::window_mode::standard
          }
    {
        build_ui(1);
    } // function -------------------------------------------------------------

    void
    build_ui (
        int index
    ) {
        if (index == 0) {
            auto& root_layout{grab_root_layout()};
            root_layout.set_kind(cmp::layout::kind::flow);
            root_layout.set_axis(cmp::layout::axis::vertical);
            root_layout.set_direction(cmp::layout::direction::forward);

            m_1st_row = root_layout.add_layout(
                cmp::layout::kind::flow,
                cmp::layout::axis::horizontal,
                cmp::layout::direction::forward
            );

            m_process_button = m_1st_row->add_widget<cmp::push_button>();
            m_process_button->set_text(u8"Process Δt");
            m_process_button->set_size(100, 25);

            m_sidestep_button = m_1st_row->add_widget<cmp::push_button>();
            m_sidestep_button->set_text(u8"Sidestep ₤");
            m_sidestep_button->set_size(100, 25);

            m_2nd_row = root_layout.add_layout(
                cmp::layout::kind::flow,
                cmp::layout::axis::horizontal,
                cmp::layout::direction::forward
            );

            m_coracao_check_box = m_2nd_row->add_widget<cmp::check_box>();
            m_coracao_check_box->set_text(u8"Coração");
            m_coracao_check_box->set_size(100, 25);

            m_exito_check_box = m_2nd_row->add_widget<cmp::check_box>();
            m_exito_check_box->set_text(u8"Êxito");
            m_exito_check_box->set_size(100, 25);

            root_layout.show();
        } else if (index == 1) {
            auto& root_layout{grab_root_layout()};
            root_layout.set_kind(cmp::layout::kind::fixed);

            int y1{0};
            int y2{0};

            m_kind = root_layout.add_widget<cmp::group_box>();
            m_kind->set_text(u8"Kind");
            m_kind->set_size(90, 25 * 4 + 8 * 4);
            m_kind->set_position(8, y1 += 8);

            m_inform_radio_button
                = root_layout.add_widget<cmp::radio_button>();
            m_inform_radio_button->set_text(u8"Inform");
            m_inform_radio_button->set_size(90 - 16, 25);
            m_inform_radio_button->set_position(16, y1 += 8 * 4);

            m_warn_radio_button
                = root_layout.add_widget<cmp::radio_button>();
            m_warn_radio_button->set_text(u8"Warn");
            m_warn_radio_button->set_size(90 - 16, 25);
            m_warn_radio_button->set_position(16, y1 += 25 + 8);

            m_alert_radio_button
                = root_layout.add_widget<cmp::radio_button>();
            m_alert_radio_button->set_text(u8"Alert");
            m_alert_radio_button->set_size(90 - 16, 25);
            m_alert_radio_button->set_position(16, y1 += 25 + 8);

            m_options = root_layout.add_widget<cmp::group_box>();
            m_options->set_text(u8"Options");
            m_options->set_size(160 + 8 * 2, 25 * 4 + 8 * 4);
            m_options->set_position(8 + 90 + 8, y2 += 8);

            m_ok_option_radio_button
                = root_layout.add_widget<cmp::radio_button>();
            m_ok_option_radio_button->set_text(u8"OK");
            m_ok_option_radio_button->set_size(100, 25);
            m_ok_option_radio_button->set_position(8 + 90 + 8 * 2, y2 += 8 * 4);

            m_yes_no_option_radio_button
                = root_layout.add_widget<cmp::radio_button>();
            m_yes_no_option_radio_button->set_text(u8"Yes, No");
            m_yes_no_option_radio_button->set_size(100, 25);
            m_yes_no_option_radio_button->set_position(8 + 90 + 8 * 2, y2 += 25 + 8);

            m_include_cancel_option_check_box
                = root_layout.add_widget<cmp::check_box>();
            m_include_cancel_option_check_box->set_text(
                u8"Include Cancel option"
            );
            m_include_cancel_option_check_box->set_size(160, 25);
            m_include_cancel_option_check_box->set_position(8 + 90 + 8 * 2, y2 += 25 + 8);

            m_show_message_push_button
                = root_layout.add_widget<cmp::push_button>();
            m_show_message_push_button->set_text(u8"Show Message");
            m_show_message_push_button->set_size(110, 25);
            m_show_message_push_button->set_position(8, y1 += 25 + 8 * 2);
            m_show_message_push_button->set_trigger_event_handler(
                [this] () {
                    cmp::dialog::button_set options{
                        m_include_cancel_option_check_box->is_checked()
                            ? cmp::dialog::button_set::ok_cancel
                            : cmp::dialog::button_set::ok
                    };
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
                        m_show_message_push_button->apply_preferred_size();
                        m_ok_option_radio_button->apply_preferred_size();
                        m_yes_no_option_radio_button->apply_preferred_size();
                        m_include_cancel_option_check_box->apply_preferred_size();
                        m_response_label->set_text(u8"");
                        m_response_label->apply_preferred_size();
                        return;
                    }
                    if (response == cmp::dialog::button::ok) {
                        m_response_label->set_text(u8"Response: OK");
                        m_response_label->apply_preferred_size();
                    } else {
                        m_response_label->set_text(u8"Response: Cancel");
                        m_response_label->apply_preferred_size();
                    }
                }
            );

            m_response_label = root_layout.add_widget<cmp::label>();
            m_response_label->set_size(125, 25);
            m_response_label->set_position(8, y1 += 25 + 8);

            root_layout.show();
        }
    }

    void
    handle_key_down_event (
        cmp::key_event& ev
    )
    override
    {
        auto& root_layout{grab_root_layout()};
        switch (ev.get_key()) {
            case cmp::key::numpad_6:
            case cmp::key::number_6:
                root_layout.set_x(root_layout.get_x() + 10);
                break;
            case cmp::key::numpad_4:
            case cmp::key::number_4:
                root_layout.set_x(root_layout.get_x() - 10);
                break;
            case cmp::key::numpad_8:
            case cmp::key::number_8:
                root_layout.set_y(root_layout.get_y() - 10);
            break;
            case cmp::key::numpad_2:
            case cmp::key::number_2:
                root_layout.set_y(root_layout.get_y() + 10);
                break;
            case cmp::key::numpad_5:
            case cmp::key::number_5:
                root_layout.set_direction(
                    root_layout.get_direction() == cmp::layout::direction::forward
                        ? cmp::layout::direction::reverse
                        : cmp::layout::direction::forward
                );
                break;
            case cmp::key::numpad_7:
            case cmp::key::number_7:
                m_1st_row->set_direction(
                    m_1st_row->get_direction() == cmp::layout::direction::forward
                        ? cmp::layout::direction::reverse
                        : cmp::layout::direction::forward
                );
                break;
            case cmp::key::numpad_9:
            case cmp::key::number_9:
                m_2nd_row->set_direction(
                    m_2nd_row->get_direction() == cmp::layout::direction::forward
                        ? cmp::layout::direction::reverse
                        : cmp::layout::direction::forward
                );
                break;
            case cmp::key::numpad_0:
            case cmp::key::number_0:
                root_layout.set_kind(
                    root_layout.get_kind() == cmp::layout::kind::flow
                        ? cmp::layout::kind::fixed
                        : cmp::layout::kind::flow
                );
                break;
        }
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
    // Index 0
    cmp::push_button_truptr m_process_button;
    cmp::push_button_truptr m_sidestep_button;
    cmp::check_box_truptr m_coracao_check_box;
    cmp::check_box_truptr m_exito_check_box;

    cmp::layout_truptr m_1st_row;
    cmp::layout_truptr m_2nd_row;

    // Index 1
    cmp::group_box_truptr m_kind;
    cmp::radio_button_truptr m_inform_radio_button;
    cmp::radio_button_truptr m_warn_radio_button;
    cmp::radio_button_truptr m_alert_radio_button;

    cmp::group_box_truptr m_options;
    cmp::radio_button_truptr m_ok_option_radio_button;
    cmp::radio_button_truptr m_yes_no_option_radio_button;
    cmp::check_box_truptr m_include_cancel_option_check_box;

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
