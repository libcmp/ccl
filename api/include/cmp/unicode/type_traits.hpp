// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_TYPE_TRAITS_HPP_INCLUDED
#define CMP_UNICODE_TYPE_TRAITS_HPP_INCLUDED

#include <string>
#include <type_traits>

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/core/type_traits.hpp>

namespace cmp {

template <
    typename T,
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char)>
>
constexpr bool is_writable_char_string_v{
    std::is_same_v<std::remove_volatile_t<T>, std::string>
        || std::is_same_v<T, char*>
        || std::is_same_v<T, char* const>
        || std::is_same_v<T, volatile char*>
        || std::is_same_v<T, volatile char* const>
        || std::is_same_v<T, char[Size]>
        || std::is_same_v<T, volatile char[Size]>
};

template <
    typename T,
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char8_t)>
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
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char16_t)>
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
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char32_t)>
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
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (wchar_t)>
>
constexpr bool is_writable_wide_string_v{
    std::is_same_v<std::remove_volatile_t<T>, std::wstring>
        || std::is_same_v<T, wchar_t*>
        || std::is_same_v<T, wchar_t* const>
        || std::is_same_v<T, volatile wchar_t*>
        || std::is_same_v<T, volatile wchar_t* const>
        || std::is_same_v<T, wchar_t[Size]>
        || std::is_same_v<T, volatile wchar_t[Size]>
};

template <
    typename T,
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char)>
>
constexpr bool is_char_string_v{
    is_writable_char_string_v<T>
        || std::is_same_v<std::remove_cv_t<T>, std::string_view>
        || std::is_same_v<std::remove_volatile_t<T>, const std::string>
        || std::is_same_v<T, const char*>
        || std::is_same_v<T, const char* const>
        || std::is_same_v<T, const volatile char*>
        || std::is_same_v<T, const volatile char* const>
        || std::is_same_v<T, const char[Size]>
        || std::is_same_v<T, const volatile char[Size]>
};

template <
    typename T,
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char8_t)>
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
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char16_t)>
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
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (char32_t)>
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
    typename T,
    std::size_t Size
        = constant_max_v<std::size_t, 1, sizeof (T) / sizeof (wchar_t)>
>
constexpr bool is_wide_string_v{
    is_writable_wide_string_v<T>
        || std::is_same_v<std::remove_cv_t<T>, std::wstring_view>
        || std::is_same_v<std::remove_volatile_t<T>, const std::wstring>
        || std::is_same_v<T, const wchar_t*>
        || std::is_same_v<T, const wchar_t* const>
        || std::is_same_v<T, const volatile wchar_t*>
        || std::is_same_v<T, const volatile wchar_t* const>
        || std::is_same_v<T, const wchar_t[Size]>
        || std::is_same_v<T, const volatile wchar_t[Size]>
};

// Unicode Text Objects -------------------------------------------------------

template <
    typename T
>
constexpr bool is_writable_unicode_text_object_v{
    is_writable_utf8_string_v<T>
        || is_writable_utf16_string_v<T>
        || is_writable_utf32_string_v<T>
        || is_writable_wide_string_v<T>
};

template <
    typename T
>
constexpr bool is_unicode_text_object_v{
    is_utf8_string_v<T>
        || is_utf16_string_v<T>
        || is_utf32_string_v<T>
        || is_wide_string_v<T>
};

template <
    typename T
>
constexpr bool is_unicode_text_object_view_v{
    std::is_same_v<std::remove_cv_t<T>, std::u8string_view>
        || std::is_same_v<std::remove_cv_t<T>, std::u16string_view>
        || std::is_same_v<std::remove_cv_t<T>, std::u32string_view>
        || std::is_same_v<std::remove_cv_t<T>, std::wstring_view>
};

template <
    typename T
>
constexpr bool is_writable_raii_unicode_text_object_v{
    is_writable_unicode_text_object_v<T>
        && !std::is_pointer_v<std::decay_t<T>>
};

template <
    typename T
>
constexpr bool is_raii_unicode_text_object_v{
    is_unicode_text_object_v<T>
        && !is_unicode_text_object_view_v<T>
        && !std::is_pointer_v<std::decay_t<T>>
};

// Text Objects ---------------------------------------------------------------

template <
    typename T
>
constexpr bool is_writable_text_object_v{
    is_writable_unicode_text_object_v<T>
        || is_writable_char_string_v<T>
};

template <
    typename T
>
constexpr bool is_text_object_v{
    is_unicode_text_object_v<T>
        || is_char_string_v<T>
};

template <
    typename T
>
constexpr bool is_text_object_view_v{
    is_unicode_text_object_view_v<T>
        || std::is_same_v<std::remove_cv_t<T>, std::string_view>
};

template <
    typename T
>
constexpr bool is_writable_raii_text_object_v{
    is_writable_text_object_v<T>
        && !std::is_pointer_v<std::decay_t<T>>
};

template <
    typename T
>
constexpr bool is_raii_text_object_v{
    is_text_object_v<T>
        && !is_text_object_view_v<T>
        && !std::is_pointer_v<std::decay_t<T>>
};

} // namespace ----------------------------------------------------------------

#endif // CMP_UNICODE_TYPE_TRAITS_HPP_INCLUDED
