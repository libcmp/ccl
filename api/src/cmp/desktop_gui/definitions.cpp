// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/config.hpp>
#include <cmp/core/operating_system.hpp>

#if CMP_CONFIG_HEADER_ONLY == false && CMP_CONFIG_DESKTOP_GUI_PACKAGE_EXCLUDED == false
#   if defined(CMP_OS_MACOS)
#       include <cmp/desktop_gui/impl/macos/macos_desktop_gui_application.mm>
#       include <cmp/desktop_gui/impl/macos/macos_window.mm>
#   endif
#   include <cmp/desktop_gui/general.cpp>
#endif
