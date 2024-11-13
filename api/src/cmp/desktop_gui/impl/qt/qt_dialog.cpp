// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

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
        static_cast<message_box_function_t>(&QMessageBox::information),
        buttons
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
        static_cast<message_box_function_t>(&QMessageBox::warning),
        buttons
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
        static_cast<message_box_function_t>(&QMessageBox::critical),
        buttons
    );
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

QMessageBox::StandardButtons
dialog::get_native_buttons (
    button_set buttons
)
noexcept
{
	QMessageBox::StandardButtons standard_buttons;
    switch (buttons) {
    	case button_set::ok:
        	standard_buttons = QMessageBox::Ok;
            break;
        case button_set::ok_cancel:
            standard_buttons = QMessageBox::Ok | QMessageBox::Cancel;
            break;
        case button_set::yes_no:
            standard_buttons = QMessageBox::Yes | QMessageBox::No;
            break;
        case button_set::yes_no_cancel:
            standard_buttons = QMessageBox::Yes
                | QMessageBox::No
                | QMessageBox::Cancel;
            break;
    }
    return standard_buttons;
}

dialog::button
dialog::message_box (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    message_box_function_t message_box_function,
    button_set buttons
)
noexcept
{
    QMessageBox::StandardButton result{
        message_box_function(
            parent->grab_native_handle().cmp_main_window_handle,
            QString::fromUtf8(title.data()),
            QString::fromUtf8(message.data()),
            get_native_buttons(buttons),
            QMessageBox::NoButton
        )
    };
    switch (result) {
        case QMessageBox::Ok:
            return button::ok;
    	case QMessageBox::Cancel:
          	return button::cancel;
        case QMessageBox::Yes:
            return button::yes;
        case QMessageBox::No:
            return button::no;
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
