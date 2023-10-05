// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_COMMON_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
#define CMP_DESKTOP_GUI_COMMON_DESKTOP_GUI_APPLICATION_HPP_INCLUDED

#include <cmp/core/platform.hpp>

#if defined(CMP_OS_WINDOWS)
#   include <cmp/desktop_gui/impl/windows/windows_desktop_gui_application.hpp>
#elif defined(CMP_OS_MACOS)
#   include <cmp/desktop_gui/impl/macos/macos_desktop_gui_application.hpp>
#elif defined(CMP_OS_LINUX_BASED)
#   include <cmp/desktop_gui/impl/gtk/gtk_desktop_gui_application.hpp>
#endif

namespace cmp {

CMP_LIBRARY_NAME
desktop_gui_application*
dgui_app ()
noexcept;

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_COMMON_DESKTOP_GUI_APPLICATION_HPP_INCLUDED
