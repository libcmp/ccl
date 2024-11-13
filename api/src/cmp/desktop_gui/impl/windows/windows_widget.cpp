// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_widget.hpp>

namespace cmp {

namespace impl {

widget_native_handle
create_widget (
    const window_native_handle& parent_window,
    native_widget_kind kind
)
noexcept
{
    std::wstring_view class_name;
    DWORD style;
    switch (kind) {
        case native_widget_kind::label:
            class_name = L"static";
            style = 0;
            break;
        case native_widget_kind::push_button:
            class_name = L"button";
            style = BS_PUSHBUTTON;
            break;
        case native_widget_kind::check_box:
            class_name = L"button";
            style = BS_AUTOCHECKBOX;
            break;
        case native_widget_kind::radio_button:
            class_name = L"button";
            style = BS_AUTORADIOBUTTON;
            break;
        case native_widget_kind::group_box:
            class_name = L"button";
            style = BS_GROUPBOX;
            break;
    }
    HWND result{
        CreateWindowW(
            class_name.data(),
            L"",
            style | WS_CHILD | WS_TABSTOP,
            0,
            0,
            to_dotval(100, GetDpiForWindow(parent_window.window_handle)).get_value(),
            to_dotval(25, GetDpiForWindow(parent_window.window_handle)).get_value(),
            parent_window.window_handle,
            NULL,
            dgui_app()->grab_native_handle().application_instance_handle,
            NULL
        )
    };
    SendMessage(
        result,
        WM_SETFONT,
        reinterpret_cast<LPARAM>(GetStockObject(DEFAULT_GUI_FONT)),
        true
    );
    return {parent_window.window_handle, result};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    const window_native_handle& handle
)
    : m_native_handle{handle.window_handle, nullptr}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

widget_native_handle&
widget::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

const widget_native_handle&
widget::grab_native_handle ()
const noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

pixval
widget::get_x ()
const noexcept
{
    RECT rect;
    GetClientRect(grab_native_handle().widget_handle, &rect);
    return to_pixval(dotval{static_cast<int>(rect.left)}, get_parent_dpi());
} // function -----------------------------------------------------------------

void
widget::set_x (
    pixval new_x
)
noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    POINT point;
    point.x = rect.left;
    point.y = rect.top;
    ScreenToClient(grab_native_handle().parent_handle, &point);
    const LONG current_y{point.y};
    SetWindowPos(
        grab_native_handle().widget_handle,
        HWND_TOP,
        to_dotval(new_x, get_parent_dpi()).get_value(),
        current_y,
        0,
        0,
        SWP_NOSIZE
    );
} // function -----------------------------------------------------------------

pixval
widget::get_y ()
const noexcept
{
    RECT rect;
    GetClientRect(grab_native_handle().widget_handle, &rect);
    return to_pixval(dotval{static_cast<int>(rect.top)}, get_parent_dpi());
} // function -----------------------------------------------------------------

void
widget::set_y (
    pixval new_y
)
noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    POINT point;
    point.x = rect.left;
    point.y = rect.top;
    ScreenToClient(grab_native_handle().parent_handle, &point);
    const LONG current_x{point.x};
    SetWindowPos(
        grab_native_handle().widget_handle,
        HWND_TOP,
        current_x,
        to_dotval(new_y, get_parent_dpi()).get_value(),
        0,
        0,
        SWP_NOSIZE
    );
} // function -----------------------------------------------------------------

void
widget::get_position (
    pixval& x,
    pixval& y
)
const noexcept
{
    auto dpi{get_parent_dpi()};
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    x = to_pixval(dotval{static_cast<int>(rect.left)}, dpi);
    y = to_pixval(dotval{static_cast<int>(rect.top)}, dpi);
} // function -----------------------------------------------------------------

void
widget::set_position (
    pixval new_x,
    pixval new_y
)
noexcept
{
    auto dpi{get_parent_dpi()};
    SetWindowPos(
        grab_native_handle().widget_handle,
        HWND_TOP,
        to_dotval(new_x, dpi).get_value(),
        to_dotval(new_y, dpi).get_value(),
        0,
        0,
        SWP_NOSIZE
    );
} // function -----------------------------------------------------------------

pixval
widget::get_width ()
const noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    return to_pixval(
        dotval{static_cast<int>(rect.right - rect.left)},
        get_parent_dpi()
    );
} // function -----------------------------------------------------------------

void
widget::set_width (
    pixval new_width
)
noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    const LONG current_height{rect.bottom - rect.top};
    SetWindowPos(
        grab_native_handle().widget_handle,
        HWND_TOP,
        0,
        0,
        to_dotval(new_width, get_parent_dpi()).get_value(),
        current_height,
        SWP_NOMOVE
    );
} // function -----------------------------------------------------------------

pixval
widget::get_height ()
const noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    return to_pixval(
        dotval{static_cast<int>(rect.bottom - rect.top)},
        get_parent_dpi()
    );
} // function -----------------------------------------------------------------

void
widget::set_height (
    pixval new_height
)
noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    const LONG current_width{rect.right - rect.left};
    SetWindowPos(
        grab_native_handle().widget_handle,
        HWND_TOP,
        0,
        0,
        current_width,
        to_dotval(new_height, get_parent_dpi()).get_value(),
        SWP_NOMOVE
    );
} // function -----------------------------------------------------------------

void
widget::get_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    auto dpi{get_parent_dpi()};
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    width = to_pixval(dotval{static_cast<int>(rect.right - rect.left)}, dpi);
    height = to_pixval(dotval{static_cast<int>(rect.bottom - rect.top)}, dpi);
} // function -----------------------------------------------------------------

void
widget::set_size (
    pixval new_width,
    pixval new_height
)
noexcept
{
    auto dpi{get_parent_dpi()};
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    SetWindowPos(
        grab_native_handle().widget_handle,
        HWND_TOP,
        0,
        0,
        to_dotval(new_width, dpi).get_value(),
        to_dotval(new_height, dpi).get_value(),
        SWP_NOMOVE
    );
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
widget::show ()
noexcept
{
    ShowWindow(grab_native_handle().widget_handle, SW_SHOW);
} // function -----------------------------------------------------------------

void
widget::hide ()
noexcept
{
    ShowWindow(grab_native_handle().widget_handle, SW_HIDE);
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    widget_native_handle&& widget_handle
)
    : m_native_handle{std::move(widget_handle)}
{
} // function -----------------------------------------------------------------

int
widget::get_parent_dpi ()
const noexcept
{
    return static_cast<int>(GetDpiForWindow(m_native_handle.parent_handle));
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
