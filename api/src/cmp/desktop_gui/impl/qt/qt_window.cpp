// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/qt/qt_window.hpp>

namespace cmp {

namespace impl {

// Free Functions -------------------------------------------------------------

key
translate_key_code (
    Qt::Key key_code,
    Qt::KeyboardModifiers modifiers
) {
    switch (key_code) {
        case Qt::Key_F1:
            return key::f1;
        case Qt::Key_F2:
            return key::f2;
        case Qt::Key_F3:
            return key::f3;
        case Qt::Key_F4:
            return key::f4;
        case Qt::Key_F5:
            return key::f5;
        case Qt::Key_F6:
            return key::f6;
        case Qt::Key_F7:
            return key::f7;
        case Qt::Key_F8:
            return key::f8;
        case Qt::Key_F9:
            return key::f9;
        case Qt::Key_F10:
            return key::f10;
        case Qt::Key_F11:
            return key::f11;
        case Qt::Key_F12:
            return key::f12;
        case Qt::Key_F13:
            return key::f13;
        case Qt::Key_F14:
            return key::f14;
        case Qt::Key_F15:
            return key::f15;
        case Qt::Key_F16:
            return key::f16;
        case Qt::Key_F17:
            return key::f17;
        case Qt::Key_F18:
            return key::f18;
        case Qt::Key_F19:
            return key::f19;
        case Qt::Key_F20:
            return key::f20;
        case Qt::Key_F21:
            return key::f21;
        case Qt::Key_F22:
            return key::f22;
        case Qt::Key_F23:
            return key::f23;
        case Qt::Key_F24:
            return key::f24;
        case Qt::Key_0:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_0 : key::number_0;
        case Qt::Key_1:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_1 : key::number_1;
        case Qt::Key_2:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_2 : key::number_2;
        case Qt::Key_3:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_3 : key::number_3;
        case Qt::Key_4:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_4 : key::number_4;
        case Qt::Key_5:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_5 : key::number_5;
        case Qt::Key_6:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_6 : key::number_6;
        case Qt::Key_7:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_7 : key::number_7;
        case Qt::Key_8:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_8 : key::number_8;
        case Qt::Key_9:
            return modifiers.testFlag(Qt::KeypadModifier) ? key::numpad_9 : key::number_9;
        case Qt::Key_A:
            return key::a;
        case Qt::Key_B:
            return key::b;
        case Qt::Key_C:
            return key::c;
        case Qt::Key_D:
            return key::d;
        case Qt::Key_E:
            return key::e;
        case Qt::Key_F:
            return key::f;
        case Qt::Key_G:
            return key::g;
        case Qt::Key_H:
            return key::h;
        case Qt::Key_I:
            return key::i;
        case Qt::Key_J:
            return key::j;
        case Qt::Key_K:
            return key::k;
        case Qt::Key_L:
            return key::l;
        case Qt::Key_M:
            return key::m;
        case Qt::Key_N:
            return key::n;
        case Qt::Key_O:
            return key::o;
        case Qt::Key_P:
            return key::p;
        case Qt::Key_Q:
            return key::q;
        case Qt::Key_R:
            return key::r;
        case Qt::Key_S:
            return key::s;
        case Qt::Key_T:
            return key::t;
        case Qt::Key_U:
            return key::u;
        case Qt::Key_V:
            return key::v;
        case Qt::Key_W:
            return key::w;
        case Qt::Key_X:
            return key::x;
        case Qt::Key_Y:
            return key::y;
        case Qt::Key_Z:
            return key::z;
        case Qt::Key_Space:
            return key::space_bar;
        default:
            return key::unknown;
    }
} // function -----------------------------------------------------------------

void
forward_key_down_event_to_window (
    cmp_main_window* cmp_main_window_handle,
    QKeyEvent* event
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == cmp_main_window_handle) {
            key_event ev{
                key_event_type::key_down,
                translate_key_code(
                  static_cast<Qt::Key>(event->key()),
                  event->modifiers()
                )
            };
            current_association.second->handle_key_down_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_key_up_event_to_window (
    cmp_main_window* cmp_main_window_handle,
    QKeyEvent* event
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == cmp_main_window_handle) {
            key_event ev{
                key_event_type::key_up,
                translate_key_code(
                  static_cast<Qt::Key>(event->key()),
                  event->modifiers()
                )
            };
            current_association.second->handle_key_up_event(ev);
            break;
        }
    }
} // function -----------------------------------------------------------------

void
forward_resize_event_to_window (
    cmp_main_window* cmp_main_window_handle
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == cmp_main_window_handle) {
            current_association.second->update_root_layout();
            current_association.second->handle_resize_event();
            break;
        }
    }
} // function -----------------------------------------------------------------

bool
forward_close_event_to_window (
    cmp_main_window* cmp_main_window_handle
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (
        auto current_association{std::begin(window_associations)};
        current_association != std::end(window_associations);
        ++current_association
    ) {
        if (current_association->first == cmp_main_window_handle) {
            close_event ev{true};
            current_association->second->handle_close_event(ev);
            if (ev.should_close()) {
                window_associations.erase(current_association);
                return false;
            } else {
                return true;
            }
        }
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
    m_native_handle.cmp_main_window_handle = nullptr;
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
    if (m_native_handle.cmp_main_window_handle != nullptr) {
        fix_association();
    }

    other.m_native_handle.cmp_main_window_handle = nullptr;
} // function -----------------------------------------------------------------

window&
window::operator = (
    window&& other
)
noexcept
{
    if (this != &other) {
        close();

        m_native_handle = other.m_native_handle;
        m_start_time = other.m_start_time;
        m_last_time = other.m_last_time;

        if (m_native_handle.cmp_main_window_handle != nullptr) {
            fix_association();
        }

        other.m_native_handle.cmp_main_window_handle = nullptr;
    }

    return *this;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

window_native_handle&
window::grab_native_handle ()
noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

const window_native_handle&
window::grab_native_handle ()
const noexcept
{
    return m_native_handle;
} // function -----------------------------------------------------------------

std::u8string
window::get_title ()
const
{
    return to_u8string(
        m_native_handle.cmp_main_window_handle->windowTitle().toStdU16String()
    );
} // function -----------------------------------------------------------------

void
window::set_title (
    const std::u8string& new_title
) {
    m_native_handle.cmp_main_window_handle->setWindowTitle(
        QString::fromUtf8(new_title.data())
    );
} // function -----------------------------------------------------------------

layout&
window::grab_root_layout ()
noexcept
{
    return m_root_layout;
} // function -----------------------------------------------------------------

void
window::get_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    width = m_native_handle.cmp_main_window_handle->width();
    height = m_native_handle.cmp_main_window_handle->height();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

bool
window::open (
    int width,
    int height,
    const std::u8string& title,
    window_mode mode
) {
    if (m_native_handle.cmp_main_window_handle != nullptr) {
        return false;
    }

    auto& application_native_handle{dgui_app()->grab_native_handle()};

    m_native_handle.cmp_main_window_handle = new impl::cmp_main_window();
    set_title(title);
    m_native_handle.cmp_main_window_handle->resize(width, height);
    if (mode == window_mode::maximized) {
        m_native_handle.cmp_main_window_handle->setWindowState(
            Qt::WindowMaximized
        );
    } else if (mode == window_mode::minimized) {
        m_native_handle.cmp_main_window_handle->setWindowState(
            Qt::WindowMinimized
        );
    }
    m_native_handle.cmp_main_window_handle->setAttribute(Qt::WA_DeleteOnClose);

    m_root_layout.m_parent = nullptr;
    m_root_layout.set_kind(layout::kind::flow);
    m_root_layout.set_direction(layout::direction::forward);
    m_root_layout.set_axis(layout::axis::vertical);
    m_root_layout.grab_enclosing_window_handle() = grab_native_handle();

    m_start_time = std::chrono::steady_clock::now();
    m_last_time = m_start_time;

    application_native_handle.window_associations.emplace_back(
        m_native_handle.cmp_main_window_handle,
        this
    );

    return true;
} // function -----------------------------------------------------------------

void
window::show ()
{
    if (m_native_handle.cmp_main_window_handle->isVisible()) {
        return;
    }

    m_native_handle.cmp_main_window_handle->show();
} // function -----------------------------------------------------------------

void
window::hide ()
{
    m_native_handle.cmp_main_window_handle->hide();
} // function -----------------------------------------------------------------

void
window::close ()
{
    m_native_handle.cmp_main_window_handle->close();
} // function -----------------------------------------------------------------

void
window::update (
    double delta_seconds,
    double total_seconds
) {
} // function -----------------------------------------------------------------

void
window::handle_key_down_event (
    key_event& ev
) {
} // function -----------------------------------------------------------------

void
window::handle_key_up_event (
    key_event& ev
) {
} // function -----------------------------------------------------------------

void
window::handle_resize_event ()
{
} // function -----------------------------------------------------------------

void
window::handle_close_event (
    close_event& ev
) {
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

void
window::update_root_layout ()
noexcept
{
    if (!m_root_layout.is_empty()) {
        pixval width;
        pixval height;
        get_size(width, height);
        m_root_layout.set_size(width, height);
    }
} // function -----------------------------------------------------------------

void
window::fix_association ()
noexcept
{
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    auto association_iterator{
        std::find_if(
            std::begin(window_associations),
            std::end(window_associations),
            [this] (const auto& element) {
                return element.first == m_native_handle.cmp_main_window_handle;
            }
        )
    };
    association_iterator->second = this;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
