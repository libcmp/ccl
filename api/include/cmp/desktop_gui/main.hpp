// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_MAIN_HPP_INCLUDED
#define CMP_DESKTOP_GUI_MAIN_HPP_INCLUDED

#include <cmp/core/platform.hpp>

#if defined(CMP_OS_WINDOWS) && !defined(CMP_COMPILER_GCC)
#pragma comment(linker, "/ENTRY:mainCRTStartup")
#endif // CMP_OS_WINDOWS

#endif // CMP_DESKTOP_GUI_MAIN_HPP_INCLUDED
