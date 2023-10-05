// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <gdk/gdkkeysyms.h>

#include <cmp/desktop_gui/impl/gtk/gtk_window.hpp>

namespace cmp {

namespace impl {

void
update_window (
    window* w
) {
    w->update();
} // function -----------------------------------------------------------------

key
translate_key_code (
    guint key_code
) {
    switch (key_code) {
        case GDK_KEY_F1:
            return key::f1;
        case GDK_KEY_F2:
            return key::f2;
        case GDK_KEY_F3:
            return key::f3;
        case GDK_KEY_F4:
            return key::f4;
        case GDK_KEY_F5:
            return key::f5;
        case GDK_KEY_F6:
            return key::f6;
        case GDK_KEY_F7:
            return key::f7;
        case GDK_KEY_F8:
            return key::f8;
        case GDK_KEY_F9:
            return key::f9;
        case GDK_KEY_F10:
            return key::f10;
        case GDK_KEY_F11:
            return key::f11;
        case GDK_KEY_F12:
            return key::f12;
        case GDK_KEY_F13:
            return key::f13;
        case GDK_KEY_F14:
            return key::f14;
        case GDK_KEY_F15:
            return key::f15;
        case GDK_KEY_F16:
            return key::f16;
        case GDK_KEY_F17:
            return key::f17;
        case GDK_KEY_F18:
            return key::f18;
        case GDK_KEY_F19:
            return key::f19;
        case GDK_KEY_F20:
            return key::f20;
        case GDK_KEY_F21:
            return key::f21;
        case GDK_KEY_F22:
            return key::f22;
        case GDK_KEY_F23:
            return key::f23;
        case GDK_KEY_F24:
            return key::f24;
        case GDK_KEY_0:
            return key::number_0;
        case GDK_KEY_1:
            return key::number_1;
        case GDK_KEY_2:
            return key::number_2;
        case GDK_KEY_3:
            return key::number_3;
        case GDK_KEY_4:
            return key::number_4;
        case GDK_KEY_5:
            return key::number_5;
        case GDK_KEY_6:
            return key::number_6;
        case GDK_KEY_7:
            return key::number_7;
        case GDK_KEY_8:
            return key::number_8;
        case GDK_KEY_9:
            return key::number_9;
        case GDK_KEY_KP_0:
            return key::numpad_0;
        case GDK_KEY_KP_1:
            return key::numpad_1;
        case GDK_KEY_KP_2:
            return key::numpad_2;
        case GDK_KEY_KP_3:
            return key::numpad_3;
        case GDK_KEY_KP_4:
            return key::numpad_4;
        case GDK_KEY_KP_5:
            return key::numpad_5;
        case GDK_KEY_KP_6:
            return key::numpad_6;
        case GDK_KEY_KP_7:
            return key::numpad_7;
        case GDK_KEY_KP_8:
            return key::numpad_8;
        case GDK_KEY_KP_9:
            return key::numpad_9;
        case GDK_KEY_A:
        case GDK_KEY_a:
            return key::a;
        case GDK_KEY_B:
        case GDK_KEY_b:
            return key::b;
        case GDK_KEY_C:
        case GDK_KEY_c:
            return key::c;
        case GDK_KEY_D:
        case GDK_KEY_d:
            return key::d;
        case GDK_KEY_E:
        case GDK_KEY_e:
            return key::e;
        case GDK_KEY_F:
        case GDK_KEY_f:
            return key::f;
        case GDK_KEY_G:
        case GDK_KEY_g:
            return key::g;
        case GDK_KEY_H:
        case GDK_KEY_h:
            return key::h;
        case GDK_KEY_I:
        case GDK_KEY_i:
            return key::i;
        case GDK_KEY_J:
        case GDK_KEY_j:
            return key::j;
        case GDK_KEY_K:
        case GDK_KEY_k:
            return key::k;
        case GDK_KEY_L:
        case GDK_KEY_l:
            return key::l;
        case GDK_KEY_M:
        case GDK_KEY_m:
            return key::m;
        case GDK_KEY_N:
        case GDK_KEY_n:
            return key::n;
        case GDK_KEY_O:
        case GDK_KEY_o:
            return key::o;
        case GDK_KEY_P:
        case GDK_KEY_p:
            return key::p;
        case GDK_KEY_Q:
        case GDK_KEY_q:
            return key::q;
        case GDK_KEY_R:
        case GDK_KEY_r:
            return key::r;
        case GDK_KEY_S:
        case GDK_KEY_s:
            return key::s;
        case GDK_KEY_T:
        case GDK_KEY_t:
            return key::t;
        case GDK_KEY_U:
        case GDK_KEY_u:
            return key::u;
        case GDK_KEY_V:
        case GDK_KEY_v:
            return key::v;
        case GDK_KEY_W:
        case GDK_KEY_w:
            return key::w;
        case GDK_KEY_X:
        case GDK_KEY_x:
            return key::x;
        case GDK_KEY_Y:
        case GDK_KEY_y:
            return key::y;
        case GDK_KEY_Z:
        case GDK_KEY_z:
            return key::z;
        case GDK_KEY_space:
            return key::space_bar;
        default:
            return key::unknown;
    }
} // function -----------------------------------------------------------------

gboolean
forward_key_down_event_to_window (
    GtkEventControllerKey* controller,
    guint keyval,
    guint keycode,
    GdkModifierType state,
    gpointer user_data
) {
    GtkWidget* gtk_application_window{
        gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(controller))
    };
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == gtk_application_window) {
            current_association.second->handle_key_down_event(
                translate_key_code(keyval)
            );
            break;
        }
    }
    return TRUE;
} // function -----------------------------------------------------------------

gboolean
forward_key_up_event_to_window (
    GtkEventControllerKey* controller,
    guint keyval,
    guint keycode,
    GdkModifierType state,
    gpointer user_data
) {
    GtkWidget* gtk_application_window{
        gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(controller))
    };
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == gtk_application_window) {
            current_association.second->handle_key_up_event(
                translate_key_code(keyval)
            );
            break;
        }
    }
    return TRUE;
} // function -----------------------------------------------------------------

void
forward_resize_event_to_window (
    GtkWidget* gtk_application_window
) {
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
    };
    for (const auto& current_association : window_associations) {
        if (current_association.first == gtk_application_window) {
            current_association.second->handle_resize_event();
            break;
        }
    }
} // function -----------------------------------------------------------------

gboolean
forward_close_event_to_window (
    GtkWindow* gtk_application_window,
    gpointer user_data
) {
    auto window_handle{GTK_WIDGET(gtk_application_window)};
    auto& window_associations{
        dgui_app()->grab_native_handle().window_associations
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
                return FALSE;
            } else {
                return TRUE;
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
    m_native_handle.gtk_application_window = NULL;
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
    if (m_native_handle.gtk_application_window != NULL) {
        fix_association();
    }

    other.m_native_handle.gtk_application_window = NULL;
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

    if (m_native_handle.gtk_application_window != NULL) {
        fix_association();
    }

    other.m_native_handle.gtk_application_window = NULL;

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
    const gchar* title_ptr{
        gtk_window_get_title(
            GTK_WINDOW(m_native_handle.gtk_application_window)
        )
    };
    std::u8string title;
    if (title_ptr == NULL) {
        return title;
    }
    gchar current_code_unit;
    while ((current_code_unit = *title_ptr) != 0) {
        title.push_back(current_code_unit);
        ++title_ptr;
    }
    return title;
} // function -----------------------------------------------------------------

void
window::set_title (
    const std::u8string& new_title
) {
    gtk_window_set_title(
        GTK_WINDOW(m_native_handle.gtk_application_window),
        reinterpret_cast<const gchar*>(new_title.data())
    );
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

bool
window::open (
    int width,
    int height,
    const std::u8string& title,
    window_mode mode
) {
    if (m_native_handle.gtk_application_window != NULL) {
        return false;
    }

    auto& application_native_handle{dgui_app()->grab_native_handle()};

    m_native_handle.gtk_application_window = gtk_application_window_new(
        application_native_handle.gtk_application
    );
    set_title(title);
    gtk_window_set_default_size(
        GTK_WINDOW(m_native_handle.gtk_application_window),
        width,
        height
    );
    if (mode == window_mode::maximized) {
        gtk_window_maximize(
            GTK_WINDOW(m_native_handle.gtk_application_window)
        );
    } else if (mode == window_mode::minimized) {
        gtk_window_minimize(
            GTK_WINDOW(m_native_handle.gtk_application_window)
        );
    }
    g_signal_connect(
        GTK_WIDGET(m_native_handle.gtk_application_window),
        "notify::default-width",
        G_CALLBACK(impl::forward_resize_event_to_window),
        NULL
    );
    g_signal_connect(
        GTK_WIDGET(m_native_handle.gtk_application_window),
        "notify::default-height",
        G_CALLBACK(impl::forward_resize_event_to_window),
        NULL
    );
    g_signal_connect(
        GTK_WIDGET(m_native_handle.gtk_application_window),
        "close-request",
        G_CALLBACK(impl::forward_close_event_to_window),
        NULL
    );

    m_controller = gtk_event_controller_key_new();
    gtk_widget_add_controller(
        m_native_handle.gtk_application_window,
        m_controller
    );
    g_signal_connect(
        m_controller,
        "key-released",
        G_CALLBACK(impl::forward_key_up_event_to_window),
        NULL
    );
    g_signal_connect(
        m_controller,
        "key-pressed",
        G_CALLBACK(impl::forward_key_down_event_to_window),
        NULL
    );

    m_start_time = std::chrono::steady_clock::now();
    m_last_time = m_start_time;

    application_native_handle.window_associations.emplace_back(
        m_native_handle.gtk_application_window,
        this
    );

    return true;
} // function -----------------------------------------------------------------

void
window::show ()
{
    if (gtk_widget_is_visible(m_native_handle.gtk_application_window)) {
        return;
    }

    gtk_window_present(GTK_WINDOW(m_native_handle.gtk_application_window));
} // function -----------------------------------------------------------------

void
window::hide ()
{
    gtk_widget_set_visible(m_native_handle.gtk_application_window, FALSE);
} // function -----------------------------------------------------------------

void
window::close ()
{
    gtk_window_close(GTK_WINDOW(m_native_handle.gtk_application_window));
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
                return element.first == m_native_handle.gtk_application_window;
            }
        )
    };
    association_iterator->second = this;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
