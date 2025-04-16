// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_COMMON_WIDGET_HPP_INCLUDED
#define CMP_DESKTOP_GUI_COMMON_WIDGET_HPP_INCLUDED

#include <cmp/desktop_gui/window_native_handle.hpp>
#include <cmp/desktop_gui/widget_native_handle.hpp>
#include <cmp/desktop_gui/layout.hpp>

#if defined(CMP_OS_WINDOWS)
#include <windowsx.h>
#include <commctrl.h>
#endif

namespace cmp {

class widget;

enum class native_widget_kind {
    label,
    push_button,
    check_box,
    radio_button,
    group_box
}; // enum --------------------------------------------------------------------

namespace impl {

#if defined(CMP_OS_WINDOWS)
[[nodiscard]]
CMP_CONDITIONAL_EXPORT
widget_native_handle
create_widget (
    const HWND& parent_handle,
    native_widget_kind kind
)
noexcept;
#elif defined(CMP_OS_MACOS)
[[nodiscard]]
CMP_CONDITIONAL_EXPORT
widget_native_handle
create_widget (
    NSResponder* parent_handle,
    native_widget_kind kind
)
noexcept;
#elif defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
#   if CMP_CONFIG_USE_QT == true
[[nodiscard]]
CMP_CONDITIONAL_EXPORT
widget_native_handle
create_widget (
    QWidget* parent_handle,
    native_widget_kind kind
)
noexcept;
#   else
[[nodiscard]]
CMP_CONDITIONAL_EXPORT
widget_native_handle
create_widget (
    GtkWidget* parent_handle,
    native_widget_kind kind
)
noexcept;
#   endif
#endif

template <
    typename... Args
>
void
noop (
    Args... args
)
noexcept;

#if defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
#   if CMP_CONFIG_USE_QT == true
widget*
find_widget (
    QWidget* widget_handle,
    const std::vector<std::unique_ptr<window_element>>& window_elements
);
#   else
widget*
find_widget (
    GtkWidget* widget_handle,
    const std::vector<std::unique_ptr<window_element>>& window_elements
);
#   endif
#endif

} // namespace ----------------------------------------------------------------

class CMP_CONDITIONAL_EXPORT_CLASS widget
    : public window_element
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    explicit
    widget (
        layout& parent
    );

    ~widget ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    widget_native_handle&
    grab_native_handle ()
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const widget_native_handle&
    grab_native_handle ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    layout&
    grab_enclosing_layout ()
    noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const layout&
    grab_enclosing_layout ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_x ()
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_y ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_position (
        pixval& x,
        pixval& y
    )
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_width ()
    const noexcept override;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    pixval
    get_height ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_size (
        pixval& width,
        pixval& height
    )
    const noexcept override;

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
    handle_dpi_update_event (
        int old_dpi,
        int new_dpi
    )
    override;

    // Friends ----------------------------------------------------------------

    friend class layout;

protected:
    // Protected Functions ----------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    explicit
    widget (
        layout& parent,
        widget_native_handle&& handle
    );

    CMP_CONDITIONAL_EXPORT
    bool
    is_geometry_modification_prohibited ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_x_forcefully (
        pixval new_x
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_y_forcefully (
        pixval new_y
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_position_forcefully (
        pixval new_x,
        pixval new_y
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_width_forcefully (
        pixval new_width
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_height_forcefully (
        pixval new_height
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_size_forcefully (
        pixval new_width,
        pixval new_height
    )
    noexcept override;

#if defined(CMP_OS_MACOS) || defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
    static
    void
    get_preferred_size_generically (
        const widget_native_handle& native_handle,
        pixval& width,
        pixval& height
    )
    noexcept;
#endif

#if defined(CMP_OS_WINDOWS)
    [[nodiscard]]
    int
    get_parent_dpi ()
    const noexcept;
#endif

private:
    // Private Data -----------------------------------------------------------

    widget_native_handle m_native_handle;
    layout* m_enclosing_layout;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_COMMON_WIDGET_HPP_INCLUDED
