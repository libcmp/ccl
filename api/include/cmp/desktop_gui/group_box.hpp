// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_GROUP_BOX_HPP_INCLUDED
#define CMP_DESKTOP_GUI_GROUP_BOX_HPP_INCLUDED

#include <string>
#include <string_view>
#include <functional>

#include <cmp/desktop_gui/widget.hpp>
#include <cmp/desktop_gui/desktop_gui_application.hpp>
#include <cmp/unicode/algorithms.hpp>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS group_box
    : public widget
{
public:
    // Constants --------------------------------------------------------------

    static constexpr native_widget_kind g_kind{
        native_widget_kind::group_box
    };

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    explicit
    group_box (
        layout& enclosing_layout
    );

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    layout&
    grab_content_layout ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    const layout&
    grab_content_layout ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    std::u8string
    get_text ()
    const;

    CMP_CONDITIONAL_EXPORT
    void
    set_text (
        std::u8string_view new_text
    );

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_preferred_width ()
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_preferred_height ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_preferred_size (
        pixval& width,
        pixval& height
    )
    const noexcept override;

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    void
    show ()
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    hide ()
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    update ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    handle_dpi_update_event (
        int old_dpi,
        int new_dpi
    )
    override;

    template <
        typename Widget,
        typename... Arguments
    >
    requires (std::derived_from<Widget, widget>)
    trusted_ptr<Widget>
    add_widget (
        Arguments&&... arguments
    ) {
        auto widget_ptr{
            m_content_layout.grab_children().emplace_back(
                std::make_unique<Widget>(
                    grab_native_handle(),
                    m_content_layout,
                    std::forward<Arguments>(arguments)...
                )
            ).get()
        };
#if (!defined(CMP_OS_LINUX_BASED) && !defined(CMP_OS_FREEBSD)) || CMP_CONFIG_USE_GTK == false
        m_content_layout.update();
#endif
        return assure(widget_ptr);
    } // function -------------------------------------------------------------

protected:
    // Protected functions ----------------------------------------------------

    void
    set_x_forcefully (
        pixval new_x
    )
    noexcept override;

    void
    set_y_forcefully (
        pixval new_y
    )
    noexcept override;

    void
    set_position_forcefully (
        pixval new_x,
        pixval new_y
    )
    noexcept override;

    void
    set_width_forcefully (
        pixval new_width
    )
    noexcept override;

    void
    set_height_forcefully (
        pixval new_height
    )
    noexcept override;

    void
    set_size_forcefully (
        pixval new_width,
        pixval new_height
    )
    noexcept override;

private:
    // Private Data -----------------------------------------------------------

    layout m_content_layout;

    // Private Functions ------------------------------------------------------

    pixval
    calculate_margin ()
    const noexcept;

    void
    update_margins ()
    noexcept;
}; // class -------------------------------------------------------------------

using group_box_truptr = trusted_ptr<group_box>;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_GROUP_BOX_HPP_INCLUDED
