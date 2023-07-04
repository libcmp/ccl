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
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u8string& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u16string& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u32string& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::wstring& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::string_view& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u8string_view& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u16string_view& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::u32string_view& s
)
noexcept
{
    return s.size();
} // function -----------------------------------------------------------------

std::size_t
string_size (
    const std::wstring_view& s
)
noexcept
{
    return s.size();
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
    while (*current != '\0') {
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
    while (*current != '\0') {
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
    while (*current != '\0') {
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
    const wchar_t* current{s};
    while (*current != '\0') {
        ++current;
    }
    return current - s;
} // function -----------------------------------------------------------------

void
insert_code_point (
    std::u8string& s,
    char32_t code_point,
    std::u8string::size_type index
) {
    if (!is_code_point_valid(code_point)) {
        throw invalid_code_point{};
    }

    if (fits_in_7_bits(code_point)) {
        s.insert(index, 1, static_cast<char8_t>(code_point));
    } else if (code_point <= 0b0111'1111'1111) {
        s.insert(
            index++,
            1,
            static_cast<char8_t>(
                (code_point >> 6) | 0b1100'0000
            )
        );
        s.insert(
            index,
            1,
            static_cast<char8_t>(
                (code_point & 0b0011'1111) | 0b1000'0000
            )
        );
    } else if (code_point <= 0b1111'1111'1111'1111) {
        s.insert(
            index++,
            1,
            static_cast<char8_t>(
                (code_point >> 12) | 0b1110'0000
            )
        );
        s.insert(
            index++,
            1,
            static_cast<char8_t>(
                ((code_point >> 6) & 0b0011'1111) | 0b1000'0000
            )
        );
        s.insert(
            index,
            1,
            static_cast<char8_t>(
                (code_point & 0b0011'1111) | 0b1000'0000
            )
        );
    } else {
        s.insert(
            index++,
            1,
            static_cast<char8_t>(
                (code_point >> 18) | 0b1111'0000
            )
        );
        s.insert(
            index++,
            1,
            static_cast<char8_t>(
                ((code_point >> 12) & 0b0011'1111) | 0b1000'0000
            )
        );
        s.insert(
            index++,
            1,
            static_cast<char8_t>(
                ((code_point >> 6) & 0b0011'1111) | 0b1000'0000
            )
        );
        s.insert(
            index,
            1,
            static_cast<char8_t>(
                (code_point & 0b0011'1111) | 0b1000'0000
            )
        );
    }
} // function -----------------------------------------------------------------

void
insert_code_point (
    std::u16string& s,
    char32_t code_point,
    std::u16string::size_type index
) {
    if (
        !is_surrogate(code_point)
            && code_point <= maximum_bmp_code_point
    ) {
        s.insert(index, 1, static_cast<char16_t>(code_point));
    } else {
        code_point -= 0x10000;
        s.insert(
            index++,
            1,
            static_cast<char16_t>(
                ((0b1111'1111'1100'0000'0000 & code_point) >> 10)
                    + leading_surrogate_minimum_value
            )
        );
        s.insert(
            index,
            1,
            static_cast<char16_t>(
                (0b0000'0000'0011'1111'1111 & code_point)
                    + trailing_surrogate_minimum_value
            )
        );
    }
} // function -----------------------------------------------------------------

void
insert_code_point (
    std::u32string& s,
    char32_t code_point,
    std::u32string::size_type index
) {
    s.insert(index, 1, code_point);
} // function -----------------------------------------------------------------

void
insert_code_point (
    std::wstring& s,
    char32_t code_point,
    std::wstring::size_type index
) {
    if constexpr (sizeof (wchar_t) == 2) {
        if (
            !is_surrogate(code_point)
                && code_point <= maximum_bmp_code_point
        ) {
            s.insert(index, 1, static_cast<char16_t>(code_point));
        } else {
            code_point -= 0x10000;
            s.insert(
                index++,
                1,
                static_cast<char16_t>(
                    ((0b1111'1111'1100'0000'0000 & code_point) >> 10)
                        + leading_surrogate_minimum_value
                )
            );
            s.insert(
                index,
                1,
                static_cast<char16_t>(
                    (0b0000'0000'0011'1111'1111 & code_point)
                        + trailing_surrogate_minimum_value
                )
            );
        }
    } else {
        s.insert(index, 1, code_point);
    }
} // function -----------------------------------------------------------------

std::u8string
to_u8string (
    const std::string& s
) {
    std::u8string result;
    result.reserve(string_size(s));
    for (char current_char : s) {
        append_code_point(result, static_cast<char32_t>(current_char));
    }
    return result;
} // function -----------------------------------------------------------------

std::u16string
to_u16string (
    const std::string& s
) {
    std::u16string result;
    result.reserve(string_size(s));
    for (char current_char : s) {
        append_code_point(result, static_cast<char32_t>(current_char));
    }
    return result;
} // function -----------------------------------------------------------------

std::u32string
to_u32string (
    const std::string& s
) {
    std::u32string result;
    result.reserve(string_size(s));
    for (char current_char : s) {
        append_code_point(result, static_cast<char32_t>(current_char));
    }
    return result;
} // function -----------------------------------------------------------------

std::wstring
to_wstring (
    const std::string& s
) {
    std::wstring result;
    result.reserve(string_size(s));
    for (char current_char : s) {
        append_code_point(result, static_cast<wchar_t>(current_char));
    }
    return result;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
