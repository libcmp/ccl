// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_widget.hpp>

namespace cmp {

namespace impl {

widget_native_handle
create_widget (
    const HWND& parent_handle,
    native_widget_kind kind
)
noexcept
{
    std::wstring_view class_name;
    DWORD style;
    switch (kind) {
        case native_widget_kind::label:
            class_name = L"static";
            style = SS_CENTERIMAGE;
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
            style = BS_AUTORADIOBUTTON | WS_GROUP;
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
            to_dotval(
                100,
                GetDpiForWindow(parent_handle)
            ).get_value(),
            to_dotval(
                25,
                GetDpiForWindow(parent_handle)
            ).get_value(),
            parent_handle,
            nullptr,
            dgui_app()->grab_native_handle().application_instance_handle,
            nullptr
        )
    };
    if (kind == native_widget_kind::group_box) {
        SetWindowSubclass(result, impl::control_procedure, 0, 0);
    }
    auto font{GetStockObject(DEFAULT_GUI_FONT)};
    LOGFONTW logfont;
    GetObject(font, sizeof (LOGFONTW), &logfont);
    logfont.lfHeight
        = -12 * static_cast<double>(GetDpiForWindow(parent_handle)) / 96;
    auto new_font{CreateFontIndirectW(&logfont)};
    SendMessage(
        result,
        WM_SETFONT,
        reinterpret_cast<LPARAM>(new_font),
        true
    );
    return {parent_handle, result};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::widget

// Constructors and Destructor ------------------------------------------------

widget::widget (
    layout& enclosing_layout
)
    : m_native_handle{
          enclosing_layout.grab_enclosing_window_handle().window_handle,
          nullptr
      }
    , m_enclosing_layout{&enclosing_layout}
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

layout&
widget::grab_enclosing_layout ()
noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

const layout&
widget::grab_enclosing_layout ()
const noexcept
{
    return *m_enclosing_layout;
} // function -----------------------------------------------------------------

pixval
widget::get_x ()
const noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    POINT point;
    point.x = rect.left;
    point.y = rect.top;
    ScreenToClient(grab_native_handle().parent_handle, &point);
    return to_pixval(dotval{static_cast<int>(point.x)}, get_parent_dpi());
} // function -----------------------------------------------------------------

pixval
widget::get_y ()
const noexcept
{
    RECT rect;
    GetWindowRect(grab_native_handle().widget_handle, &rect);
    POINT point;
    point.x = rect.left;
    point.y = rect.top;
    ScreenToClient(grab_native_handle().parent_handle, &point);
    return to_pixval(dotval{static_cast<int>(point.y)}, get_parent_dpi());
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
    POINT point;
    point.x = rect.left;
    point.y = rect.top;
    ScreenToClient(grab_native_handle().parent_handle, &point);
    x = to_pixval(dotval{static_cast<int>(point.x)}, dpi);
    y = to_pixval(dotval{static_cast<int>(point.y)}, dpi);
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

void
widget::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
    /*
        Here we update the font size.
    */
    auto font{
        reinterpret_cast<HFONT>(
            SendMessage(m_native_handle.widget_handle, WM_GETFONT, 0, 0)
        )
    };
    LOGFONTW logfont;
    GetObject(font, sizeof (LOGFONTW), &logfont);
    logfont.lfHeight = -12 * new_dpi / 96;
    auto new_font{CreateFontIndirectW(&logfont)};
    SendMessageW(
        m_native_handle.widget_handle,
        WM_SETFONT,
        (WPARAM)new_font,
        TRUE
    );

    /*
        Here we update the widget's position and size.
    */
    RECT rect;
    GetWindowRect(m_native_handle.widget_handle, &rect);
    POINT top_left;
    top_left.x = rect.left;
    top_left.y = rect.top;
    ScreenToClient(m_native_handle.parent_handle, &top_left);
    auto x{top_left.x};
    auto y{top_left.y};
    auto width{rect.right - rect.left};
    auto height{rect.bottom - rect.top};
    double factor{static_cast<double>(new_dpi) / old_dpi};
    SetWindowPos(
        m_native_handle.widget_handle,
        HWND_TOP,
        std::ceil(x * factor),
        std::ceil(y * factor),
        std::ceil(width * factor),
        std::ceil(height * factor),
        0
    );
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

widget::widget (
    layout& enclosing_layout,
    widget_native_handle&& widget_handle
)
    : m_native_handle{std::move(widget_handle)}
    , m_enclosing_layout{&enclosing_layout}
{
} // function -----------------------------------------------------------------

bool
widget::is_geometry_modification_prohibited ()
const noexcept
{
    return m_enclosing_layout->get_kind() != layout::kind::fixed;
} // function -----------------------------------------------------------------

void
widget::set_x_forcefully (
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

void
widget::set_y_forcefully (
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
widget::set_position_forcefully (
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

void
widget::set_width_forcefully (
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

void
widget::set_height_forcefully (
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
widget::set_size_forcefully (
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

int
widget::get_parent_dpi ()
const noexcept
{
    return static_cast<int>(
        GetDpiForWindow(
            grab_enclosing_layout().grab_enclosing_window_handle()
                .window_handle
        )
    );
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
