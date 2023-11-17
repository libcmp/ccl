// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/desktop_gui/window.hpp>
#include <cmp/io/uio.hpp>

class demo_window
    : public cmp::window
{
public:
    demo_window ()
        : cmp::window{
              400,
              300,
              u8"Demo Window",
              cmp::window_mode::standard
          }
        , m_show_counter{false}
    {
        set_title(get_title() + u8" ¯\\_(ツ)_/¯");
    } // function -------------------------------------------------------------

    void
    update (
        double delta_seconds,
        double total_seconds
    )
    override
    {
        if (m_show_counter) {
            set_title(
                cmp::format_floating_point<std::u8string>(
                    total_seconds,
                    cmp::floating_point_format{
                        10,
                        cmp::sign_status::only_when_negative,
                        cmp::thousands_separator::comma,
                        cmp::radix_character::period,
                        cmp::radix_place_limit::exactly_equal,
                        1
                    }
                )
            );
        }
    } // function -------------------------------------------------------------

    void
    handle_key_down_event (
        cmp::key_event& ev
    )
    override
    {
        cmp::key event_key{ev.get_key()};
        cmp::uout << cmp::to_u8string(event_key) << " down.\n";
        if (event_key == cmp::key::space_bar) {
            if (m_show_counter) {
                m_show_counter = false;
                set_title(u8"Demo Window ¯\\_(ツ)_/¯");
            } else {
                m_show_counter = true;
            }
        }
    } // function -------------------------------------------------------------

    void
    handle_key_up_event (
        cmp::key_event& ev
    )
    override
    {
        cmp::uout << cmp::to_u8string(ev.get_key()) << " up.\n";
    } // function -------------------------------------------------------------

    void
    handle_resize_event ()
    override
    {
        cmp::uout << "Resized.\n";
    } // function -------------------------------------------------------------

    void
    handle_close_event (
        cmp::close_event& ev
    )
    override
    {
        cmp::uout << "Closing.\n";
    } // function -------------------------------------------------------------

private:
    // Private Data -----------------------------------------------------------

    bool m_show_counter;
}; // class -------------------------------------------------------------------

int
main (
    int argc,
    char** argv
) {
    cmp::desktop_gui_application app{argc, argv};
    demo_window window;
    window.show();
    return app.run();
} // function -----------------------------------------------------------------
