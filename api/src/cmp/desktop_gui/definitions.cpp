// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/config.hpp>
#include <cmp/core/platform.hpp>

#if CMP_CONFIG_HEADER_ONLY == false && CMP_CONFIG_DESKTOP_GUI_PACKAGE_EXCLUDED == false
#   include <cmp/desktop_gui/impl/common/common_desktop_gui_application.cpp>
#   include <cmp/desktop_gui/impl/common/common_window.cpp>
#   if defined(CMP_OS_WINDOWS)
#       include <cmp/desktop_gui/impl/windows/windows_desktop_gui_application.cpp>
#       include <cmp/desktop_gui/impl/windows/windows_window.cpp>
#   elif defined(CMP_OS_MACOS)
#       include <cmp/desktop_gui/impl/macos/macos_desktop_gui_application.mm>
#       include <cmp/desktop_gui/impl/macos/macos_window.mm>
#   elif defined(CMP_OS_LINUX_BASED) || defined(CMP_OS_FREEBSD)
#       include <cmp/desktop_gui/impl/gtk/gtk_desktop_gui_application.cpp>
#       include <cmp/desktop_gui/impl/gtk/gtk_window.cpp>
#   endif
#   include <cmp/desktop_gui/close_event.cpp>
#   include <cmp/desktop_gui/event.cpp>
#   include <cmp/desktop_gui/general.cpp>
#   include <cmp/desktop_gui/key_event.cpp>
#endif
