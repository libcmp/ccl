// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_TYPE_TRAITS_HPP_INCLUDED
#define CMP_UNICODE_TYPE_TRAITS_HPP_INCLUDED

#include <type_traits>
#include <string>

#include <cmp/core/config.hpp>
#include <cmp/core/type_traits.hpp>

namespace cmp {

template <
    typename T,
    std::size_t Size = sizeof (T) / sizeof (char8_t)
>
constexpr bool is_writable_utf8_string_v{
    std::is_same_v<std::remove_volatile_t<T>, std::u8string>
        || std::is_same_v<T, char8_t*>
        || std::is_same_v<T, char8_t* const>
        || std::is_same_v<T, volatile char8_t*>
        || std::is_same_v<T, volatile char8_t* const>
        || std::is_same_v<T, char8_t[Size]>
        || std::is_same_v<T, volatile char8_t[Size]>
};

template <
    typename T,
    std::size_t Size = sizeof (T) / sizeof (char16_t)
>
constexpr bool is_writable_utf16_string_v{
    std::is_same_v<std::remove_volatile_t<T>, std::u16string>
        || std::is_same_v<T, char16_t*>
        || std::is_same_v<T, char16_t* const>
        || std::is_same_v<T, volatile char16_t*>
        || std::is_same_v<T, volatile char16_t* const>
        || std::is_same_v<T, char16_t[Size]>
        || std::is_same_v<T, volatile char16_t[Size]>
};

template <
    typename T,
    std::size_t Size = sizeof (T) / sizeof (char32_t)
>
constexpr bool is_writable_utf32_string_v{
    std::is_same_v<std::remove_volatile_t<T>, std::u32string>
        || std::is_same_v<T, char32_t*>
        || std::is_same_v<T, char32_t* const>
        || std::is_same_v<T, volatile char32_t*>
        || std::is_same_v<T, volatile char32_t* const>
        || std::is_same_v<T, char32_t[Size]>
        || std::is_same_v<T, volatile char32_t[Size]>
};

template <
    typename T,
    std::size_t Size = sizeof (T) / sizeof (char8_t)
>
constexpr bool is_utf8_string_v{
    is_writable_utf8_string_v<T>
        || std::is_same_v<std::remove_cv_t<T>, std::u8string_view>
        || std::is_same_v<std::remove_volatile_t<T>, const std::u8string>
        || std::is_same_v<T, const char8_t*>
        || std::is_same_v<T, const char8_t* const>
        || std::is_same_v<T, const volatile char8_t*>
        || std::is_same_v<T, const volatile char8_t* const>
        || std::is_same_v<T, const char8_t[Size]>
        || std::is_same_v<T, const volatile char8_t[Size]>
};

template <
    typename T,
    std::size_t Size = sizeof (T) / sizeof (char16_t)
>
constexpr bool is_utf16_string_v{
    is_writable_utf16_string_v<T>
        || std::is_same_v<std::remove_cv_t<T>, std::u16string_view>
        || std::is_same_v<std::remove_volatile_t<T>, const std::u16string>
        || std::is_same_v<T, const char16_t*>
        || std::is_same_v<T, const char16_t* const>
        || std::is_same_v<T, const volatile char16_t*>
        || std::is_same_v<T, const volatile char16_t* const>
        || std::is_same_v<T, const char16_t[Size]>
        || std::is_same_v<T, const volatile char16_t[Size]>
};

template <
    typename T,
    std::size_t Size = sizeof (T) / sizeof (char32_t)
>
constexpr bool is_utf32_string_v{
    is_writable_utf32_string_v<T>
        || std::is_same_v<std::remove_cv_t<T>, std::u32string_view>
        || std::is_same_v<std::remove_volatile_t<T>, const std::u32string>
        || std::is_same_v<T, const char32_t*>
        || std::is_same_v<T, const char32_t* const>
        || std::is_same_v<T, const volatile char32_t*>
        || std::is_same_v<T, const volatile char32_t* const>
        || std::is_same_v<T, const char32_t[Size]>
        || std::is_same_v<T, const volatile char32_t[Size]>
};

template <
    typename T
>
constexpr bool is_writable_unicode_string_v{
    is_writable_utf8_string_v<T>
        || is_writable_utf16_string_v<T>
        || is_writable_utf32_string_v<T>
};

template <
    typename T
>
constexpr bool is_unicode_string_v{
    is_utf8_string_v<T>
        || is_utf16_string_v<T>
        || is_utf32_string_v<T>
};

template <
    typename T
>
constexpr bool is_unicode_string_view_v{
    std::is_same_v<std::remove_cv_t<T>, std::u8string_view>
        || std::is_same_v<std::remove_cv_t<T>, std::u16string_view>
        || std::is_same_v<std::remove_cv_t<T>, std::u32string_view>
};

template <
    typename T
>
constexpr bool is_writable_raii_unicode_string_v{
    is_writable_unicode_string_v<T>
        && !is_unicode_string_view_v<T>
        && !std::is_pointer_v<std::decay_t<T>>
};

template <
    typename T
>
constexpr bool is_raii_unicode_string_v{
    is_unicode_string_v<T>
        && !is_unicode_string_view_v<T>
        && !std::is_pointer_v<std::decay_t<T>>
};

} // namespace ----------------------------------------------------------------

#endif // CMP_UNICODE_TYPE_TRAITS_HPP_INCLUDED
