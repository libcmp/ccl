// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <Windows.h>

#include <cmp/desktop_gui/impl/common/common_dialog.hpp>

namespace cmp {

namespace impl {

LRESULT CALLBACK
hook_procedure (
    int n_code,
    WPARAM w_param,
    LPARAM l_param
) {
    if (n_code == HCBT_ACTIVATE) {
        auto dialog_window{reinterpret_cast<HWND>(w_param)};
        HWND button_handle;

        button_handle = GetDlgItem(dialog_window, IDOK);
        if (button_handle != NULL) {
            SetDlgItemTextW(dialog_window, IDOK, L"OK");
        }

        button_handle = GetDlgItem(dialog_window, IDCANCEL);
        if (button_handle != NULL) {
            SetDlgItemTextW(dialog_window, IDCANCEL, L"Cancel");
        }

        button_handle = GetDlgItem(dialog_window, IDYES);
        if (button_handle != NULL) {
            SetDlgItemTextW(dialog_window, IDYES, L"Yes");
        }

        button_handle = GetDlgItem(dialog_window, IDNO);
        if (button_handle != NULL) {
            SetDlgItemTextW(dialog_window, IDNO, L"No");
        }

        button_handle = GetDlgItem(dialog_window, IDHELP);
        if (button_handle != NULL) {
            SetDlgItemTextW(dialog_window, IDHELP, L"Help");
        }

        UnhookWindowsHookEx(dialog::g_hook_procedure_handle);
        return 0;
    } else {
        return CallNextHookEx(
            dialog::g_hook_procedure_handle,
            n_code,
            w_param,
            l_param
        );
    }
} // function -----------------------------------------------------------------

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
        MB_ICONINFORMATION | get_native_buttons(buttons)
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
        MB_ICONWARNING | get_native_buttons(buttons)
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
        MB_ICONERROR | get_native_buttons(buttons)
    );
} // function -----------------------------------------------------------------

// Private Data ---------------------------------------------------------------

HHOOK dialog::g_hook_procedure_handle;

// Private Functions ----------------------------------------------------------

UINT
dialog::get_native_buttons (
    button_set buttons
)
noexcept
{
    switch (buttons) {
        case button_set::ok:
            return MB_OK;
        case button_set::ok_cancel:
            return MB_OKCANCEL;
        case button_set::yes_no:
            return MB_YESNO;
        case button_set::yes_no_cancel:
            return MB_YESNOCANCEL;
    }
} // function -----------------------------------------------------------------

dialog::button
dialog::get_standard_button (
    UINT button
)
noexcept
{
    switch (button) {
        case IDOK:
            return button::ok;
        case IDCANCEL:
            return button::cancel;
        case IDYES:
            return button::yes;
        case IDNO:
            return button::no;
    }
} // function -----------------------------------------------------------------

dialog::button
dialog::message_box (
    window* parent,
    std::u8string_view title,
    std::u8string_view message,
    UINT type
)
noexcept
{
    g_hook_procedure_handle = SetWindowsHookExW(
        WH_CBT,
        &impl::hook_procedure,
        NULL,
        GetCurrentThreadId()
    );
    std::wstring title_wstring{to_wstring(title)};
    std::wstring message_wstring{to_wstring(message)};
    return get_standard_button(
        MessageBoxW(
            parent ? parent->grab_native_handle().window_handle : NULL,
            message_wstring.data(),
            title_wstring.data(),
            type
        )
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
