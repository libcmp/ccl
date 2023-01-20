// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_OPERATING_SYSTEM_HPP_INCLUDED
#define CMP_CORE_OPERATING_SYSTEM_HPP_INCLUDED

#if defined(_WIN32) \
    || defined(_WIN64) \
    || defined(__WIN32__) \
    || defined(__TOS_WIN__) \
    || defined(__WINDOWS__)

#   define CMP_OS_WINDOWS
#   define CMP_OS_NAME "Windows"

#elif defined(__APPLE__) \
    || defined(__MACH__)

#   define CMP_OS_MACOS
#   define CMP_OS_NAME "macOS"

#elif defined(__linux__) \
    || defined(linux) \
    || defined(__linux)

#   define CMP_OS_LINUX_BASED
#   define CMP_OS_NAME "Linux-based"

#elif defined(__FreeBSD__)

#   define CMP_OS_FREEBSD
#   define CMP_OS_NAME "FreeBSD"

#endif

#if defined(CMP_OS_MACOS) \
    || defined(CMP_OS_LINUX_BASED) \
    || defined(CMP_OS_FREEBSD)

#   define CMP_OS_UNIX_LIKE

#endif

#endif // CMP_CORE_OPERATING_SYSTEM_HPP_INCLUDED
