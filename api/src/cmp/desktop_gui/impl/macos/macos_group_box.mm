// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/group_box.hpp>

namespace cmp {

// ------------------------------------------------------------ cmp::group_box

// Constructors and Destructor ------------------------------------------------

group_box::group_box (
    layout& enclosing_layout
)
    : widget{
          enclosing_layout,
          impl::create_widget(
              enclosing_layout.grab_enclosing_window_handle()
                  .cmp_window_handle,
              native_widget_kind::group_box
          )
      }
    , m_content_layout{
          enclosing_layout.grab_enclosing_window_handle(),
          layout::kind::flow,
          layout::axis::vertical,
          layout::direction::forward
      }
{
    update_margins();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

layout&
group_box::grab_content_layout ()
noexcept
{
    return m_content_layout;
} // function -----------------------------------------------------------------

const layout&
group_box::grab_content_layout ()
const noexcept
{
    return m_content_layout;
} // function -----------------------------------------------------------------

std::u8string
group_box::get_text ()
const
{
    std::u8string result;
    for (
        const char* current_character{
            [[reinterpret_cast<NSBox*>(grab_native_handle().widget_handle) title]
                UTF8String
            ]
        };
        *current_character != '\0';
        ++current_character
    ) {
        result.push_back(*current_character);
    }
    return result;
} // function -----------------------------------------------------------------

void
group_box::set_text (
    std::u8string_view new_text
) {
    [reinterpret_cast<NSBox*>(grab_native_handle().widget_handle) setTitle:
        [NSString stringWithUTF8String:
            reinterpret_cast<const char*>(new_text.data())
        ]
    ];
} // function -----------------------------------------------------------------

pixval
group_box::get_preferred_width ()
const noexcept
{
    return m_content_layout.get_preferred_width();
} // function -----------------------------------------------------------------

pixval
group_box::get_preferred_height ()
const noexcept
{
    return m_content_layout.get_preferred_height() + calculate_margin() * 2;
} // function -----------------------------------------------------------------

void
group_box::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    m_content_layout.get_preferred_size(width, height);
    height += calculate_margin() * 2;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

void
group_box::show ()
noexcept
{
    widget::show();
    m_content_layout.show();
} // function -----------------------------------------------------------------

void
group_box::hide ()
noexcept
{
    widget::hide();
    m_content_layout.hide();
} // function -----------------------------------------------------------------

void
group_box::update ()
noexcept
{
    m_content_layout.update();
} // function -----------------------------------------------------------------

void
group_box::handle_dpi_update_event (
    int old_dpi,
    int new_dpi
) {
    widget::handle_dpi_update_event(old_dpi, new_dpi);
    m_content_layout.handle_dpi_update_event(old_dpi, new_dpi);
} // function -----------------------------------------------------------------

// Protected functions --------------------------------------------------------

void
group_box::set_x_forcefully (
    pixval new_x
)
noexcept
{
    widget::set_x_forcefully(new_x);
} // function -----------------------------------------------------------------

void
group_box::set_y_forcefully (
    pixval new_y
)
noexcept
{
    widget::set_y_forcefully(new_y);
} // function -----------------------------------------------------------------

void
group_box::set_position_forcefully (
    pixval new_x,
    pixval new_y
)
noexcept
{
    widget::set_position_forcefully(new_x, new_y);
} // function -----------------------------------------------------------------

void
group_box::set_width_forcefully (
    pixval new_width
)
noexcept
{
    widget::set_width_forcefully(new_width);
    m_content_layout.set_width_forcefully(new_width);
} // function -----------------------------------------------------------------

void
group_box::set_height_forcefully (
    pixval new_height
)
noexcept
{
    widget::set_height_forcefully(new_height);
    m_content_layout.set_height_forcefully(new_height - calculate_margin());
} // function -----------------------------------------------------------------

void
group_box::set_size_forcefully (
    pixval new_width,
    pixval new_height
)
noexcept
{
    widget::set_size_forcefully(new_width, new_height);
    m_content_layout.set_size_forcefully(
        new_width,
        new_height - calculate_margin()
    );
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

pixval
group_box::calculate_margin ()
const noexcept
{
    return 20;
    auto nsbox{reinterpret_cast<NSBox*>(grab_native_handle().widget_handle)};
    NSRect box_frame{[nsbox frame]};
    NSRect content_frame{[[nsbox contentView] frame]};
    return box_frame.size.height - content_frame.size.height;
} // function -----------------------------------------------------------------

void
group_box::update_margins ()
noexcept
{
    auto nsbox{reinterpret_cast<NSBox*>(grab_native_handle().widget_handle)};
    [nsbox setContentViewMargins: NSSize{0, 0}];
    m_content_layout.set_right_margin(8);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
