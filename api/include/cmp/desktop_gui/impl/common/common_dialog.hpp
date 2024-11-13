// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_COMMON_DIALOG_HPP_INCLUDED
#define CMP_DESKTOP_GUI_COMMON_DIALOG_HPP_INCLUDED

#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
#   include <QMessageBox>
#   include <functional>
#endif

#include <string_view>

#include <cmp/core/platform.hpp>
#include <cmp/desktop_gui/window.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

namespace impl {

#if defined(CMP_OS_WINDOWS)
LRESULT CALLBACK
hook_procedure (
    int n_code,
    WPARAM w_param,
    LPARAM l_param
);
#endif

} // namespace ----------------------------------------------------------------

class CMP_CONDITIONAL_EXPORT_CLASS dialog {
public:
    // Types ------------------------------------------------------------------

    enum class button_set {
        ok,
        ok_cancel,
        yes_no,
        yes_no_cancel
    }; // enum ----------------------------------------------------------------

    enum class button {
        ok,
        cancel,
        yes,
        no
    }; // enum ----------------------------------------------------------------

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    static
    button
    inform (
        window* parent,
        std::u8string_view title,
        std::u8string_view message,
        button_set buttons
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    static
    button
    warn (
        window* parent,
        std::u8string_view title,
        std::u8string_view message,
        button_set buttons
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    static
    button
    alert (
        window* parent,
        std::u8string_view title,
        std::u8string_view message,
        button_set buttons
    )
    noexcept;

    // Friends ----------------------------------------------------------------

#if defined(CMP_OS_WINDOWS)
    friend
    LRESULT CALLBACK
    impl::hook_procedure (
        int n_code,
        WPARAM w_param,
        LPARAM l_param
    );
#endif

private:
    // Private Types ----------------------------------------------------------

#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
    using message_box_function_t =
        QMessageBox::StandardButton
        (*) (
            QWidget*,
            const QString&,
            const QString&,
            QMessageBox::StandardButtons,
            QMessageBox::StandardButton
        );
#endif

    // Private Data -----------------------------------------------------------

#if defined(CMP_OS_WINDOWS)
    static HHOOK g_hook_procedure_handle;
#endif

    // Private Functions ------------------------------------------------------

#if defined(CMP_OS_WINDOWS)
    CMP_CONDITIONAL_EXPORT
    static
    UINT
    get_native_buttons (
        button_set buttons
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    static
    button
    get_standard_button (
        UINT button
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    static
    button
    message_box (
        window* parent,
        std::u8string_view title,
        std::u8string_view message,
        UINT type
    )
    noexcept;
#elif defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
    static
    QMessageBox::StandardButtons
    get_native_buttons (
        button_set buttons
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    static
    button
    message_box (
        window* parent,
        std::u8string_view title,
        std::u8string_view message,
        message_box_function_t message_box_function,
        button_set buttons
    )
    noexcept;
#endif
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_COMMON_DIALOG_HPP_INCLUDED
