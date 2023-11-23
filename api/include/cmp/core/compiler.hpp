// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_COMPILER_HPP_INCLUDED
#define CMP_CORE_COMPILER_HPP_INCLUDED

#define CMP_DO_PRAGMA(p) _Pragma(#p)

#if defined(__clang__)

#   define CMP_COMPILER_CLANG
#   define CMP_COMPILER_NAME "Clang"

#   define CMP_DISABLE_WARNING_PUSH CMP_DO_PRAGMA(GCC diagnostic push)
#   define CMP_DISABLE_WARNING_POP CMP_DO_PRAGMA(GCC diagnostic pop)
#   define CMP_DISABLE_WARNING(id) CMP_DO_PRAGMA(GCC diagnostic ignored id)

#   define CMP_WARNING_ID_MACRO_REDEFINED "-Wmacro-redefined"

#elif defined(__GNUC__)

#   define CMP_COMPILER_GCC
#   define CMP_COMPILER_NAME "GCC"

#   define CMP_DISABLE_WARNING_PUSH CMP_DO_PRAGMA(GCC diagnostic push)
#   define CMP_DISABLE_WARNING_POP CMP_DO_PRAGMA(GCC diagnostic pop)
#   define CMP_DISABLE_WARNING(id) CMP_DO_PRAGMA(GCC diagnostic ignored id)

#   define CMP_WARNING_ID_MACRO_REDEFINED "-Wbuiltin-macro-redefined"

#elif defined(_MSC_VER)

#   define CMP_COMPILER_MSVC
#   define CMP_COMPILER_NAME "Visual C++"

#   define CMP_DISABLE_WARNING_PUSH CMP_DO_PRAGMA(warning(push))
#   define CMP_DISABLE_WARNING_POP CMP_DO_PRAGMA(warning(pop))
#   define CMP_DISABLE_WARNING(id) CMP_DO_PRAGMA(warning(disable: id))

#   define CMP_WARNING_ID_MACRO_REDEFINED 4005

#else

#   define CMP_COMPILER_UNSUPPORTED
#   define CMP_COMPILER_NAME "<Unsupported>"

#endif

#endif // CMP_CORE_COMPILER_HPP_INCLUDED
