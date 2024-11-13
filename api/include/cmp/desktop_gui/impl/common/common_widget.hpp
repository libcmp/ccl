// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_COMMON_WIDGET_HPP_INCLUDED
#define CMP_DESKTOP_GUI_COMMON_WIDGET_HPP_INCLUDED

#if defined(CMP_OS_WINDOWS)
#include <windowsx.h>
#include <commctrl.h>
#endif

#include <cmp/desktop_gui/window_native_handle.hpp>
#include <cmp/desktop_gui/widget_native_handle.hpp>
#include <cmp/desktop_gui/window_element.hpp>

namespace cmp {

namespace impl {

enum class native_widget_kind {
    label,
    push_button,
    check_box,
    radio_button,
    group_box
}; // enum --------------------------------------------------------------------

widget_native_handle
create_widget (
    const window_native_handle& parent_window,
    native_widget_kind kind
)
noexcept;

template <
    typename... Args
>
void
noop (
    Args... args
)
noexcept;

} // namespace ----------------------------------------------------------------

class CMP_CONDITIONAL_EXPORT_CLASS widget
    : public window_element
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_EXPORT
    widget (
        const window_native_handle& handle
    );

    ~widget ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    widget_native_handle&
    grab_native_handle ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    const widget_native_handle&
    grab_native_handle ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_x ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_x (
        pixval new_x
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_y ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_y (
        pixval new_y
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_position (
        pixval& x,
        pixval& y
    )
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_position (
        pixval new_x,
        pixval new_y
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_width ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_width (
        pixval new_width
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_height ()
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_height (
        pixval new_height
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    get_size (
        pixval& width,
        pixval& height
    )
    const noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    set_size (
        pixval new_width,
        pixval new_height
    )
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    pixval
    get_preferred_width ()
    const noexcept override;

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

    CMP_CONDITIONAL_EXPORT
    void
    apply_preferred_size ()
    noexcept;

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    void
    show ()
    noexcept override;

    CMP_CONDITIONAL_EXPORT
    void
    hide ()
    noexcept override;

protected:
    // Protected Functions ----------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    explicit
    widget (
        widget_native_handle&& handle
    );

#if defined(CMP_OS_WINDOWS)
    int
    get_parent_dpi ()
    const noexcept;
#endif
private:
    // Private Data -----------------------------------------------------------

    widget_native_handle m_native_handle;

    // Private Functions ------------------------------------------------------
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if defined(CMP_OS_WINDOWS)
#   include <ShellScalingApi.h>
#   pragma comment(linker,"\"/manifestdependency:type='win32' \
        name='Microsoft.Windows.Common-Controls' \
        version='6.0.0.0' \
        processorArchitecture='*' \
        publicKeyToken='6595b64144ccf1df' \
        language='*'\"")
#   pragma comment(lib,"Shcore.lib")
#   pragma comment(lib,"Comctl32.lib")
#endif

#endif // CMP_DESKTOP_GUI_COMMON_WIDGET_HPP_INCLUDED
