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
              enclosing_layout.grab_enclosing_window_handle().window_handle,
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
    std::wstring title_wstring;
    title_wstring.resize(
        GetWindowTextLengthW(grab_native_handle().widget_handle)
    );
    GetWindowTextW(
        grab_native_handle().widget_handle,
        title_wstring.data(),
        title_wstring.size() + 1
    );
    return to_u8string(title_wstring);
} // function -----------------------------------------------------------------

void
group_box::set_text (
    std::u8string_view new_text
) {
    std::wstring title_wstring{to_wstring(new_text)};
    SetWindowTextW(grab_native_handle().widget_handle, title_wstring.data());

    if (is_dynamically_sized()) {
        apply_preferred_size();
    }
} // function -----------------------------------------------------------------

pixval
group_box::get_preferred_width ()
const noexcept
{
    return m_content_layout.get_preferred_width()
        + m_content_layout.get_left_margin()
        + m_content_layout.get_right_margin();
} // function -----------------------------------------------------------------

pixval
group_box::get_preferred_height ()
const noexcept
{
    return m_content_layout.get_preferred_height()
        + m_content_layout.get_top_margin()
        + m_content_layout.get_bottom_margin();
} // function -----------------------------------------------------------------

void
group_box::get_preferred_size (
    pixval& width,
    pixval& height
)
const noexcept
{
    m_content_layout.get_preferred_size(width, height);
    width += m_content_layout.get_left_margin()
        + m_content_layout.get_right_margin();
    height += m_content_layout.get_top_margin()
        + m_content_layout.get_bottom_margin();
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
    update_margins();
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
    m_content_layout.set_height_forcefully(new_height);
} // function -----------------------------------------------------------------

void
group_box::set_size_forcefully (
    pixval new_width,
    pixval new_height
)
noexcept
{
    widget::set_size_forcefully(new_width, new_height);
    m_content_layout.set_size_forcefully(new_width, new_height);
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

pixval
group_box::calculate_margin ()
const noexcept
{
    HWND widget_handle{grab_native_handle().widget_handle};
    HDC device_context{GetWindowDC(widget_handle)};
    HFONT font{(HFONT)GetCurrentObject(device_context, OBJ_FONT)};
    LOGFONTW log_font;
    memset(&log_font, 0, sizeof (LOGFONTW));
    GetObject(font, sizeof (LOGFONTW), &log_font);
    LONG height{std::abs(log_font.lfHeight)};
    ReleaseDC(widget_handle, device_context);
    return to_pixval(dotval{static_cast<int>(height)}, get_parent_dpi());
} // function -----------------------------------------------------------------

void
group_box::update_margins ()
noexcept
{
    const pixval margin{calculate_margin()};
    const pixval half_margin{margin / 2};

    m_content_layout.set_left_margin(half_margin);
    m_content_layout.set_top_margin(margin.get_value() * 1.5);
    m_content_layout.set_right_margin(half_margin);
    m_content_layout.set_bottom_margin(half_margin);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
