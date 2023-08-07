// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/windows/windows_window.hpp>

namespace cmp {

namespace impl {

typename desktop_gui_application::native_handle&
grab_application_native_handle ()
noexcept
{
    return desktop_gui_application::get_instance_ptr()->grab_native_handle();
} // function -----------------------------------------------------------------

void
update_window (
    window* w
) {
    w->update();
} // function -----------------------------------------------------------------

key
translate_key_code (
    WPARAM key_code
) {
    switch (key_code) {
        case VK_F1:
            return key::f1;
        case VK_F2:
            return key::f2;
        case VK_F3:
            return key::f3;
        case VK_F4:
            return key::f4;
        case VK_F5:
            return key::f5;
        case VK_F6:
            return key::f6;
        case VK_F7:
            return key::f7;
        case VK_F8:
            return key::f8;
        case VK_F9:
            return key::f9;
        case VK_F10:
            return key::f10;
        case VK_F11:
            return key::f11;
        case VK_F12:
            return key::f12;
        case VK_F13:
            return key::f13;
        case VK_F14:
            return key::f14;
        case VK_F15:
            return key::f15;
        case VK_F16:
            return key::f16;
        case VK_F17:
            return key::f17;
        case VK_F18:
            return key::f18;
        case VK_F19:
            return key::f19;
        case VK_F20:
            return key::f20;
        case VK_F21:
            return key::f21;
        case VK_F22:
            return key::f22;
        case VK_F23:
            return key::f23;
        case VK_F24:
            return key::f24;
        case 0x30:
            return key::number_0;
        case 0x31:
            return key::number_1;
        case 0x32:
            return key::number_2;
        case 0x33:
            return key::number_3;
        case 0x34:
            return key::number_4;
        case 0x35:
            return key::number_5;
        case 0x36:
            return key::number_6;
        case 0x37:
            return key::number_7;
        case 0x38:
            return key::number_8;
        case 0x39:
            return key::number_9;
        case VK_NUMPAD0:
            return key::numpad_0;
        case VK_NUMPAD1:
            return key::numpad_1;
        case VK_NUMPAD2:
            return key::numpad_2;
        case VK_NUMPAD3:
            return key::numpad_3;
        case VK_NUMPAD4:
            return key::numpad_4;
        case VK_NUMPAD5:
            return key::numpad_5;
        case VK_NUMPAD6:
            return key::numpad_6;
        case VK_NUMPAD7:
            return key::numpad_7;
        case VK_NUMPAD8:
            return key::numpad_8;
        case VK_NUMPAD9:
            return key::numpad_9;
        case 0x41:
            return key::a;
        case 0x42:
            return key::b;
        case 0x43:
            return key::c;
        case 0x44:
            return key::d;
        case 0x45:
            return key::e;
        case 0x46:
            return key::f;
        case 0x47:
            return key::g;
        case 0x48:
            return key::h;
        case 0x49:
            return key::i;
        case 0x4A:
            return key::j;
        case 0x4B:
            return key::k;
        case 0x4C:
            return key::l;
        case 0x4D:
            return key::m;
        case 0x4E:
            return key::n;
        case 0x4F:
            return key::o;
        case 0x50:
            return key::p;
        case 0x51:
            return key::q;
        case 0x52:
            return key::r;
        case 0x53:
            return key::s;
        case 0x54:
            return key::t;
        case 0x55:
            return key::u;
        case 0x56:
            return key::v;
        case 0x57:
            return key::w;
        case 0x58:
            return key::x;
        case 0x59:
            return key::y;
        case 0x5A:
            return key::z;
        case VK_SPACE:
            return key::space_bar;
        default:
            return key::unknown;
    }
} // function -----------------------------------------------------------------

void
forward_key_down_event_to_window (
    HWND window_handle,
    WPARAM w_param
) {
    auto& window_associations{
        grab_application_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == window_handle) {
            current_association.second->handle_key_down_event(
                translate_key_code(w_param)
            );
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_key_up_event_to_window (
    HWND window_handle,
    WPARAM w_param
) {
    auto& window_associations{
        grab_application_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == window_handle) {
            current_association.second->handle_key_up_event(
                translate_key_code(w_param)
            );
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_resize_event_to_window (
    HWND window_handle
) {
    auto& window_associations{
        grab_application_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == window_handle) {
            current_association.second->handle_resize_event();
            break;
        }
    }
} // function -----------------------------------------------------------------

bool
forward_close_event_to_window (
    HWND window_handle
) {
    auto& window_associations{
        grab_application_native_handle().window_associations
    };
    for (
        auto current_association{std::begin(window_associations)};
        current_association != std::end(window_associations);
        ++current_association
    ) {
        if (current_association->first == window_handle) {
            if (
                current_association->second->handle_close_event()
                    == close_window::yes
            ) {
                window_associations.erase(current_association);
                return true;
            } else {
                return false;
            }
        }
    }
} // function -----------------------------------------------------------------

void
forward_update_to_window (
    HWND window_handle
) {
    auto& window_associations{
        impl::grab_application_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == window_handle) {
            update_window(current_association.second);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
close_window (
    HWND window_handle
) {
    if (forward_close_event_to_window(window_handle)) {
        DestroyWindow(window_handle);
    }
} // function -----------------------------------------------------------------

LRESULT CALLBACK
window_procedure (
    HWND window_handle,
    UINT message,
    WPARAM w_param,
    LPARAM l_param
) {
    switch (message) {
        case WM_CLOSE:
            close_window(window_handle);
            return 0;
        case WM_KEYDOWN:
            forward_key_down_event_to_window(window_handle, w_param);
            return 0;
        case WM_KEYUP:
            forward_key_up_event_to_window(window_handle, w_param);
            return 0;
        case WM_PAINT:
            forward_update_to_window(window_handle);
            return 0;
        case WM_SIZE:
            forward_resize_event_to_window(window_handle);
            return 0;
        default:
            return DefWindowProcW(window_handle, message, w_param, l_param);
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

// --------------------------------------------------------------- cmp::window

// Constructors and Destructor ------------------------------------------------

window::window (
    int initial_width,
    int initial_height,
    const std::u8string& initial_title,
    window_mode initial_mode
) {
    m_native_handle.window_handle = NULL;
    open(initial_width, initial_height, initial_title, initial_mode);
} // function -----------------------------------------------------------------

// Move Operations ------------------------------------------------------------

window::window (
    window&& other
)
noexcept
    : m_native_handle{other.m_native_handle}
    , m_start_time{other.m_start_time}
    , m_last_time{other.m_last_time}
{
    if (m_native_handle.window_handle != NULL) {
        update_association();
    }

    other.m_native_handle.window_handle = NULL;
} // function -----------------------------------------------------------------

window&
window::operator = (
    window&& other
)
noexcept
{
    close();

    m_native_handle = other.m_native_handle;
    m_start_time = other.m_start_time;
    m_last_time = other.m_last_time;

    if (m_native_handle.window_handle != NULL) {
        update_association();
    }

    other.m_native_handle.window_handle = NULL;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

window_native_handle&
window::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

std::u8string
window::get_title ()
const
{
    std::wstring title_wstring;
    title_wstring.resize(GetWindowTextLengthW(m_native_handle.window_handle));
    GetWindowTextW(
        m_native_handle.window_handle,
        title_wstring.data(),
        title_wstring.size() + 1
    );
    return to_u8string(title_wstring);
} // function -----------------------------------------------------------------

void
window::set_title (
    const std::u8string& new_title
) {
    std::wstring title_wstring{to_wstring(new_title)};
    SetWindowTextW(m_native_handle.window_handle, title_wstring.data());
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

bool
window::open (
    int width,
    int height,
    const std::u8string &title,
    cmp::window_mode mode
) {
    if (m_native_handle.window_handle != NULL) {
        return false;
    }

    auto& application_native_handle{
        impl::grab_application_native_handle()
    };

    std::wstring title_wstring{to_wstring(title)};

    RECT rectangle;
    rectangle.left = 0;
    rectangle.top = 0;
    rectangle.right = width;
    rectangle.bottom = height;

    AdjustWindowRect(&rectangle, WS_OVERLAPPEDWINDOW, false);

    int window_width{rectangle.right - rectangle.left};
    int window_height{rectangle.bottom - rectangle.top};

    m_native_handle.window_handle = CreateWindowW(
        application_native_handle.window_class_name,
        title_wstring.data(),
        WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2,
        window_width,
        window_height,
        0,
        0,
        application_native_handle.application_instance_handle,
        0
    );

    if (!m_native_handle.window_handle) {
        return false;
    }

    int native_modes[] = {
        SW_SHOWNORMAL,
        SW_SHOWMAXIMIZED,
        SW_SHOWMINIMIZED
    };
    m_native_handle.show_command = native_modes[static_cast<int>(mode)];

    m_start_time = std::chrono::steady_clock::now();
    m_last_time = m_start_time;

    application_native_handle.window_associations.emplace_back(
        m_native_handle.window_handle,
        this
    );
} // function -----------------------------------------------------------------

void
window::show ()
{
    if (IsWindowVisible(m_native_handle.window_handle)) {
        return;
    }

    ShowWindow(
        m_native_handle.window_handle,
        m_native_handle.show_command
    );
    UpdateWindow(m_native_handle.window_handle);
    m_native_handle.show_command = SW_SHOWNORMAL;
} // function -----------------------------------------------------------------

void
window::hide ()
{
    ShowWindow(m_native_handle.window_handle, SW_HIDE);
} // function -----------------------------------------------------------------

void
window::close ()
{
    impl::close_window(m_native_handle.window_handle);
} // function -----------------------------------------------------------------

void
window::update (
    double delta_seconds,
    double total_seconds
) {
} // function -----------------------------------------------------------------

void
window::handle_key_down_event (
    key event_key
) {
} // function -----------------------------------------------------------------

void
window::handle_key_up_event (
    key event_key
) {
} // function -----------------------------------------------------------------

void
window::handle_resize_event ()
{
} // function -----------------------------------------------------------------

close_window
window::handle_close_event ()
{
    return close_window::yes;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
window::update () {
    std::chrono::steady_clock::time_point current_time{
        std::chrono::steady_clock::now()
    };
    std::chrono::duration<double> difference{
        std::chrono::duration_cast<
            std::chrono::duration<double>
        >(current_time - m_last_time)
    };
    double delta_seconds{difference.count()};

    m_last_time = current_time;
    difference = std::chrono::duration_cast<
        std::chrono::duration<double>
    >(current_time - m_start_time);
    double total_seconds{difference.count()};

    update(delta_seconds, total_seconds);
} // function -----------------------------------------------------------------

void
window::update_association ()
noexcept
{
    auto& window_associations{
        impl::grab_application_native_handle().window_associations
    };
    auto association_iterator{
        std::find_if(
            std::begin(window_associations),
            std::end(window_associations),
            [this] (const auto& element) {
                return element.first == m_native_handle.window_handle;
            }
        )
    };
    association_iterator->second = this;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
