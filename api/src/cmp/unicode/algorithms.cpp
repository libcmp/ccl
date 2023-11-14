// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/algorithms.hpp>

namespace cmp {

std::size_t
string_size (
    const std::string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u8string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u16string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u32string& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::wstring& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u8string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u16string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u32string_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::wstring_view& s
)
noexcept
{
    return std::size(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char* s
)
noexcept
{
    return std::strlen(s);
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char8_t* s
)
noexcept
{
    const char8_t* current{s};
    while (*current != u8'\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char16_t* s
)
noexcept
{
    const char16_t* current{s};
    while (*current != u'\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const char32_t* s
)
noexcept
{
    const char32_t* current{s};
    while (*current != U'\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const wchar_t* s
)
noexcept
{
    return std::wcslen(s);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
